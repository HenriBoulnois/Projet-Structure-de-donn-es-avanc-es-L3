#include <stdio.h>
#include "p_table_des_matieres.h"

int main(int argc, char** argv){

    t_table ma_table = nouvelle_entree("1", TABLE_VIDE, TABLE_VIDE);
    t_table ma_table_2;
    printf("1er affichage\n");
    afficher_entree(ma_table);
    creer_aine(ma_table, "1.2");
    creer_aine(ma_table, "1.1");
    creer_benjamin(ma_table, "1.3");
    creer_aine(ma_table, "1.0");
    printf("2eme affichage\n");
    afficher_table(ma_table, 0);
    creer_benjamin(ma_table->le_premier_fils, "1.0.0");
    creer_benjamin(ma_table->le_dernier_fils, "1.3.0");
    printf("3eme affichage\n");
    afficher_table(ma_table, 0);
    creer_petit_frere(ma_table,"3");
    creer_petit_frere(ma_table,"2");
    inserer_grand_frere(&ma_table,"0");
    //printf(ma_table->le_frere_precedent->l_etiquette);
    printf("4eme affichage\n");
    afficher_table(ma_table, 0);
    remonter(ma_table->le_frere_suivant->le_premier_fils->le_frere_suivant->le_frere_suivant->le_frere_suivant);
    /** decaler_sur_partie(ma_table->le_frere_suivant->le_premier_fils->le_frere_suivant);**/
    /** remonter 1.3 **/
    printf("5eme affichage\n");
    afficher_table(ma_table, 0);
    descendre(ma_table->le_frere_suivant);
    /** descendre 1 **/
    printf("6eme affichage\n");
    afficher_table(ma_table, 0);
    supprimer_entree(&ma_table);
    printf("7eme affichage\n");
    afficher_table(ma_table, 0);
    supprimer_entree(&ma_table);
    printf("8eme affichage\n");
    afficher_table(ma_table, 0);

    printf("************** SAVE\n");

    afficher_table(ma_table, 0);
    FILE* mon_fichier = fopen("toto.sav", "w");
    sauver_table(ma_table, mon_fichier);
    fclose(mon_fichier);

    printf("************** LOAD \n");
    
    mon_fichier = fopen("toto.sav", "r");
    charger_table(&ma_table_2, mon_fichier);
    fclose(mon_fichier);
    afficher_table(ma_table_2, 0);
 
    detruire_table(&ma_table);
    afficher_table(ma_table, 0);
    return 0;
}