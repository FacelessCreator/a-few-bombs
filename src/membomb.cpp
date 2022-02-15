#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define TIME_BETWEEN_ALLOCATIONS 50

int main() {
    size_t pagesize = getpagesize();

    while(1) {
        std::this_thread::sleep_for(std::chrono::microseconds(TIME_BETWEEN_ALLOCATIONS));
        void * memblock = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
        if (memblock)
            memset(memblock, 0, pagesize);
    }
}
