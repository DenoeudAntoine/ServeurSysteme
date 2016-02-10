#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"

int main(void)
{
  int socket_serveur;
    initialiser_signaux();
   socket_serveur = creer_serveur(8080);
  
    if(socket_serveur == -1) {
      perror("créer_serveur");
      exit(1);
    }

    while(1) {
      int socket_client;
      int pid;
      socket_client = accept(socket_serveur,NULL,NULL);
     
      if(socket_client == -1)
	{
	  perror ("accept");
	  /* traitement d ’ erreur */
	  return 1;
	}
      pid = fork();
      if(pid == 0) {
      /* On peut maintenant dialoguer avec le client */
      const char * message_bienvenue = "Bonjour,bienvenue sur mon serveur\n c'est cool \n toto \n plus d'idées \n bon \n c'est \n bientot \n fini \n ! \n ou pas \n ah si.\n";
      sleep(1);
      write(socket_client,message_bienvenue,strlen(message_bienvenue)+1);
      char message_client[50];
      memset(message_client, 0, sizeof(message_client));
      while(read(socket_client,&message_client,50)>0){
	write(socket_client,&message_client,50);
        memset(message_client, 0, sizeof(message_client));
      }
      } else {
	close(socket_client);
      }
      
      
    }

    close(socket_serveur);
    
    return 0;
}
