import bluetooth
import select

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.setblocking(False)

try:
    sock.connect(("B8:27:EB:5C:5C:01", 3))
except:
    pass

while True:
    print("waiting for connection")
    readable, writable, excepts = select.select([], [sock], [], 1)
    if sock in writable:
        sock.send("hello world!")
        sock.close()
        break
