#include<iostream>
#include<thread>
#include<atomic>

int main(){
	while(true) {
		int x(0), y(0);

		std::thread t0([&x, &y]() {
			x=1;
			y=3;
		});
		std::thread t1([&x, &y]() {
			if(y == 3 && x == 0)
			std::cout << "Reordering happened" << std::endl;

		});


		t0.join();
		t1.join();
	}
	return 0;
}