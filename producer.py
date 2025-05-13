# producer.py
from kafka import KafkaProducer
import json
import time
import random
producer = KafkaProducer(
    bootstrap_servers='localhost:9092',
    value_serializer=lambda v: json.dumps(v).encode('utf-8')
)

def generate_log():
    return {
        "timestamp": time.time(),
        "src_ip": f"192.168.1.{random.randint(1, 255)}",
        "dst_ip": f"10.0.0.{random.randint(1, 255)}",
        "port": random.choice([22, 80, 443, 8080, 3389]),
        "protocol": random.choice(["TCP", "UDP"]),
        "bytes_sent": random.randint(100, 5000)
    }

while True:
    log = generate_log()
    producer.send('network-logs', log)
    print("Sent:", log)
    time.sleep(1)
