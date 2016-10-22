#ifndef FGMESSAGE_INCLUDE
#define FGMESSAGE_INCLUDE
#include <stdbool.h>

extern void send_fgmessage(bool app_flag);
extern void fgmessage_subscribe();
extern void fgmessage_unsubscribe();

#endif

