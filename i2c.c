#include <stdio.h>
#include <unistd.h>
#include <wiringPiI2C.h>
//----------------------------------------------------------------------
// Fonction principale
//----------------------------------------------------------------------
int main(void)
{
int fd;
unsigned char Tab[10];
fd = wiringPiI2CSetup(0x25); // Configure la liaison I2C avec l’adresse 0x25
if(fd == -1)
{
printf("Pas d'i2c\n");
return -1;
}
flux_journal = fopen(journal.txt, "r");
if (flux_fichier_travail==NULL)
	{
	printf("Erreur lors de l'ouverture du fichier de travail.");
	return;
	}

Tab[0] = 80;
Tab[1] = 45;
63 68 61 6D 70 5F 74 65 78 74 65 3D
write(fd, Tab, 2); // Ecriture sur le bus I2C de 2 octets
return 0;
}
//----------------------------------------------------------------------
