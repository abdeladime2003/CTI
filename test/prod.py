from confluent_kafka import Producer #type:ignore

# Configuration du Producer
conf = {
    'bootstrap.servers': 'localhost:9092',  # Adresse de ton broker Kafka
    'client.id': 'python-producer'
}

# Création du Producer
producer = Producer(conf)

# Callback pour vérifier si le message a été bien envoyé
def delivery_report(err, msg):
    if err is not None:
        print(f"Message delivery failed: {err}")
    else:
        print(f"Message delivered to {msg.topic()} [{msg.partition()}]")

# Envoi d'un message
producer.produce('test-topic', key='key', value='Hello Kafka from Python!', callback=delivery_report)

# Attendre que tous les messages soient envoyés
producer.flush()
