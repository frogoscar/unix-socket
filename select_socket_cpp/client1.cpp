#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in server;
  string message;
  char server_reply[64];

  // Create socket : TCP
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("Cound'n create socket\n");
    return 1;
  }
  printf("Client socket created\n");

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(1314);

  // Connect to remote server
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    cout << "Connection to server error" << endl;
    return 1;
  }

  cout << "Connected to server" << endl;

  // Keep communicating with server
  while (1) {
    cout << "Enter your message : ";
    getline(cin, message);

    // Send some data
    if (send(sock, message.c_str(), message.length(), 0) < 0) {
      cout << "Function send() error" << endl;
      return 1;
    }

    // Receive a reply from the server
    bzero(server_reply, 64);
    if (recv(sock, server_reply, sizeof(server_reply), 0) < 0) {
      cout << "Function recv() failed" << endl;
      break;
    }

    cout << "Server replied : ";
    cout << server_reply << endl;
  }

  close(sock);
  return 0;
}
