class Bank:
    def __init__(self, accounts):
        self.accounts = accounts


class Account:
    def __init__(self, balance):
        self.__balance = balance

    def top_up(self, amount):
        self.__balance += amount

    def withdraw(self, amount):
        self.__balance -= amount

    def check(self):
        print("Your current balance:", self.__balance)

    def get_balance(self):
        return self.__balance

    def set_balance(self, balance):
        self.__balance = balance


class SavingAccount(Account):
    def procents(self):
        current_balance = self.get_balance()
        self.set_balance(current_balance * 1.12)

    def commission(self):
        current_balance = self.get_balance()
        self.set_balance(current_balance * 0.99)


class CheckingAccount(Account):
    def procents(self):
        current_balance = self.get_balance()
        self.set_balance(current_balance + 20000)

    def commission(self):
        current_balance = self.get_balance()
        self.set_balance(current_balance * 0.86)


def main():
    saving_acc = SavingAccount(1000)
    checking_acc = CheckingAccount(5000)

    print("Saving Account:")
    saving_acc.check()
    saving_acc.procents()
    saving_acc.commission()
    saving_acc.check()

    print("Checking Account:")
    checking_acc.check()
    checking_acc.procents()
    checking_acc.commission()
    checking_acc.check()


if __name__ == "__main__":
    main()
