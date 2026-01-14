#include <iostream>
#include "include/Teacher.h"
#include "include/TeacherDatabase.h"

using namespace School;

void printMenu() {
    std::cout << "\n=== МЕНЮ ===\n";
    std::cout << "1. Додати вчителя\n";
    std::cout << "2. Звільнити вчителя\n";
    std::cout << "3. Збільшити зарплату\n";
    std::cout << "4. Зменшити зарплату\n";
    std::cout << "5. Показати всіх\n";
    std::cout << "6. Показати активних\n";
    std::cout << "7. Показати звільнених\n";
    std::cout << "0. Вихід\n";
    std::cout << "Ваш вибір: ";
}

int main() {
    TeacherDatabase db;
    int choice;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int code, year;
                std::string name;
                double salary;
                std::cout << "Введіть код: ";
                std::cin >> code;
                std::cout << "Введіть ім'я: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Введіть зарплату: ";
                std::cin >> salary;
                std::cout << "Введіть рік прийому: ";
                std::cin >> year;
                db.addTeacher(Teacher(code, name, salary, year));
                break;
            }
            case 2: {
                int code;
                std::cout << "Код вчителя: ";
                std::cin >> code;
                if (!db.fireByCode(code)) std::cout << "Не знайдено!\n";
                break;
            }
            case 3: {
                int code; double amount;
                std::cout << "Код вчителя: ";
                std::cin >> code;
                std::cout << "На скільки збільшити: ";
                std::cin >> amount;
                if (!db.increaseSalaryByCode(code, amount)) std::cout << "Не знайдено!\n";
                break;
            }
            case 4: {
                int code; double amount;
                std::cout << "Код вчителя: ";
                std::cin >> code;
                std::cout << "На скільки зменшити: ";
                std::cin >> amount;
                if (!db.decreaseSalaryByCode(code, amount)) std::cout << "Не знайдено!\n";
                break;
            }
            case 5: db.displayAll(); break;
            case 6: db.displayActive(); break;
            case 7: db.displayFired(); break;
            case 0: std::cout << "Вихід...\n"; break;
            default: std::cout << "Невірний вибір!\n"; break;
        }
    } while (choice != 0);

    return 0;
}
