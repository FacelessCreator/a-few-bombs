#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <iostream>

#define TIME_BETWEEN_ALLOCATIONS 50

int main() {
    size_t pagesize = getpagesize();

    bool memory_allocation_fails = false;

    while(1) {
        std::this_thread::sleep_for(std::chrono::microseconds(TIME_BETWEEN_ALLOCATIONS));
        void * memblock = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
        if (memblock != MAP_FAILED) {
            memset(memblock, 0, pagesize);
        } else if (!memory_allocation_fails) {
            memory_allocation_fails = true;
            std::cout << "Memory allocation failed first time" << std::endl;
        }
    }
}
