#ifndef SCHOOLDATABASE_H
#define SCHOOLDATABASE_H
#include "SchoolClass.h"

namespace School {
    const int kMaxClasses = 5;

    class SchoolDatabase {
    public:
        SchoolDatabase();
        ~SchoolDatabase();

        SchoolClass& addClass(const SchoolClass& c);
        void displayAll() const;
        void displayOvercrowded() const;
        void displayGraduating() const;
        void displayPrimary() const;

    private:
        SchoolClass mClasses[kMaxClasses];
        int mNextSlot;
    };
}
#endif // SCHOOLDATABASE_H
