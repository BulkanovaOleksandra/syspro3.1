#include <iostream>
#include "SchoolClass.h"
#include "SchoolDatabase.h"

using namespace School;

int main() {
    std::cout << "Тестування інформаційної системи школи\n\n";

    // Об'єкти на стеку
    SchoolClass c1(1, 101, 1, 28, 'A', 5, 2019);
    SchoolClass c2(2, 102, 2, 32, 'B', 11, 2015);

    std::cout << "Об'єкти на стеку:\n";
    c1.printInfo();
    c2.printInfo();

    // Об'єкти на купі
    SchoolClass* c3 = new SchoolClass(3, 103, 1, 25, 'C', 2, 2021);
    SchoolClass* c4 = new SchoolClass(4, 104, 2, 35, 'D', 11, 2014);

    std::cout << "\nОб'єкти на купі:\n";
    c3->printInfo();
    c4->printInfo();

    // Використання бази
    SchoolDatabase db;
    db.addClass(c1);
    db.addClass(c2);
    db.addClass(*c3);
    db.addClass(*c4);

    std::cout << "\n=== Вивід усіх класів ===\n";
    db.displayAll();

    std::cout << "\n=== Переповнені класи ===\n";
    db.displayOvercrowded();

    std::cout << "\n=== Випускні класи ===\n";
    db.displayGraduating();

    std::cout << "\n=== Початкові класи ===\n";
    db.displayPrimary();

    delete c3;
    delete c4;

    return 0;
}
