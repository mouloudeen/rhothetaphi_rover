import socket
import json


class ihm():

    def __init__(self):
        # constructeur
        self.HOST = "193.253.53.72"
        self.port = 2302

    def sendClient(self, data):
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect((self.HOST, self.port))
        dataString = json.dumps(data)
        n = client.send(dataString.encode("utf-8"))
        if n != lend(data):
            print("Erreur !")
        client.close()
