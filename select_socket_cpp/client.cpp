#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sock;
  const int BUF_SIZE = 64;
  struct sockaddr_in server;
  char message[BUF_SIZE], server_reply[BUF_SIZE];

  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("cound not create socket\n");
  }
  printf("Socket created\n");

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(1314);

  // Connect to remote server
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("connection error\n");
    return 1;
  }

  puts("Connected\n");

  // keep communicating with server
  while (1) {
    printf("write your message : ");
    if (fgets(message, BUF_SIZE, stdin) != NULL) {
      // Send some data
      if (send(sock, message, strlen(message), 0) < 0) {
        printf("send error\n");
        return 1;
      }
    }

    // Receive a reply from the server
    memset(server_reply, '\0', sizeof(server_reply));
    if (recv(sock, server_reply, BUF_SIZE, 0) < 0) {
      printf("recv failed\n");
      break;
    }

    printf("Server reply : %s", server_reply);
  }

  close(sock);
  return 0;
}
