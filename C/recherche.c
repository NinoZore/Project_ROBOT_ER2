
#include <stdio.h>
#include <string.h>
  
int main(void)
{
    char test[]="journal.txt";
    FILE *Fichier;
  
    char find[100];
    char CODE81[] = "81";
    char CODE80[] = "80";
    char CODE79[] = "79";
    
    Fichier = fopen(test, "r");
    if (!Fichier)
         printf("\aERREUR: Impossible d'ouvrir le fichier: %s.\n", test);
    
while (fgets(find,100,Fichier) != NULL)
    {
        if (strstr(find, CODE81) != NULL){
        printf("81 trouvé");

      }
        if (strstr(find, CODE80) != NULL){
        printf("80 trouvé");

      }
        if (strstr(find, CODE79) != NULL){
        printf("79 trouvé");

      }
    }
    fclose(Fichier);
    return 0;
}



