#ifndef TEACHER_H
#define TEACHER_H
#include <string>
#include <iostream>

namespace School {
    class Teacher {
    private:
        int teacherCode;        // унікальний код (сумісний з SchoolClass::teacherCode)
        std::string name;       // ПІБ
        double salary;          // поточна зарплата
        bool isActive;          // у штаті (true) / звільнений (false)
        int hireYear;           // рік прийому

    public:
        Teacher();
        Teacher(int code, const std::string& name, double salary, int hireYear);

        // Модифікації статусу та зарплати
        void increaseSalary(double amount);
        void decreaseSalary(double amount);
        void fire();            // звільнити (залишається в системі)
        void rehire(double newSalary); // повернути у штат

        // Гетери
        int getCode() const;
        const std::string& getName() const;
        double getSalary() const;
        bool isInStaff() const;
        int getHireYear() const;

        // Вивід
        void printInfo() const;
    };
}
#endif // TEACHER_H
