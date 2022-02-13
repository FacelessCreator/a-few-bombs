#include <chrono>
#include <thread>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

#define TIME_BETWEEN_ALLOCATIONS 50

int main() {
    size_t pagesize = getpagesize();

    while(1) {
        std::this_thread::sleep_for(std::chrono::microseconds(TIME_BETWEEN_ALLOCATIONS));
        char * memblock = (char *) malloc(pagesize);
        if (memblock)
            memset(memblock, 0, pagesize);
    }
}
