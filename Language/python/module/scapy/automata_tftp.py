from scapy.all import *


class TFTP_read(Automaton):
    def parse_args(self, filename, server, sport = None, port=69, **kargs):
        Automaton.parse_args(self, **kargs)
        self.filename = filename
        self.server = server
        self.port = port
        self.sport = sport

    def master_filter(self, pkt):
        return ( IP in pkt and pkt[IP].src == self.server and UDP in pkt
                 and pkt[UDP].dport == self.my_tid
                 and (self.server_tid is None or pkt[UDP].sport == self.server_tid) )

    # BEGIN
    @ATMT.state(initial=1)
    def BEGIN(self):
        self.blocksize=512
        self.my_tid = self.sport or RandShort()._fix()
        bind_bottom_up(UDP, TFTP, dport=self.my_tid)
        self.server_tid = None
        self.res = ""

        self.l3 = IP(dst=self.server)/UDP(sport=self.my_tid, dport=self.port)/TFTP()
        self.last_packet = self.l3/TFTP_RRQ(filename=self.filename, mode="octet")
        self.send(self.last_packet)
        self.awaiting=1

        raise self.WAITING()

    # WAITING
    @ATMT.state()
    def WAITING(self):
        pass

    @ATMT.receive_condition(WAITING)
    def receive_data(self, pkt):
        if TFTP_DATA in pkt and pkt[TFTP_DATA].block == self.awaiting:
            if self.server_tid is None:
                self.server_tid = pkt[UDP].sport
                self.l3[UDP].dport = self.server_tid
            raise self.RECEIVING(pkt)

    @ATMT.action(receive_data)
    def send_ack(self):
        self.last_packet = self.l3 / TFTP_ACK(block = self.awaiting)
        self.send(self.last_packet)

    @ATMT.receive_condition(WAITING, prio=1)
    def receive_error(self, pkt):
        if TFTP_ERROR in pkt:
            raise self.ERROR(pkt)

    @ATMT.timeout(WAITING, 3)
    def timeout_waiting(self):
        raise self.WAITING()

    @ATMT.action(timeout_waiting)
    def retransmit_last_packet(self):
        self.send(self.last_packet)

    # RECEIVED
    @ATMT.state()
    def RECEIVING(self, pkt):
        recvd = pkt[Raw].load
        self.res += recvd
        self.awaiting += 1
        if len(recvd) == self.blocksize:
            raise self.WAITING()
        raise self.END()

    # ERROR
    @ATMT.state(error=1)
    def ERROR(self,pkt):
        split_bottom_up(UDP, TFTP, dport=self.my_tid)
        return pkt[TFTP_ERROR].summary()

    #END
    @ATMT.state(final=1)
    def END(self):
        split_bottom_up(UDP, TFTP, dport=self.my_tid)
        return self.res


if __name__ == "__main__":
    # tmp_tftp = TFTP_read("my_file", "192.168.1.128")
    # tmp_tftp.run()
    TFTP_read.graph()
