import bluetooth
import select

server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
server_sock.setblocking(False)
server_sock.bind(("", 3))

while True:
    print("waiting for connection")
    readable, writable, excepts = select.select([server_sock], [], [], 1)
    if server_sock in readable:
        client_sock, client_info = server_sock.accept()
        client_sock.setblocking(False)
        print("Accepted connection from: ", client_info)
        break

while True:
    print("waiting for data")
    readable, writable, excepts = select.select([client_sock], [], [], 1)
    if client_sock in readable:
        data = client_sock.recv[1024]
        print("received: ", data)
        break

client_sock.close()
server_sock.close()
