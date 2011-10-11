#ifndef __MAIN__H_
#ifdef _WIN32
    #include "radop.h"
#else
    #include "src\radop.h"
#endif

/* print the authors group member */
void prnmember(void);

/* get radix number from user */
enum radix_t getusrrad(void);

/* get filtered user string from console */
void readkeyb(char **result, size_t minlen, size_t maxlen, int echo, const char* charset);

#endif
