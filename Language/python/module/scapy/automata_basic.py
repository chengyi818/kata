from scapy.all import *


class HelloWorld(Automaton):
    @ATMT.state(initial=1)
    def BEGIN(self):
        print("State=BEGIN")

    @ATMT.condition(BEGIN)
    def wait_for_nothing(self):
        print("Wait for nothing...")
        raise self.END()

    @ATMT.action(wait_for_nothing)
    def on_nothing(self):
        print("Action on 'nothing' condition")

    @ATMT.state(final=1)
    def END(self):
        print("State=END")


a = HelloWorld()
HelloWorld.graph()
a.run()
