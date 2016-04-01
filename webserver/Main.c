#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "socket.h"

int main(void)
{
  
  const char* msgErreur400 = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
  const char* msg200 = "HTTP/1.1 200 OK\r\nContent-Length: ";
  const char * message_bienvenue = "Bonjour,bienvenue sur mon serveur Pawnee !\n";
  
  char buff[1024];
  int socket_serveur;
  
  
  
 
  socket_serveur = creer_serveur(9876);

 initialiser_signaux();
  
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
     FILE *file = fdopen(socket_client,"w+");
    pid = fork();
    if(pid == 0) {
      /* On peut maintenant dialoguer avec le client */
      
      /* char message_client[50];
	 memset(message_client, 0, sizeof(message_client));
	 while(read(socket_client,&message_client,50)>0){
	 write(socket_client,&message_client,50);
	 memset(message_client, 0, sizeof(message_client));
	 }*/
      
      fgets(buff,1024,file);
      if(verifierEntete(buff) == 1){
	
	fprintf(file, msg200, strlen(msg200));
	fprintf(file, "%zu\r\n\r\n", strlen(message_bienvenue));
        fprintf(file, message_bienvenue, strlen(message_bienvenue));
	
	while(1){
	  /*fgets(buff,1024,file);
		printf("<Pawnee> %s",buff);
		memset(buff,0,sizeof(buff));*/
	}
	
      } else {
	fprintf(file, msgErreur400, strlen(msgErreur400));
	close(socket_client);
	return 1;
      }
    } else {
      close(socket_client);
      wait(NULL);
    }
    
    
  }
  close(socket_serveur);
  
  return 0;
}

  int verifierEntete(char * str)
  {

  char *mots;
  char *tmp;
  tmp = strdup(str);
  mots = strtok(tmp," ");
  
  
  if(strcmp(mots,"GET") != 0)
    return 0;
    

  mots = strtok(NULL," ");
  mots = strtok(NULL," ");
  if(strcmp(mots,"HTTP/1.0") == 0 || strcmp(mots,"HTTP/1.1") == 0)
    return 0;
  
  printf("%s\n",str);
  return 1;
}

void traitement_signal(int sig)
{
  printf("Signal %d reçu\n",sig);
  /* attend un fils */
  if(sig == SIGCHLD)
    {
      if(waitpid(-1, NULL, 0) == -1)
	perror("waitpid");
    }
  /* ignore les SIGPIPE */
  else if(sig == SIGPIPE)
    if(signal(sig, SIG_IGN) == SIG_ERR)
      perror("signal(SIGPIPE, SIG_IGN)");
}
void initialiser_signaux(void)
{
  struct sigaction sa;
  /* handler */
  sa.sa_handler = traitement_signal;
  /* ensemble des signaux vides */
  sigemptyset(&sa.sa_mask);
  /* option par default */
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGPIPE, &sa, NULL) == -1)
    perror("sigaction(SIGPIPE)");
  if(sigaction(SIGCHLD, &sa, NULL) == -1)
    perror("sigaction(SIGCHLD)");
}
