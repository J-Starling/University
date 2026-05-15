"""
Модуль для работы с нефтехранилищами.

Иерархия классов:
    StorageFacility  —  базовый класс промышленного объекта хранения
    OilStorage       —  нефтехранилище (наследник StorageFacility)
"""


class StorageFacility:
    """Базовый класс промышленного объекта хранения."""

    def __init__(self, name: str, location: str, capacity: float):
        self.name = name
        self.location = location
        self.capacity = capacity  # м³

    def get_info(self) -> str:
        return f"Объект: {self.name}, Расположение: {self.location},\
        Вместимость: {self.capacity} м³"

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}(name={self.name!r},\
              location={self.location!r}, capacity={self.capacity})"


class OilStorage(StorageFacility):
    """
    Нефтехранилище — наземный резервуарный парк для хранения нефти.

    Атрибуты:
        name (str)            — название хранилища
        location (str)        — местоположение
        capacity (float)      — максимальный объём, м³
        oil_type (str)        — марка/тип нефти
        year_built (int)      — год постройки
        current_volume (float)— текущий объём нефти, м³
        _temperature (float)  — рабочая температура хранения, °C  [защищённый]
        __pressure (float)    — давление в резервуаре, атм         [приватный]
    """

    _count = 0  # счётчик созданных экземпляров (атрибут класса)

    def __init__(
        self,
        name: str,
        location: str,
        capacity: float,
        oil_type: str,
        year_built: int = 2000,
        current_volume: float = 0.0,
        temperature: float = 15.0,
        pressure: float = 1.0,
    ):
        super().__init__(name, location, capacity)
        self.oil_type = oil_type
        self.year_built = year_built
        self.current_volume = current_volume
        self._temperature = temperature   # защищённый
        self.__pressure = pressure        # приватный
        OilStorage._count += 1

    @property
    def fill_percentage(self) -> float:
        """Процент заполнения резервуара."""
        return round(self.current_volume / self.capacity * 100, 2)

    def fill(self, amount: float) -> None:
        """Закачать нефть в хранилище (м³)."""
        if amount <= 0:
            raise ValueError("Объём должен быть положительным.")
        free = self.capacity - self.current_volume
        added = min(amount, free)
        self.current_volume += added
        overflow = amount - added
        if overflow > 0:
            print(
                f"Переполнение: {overflow:.1f} м³ не вошло в '{self.name}'.")

    def drain(self, amount: float) -> None:
        """Откачать нефть из хранилища (м³)."""
        if amount <= 0:
            raise ValueError("Объём должен быть положительным.")
        drained = min(amount, self.current_volume)
        self.current_volume -= drained
        shortage = amount - drained
        if shortage > 0:
            print(f"  [!] В '{self.name}' не хватило {shortage:.1f} м³.")

    def is_full(self) -> bool:
        """Возвращает True, если резервуар заполнен до максимума."""
        return self.current_volume >= self.capacity

    def set_pressure(self, value: float) -> None:
        """Установить давление в резервуаре (атм)."""
        if value < 0:
            raise ValueError("Давление не может быть отрицательным.")
        self.__pressure = value

    def get_pressure(self) -> float:
        """Получить текущее давление (атм)."""
        return self.__pressure

    def get_info(self) -> str:
        """Расширенная информация о нефтехранилище."""
        base = super().get_info()
        return (
            f"{base}\n"
            f"  Тип нефти: {self.oil_type}, Год постройки: {self.year_built}\n"
            f"  Заполнено: {self.current_volume:.1f} м³\
                  ({self.fill_percentage}%)\n"
            f"  Температура: {self._temperature}°C,\
                  Давление: {self.__pressure} атм"
        )

    @classmethod
    def get_count(cls) -> int:
        """Возвращает общее количество созданных нефтехранилищ."""
        return cls._count

    @classmethod
    def create_default(cls, name: str, location: str) -> "OilStorage":
        """Создать нефтехранилище со стандартными параметрами."""
        return cls(name, location, capacity=5000.0, oil_type="Urals")

    @staticmethod
    def barrels_to_m3(barrels: float) -> float:
        """Перевести баррели нефти в кубические метры."""
        return round(barrels * 0.158987, 3)

    def __str__(self) -> str:
        return (
            f"OilStorage «{self.name}» | {self.oil_type} | "
            f"{self.current_volume:.0f}/{self.capacity:.0f} м³\
                  ({self.fill_percentage}%)"
        )

    def __repr__(self) -> str:
        return (
            f"OilStorage(name={self.name!r}, location={self.location!r}, "
            f"capacity={self.capacity}, oil_type={self.oil_type!r}, "
            f"current_volume={self.current_volume})"
        )

    def __add__(self, other: "OilStorage") -> "OilStorage":
        """
        Объединить два хранилища в одно суммарное.
        Новый резервуар: суммарная вместимость и суммарный текущий объём.
        """
        if not isinstance(other, OilStorage):
            return NotImplemented
        return OilStorage(
            name=f"{self.name} + {other.name}",
            location=f"{self.location} / {other.location}",
            capacity=self.capacity + other.capacity,
            oil_type=self.oil_type if self.oil_type == other.oil_type
            else "Смесь",
            current_volume=self.current_volume + other.current_volume,
        )

    def __ge__(self, other: "OilStorage") -> bool:
        """Сравнить хранилища по текущему объёму нефти (>=)."""
        if not isinstance(other, OilStorage):
            return NotImplemented
        return self.current_volume >= other.current_volume

    def __gt__(self, other: "OilStorage") -> bool:
        """Сравнить хранилища по текущему объёму нефти (>)."""
        if not isinstance(other, OilStorage):
            return NotImplemented
        return self.current_volume > other.current_volume

    def __eq__(self, other: object) -> bool:
        """Два хранилища равны, если совпадают название и местоположение."""
        if not isinstance(other, OilStorage):
            return NotImplemented
        return self.name == other.name and self.location == other.location

    def __bool__(self) -> bool:
        """Хранилище «истинно», если в нём есть нефть."""
        return self.current_volume > 0

    def __len__(self) -> int:
        """len() возвращает вместимость резервуара в целых м³."""
        return int(self.capacity)
