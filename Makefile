all: trainset

clean: clean-trainset

trainset:
	clang++ -O3 -o trainset trainset.cpp

clean-trainset:
	rm trainset
	rm *.out.txt
