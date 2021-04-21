#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "capteur.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pango/pangocairo.h>
#include <curl/curl.h>
#include "curl/curl.h"

#include "clientInd.h"
#include "clientPro.h"
#include "ouvrierAouady.h"

#include "Bestouv.h"
#include "animal.h"

int x=1,y=1;  // variable pour chayma aouady radio buttons 
int j,m,a,y2 = 1; // variable  pour chayma boualy tache 2
char idClient[20]; // variable de chayma aouady tache 1 

// variable de hazem ..
//------------------------------
int yH=1;
int z=1;
int choix2[]={0,0,0};
int choix3[]={0,0,0};
//------------------------------


//------------------------<<<< Tache ILyes >>><<<G.Capteur>>>----------------------------------------

GtkTreeIter iter1;
GtkListStore *listf;
capteur cap ;


void toggled_func(GtkCellRendererToggle *cell_renderer,gchar *paths,gpointer user_data) //selection capteur de treeview
{
    GtkTreeIter iter;
    GtkTreePath *path;
    gboolean boolean;
    FILE* f;
    gchar *Numero;
   
   
    path = gtk_tree_path_new_from_string (paths);
    gtk_tree_model_get_iter (GTK_TREE_MODEL (user_data),&iter,path);
    gtk_tree_model_get (GTK_TREE_MODEL (user_data),&iter,SELECTION,&boolean,Eid,&Numero,-1);
    gtk_list_store_set (user_data, &iter,SELECTION, !boolean,-1);
    listf=user_data;
    iter1=iter;
    if (!boolean){
    f=fopen("idtmp.txt","w");
    if(f!=NULL) 
    {
    fprintf(f,"%s \n",Numero);
    fclose(f);}}       
}




void
on_authen_clicked                      (GtkWidget       *button,
                                        gpointer         user_data) ///1 er bouton de login dans  fenetre principale 
{
 GtkWidget *principal , *login ;
 
   principal = lookup_widget(button, "window1") ;
   gtk_widget_hide(principal) ;
   login = lookup_widget(button, "login") ;
   login=create_login();
   gtk_widget_show(login); 
}


void
on_buttonLogin_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)         /// login 
{
GtkWidget *login;
GtkWidget *employe , *admin ;  
GtkWidget *entryuser , *entrypass ;
GtkWidget *label ;

FILE *f ; 
char user[50] ;
char pass[50] ;
char gUser[50];
char gPass[50];
int k =0 ; 
char role ; 
    GdkColor red ;
    gdk_color_parse ("red", &red);

login=lookup_widget(button,"login");

entryuser = lookup_widget(login , "entryUser");
entrypass =lookup_widget(login , "entryPass");
strcpy(gUser,gtk_entry_get_text(GTK_ENTRY(entryuser))) ;
strcpy (gPass ,gtk_entry_get_text(GTK_ENTRY(entrypass))) ;

f = fopen("users.txt","r") ;
if (f!=NULL)
{
  while ((fscanf(f,"%s %s\n",user,pass)!=EOF )&& (!k) ) 
      {
             if ( (strcmp(user,gUser)== 0) && (strcmp(pass,gPass)== 0) )
        	 {
                   k=1;
 		   role = user[0] ; 
                 }
      }
fclose(f);
}
if (k) 
{
 if (role == 'e' )
   {
     employe=lookup_widget(button,"employe");
     employe=create_employe();
     gtk_widget_show(employe); 
     gtk_widget_hide(login);

    }
 else if (role =='a')
     {
      admin=lookup_widget(button,"ADMIN");
     admin=create_ADMIN();
     gtk_widget_show(admin); 
     gtk_widget_hide(login);
      } 

}
else  
     {
      gchar *erreur = "l'identifiant ou le mot de passe est incorrect" ;

      label=lookup_widget(login,"labelLogin");
      gtk_label_set_text (GTK_LABEL(label), _(erreur));
      gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &red);
      }
}


void
on_treeview2_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_buttonRechercheCapteur_clicked      (GtkWidget       *button,
                                        gpointer         user_data)      /// recherche capteurs 
{   
     GtkWidget *entry ;
     GtkWidget *principal;
     GtkWidget *principal1;   
     GtkWidget  *treeview ; 
     char rech[50] ;

     entry=lookup_widget(button,"entryRechercheCapteur");
     strcpy(rech,gtk_entry_get_text(GTK_ENTRY(entry)));
     recher( rech ) ;    
     
   principal=lookup_widget(button,"windowGestion_Capteur");
   principal = create_windowGestion_Capteur();
   gtk_widget_show (principal);
    principal1=lookup_widget(button,"windowGestion_Capteur");
     gtk_widget_destroy(principal1);
       gtk_widget_show (principal);
  treeview=lookup_widget(principal,"treeviewCap");
  afficher_cap(treeview,"rechecap.txt");
  gtk_widget_destroy(principal1) ;
}


void
on_buttonRefresh_clicked               (GtkWidget       *button,
                                        gpointer         user_data)       //// refresh
{
        GtkWidget *principale ;
	GtkListStore *treeview;


principale = lookup_widget(button,"windowGestion_Capteur");
gtk_widget_hide (principale) ;
principale = create_windowGestion_Capteur();
gtk_widget_show (principale);
treeview=lookup_widget(principale,"treeviewCap");
afficher_cap(treeview,"capteur.txt");

}


void
on_buttonAlerte_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonSupprimerCap_clicked          (GtkWidget       *button,
                                        gpointer         user_data)    /// 1er supprimer capteur 
{
	GtkWidget *message;
	GtkWidget *principal;

	message=lookup_widget(button,"windowConfirmSupp");
	message=create_windowConfirmSupp();
	gtk_widget_show(message);
}


void
on_buttonModifierCap_clicked           (GtkWidget       *button,
                                        gpointer         user_data) /// 1er modifier  capteur clicked 
{
	GtkWidget *formulaire;
GtkWidget *principal;
 GtkWidget *combobox;
 GtkWidget *entry1 ;
 GtkWidget *entry2;
 GtkWidget *entry3;
 GtkSpinButton *spinbutton1;
 GtkSpinButton *spinbutton2;
 GtkWidget *radiobutton1;
 GtkWidget *radiobutton2;
 GtkWidget *radiobutton3;
   GtkWidget *checkbox1 ;
    GtkWidget *checkbox2 ;
    GtkWidget *label ;
    GtkWidget *ajout ;
    FILE *f, *f1;
    capteur c ; 
     GdkColor Green;
     GdkColor darksalmon ;
    gdk_color_parse ("green", &Green);
    gdk_color_parse ("darksalmon", &darksalmon);
 char id[20] ;
 double valmin , valmax;
  
  
  principal=lookup_widget(button,"windowGestion_Capteur");
  

  formulaire=lookup_widget(button,"windowAjouterCap");
  formulaire=create_windowAjouterCap();
    gtk_widget_show(formulaire);
  ajout = lookup_widget(formulaire,"buttonAjoutFinalCap");
 entry1=lookup_widget(formulaire,"entryNumCap");
 combobox=lookup_widget(formulaire,"comboboxTypeCapteur");
 entry2=lookup_widget(formulaire,"entryMarqueCap");
 entry3=lookup_widget(formulaire,"entryPlace");
 spinbutton1=lookup_widget(formulaire,"spinbuttonValMin");
 spinbutton2=lookup_widget(formulaire,"spinbuttonValMax");
 radiobutton1=lookup_widget(formulaire,"radiobutton_etanche");
 radiobutton2=lookup_widget(formulaire,"radiobutton_perm");
 //radiobutton3=lookup_widget(formulaire,"radiobuttonNone");
 checkbox1 =lookup_widget(formulaire,"checkbutton_Inter");
 checkbox2 =lookup_widget(formulaire,"checkbutton_exter");
  f=fopen("idtmp.txt","r");
  fscanf(f,"%s \n",id);  
  fclose(f);
 c= rech_capteur("capteur.txt",id) ; 

  gtk_entry_set_text (GTK_ENTRY (entry1), _(c.id));
  gtk_editable_set_editable(GTK_EDITABLE(entry1), FALSE);
  gtk_widget_modify_text(entry1, GTK_STATE_NORMAL, &Green);
  gtk_widget_modify_base(entry1, GTK_STATE_NORMAL, &darksalmon);
 gtk_widget_set_can_focus(GTK_WIDGET(entry1), FALSE);


  gtk_entry_set_text (GTK_ENTRY (entry2), _(c.marque));
  gtk_entry_set_text (GTK_ENTRY (entry3), _(c.place));
if ( strcmp(c.type,"Temperature")==0 )
  gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),0);
