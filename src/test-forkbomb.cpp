#include "etc.hpp"

#include <dirent.h>

#define LOGO "FORKBOMB TEST"

#define LOG_NAME "forkbomb_log.csv"

#define BOMB_FILEPATH "build/forkbomb"

#define TIME_BETWEEN_LOGGING 250
#define COUT_EVERY_N_LOGS 4

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

int main() {
    printLogo(LOGO);

    ofstream logfile = openLog(LOG_NAME);

    logfile << "\"i\",\"time\",\"proc_count\",\"forkbombs_count\"" << endl;

    execBomb(BOMB_FILEPATH);

    int64_t i = 0;

    while (1)
    {
        waitMilliseconds(TIME_BETWEEN_LOGGING);
        
        ++i;
        string str_time = getCurrentTimeString();
        int proc_count = countSystemProcesses();
        int forkbombs_count = -1; // TODO add forkbomb count

        logfile << i << "," << str_time << "," << proc_count << "," << forkbombs_count << endl;
        logfile.flush();

        if (i % COUT_EVERY_N_LOGS == 0) {
            cout << "[" << str_time << "] proc_count=" << proc_count << " forkbombs_count=" << forkbombs_count << endl;
        }
    }

}
