from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .utils.mongo import get_mongo_connexion

class AlertListView(APIView):
    def get(self, request):
        # Projection : on ne récupère que les 5 colonnes souhaitées
        projection = {
            '_id': 0,
            'timestamp': 1,
            'src_ip': 1,
            'dst_ip': 1,
            'threat_type': 1,
            'prediction': 1
        }
        alerts_collection = get_mongo_connexion()
        alerts_cursor = alerts_collection.find({}, projection)
        alerts = list(alerts_cursor)
        return Response(alerts, status=status.HTTP_200_OK)
