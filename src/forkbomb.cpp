#include <chrono>
#include <thread>
#include <unistd.h>

#define TIME_BETWEEN_FORKS 1000

int main() {
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_BETWEEN_FORKS));
        fork();
    }
}
