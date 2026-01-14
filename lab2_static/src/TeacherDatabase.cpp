#include "TeacherDatabase.h"
#include <iostream>

namespace School {
    TeacherDatabase::TeacherDatabase() = default;
    TeacherDatabase::~TeacherDatabase() = default;

    void TeacherDatabase::addTeacher(const Teacher& t) {
        // Якщо код вже існує — оновлюємо запис (просте правило у межах ЛР)
        for (auto& existing : mTeachers) {
            if (existing.getCode() == t.getCode()) {
                existing = t;
                return;
            }
        }
        mTeachers.push_back(t);
    }

    std::optional<Teacher*> TeacherDatabase::findByCode(int code) {
        for (auto& t : mTeachers) {
            if (t.getCode() == code) return &t;
        }
        return std::nullopt;
    }

    std::optional<const Teacher*> TeacherDatabase::findByCode(int code) const {
        for (auto const& t : mTeachers) {
            if (t.getCode() == code) return &t;
        }
        return std::nullopt;
    }

    bool TeacherDatabase::fireByCode(int code) {
        auto t = findByCode(code);
        if (!t) return false;
        (t.value())->fire();
        return true;
    }

    bool TeacherDatabase::increaseSalaryByCode(int code, double amount) {
        auto t = findByCode(code);
        if (!t) return false;
        (t.value())->increaseSalary(amount);
        return true;
    }

    bool TeacherDatabase::decreaseSalaryByCode(int code, double amount) {
        auto t = findByCode(code);
        if (!t) return false;
        (t.value())->decreaseSalary(amount);
        return true;
    }

    void TeacherDatabase::displayAll() const {
        std::cout << "=== УСІ ВЧИТЕЛІ ===\n";
        for (auto const& t : mTeachers) t.printInfo();
    }

    void TeacherDatabase::displayActive() const {
        std::cout << "=== ВЧИТЕЛІ У ШТАТІ ===\n";
        for (auto const& t : mTeachers) if (t.isInStaff()) t.printInfo();
    }

    void TeacherDatabase::displayFired() const {
        std::cout << "=== ЗВІЛЬНЕНІ ВЧИТЕЛІ ===\n";
        for (auto const& t : mTeachers) if (!t.isInStaff()) t.printInfo();
    }
}
