class CarEngine:
    def start(self):
        print("Car engine started")


class PlaneEngine:
    def start(self):
        print("Plane engine started")


class EngineStarter:
    # 这个类提供了start_engine方法，但是它不初始化engine
    def start_engine(self):
        self.engine.start()


class Car(EngineStarter):
    def __init__(self):
        self.engine = CarEngine()


class Plane(EngineStarter):
    def __init__(self):
        self.engine = PlaneEngine()


# 外部代码
my_car = Car()
my_car.start_engine()  # 输出: Car engine started

my_plane = Plane()
my_plane.start_engine()  # 输出: Plane engine started
