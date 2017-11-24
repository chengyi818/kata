class fruit(object):
    def show_weight(self):
        print("fruit show weight: ", self.weight)

    def show_price(self):
        print("fruit show price: ", self.price)


class apple(fruit):
    def __init__(self, owner, weight, price):
        self.owner = owner
        self.__weight = weight
        self.price = price

    def show_owner(self):
        print("apple show owner: ", self.owner)

    # def show_weight(self):
    #     print("apple show weight: ", self.weight)


if __name__ == "__main__":
    tmp_apple = apple("Lily", "500g", 10)
    tmp_apple.show_weight()
    tmp_apple.show_price()
    tmp_apple.show_owner()
