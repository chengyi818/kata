Import WMI

def getlocalip():
    local = wmi.WMI()
    for interface in local.Win32_NetworkAdapterConfiguration(IPEnabled=1):
        for ip_address in interface.IPAddress:
            if ip_address != '0.0.0.0':
                localip = ip_address
    return localip
