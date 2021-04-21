#include<gtk/gtk.h>
typedef struct {

    char Nom[40];
    char Prenom [40];
    char Date_de_naissance [40];
    char adresse_mail [40];
    char CIN;
    char Numero_de_tel;
}ouvrier;

//calcul du nbrs de jours travaillés par ouvrier et determiner le BestOuvrier
int bestouv(char cin[],int year);
//fonction qui fait le parcours du fichier ouvrier.txt afin de faire sortir les labels
//ouvrier find_ouvrier(char cin[]);
void afficher_bestouv(GtkWidget *liste);
