#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "socket.h"

int main(void)
{
  int socket_serveur;
    initialiser_signaux();
   socket_serveur = creer_serveur(9876);
  
    if(socket_serveur == -1) {
      perror("créer_serveur");
      exit(1);
    }
     int socket_client;
    while(1) {
     
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
      const char * message_bienvenue = "Bonjour,bienvenue sur mon serveur Pawnee !\n";
      sleep(1);
      write(socket_client,message_bienvenue,strlen(message_bienvenue)+1);
      /* char message_client[50];
      memset(message_client, 0, sizeof(message_client));
      while(read(socket_client,&message_client,50)>0){
	write(socket_client,&message_client,50);
        memset(message_client, 0, sizeof(message_client));
	}*/

      FILE *file = fdopen(socket_client,"w+");
      char buff[1024];
      memset(buff,0,sizeof(buff));
      
      while(1){
	fgets(buff,1024,file);
	printf("<Pawnee> %s",buff);
	memset(buff,0,sizeof(buff));
      }
      
      } else {
	close(socket_client);
      }
      
      
    }

    close(socket_serveur);
    
    return 0;
}

void traitement_signal(int sig){
  printf("Signal %d reçu\n", sig);
  int status = 0;
  while(waitpid(-1,&status,WNOHANG)!=-1){
  }
}

void initialiser_signaux(void)
{

  if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
    perror("initialiser signaux");

  struct sigaction sa;

  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction(SIGCHLD)");
  }
}
