from confluent_kafka import Consumer, KafkaException, KafkaError  #type:ignore

# Configuration du Consumer
conf = {
    'bootstrap.servers': 'localhost:9092',  # Adresse du broker Kafka
    'group.id': 'python-consumer',  # Nom du groupe de consommateurs
    'auto.offset.reset': 'earliest'  # Lire les messages depuis le début
}

# Création du Consumer
consumer = Consumer(conf)

# S'abonner à un topic
consumer.subscribe(['test-topic'])

try:
    while True:
        msg = consumer.poll(1.0)  # Attendre un message (timeout de 1 seconde)

        if msg is None:
            continue  # Pas de message disponible
        if msg.error():
            if msg.error().code() == KafkaError._PARTITION_EOF:
                print(f"End of partition reached: {msg.topic()} [{msg.partition()}]")
            else:
                raise KafkaException(msg.error())
        else:
            # Affichage du message
            print(f"Message reçu: {msg.value().decode('utf-8')}")

except KeyboardInterrupt:
    pass
finally:
    # Fermeture du consumer
    consumer.close()
