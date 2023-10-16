#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x(0);
std::atomic<int> y(0);
int r1 = 0;
int r2 = 0;
// std::atomic<int> r1(0);
// std::atomic<int> r2(0);

//-------------------------------------
//  MersenneTwister
//  A thread-safe random number generator with good randomness
//  in a small number of instructions. We'll use it to introduce
//  random timing delays.
//-------------------------------------
#define MT_IA  397
#define MT_LEN 624

class MersenneTwister
{
    unsigned int m_buffer[MT_LEN];
    int m_index;

public:
    MersenneTwister(unsigned int seed);
    // Declare noinline so that the function call acts as a compiler barrier:
    unsigned int integer() __attribute__((noinline));
};

MersenneTwister::MersenneTwister(unsigned int seed)
{
    // Initialize by filling with the seed, then iterating
    // the algorithm a bunch of times to shuffle things up.
    for (int i = 0; i < MT_LEN; i++)
        m_buffer[i] = seed;
    m_index = 0;
    for (int i = 0; i < MT_LEN * 100; i++)
        integer();
}

unsigned int MersenneTwister::integer()
{
    // Indices
    int i = m_index;
    int i2 = m_index + 1; if (i2 >= MT_LEN) i2 = 0; // wrap-around
    int j = m_index + MT_IA; if (j >= MT_LEN) j -= MT_LEN; // wrap-around

    // Twist
    unsigned int s = (m_buffer[i] & 0x80000000) | (m_buffer[i2] & 0x7fffffff);
    unsigned int r = m_buffer[j] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
    m_buffer[m_index] = r;
    m_index = i2;

    // Swizzle
    r ^= (r >> 11);
    r ^= (r << 7) & 0x9d2c5680UL;
    r ^= (r << 15) & 0xefc60000UL;
    r ^= (r >> 18);
    return r;
}



void thread1() {
    MersenneTwister random(1);
    while (random.integer() % 8 != 0) {}  // Random delay
    x.store(1, std::memory_order_relaxed);
	// r1.store(y.load(std::memory_order_relaxed), std::memory_order_relaxed);
    // if (flag2.load(std::memory_order_relaxed)) {
    //     std::cout << "Reordering occurred: x=1 and y=" << y.load(std::memory_order_relaxed) << std::endl;
    // }
}

void thread2() {
    MersenneTwister random(2);
    while (random.integer() % 8 != 0) {}  // Random delay
    // y.store(1, std::memory_order_relaxed);
	r1 = x.load(std::memory_order_relaxed);
	r2 = x.load(std::memory_order_relaxed);
    // if (flag1.load(std::memory_order_relaxed)) {
    //     std::cout << "Reordering occurred: y=1 and x=" << x.load(std::memory_order_relaxed) << std::endl;
    // }
}

int main() {
	for(long long itr = 0; ; itr++){
		std::thread t1(thread1);
		std::thread t2(thread2);
		t1.join();
		t2.join();
		int a1 = r1;
		int a2 = r2;
		if(a1 == 1 && a2 == 0){
			std::cout << "Reordering occurred: x=0 and y=0 at "<< itr << std::endl;
			break;
		}
		int wait = 10;
		while(wait--){}
		x.store(0, std::memory_order_relaxed);
		y.store(0, std::memory_order_relaxed);
		r1 = 0;
		r2 = 0;
		wait = 10;
		while(wait--){}
	}
    return 0;
}