else if ( strcmp(c.type,"Humidite")==0 )
   gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),1);
else if ( strcmp(c.type,"Co2")==0 )
   gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),2);
else if ( strcmp(c.type,"Luminosite")==0 )
   gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),3);
else if ( strcmp(c.type,"Ph")==0 )
   gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),4);
else if ( strcmp(c.type,"Pression")==0 )
   gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),5);
else 
   gtk_combo_box_set_active(GTK_COMBO_BOX (combobox),6);

  valmin =atof(c.valMin) ; 
  valmax = atof(c.valMax) ;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton1),valmin);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2),valmax);
   if(strcmp(c.inOut,"Interieur")==0)
     {gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox1),TRUE);}
   if(strcmp(c.inOut,"Exterieur")==0)
     {gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox2),TRUE);}

  if(strcmp(c.perm,"Permeable")==0)
    {gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2),TRUE);}
   else 
    {gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1),TRUE); }
 
gchar *modif = "Modification du Capteur" ;

  label=lookup_widget(formulaire,"label41");
 gtk_label_set_text (GTK_LABEL(label), _(modif));
  gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &Green);
  gtk_widget_modify_base(label, GTK_STATE_NORMAL, &darksalmon);
 
 gtk_widget_set_sensitive (ajout,FALSE); 


  gtk_widget_hide(principal) ;


}


void
on_buttonAjoutercap_clicked            (GtkWidget       *button,
                                        gpointer         user_data)  /// 1er ajouer  capteur clicked 
{
    GtkWidget *formulaire;
GtkWidget *principal;
GtkWidget *modif;

principal=lookup_widget(button,"windowGestion_Capteur");
gtk_widget_destroy(principal);
formulaire=lookup_widget(button,"windowAjouterCap");
formulaire=create_windowAjouterCap();
gtk_widget_show(formulaire);

modif = lookup_widget(formulaire,"modifFinalCap");
gtk_widget_set_sensitive (modif,FALSE); 
}


void
on_buttonHomeGestCap_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
  
       GtkWidget *dashboard ;
       GtkWidget *Gcap ;
Gcap=lookup_widget(button,"windowGestion_Capteur");
gtk_widget_hide(Gcap);
dashboard=lookup_widget(button,"employe");
dashboard=create_employe();
gtk_widget_show(dashboard);

}


void
on_buttonDeconnexionGcap_clicked       (GtkWidget       *button,
                                        gpointer         user_data)   /// logout from G.cap
{
   GtkWidget *login ;
   GtkWidget *Gcap ;
Gcap=lookup_widget(button,"windowGestion_Capteur");
gtk_widget_destroy(Gcap);
login=lookup_widget(button,"login");
login=create_login();
gtk_widget_show(login);

}


void
on_buttonGclient_clicked               (GtkWidget       *button,
                                        gpointer         user_data) // acceder au g.client from employee dashboard
{
   GtkWidget *dashcboard; 
  GtkWidget *menu ;

  dashcboard=lookup_widget(button,"employe");
  gtk_widget_destroy(dashcboard); 
 menu =  lookup_widget(button,"menu");      
  menu = create_menu ();
  gtk_widget_show (menu);
}


void
on_buttonGTroup_clicked                (GtkWidget       *button,
                                        gpointer         user_data) //acceder au gest troupeaux
{
  GtkWidget *troupo ;
  GtkWidget *treeview ; 
  troupo=lookup_widget(button,"GT_Employe1");
  troupo = create_GT_Employe1() ;
   treeview = lookup_widget(button,"treeviewGT1") ;
  gtk_widget_show(troupo) ;
  afficher_animal(treeview) ;

}


void
on_buttonGcap_clicked                  (GtkWidget       *button,
                                        gpointer         user_data) /// acceder au gestion capteur from employee dashbord 
{
  GtkWidget *Gcap;
GtkWidget *dashcboard; 
GtkWidget *treeview2;



dashcboard=lookup_widget(button,"employe");
gtk_widget_destroy(dashcboard);

Gcap=lookup_widget(button,"windowGestion_Capteur");
Gcap=create_windowGestion_Capteur();
gtk_widget_show(Gcap);
treeview2=lookup_widget(Gcap,"treeviewCap");
afficher_cap(treeview2,"capteur.txt");
}


void
on_buttonGequip_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonGouvr_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_logOutDashboard_clicked             (GtkWidget       *button,
                                        gpointer         user_data)  // logout from employee dashboard
{
   GtkWidget *login ;
   GtkWidget *dashboard ;
dashboard=lookup_widget(button,"employe");
gtk_widget_destroy(dashboard);
login=lookup_widget(button,"login");
login=create_login();
gtk_widget_show(login);
}


void
on_buttonAjoutFinalCap_clicked         (GtkWidget       *button,
                                        gpointer         user_data) /// ajout final capteur 
{
    
     GtkWidget *window ;
 GtkWidget *combobox;
 GtkWidget *entry1 ;
 GtkWidget *entry2;
 GtkWidget *entry3;
 GtkWidget *spinbutton1;
 GtkWidget *spinbutton2;
 GtkWidget *radiobutton1;
 GtkWidget *radiobutton2;
 GtkWidget *radiobutton3;
 GtkWidget *checkbox1 ;
 GtkWidget *checkbox2 ;
 GtkWidget *dialog1;
  GtkWidget *label ;
 capteur c;
 FILE *f;
    GdkColor red ;
    gdk_color_parse ("red", &red);
 int valmin,valmax;
 
 window=lookup_widget(button,"windowAjouterCap");
 entry1=lookup_widget(button,"entryNumCap");
 combobox=lookup_widget(window,"comboboxTypeCapteur");
 entry2=lookup_widget(button,"entryMarqueCap");
 entry3=lookup_widget(button,"entryPlace");
 spinbutton1=lookup_widget(button,"spinbuttonValMin");
 spinbutton2=lookup_widget(button,"spinbuttonValMax");
 radiobutton1=lookup_widget(button,"radiobutton_etanche");
 radiobutton2=lookup_widget(button,"radiobutton_perm");
 radiobutton3=lookup_widget(button,"radiobuttonNone");
 checkbox1 =lookup_widget(button,"checkbutton_Inter");
 checkbox2 =lookup_widget(button,"checkbutton_exter");
 
 strcpy(c.id,gtk_entry_get_text(GTK_ENTRY(entry1)));
 strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(entry2)));
 strcpy(c.place,gtk_entry_get_text(GTK_ENTRY(entry3)));
 strcpy(c.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox)));
 valmin =gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spinbutton1));
 sprintf(c.valMin ,"%d",valmin) ;
 valmax =gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spinbutton2));
 sprintf(c.valMax ,"%d",valmax) ;
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1)))
  {strcpy(c.perm,"Etanche");}
 else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2)))
  {strcpy(c.perm,"Permeable");}

 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox1)))
  {strcpy(c.inOut,"Interieur");}
  else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox2)))
  {strcpy(c.inOut,"Exterieur");}
    else if( (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox2))) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox1))) )
  {strcpy(c.inOut,"Exterieur/interieur");}
  else {strcpy(c.inOut,"None");}
  
 if ( ajout_capteur("capteur.txt",c ) ) 
  {   dialog1 = create_dialogAjoutSucc ();
      gtk_widget_show (dialog1); 
      gtk_entry_set_text (GTK_ENTRY (entry1), _(""));
      gtk_entry_set_text (GTK_ENTRY (entry2), _(""));
      gtk_entry_set_text (GTK_ENTRY (entry3), _("")); 
      gtk_combo_box_set_active(GTK_COMBO_BOX(combobox),-1);
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton1),0);
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2),0);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox2),FALSE);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox1),FALSE);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2),FALSE);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1),FALSE);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton3),TRUE);
}
 else 
 {
   gchar *modif = "Numero de capteur existe deja ! " ;

  label=lookup_widget(window,"label41");
 gtk_label_set_text (GTK_LABEL(label), _(modif));
  gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &red);

  }
    
    
}


