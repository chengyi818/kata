import bluetooth

nearby_devices = bluetooth.discover_devices()
print(nearby_devices)
for mac in nearby_devices:
    print(bluetooth.lookup_name(mac))
