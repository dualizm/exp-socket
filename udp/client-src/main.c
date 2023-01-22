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
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  socklen_t slen;
  int n;

  char const hello[] = "Hello from client";
  sendto(sock, hello, sizeof hello, MSG_CONFIRM,
         (const struct sockaddr *)&serv_addr, sizeof(serv_addr));

  size_t const buflen = 1024;
  char buffer[buflen];
  n = recvfrom(sock, buffer, buflen, MSG_WAITALL, (struct sockaddr *)&serv_addr,
               &slen);

  buffer[n] = '\0';
  printf("Server: %s\n", buffer);

  close(sock);

  return EXIT_SUCCESS;
}