void
on_modifFinalCap_clicked               (GtkWidget       *button,
                                        gpointer         user_data) // modifier final capteur
{
   
  GtkWidget *window ;
 GtkWidget *combobox;
 GtkWidget *entry1 ;
 GtkWidget *entry2;
 GtkWidget *entry3;
 GtkWidget *spinbutton1;
 GtkWidget *spinbutton2;
 GtkWidget *radiobutton1;
 GtkWidget *radiobutton2;
 GtkWidget *radiobutton3;
 GtkWidget *checkbox1 ;
 GtkWidget *checkbox2 ;
 GtkWidget *dialog1;
 capteur c;
 FILE *f;
 int valmin,valmax;
 
 window=lookup_widget(button,"windowAjouterCap");
 entry1=lookup_widget(button,"entryNumCap");
 combobox=lookup_widget(window,"comboboxTypeCapteur");
 entry2=lookup_widget(button,"entryMarqueCap");
 entry3=lookup_widget(button,"entryPlace");
 spinbutton1=lookup_widget(button,"spinbuttonValMin");
 spinbutton2=lookup_widget(button,"spinbuttonValMax");
 radiobutton1=lookup_widget(button,"radiobutton_etanche");
 radiobutton2=lookup_widget(button,"radiobutton_perm");
 radiobutton3=lookup_widget(button,"radiobuttonNone");
 checkbox1 =lookup_widget(button,"checkbutton_Inter");
 checkbox2 =lookup_widget(button,"checkbutton_exter");
 
 strcpy(c.id,gtk_entry_get_text(GTK_ENTRY(entry1)));
 strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(entry2)));
 strcpy(c.place,gtk_entry_get_text(GTK_ENTRY(entry3)));
 strcpy(c.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox)));
 valmin =gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spinbutton1));
 sprintf(c.valMin ,"%d",valmin) ;
 valmax =gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spinbutton2));
 sprintf(c.valMax ,"%d",valmax) ;
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1)))
  {strcpy(c.perm,"Etanche");}
 else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2)))
  {strcpy(c.perm,"Permeable");}

 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox1)))
  {strcpy(c.inOut,"Interieur");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox2)))
  {strcpy(c.inOut,"Exterieur");}
    else if( (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox2))) && (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox1))) )
  {strcpy(c.inOut,"Exterieur/interieur");}
  else {strcpy(c.inOut,"None");}
  
 modif_capteur("capteur.txt",c ) ;
      dialog1 = create_dialogAjoutSucc ();
      gtk_widget_show (dialog1); 
     
}


void
on_buttonAnullerAjout_clicked          (GtkWidget       *button,
                                        gpointer         user_data) // annuler ajout capteur
{  
      
       
	GtkWidget *form;
	GtkWidget *princ;
	GtkWidget *treeview;

form=lookup_widget(button,"windowAjouterCap");
gtk_widget_destroy(form);
princ=lookup_widget(button,"windowGestion_Capteur");
princ=create_windowGestion_Capteur();
gtk_widget_show(princ);

  treeview=lookup_widget(princ,"treeviewCap");
  afficher_cap(treeview,"capteur.txt");
}


void
on_closebutton_AjoutSucc_clicked       (GtkWidget       *button,
                                        gpointer         user_data)
{
  GtkWidget *dialog ;
   dialog =lookup_widget(button,"dialogAjoutSucc");
   gtk_widget_destroy (dialog);
}


void
on_buttonValiderSuppCap_clicked        (GtkWidget       *button,
                                        gpointer         user_data)    /// supression final capteur
{
      GtkWidget  *affichage1 , *dialog1;
      GtkWindow *affichage ;
   GtkWidget  *message ;
   GtkListStore *treeview2;
   GtkWidget *liste;



    FILE* f1;
    capteur c ; 
     char id[20] ;
  

f1=fopen("idtmp.txt","r");
  if(f1!=NULL) 
  {
  fscanf(f1,"%s \n",id);
  fclose(f1);}
  remove("idtmp.txt");

  gtk_list_store_set (listf,&iter1,SELECTION, FALSE,-1);
 if ( supp_capteur("capteur.txt", id ))  
{
   message=lookup_widget(button,"windowConfirmSupp");

   treeview2=lookup_widget(button,"treeviewCap");
   afficher_cap(treeview2,"capteur.txt");
   gtk_widget_hide(message);

}
}


void
on_buttonAnnulerSuppCap_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *message;

   message=lookup_widget(button,"windowConfirmSupp");
   gtk_widget_destroy(message);
}


void
on_radio_homme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
     if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{ x = 1;}
}


void
on_radio_femme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{ x = 1;}
}


void
on_button_retour_client_individuel_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"ajout_client_individuel");
	window2 = create_liste_clients_particuliers ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
	GtkWidget *window;
	GtkWidget *treeview;

      treeview = lookup_widget(window2,"treeview_liste_clients_ind");

      afficher_client_ind(treeview);
}


void
on_button_ajouter_client_individuel_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

	clientInd c;	
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *spin1;
	GtkWidget *spin2;
	GtkWidget *spin3;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	GtkWidget *output6;
	GtkWidget *output7;
	char texte[150];
	input1 = lookup_widget(objet_graphique,"entry6");
	input2 = lookup_widget(objet_graphique,"entry1");
	input3 = lookup_widget(objet_graphique,"entry2");
	input4 = lookup_widget(objet_graphique,"entry3");
	input5 = lookup_widget(objet_graphique,"entry4");
	input6 = lookup_widget(objet_graphique,"entry5");


	if (x == 1){
		strcpy(c.sexe,"Homme");
	}
	if(x == 2){
		strcpy(c.sexe,"Femme");
	}
	
	spin1 = lookup_widget(objet_graphique,"spinbutton1");
	spin2 = lookup_widget(objet_graphique,"spinbutton2");
	spin3 = lookup_widget(objet_graphique,"spinbutton3");
	
	c.date_naissance.jour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin1));
        c.date_naissance.mois = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin2));
	c.date_naissance.annee = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin3));

	strcpy(c.cin,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(c.prenom,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(c.adresse,gtk_entry_get_text(GTK_ENTRY(input4)));
	strcpy(c.numTel,gtk_entry_get_text(GTK_ENTRY(input5)));
	strcpy(c.email,gtk_entry_get_text(GTK_ENTRY(input6)));
	

	int test1=1,test2,test3,test4 = 1 , test5 , test6;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if (rechercher_cin(c.cin)==1 || verifyNumber(c.cin)==0)
		{test1=0;}
	output1 = lookup_widget(objet_graphique,"labelStatCin");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	/*-----------------------------------------------------*/
	test2 = verifyName(c.nom);
	output2 = lookup_widget(objet_graphique,"labelStatNom");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"😡");
	}
	/*------------------------------------------------------*/
	test3 = verifyName(c.prenom);
	output3 = lookup_widget(objet_graphique,"labelStatPrenom");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"😡");
	}
	/*-------------------------------------------------------*/ 
	if (strcmp(c.adresse,"")==0){
	test4 =0;
	}
	output4 = lookup_widget(objet_graphique,"labelStatAdresse");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"😡");
	}
	
	test5= verifyNumber(c.numTel);
	output5 = lookup_widget(objet_graphique,"labelStatNum");
	if(test5){
		gtk_label_set_text(GTK_LABEL(output5),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output5),"😡");
	}


	if(test1 && test2 && test3 && test4 && test5){
				
		ajouter_client_ind(c);

		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		sprintf(texte,"Ajout réussi\n");
		output7 = lookup_widget(objet_graphique,"labelStatAjout");

		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output7, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output7),texte);	
		GtkWidget *window1;
		window1 = create_operationReussie ();
		gtk_widget_show(window1);
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output7 = lookup_widget(objet_graphique,"labelStatAjout");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output7, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output7),texte);	
	}
	
}


void
on_treeview_liste_clients_ind_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
  GtkTreeIter Iter;
