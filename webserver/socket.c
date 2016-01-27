#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol){
  int socket_serveur ;
  socket_serveur = socket(AF_INET,SOCK_STREAM,0);
  if (socket_serveur == -1)
    {
      perror ( " socket_serveur " );
      /* traitement de l ’ erreur */
    }
  /* Utilisation de la socket serveur */
}
