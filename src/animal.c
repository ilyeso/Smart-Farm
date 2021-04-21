

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include <gtk/gtk.h>


enum
{
	EID,
	EFAMILLE,
	ESEXE,
	EPOIDS,
	ESANTE,
	EDATE,
	ECOLUMNS,
};


// Fonction Ajouter //
void ajouter_animal(animal a)
{
    FILE *f;
    f=fopen("Troupeaux.txt","a+");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %s %s %s %s %d %d %d\n", a.id, a.famille, a.sexe, a.poids, a.sante.vac, a.sante.malade, a.sante.gestante, a.date.j, a.date.m, a.date.a);
        fclose(f);
    }
}


// Fonction Supprimer //
void supp_animal(char ident[])
{
animal b;
FILE *f,*g;

    f=fopen("Troupeaux.txt","r");
    g=fopen("Troupeaux2.txt","a");

    if ((f==NULL) || (g==NULL))
    	return;
    else
    {
    	while(fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", b.id, b.famille, b.sexe, b.poids, b.sante.vac, b.sante.malade, b.sante.gestante, &b.date.j, &b.date.m, &b.date.a)!=EOF)
	{
        	if (strcmp(ident,b.id)!=0)
	     		fprintf(g,"%s %s %s %s %s %s %s %d %d %d\n", b.id, b.famille, b.sexe, b.poids, b.sante.vac, b.sante.malade, b.sante.gestante, b.date.j, b.date.m, b.date.a);
        }
	fclose(f);
        fclose(g);

remove("Troupeaux.txt");
rename("Troupeaux2.txt","Troupeaux.txt");
    }
}


// Fonction Afficher //
void afficher_animal(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char id[20];
   	char famille[20];
   	char sexe[20];
   	char poids[20];
	sante sante;
   	date date;
	char dn[20];
	char st[50];
	FILE *f;
	
	store = NULL;
	store = gtk_tree_view_get_model(liste);
 
	if (store==NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Id",renderer,"text",EID,NULL);
         	column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        	renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("Famille",renderer,"text",EFAMILLE,NULL);
                column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("Sexe",renderer,"text",ESEXE,NULL);
                column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("Poids",renderer,"text",EPOIDS,NULL);
                column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("Sante",renderer,"text",ESANTE,NULL);
                column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes("Date",renderer,"text",EDATE,NULL);
                column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	}

	store=gtk_list_store_new (ECOLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	
	f=fopen("Troupeaux.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", id, famille, sexe, poids, sante.vac, sante.malade, sante.gestante, &date.j, &date.m, &date.a)!=EOF)
		{
			gtk_list_store_append (store, &iter);
			sprintf(dn,"%d/%d/%d", date.j, date.m, date.a);
			sprintf(st,"%s/%s/%s", sante.vac, sante.malade, sante.gestante);
			gtk_list_store_set (store, &iter, EID, id, EFAMILLE, famille, ESEXE, sexe, EPOIDS, poids, ESANTE, st, EDATE, dn, -1);
		}

		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
		fclose(f);
	}
}


