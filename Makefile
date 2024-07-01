# ID: 3224653689
# MAIL: adam.sinale@gmail.com

CC=g++
FLAGS=-std=c++14 -Werror -Wsign-conversion

CPPs = tree.cpp node.cpp
OBJECTS=$(subst .cpp,.o,$(CPPs))

run: demo
	./$^

demo: Demo.o $(filter-out Test.o, $(OBJECTS))
	$(CC) $(FLAGS) $^ -o demo

%.o: %.cpp
	$(CC) $(FLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test
