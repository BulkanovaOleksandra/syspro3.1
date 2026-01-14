CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
AR = ar
ARFLAGS = rcs

TARGET = lr2_static
LIBNAME = libteacher.a

SRC = src/Teacher.cpp src/TeacherDatabase.cpp
OBJ = $(SRC:.cpp=.o)

all: $(LIBNAME) $(TARGET)

$(LIBNAME): $(OBJ)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ)

$(TARGET): main.o $(LIBNAME)
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o -L. -lteacher

main.o: main.cpp include/Teacher.h include/TeacherDatabase.h
	$(CXX) $(CXXFLAGS) -c main.cpp

src/Teacher.o: src/Teacher.cpp include/Teacher.h
	$(CXX) $(CXXFLAGS) -c src/Teacher.cpp -o src/Teacher.o

src/TeacherDatabase.o: src/TeacherDatabase.cpp include/TeacherDatabase.h include/Teacher.h
	$(CXX) $(CXXFLAGS) -c src/TeacherDatabase.cpp -o src/TeacherDatabase.o

clean:
	rm -f $(TARGET) $(LIBNAME) main.o $(OBJ)
