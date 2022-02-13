#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define LOG_FOLDER_NAME "log"
#define LOG_NAME "forkbomb_log.csv"

#define BOMB_FILEPATH "build/forkbomb"

#define TIME_BETWEEN_LOGGING 250
#define COUT_EVERY_N_LOGS 4

using namespace std;

bool isInteger(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

int countSystemProcesses() {
    DIR * dir = opendir("/proc");
    if (dir == NULL) {
        return -1;
    }
    int count = 0;
    dirent * entity = readdir(dir);
    while (entity != NULL)
    {
        if (isInteger(entity->d_name)) {
            ++count;
        }
        entity = readdir(dir);
    }
    return count;
}

void execBomb(const char * name) {
    pid_t pid = fork();
    if (pid == -1) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (pid > 0) {
        // parent
        return;
    } else {
        // child
        int result = execve(name, {}, {});
        if (result == -1) {
            cerr << "Bomb execution failed" << endl;
            exit(1);
        }
    }
}

int main() {
    cout << "--------------------------" << endl;
    cout << "       FORKBOMB TEST" << endl;
    cout << "use ctrl+C to stop process" << endl;
    cout << "--------------------------" << endl;
    cout << "Log will be in " << LOG_FOLDER_NAME "/" LOG_NAME << endl;

    system("mkdir -p " LOG_FOLDER_NAME);
    ofstream logfile(LOG_FOLDER_NAME "/" LOG_NAME);

    logfile << "\"i\",\"time\",\"proc_count\",\"forkbombs_count\"" << endl;

    execBomb(BOMB_FILEPATH);

    int64_t i = 0;

    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_BETWEEN_LOGGING));

        time_t current_time = time(0);
        tm *gmtm = gmtime(&current_time);
        
        ++i;
        string str_time = to_string(gmtm->tm_hour) + ":" + to_string(gmtm->tm_min) + ":" + to_string(gmtm->tm_sec);
        int proc_count = countSystemProcesses();
        int forkbombs_count = -1; // TODO add forkbomb count

        logfile << i << "," << str_time << "," << proc_count << "," << forkbombs_count << endl;
        logfile.flush();

        if (i % COUT_EVERY_N_LOGS == 0) {
            cout << "[" << str_time << "] proc_count=" << proc_count << " forkbombs_count=" << forkbombs_count << endl;
        }
    }

}
