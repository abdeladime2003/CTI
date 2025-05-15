from pyspark.sql import SparkSession
from pyspark.sql.functions import from_json, col
from pyspark.sql.types import StructType, StringType

# Définir le schéma des logs
log_schema = StructType() \
    .add("_id", StringType()) \
    .add("timestamp", StringType()) \
    .add("src_ip", StringType()) \
    .add("dst_ip", StringType()) \
    .add("port", StringType()) \
    .add("protocol", StringType()) \
    .add("bytes_sent", StringType()) \
    .add("processed", StringType())

# Créer une SparkSession avec la configuration correcte pour MongoDB 10.3.0
spark = SparkSession.builder \
    .appName("KafkaToMongoDB") \
    .config("spark.jars.packages", "org.mongodb.spark:mongo-spark-connector_2.12:10.3.0") \
    .config("spark.mongodb.connection.uri", "mongodb://172.30.240.1:27017") \
    .getOrCreate()

# Lire le stream depuis Kafka
df_raw = spark.readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "localhost:9092") \
    .option("subscribe", "logs-topic") \
    .option("startingOffsets", "latest") \
    .load()

# Convertir les messages Kafka en JSON
df_logs = df_raw.selectExpr("CAST(value AS STRING) as json_str") \
    .select(from_json(col("json_str"), log_schema).alias("data")) \
    .select("data.*")

# Filtrage d'exemple : UDP sur port 22
df_alerts = df_logs.filter((col("protocol") == "UDP") & (col("port") == "22"))

# Fonction batch pour écrire dans MongoDB avec le connecteur 10.3.0
def write_to_mongo(batch_df, batch_id):
    if not batch_df.isEmpty():
        batch_df.write \
            .format("mongodb") \
            .mode("append") \
            .option("database", "kafka_logs") \
            .option("collection", "alerts") \
            .save()
        print(f"Batch {batch_id} écrit dans MongoDB avec succès")
    else:
        print(f"Batch {batch_id} vide, rien à écrire")

# Démarrer le stream avec foreachBatch
query = df_alerts.writeStream \
    .foreachBatch(write_to_mongo) \
    .outputMode("append") \
    .option("checkpointLocation", "/tmp/spark_checkpoint_logs") \
    .start()

query.awaitTermination()