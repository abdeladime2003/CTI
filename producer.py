from kafka import KafkaProducer
from pymongo import MongoClient
import json
import time
import subprocess

def get_default_gateway_via_ip_route():
    try:
        result = subprocess.run(['ip', 'route'], stdout=subprocess.PIPE, text=True)
        for line in result.stdout.splitlines():
            if line.startswith('default via'):
                parts = line.split()
                return parts[2] 
        return "Pas de gateway trouvée"
    except Exception as e:
        return f"Erreur: {e}"
ip_address = get_default_gateway_via_ip_route()
mongo_client = MongoClient(f"mongodb://{ip_address}:27017/")
db = mongo_client["kafka_logs"]
collection = db["logs_raw"]

# Connexion Kafka
producer = KafkaProducer(
    bootstrap_servers="localhost:9092",
    value_serializer=lambda v: json.dumps(v).encode('utf-8')
)

topic_name = "cyber_logs"

# Lire les documents de MongoDB et envoyer vers Kafka
def send_logs_to_kafka():
    for doc in collection.find(limit=10):  # Limiter à 10 documents pour la démonstratio
        # Supprimer le _id car BSON ObjectId n'est pas sérialisable
        if '_id' in doc:
            del doc['_id']
        
        print(f"Envoi : {doc}")
        producer.send(topic_name, doc)
        time.sleep(1)  # simuler le streaming avec 1 seconde de délai
    
    producer.flush() # Assurez-vous que tous les messages sont envoyés
    print("Tous les logs ont été envoyés.")

if __name__ == "__main__":
    send_logs_to_kafka()
