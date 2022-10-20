#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXIMOMSG 5000

int main(int argc, char *argv[]){
  signal(SIGPIPE, SIG_IGN);
  char buffer[MAXIMOMSG + 1];
  int tamanho, meusocket;
  struct sockaddr_in destinatario;

  char msg[100];

  meusocket = socket(AF_INET, SOCK_STREAM, 0);
  
  destinatario.sin_addr.s_addr = inet_addr("195.144.107.198");

  destinatario.sin_family = AF_INET;

  destinatario.sin_port = htons(21);

  memset(&(destinatario.sin_zero), '\0', sizeof(destinatario.sin_zero));

  connect(meusocket, (struct sockaddr *)&destinatario, sizeof(struct sockaddr));

  //220 banner

  tamanho = recv(meusocket, buffer, MAXIMOMSG, 0);
  printf("%s\n", buffer);

  //USER
  strcpy(msg, "USER demo\r\n");
  send(meusocket, msg, strlen(msg), 0);

  //331 - password required
  tamanho = recv(meusocket, buffer, MAXIMOMSG, 0);
  printf("%s\n", buffer);

  //PASS
  strcpy(msg, "PASS password\r\n");
  send(meusocket, msg, strlen(msg), 0);

  //230 - user logged in
  tamanho = recv(meusocket, buffer, MAXIMOMSG, 0);
  printf("%s\n", buffer);

  //QUIT
  strcpy(msg, "QUIT\r\n");
  send(meusocket, msg, strlen(msg), 0);

  //termina o socket
  close(meusocket);
  
  return 0;
}
