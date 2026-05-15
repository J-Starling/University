from oil_storage import OilStorage


def separator(title: str = "") -> None:
    line = "─" * 55
    if title:
        print(f"\n{line}\n  {title}\n{line}")
    else:
        print(line)


separator("Создание объектов")

tank1 = OilStorage(
    name="Резервуар РВС-1",
    location="Самара",
    capacity=10_000,
    oil_type="Urals",
    year_built=2005,
)

tank2 = OilStorage.create_default("Резервуар РВС-2", "Уфа")

print(tank1.get_info())
print()
print(tank2.get_info())

separator("Заполнение и откачка")

tank1.fill(7_500)
tank2.fill(3_200)

print(f"tank1 заполнен на {tank1.fill_percentage}%")
print(f"tank2 заполнен на {tank2.fill_percentage}%")

tank1.drain(1_000)
print(f"После откачки 1000 м³: tank1 = {tank1.current_volume:.0f} м³")

print("\nПопытка закачать лишнего:")
tank2.fill(3_000)   # свободно лишь 1800 м³

separator("__str__ и __bool__")

print(tank1)
print(tank2)
print(f"В tank1 есть нефть? → {bool(tank1)}")

empty = OilStorage("Пустой", "Казань", 2000, "Brent")
print(f"В empty есть нефть?  → {bool(empty)}")

separator("Оператор + (объединение)")

combined = tank1 + tank2
print(combined)
print(combined.get_info())

separator("Операторы сравнения >= и >")

print(f"tank1 ({tank1.current_volume:.0f} м³) >= tank2 \
      ({tank2.current_volume:.0f} м³) ? → {tank1 >= tank2}")
print(f"tank2 ({tank2.current_volume:.0f} м³) >  tank1 \
      ({tank1.current_volume:.0f} м³) ? → {tank2 > tank1}")

separator("__len__ и is_full()")

print(f"len(tank1) = {len(tank1)} м³  (вместимость)")
print(f"tank1 полон? → {tank1.is_full()}")

tank1.fill(99_999)   # зальём под завязку
print(f"После заполнения: tank1 полон? → {tank1.is_full()}")

separator("Давление (приватный атрибут)")

tank1.set_pressure(1.8)
print(f"Давление в tank1: {tank1.get_pressure()} атм")

separator("Статический метод: конвертация баррелей → м³")

barrels = 50_000
m3 = OilStorage.barrels_to_m3(barrels)
print(f"{barrels:,} баррелей = {m3:,.3f} м³")

separator("Метод класса: счётчик экземпляров")

print(f"Всего создано нефтехранилищ: {OilStorage.get_count()}")

separator("__eq__")

twin = OilStorage("Резервуар РВС-1", "Самара", 8_000, "Brent")
print(f"tank1 == twin (одно имя и место)? → {tank1 == twin}")
print(f"tank1 == tank2? → {tank1 == tank2}")
