#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define CMD_SIZE 100

const char lackArgs[] = "Pas assez d'aguments \n" ;

//Définition de la requête en écriture
int defWRQ(char* filename, char* mode, char* cmd){
	int cmdLen= 2+strlen(filename)+1+strlen(mode)+1;
	//cmd=malloc(cmdLen);
	
	cmd[0]=0;
	cmd[1]=2;
	strcpy(&cmd[2],filename);
	cmd[2+strlen(filename)]=0;
	strcpy(&cmd[3+strlen(filename)],mode);
	//cmd[cmdLen-1]=0;
	
	return cmdLen;
}



int main(int argc, char** argv){	
	
	struct addrinfo hints;
    struct addrinfo *result, *tmp;
    char host[256];
	const char* port="69";
    int s;
    int skt;
    
	char cmd[CMD_SIZE];
	char *filename=argv[2];
	
    
	
	
	//S'il n'y a pas assez d'argument, on renvoie un message d'erreur
	if (argc<3){
		write(STDOUT_FILENO, lackArgs, sizeof(lackArgs));
		exit(EXIT_FAILURE);
		}
	
	
	//Initialisation de getaddrinfo()	
	memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(argv[1], port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    //On renvoie l'addresse IP du serveur choisi
    for (tmp = result; tmp != NULL; tmp = tmp->ai_next) {
        getnameinfo(tmp->ai_addr, tmp->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        write(STDOUT_FILENO, host, strlen(host));
        write(STDOUT_FILENO, "\n", strlen("\n"));
    }
    
    //Réservation de la socket
	skt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (skt<0){
		write(STDOUT_FILENO, "Socket error", strlen("Socket error"));
		exit(EXIT_FAILURE);
	}	
	
	//Ecriture de la requête RRQ dans cmd
	int cmdSize=defWRQ(filename,"octet",cmd);
	
	//Envoi de la requête
	int t = sendto (skt, cmd, cmdSize, 0, result->ai_addr, result->ai_addrlen);
	if(t<0){
		write(STDOUT_FILENO, "Send error", strlen("Send error"));
	}
	
		

	
}
