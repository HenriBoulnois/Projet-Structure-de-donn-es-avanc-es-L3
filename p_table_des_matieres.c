#include "p_table_des_matieres.h"
#include "../utilitaires/p_utilitaires.h"
#include <string.h>


/**
 * Cette fonction alloue une entree de tableau des matières
 * On fournit en paramètre un pointeur vers le pere et un pointeur vers le frere qui précédera immédiatement la nouvelle entrée.
 * l'adresse de la nouvelle entrée est retournée
 * @param etiquette : char* : une chaine de caractère qui est recopiée dans l'entrée
 * @param pere : a_entree : le pointeur vers le père (si la nouvelle entrée n'a pas de père alors ce paramètre vaut NULL)
 * @param gd_frere : a_entree : le pointeur vers le frère qui précédent (si la nouvelle entrée n'a pas de père alors ce paramètre vaut NULL)
 * @warning : On pourra supposer que le pere du grand frere et le même que le paramètre père.
 * 
 */

FILE* fichier;
int TAILLE_MAX = 50;
char buffer[50];
char test[50];
char lettretest;

t_entree* nouvelle_entree(char* etiquette, a_entree pere, a_entree gd_frere) {
    a_entree n_entree = (a_entree)malloc(sizeof(t_entree));
    n_entree->l_etiquette = etiquette;
    n_entree->le_premier_fils = NULL;
    n_entree->le_dernier_fils = NULL;
    n_entree->le_pere = pere;
    n_entree->le_frere_precedent = gd_frere;
    n_entree->le_frere_suivant = NULL;
    return n_entree;
}

void afficher_entree(a_entree ceci) {
    printf("%s\n",ceci->l_etiquette);
}

void afficher_table(t_table ceci, int decalage) {
    if(ceci!=TABLE_VIDE) {
        afficher_n_espaces(2*decalage);
        afficher_entree(ceci);
        afficher_table(ceci->le_premier_fils,decalage+1);
        afficher_table(ceci->le_frere_suivant, decalage);
    }
}

void creer_aine(t_table ceci, char* etiquette) {
    a_entree n_entree = (a_entree)malloc(sizeof(t_entree));
    n_entree->l_etiquette = etiquette;
    n_entree->le_pere = ceci;
    n_entree->le_frere_suivant = ceci->le_premier_fils;
    ceci->le_premier_fils = n_entree;
    if(ceci->le_dernier_fils==NULL) {
        ceci->le_dernier_fils = ceci->le_premier_fils;
    }
}

void creer_benjamin(a_entree ceci, char* etiquette) {
    a_entree n_entree = (a_entree)malloc(sizeof(t_entree));
    n_entree->l_etiquette = etiquette;
    n_entree->le_pere = ceci;
    n_entree->le_frere_precedent = ceci->le_dernier_fils;
    ceci->le_dernier_fils = n_entree;
    if(ceci->le_premier_fils!=NULL) {
        ceci->le_dernier_fils->le_frere_precedent->le_frere_suivant = ceci->le_dernier_fils;
    } else {
        ceci->le_premier_fils = ceci->le_dernier_fils;
    }
}

void creer_petit_frere(a_entree ceci, char* etiquette) {
    a_entree n_entree = (a_entree)malloc(sizeof(t_entree));
    n_entree->l_etiquette = etiquette;
    n_entree->le_frere_precedent = ceci;
    n_entree->le_frere_suivant = ceci->le_frere_suivant;
    ceci->le_frere_suivant = n_entree;
}

void inserer_grand_frere(t_table* ceci, char* etiquette) {
    a_entree n_entree = (a_entree)malloc(sizeof(t_entree));
    n_entree->l_etiquette = etiquette;
    n_entree->le_frere_suivant = (*ceci);
    n_entree->le_frere_precedent = (*ceci)->le_frere_precedent;
    (*ceci)->le_frere_precedent = n_entree;
    *ceci = n_entree;
}

int remonter(a_entree ceci) {
    if(ceci->le_pere!=NULL) {
        ceci->le_frere_suivant = ceci->le_pere->le_frere_suivant;
        ceci->le_frere_precedent->le_frere_suivant = NULL;
        ceci->le_pere->le_frere_suivant = ceci;
        return 1;
    }
    return 0;
}

