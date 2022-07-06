target = http-request
objects = main.o http.o

$(target) : main.o http.o
	g++ $(objects) -lcurl -o $(target)

main.o : 
	g++ -c main.cpp

http.o : 
	g++ -c http.cpp

.PHONY : clean
clean : 
	rm -rf $(objects)

clean-full : 
	rm -rf $(objects) $(target)

