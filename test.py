import random
import time
import json
from datetime import datetime
from kafka import KafkaProducer

# Initialisation du producer Kafka (remplace 'localhost:9092' si besoin)
producer = KafkaProducer(
    bootstrap_servers='localhost:9092',
    value_serializer=lambda v: json.dumps(v).encode('utf-8')
)

# Paramètres
ips = [f"192.168.1.{i}" for i in range(1, 100)]
methods = ["GET", "POST", "PUT", "DELETE"]
normal_paths = ["/", "/index.html", "/home", "/dashboard", "/api/user", "/login"]
attack_paths = [
    "/admin", "/wp-login.php", "/.env", "/etc/passwd",
    "/login?user=admin'--", "/api/deleteAll", "/search?q=../../../../etc/shadow"
]
status_normal = [200, 200, 200, 404, 500]
status_attack = [403, 500, 401]

# Générateur de log
def generate_log():
    is_attack = random.random() < 0.1  # 10% de logs sont des attaques
    ip = random.choice(ips)
    method = random.choice(methods)
    path = random.choice(attack_paths if is_attack else normal_paths)
    status = random.choice(status_attack if is_attack else status_normal)

    log_entry = {
        "timestamp": datetime.utcnow().isoformat(),
        "ip": ip,
        "method": method,
        "path": path,
        "status": status,
        "label": "attack" if is_attack else "normal"
    }

    return log_entry

# Boucle de simulation
while True:
    log = generate_log()
    print(log)  # Affiche dans le terminal
    producer.send("web-logs", value=log)
    time.sleep(0.5)  # Fréquence d'envoi