gchar* cin;
gchar* nom;
gchar* prenom;
gchar* sexe;
gchar* date;
gchar* adresse;
gchar* numTel;
gchar* email;
clientInd p;
GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if(gtk_tree_model_get_iter(model,&Iter,path)){
gtk_tree_model_get(GTK_LIST_STORE(model),&Iter,0,&cin,1,&nom,2,&prenom,3,&sexe,4,&date,5,&adresse,6,&numTel,7,&email,-1);

strcpy(p.cin,cin);

supprimer_client_ind(p.cin);
}
}


void
on_buttonMenu_clicked                  (GtkWidget       *button,
                                        gpointer         user_data)
{
        GtkWidget *window1;
	GtkWidget *window2;
	GtkWidget *window3;
	window1 = lookup_widget(button,"liste_clients_particuliers");
	window3 = lookup_widget(button,"liste_clients_professionnels");
	window2 = create_menu ();

	gtk_widget_destroy(window1);
	gtk_widget_destroy(window3);
	gtk_widget_show(window2);
}


void
on_buttonAfficherPart_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window;
GtkWidget *treeview;
window = lookup_widget(button,"liste_clients_particuliers");
treeview = lookup_widget(window,"treeview_liste_clients_ind");

afficher_client_ind(treeview);
}


void
on_button_supprimer_client_individuel_liste_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data) 
{

	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"liste_clients_particuliers");
	window2 = create_supprimerClientInd ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_button_modifier_client_particuler_liste_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
        GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"liste_clients_particuliers");
	window2 = create_modification_client_particulier ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_button_ajouter_client_particulier_liste_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
        GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"liste_clients_particuliers");
	window2 = create_ajout_client_individuel ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_button_valider_ajout_client_pro_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
       
	clientPro c;	
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;

	input1 = lookup_widget(objet_graphique,"entry7");
	input2 = lookup_widget(objet_graphique,"entry8");
	input3 = lookup_widget(objet_graphique,"entry9");
	input4 = lookup_widget(objet_graphique,"entry10");
	
	output1 = lookup_widget(objet_graphique,"labelStatPNom");
	output2 = lookup_widget(objet_graphique,"labelStatPAdresse");
	output3 = lookup_widget(objet_graphique,"labelStatPNum");
	output4 = lookup_widget(objet_graphique,"labelStatPEmail");

	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(c.adresse,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(c.numTel,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(c.email,gtk_entry_get_text(GTK_ENTRY(input4)));
	char texte[200];
	int test1=1,test2=1,test3,test4=1;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if (rechercher_nom(c.nom)==1 || strcmp(c.nom,"")==0)
		{test1=0;}
	output1 = lookup_widget(objet_graphique,"labelStatPNom");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	/*-----------------------------------------------------*/
	if (strcmp(c.adresse,"")==0)
		{test2=0;}
	output2 = lookup_widget(objet_graphique,"labelStatPAdresse");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"😡");
	}
	/*------------------------------------------------------*/
	test3 = verifyNumber(c.numTel);
	output3 = lookup_widget(objet_graphique,"labelStatPNum");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"😡");
	}
	/*-------------------------------------------------------*/ 
	if (strcmp(c.email,"")==0){
	test4 =0;
	}
	output4 = lookup_widget(objet_graphique,"labelStatPEmail");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"😡");
	}

	if(test1 && test2 && test3 && test4){
				
		ajouter_client_pro(c);

		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		sprintf(texte,"Ajout reussi\n");
		output5 = lookup_widget(objet_graphique,"labelStatPAjout");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output5, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output5),texte);		
		GtkWidget *window1;
		window1 = create_operationReussie ();
		gtk_widget_show(window1);
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output5 = lookup_widget(objet_graphique,"labelStatPAjout");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output5, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output5),texte);	
	}

	
}


void
on_button_retour_ajout_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
        GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"ajouter_client_entreprise_");
	window2 = create_liste_clients_professionnels ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
	GtkWidget *treeview;

treeview = lookup_widget(window2,"treeview_liste_clients_pro");

afficher_client_pro(treeview);
}


void
on_buttonClientsPart_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"menu");
	window2 = create_liste_clients_particuliers ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
	GtkWidget *treeview;

treeview = lookup_widget(window2,"treeview_liste_clients_ind");

afficher_client_ind(treeview);
}


void
on_buttonClientsPro_clicked            (GtkWidget       *button,
                                        gpointer         user_data)
{
        GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"menu");
	window2 = create_liste_clients_professionnels ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
	GtkWidget *treeview;

treeview = lookup_widget(window2,"treeview_liste_clients_pro");

afficher_client_pro(treeview);
}


void
on_buttonOuiAttention_clicked          (GtkWidget       *button,
                                        gpointer         user_data)   
{
	
	GtkWidget *window;
	window = lookup_widget(button,"Attention");
	
	if (rechercher_cin(idClient))
		{supprimer_client_ind(idClient);
		GtkWidget *window1;
		window1 = create_operationReussie ();
		gtk_widget_show(window1);
		gtk_widget_destroy(window);
}
	if (rechercher_nom(idClient))
		{supprimer_client_pro(idClient);
		GtkWidget *window1;
		window1 = create_operationReussie ();
		gtk_widget_show(window1);
		gtk_widget_destroy(window);}
	gtk_widget_destroy(window);
}


void
on_buttonNonAttention_clicked          (GtkWidget       *button,
                                        gpointer         user_data)  
{
	GtkWidget *window;
	window = lookup_widget(button,"Attention");
	gtk_widget_destroy(window);
}


void
on_buttonChercherPro_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
clientPro c;
int r;
char texte[100];
char texte2[100];
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *input4;
GtkWidget *input5;
GtkWidget *status;
	input1 = lookup_widget(button,"entry22");
	input2 = lookup_widget(button,"entry11");
	input3 = lookup_widget(button,"entry12");
	input4 = lookup_widget(button,"entry13");
	input5 = lookup_widget(button,"entry14");
	status = lookup_widget(button,"labelStatusPro");
strcpy(texte,gtk_entry_get_text(GTK_ENTRY(input1)));
r= rechercher_nom(texte);
if (r==0)
{
strcpy(texte2,"Nom non trouvé");
gtk_label_set_text(GTK_LABEL(status),texte2);
} 
else {
	strcpy(texte2,"Nom trouvé. Veuillez taper vos nouveaux données");
	gtk_label_set_text(GTK_LABEL(status),texte2);		
	strcpy(c.adresse,find_client_pro(texte).adresse);
	strcpy(c.numTel,find_client_pro(texte).numTel);
	strcpy(c.email,find_client_pro(texte).email);
	strcpy(c.nom,texte);
	gtk_entry_set_text(GTK_ENTRY(input2),c.nom);
	gtk_entry_set_text(GTK_ENTRY(input3),c.adresse);
	gtk_entry_set_text(GTK_ENTRY(input4),c.numTel);
	gtk_entry_set_text(GTK_ENTRY(input5),c.email);

}
}


void
on_button_retour_modifier_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"modifier_client_entreprise_");
	window2 = create_liste_clients_professionnels ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);

GtkWidget *treeview;

treeview = lookup_widget(window2,"treeview_liste_clients_pro");

afficher_client_pro(treeview);
}


void
on_button_valider_modifier_client_pro_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)  
{
clientPro c;	
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	char texte[200];
	input1 = lookup_widget(objet_graphique,"entry11");
	input2 = lookup_widget(objet_graphique,"entry12");
	input3 = lookup_widget(objet_graphique,"entry13");
	input4 = lookup_widget(objet_graphique,"entry14");
	
	output1 = lookup_widget(objet_graphique,"labelStatPMNom");
	output2 = lookup_widget(objet_graphique,"labelStatPMAdresse");
	output3 = lookup_widget(objet_graphique,"labelStatPMNum");
	output4 = lookup_widget(objet_graphique,"labelStatPMEmail");

	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(c.adresse,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(c.numTel,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(c.email,gtk_entry_get_text(GTK_ENTRY(input4)));
	
	int test1=1,test2=1,test3,test4=1;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if (strcmp(c.nom,"")==0)
		{test1=0;}
	output1 = lookup_widget(objet_graphique,"labelStatPMNom");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	/*-----------------------------------------------------*/
	if (strcmp(c.adresse,"")==0)
		{test2=0;}
	output2 = lookup_widget(objet_graphique,"labelStatPMAdresse");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"😡");
	}
	/*------------------------------------------------------*/
	test3 = verifyNumber(c.numTel);
	output3 = lookup_widget(objet_graphique,"labelStatPMNum");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"😡");
	}
	/*-------------------------------------------------------*/ 
	if (strcmp(c.email,"")==0){
	test4 =0;
	}
	output4 = lookup_widget(objet_graphique,"labelStatPMEmail");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"😡");
	}

	if(test1 && test2 && test3 && test4){
				
		modifier_client_pro(c);
		sprintf(texte,"Modificaton reussie\n");
		output5 = lookup_widget(objet_graphique,"labelStatPModify");

		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output5, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output5),texte);
		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		GtkWidget *window1;
		window1 = create_operationReussie ();
		gtk_widget_show(window1);
		
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output5 = lookup_widget(objet_graphique,"labelStatPModify");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output5, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output5),texte);	
	}
}


