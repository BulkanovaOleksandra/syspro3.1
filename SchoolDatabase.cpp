#include "SchoolDatabase.h"
#include <iostream>
#include <stdexcept>

namespace School {
    SchoolDatabase::SchoolDatabase() : mNextSlot(0) {}
    SchoolDatabase::~SchoolDatabase() = default;

    SchoolClass& SchoolDatabase::addClass(const SchoolClass& c) {
        if (mNextSlot >= kMaxClasses) {
            std::cerr << "Неможливо додати новий клас: масив заповнений!\n";
            throw std::runtime_error("SchoolDatabase is full");
        }
        mClasses[mNextSlot] = c;
        return mClasses[mNextSlot++];
    }

    void SchoolDatabase::displayAll() const {
        std::cout << "=== УСІ КЛАСИ ШКОЛИ ===\n";
        for (int i = 0; i < mNextSlot; ++i) {
            mClasses[i].printInfo();
        }
    }

    void SchoolDatabase::displayOvercrowded() const {
        std::cout << "=== ПЕРЕПОВНЕНІ КЛАСИ ===\n";
        for (int i = 0; i < mNextSlot; ++i) {
            if (mClasses[i].isOvercrowded()) {
                mClasses[i].printInfo();
            }
        }
    }

    void SchoolDatabase::displayGraduating() const {
        std::cout << "=== ВИПУСКНІ КЛАСИ ===\n";
        for (int i = 0; i < mNextSlot; ++i) {
            if (mClasses[i].isGraduatingYear()) {
                mClasses[i].printInfo();
            }
        }
    }

    void SchoolDatabase::displayPrimary() const {
        std::cout << "=== ПОЧАТКОВІ КЛАСИ ===\n";
        for (int i = 0; i < mNextSlot; ++i) {
            if (mClasses[i].isPrimary()) {
                mClasses[i].printInfo();
            }
        }
    }
}
