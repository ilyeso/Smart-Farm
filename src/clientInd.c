#include <stdio.h>
#include <string.h>
#include "clientInd.h"
#include <gtk/gtk.h>
#include <time.h>

enum{
        ECIN,
        ENOM,
        EPRENOM,
        ESEXE,
        EDATE,
        EADRESSE,
        ENUMTEL,
	EMAIL,
        ECOLUMNS,

    };
///////////////////////////////////////////////////////////////////////////
void ajouter_client_ind(clientInd c)
{
FILE *f;
f= fopen("clientsInd.txt","a+");
if (f!=NULL)
{
fprintf(f,"%s %s %s %s %d %d %d %s %s %s \n",c.cin,c.nom,c.prenom,c.sexe,c.date_naissance.jour,c.date_naissance.mois,c.date_naissance.annee,c.adresse,c.numTel,c.email);
fclose(f);
}
}


//////////////////////////////////////////////////////////////////////////////
void supprimer_client_ind(char cin[])
{
clientInd c2;
FILE *f, *g;
	f=fopen("clientsInd.txt","r");
	g=fopen("clientsInd2.txt","a");

	if(f==NULL || g==NULL)
		return;
	else
	{
		while(fscanf(f,"%s %s %s %s %d %d %d %s %s %s \n",c2.cin,c2.nom,c2.prenom,c2.sexe,&c2.date_naissance.jour,&c2.date_naissance.mois,&c2.date_naissance.annee,c2.adresse,c2.numTel,c2.email)!=EOF)
	{
	if (strcmp(cin,c2.cin)!=0 ){
		fprintf(g,"%s %s %s %s %d %d %d %s %s %s \n",c2.cin,c2.nom,c2.prenom,c2.sexe,c2.date_naissance.jour,c2.date_naissance.mois,c2.date_naissance.annee,c2.adresse,c2.numTel,c2.email);}
	}
	fclose(f);
	fclose(g);
	remove("clientsInd.txt");
	rename("clientsInd2.txt","clientsInd.txt");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
void afficher_client_ind(GtkWidget *liste){
       
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        GtkTreeIter iter;
        GtkListStore *store;
       
        char cin[20];
        char nom[30];
        char prenom[30];
	char sexe[20];
        Date date;
        char adresse[100];
        char numTel[20];
        char email[20];
     	char dat[50];
        FILE *f;
        store = NULL;
        store = gtk_tree_view_get_model(liste);

        if(store == NULL){
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Cin",renderer,"text",ECIN,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",ENOM,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Prenom",renderer,"text",EPRENOM,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Sexe",renderer,"text",ESEXE,NULL);
            column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes("Date de naissance",renderer,"text",EDATE,NULL);
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
    store = gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
       
       
        f = fopen("clientsInd.txt","r");
    if(f == NULL){
            return;
        }
    else{
            while(fscanf(f,"%s %s %s %s %d %d %d %s %s %s \n",cin,nom,prenom,sexe,&date.jour,&date.mois,&date.annee,adresse,numTel,email) != EOF){            
    gtk_list_store_append(store,&iter);
	sprintf(dat,"%d/%d/%d",date.jour,date.mois,date.annee);
                gtk_list_store_set(store,&iter,ECIN,cin,ENOM,nom,EPRENOM,prenom,ESEXE,sexe,EDATE,dat,EADRESSE,adresse,ENUMTEL,numTel,EMAIL,email,-1);
               
            }
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
    g_object_unref(store);
            fclose(f);
        }
       
    }

///////////////////////////////////////////////////////////////////////////////////////
void modifier_client_ind( clientInd c)
{
	clientInd h;
	FILE *f, *g;
	f=fopen("clientsInd.txt","r");
	g=fopen("clientsInd2.txt","a");
	if (f!=NULL && g!=NULL) {
		while(fscanf(f,"%s %s %s %s %d %d %d %s %s %s \n",h.cin,h.nom,h.prenom,h.sexe,&h.date_naissance.jour,&h.date_naissance.mois,&h.date_naissance.annee,h.adresse,h.numTel,h.email)!=EOF)
			{ if(strcmp(c.cin,h.cin)==0){
				fprintf(g,"%s %s %s %s %d %d %d %s %s %s \n",c.cin,c.nom,c.prenom,c.sexe,c.date_naissance.jour,c.date_naissance.mois,c.date_naissance.annee,c.adresse,c.numTel,c.email);}
			else{
				fprintf(g,"%s %s %s %s %d %d %d %s %s %s \n",h.cin,h.nom,h.prenom,h.sexe,h.date_naissance.jour,h.date_naissance.mois,h.date_naissance.annee,h.adresse,h.numTel,h.email);}
			}
		}
	fclose(f);
	fclose(g);
	remove("clientsInd.txt");
	rename("clientsInd2.txt","clientsInd.txt");
}


//////////////////////////////////////////////////////////////////
int rechercher_cin(char cin[]){
    clientInd y;
    FILE *f;
    f = fopen("clientsInd.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s %d %d %d %s %s %s \n",y.cin,y.nom,y.prenom,y.sexe,&(y.date_naissance.jour),&(y.date_naissance.mois),&(y.date_naissance.annee),y.adresse,y.numTel,y.email) != EOF){
        	if(strcmp(y.cin,cin) == 0){
       		     return 1;
        	}
    	}
}
    fclose(f);
    return 0;
    

}

/////////////////////////////////////////////////////////////////////////

clientInd find_client_ind(char cin[])
{
    clientInd y;
    FILE *f;
    f = fopen("clientsInd.txt","r");
    if(f != NULL){
    	while(fscanf(f,"%s %s %s %s %d %d %d %s %s %s \n",y.cin,y.nom,y.prenom,y.sexe,&(y.date_naissance.jour),&(y.date_naissance.mois),&(y.date_naissance.annee),y.adresse,y.numTel,y.email) != EOF){
        	if(strcmp(y.cin,cin) == 0){
       		     return y;
        	}
    	}
}
    fclose(f);
    return;
}


//////////////////////////////////////////////

int verifyNumber(char c[]){
    if(strlen(c) < 7){
        return 0;
    }
    else{
        int i,x;
        for(i=0;i<8;i++){
            x = c[i];
            if(x>57 || x<48){
                return 0;
            }
        }
        return 1;
    }
}
/*----------------------------------------*/
int verifyName(char c[]){
    if(strlen(c) == 0){
        return 0;
    }
    else{
        int i,x;
        for(i=0;i<strlen(c);i++){
            x= c[i];
            if(x<65 || x>122 || (x>90 && x < 97)){
                return 0;
            }
        }
        return 1;
    }
}

int verifyDate(Date d){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int j,m,a;
    j = tm.tm_mday;
    m =  tm.tm_mon + 1;
    a =  tm.tm_year + 1900;

    if(d.annee < a){
        return 1;
    }
    else if(d.annee == a){
        if(d.mois < m){
            return 1;
        }
        else if(d.mois == m){
            if(d.jour > j){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}	
