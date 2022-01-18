#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



const char lackArgs[] = "Pas assez d'aguments \n" ;

int main(int argc, char** argv){	
	
	//S'il n'y a pas assez d'argument, on renvoie un message d'erreur
	if (argc<3){
		write(STDOUT_FILENO, lackArgs, sizeof(lackArgs));
		exit(EXIT_FAILURE);
		}
		
	//Sinon on affiche les 3 premiers arguments	
	else {
		char* cmd =strcat(argv[0]," ");
		char* adress = strcat(argv[1],"  ");
		char* file = strcat(argv[2],"\n");
		write(STDOUT_FILENO, cmd, sizeof(cmd));
		write(STDOUT_FILENO, adress, sizeof(adress));
		write(STDOUT_FILENO, file, sizeof(file));
		exit(EXIT_SUCCESS);
	}		
			
		
		
	

	
}
