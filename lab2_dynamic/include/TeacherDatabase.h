#ifndef TEACHERDATABASE_H
#define TEACHERDATABASE_H
#include "Teacher.h"
#include <vector>
#include <optional>

namespace School {
    class TeacherDatabase {
    public:
        TeacherDatabase();
        ~TeacherDatabase();

        // Додавання/пошук
        void addTeacher(const Teacher& t);
        std::optional<Teacher*> findByCode(int code);       // для інтеграції з SchoolClass::teacherCode
        std::optional<const Teacher*> findByCode(int code) const;

        // Операції за завданням
        bool fireByCode(int code);                           // звільнити (залишається у системі)
        bool increaseSalaryByCode(int code, double amount);  // збільшити
        bool decreaseSalaryByCode(int code, double amount);  // зменшити

        // Вивід
        void displayAll() const;
        void displayActive() const;
        void displayFired() const;

    private:
        std::vector<Teacher> mTeachers;
    };
}
#endif // TEACHERDATABASE_H
