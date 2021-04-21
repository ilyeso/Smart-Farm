#include <gtk/gtk.h>

typedef struct{
char nom[100];
char adresse[200];
char email[100];
char numTel[20];
} clientPro;

void ajouter_client_pro( clientPro c);
void afficher_client_pro( GtkWidget *liste);
void modifier_client_pro( clientPro c);
void supprimer_client_pro( char nom[]);
clientPro find_client_pro(char nom[]);
int rechercher_nom(char nom[]) ;
