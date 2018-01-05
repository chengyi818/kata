import ifaddr

adapters = ifaddr.get_adapters()

for adapter in adapters:
    print("IPs of netmask adapter: ", adapter.nice_name)
    for ip in adapter.ips:
        print(ip.ip, ip.network_prefix)
