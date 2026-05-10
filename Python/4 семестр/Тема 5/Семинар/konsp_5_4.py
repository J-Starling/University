class Temperature:
    def __init__(self, temperature):
        self._celsius = temperature

    @property
    def farenheit(self):
        return self._celsius * 1.8 + 32


def main():
    t = int(input("Write a temperature in Celsius: "))
    cel = Temperature(t)

    print("Temeperature in Farenheit:", cel.farenheit)


if __name__ == "__main__":
    main()
