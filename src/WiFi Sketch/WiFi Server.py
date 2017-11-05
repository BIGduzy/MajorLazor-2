import socket
import sys
import json
import os

players = []
failCount = 0

def cls():
    os.system('cls' if os.name=='nt' else 'clear')

def registerPlayer(playerId, lives):
    newPlayer = {'id': playerId, 'lives': lives}
    value = [player for player in players if player['id'] == playerId]
    if value:
        print("invalid player id registerd")
    else:
        players.append(newPlayer)

def updatePlayer(playerId, damage):
    value = [player for player in players if player['id'] == playerId]
    if value:
        value[0]['lives'] = value[0]['lives'] - damage
    #print(value)

def showStats():
    #cls()
    print("-" * 30)
    for entry in players:
        print(entry['id'], "--", entry['lives'])

    print("-" * 30)


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('192.168.1.25', 1337)
print('starting up on {} port {}'.format(*server_address))
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    #print('waiting for a connection')
    connection, client_address = sock.accept()
    try:
        #print('connection from', client_address)

        # Receive the data in small chunks and retransmit it
        while True:
            data = connection.recv(1024)
            #print('received {!r}'.format(data))
            if data:
                try:
                    jsonDump = json.loads(data.decode())
                except:
                    failCount += 1
                #print("PlayerId:", jsonDump['data'][0], "-- Damage:", jsonDump['data'][1])
                #print('sending data back to the client')
                if (jsonDump['ID'][0] == 0):
                    registerPlayer(jsonDump['data'][0], jsonDump['data'][1])
                elif (jsonDump['ID'][0] == 1):
                    updatePlayer(jsonDump['data'][0], jsonDump['data'][1])

                showStats()
                
                #connection.sendall(b"accepted\r")
            else:
                #print('no data from', client_address)
                break

    finally:
        # Clean up the connection
        connection.close()
