#include <iostream>
#include <utility>

#include "lab3/student.hpp"
#include "lab3/student_set.hpp"

int main() {
    lab3::Student ivan("Ivan", 1);
    lab3::Student petr("Petr", 2);
    lab3::Student fedor("Fedor", 3);

    lab3::StudentSet group1;
    group1.add(ivan);
    group1 += petr;

    lab3::StudentSet group2;
    group2 += petr;
    group2 += fedor;

    std::cout << "Gr 1: " << group1 << '\n';
    std::cout << "Gr 2: " << group2 << '\n';

    lab3::StudentSet united = group1 | group2;
    lab3::StudentSet common = group1 & group2;
    lab3::StudentSet diff = group1 - group2;

    std::cout << "\nОбъединение: " << united << '\n';
    std::cout << "Пересечение: " << common << '\n';
    std::cout << "Разность: " << diff << '\n';

    std::cout << "\nКол-во студентов в Gr 1: " << group1.size() << '\n';
    std::cout << "Иван в Gr 1? : " << std::boolalpha << group1.contains(ivan) << '\n';

    lab3::StudentSet copied = group1;
    lab3::StudentSet moved = std::move(copied);

    std::cout << "\nГруппа после перемещения: " << moved << '\n';

    moved -= ivan;
    std::cout << "Удалили Ивана: " << moved << '\n';

    return 0;
}