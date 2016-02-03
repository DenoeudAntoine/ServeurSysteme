#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"

int main(void)
{
  int socket_serveur;
   socket_serveur = creer_serveur(8080);
    if(socket_serveur == -1) {
      perror("cr�er_serveur");
      exit(1);
    }

       while(1) {
	 int socket_client ;

	 socket_client = accept(socket_serveur,NULL,NULL);
	 if(socket_client == -1)
	   {
	     perror ("accept");
       /* traitement d � erreur */
	   }
	 /* On peut maintenant dialoguer avec le client */
	 const char * message_bienvenue = "Bonjour,bienvenue sur mon serveur\n c'est cool \n toto \n plus d'id�es \n bon \n c'est \n bientot \n fini \n ! \n ou pas \n ah si.\n";
	 sleep(1);
	 write(socket_client,message_bienvenue,strlen(message_bienvenue));
	 
   }
       
       
       
       return 0;
}
