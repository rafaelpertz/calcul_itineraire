#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <BDD.h>

void openBDD(){
	FILE* data = fopen("test.txt", "r");
	printf(data);
    	if (!data) {
        	perror("Erreur ouverture fichier test.txt");
        return data;
    }
}
BDD::BDD(
