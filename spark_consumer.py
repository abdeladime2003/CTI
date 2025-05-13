from pyspark.sql import SparkSession
from pyspark.sql.functions import expr

# Création de la SparkSession avec le connecteur MongoDB
spark = SparkSession.builder \
    .appName("MongoDBSparkConnectorFix") \
    .config("spark.jars.packages", "org.mongodb.spark:mongo-spark-connector_2.12:10.3.0") \
    .getOrCreate()

# Lecture du topic Kafka
logs = spark.readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "localhost:9092") \
    .option("subscribe", "network-logs") \
    .load()

# Décodage des messages Kafka (JSON brut)
logs_decoded = logs.selectExpr("CAST(value AS STRING) AS json")

# Extraction des champs JSON
logs_data = logs_decoded.select(
    expr("json_tuple(json, 'timestamp', 'src_ip', 'dst_ip', 'port', 'protocol', 'bytes_sent') as (timestamp, src_ip, dst_ip, port, protocol, bytes_sent)")
)

# Fonction de traitement de chaque micro-batch
def process_batch(df, epoch_id):
    if not df.isEmpty():
        df.show(truncate=False)  # Affiche les données traitées
        df.write \
            .format("mongo") \
            .option("uri", "mongodb://172.30.240.1:27017/kafka_logs.logs") \
            .mode("append") \
            .save()
        print(f"Batch {epoch_id} written to MongoDB")
    else:
        print(f"Batch {epoch_id} is empty")

# Exécution du flux avec foreachBatch vers MongoDB
logs_data.writeStream \
    .foreachBatch(process_batch) \
    .outputMode("append") \
    .option("checkpointLocation", "/tmp/spark_checkpoint") \
    .start() \
    .awaitTermination()
