#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

int creer_serveur(int port) {
  int socket_serveur ;
  socket_serveur = socket(AF_INET,SOCK_STREAM,0);
  if ( socket_serveur == -1)
    {
      perror ("socket_serveur");
      exit(1);
    }
  int optval = 1;
  if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int)) == -1 )
    perror("Can not set SO_REUSEADDR option");
  struct sockaddr_in saddr;

  saddr.sin_family = AF_INET ; /* Socket ipv4 */
  saddr.sin_port = htons (port); /* Port d � �coute */
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); /* �coute sur toutes les interfaces */
  
  if (bind (socket_serveur,(struct sockaddr *) &saddr,sizeof(saddr)) == -1)
    {
      perror (" bind socker_serveur ");
      /* traitement de l � erreur */
    }

  if (listen(socket_serveur,10) == -1)
    {
      perror ( " listen socket_serveur " );
      /* traitement d � erreur */
    }
  return socket_serveur;

}




