#define NUMPORT        			2222
#define JOURNAL         		"journal.txt"
#define FICHIER_INDEX_HTML		"index.html"
#define FICHIER_ROBOT_HTML		"robot.html"

#include <stdlib.h> 
#include <stdio.h> 
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <errno.h> 
#include <string.h>
#include <strings.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int Recherche_Fichier_Html(const char *page, char *fichier_html);
int Recherche_Requete_GET(const char *Message, char *page_html, char *version_http);

//------------------------------------------------------------------------
// Fonction principale
//------------------------------------------------------------------------
int main() 
{ 
	int sock_ecoute, sock_com, taille_addr; 
	char buffer[1500];
	char buffer2[1500]; 
	char message[256]; 
	struct sockaddr_in addr_s, addr_cl; 
	int code_retour, n;
	int fd;
	char m[1500];
	int Num_message = 0;
	int nb_connexion = 0;
	char page_html[300];
	char fichier_html[1500];
	char version_http[100];

    FILE *Fichier;
  	char test[]="journal.txt";
    char find[100];
    char CODE81[] = "81";
    char CODE80[] = "80";
    char CODE79[] = "79";
	
	
	
		
	// Creation du socket d'écoute pour le serveur
	sock_ecoute = socket(PF_INET, SOCK_STREAM, 0); 
	if (sock_ecoute<0) 
	{ 
		perror("socket"); 
		return 1; 
	} 
	
	// Variable de definition de la connexion pour le socket serveur 
	addr_s.sin_family  			= AF_INET; 
	addr_s.sin_addr.s_addr      = INADDR_ANY; 
	addr_s.sin_port  			= htons(NUMPORT); 
	bzero(addr_s.sin_zero, sizeof(addr_s.sin_zero)); 
	
	// bind : affectation d'une extrémité de connexion locale au socket
	code_retour = bind(sock_ecoute, (struct sockaddr *) &addr_s, sizeof(addr_s)); 
	if (code_retour!=0)  
	{ 
		perror("bind"); 
		return 1; 
	}  
	
	// listen : Mise a l'écoute du socket serveur 
	code_retour = listen(sock_ecoute,1); 
	if (code_retour!=0)  
	{ 
		perror("listen"); 
		return 1; 
	} 
	
	// Suppression du journal précédent
	remove(JOURNAL);
	
	// Creation d'un nouveau Journal
	fd = open(JOURNAL, O_RDWR | O_CREAT);
	close(fd);
	
	// Change les droits d'acces au fichier Journal
	chmod(JOURNAL, S_IRUSR | S_IWUSR);
	
	printf("Serveur en écoute, attente d'une connexion cliente...\r\n");
	
	while(1)
	{ 
		// Acceptation de l’établissement de la connexion avec le socket client qui fait la demande
		taille_addr = sizeof(addr_cl); 
		sock_com = accept(sock_ecoute, (struct sockaddr *) &addr_cl, (socklen_t *) &taille_addr); 
		if (sock_com<0) 
		{ 
			perror("socket"); 
			return 1;
		}
		
		nb_connexion++;
		printf("\n\n----------------------------------------------------------------\n");
		printf("      Connexion numero : %d \n", nb_connexion); 
		printf("      IP du client : %s\n",inet_ntoa(addr_cl.sin_addr)); 
		printf("----------------------------------------------------------------\n");
		
		//Reception et affichage du message client 
		bzero(buffer, sizeof(buffer)); 
		n = read(sock_com,buffer,sizeof(buffer)); 
		if (n<0) 
		{ 
			perror("read"); 
		} 
		else if(n==0) 
		{ 
			printf("   Connection rompue par le client\n"); 
		} 
		else 
		{
			// Affichage du message recu
			printf("\n    Message recu sur le serveur :\n");
			printf("%s\n",buffer);
			printf("    Fin du Message recu sur le serveur\n");
			
			// Recherche de la page html de la requete GET
			if(Recherche_Requete_GET(buffer, page_html, version_http) == 1)
			{
				Recherche_Fichier_Html(page_html, fichier_html);
				printf("Page html demandée : %s\r\n", page_html);
				printf("Page html à afficher : %s\r\n", fichier_html);
				printf("Version HTTP : %s\r\n", version_http);
			}
			else
			{
				printf("Pas de requete GET\r\n");
			}

			
			// Enregistrement du message recu dans le journal
			fd = open(JOURNAL, O_RDWR | O_APPEND);
			Num_message++;
			sprintf(buffer2, "//-----------------------------------------\r\n");
			write(fd,buffer2,strlen(buffer2));
			
			sprintf(buffer2, "// Message numero : %d\r\n", Num_message);
			write(fd,buffer2,strlen(buffer2));

			sprintf(buffer2, "//-----------------------------------------\r\n");
			write(fd,buffer2,strlen(buffer2));

			write(fd,buffer,strlen(buffer));
			
			sprintf(buffer2, "//-----------------------------------------\r\n\r\n\r\n\r\n");
			write(fd,buffer2,strlen(buffer2));
			close(fd);
			
			// Reponse du serveur HTTP au client
			printf("Envoie de la commande au client : HTTP/1.1 200 OK\n");
			sprintf(message,"%s 200 OK\r\n", version_http); 
			n = write(sock_com,message,strlen(message));
			
			// lecture du fichier html à envoyer : fichier_html
			fd = open(fichier_html, O_RDONLY);
			bzero(m, 1500);
			read(fd, m, sizeof(m));
			//printf("\n %s\n", m);
			close(fd);
			
			// Envoi de la page HTML au client 
			printf("Envoie de la page html au client\n");
			n = write(sock_com,m,strlen(m));
			close(sock_com);
			printf("\n Fin de communication avec la connexion numero : %d\n", nb_connexion);
			printf("----------------------------------------------------------------\n");
		}
	printf("1\n");
	Fichier = fopen(&test, "r+");
	printf("2\n");
    if (!Fichier)printf("\aERREUR: Impossible d'ouvrir le fichier: %s.\n", JOURNAL);
    printf("3\n");
	while (fgets(find,100,Fichier) != NULL){
		printf("4\n");
			if (strstr(find, CODE81) != NULL){
			printf("81 trouvé");

		}
			if (strstr(find, CODE80) != NULL){
			printf("80 trouvé");

		}
			if (strstr(find, CODE79) != NULL){
			printf("79 trouvé");

		}
	  fclose(Fichier);
    }
	}
	
	close(sock_ecoute);  	// jamais atteint !!!!
	return 0;
}
//------------------------------------------------------------------------



