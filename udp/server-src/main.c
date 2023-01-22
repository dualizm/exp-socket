#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  int32_t const port = 8080;

  /* init socket */
  int32_t server_fd;
  if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("init socket failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  socklen_t slen;
  int n;
  struct sockaddr_in cliaddr;

  size_t const buflen = 1024;
  char buffer[buflen];
  n = recvfrom(server_fd, buffer, buflen, MSG_WAITALL,
               (struct sockaddr *)&cliaddr, &slen);

  buffer[n] = '\0';
  printf("Client: %s\n", buffer);

  char hello[] = "Hello from server";
  sendto(server_fd, hello, sizeof hello, MSG_CONFIRM,
         (const struct sockaddr *)&cliaddr, slen);
  puts("hello message send");

  shutdown(server_fd, SHUT_RDWR);
  close(server_fd);

  return EXIT_SUCCESS;
}
