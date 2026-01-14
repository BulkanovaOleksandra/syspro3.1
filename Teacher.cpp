#include "Teacher.h"
#include <iomanip>
#include <stdexcept>

namespace School {
    Teacher::Teacher()
        : teacherCode(0), name(""), salary(0.0), isActive(true), hireYear(0) {}

    Teacher::Teacher(int code, const std::string& name, double salary, int hireYear)
        : teacherCode(code), name(name), salary(salary), isActive(true), hireYear(hireYear) {
        if (salary < 0.0) throw std::invalid_argument("Salary cannot be negative");
    }

    void Teacher::increaseSalary(double amount) {
        if (amount < 0.0) throw std::invalid_argument("Increase amount cannot be negative");
        salary += amount;
    }

    void Teacher::decreaseSalary(double amount) {
        if (amount < 0.0) throw std::invalid_argument("Decrease amount cannot be negative");
        salary -= amount;
        if (salary < 0.0) salary = 0.0; // базова безпека
    }

    void Teacher::fire() { isActive = false; }

    void Teacher::rehire(double newSalary) {
        if (newSalary < 0.0) throw std::invalid_argument("Salary cannot be negative");
        isActive = true;
        salary = newSalary;
    }

    int Teacher::getCode() const { return teacherCode; }
    const std::string& Teacher::getName() const { return name; }
    double Teacher::getSalary() const { return salary; }
    bool Teacher::isInStaff() const { return isActive; }
    int Teacher::getHireYear() const { return hireYear; }

    void Teacher::printInfo() const {
        std::cout << "Вчитель #" << teacherCode << " | " << name
                  << " | Зарплата: " << std::fixed << std::setprecision(2) << salary
                  << " | Статус: " << (isActive ? "працює" : "звільнений")
                  << " | Рік прийому: " << hireYear << "\n";
    }
}