void
on_buttonChercherInd_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
clientInd c;
int r;
char texte[100];
char texte2[100];
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *input4;
GtkWidget *input5;
GtkWidget *input6;
GtkWidget *input7;
GtkWidget *spin1;
GtkWidget *spin2;
GtkWidget *spin3;
GtkWidget *radioh;
GtkWidget *radiof;
GtkWidget *status;

	spin1 = lookup_widget(objet_graphique,"spinbutton4");
	spin2 = lookup_widget(objet_graphique,"spinbutton5");
	spin3 = lookup_widget(objet_graphique,"spinbutton6");
	input1 = lookup_widget(objet_graphique,"entry21");
	input2 = lookup_widget(objet_graphique,"entry20");
	input3 = lookup_widget(objet_graphique,"entry15");
	input4 = lookup_widget(objet_graphique,"entry16");
	input5 = lookup_widget(objet_graphique,"entry17");
	input6 = lookup_widget(objet_graphique,"entry18");
	input7 = lookup_widget(objet_graphique,"entry19");
	status = lookup_widget(objet_graphique,"label_status");
strcpy(texte,gtk_entry_get_text(GTK_ENTRY(input1)));
r= rechercher_cin(texte);
if (r==0)
{
strcpy(texte2,"Cin non trouvé");
gtk_label_set_text(GTK_LABEL(status),texte2);
} 
else {
	strcpy(texte2,"Cin trouvé");
	gtk_label_set_text(GTK_LABEL(status),texte2);	
	strcpy(c.cin,find_client_ind(texte).cin);
	strcpy(c.nom,find_client_ind(texte).nom);
	strcpy(c.prenom,find_client_ind(texte).prenom);
	strcpy(c.sexe,find_client_ind(texte).sexe);
	c.date_naissance.jour = find_client_ind(texte).date_naissance.jour;
	c.date_naissance.mois = find_client_ind(texte).date_naissance.mois;
	c.date_naissance.annee = find_client_ind(texte).date_naissance.annee;
	strcpy(c.adresse,find_client_ind(texte).adresse);
	strcpy(c.numTel,find_client_ind(texte).numTel);
	strcpy(c.email,find_client_ind(texte).email);
	gtk_entry_set_text(GTK_ENTRY(input2),c.cin);
	gtk_entry_set_text(GTK_ENTRY(input3),c.nom);
	gtk_entry_set_text(GTK_ENTRY(input4),c.prenom);
	if (y==1)
	{strcpy(c.sexe,"Homme");}
	else
	{strcpy(c.sexe,"Femme");}
	gtk_entry_set_text(GTK_ENTRY(input5),c.adresse);
	gtk_entry_set_text(GTK_ENTRY(input6),c.numTel);
	gtk_entry_set_text(GTK_ENTRY(input7),c.email);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON (spin1),c.date_naissance.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON (spin2),c.date_naissance.mois);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON (spin3),c.date_naissance.annee);

}
}


void
on_radiobuttonHommeModifier_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
   if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{ y = 1;}
}


void
on_radiobuttonFemmeModifier_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	{ y = 2;}
}


void
on_button_retour_modifier_client_particulier_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"modification_client_particulier");
	window2 = create_liste_clients_particuliers ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
	GtkWidget *treeview;

treeview = lookup_widget(window2,"treeview_liste_clients_ind");

afficher_client_ind(treeview);	
}


void
on_button_modifier_client_individuel_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
clientInd c;	
	GtkWidget *input1;
	GtkWidget *input2;
	GtkWidget *input3;
	GtkWidget *input4;
	GtkWidget *input5;
	GtkWidget *input6;
	GtkWidget *output1;
	GtkWidget *output2;
	GtkWidget *output3;
	GtkWidget *output4;
	GtkWidget *output5;
	GtkWidget *output6;
	GtkWidget *output7;
	GtkWidget *spin1;
	GtkWidget *spin2;
	GtkWidget *spin3;

	input1 = lookup_widget(objet_graphique,"entry20");
	input2 = lookup_widget(objet_graphique,"entry15");
	input3 = lookup_widget(objet_graphique,"entry16");
	input4 = lookup_widget(objet_graphique,"entry17");
	input5 = lookup_widget(objet_graphique,"entry18");
	input6 = lookup_widget(objet_graphique,"entry19");

	if (y == 1){
		strcpy(c.sexe,"Homme");
	}
	else
	if(y == 2){
		strcpy(c.sexe,"Femme");
	}
	
	spin1 = lookup_widget(objet_graphique,"spinbutton4");
	spin2 = lookup_widget(objet_graphique,"spinbutton5");
	spin3 = lookup_widget(objet_graphique,"spinbutton6");
	
	c.date_naissance.jour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin1));
        c.date_naissance.mois = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin2));
	c.date_naissance.annee = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin3));

	strcpy(c.cin,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(c.prenom,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(c.adresse,gtk_entry_get_text(GTK_ENTRY(input4)));
	strcpy(c.numTel,gtk_entry_get_text(GTK_ENTRY(input5)));
	strcpy(c.email,gtk_entry_get_text(GTK_ENTRY(input6)));
	
	char texte[200];
	int test1=1,test2,test3,test4 = 1 , test5 , test6=1;
	/*----------- CONTROLE DE SAISIE --------------------*/
	if (verifyNumber(c.cin)==0)
		{test1=0;}
	output1 = lookup_widget(objet_graphique,"labelStatMICin");
	if(test1){
		gtk_label_set_text(GTK_LABEL(output1),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output1),"😡");
	}
	/*-----------------------------------------------------*/
	test2 = verifyName(c.nom);
	output2 = lookup_widget(objet_graphique,"labelStatMINom");
	if(test2){
		gtk_label_set_text(GTK_LABEL(output2),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output2),"😡");
	}
	/*------------------------------------------------------*/
	test3 = verifyName(c.prenom);
	output3 = lookup_widget(objet_graphique,"labelStatMIPrenom");
	if(test3){
		gtk_label_set_text(GTK_LABEL(output3),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output3),"😡");
	}
	/*-------------------------------------------------------*/ 
	if (strcmp(c.adresse,"")==0){
	test4 =0;
	}
	output4 = lookup_widget(objet_graphique,"labelStatMIAdresse");
	if(test4){
		gtk_label_set_text(GTK_LABEL(output4),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output4),"😡");
	}
	
	test5= verifyNumber(c.numTel);
	output5 = lookup_widget(objet_graphique,"labelStatMINum");
	if(test5){
		gtk_label_set_text(GTK_LABEL(output5),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output5),"😡");
	}

	if (strcmp(c.adresse,"")==0){
	test6 =0;
	}
	output6 = lookup_widget(objet_graphique,"labelStatMIEmail");
	if(test6){
		gtk_label_set_text(GTK_LABEL(output6),"😎");
	}
	else{
		gtk_label_set_text(GTK_LABEL(output6),"😡");
	}

	if(test1 && test2 && test3 && test4 && test5 && test6){
				
		modifier_client_ind(c);
		sprintf(texte,"Modification reussie\n");
		output7 = lookup_widget(objet_graphique,"labelStatModifyInd");

		GdkColor color;
		gdk_color_parse ("#00ff00", &color);
		gtk_widget_modify_fg (output7, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output7),texte);	
		/*sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input1),reset);
		gtk_entry_set_text(GTK_ENTRY(input2),reset);
		gtk_entry_set_text(GTK_ENTRY(input3),reset);
		gtk_entry_set_text(GTK_ENTRY(input5),reset);
		gtk_entry_set_text(GTK_ENTRY(input6),reset);
		gtk_combo_box_set_active(input4,0);*/
		GtkWidget *window1;
		window1 = create_operationReussie ();
		gtk_widget_show(window1);
		
	}
	else{
					
		sprintf(texte,"Verifier vos donnée SVP\n");
		output7 = lookup_widget(objet_graphique,"labelStatModifyInd");

		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output7, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output7),texte);	
	}
}


