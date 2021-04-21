#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gdk/gdkkeysyms.h>
#include "support.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "capteur.h"
#include <gtk/gtk.h>
#include "callbacks.h"

//---------------------------------------<<<<< recherche >>>-------------------------
capteur rech_capteur(char *fi,char idRech[])

{
    capteur vide ={"-1","vide","vide","vide","0","0","vide","vide"} ;
    capteur c ;
    FILE *f;
    f=fopen(fi,"r");

    while (fscanf(f,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm)!=EOF)
        {
          if(strcmp (c.id,idRech )==0)
          {
           fclose(f);
           return c ;
           }
        }

   fclose(f);
   return vide;
}

//-----------------------------------------------------------------------------------------
//---------------------------------------<<<<< Ajout >>>-----------------------------------

int ajout_capteur(char *fi, capteur c )
{
    FILE *f;
    f=fopen(fi,"a");
    if(f!=NULL)
    {
        if (   strcmp(rech_capteur(fi,c.id).id,c.id)!=0    )
       {
           fprintf(f,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm);
           fclose(f);
           return 1 ;
       }
       else
        {
        fclose(f);
        return 0;
        }

    }
}
//----------------------------------------------------------------------------------
//---------------------------------------<<<<< Suppression >>>-------------------------
int supp_capteur(char *fi, char *id )
{
FILE *f1 ;
FILE *f2;
capteur c ;
int k=0;
f1=fopen(fi,"r");

if(f1!=NULL)
 {
   f2=fopen("cap_temp.txt","w");
    if(f2!=NULL)
    {
           while(fscanf(f1,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm)!= EOF)
           {

             if(strcmp (c.id,id )!=0)
                    fprintf(f2,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm) ;
             else
               k=1 ;

            }
           fclose(f1);
           fclose(f2);
   }
}
if (k==1)
{
    remove("capteur.txt");
    rename("cap_temp.txt","capteur.txt");
    return 1;
}
else
{
    remove("cap_temp.txt");
    return 0;
}

}

//------------------------------------------------------------------------------------
//---------------------------------------<<<<< Modification >>>-------------------------
void modif_capteur (char *fi , capteur k  )
{

FILE *f1 ;
FILE *f2;
capteur c ;
f1=fopen(fi,"r");

if(f1!=NULL)
{
   f2=fopen("modif_temp.txt","w");
    if(f2!=NULL)
       {
           while(fscanf(f1,"%s %s %s %s %s %s %s %s",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm)!=EOF)
           {

            if(strcmp (c.id,k.id )==0)
            fprintf(f2,"%s %s %s %s %s %s %s %s\n",k.id,k.type,k.marque,k.place,k.valMin,k.valMax,k.inOut,k.perm);
            else
            fprintf(f2,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm);

            }
           fclose(f1);
           fclose(f2);
       }
}
remove("capteur.txt");
rename("modif_temp.txt","capteur.txt");
}
//-----------------------------------------------------------------------------------------
//--------------------<<<<< AFFICHAGE >>>------------------------------------------------
 
