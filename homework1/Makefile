vshell: vshell.o
	$(CXX) $^ -lboost_filesystem -lboost_program_options -o $@

vshell.o: vshell.cpp
	$(CXX) -c $^

clean:
	rm *.o vshell
