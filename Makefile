CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = lab1_school
OBJS = main.o SchoolClass.o SchoolDatabase.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp SchoolClass.h SchoolDatabase.h
	$(CXX) $(CXXFLAGS) -c main.cpp

SchoolClass.o: SchoolClass.cpp SchoolClass.h
	$(CXX) $(CXXFLAGS) -c SchoolClass.cpp

SchoolDatabase.o: SchoolDatabase.cpp SchoolDatabase.h SchoolClass.h
	$(CXX) $(CXXFLAGS) -c SchoolDatabase.cpp

clean:
	rm -f $(TARGET) $(OBJS)
