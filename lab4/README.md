## Лабораторная работа №4

ФИО: Тимошенко Артём Романович

Группа: M8О-202БВ-25

Вариант: 9

## Классы

| Класс | Назначение |
|---|---|
| `Shape` | Абстрактный базовый класс |
| `Circle` | Круг с радиусом `r` |
| `Ellipse` | Эллипс с полуосями `a`, `b` |
| `Sector` | Сектор с радиусом `r` и углом `angle` |
| `Point` | Точка `(x, y)` |
| `ShapeCollection` | Коллекция фигур |

`Circle`, `Ellipse`, `Sector` публично наследуют `Shape`. Методы `metric()`, `containsPoint()`, `clone()`, `print()` и `read()` виртуальные. Методы, не изменяющие объект, имеют `const`. Виртуальный деструктор обеспечивает удаление через `Shape*`.

`metric()` вычисляет площадь: круг — `πr²`, эллипс — `πab`, сектор — `angle * r² / 2`. Особые методы: `radius()`, `isCircle()`, `isSemicircle()`.

`operator double()` возвращает площадь, `operator==` сравнивает площади с точностью `1e-6`. `operator<<` и `operator>>` делегируют работу виртуальным `print()` и `read()`.

## Ввод и вывод

Вводятся числа в порядке полей: `3` для круга, `4 2` для эллипса, `2 1.5708` для сектора. Вывод содержит имя фигуры, поля и площадь.

Пример вывода:

```text
Circle: r=3 metric=28.2743
Ellipse: a=4 b=2 metric=25.1327
Sector: r=2 angle=1.5708 metric=3.1416
```

Положительные радиусы и полуоси обязательны. Угол сектора в радианах, от `0` до `2π`. Все фигуры расположены в начале координат. Угол сектора отсчитывается против часовой стрелки от положительной оси X. Граница считается принадлежащей фигуре.

## Коллекция и владение

`ShapeCollection` хранит динамический массив `Shape**` и владеет копиями фигур. Добавление создаёт копию через `clone()`, а удаление освобождает память. `size()` и `at()` позволяют обходить коллекцию, `totalMetric()` считает сумму площадей. Реализовано правило пяти, копирование глубокое, перемещение передаёт владение памятью.

## Сборка и тестирование

В корневом `CMakeLists.txt` нужно добавить `add_subdirectory(lab4)`. Программа и тесты собираются раздельно. Есть 10 Google Test.

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target lab4_main lab4_tests
./cmake-build-debug/lab4/lab4_main
./cmake-build-debug/lab4/lab4_tests
```

Проверка памяти с санитайзером:

```bash
cmake -S . -B cmake-build-asan -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -g" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build cmake-build-asan --target lab4_tests
./cmake-build-asan/lab4/lab4_tests
```
