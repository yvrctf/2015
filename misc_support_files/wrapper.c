// socat TCP4-LISTEN:6666,fork,reuseaddr EXEC:"/usr/local/sbin/wrapper32 -d /home/challenge/chroot -u test -x /challenge/clevername32"

#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CTF_DEFAULT_TIMEOUT 20

char *empty[] = { NULL };
extern char *optarg;

void alarm_handler(int signo) {
    killpg(0, SIGKILL);
    exit(EXIT_FAILURE);
}

int drop_privileges(char *username, char *chroot_dir) {
    struct passwd *pw = getpwnam(username);

    if (!chroot_dir) {
        if (chdir("/") == -1)
            exit(EXIT_FAILURE);
    } else {
        if (chdir(chroot_dir) == -1 || chroot(chroot_dir) == -1)
            exit(EXIT_FAILURE);
    }

    if (!pw)
        exit(EXIT_FAILURE);

    if (setgroups(0, NULL) == -1)
        exit(EXIT_FAILURE);

    if (setgid(pw->pw_gid) == -1)
        exit(EXIT_FAILURE);

    if (setuid(pw->pw_uid) == -1)
        exit(EXIT_FAILURE);

    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
        exit(EXIT_FAILURE);

    return 0;
}

int main(int argc, char **argv) {
    char *chroot_dir = NULL, *drop_user = NULL, *program = NULL;
    int timeout = CTF_DEFAULT_TIMEOUT, opt;
    long i, max;
    pid_t pid;

    umask(0);

    if (prctl(PR_SET_DUMPABLE, 0, 0, 0, 0) == -1)
        exit(EXIT_FAILURE);

    while ((opt = getopt(argc, argv, "d:u:t:x:")) != -1) {
        switch (opt) {
            case 'd':
                chroot_dir = optarg;
                break;
            case 'u':
                drop_user = optarg;
                break;
            case 't':
                timeout = atoi(optarg);
                break;
            case 'x':
                program = optarg;
                break;
        }
    }

    setsid();

    if (chdir("/") == -1)
        exit(EXIT_FAILURE);

    pid = fork();
    if (pid > 0) {
        signal(SIGALRM, alarm_handler);
        alarm(timeout);
        waitpid(pid, NULL, 0);
        exit(EXIT_SUCCESS);
    } else if (pid == 0) {
        if (!drop_user || !program)
            exit(EXIT_FAILURE);

        drop_privileges(drop_user, chroot_dir);

        for (i = 3, max = sysconf(_SC_OPEN_MAX); i < max; i++)
            close(i);

        execve(program, empty, empty);
    }

    exit(EXIT_FAILURE);
}
