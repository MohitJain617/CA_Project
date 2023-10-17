all: storeload loadstore loadload storestore

storeload:
	g++ -o storeload store_load.cpp -lpthread -std=c++11

loadstore:
	g++ -o loadstore load_store.cpp -lpthread -std=c++11

loadload:
	g++ -o loadload load_load.cpp -lpthread -std=c++11

storestore:
	g++ -o storestore store_store.cpp -lpthread -std=c++11

clean:
	rm -f storeload loadstore loadload storestore