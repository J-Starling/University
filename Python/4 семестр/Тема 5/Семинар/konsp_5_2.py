class BankAccount:
    def __init__(self, balance):
        self.__balance = balance

    def top_up(self, amount):
        self.__balance += amount

    def withdraw(self, amount):
        self.__balance -= amount

    def check(self):
        print("Your current balance:", self.__balance)


def main():
    balance = 300000
    a = BankAccount(balance)

    a.check()
    money_top = int(input("Write an amount to top up: "))
    a.top_up(money_top)
    a.check()
    money_with = int(input("Write an amount to withdraw: "))
    a.withdraw(money_with)
    a.check()


if __name__ == "__main__":
    main()
