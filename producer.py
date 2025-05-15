from kafka import KafkaProducer
from pymongo import MongoClient
import json
import time

# Connexion MongoDB
mongo_client = MongoClient("mongodb://172.30.240.1:27017/")
db = mongo_client["kafka_logs"]  
collection = db["logs_raw"] 
producer = KafkaProducer(
    bootstrap_servers='localhost:9092',
    value_serializer=lambda v: json.dumps(v).encode('utf-8')
)

# Lecture des logs et envoi dans Kafka
for log in collection.find():
    log['_id'] = str(log['_id'])
    producer.send("logs-topic", value=log)
    print(f"[✓] Log envoyé : {log}")
    time.sleep(0.5)  # Attente entre chaque envoi (simulation streaming)

producer.flush()
print("✔️ Tous les logs ont été envoyés.")