void
on_treeview_liste_clients_pro_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter Iter;
	gchar* nom;
	gchar* adresse;
	gchar* numTel;
	gchar* email;
	clientPro p;
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if(gtk_tree_model_get_iter(model,&Iter,path)){
gtk_tree_model_get(GTK_LIST_STORE(model),&Iter,0,&nom,1,&adresse,2,&email,3,&numTel,-1);

strcpy(p.nom,nom);
strcpy(p.adresse,adresse);
strcpy(p.numTel,numTel);
strcpy(p.email,email);
supprimer_client_pro(p.nom);
}
}


void
on_button_liste_supprimer_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data) 
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"liste_clients_professionnels");
	window2 = create_SupprimerClientPro ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_button_liste_modifier_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{

	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"liste_clients_professionnels");
	window2 = create_modifier_client_entreprise_ ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_button_liste_ajouter_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data)
{
 	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"liste_clients_professionnels");
	window2 = create_ajouter_client_entreprise_ ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_buttonAfficherPro_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window;
GtkWidget *treeview;
window = lookup_widget(button,"liste_clients_professionnels");
treeview = lookup_widget(window,"treeview_liste_clients_pro");

afficher_client_pro(treeview);
}


void
on_buttonOk_clicked                    (GtkWidget       *button,
                                        gpointer         user_data) 
{
       GtkWidget *window;
	window = lookup_widget(button,"operationReussie");
	gtk_widget_destroy(window);
}


void
on_buttonRetourFail_clicked            (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"menu");
	window2 = create_liste_clients_particuliers ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);
}


void
on_buttonAfficher_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget *output;
	GtkWidget *month;
	GtkWidget *year;
	month = lookup_widget(button,"spinGabsenteismeMOIS");
	year  = lookup_widget(button,"spinGabsenteismeANNE");
	int mois,annee;
	mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(month));
	annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(year));
	double result = calcul_taux(mois,annee)*100;
	char texte[200];
	int x = 37;
	sprintf(texte,"Taux pour %d/%d est %.2lf %c",mois,annee,result,x);
	output = lookup_widget(button,"labelTaux");
	gtk_label_set_text(GTK_LABEL(output),texte);
}


void
on_buttonMarquer_clicked               (GtkWidget       *button,
                                        gpointer         user_data) // cette bouton a ete supprimé de projet final 
{

}


void
on_buttonTauxAbsence_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
 GtkWidget *Menu ; 
 Menu = lookup_widget(button,"Menu") ;
 Menu=create_Menu();
 gtk_widget_show(Menu) ;
 
}


void
on_buttonTroupChaqType_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
   GtkWidget *troup ;
   troup = lookup_widget(button , "Nombre_de_troupeaux_de_chaque_type") ;
   troup = create_Nombre_de_troupeaux_de_chaque_type() ;
   gtk_widget_show(troup) ;
}


void
on_button8_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonValAlarm_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{
        GtkWidget *capteur ;
	GtkWidget *treeview ;
	
	GtkWidget *labelMark ;
	GtkWidget *labelmax ;
    capteur =lookup_widget(button ,"window2") ;
    
    capteur = create_window2 () ;
    gtk_widget_show(capteur) ;
     treeview = lookup_widget(capteur,"treeviewValeurAlarm");
    afficher_valAlarm(treeview,"Alarmant.txt");
		
       
 	char resultat[50] ;
 	int num  ;
 	char numm[50] ;

 
  //alarme( 50.0 ,"valeur.txt");  //  erreur de segmentation quand je fait appel au deux fonction alarme ey MaxMarque 




 
    MaxMarques( resultat, &num ) ;
    sprintf(numm ,"%d",num) ;

  labelMark=lookup_widget(capteur,"labelResultatMark");
  gtk_label_set_text (GTK_LABEL(labelMark), _(resultat));
   
  labelmax=lookup_widget(capteur,"labelNombreCapDefec");
  gtk_label_set_text (GTK_LABEL(labelmax), _(numm));

}


void
on_buttonAnneeSeche_clicked            (GtkWidget       *button,
                                        gpointer         user_data)
{
  GtkWidget *seche ;
   seche = lookup_widget(button , "GT_AS") ;
    seche = create_GT_AS() ;
   gtk_widget_show(seche) ;
}


void
on_buttonLogOutAdmin_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
  GtkWidget *window1 ;
  GtkWidget *dash ; 
    dash = lookup_widget(button,"ADMIN");
    window1 = lookup_widget(button , "window1") ;
    gtk_widget_destroy(dash) ;  
    window1 = create_window1() ;
   gtk_widget_show(window1) ; 
}


void
on_buttonDec_GT2_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonMP_GT2_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_radiobuttonMale_GT2_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
{yH=1;}
}


void
on_radiobuttonF_GT2_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
{yH=2;}
}


void
on_checkbuttonVac_GT2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix2[0]=1;} 
}


void
on_checkbuttonMal_GT2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix2[1]=1;}
}


void
on_checkbuttonGes_GT2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix2[2]=1;}
}


void
on_buttonConfirmer_GT2_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
animal a;

GtkWidget *input1;
GtkWidget *input2;
GtkWidget *spin1;
GtkWidget *spin2;
GtkWidget *spin3;
GtkWidget *comboboxentry2;

input1 = lookup_widget(button,"entryId_GT2");
comboboxentry2 = lookup_widget(button,"comboboxentryFam_GT2");
input2=lookup_widget(button,"entryPoids_GT2");
spin1 = lookup_widget(button,"spinbuttonJ_GT2");
spin2 = lookup_widget(button,"spinbuttonM_GT2");
spin3 = lookup_widget(button,"spinbuttonA_GT2");


strcpy(a.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(a.famille,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxentry2)));
if (yH == 1)
{
	strcpy(a.sexe,"Male");
}
if (yH == 2)
{
	strcpy(a.sexe,"Femelle");
}
strcpy(a.poids,gtk_entry_get_text(GTK_ENTRY(input2)));
if (choix2[0]==1)
{
	strcpy(a.sante.vac,"Vac");
}
if (choix2[0]==0)
{
	strcpy(a.sante.vac,"Non_Vac");
}
if (choix2[1]==1)
{
	strcpy(a.sante.malade,"Mal");
}
if (choix2[1]==0)
{
	strcpy(a.sante.malade,"Non_Mal");
}
if (choix2[2]==1)
{
	strcpy(a.sante.gestante,"Ges");
}
if (choix2[2]==0)
{
	strcpy(a.sante.gestante,"Non_Ges");
}
a.date.j = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin1));
a.date.m = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin2));
a.date.a = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin3));

ajouter_animal(a);
}


void
on_buttonAfficher_GT2_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window1;
GtkWidget *window2;
window1 = lookup_widget(button,"GT_Employe2");
window2 = create_GT_Employe1 ();
gtk_widget_destroy(window1);
gtk_widget_show(window2);
}


void
on_treeviewGT1_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter Iter;
gchar *Id;
gchar *Famille;
gchar *Sexe;
gchar *Poids;
gchar *Sante;
gchar *Date;
animal a;
GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if(gtk_tree_model_get_iter(model,&Iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&Iter,0,&Id,1,&Famille,2,&Sexe,3,&Poids,4,&Sante,5,&Date,-1);

strcpy(a.id,Id);

supp_animal(a.id);
}
}


