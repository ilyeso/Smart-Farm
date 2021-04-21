#include <stdio.h>
#include <string.h>
#include "clientPro.h"
#include <gtk/gtk.h>

enum{
        ENOM,
        EADRESSE,
        ENUMTEL,
	EMAIL,
        ECOLUMNS,
    };

///////////////////////////////////////////////////////////////////////////
void ajouter_client_pro(clientPro c)
{
FILE *f;
f= fopen("clientsPro.txt","a+");
if (f!=NULL)
{
fprintf(f,"%s %s %s %s  \n",c.nom,c.adresse,c.email,c.numTel);
fclose(f);
}
}


//////////////////////////////////////////////////////////////////////////////
void supprimer_client_pro(char nom[])
{
clientPro c2;
FILE *f, *g;
	f=fopen("clientsPro.txt","r");
	g=fopen("clientsPro2.txt","a");

	if(f==NULL || g==NULL)
		return;
	else
	{
		while(fscanf(f,"%s %s %s %s \n",c2.nom,c2.adresse,c2.numTel,c2.email)!=EOF)
	{
	if (strcmp(nom,c2.nom)!=0 ){
		fprintf(g,"%s %s %s %s \n",c2.nom,c2.adresse,c2.email,c2.numTel);}
	}
	fclose(f);
	fclose(g);
	remove("clientsPro.txt");
	rename("clientsPro2.txt","clientsPro.txt");
	}
}

////////////////////////////////////////////////////////////////////////////////

void modifier_client_pro( clientPro c)
{
	clientPro h;
	FILE *f, *g;
	f=fopen("clientsPro.txt","r");
	g=fopen("clientsPro2.txt","a");
	if (f!=NULL && g!=NULL) {
		while(fscanf(f,"%s %s %s %s\n",h.nom,h.adresse,h.email,h.numTel)!=EOF)
			{ if(strcmp(c.nom,h.nom)==0){
				fprintf(g,"%s %s %s %s\n",c.nom,c.adresse,c.email,c.numTel);}
			else{
				fprintf(g,"%s %s %s %s\n",h.nom,h.adresse,h.email,h.numTel);}
			}
		}
	fclose(f);
	fclose(g);
	remove("clientsPro.txt");
	rename("clientsPro2.txt","clientsPro.txt");
}

////////////////////////////////////////////////////////////////////////////////
void afficher_client_pro(GtkWidget *liste)
{
GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        GtkTreeIter iter;
        GtkListStore *store;
       
        char nom[100];
        char adresse[100];
        char numTel[20];
        char email[100];
     
        FILE *f;
        store = NULL;
        store = gtk_tree_view_get_model(liste);

        if(store == NULL){

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("nom",renderer,"text",ENOM,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Adresse",renderer,"text",EADRESSE,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Numero Tel",renderer,"text",ENUMTEL,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Email",renderer,"text",EMAIL,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
        }
    store = gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
       
       
        f = fopen("clientsPro.txt","r");
    if(f == NULL){
            return;
        }
    else{
            while(fscanf(f,"%s %s %s %s \n",nom,adresse,email,numTel) != EOF){            
    gtk_list_store_append(store,&iter);
                gtk_list_store_set(store,&iter,ENOM,nom,EADRESSE,adresse,EMAIL,email,ENUMTEL,numTel,-1);
               
            }
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
    g_object_unref(store);
            fclose(f);
        }
       
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////


int rechercher_nom(char nom[]){
    clientPro y;
    FILE *f;
    f = fopen("clientsPro.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s  \n",y.nom,y.adresse,y.email,y.numTel) != EOF){
        	if(strcmp(y.nom,nom) == 0){
       		     return 1;
        	}
    	}
}
    fclose(f);
    return 0;
    

}

//////////////////////////////////////////////////////////////////////////////////////////////////

clientPro find_client_pro(char nom[]){
    clientPro y;
    FILE *f;
    f = fopen("clientsPro.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s  \n",y.nom,y.adresse,y.email,y.numTel) != EOF){
        	if(strcmp(y.nom,nom) == 0){
       		     return y;
        	}
    	}
}
    fclose(f);
    return;
}


