#include "etc.hpp"

#include <sys/sysinfo.h>

#define LOGO "MEMBOMB TEST"

#define LOG_NAME "membomb_log.csv"

#define BOMB_FILEPATH "build/membomb"

#define TIME_BETWEEN_LOGGING 500
#define COUT_EVERY_N_LOGS 4

using namespace std;

int main() {
    printLogo(LOGO);
    ofstream logfile = openLog(LOG_NAME);
    
    struct sysinfo system_info;
    sysinfo(&system_info);
    cout << "Total RAM: " << bytesCountToMibibytesCount(system_info.totalram) << " MiB" << endl;
    cout << "High RAM: " << bytesCountToMibibytesCount(system_info.totalhigh) << " MiB" << endl;
    cout << "SWAP RAM: " << bytesCountToMibibytesCount(system_info.totalswap) << " MiB" << endl;
    
    logfile << "\"i\",\"time\",\"free_ram_MiB\",\"membomb_ram_MiB\"" << endl;
    pid_t bomb_pid = execBomb(BOMB_FILEPATH);

    int64_t i = 0;

    while(1) {
        waitMilliseconds(TIME_BETWEEN_LOGGING);
        
        sysinfo(&system_info);

        ++i;
        string str_time = getCurrentTimeString();
        unsigned long free_ram = bytesCountToMibibytesCount(system_info.freeram);
        unsigned long membomb_ram = bytesCountToMibibytesCount(getProcRAM(bomb_pid));

        logfile << i << "," << str_time << "," << free_ram << "," << membomb_ram << endl;
        logfile.flush();

        if (i % COUT_EVERY_N_LOGS == 0) {
            cout << "[" << str_time << "] free_ram=" << free_ram << " MiB membomb_ram=" << membomb_ram << " MiB" << endl;
        }
    }
}
