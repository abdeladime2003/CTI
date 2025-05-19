from pymongo import MongoClient #type: ignore
def get_mongo_connexion():
    client = MongoClient("mongodb://localhost:27017/")
    db = client["cybersec_db"]
    alerts_collection = db["alerts"]
    return alerts_collection
    