// Fonction Modifier //
void modif_animal(animal a)
{
	animal c;
	FILE *f, *g;
	f=fopen("Troupeaux.txt","r");
	g=fopen("Troupeaux2.txt","a");
	if (f!=NULL && g!=NULL) 
	{
		while(fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", c.id, c.famille, c.sexe, c.poids, c.sante.vac, c.sante.malade, c.sante.gestante, &c.date.j, &c.date.m, &c.date.a)!=EOF)
		{
			if(strcmp(a.id,c.id)==0)
			{
				fprintf(g,"%s %s %s %s %s %s %s %d %d %d\n", a.id, a.famille, a.sexe, a.poids, a.sante.vac, a.sante.malade, a.sante.gestante, a.date.j, a.date.m, a.date.a);
			}
			else
			{
				fprintf(g,"%s %s %s %s %s %s %s %d %d %d\n", c.id, c.famille, c.sexe, c.poids, c.sante.vac, c.sante.malade, c.sante.gestante, c.date.j, c.date.m, c.date.a);
			}
		}
	}
	fclose(f);
	fclose(g);
	remove("Troupeaux.txt");
	rename("Troupeaux2.txt","Troupeaux.txt");
}

// Fonctions Nombre d'animaux de chaque famille //
// Fonction Nombre de Vache //
int nb_vache()
{
	FILE *f;
	char ch1[20];
	char ch2[20];
	char ch3[20];
	char ch4[20];
	char ch5[20];
	char ch6[20];
	char ch7[20];
	int  a,b,c;
	int nb=0;

	f=fopen("Troupeaux.txt","r");
	while (fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", ch1, ch2, ch3, ch4, ch5, ch6, ch7, &a, &b, &c)!=EOF)
        {
        	if (strcmp(ch2,"Vache")==0)
        	        nb=nb+1;
        }
	fclose(f);
	return nb;
}


// Fonction Nombre de Mouton //
int nb_mouton()
{
	FILE *f;
	char ch1[20];
	char ch2[20];
	char ch3[20];
	char ch4[20];
	char ch5[20];
	char ch6[20];
	char ch7[20];
	int  a,b,c;
	int nb=0;

	f=fopen("Troupeaux.txt","r");
	while (fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", ch1, ch2, ch3, ch4, ch5, ch6, ch7, &a, &b, &c)!=EOF)
        {
        	if (strcmp(ch2,"Mouton")==0)
        	        nb=nb+1;
        }
	fclose(f);
	return nb;
}


// Fonction Nombre de Cheval //
int nb_cheval()
{
	FILE *f;
	char ch1[20];
	char ch2[20];
	char ch3[20];
	char ch4[20];
	char ch5[20];
	char ch6[20];
	char ch7[20];
	int  a,b,c;
	int nb=0;

	f=fopen("Troupeaux.txt","r");
	while (fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", ch1, ch2, ch3, ch4, ch5, ch6, ch7, &a, &b, &c)!=EOF)
        {
        	if (strcmp(ch2,"Cheval")==0)
        	        nb=nb+1;
        }
	fclose(f);
	return nb;
}


// Fonction Nombre de Poule //
int nb_poule()
{
	FILE *f;
	char ch1[20];
	char ch2[20];
	char ch3[20];
	char ch4[20];
	char ch5[20];
	char ch6[20];
	char ch7[20];
	int  a,b,c;
	int nb=0;

	f=fopen("Troupeaux.txt","r");
	while (fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", ch1, ch2, ch3, ch4, ch5, ch6, ch7, &a, &b, &c)!=EOF)
        {
        	if (strcmp(ch2,"Poule")==0)
        	        nb=nb+1;
        }
	fclose(f);
	return nb;
}


// Fonction Rechercher //
int rechercher_animal(char ident[])
{
	animal g;
        FILE *f;
        f = fopen("Troupeaux.txt","r");
        if(f != NULL)
	{
	    	while(fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", g.id, g.famille, g.sexe, g.poids, g.sante.vac, g.sante.malade, g.sante.gestante, &g.date.j, &g.date.m, &g.date.a)!=EOF)
		{
        		if(strcmp(g.id,ident) == 0)
			{
       		     		return 1;
        		}
    		}
	}
    	fclose(f);
    	return 0;
}


// Fonction Find //
animal find_animal(char ident[])
{
	animal h;
	FILE *f;
        f = fopen("Troupeaux.txt","r");
        if(f != NULL)
	{
	    	while(fscanf(f,"%s %s %s %s %s %s %s %d %d %d\n", h.id, h.famille, h.sexe, h.poids, h.sante.vac, h.sante.malade, h.sante.gestante, &h.date.j, &h.date.m, &h.date.a)!=EOF)
		{        	
			if(strcmp(h.id,ident) == 0)
			{
       		     		return h;
	        	}
	    	}
	}
	fclose(f);
  	return;
}


// Fonctions Année la plus sèche //
/* Fonction Rechercher */
int rech(int t[], int n, int val)
{
int i=0;
while ((i<n)&&(t[i]!=val))
{
       i++;
}
    return i;
}

/* Fonction Principale */
int annee_seche()
{
int id,j,m,a,r1,r2,x,y,z,an;
int n1=0;
int annee[20];
float t,min;
float somme[20];
float moyenne[20];
FILE *f;

/* Remplir le tableau des années */
f=fopen("temperature.txt","r");
while (fscanf(f,"%d %d %d %d %f\n", &id, &j, &m, &a, &t)!=EOF)
{
	r1= rech(annee, n1, a);
        if(r1==n1)
        {
                annee[n1]=a;
                somme[n1]=0;
                n1++;
        }
}
fclose(f);

/* Remplir le tableau des sommes */
f=fopen("temperature.txt","r");
while (fscanf(f,"%d %d %d %d %f\n", &id, &j, &m, &a, &t)!=EOF)
{
	r2= rech(annee, n1, a);
        somme[r2]=somme[r2]+t;
}
fclose(f);

/* Remplir le tableau des moyennes */
for (y=0; y<n1; y++)
{
	moyenne[y]=(somme[y]/365);
}

/* Calcul de l'année la plus sèche */
min = moyenne[0];
for (z=0; z<n1; z++)
{
if (moyenne[z] < min)
        {
        min= moyenne[z];
        an = z;
        }
}
return annee[an];
}


