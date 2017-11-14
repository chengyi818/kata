import sys
import bluetooth

service_matches = bluetooth.find_service(name="SampleServer",
                                         uuid=bluetooth.SERIAL_PORT_CLASS)

if len(service_matches) == 0:
    print("couldn't find the service")
    sys.exit()


first_match = service_matches[0]
port = first_match['port']
name = first_match['name']
host = first_match['host']

print("connecting to: ", host)

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((host, port))
sock.send("PyBluez client says hello")
data = sock.recv(1024)
print("received: ", data)

sock.close()