void
on_buttonMP_GT1_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonDec_GT1_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonMAJ_clicked                   (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window;
GtkWidget *treeview;
window   = lookup_widget(button,"GT_Employe1");
treeview = lookup_widget(window,"treeviewGT1");

afficher_animal(treeview);
}


void
on_buttonAjouter_GT1_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window1;
GtkWidget *window2;
window1 = lookup_widget(button,"GT_Employe1");
window2 = create_GT_Employe2 ();
gtk_widget_destroy(window1);
gtk_widget_show(window2);
}


void
on_buttonModifier_GT1_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window1;
GtkWidget *window2;
window1 = lookup_widget(button,"GT_Employe1");
window2 = create_GT_Employe3 ();
gtk_widget_destroy(window1);
gtk_widget_show(window2);
}


void
on_buttonSupp_GT1_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *input;
char ident[50];

input=lookup_widget(button,"entrySupp_GT1");
strcpy(ident,gtk_entry_get_text(GTK_ENTRY(input)));

supp_animal(ident);
}


void
on_buttonDec_AS_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonMP_AS_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonCalculer_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonMP_GT3_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonDec_GT3_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_radiobuttonM_GT3_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
{z=1;}
}


void
on_radiobuttonF_GT3_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
{z=2;}
}


void
on_checkbuttonVac_GT3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix3[0]=1;}
}


void
on_checkbuttonMal_GT3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix3[1]=1;}
}


void
on_checkbuttonGes_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix3[2]=1;}
}


void
on_buttonConfirmer_GT3_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
animal a;

GtkWidget *input1;
GtkWidget *input2;
GtkWidget *spin1;
GtkWidget *spin2;
GtkWidget *spin3;
GtkWidget *comboboxentry3;

input1 = lookup_widget(button,"entryId_GT3");
comboboxentry3 = lookup_widget(button,"comboboxentryFam_GT3");
input2=lookup_widget(button,"entryPoids_GT3");
spin1 = lookup_widget(button,"spinbuttonJ_GT3");
spin2 = lookup_widget(button,"spinbuttonM_GT3");
spin3 = lookup_widget(button,"spinbuttonA_GT3");


strcpy(a.id,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(a.famille,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxentry3)));
if (z == 1)
{
	strcpy(a.sexe,"Male");
}
if (z == 2)
{
	strcpy(a.sexe,"Femelle");
}
strcpy(a.poids,gtk_entry_get_text(GTK_ENTRY(input2)));
if (choix3[0]==1)
{
	strcpy(a.sante.vac,"Vac");
}
if (choix3[0]==0)
{
	strcpy(a.sante.vac,"Non_Vac");
}
if (choix3[1]==1)
{
	strcpy(a.sante.malade,"Mal");
}
if (choix3[1]==0)
{
	strcpy(a.sante.malade,"Non_Mal");
}
if (choix3[2]==1)
{
	strcpy(a.sante.gestante,"Ges");
}
if (choix3[2]==0)
{
	strcpy(a.sante.gestante,"Non_Ges");
}
a.date.j = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin1));
a.date.m = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin2));
a.date.a = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (spin3));

modif_animal(a);
}


void
on_buttonAfficher_GT3_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *window1;
GtkWidget *window2;
window1 = lookup_widget(button,"GT_Employe3");
window2 = create_GT_Employe1 ();
gtk_widget_destroy(window1);
gtk_widget_show(window2);
}


void
on_buttonSMS_clicked                   (GtkWidget       *button,
                                        gpointer         user_data)  /// envoyer SMS , -ilyes- 
{
 GtkWidget *dialog1;
 GtkWidget *windowsms ;
  GtkWidget *sms ;
  char account_sid[100] = "AC07c8406b20bba8d3f301231efca624e9" ;
  char auth_token[100] = "8ccd1958761ed70ac93d5680da63f519" ;
  char message[500]  ;
  char from_number[100] = "+14016842165";
  char to_number[100]="+21655249653" ;
  char picture_url[50] = "http://tny.im/nBw" ;
  int verbose =1 ;
  
  windowsms=lookup_widget(button,"windowSMS");
  sms =lookup_widget(windowsms , "entryMessageSMS");
  strcpy(message,gtk_entry_get_text(GTK_ENTRY(sms))) ;



  /* if ( twilio_send_message(account_sid,
                        auth_token,
                        message,
                        from_number,
                        to_number,
                        picture_url,
                        verbose)     ) 

    { dialog1 = create_dialogAjoutSucc ();
      gtk_widget_show (dialog1);  }        */

}


void
on_buttonRetourCapAdmin_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_buttonLogOutCapAdmin_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *login ;
   GtkWidget *statCap ;
statCap=lookup_widget(button,"window2");
gtk_widget_destroy(statCap);
login=lookup_widget(button,"login");
login=create_login();
gtk_widget_show(login);

}


void
on_buttonOuvrierAnnee_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
     GtkWidget *ouv ; 
    ouv = lookup_widget(button,"Ouvrier_de_lannee") ;
     ouv=create_Ouvrier_de_lannee();
     gtk_widget_show(ouv) ;
}


void
on_buttonEnvoyerSMS_ADMIN_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *sms ; 
 sms = lookup_widget(button,"windowSMS") ;
 sms=create_windowSMS();
 gtk_widget_show(sms) ;
}


void
on_buttonSupprimerInd_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *input;
	GtkWidget *output;
	char id[20];
	char texte[100];

	input = lookup_widget(button,"entry23");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input)));
	
	if(rechercher_cin(id)){
		strcpy(idClient,id);	
		/*sprintf(texte,"Votre suppression à été effectué avec succés\n");
		output = lookup_widget(objet_graphique,"output_del");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);*/
		GtkWidget *attention;
		attention = create_Attention ();
		gtk_widget_show(attention);
		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input),reset);
		
	}
	else{
		sprintf(texte,"CIN NON EXISTANT\n");
		output = lookup_widget(button,"SupprimerStatus");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}

}


void
on_buttonSupprimerPro_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *input;
	GtkWidget *output;
	char id[20];
	char texte[100];

	input = lookup_widget(button,"entry24");
	strcpy(id,gtk_entry_get_text(GTK_ENTRY(input)));
	
	if(rechercher_nom(id)){
		strcpy(idClient,id);	
		/*sprintf(texte,"Votre suppression à été effectué avec succés\n");
		output = lookup_widget(objet_graphique,"output_del");
		GdkColor color;
		gdk_color_parse ("#40e61a", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);*/
		GtkWidget *attention;
		attention = create_Attention ();
		gtk_widget_show(attention);
		char reset[20];
		sprintf(reset,"");
		gtk_entry_set_text(GTK_ENTRY(input),reset);
		
	}
	else{
		sprintf(texte,"CIN NON EXISTANT\n");
		output = lookup_widget(button,"SupprimerStatus");
		GdkColor color;
		gdk_color_parse ("#ff250d", &color);
		gtk_widget_modify_fg (output, GTK_STATE_NORMAL, &color);
    		gtk_label_set_text(GTK_LABEL(output),texte);	
	}

}


void
on_buttonRetourSupprimerInd_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"supprimerClientInd");
	window2 = create_liste_clients_particuliers ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);

	GtkWidget *treeview;

	treeview = lookup_widget(window2,"treeview_liste_clients_ind");

afficher_client_ind(treeview);
}


void
on_buttonRetourSupprimerPro_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *window1;
	GtkWidget *window2;
	window1 = lookup_widget(button,"SupprimerClientPro");
	window2 = create_liste_clients_professionnels ();
	gtk_widget_destroy(window1);
	gtk_widget_show(window2);

GtkWidget *treeview;

treeview = lookup_widget(window2,"treeview_liste_clients_pro");

afficher_client_pro(treeview);
}


void
on_actualiser_la_page_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
        /* GtkWidget *treeview;
         GtkWidget  *listeTroup;
         GtkWidget  *listeTroup1;

	listeTroup=lookup_widget(button, "liste_des_troupeaux");
	listeTroup1=lookup_widget(button, "liste_des_troupeaux");
	treeview = lookup_widget(listeTroup1, "treeview_nbr_de_troupeaux_de_chaque_types");
	listeTroup1= create_liste_des_troupeaux();
	gtk_widget_show(listeTroup1);
	gtk_widget_destroy(listeTroup);
	afficher_nbrtroup(treeview);*/
	
	
}


