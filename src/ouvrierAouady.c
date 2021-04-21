#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ouvrierAouady.h"

double calcul_taux(int m,int a);
void ajout_presence(char cin[],int j,int m,int a,int e);


double calcul_taux(int m,int a){
    FILE *f;
    double nbre_seance = 0;
    double nbre_absence = 0;
    char id[20];
    int jj,aa,mm,res;
    double result;
    f = fopen("absenteisme.txt","r");
    if(f != NULL){
        while(fscanf(f,"%s %d %d %d %d\n",id,&jj,&mm,&aa,&res) != EOF){
            if(mm == m && aa == a){
                nbre_seance ++;
                if(res == 0){
                    nbre_absence ++;
                }
            }
        }
    }
    fclose(f);
    printf("nbre de ligne : [%lf]\n",nbre_seance);
    printf("nbre d'absence: [%lf]\n",nbre_absence);
    return (nbre_absence/nbre_seance);
}
void ajout_presence(char cin[],int j,int m,int a,int e){
    FILE *f,*g;
    char id[20];
    int jj,aa,mm,pres,test = 0;
    f = fopen("absenteisme.txt","r");
    g = fopen("temp.txt","a");
    if(f != NULL){
        while(fscanf(f,"%s %d %d %d %d\n",id,&jj,&mm,&aa,&pres) != EOF){
            if((strcmp(cin,id) == 0) && (jj == j) && (m = mm) && (aa == a)){
                fprintf(g,"%s %d %d %d %d\n",cin,j,m,a,e);
                test = 1;
            }
            else{
                fprintf(g,"%s %d %d %d %d\n",id,jj,mm,aa,pres);
            }
        }
        if(test == 0){
            fprintf(g,"%s %d %d %d %d\n",cin,j,m,a,e);
        }
        
    }
    fclose(f);
    fclose(g);
    remove("absenteisme.txt");
    rename("temp.txt","absenteisme.txt");
}



//////////////////////////////////////////////////////////////////////////////////////////////////