void afficher_cap(GtkWidget *liste ,char file[])
{
	GtkCellRenderer *renderer;
	GtkCellRenderer *renderer1;
	GtkTreeViewColumn *column;
	GtkTreeIter    iter;
	GtkListStore *store;

  char Numero [50]  ;
  char Type[50]  ;
  char Marque[50] ;
  char Emplacement[50] ;
  char valeurMin[50]  ;
  char valeurMax[50] ;
  char internExtern[50];
  char Permeabilite[50];

	// store = NULL ;
	FILE *f ; 
	
	store=gtk_tree_view_get_model(liste);
		if (store == NULL ) 
		{
 		renderer = gtk_cell_renderer_toggle_new();
		renderer1=renderer;
		column = gtk_tree_view_column_new_with_attributes("SELECTION", renderer, "active",SELECTION, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Numero", renderer, "text",Eid, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",Etype, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Marque", renderer, "text",Emarque, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Emplacement", renderer, "text",Eplace, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("valeurMin", renderer, "text",EvalMin, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("valeurMax", renderer, "text",EvalMax, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("internExtern", renderer, "text",EinOut, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Permeabilite", renderer, "text",Eperm, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
		
		

  store=gtk_list_store_new (COLUMNS,G_TYPE_BOOLEAN, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
		}

		f=fopen(file,"r");
		if(f==NULL)
		{
		return;
		}
		else
 		{
              //  f=fopen(file,"a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s\n",Numero,Type,Marque,Emplacement,valeurMin,valeurMax,internExtern,Permeabilite)!=EOF)
		{
 	gtk_list_store_append (store, &iter);
	gtk_list_store_set(store, &iter, SELECTION, FALSE, Eid, Numero,Etype, Type, Emarque, Marque,Eplace,Emplacement,EvalMin,valeurMin,EvalMax,valeurMax,EinOut,internExtern,Eperm,Permeabilite, -1);
		}

              fclose(f);
	      gtk_tree_view_set_model (GTK_TREE_VIEW (liste),  GTK_TREE_MODEL (store));
              g_signal_connect(G_OBJECT(renderer1), "toggled", (GCallback)toggled_func, store);
              g_object_unref (store);

		
}

}
//--------------------------------------------------------------------------------------------
 
 void recher(char rech[] ) 
{

capteur c ;
FILE *f ;
FILE *f1 ;
f1=fopen("capteur.txt","r");
if (f1!=NULL)
{
    f=fopen("rechecap.txt","w+") ;
   if (f!=NULL )
   {
    while(fscanf(f1,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm)!= EOF)
    {
      if((strcmp(c.id,rech)==0) ||(strcmp(c.type,rech)==0) || (strcmp(c.marque,rech)==0) ||  (strcmp(c.place,rech)==0) ||  (strcmp(c.inOut,rech)==0) ||  (strcmp(c.perm,rech)==0) )
       {
      fprintf(f,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm) ;
       }

}

}
           fclose(f);
           fclose(f1);
}

}

/* ---------------------------------------------------------------------------------------------
                       fonctions des capteurs dans la  tache  2 
---------------------------------------------------------------------------------------------  */ 

void afficher_valAlarm(GtkWidget *liste ,char file[])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter    iter;
	GtkListStore *store;
	GdkPixbuf *pix ;

  char Numero [50]  ;
  char Type[50]  ;
  char Emplacement[50] ;
  char valeur[50] ;

	 store = NULL ;
	FILE *f ; 
	pix = gdk_pixbuf_new_from_file("icons8-alert-30.png", NULL);
	store=gtk_tree_view_get_model(liste);
		if (store == NULL ) 
		{
 		renderer = gtk_cell_renderer_pixbuf_new();
		column = gtk_tree_view_column_new_with_attributes("Alerte", renderer, "pixbuf",IMAGE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Numero", renderer, "text",Enum, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Emplacement", renderer, "text",Emplace, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("Valeur", renderer, "text",Eval, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);


      store=gtk_list_store_new (Columns,GDK_TYPE_PIXBUF, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );
		}

		f=fopen(file,"r");
		if(f==NULL)
		{
		return;
		}
		else
 		{
                f=fopen(file,"a+");
		while(fscanf(f,"%s %s %s %s\n",Numero,Type,Emplacement , valeur)!=EOF)
		{
 	gtk_list_store_append (store, &iter);
	gtk_list_store_set(store, &iter, IMAGE, pix, Enum, Numero,ETYPE, Type ,Emplace,Emplacement,Eval,valeur, -1);
		}

              fclose(f);
	      gtk_tree_view_set_model (GTK_TREE_VIEW (liste),  GTK_TREE_MODEL (store));
              g_object_unref (store);
              //g_object_unref (pix);	     

		
}

}

//----------------------------------------------------------------------------------------------

  void alarme( float rate , char value[] )
{
    FILE *f ;
    FILE *g ;
    int jour,mois,annee;
    float valeurCap, valmin , valmax ;
    char idCap[20]; 
    capteur c ;


       f=fopen(value,"r");
    if (f!=NULL)
        {
           g=fopen("Alarmant.txt","w");
           if (g!= NULL)
               {

              while(fscanf(f,"%s %d %d %d %f\n",idCap,&jour,&mois,&annee,&valeurCap)!=EOF)
              {
             //sprintf(IDrech ,"%d",idCap) ;
             //itoa(idCap,IDrech,10);
             c =  rech_capteur("capteur.txt" ,idCap ) ;
             valmin = atof(c.valMin) ;
             valmax = atof(c.valMax) ;

             if (   ( valeurCap <= ( valmin-((valmin * rate)/100 ))) || ( valeurCap >= (valmax * rate ) / 100  )    )
             {
                 fprintf(g,"%s %s %s %s\n",c.id,c.type ,c.place,c.perm);
             }
         }
         }
         fclose(f);
         fclose(g) ;
        }

}

    
/* void alarme( float rate , char value[] )
{

    FILE *f ;
    FILE *g ;
    int i ;
    int  idCap ,jour,mois,annee;
    char IDrech[10] ;
    float valeurCap, valmin , valmax ;
    capteur c ;
    int T[50] ;
    int n =0 ;

     f=fopen(value,"r");
      if( f!=NULL )
       {
        while(fscanf(f,"%d %d %d %d %f\n",&idCap,&jour,&mois,&annee,&valeurCap)!=EOF)
         {
              sprintf(IDrech ,"%d",idCap) ;
             // itoa(idCap,IDrech,10);
             c = ( rech_capteur("capteur.txt" ,IDrech ));
             valmin = atof(c.valMin) ;
             valmax = atof(c.valMax) ;

             if (   ( valeurCap <= ( valmin-((valmin * rate)/100 ))) || ( valeurCap >= (valmax * rate ) / 100  )    )
             {
                 T[n] = idCap ;
                 printf("%d\n",T[n]) ;
                 n++ ;

             }
         }
         fclose(f);
       }
       g= fopen("alarmant.txt","w") ;
       if (g!=NULL)
    {
       for (i=0;i<n;i++)
       {
           sprintf(IDrech ,"%d",T[i]) ;
           c = ( rech_capteur("capteur.txt" ,IDrech ));
           fprintf(g,"%s %s %s\n",c.id,c.place,c.type) ;

       }
       fclose(g);
     }

}     */ 
//--------------------------------------------------------------------------------
/*              marque des capteurs ayant max des cap déféctueux
----------------------------------------------------------------------------------*/
  int rechercheMot( char mat [][50],int n, char mot[])
{
    int i ;
    int k =0 ;

    for (i=0;(i<n)&&(!k);i++)
    {
       if (  strcmp( mat[i] , mot)== 0 )
        k=1 ;
    }
        return k ;
}
//----------------------------------------------------------
   
void MaxMarques(char resultat[] , int *max )
{

     int idCap, jour,mois,annee;
     char IDrech[20];  /// pour convertir id du capteur en chaine
     char ID[20]; /// de meme
     float valeurCap, valmin , valmax ;
     int Tid[100]; /// tableau des id  des capteurs defectueux
     int nTid =0; /// taille du tableau des id defectueux
     char Mat[50][50] = {"vide"}; /// matrice des noms des marques
     int nMat =0 ; /// taille du matrice des nom des marques
     int defec[100] ; /// tableau de compter nombre d'occurence des marques
     int i=0 , j;
     int indice ; /// pour determiner l'indice du max du tableau defect
     capteur c ;
     FILE *fi ;
     FILE *gi ;
 ///------------<<<<< recherche les id des capteurs defectueux depuis le fichier valeur.txt >>>>---------
     fi=fopen("valeur.txt","r");
    if (fi==NULL)
        return ;
    else
        {
         while(fscanf(fi,"%d %d %d %d %f",&idCap,&jour,&mois,&annee,&valeurCap)!=EOF)
         {
             sprintf(IDrech,"%d",idCap) ; 
            // itoa(idCap,IDrech,10);
             c = ( rech_capteur("capteur.txt" ,IDrech ));
             valmin = atof(c.valMin) ;
             valmax = atof(c.valMax) ;

             if (   (valeurCap < valmin ) || (valeurCap > valmax  ) )
             {
                 Tid[i]=idCap ;
                   i++;
                   nTid++;
             }
         }
         fclose(fi);
        }
       
///--------<<<<< extraire les differents marques des capteur depuis le fichier capteur.txt >>>------------------


    gi=fopen("capteur.txt","r");
    if (gi!=NULL)
    {
         while(fscanf(gi,"%s %s %s %s %s %s %s %s\n",c.id,c.type,c.marque,c.place,c.valMin,c.valMax,c.inOut,c.perm)!= EOF)
         {

             if ( strcmp( Mat[0],"vide" )== 0)
                 {

                 strcpy(Mat[0],c.marque) ;
                   nMat++ ;
                  }
             if(!(rechercheMot(  Mat, nMat , c.marque) ))
               {

                  strcpy(Mat[nMat],c.marque) ;
                    nMat++;
               }
         }
    }
    fclose(gi);
///-----------<<< remplir un tableau des entiers de meme taille que matrice de marque , et determiner la marque à chercher

    for (i=0;i<nMat;i++)
    {
        defec[i]=0 ;
    }
    for (i=0;i<nTid;i++)
    {
        sprintf(ID , "%d",Tid[i]) ;
       // itoa(Tid[i],ID,10) ;
        c=rech_capteur("capteur.txt",ID);
        for(j=0;j<nMat;j++)
        {
            if (strcmp(c.marque,Mat[j])==0  )
                defec[j] ++ ;
        }
    }
  
    ///----- <<< chercher le max de ce tableau et determine son indice >>>-----------------

   *max =defec[0] ;
    for(i=1;i<nMat;i++)
    {
        if (defec[i]>*max)
        {
             *max=defec[i];
            indice = i ;
        }

    }
    strcpy(resultat,Mat[indice]) ;

   
 }

















