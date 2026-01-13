#ifndef SCHOOLCLASS_H
#define SCHOOLCLASS_H
#include <string>
#include <iostream>

namespace School {
    class SchoolClass {
    private:
        int classCode;
        int teacherCode;
        int typeCode;
        int studentCount;
        char letter;
        int studyYear;
        int creationYear;

    public:
        SchoolClass();
        SchoolClass(int classCode, int teacherCode, int typeCode,
                    int studentCount, char letter, int studyYear, int creationYear);

        int getClassCode() const;
        int getStudentCount() const;
        int getStudyYear() const;

        void setStudentCount(int newCount);
        void setTeacherCode(int newTeacher);

        bool isOvercrowded() const;     // >30 учнів
        bool isGraduatingYear() const;  // 11-й рік
        bool isPrimary() const;         // 1–4 рік

        void printInfo() const;
    };
}
#endif // SCHOOLCLASS_H
