#ifndef P_TABLE_DES_MATIERES_H
#define P_TABLE_DES_MATIERES_H 

#include <stdio.h>
#include <stdlib.h>

#define TABLE_VIDE NULL

typedef struct s_entree{
    char* l_etiquette;
    struct s_entree* le_premier_fils;
    struct s_entree* le_dernier_fils;
    struct s_entree* le_frere_precedent;
    struct s_entree* le_frere_suivant;
    struct s_entree* le_pere;
}t_entree;

typedef t_entree* a_entree;
typedef a_entree t_table;

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
t_entree* nouvelle_entree(char* etiquette, a_entree pere, a_entree gd_frere);

/**
 * Pour vous inciter à écrire des fonctions de débugages.
 * Cette fonction affiche le contenu de *ceci.
 */
void afficher_entree(a_entree ceci);

/**
 * Affiche la table comme une table des matières.
 */
void afficher_table(t_table ceci, int decalage);

/**
 * Ajouter à la table <ceci> une entrée en position de fils ainé.
 */
void creer_aine(t_table ceci, char* etiquette);

/**
 * Ajouter à la table <ceci> une entrée en position de dernier fils.
 */
void creer_benjamin(a_entree ceci, char* etiquette);

/**
 * Ajouter une entrée en position juste après ceci dans la fratrie.
 */
void creer_petit_frere(a_entree ceci, char* etiquette);

/**
 * Ajouter une entrée en position juste avant *ceci dans la fratrie.
 * @warning *ceci change pour prendre comme valeur l'adresse de la nouvelle entrée.
 */
void inserer_grand_frere(t_table* ceci, char* etiquette);

/**
 * Change le status de <ceci> dans la table.
 * <ceci> prend la place du cadet de son frère.
 * L'ancien cadet du père devient par conséquent le cadet du <ceci>.
 * @warning : <ceci> ne peut pas remonter si il n'a pas de père (i.e. ceci est un titre de niveau maximal dans la table)
 * Dans ce cas la fonction retourne 0 et ne fait rien.
 * Dans les autres cas la fonction retourne 1.
 */
int remonter(a_entree ceci);

/**
 * Change le status de <ceci> dans la table.
 * <ceci> prend la place du fils ainée du frère qui le précédait dans la table.
 * L'ancien cadet de ceci devient par conséquent le cadet du nouveau père de <ceci>.
 * @warning : <ceci> ne peut pas déscendre si il n'a pas de frère qui le précéde.
 * Dans ce cas la fonction retourne 0 et ne fait rien.
 * Dans les autres cas la fonction retourne 1.
 */
int descendre(a_entree ceci);

/**
 * Supprime <ceci> de la table.
 * Toutes les entrées situées sous ceci remontent d'une génération.
 * 
 */
void supprimer_entree(a_entree* ceci);

/**
 * libère toutes la mémoire de la table *<ceci>
 * *<ceci> vaut TABLE_VIDE.
 * 
 */
void detruire_table(t_table* ceci);

/**
 * Sauve le contenu de <ceci> dans le fichier texte <dans> ouvert en écriture.
 */
void sauver_table(t_table ceci, FILE* dans);

/**
 * Fonction pour vous aider à faire la fonction charger_table.
 * Elle amorce le processus de chargement en règlant les différentes variables globales.
 */
void amorcer(FILE* fichier);

/**
 * Fonction pour vous aider à faire la fonction charger_table.
 * elle lit les caractères d'un fichier jusqu'à rencontrer le caractère <lettre>.
 * les caractères lus sont rangés dans un "buffer".
 * On pourra supposer que 50 caractères suffisent pour la taille du buffer.
 * Après la lecture du fichier s'arrète juste après le caractère <lettre> attendu.
 */
void passer();

/**
 * Fonction pour vous aider à faire la fonction charger_table.
 * elle lit les caractères d'un fichier entamé et constuit une table dont le père et le grand frère sont passés en paramètre.
 * elle fournit dans *<benjamin> la valeur du dernière frère de la fraterie en cours.
 */
//void charger_table_aux(t_table* ceci, a_entree pere, a_entree gd_frere, a_entree* benjamin);


/**
 * fonction permettant de charger une table à partir d'un fichier texte ouvert en lecture.
 * Cette fonction est le mirroir de la fonction sauver.
 */
void charger_table(t_table* ceci, FILE* depuis);


#endif