void
on_buttonactualiser_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
		GtkWidget *bestouv1;
		GtkWidget *bestouv;
		GtkWidget *treeview;
		
                bestouv=lookup_widget(button, "bestouv");
		bestouv1=lookup_widget(button, "bestouv");
		treeview = lookup_widget(bestouv,"treeviewbestouv");
		bestouv1 = create_bestouv();
		gtk_widget_show(bestouv1);//on affiche la prochaine fenêtre
		gtk_widget_destroy(bestouv);//on ferme la première fenêtre
		afficher_bestouv(treeview);
}


void
on_treeview_nbr_de_troupeaux_de_chaque_types_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gchar* id;
	gchar* famille;
	gchar* sexe;
	gchar* poids;
	animal a;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		//obtention des valeurs de la ligne selectionnée
		gtk_tree_model_get (GTK_LIST_STORE (model) , &iter, 0, &id, 1, &famille, 2, &sexe, 3,  &poids,4, -1);	
		strcpy(a.id,id);
		strcpy(a.famille,famille);
		strcpy(a.sexe,sexe);
		strcpy(a.poids,poids);
		//mise à jour de l'affichage de la treeview
		//afficher_nbrtroup(treeview);
	}
}


void
on_treeviewbestouv_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gchar* Nom;
	gchar* Prenom;
	gchar* Date_de_naissance;
	gchar* adresse_mail;
	gchar* CIN;
	gchar* Numero_de_tel;
	ouvrier o;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);

	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		//obtention des valeurs de la ligne selectionnée
		gtk_tree_model_get (GTK_LIST_STORE (model) , &iter, 0, &Nom, 1, &Prenom, 2, &Date_de_naissance, 3,  &adresse_mail,4, &CIN,5, &Numero_de_tel ,6, -1);	
		strcpy(o.Nom,Nom);
		strcpy(o.Prenom,Prenom);
		strcpy(o.Date_de_naissance,Date_de_naissance);
		strcpy(o.adresse_mail,adresse_mail);
		strcpy(o.CIN,CIN);
		strcpy(o.Numero_de_tel,Numero_de_tel);
		//mise à jour de l'affichage de la treeview
		afficher_bestouv(treeview);
	}
}


void
on_Afficher_le_nombre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

	 GtkWidget *treeview;
         GtkWidget  *listeTroup;
	GtkWidget *page ;
	page = lookup_widget(button, "Nombre_de_troupeaux_de_chaque_type");
	listeTroup=lookup_widget(button, "liste_des_troupeaux");
	treeview = lookup_widget(button, "treeview_nbr_de_troupeaux_de_chaque_types");


	listeTroup=create_liste_des_troupeaux();
	gtk_widget_show(listeTroup);
	gtk_widget_destroy(page);
	//afficher_nbrtroup(treeview);
}


void
on_buttonAFFICHERLOUVDELANNEE_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
		GtkWidget *Ouvr;
		GtkWidget *bestouv;
		GtkWidget *treeview ;

                Ouvr=lookup_widget(button, "Ouvrier_de_lannee");
		bestouv = create_bestouv();
		treeview = lookup_widget(bestouv,"treeviewbestouv");
		gtk_widget_show(bestouv);//on affiche la prochaine fenêtre
		gtk_widget_destroy(Ouvr);//on ferme la première fenêtre
		afficher_bestouv(treeview);

}


void
on_dashEmplGclient_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    
       GtkWidget *dashboard ;
       GtkWidget *Gclient ;
	Gclient=lookup_widget(button,"liste_clients_particuliers");
	gtk_widget_hide(Gclient);
	dashboard=lookup_widget(button,"employe");
	dashboard=create_employe();
	gtk_widget_show(dashboard);
}


void
on_dashEmplGclientMenu_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

       GtkWidget *dashboard ;
       GtkWidget *menu ;
	menu=lookup_widget(button,"menu");
	gtk_widget_hide(menu);
	dashboard=lookup_widget(button,"employe");
	dashboard=create_employe();
	gtk_widget_show(dashboard);
}


void
on_dashEmplGclientPro_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
 	GtkWidget *dashboard ;
        GtkWidget *menu ;
	menu=lookup_widget(button,"liste clients professionnels");
	gtk_widget_hide(menu);
	dashboard=lookup_widget(button,"employe");
	dashboard=create_employe();
	gtk_widget_show(dashboard);
}


void
on_buttonRech_GT3_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
animal a;
int r;
char texte[100];
char texte2[100];
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *spin1;
GtkWidget *spin2;
GtkWidget *spin3;
GtkWidget *comboboxentry3;
GtkWidget *status;

input3 = lookup_widget(button,"entryRech_GT3");
input1 = lookup_widget(button,"entryId_GT3");
comboboxentry3 = lookup_widget(button,"comboboxentryFam_GT3");
input2 = lookup_widget(button,"entryPoids_GT3");
spin1 = lookup_widget(button,"spinbuttonJ_GT3");
spin2 = lookup_widget(button,"spinbuttonM_GT3");
spin3 = lookup_widget(button,"spinbuttonA_GT3");
status = lookup_widget(button,"labelFind_GT3");

strcpy(texte,gtk_entry_get_text(GTK_ENTRY(input3)));
r= rechercher_animal(texte);
if (r==0)
{
	strcpy(texte2,"Id non trouvé");
	gtk_label_set_text(GTK_LABEL(status),texte2);
} 
else 
{
	strcpy(texte2,"Id trouvé");
	gtk_label_set_text(GTK_LABEL(status),texte2);

	strcpy(a.id,find_animal(texte).id);
	strcpy(a.famille,find_animal(texte).famille);
	strcpy(a.poids,find_animal(texte).poids);
	strcpy(a.sexe,find_animal(texte).sexe);
	a.date.j = find_animal(texte).date.j;
	a.date.m = find_animal(texte).date.m;
	a.date.a = find_animal(texte).date.a;

	gtk_entry_set_text(GTK_ENTRY(input1),a.id);
	gtk_entry_set_text(GTK_ENTRY(input2),a.poids);
	if (z == 1)
	{
		strcpy(a.sexe,"Male");
	}
	if (z == 2)
	{
		strcpy(a.sexe,"Femelle");
	}
	if (choix3[0]==1)
	{
		strcpy(a.sante.vac,"Vac");
	}
	if (choix3[0]==0)
	{
		strcpy(a.sante.vac,"Non_Vac");
	}
	if (choix3[1]==1)
	{
		strcpy(a.sante.malade,"Mal");
	}
	if (choix3[1]==0)
	{
		strcpy(a.sante.malade,"Non_Mal");
	}
	if (choix3[2]==1)
	{
		strcpy(a.sante.gestante,"Ges");
	}
	if (choix3[2]==0)
	{
		strcpy(a.sante.gestante,"Non_Ges");
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON (spin1),a.date.j);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON (spin2),a.date.m);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON (spin3),a.date.a);	
}
}


void
on_buttonDec_GTA_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affichage, *output1, *output2, *output3, *output4;
int v,m,c,p;

v=nb_vache();
m=nb_mouton();
c=nb_cheval();
p=nb_poule();

char Vache[100];
char Mouton[100];
char Cheval[100];
char Poulet[100];

sprintf(Vache, "%d", v);
sprintf(Mouton, "%d", m);
sprintf(Cheval, "%d", c);
sprintf(Poulet, "%d", p);

output1 = lookup_widget(button,"labelNbV");
gtk_label_set_text(GTK_LABEL(output1),Vache);

output2 = lookup_widget(button,"labelNbM");
gtk_label_set_text(GTK_LABEL(output2),Mouton);

output3 = lookup_widget(button,"labelNbC");
gtk_label_set_text(GTK_LABEL(output3),Cheval);

output4 = lookup_widget(button,"labelNbP");
gtk_label_set_text(GTK_LABEL(output4),Poulet);
}


void
on_buttonMP_GTA_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonCalculer_GTA_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonCalculer_AS_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affichage, *output5;
int as;

as=annee_seche();

char seche[100];

sprintf(seche, "%d", as);

output5 = lookup_widget(button,"labelAS2");
gtk_label_set_text(GTK_LABEL(output5),seche);
}

