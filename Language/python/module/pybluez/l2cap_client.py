import bluetooth


server_address = "B8:27:EB:5C:5C:01"
port = 0x1001

sock = bluetooth.BluetoothSocket(bluetooth.L2CAP)
sock.connect((server_address, port))

sock.send("hello world!")

sock.close()
