#include <gtk/gtk.h>


enum
{
	SELECTION,
        Eid,
  	Etype,
  	Emarque,
  	Eplace,
  	EvalMin,
  	EvalMax,
  	EinOut,
	Eperm,
	COLUMNS ,
};
enum 
{
  IMAGE ,
  Enum ,
  ETYPE ,
  Emplace,
  Eval,
  Columns,
} ;

typedef struct capteur
{
  char id[50]  ;
  char type[50]  ;
  char marque[50] ;
  char place[50] ;
  char valMin[50]  ;
  char valMax[50] ;
  char inOut[50];
  char perm[50] ;
 }capteur ;

//---------------------------
capteur rech_capteur(char *fi,char idRech[] );
//--------------------------------
int ajout_capteur(char *fi, capteur c ) ;
//-------------------------------------
int supp_capteur(char *fi, char *id );
//------------------------------------
void modif_capteur (char *fi , capteur k  ) ;
//-------------------------------------------
void afficher_cap(GtkWidget *liste,char file[]);
//-----------------------------------------------
 void recher(char rech[] )  ;
//-----------------------------------------
void afficher_valAlarm(GtkWidget *liste ,char file[]) ;
//------------------------------------------------------------
void alarme( float rate , char value[] ) ;
//-----------------------------------------------------------------
int rechercheMot( char mat [][50],int n, char mot[]) ;
//---------------------------------------------------------------------
void MaxMarques(char resultat[] , int *max ) ; 
//----------------------------------------------------------------------












