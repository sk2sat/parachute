
default:
	g++ main.cc -o para

run:
	make
	./para

run_dat:
	make
	./para > data.dat


