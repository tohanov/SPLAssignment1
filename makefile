all: clean compile link check


clean:
	echo "Cleaning..."
	rm -f bin/*

# -Weffc++
compile: src/main.cpp src/Action.cpp src/Customer.cpp src/Studio.cpp src/Trainer.cpp src/Workout.cpp
	echo "Compiling..."
	g++ -std=c++11 -g -Wall -Iinclude -c -o bin/main.o src/main.cpp -O3
	g++ -std=c++11 -g -Wall -Iinclude -c -o bin/Action.o src/Action.cpp -O3
	g++ -std=c++11 -g -Wall -Iinclude -c -o bin/Customer.o src/Customer.cpp -O3
	g++ -std=c++11 -g -Wall -Iinclude -c -o bin/Studio.o src/Studio.cpp -O3
	g++ -std=c++11 -g -Wall -Iinclude -c -o bin/Trainer.o src/Trainer.cpp -O3
	g++ -std=c++11 -g -Wall -Iinclude -c -o bin/Workout.o src/Workout.cpp -O3


link: bin/main.o bin/Action.o bin/Customer.o bin/Studio.o bin/Trainer.o bin/Workout.o
	echo "Linking..."
	g++ -std=c++11 -o bin/studio bin/main.o bin/Action.o bin/Customer.o bin/Studio.o bin/Trainer.o bin/Workout.o -O3


check: bin/studio
	echo "Running with valgrind..."
	valgrind --leak-check=full --show-reachable=yes bin/studio ExampleInput.txt

checkV:
	echo "Running with valgrind with -v flag..."
	valgrind -v --leak-check=full --show-reachable=yes bin/studio ExampleInput.txt

#suppressing printing of the commands that are running
ifndef VERBOSE
.SILENT:
endif
