CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude -fPIC
LDFLAGS = -shared
TARGET = lr2_shared
LIBNAME = libteacher.so

SRC = src/Teacher.cpp src/TeacherDatabase.cpp
OBJ = $(SRC:.cpp=.o)

all: $(LIBNAME) $(TARGET)

$(LIBNAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(LIBNAME) $(OBJ)

$(TARGET): main.o $(LIBNAME)
	$(CXX) -std=c++17 -o $(TARGET) main.o -L. -lteacher

main.o: main.cpp include/Teacher.h include/TeacherDatabase.h
	$(CXX) $(CXXFLAGS) -c main.cpp

src/Teacher.o: src/Teacher.cpp include/Teacher.h
	$(CXX) $(CXXFLAGS) -c src/Teacher.cpp -o src/Teacher.o

src/TeacherDatabase.o: src/TeacherDatabase.cpp include/TeacherDatabase.h include/Teacher.h
	$(CXX) $(CXXFLAGS) -c src/TeacherDatabase.cpp -o src/TeacherDatabase.o

clean:
	rm -f $(TARGET) $(LIBNAME) main.o $(OBJ)
