#include "../basics.hpp"


#ifdef _WIN32
    int procs =  = static_cast<int>(std::thread::hardware_concurrency());
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    int procs = (nprocs > 0)? static_cast<int>(nprocs) : 1;
#endif



void wipe() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}