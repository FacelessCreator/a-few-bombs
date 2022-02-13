#include <iostream>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <string.h>

using namespace std;

#define LOG_FOLDER_NAME "log"

void printLogo(const char * logo) {
    cout << "--------------------------" << endl;
    cout << "       " << logo << endl;
    cout << "use ctrl+C to stop process" << endl;
    cout << "--------------------------" << endl;
}

pid_t execBomb(const char * name) {
    pid_t pid = fork();
    if (pid == -1) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (pid > 0) {
        // parent
        cout << "Bomb has been planted" << endl;
        return pid;
    } else {
        // child
        int result = execve(name, {}, {});
        if (result == -1) {
            cerr << "Bomb execution failed" << endl;
            exit(1);
        }
    }
    return -1;
}

ofstream openLog(const char * log_name) {
    system("mkdir -p " LOG_FOLDER_NAME);
    string filepath = LOG_FOLDER_NAME "/" + string(log_name);
    cout << "Log will be in " << filepath << endl;
    return ofstream(filepath);
}

std::string getCurrentTimeString() {
    time_t current_time = time(0);
    tm *gmtm = gmtime(&current_time);
    return to_string(gmtm->tm_hour) + ":" + to_string(gmtm->tm_min) + ":" + to_string(gmtm->tm_sec);
}

void waitMilliseconds(int64_t millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void getMemory(int pid, int* currRealMem, int* peakRealMem, int* currVirtMem, int* peakVirtMem) {

    // stores each word in status file
    char buffer[1024] = "";

    // linux file contains this-process info
    string filepath = "/proc/"+to_string(pid)+"/status";
    FILE* file = fopen(filepath.data(), "r");

    // read the entire file
    while (fscanf(file, " %1023s", buffer) == 1) {

        if (strcmp(buffer, "VmRSS:") == 0) {
            fscanf(file, " %d", currRealMem);
        }
        if (strcmp(buffer, "VmHWM:") == 0) {
            fscanf(file, " %d", peakRealMem);
        }
        if (strcmp(buffer, "VmSize:") == 0) {
            fscanf(file, " %d", currVirtMem);
        }
        if (strcmp(buffer, "VmPeak:") == 0) {
            fscanf(file, " %d", peakVirtMem);
        }
    }
    fclose(file);
}

unsigned long getProcRAM(pid_t proc_pid) {
    int currRealMem;
    int peakRealMem;
    int currVirtMem;
    int peakVirtMem;
    getMemory(proc_pid, &currRealMem, &peakRealMem, &currVirtMem, &peakVirtMem);
    return currVirtMem * 1024;
}

unsigned long bytesCountToMibibytesCount(unsigned long bytesCount) {
    return bytesCount / (1 << 20);
}
