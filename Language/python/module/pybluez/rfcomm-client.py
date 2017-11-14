import bluetooth

server_address = "00:1A:7D:DA:71:11"
port = 1

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((server_address, port))
sock.send("hello world!")

sock.close()
