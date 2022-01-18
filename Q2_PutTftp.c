#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <netdb.h>


const char lackArgs[] = "Pas assez d'aguments \n" ;

int main(int argc, char** argv){	
	
	struct addrinfo hints;
    struct addrinfo *result, *tmp;
    char host[256];
	const char* port="69";
    int s;
	
	
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
    
		
		
	

	
}
