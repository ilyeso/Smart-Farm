

#include <gtk/gtk.h>


// Structure Santé //
typedef struct sante
{
    char vac[20];
    char malade[20];
    char gestante[20];
}   sante;


// Structure Date de Naissance //
typedef struct date
{
    int j;
    int m;
    int a;
}   date;


// Structure Animal //
typedef struct animal
{
    char id[20];
    char famille[20];
    char sexe[20];
    char poids[20];
    sante sante;
    date date;
}   animal;


void ajouter_animal(animal a);
void supp_animal(char ident[]);
void afficher_animal(GtkWidget *liste);
void modif_animal(animal a);
int nb_vache();
int nb_mouton();
int nb_cheval();
int nb_poule();
int rechercher_animal(char ident[]);
animal find_animal(char ident[]);
int rech(int t[], int n, int val);
int annee_seche();