//------------------------------------------------------------------------
// Recherche du fichier html à envoyer au client
//------------------------------------------------------------------------
int Recherche_Fichier_Html(const char *page, char *fichier_html) 
{
	bzero(fichier_html, 1500);
	
	stpcpy(fichier_html, FICHIER_INDEX_HTML);		// Page par defaut
	
	if(strcmp(page, "robot.html") == 0)		stpcpy(fichier_html, FICHIER_ROBOT_HTML);
	
	return 1;
}
//------------------------------------------------------------------------




//------------------------------------------------------------------------
// Recupere le nom de la page html passée dans le requete GET
//------------------------------------------------------------------------
int Recherche_Requete_GET(const char *Message, char *page_html, char *version_http) 
{
	int i;
	int n;
	int k;
	int l = 0;
	char *Texte_a_rechercher = "GET /";


	bzero(page_html, 300);
	n = strlen(Message);
	for(i=0; i<n; i++)
	{
		if(strncmp(&Message[i], Texte_a_rechercher, strlen(Texte_a_rechercher)) == 0)
		{
			for(k=(i+5); k<n; k++)
			{
				if(Message[k] == ' ')
				{
					l = k + 1;
					k = n + 1;
				}
				else
				{
					*page_html = Message[k];
					page_html = page_html + 1;
				}
			}
			
			if(l == 0)
			{
				stpcpy(version_http, "HTTP/1.1");
			}
			else
			{
				*version_http = 0;
				for(k=l; k<n; k++)
				{
					if(Message[k] == '\r')
					{
						l = k + 1;
						k = n + 1;
					}
					else
					{
						*version_http = Message[k];
						version_http = version_http + 1;
						*version_http = 0;
					}
				}
			}
			return 1;    // Commande trouvée
		}
	}
	return -1; // Commande non trouvée
}
//------------------------------------------------------------------------








