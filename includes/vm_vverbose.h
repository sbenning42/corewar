#ifndef VM_VVERBOSE_H
# define VM_VVERBOSE_H

# define VV_SEP         "****************************************"
# define VV_NSEP        "****************************************\n"
# define VV_SEPLINE     VV_SEP VV_NSEP
# define VV_ENTER_FMT   "%s: Enter %s.\n"
# define VV_QUIT_FMT    "%s: Quit %s.\n"

# include "vm.h"

void                    vv_enter(char *f);
void                    vv_quit(char *f);
void                    vv_msg(char *msg);
void                    vv_dump(void);

#endif
