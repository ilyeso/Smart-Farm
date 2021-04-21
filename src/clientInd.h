#include <gtk/gtk.h>

typedef struct{
int jour;
int mois;
int annee;
}Date;

typedef struct{
char cin[20];
char nom[100];
char prenom[100];
char sexe[20];
Date date_naissance;
char adresse[200];
char numTel[20];
char email[100];
}clientInd;

void ajouter_client_ind( clientInd c);
void afficher_client_ind(GtkWidget *liste);
void modifier_client_ind( clientInd c);
void supprimer_client_ind( char cin[]);
clientInd find_client_ind(char cin[]);
int rechercher_cin(char cin[]) ;
int verifyNumber(char c[]);
int verifyName(char c[]);
int verifyDate(Date d) ;
