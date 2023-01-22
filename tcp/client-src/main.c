#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  int32_t const port = 8080;

  int32_t sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    perror("invalid address. address not supported");
    exit(EXIT_FAILURE);
  }

  int32_t client_fd;
  if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
                           sizeof(serv_addr))) < 0) {
    perror("connection failed");
    exit(EXIT_FAILURE);
  }

  char hello[] = "Hello from client";
  send(sock, hello, sizeof hello, 0);
  puts("Hello message sent");

  size_t const buflen = 1024;
  char buffer[buflen];
  recv(sock, buffer, buflen, 0);
  puts(buffer);

  close(client_fd);

  return EXIT_SUCCESS;
}
