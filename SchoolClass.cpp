#include "SchoolClass.h"

namespace School {
    SchoolClass::SchoolClass()
        : classCode(0), teacherCode(0), typeCode(0),
          studentCount(0), letter('A'), studyYear(0), creationYear(0) {}

    SchoolClass::SchoolClass(int classCode, int teacherCode, int typeCode,
                             int studentCount, char letter, int studyYear, int creationYear)
        : classCode(classCode), teacherCode(teacherCode), typeCode(typeCode),
          studentCount(studentCount), letter(letter), studyYear(studyYear), creationYear(creationYear) {}

    int SchoolClass::getClassCode() const { return classCode; }
    int SchoolClass::getStudentCount() const { return studentCount; }
    int SchoolClass::getStudyYear() const { return studyYear; }

    void SchoolClass::setStudentCount(int newCount) { studentCount = newCount; }
    void SchoolClass::setTeacherCode(int newTeacher) { teacherCode = newTeacher; }

    bool SchoolClass::isOvercrowded() const { return studentCount > 30; }
    bool SchoolClass::isGraduatingYear() const { return studyYear == 11; }
    bool SchoolClass::isPrimary() const { return studyYear >= 1 && studyYear <= 4; }

    void SchoolClass::printInfo() const {
        std::cout << "Клас #" << classCode << " (" << studyYear << letter << ")\n";
        std::cout << "Класний керівник (код): " << teacherCode << "\n";
        std::cout << "Тип (код): " << typeCode << "\n";
        std::cout << "Учнів: " << studentCount << "\n";
        std::cout << "Рік створення: " << creationYear << "\n";
        std::cout << "Стан: "
                  << (isOvercrowded() ? "переповнений" : "норма") << ", "
                  << (isGraduatingYear() ? "випускний клас" : "невипускний") << ", "
                  << (isPrimary() ? "початкова школа" : "середня/старша школа") << "\n";
        std::cout << "-------------------------------------------\n";
    }
}
