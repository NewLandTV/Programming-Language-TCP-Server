import socket

BUFFER_SIZE = 2048

host = "127.0.0.1"
port = 2222

clientSocket = socket.socket(socket.AF_INET ,socket.SOCK_STREAM)

clientSocket.connect((host, port))

buffer = input()

clientSocket.send(buffer.encode("ascii"))
buffer = clientSocket.recv(BUFFER_SIZE)

print("From server : ", buffer)

clientSocket.Close()