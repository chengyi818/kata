from scapy.all import DNS, IP, UDP, checksum, inet_aton, socket, struct


def pseudo_header(ip_src, ip_dst, ip_proto, length):
    """
    Return a pseudo header according to RFC768
    """
    # Prepare the binary representation of the pseudo header
    return struct.pack("!4s4sHH", inet_aton(ip_src), inet_aton(ip_dst),
                       ip_proto, length)


# Get the UDP checksum computed by Scapy
packet = IP(dst="10.11.12.13", src="10.11.12.14")/UDP()/DNS()
packet_raw = str(packet)
checksum_scapy = IP(packet_raw)[UDP].chksum

# Set the UDP checksum to 0 and compute the checksum 'manually'
packet = IP(dst="10.11.12.13", src="10.11.12.14")/UDP(chksum=0)/DNS()
packet_raw = str(packet)
udp_raw = packet_raw[20:]
phdr = pseudo_header(packet.src, packet.dst, socket.IPPROTO_UDP, len(udp_raw))

assert(checksum_scapy == checksum(phdr + udp_raw))
