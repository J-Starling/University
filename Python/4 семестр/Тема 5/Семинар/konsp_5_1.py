class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def greet(self):
        print("Greetings, ", self.name, "!", sep="")


def main():
    name = input("Write your name: ")
    age = int(input("Write your age: "))

    p = Person(name, age)
    p.greet()


if __name__ == "__main__":
    main()
