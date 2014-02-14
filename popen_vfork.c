#include <stdio.h>
#include <stdlib.h>

FILE * popen(const char* program, const char* type)
{
    FILE *iop;
    int pdes[2], fds, pid;

    if (*type != 'r' && *type != 'w' || type[1])
        return (NULL);

    if (pipe(pdes) < 0)
        return (NULL);
    switch (pid = vfork()) {
    case -1:            /* error */
        (void) close(pdes[0]);
        (void) close(pdes[1]);
        return (NULL);
        /* NOTREACHED */
    case 0:             /* child */
        if (*type == 'r') {
            if (pdes[1] != fileno(stdout)) {
                (void) dup2(pdes[1], fileno(stdout));
                (void) close(pdes[1]);
            }
            (void) close(pdes[0]);
        } else {
            if (pdes[0] != fileno(stdin)) {
                (void) dup2(pdes[0], fileno(stdin));
                (void) close(pdes[0]);
            }
            (void) close(pdes[1]);
        }
        execl("/bin/sh", "sh", "-c", program, NULL);
        _exit(127);
        /* NOTREACHED */
    }
    /* parent; assume fdopen can't fail...  */
    if (*type == 'r') {
        iop = fdopen(pdes[0], type);
        (void) close(pdes[1]);
    } else {
        iop = fdopen(pdes[1], type);
        (void) close(pdes[0]);
    }
    return (iop);
}
