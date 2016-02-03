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


int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  struct sockaddr_in {
    sa_family_t
    sin_family ; /* address family : AF_INET */
    in_port_t sin_port ; /* port in network byte order */
    struct in_addr sin_addr ;
    /* internet address */
  };
  /* Internet address . */
  struct in_addr {
    uint32_t
    s_addr ;
  };

  
}
