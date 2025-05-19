from pyspark.sql import SparkSession #type: ignore
from pyspark.sql.functions import from_json, col #type: ignore
from pyspark.sql.types import StructType, DoubleType, StringType #type: ignore
from pyspark.ml import PipelineModel #type: ignore

# 1. Créer la session Spark
spark = SparkSession.builder.appName("CyberAttackDetection").getOrCreate()

# 2. Définir le schéma
schema = StructType()
for colname in [
    'Flow ID', 'Source IP', 'Source Port', 'Destination IP', 'Destination Port',
    'Protocol', 'Timestamp', 'Flow Duration', 'Total Fwd Packets', 'Total Backward Packets',
    'Total Length of Fwd Packets', 'Total Length of Bwd Packets', 'Fwd Packet Length Max',
    'Fwd Packet Length Min', 'Fwd Packet Length Mean', 'Fwd Packet Length Std', 'Bwd Packet Length Max',
    'Bwd Packet Length Min', 'Bwd Packet Length Mean', 'Bwd Packet Length Std', 'Flow Bytes/s',
    'Flow Packets/s', 'Flow IAT Mean', 'Flow IAT Std', 'Flow IAT Max', 'Flow IAT Min', 'Fwd IAT Total',
    'Fwd IAT Mean', 'Fwd IAT Std', 'Fwd IAT Max', 'Fwd IAT Min', 'Bwd IAT Total', 'Bwd IAT Mean',
    'Bwd IAT Std', 'Bwd IAT Max', 'Bwd IAT Min', 'Fwd PSH Flags', 'Bwd PSH Flags', 'Fwd URG Flags',
    'Bwd URG Flags', 'Fwd Header Length40', 'Bwd Header Length', 'Fwd Packets/s', 'Bwd Packets/s',
    'Min Packet Length', 'Max Packet Length', 'Packet Length Mean', 'Packet Length Std',
    'Packet Length Variance', 'FIN Flag Count', 'SYN Flag Count', 'RST Flag Count', 'PSH Flag Count',
    'ACK Flag Count', 'URG Flag Count', 'CWE Flag Count', 'ECE Flag Count', 'Down/Up Ratio',
    'Average Packet Size', 'Avg Fwd Segment Size', 'Avg Bwd Segment Size', 'Fwd Header Length61',
    'Fwd Avg Bytes/Bulk', 'Fwd Avg Packets/Bulk', 'Fwd Avg Bulk Rate', 'Bwd Avg Bytes/Bulk',
    'Bwd Avg Packets/Bulk', 'Bwd Avg Bulk Rate', 'Subflow Fwd Packets', 'Subflow Fwd Bytes',
    'Subflow Bwd Packets', 'Subflow Bwd Bytes', 'Init_Win_bytes_forward', 'Init_Win_bytes_backward',
    'act_data_pkt_fwd', 'min_seg_size_forward', 'Active Mean', 'Active Std', 'Active Max', 'Active Min',
    'Idle Mean', 'Idle Std', 'Idle Max', 'Idle Min'
]:
    schema = schema.add(colname, DoubleType())

# Colonnes non utilisées comme features
excluded = ['Flow ID', 'Source IP', 'Source Port', 'Destination IP', 'Destination Port', 'Protocol', 'Timestamp']
feature_cols = [colname for colname in schema.fieldNames() if colname not in excluded]

# 3. Lire le flux Kafka
df_raw = spark.readStream \
    .format("kafka") \
    .option("kafka.bootstrap.servers", "localhost:9092") \
    .option("subscribe", "cyber_logs") \
    .load()

# 4. Parser le JSON
df_parsed = df_raw.selectExpr("CAST(value AS STRING)") \
    .select(from_json(col("value"), schema).alias("data")) \
    .select("data.*")

# 5. Cast explicite et traitement des valeurs null
for f in feature_cols:
    df_parsed = df_parsed.withColumn(f, col(f).cast("double"))

# 6. Remplacer les valeurs null par 0.0
df_clean = df_parsed.fillna(0.0)

# 7. Charger le modèle entraîné
model = PipelineModel.load("/home/abdo/Cti_Project/content/random_forest_best_model")

# 8. Appliquer le modèle
df_predicted = model.transform(df_clean)

# 9. Afficher les prédictions
query = df_predicted.select("prediction") \
    .writeStream \
    .format("console") \
    .outputMode("append") \
    .start()

query.awaitTermination()