int descendre(a_entree ceci) {
    if(ceci->le_frere_precedent!=NULL) {
        ceci->le_frere_precedent->le_premier_fils = ceci;
        ceci->le_pere = ceci->le_frere_precedent;
        ceci->le_pere->le_frere_suivant = ceci->le_frere_suivant;
        ceci->le_frere_precedent = NULL;
        ceci->le_frere_suivant = ceci->le_premier_fils;
        ceci->le_premier_fils = NULL;
    }
    return 0;
}

void supprimer_entree(a_entree* ceci) {
    if((*ceci)->le_premier_fils!=NULL) {
        (*ceci)->le_premier_fils->le_dernier_fils->le_frere_precedent->le_frere_suivant = (*ceci)->le_premier_fils->le_dernier_fils;
        (*ceci)->le_premier_fils->le_dernier_fils = (*ceci)->le_frere_suivant;
        (*ceci) = (*ceci)->le_premier_fils;
    } else {
        *ceci = (*ceci)->le_frere_suivant;
    }
}

void detruire_table(t_table* ceci) {
    free(*ceci);
    *ceci = TABLE_VIDE;
}

void ecriture_entree(a_entree ceci,char* lettre) {
    fprintf(fichier,"%s",lettre);
    fprintf(fichier,"%s\n",ceci->l_etiquette);
}

void ecriture_table(t_table ceci,char* lettre) {
    if(ceci!=TABLE_VIDE) {
        ecriture_entree(ceci,lettre);
        if(ceci->le_premier_fils!=TABLE_VIDE) {
            ecriture_table(ceci->le_premier_fils,"E\n");
        }
        if(ceci->le_frere_suivant!=TABLE_VIDE) {
            ecriture_table(ceci->le_frere_suivant,"F\n");
        }
    }
}

void sauver_table(t_table ceci, FILE* dans) {
    fichier = dans;
    char* lettre = "P\n";
    ecriture_table(ceci,lettre);
    fprintf(dans,"R\n");
    fprintf(dans,"R");
}

void amorcer(FILE* fichier) {
    fichier = fichier;
}

//La fonction lit le fichier 2 lignes à la fois afin de récuperer la valeur qui est stockée dans le buffer et la lettre qui est stockée dans lettretest
void passer() {
    for(int i = 0; i < 2; i++) {
        fgets(test,TAILLE_MAX,fichier);
        if(i==0) {
            lettretest = test[0];
        }
    }
    memcpy(buffer, test, strlen(test)-1);
}

//Fonction qui permet de creer une table, elle analyse la lettre donnée par le buffer
void creer_table(t_table* ceci) {
    passer();
    if(lettretest=='P') {
        //printf("La table va être créée\n");
        char* tmp = (char*)malloc(strlen(test)-1);
        memcpy(tmp,buffer,strlen(test)-1);
        *ceci = nouvelle_entree(tmp,NULL,NULL);
        //printf("etiquette base : %s\n",(*ceci)->l_etiquette);
        creer_table(ceci);
    }
    if(lettretest=='E') {
        //printf("c'est un enfant\n");
        char* tmp = (char*)malloc(strlen(test)-1);
        memcpy(tmp,buffer,strlen(test)-1);
        creer_aine(*ceci,tmp);
        //printf("etiquette fils : %s\n",(*ceci)->le_premier_fils->l_etiquette);
        creer_table(ceci);
    }
    if(lettretest=='F') {
        //printf("c'est un frere\n");
        char* tmp = (char*)malloc(strlen(test)-1);
        memcpy(tmp,buffer,strlen(test)-1);
        creer_petit_frere(*ceci,tmp);
        (*ceci)->le_frere_suivant->l_etiquette = tmp;
        //printf("etiquette frere : %s\n",(*ceci)->le_frere_suivant->l_etiquette);
        *ceci = (*ceci)->le_frere_suivant;
        creer_table(ceci);
    }
    if(lettretest=='R') {
        //printf("C'est la fin, enfin...\n");
    }
}


//Fonction permettant de trouver la base de la structure pour ensuite pouvoir l'afficher correctement
void trouver_la_base(t_table* ceci) {
    if((*ceci)->le_frere_precedent!=NULL) {
        *ceci = (*ceci)->le_frere_precedent;
        trouver_la_base(ceci);
    } else if((*ceci)->le_pere!=NULL) {
        *ceci = (*ceci)->le_pere;
        trouver_la_base(ceci);
    }   
}

void charger_table(t_table* ceci, FILE* depuis) {
    amorcer(depuis);
    creer_table(ceci);
    trouver_la_base(ceci);
}








