#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
  size_t const port = 8080;

  /* init socket */
  int32_t server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("init socket failed");
    exit(EXIT_FAILURE);
  }

  int32_t opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
  size_t addrlen = sizeof(address);
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, SOMAXCONN) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int32_t new_socket;
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  size_t const buflen = 1024;
  char buffer[buflen];
  recv(new_socket, buffer, buflen, 0);
  puts(buffer);

  char hello[] = "Hello from server";
  send(new_socket, hello, sizeof hello, 0);
  puts("Hello message sent");

  close(new_socket);
  shutdown(server_fd, SHUT_RDWR);

  return EXIT_SUCCESS;
}
