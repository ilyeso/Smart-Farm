#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bestouv.h"
#include "callbacks.h"
enum
{
	ENOM,
	EPRENOM,
	EDATE,
	EADRESSEMAIL,
	ECIN,
	ENUMTEL,
	COLUMNS,
};


//calcul du bestouvrier de l'année 
int bestouv(char cin[],int year)
{
    FILE *f,*g;
    char liste_cin[1000][20];
    int n = 0;
    int max = 0;
    int nbre_jour=0;
    char numcin[20];
    int jj,aa,mm,pres;
    f = fopen("ouvrier.txt","r");
    ouvrier ouv;
    if((f != NULL) && (g != NULL))
{
        while(fscanf(f,"%s %s %s %s %s %s \n",ouv.Nom,ouv.Prenom,ouv.Date_de_naissance,ouv.adresse_mail,ouv.CIN,ouv.Numero_de_tel)!=EOF)

{
            strcpy(liste_cin[n],ouv.CIN);
            ++n;
}
        int i;
        for(i = 0;i<n;i++){
            g = fopen("absenteisme.txt","r");
            nbre_jour = 0;
            while(fscanf(g,"%s %d %d %d %d\n",numcin,&jj,&mm,&aa,&pres) != EOF)
{
                if(strcmp(liste_cin[i],numcin) == 0 && (year == aa))
{
                    if(pres == 1)
			{
                        nbre_jour ++;
                   	}
}
}
            printf("[%s] => %d\n",liste_cin[i],nbre_jour);
            if(nbre_jour > max){
                max = nbre_jour;
                strcpy(cin,liste_cin[i]);
}
            fclose(g);
        }
    }
    fclose(f);
return 0;
}

/*//fonction qui fait le parcours du fichier ouvrier.txt afin de faire sortir les labels
ouvrier find_ouvrier(char cin[])
{
    ouvrier o;			
    FILE *f;
    f = fopen("ouvrier.txt","r");
    if(f != NULL)
{
    	while(fscanf(f,"%s %s %s %s %s %s \n",o.Nom,o.Prenom,o.Date_de_naissance,o.adresse_mail,o.cin,o.Numero_de_tel)!=EOF)
{
        	if(strcmp(o.cin,cin) == 0)
{
       		     return cin;
        	}
    	}
}
    fclose(f);
    return;
}
*/
void afficher_bestouv(GtkWidget *liste)
{
ouvrier o;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char Nom[40];
    	char Prenom [40];
    	char Date_de_naissance [40];
    	char adresse_mail [40];
    	char CIN;
    	char Numero_de_tel;
	store=NULL;
	
	FILE *f;

	store=gtk_tree_view_get_model(liste);
 
	if (store==NULL)
	{
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOM, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", EPRENOM, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("date de naissance", renderer, "text", EDATE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);


		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Adressemail", renderer, "text", EADRESSEMAIL, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", ECIN, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Numero_de_tel", renderer, "text", ENUMTEL, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	}

	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);
	
	f=fopen("ouvrier.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f=fopen("ouvrier.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s \n", Nom, Prenom,Date_de_naissance, adresse_mail, CIN, Numero_de_tel )!=EOF)
		{
			gtk_list_store_append (store, &iter);
			gtk_list_store_set (store, &iter, ENOM, Nom, EPRENOM, Prenom, EDATE, Date_de_naissance ,EADRESSEMAIL ,adresse_mail ,ECIN ,CIN ,ENUMTEL,Numero_de_tel -1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}
}

