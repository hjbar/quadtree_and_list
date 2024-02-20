#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE } bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc {
  int nombre;
  struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste;

/*************************************************/
/*                                               */
/*        definition type liste_de_liste         */
/*                                               */
/*************************************************/

typedef struct BlocListe {
  Liste liste;
  struct BlocListe *suivant;
} BlocListe;

typedef BlocListe *ListeL;

/*************************************************/
/*                                               */
/*           definition type ListeBis            */
/*                                               */
/*************************************************/

typedef struct BlocBis {
  int nombre;
  struct BlocBis *suivant, **pred;
} BlocBis;

typedef BlocBis *ListeBis;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste a vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element
 * x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste *L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son
 * premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste *l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_rec2(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec(Liste l);
int longueur_iter(Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD(Liste *L);
void VireDernier_rec(Liste *L);
void VireDernier_iter(Liste *L);

/*************************************************/
/*                                               */
/*    predeclarations Liste_de_Liste             */
/*                                               */
/*************************************************/

/* initialise une ListeL a vide */
void initVideL(ListeL *);
/* Elimination de chaque element de en recursif de la ListeL passé en argument*/
void VideListeL(ListeL *);
/* renvoie 1 si la ListeL en parametre est vide, 0 sinon */
bool estVideL(ListeL);
/* renvoie la premiere Liste de la ListeL en parametre */
Liste premierL(ListeL);
/* renvoie une nouvelle ListeL correspondant a celle en parametre sans son
 * premier element */
ListeL suiteL(ListeL);
/* Renvoie une nouvelle liste où l'on a ajouter la liste passée en argument dans
 * la ListeL */
ListeL ajouteL(Liste, ListeL);
/* Modifie la listeL en y ajoutant la liste passé en arguemnt*/
void empileL(Liste, ListeL *);
/* Elimine le premier element de la ListeL passé en argument*/
void depileL(ListeL *);

/*************************************************/
/*                                               */
/*          predeclarations ListeBis             */
/*                                               */
/*************************************************/

/* initialise une ListeBis a vide */
void initVideBis(ListeBis *);
/* Elimination de chaque element de en recursif de la ListeL passé en argument*/
void videBis(ListeBis *);
/* renvoie le premier element de la ListeL en parametre */
int premierBis(ListeBis);
/* renvoie une nouvelle ListeBis correspondant a celle en parametre sans son
 * premier element */
ListeBis suiteBis(ListeBis);
/* Renvoie une nouvelle liste où l'on a ajouter l'entier passée en argument dans
 * la ListeL */
ListeBis ajouteBis(int, ListeBis);
/* Modifie la listeBis en y ajoutant l'entier passé en arguemnt*/
void empileBis(int, ListeBis *);
/* Elimine le premier element de la ListeBis passé en argument*/
void depileBis(ListeBis *);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVide(Liste *L) { *L = NULL; }

bool estVide(Liste l) { return l == NULL; }

int premier(Liste l) { return l->nombre; }

Liste ajoute(int x, Liste l) {
  Liste tmp = (Liste)malloc(sizeof(Bloc));
  tmp->nombre = x;
  tmp->suivant = l;
  return tmp;
}

void empile(int x, Liste *L) { *L = ajoute(x, *L); }

Liste suite(Liste l) { return l->suivant; }

void depile(Liste *L) {
  Liste tmp = *L;
  *L = suite(*L);
  free(tmp);
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l) {
  if (estVide(l))
    printf("\n");
  else {
    printf("%d ", premier(l));
    affiche_rec(suite(l));
  }
}

void affiche_rec2(Liste l) {
  if (estVide(l))
    return;
  else {
    printf("%d ", premier(l));
    affiche_rec2(suite(l));
  }
}

void affiche_iter(Liste l) {
  Liste L2 = l;
  while (!estVide(L2)) {
    printf("%d ", premier(L2));
    L2 = suite(L2);
  }
  printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec(Liste l) {
  if (l == NULL)
    return 0;
  else
    return (1 + longueur_rec(l->suivant));
}

int longueur_iter(Liste l) {
  Liste P = l;
  int cpt = 0;
  while (P ISNOT NULL) {
    P = P->suivant;
    cpt++;
  }
  return cpt;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD(Liste *L)
// *L non NULL ie liste non vide
{
  if (((**L).suivant) == NULL)
    depile(L); // moralement : depile(& (*L)) ;
  else
    VD(&((**L).suivant));
}

void VireDernier_rec(Liste *L) {
  if ((*L)ISNOT NULL)
    VD(L); // moralement : VD(& (*L)) ;
}

void VireDernier_iter(Liste *L) {
  if ((*L)ISNOT NULL) {
    while (((**L).suivant)ISNOT NULL)
      L = &((**L).suivant);
    free(*L);
    *L = NULL;
  }
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L) {
  if (NOT(estVide(*L))) {
    depile(L);
    VideListe(L);
  }
}

/*************************************************/
/*                                               */
/*                Declaration                    */
/*                                               */
/*************************************************/

/** Vérifie que l'un des trois premiers éléments soient un 0 (fonction
 * itérative)
 * @param l1: Liste
 * @return Renvoie 1 si le premièr, second ou troisième élément de la liste est
 * un 0. Renvoie 0 sinon.
 */
bool zero123(Liste);

/** Vérifie que la liste 1 soit plus courte que la second liste (Récursive)
 * @param l1: Liste
 * @param l2: Liste
 * @return Renvoie 1 si la liste 1 est plus courte que la liste 2 sinon elle
 * renvoie 0.
 */
bool plusCourte(Liste, Liste);

/** Calcule le nombre de 0 dans la liste L avant la k-ieme postion (Fonction
 * itérative)
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @return On renvoie le nombre de 0 dans la liste L avant le k-ieme élément.
 */
int nb0avantK_it(Liste, int);
/** Calcule le nombre de 0 dans la liste L avant la k-ieme postion (Fonction
 * Récursive Simple)
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @return On renvoie le nombre de 0 dans la liste L avant le k-ieme élément.
 */
int nb0avantK_rec(Liste, int);
/** Calcule le nombre de 0 dans la liste L avant la k-ieme postion (Fonction
 * Récursive Terminale avec Sous-Fonction)
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @return On renvoie le nombre de 0 dans la liste L avant le k-ieme élément.
 */
int nb0avantK_rec_sf(Liste, int);
/** Sous-Fonction de nb0avantK_rec_sf
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @param cpt : int ; variable in correspondant au nombre de 0 trouvé
 */
int nb0avantK_sf(Liste, int, int);
/** Calcule le nombre de 0 dans la liste L avant la k-ieme postion (Fonction
 * Récursive Terminale avec Sous-Procédure)
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @return On renvoie le nombre de 0 dans la liste L avant le k-ieme élément.
 */
int nb0avantK_rec_sp(Liste, int);
/** Sous-Procédure de nb0avantK_rec_sp
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @param cpt : pointeur vers int ; variable inout correspondant au nombre de 0
 *trouvé
 **/
void nb0avantK_sp(Liste, int, int *);

/** Calcule le nombre de 0 dans la Liste L à partir du K-ieme élément depuis le
 *fond de la liste
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @return On renvoie le nombre de 0 dans la liste L à partir du k-ieme élément.
 **/
int NombreDe0ApresRetroPositionK_rec_sp(Liste, int);
/** Sous-Procédure de NombreDe0ApresRetroPositionK_rec_sp
 * @param l : Liste
 * @param k : int ; pas de restriction sur la valeur de k
 * @param cpt : pointeur vers int ; variable inout correspondant au nombre de 0
 *trouvé
 **/
void NombreDe0ApresRetroPositionK_sp(Liste, int *, int *);

/** Crée une copie de la liste passé en paramètre en ne conservant que les
   élements supérieurs à 0 et en les dédoublants dans la liste(Fonction
   Itérative)
   @param l : Liste
   @return renvoie La liste contenant 2 copies de chaque élément strictement
   supérieur à 0 de La liste L
   **/
Liste FctBegaye_it(Liste);
/** Crée une copie de la liste passé en paramètre en ne conservant que les
élements supérieurs à 0 et en les dédoublants dans la liste(Fonction récursive
simple)
   @param l : Liste
   @return renvoie La liste contenant 2 copies de chaque élément strictement
supérieur à 0 de La liste L
**/
Liste FctBegaye_rec(Liste);
/** Crée une copie de la liste passé en paramètre en ne conservant que les
élements supérieurs à 0 et en les dédoublants dans la liste(Fonction récursive
Terminale avec Sous-procédure)
   @param l : Liste
   @return renvoie La liste contenant 2 copies de chaque élément strictement
supérieur à 0 de La liste L
**/
Liste FctBegaye_recterm(Liste);
/** Sous-procédure de la Fonction FctBegaye_recterm
 * @param l : Liste
 * @param St : Liste ; variable Out, La liste résultante.
 */
void FctBegaye_bis(Liste, Liste *);

/** Modifie la Liste pointé par le pointeur passé en argument afin de ne garder
que les éléments strictement supérieur à 0 et les dédoubler (Procédure Récursive
Terminal)
    * @param L : Pointeur sur une Liste
**/
void ProcBegaye(Liste *);

/** Fonction calculant l'ensemble des permutations de taille n (recursive
 * diviser pour regner) sans fuite de memoire
 * @param n : int
 * @return la liste de liste(ListeL) contenant les permutations à n element
 */
ListeL Permutation(int);
/* Sous-fonction pour calculer le nombre de malloc utilisé*/
ListeL PermutationBis(int, int *, int *);
/** Fonction ajoutant l'entiet passé en argument à toutes les positions de la
 *liste de la liste de liste passé en argument
 * @param x : int ; l'entier a ajouter
 * @param LL : ListeL
 * @param nm1 : pointeur sur int ; compteur malloc de Liste
 * @param nm2 : pointeur sur int ; compteur malloc de ListeL
 * @return renvoie une nouvelle listeL
 **/
ListeL ATLTP(int, ListeL, int *, int *);
/** Concatene deux ListeL passé en argument
 * @param L1 : ListeL
 * @param L2 : ListeL
 * @param nm1 : pointeur sur int ; compteur nombre de malloc de type Liste
 * @param nm2 : pointeur sur int ; compteur nombre de malloc de type ListeL
 * @return revoie une nouvelle listeL avec L2 qui suit L1
 */
ListeL concat(ListeL, ListeL, int *, int *);
/** Calcule l'ensemble des Listes correspondant à l'ajout de l'entier passé en
 * argument à chaque position de la liste passé en argument
 * @param x : int ; l'entier a ajouter
 * @param L : Liste
 * @param nm1 : pointeur sur int ; compteur nombre de malloc de type Liste
 * @param nm2 : pointeur sur int ; compteur nombre de malloc de type ListeL
 * @return renvoie une nouvelle ListeL
 */
ListeL ATP(int, Liste, int *, int *);
/** Calcule l'ensemble des Listes correspondant à l'ajout en-tête de l'entier
 * passé en argument à chaque liste de la ListeL passé en argument
 * @param x : int ; l'entier a ajouter
 * @param L : Liste
 * @param nm1 : pointeur sur int ; compteur nombre de malloc de type Liste
 * @param nm2 : pointeur sur int ; compteur nombre de malloc de type ListeL
 * @return renvoie une nouvelle ListeL
 */
ListeL AETTL(int, ListeL, int *, int *);

/** Fonction calculant l'ensemble des permutations de taille n (recursive
 * diviser pour regner) sans fuite de memoire et avec compression ([somme de
 * (k-1)!*k(k-1)/2 pour k allant de 1 à n] malloc de Liste, n! malloc de Liste
 * de liste).
 * @param n : int
 * @return la liste de liste(ListeL) contenant les permutations à n element
 */
ListeL PermutationOpt(int);
/* Sous-fonction pour calculer le nombre de malloc utilisé*/
ListeL PermutationOptBis(int, int *, int *);
/** Fonction ajoutant l'entiet passé en argument à toutes les positions de la
 *liste de la liste de liste passé en argument
 * @param x : int ; l'entier a ajouter
 * @param LL : ListeL
 * @param nm1 : pointeur sur int ; compteur malloc de Liste
 * @param nm2 : pointeur sur int ; compteur malloc de ListeL
 * @return renvoie une nouvelle listeL
 **/
ListeL ATLTPRec(int, ListeL, int *, int *);
/** Concatene deux ListeL passé en argument en modifiant le dernier bloc de la
 * premiere Liste passée en argument
 * @param L1 : pointeur sur une liste
 * @param L2 : ListeL
 */
void concatRec(ListeL *, ListeL);
/** Calcule l'ensemble des Listes correspondant à l'ajout de l'entier passé en
 * argument à chaque position de la liste passé en argument
 * @param x : int ; l'entier a ajouter
 * @param L : Liste
 * @param nm1 : pointeur sur int ; compteur nombre de malloc de type Liste
 * @param nm2 : pointeur sur int ; compteur nombre de malloc de type ListeL
 * @return renvoie une nouvelle ListeL
 */
ListeL ATPRec(int, Liste, int, int, int *, int *);
/** Fonction auxiliaire de PermutationRec ajoutant un entier à une position
 * donnée dans la liste passée en argument
 * @param x : int ; l'entier à ajouter
 * @param k : int ; la position ou ajouter l'entier
 * @param L : Liste
 * @return une nouvelle liste
 */
Liste Addelem(int, int, Liste, int *);
/* Affiche une Liste de Liste*/
void afficheLL(ListeL);

/** Procedure retirant le bloc du champ pred pointé par le pointeur passé en
 * argument
 * @param P : pointeur de pointeur de ListeBis
 */
void retireBlocPred(ListeBis **);
/* affiche une ListeBis */
void afficheBis(ListeBis);

/*************************************************/
/*                                               */
/*       ZeroEnPositionUnOuDeuxOuTrois           */
/*                                               */
/*************************************************/

bool zero123(Liste l) {
  int arret = 3;
  while (l ISNOT NULL AND arret > 0) {
    if (premier(l) == 0) {
      then return TRUE;
    }
    l = l->suivant;
    arret--;
  }
  return FALSE;
}

void test_zero123() {
  printf("---------------------------------------\n");
  printf("Test de ZeroEnPositionUnOuDeuxOuTrois\n\n");

  Liste l;
  initVide(&l);
  empile(0, &l);
  // affiche_rec(l);
  if (zero123(l)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  empile(1, &l);
  // affiche_rec(l);
  if (zero123(l)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  empile(1, &l);
  // affiche_rec(l);
  if (zero123(l)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  empile(1, &l);
  // affiche_rec(l);
  if (zero123(l)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }

  VideListe(&l);

  Liste l2;
  initVide(&l2);
  // affiche_rec(l2);
  if (zero123(l2)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }
  empile(1, &l2);
  // affiche_rec(l2);
  if (zero123(l2)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }

  VideListe(&l2);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*             plusCourte                        */
/*                                               */
/*************************************************/

bool plusCourte(Liste l1, Liste l2) {
  while (l1 ISNOT NULL AND l2 ISNOT NULL) {
    l1 = l1->suivant;
    l2 = l2->suivant;
  }
  return l2 ISNOT NULL;
}

void test_plusCourte() {
  printf("---------------------------------------\n");
  printf("Test de la fonction PlusCourte\n\n");

  Liste l3;
  initVide(&l3);
  Liste l4;
  initVide(&l4);

  // affiche_rec(l3);
  // affiche_rec(l4);
  if (plusCourte(l3, l4)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }

  empile(1, &l3);
  // affiche_rec(l3);
  // affiche_rec(l4);
  if (plusCourte(l3, l4)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }

  empile(1, &l4);
  // affiche_rec(l3);
  // affiche_rec(l4);
  if (plusCourte(l3, l4)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }
  depile(&l3);
  // affiche_rec(l3);
  // affiche_rec(l4);
  if (plusCourte(l3, l4)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  VideListe(&l3);
  VideListe(&l4);

  Liste l5;
  initVide(&l5);
  Liste l6;
  initVide(&l6);

  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0)
      then empile(i, &l5);
    empile(i, &l6);
  }

  // affiche_rec(l5);
  // affiche_rec(l6);
  if (plusCourte(l5, l6)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  for (int i = 0; i < 5; i++) {
    empile(i, &l5);
  }

  // affiche_rec(l5);
  // affiche_rec(l6);
  if (plusCourte(l5, l6)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }
  for (int i = 0; i < 5; i++) {
    empile(i, &l5);
  }

  // affiche_rec(l5);
  // affiche_rec(l6);
  if (plusCourte(l5, l6)) {
    then printf("ERREUR\n");
  } else {
    printf("ok\n");
  }

  VideListe(&l5);
  VideListe(&l6);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*     NombreDe0AvantPositionK                   */
/*                                               */
/*************************************************/

int nb0avantK_it(Liste l, int K) {
  int cpt = 0;
  while (l ISNOT NULL AND K > 0) {
    if (premier(l) == 0) {
      then cpt++;
    }
    l = l->suivant;
    K--;
  }
  return cpt;
}

int nb0avantK_rec(Liste l, int K) {
  if (l == NULL OR K <= 0) {
    then return 0;
  } else if (premier(l) == 0) {
    then return 1 + nb0avantK_rec(l->suivant, K - 1);
  } else {
    return nb0avantK_rec(l->suivant, K - 1);
  }
}

int nb0avantK_rec_sf(Liste l, int K) { return nb0avantK_sf(l, K, 0); }

int nb0avantK_sf(Liste l, int K, int cpt) {
  if (l == NULL OR K <= 0) {
    then return cpt;
  }
  if (premier(l) == 0) {
    then cpt++;
  }
  return nb0avantK_sf(l->suivant, K - 1, cpt);
}

int nb0avantK_rec_sp(Liste l, int K) {
  int cpt = 0;
  nb0avantK_sp(l, K, &cpt);
  return cpt;
}

void nb0avantK_sp(Liste l, int K, int *cpt) {
  if (l == NULL OR K <= 0) {
    then return;
  }
  if (premier(l) == 0) {
    then *cpt = *cpt + 1;
  }
  then return nb0avantK_sp(l->suivant, K - 1, cpt);
}

void test_nb0avantK() {
  printf("---------------------------------------\n");
  printf("Test de la fonction NombreDe0AvantPositionK\n\n");

  Liste l7;
  initVide(&l7);

  // affiche_rec(l7);
  if (nb0avantK_it(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sf(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sp(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  for (int i = 0; i < 15; i++) {
    if (i % 3 == 0) {
      then empile(0, &l7);
    } else {
      empile(i, &l7);
    }
  }
  // affiche_rec(l7);
  if (nb0avantK_it(l7, 1) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec(l7, 1) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sf(l7, 1) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sp(l7, 1) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  // affiche_rec(l7);
  if (nb0avantK_it(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sf(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sp(l7, 2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  // affiche_rec(l7);
  if (nb0avantK_it(l7, 8) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec(l7, 8) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sf(l7, 8) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sp(l7, 8) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  // affiche_rec(l7);
  if (nb0avantK_it(l7, 15) == 5) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec(l7, 15) == 5) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sf(l7, 15) == 5) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (nb0avantK_rec_sp(l7, 15) == 5) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  VideListe(&l7);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*     NombreDe0ApresRetroPositionK              */
/*                                               */
/*************************************************/

int NombreDe0ApresRetroPositionK_rec_sp(Liste l, int K) {
  int cpt;
  NombreDe0ApresRetroPositionK_sp(l, &K, &cpt);
  return cpt;
}

void NombreDe0ApresRetroPositionK_sp(Liste l, int *K, int *cpt) {
  if (l == NULL) {
    then *cpt = 0;
  } else {
    NombreDe0ApresRetroPositionK_sp(l->suivant, K, cpt);
    *K = *K - 1;
    if (premier(l) == 0 AND(*K) >= 0) {
      then *cpt = *cpt + 1;
    }
  }
}

void test_NombreDe0ApresRetroPositionK() {
  printf("---------------------------------------\n");
  printf("Test de la fonction NombreDe0AoresRetroPositionK\n\n");

  Liste l20;
  initVide(&l20);

  // affiche_rec(l20);
  if (NombreDe0ApresRetroPositionK_rec_sp(l20, 6) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  empile(2, &l20);
  empile(0, &l20);
  empile(5, &l20);
  empile(6, &l20);
  empile(9, &l20);
  empile(0, &l20);
  empile(0, &l20);
  empile(0, &l20);
  empile(1, &l20);
  empile(0, &l20);

  // affiche_rec(l20);
  if (NombreDe0ApresRetroPositionK_rec_sp(l20, 6) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  VideListe(&l20);

  Liste l21;
  initVide(&l21);

  empile(3, &l21);
  empile(0, &l21);
  empile(0, &l21);
  empile(5, &l21);

  // affiche_rec(l21);
  if (NombreDe0ApresRetroPositionK_rec_sp(l21, 6) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  VideListe(&l21);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*              FctBegaye                        */
/*                                               */
/*************************************************/

Liste FctBegaye_it(Liste l) {
  Liste res;
  initVide(&res);
  Liste *ptRes = &res;
  while (l ISNOT NULL) {
    int nb = premier(l);
    if (nb > 0) {
      then empile(nb, ptRes);
      empile(nb, ptRes);
      ptRes = &(*ptRes)->suivant->suivant;
    }
    l = l->suivant;
  }
  return res;
}

Liste FctBegaye_rec(Liste L) {
  if (L == NULL)
    return NULL;
  Liste newL = FctBegaye_rec(suite(L));
  if (L->nombre > 0) {
    empile(L->nombre, &newL);
    empile(L->nombre, &newL);
  }
  return newL;
}

Liste FctBegaye_recterm(Liste l) {
  Liste res;
  initVide(&res);
  FctBegaye_bis(l, &res);
  return res;
}

void FctBegaye_bis(Liste l, Liste *res) {
  if (l == NULL) {
    then return;
  } else {
    if (l->nombre > 0) {
      then empile(l->nombre, res);
      empile(l->nombre, res);
      FctBegaye_bis(l->suivant, &(((*res)->suivant)->suivant));
    } else {
      FctBegaye_bis(l->suivant, res);
    }
  }
}

void test_FctBegaye() {
  printf("---------------------------------------\n");
  printf("Test de la fonction FctBegaye\n\n");

  Liste l8;
  initVide(&l8);

  Liste l9 = FctBegaye_rec(l8);
  Liste l11 = FctBegaye_recterm(l8);
  Liste l13 = FctBegaye_it(l8);

  // affiche_rec(l8);
  printf("Les 3 listes doivent etre la liste vide : []\n");
  affiche_rec(l9);
  affiche_rec(l11);
  affiche_rec(l13);

  for (int i = 0; i < 15; i++) {
    if (i % 2 == 0) {
      then empile(i, &l8);
    } else {
      empile(-1 * i, &l8);
    }
  }

  Liste l10 = FctBegaye_rec(l8);
  Liste l12 = FctBegaye_recterm(l8);
  Liste l14 = FctBegaye_it(l8);

  // affiche_rec(l8);
  printf("Les 3 listes doivent etre la liste vide : [14 14 12 12 10 10 8 8 6 6 "
         "4 4 2 2]\n");
  affiche_rec(l10);
  affiche_rec(l12);
  affiche_rec(l14);

  VideListe(&l8);
  VideListe(&l9);
  VideListe(&l10);
  VideListe(&l11);
  VideListe(&l12);
  VideListe(&l13);
  VideListe(&l14);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*           ProcBegaye                          */
/*                                               */
/*************************************************/

void ProcBegaye(Liste *l) {
  if (*l == NULL) {
    then return;
  } else {
    if ((*l)->nombre > 0) {
      then empile((*l)->nombre, l);
      ProcBegaye(&((*l)->suivant->suivant));
    } else {
      depile(l);
      ProcBegaye(l);
    }
  }
}

void test_ProcBegaye() {
  printf("---------------------------------------\n");
  printf("Test de la procedure Begaye\n\n");

  Liste l15;
  initVide(&l15);

  printf("On doit avoir 2x la liste vide []\n");
  affiche_rec(l15);
  ProcBegaye(&l15);
  affiche_rec(l15);

  for (int i = 0; i < 15; i++) {
    if (i % 2 == 0) {
      then empile(i, &l15);

    } else {
      empile(-1 * i, &l15);
    }
  }

  printf("La liste [14 -13 12 -11 10 -9 8 -7 6 -5 4 -3 2 -1 0] doit se "
         "tranformer en [14 14 12 12 10 10 8 8 6 6 4 4 2 2]\n");
  affiche_rec(l15);
  ProcBegaye(&l15);
  affiche_rec(l15);

  VideListe(&l15);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*             Permutations                      */
/*                                               */
/*************************************************/

void initVideL(ListeL *L) { *L = NULL; }

void VideListeL(ListeL *L) {
  if (NOT(estVideL(*L))) {
    then depileL(L);
    VideListeL(L);
  }
}

bool estVideL(ListeL l) { return l == NULL; }

Liste premierL(ListeL l) { return l->liste; }

ListeL suiteL(ListeL l) { return l->suivant; }

ListeL ajouteL(Liste x, ListeL l) {
  ListeL tmp = (ListeL)malloc(sizeof(BlocListe));
  tmp->liste = x;
  tmp->suivant = l;
  return tmp;
}

void empileL(Liste x, ListeL *L) { *L = ajouteL(x, *L); }

void depileL(ListeL *L) {
  ListeL tmp = *L;
  *L = suiteL(*L);
  free(tmp);
}

/* En general on observe qu'il y a des fuites de memoires pour le nombre ListeL
  En effet, pour Permutation(5) on a 588 malloc de ListeL. La Liste de liste
  finale est de longueur 120 Or On n'elimine aucune des 588 listeL alloué d'ou
  les fuites de mémoires (on devrait en eliminer 588-120=468). On a pas de fuite
  de memoire quand on s'interesse au allocation de type Liste puisque l'on
  utilise chacun des bloc alloues. Nombre de malloc de Liste = somme de
  (k-1)!*k(k+1)/2 pour k allant de 1 a n Une premiere amélioration consistera a
  eliminer les listeL dont l'on a plus besoin :
    - On elimine les permutations de rang inferieur (dans ATLTP)
    - On elimine les ListesL de L1 dans concat car l'on alloue de nouvelle
  ListeL avec leur liste
    - On elimine les ListesL de taille inferieur a k (lorsque l'on calcule les
  permutations de k element) renvoyer par ATP (dans AETTL) (On n'utilise pas
  depileL parce que la fonction elimine aussi les listes dans nos listes de
  listes) Une seconde amélioration consistera a n'allouer une nouvelle ListeL
  uniquement lorsque l'on a obtenu une nouvelle permutation mais aussi
  d'utiliser les ListeL deja alloue pour les permutations de rang inferieur en
  leur ajoutant un nouvelle element, On va modifier ATLTP pour que l'on utilise
  les ListesL deja alloue. (Pour obtenir les permutations de 5 element on alloue
  seulement 96 nouvelle ListeL car on utilise les 24 ListesL deja alloue pour
  les permutations de 4). concat pour ne faire aucune allocation, on va modifier
  ATP et on va utiliser une autre fonction que AETTL.
*/
ListeL Permutation(int n) {
  int nm1 = 0;
  int nm2 = 0;
  ListeL res = PermutationBis(n, &nm1, &nm2);
  printf("Nombre de malloc Liste: %d\tnombre de malloc ListeL: %d\n", nm1, nm2);
  return res;
}

ListeL PermutationBis(int n, int *nm1, int *nm2) {
  if (n == 0)
    then return NULL;
  if (n == 1) {
    ++(*nm1);
    ++(*nm2);
    return ajouteL(ajoute(1, NULL), NULL);
  }
  ListeL L = ATLTP(n, PermutationBis(n - 1, nm1, nm2), nm1, nm2);
  return L;
}

ListeL ATLTP(int x, ListeL LL, int *nm1, int *nm2) {
  if (LL == NULL)
    then return NULL;
  else {
    // On elimine les ListeL contenant les permutations de n-1 element
    ListeL tmp = LL;
    ListeL res = concat(ATP(x, premierL(LL), nm1, nm2),
                        ATLTP(x, suiteL(LL), nm1, nm2), nm1, nm2);
    free(tmp);
    return res;
  }
}

ListeL concat(ListeL L1, ListeL L2, int *nm1, int *nm2) {
  if (L1 == NULL)
    then return L2;
  else {
    *nm2 += 1;
    ListeL tmp = L1;
    ListeL res = ajouteL(premierL(L1), concat(suiteL(L1), L2, nm1, nm2));
    // On elimine Le premiere élément de L1 car l'on alloue une nouvelle ListeL
    // contenant la liste de L1
    free(tmp);
    return res;
  }
}

ListeL ATP(int x, Liste L, int *nm1, int *nm2) {
  *nm1 += 1;
  *nm2 += 1;
  if (L == NULL) {
    then L = ajoute(x, L);
    ListeL LL = ajouteL(L, NULL);
    return LL;
  } else {
    ListeL atp = ATP(x, suite(L), nm1, nm2);
    ListeL res = ajouteL(ajoute(x, L), AETTL(premier(L), atp, nm1, nm2));
    return res;
  }
}

ListeL AETTL(int x, ListeL LL, int *nm1, int *nm2) {
  if (LL == NULL) {
    then ListeL LL = NULL;
    return LL;
  } else {
    *nm1 += 1;
    *nm2 += 1;
    ListeL res =
        ajouteL(ajoute(x, premierL(LL)), AETTL(x, suiteL(LL), nm1, nm2));
    /** On elimine toutes les listes de listes renvoyer par ATP qui ne sont pas
    de taille k lorsque l'on est en train de générer les permutations de taille
    k.**/
    free(LL);
    return res;
  }
}

ListeL PermutationOpt(int n) {
  int nm1 = 0, nm2 = 0;
  ListeL res = PermutationOptBis(n, &nm1, &nm2);
  printf("Nombre de malloc Liste: %d\tnombre de malloc ListeL: %d\n", nm1, nm2);
  return res;
}

ListeL PermutationOptBis(int n, int *nm1, int *nm2) {
  if (n == 0) {
    then return NULL;
  } else if (n == 1) {
    then *nm1 += 1;
    *nm2 += 1;
    return ajouteL(ajoute(1, NULL), NULL);
  } else {
    return ATLTPRec(n, PermutationOptBis(n - 1, nm1, nm2), nm1, nm2);
  }
}

ListeL ATLTPRec(int x, ListeL Perm, int *nm1, int *nm2) {
  if (Perm == NULL)
    then return NULL;
  else {
    ListeL newPerm = ATPRec(x, premierL(Perm), x, 1, nm1, nm2);
    *nm1 += 1;
    empile(x, &(Perm->liste));
    ListeL suiv = Perm->suivant;
    Perm->suivant = newPerm;
    concatRec(&Perm, ATLTPRec(x, suiv, nm1, nm2));
    return Perm;
  }
}

void concatRec(ListeL *L1, ListeL L2) {
  if (*L1 == NULL) {
    then *L1 = L2;
  } else if ((*L1)->suivant == NULL) {
    then(*L1)->suivant = L2;
  } else {
    concatRec(&((*L1)->suivant), L2);
  }
}

ListeL ATPRec(int x, Liste L, int n, int k, int *nm1, int *nm2) {
  if (k == n) {
    then return NULL;
  } else {
    *nm2 += 1;
    return ajouteL(Addelem(x, k, L, nm1), ATPRec(x, L, n, k + 1, nm1, nm2));
  }
}

Liste Addelem(int x, int k, Liste L, int *nm1) {
  if (k == 0) {
    then *nm1 += 1;
    return ajoute(x, L);
  } else if (L == NULL)
    then return NULL;
  else {
    *nm1 += 1;
    return ajoute(L->nombre, Addelem(x, k - 1, suite(L), nm1));
  }
}

void afficheLL(ListeL LL) {
  printf("[\n");
  while (LL ISNOT NULL) {
    printf("[");
    affiche_rec2(premierL(LL));
    printf("]\n");
    LL = suiteL(LL);
  }
  printf("]\n");
}

void test_permutation() {
  printf("---------------------------------------\n");
  printf("Test de la fonction Permutation\n\n");

  ListeL LL;
  initVideL(&LL);
  ListeL LLRec;
  initVideL(&LLRec);

  printf("Les permutations de 0\n");
  printf("Version Recursive\n");
  LL = Permutation(0);
  afficheLL(LL);
  printf("Version Recursive Optimisee\n");
  LLRec = PermutationOpt(0);
  afficheLL(LLRec);
  printf("\n");

  VideListeL(&LL);
  VideListeL(&LLRec);

  ListeL LL2;
  initVideL(&LL2);
  ListeL LL2Rec;
  initVideL(&LL2Rec);

  printf("Les permutations de 1\n");
  printf("Version Recursive\n");
  LL2 = Permutation(1);
  afficheLL(LL2);
  printf("Version Recursive Optimisee\n");
  LL2Rec = PermutationOpt(1);
  afficheLL(LL2Rec);
  printf("\n");

  VideListeL(&LL2);
  VideListeL(&LL2Rec);

  ListeL LL3;
  initVideL(&LL3);
  ListeL LL3Rec;
  initVideL(&LL3Rec);

  printf("Les permutations de 3\n");
  printf("Version Recursive\n");
  LL3 = Permutation(3);
  afficheLL(LL3);
  printf("Version Recursive Optimisee\n");
  LL3Rec = PermutationOpt(3);
  afficheLL(LL3Rec);
  printf("\n");

  VideListeL(&LL3);
  VideListeL(&LL3Rec);

  ListeL LL4;
  initVideL(&LL4);
  ListeL LL4Rec;
  initVideL(&LL4Rec);

  printf("Les permutations de 5\n");
  printf("Version Recursive\n");
  LL4 = Permutation(5);
  afficheLL(LL4);
  printf("Version Recursive Optimisee\n");
  LL4Rec = PermutationOpt(5);
  afficheLL(LL4Rec);
  printf("\n");

  VideListeL(&LL4);
  VideListeL(&LL4Rec);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*           ListeBis                            */
/*                                               */
/*************************************************/

void initVideBis(ListeBis *LB) { *LB = NULL; }

void videBis(ListeBis *LB) {
  if (*LB == NULL)
    then return;
  depileBis(LB);
  videBis(LB);
}

int premierBis(ListeBis LB) { return LB->nombre; }

ListeBis suiteBis(ListeBis LB) { return LB->suivant; }

ListeBis ajouteBis(int x, ListeBis LB) {
  ListeBis nouv = (ListeBis)malloc(sizeof(BlocBis));
  nouv->nombre = x;
  nouv->suivant = LB;
  nouv->pred = &nouv;
  if (LB) {
    then LB->pred = &(nouv->suivant);
  }
  return nouv;
}

void empileBis(int x, ListeBis *LB) {
  ListeBis nouv = (ListeBis)malloc(sizeof(BlocBis));
  nouv->nombre = x;
  nouv->suivant = *LB;
  if (*LB)
    then(*LB)->pred = &(nouv->suivant);
  *LB = nouv;
  (*LB)->pred = LB;
}

void depileBis(ListeBis *LB) {
  if (NOT * LB)
    then return;
  ListeBis tmp = *LB;
  if (tmp->suivant)
    then tmp->suivant->pred = tmp->pred;
  else
    *tmp->pred = tmp->suivant;
  *LB = tmp->suivant;
  free(tmp);
}

void retireBlocPred(ListeBis **P) { depileBis(*P); }

void afficheBis(ListeBis LB) {
  if (NOT LB)
    then printf("\n");
  else {
    printf("%d ", premierBis(LB));
    afficheBis(suiteBis(LB));
  }
}

void test_listeBis() {
  printf("---------------------------------------\n");
  printf("Test de la fonction retireBlocPred\n\n");

  ListeBis l0;
  initVideBis(&l0);

  empileBis(1, &l0);

  printf("La liste doit etre de la forme : [1]\n");
  afficheBis(l0);
  ListeBis *test0 = l0->pred;
  printf("Le nombre pointe est : %d\n", (*test0)->nombre);
  printf("La liste doit etre de la forme : []\n");
  retireBlocPred(&test0);
  afficheBis(l0);
  printf("\n");

  videBis(&l0);

  ListeBis l1;
  initVideBis(&l1);

  empileBis(2, &l1);
  empileBis(1, &l1);

  printf("La liste doit etre de la forme : [1, 2]\n");
  afficheBis(l1);
  ListeBis *test1 = l1->suivant->pred;
  printf("Le nombre pointe est : %d\n", (*test1)->nombre);
  printf("La liste doit etre de la forme : [1]\n");
  retireBlocPred(&test1);
  afficheBis(l1);
  printf("\n");

  videBis(&l1);

  ListeBis l2;
  initVideBis(&l2);

  empileBis(42, &l2);
  empileBis(93, &l2);
  empileBis(17, &l2);
  empileBis(23, &l2);

  printf("La liste doit etre de la forme : [23, 17, 93, 42]\n");
  afficheBis(l2);
  ListeBis *test2 = l2->suivant->suivant->pred;
  printf("Le nombre pointe est : %d\n", (*test2)->nombre);
  printf("La liste doit etre de la forme : [23, 17, 42]\n");
  retireBlocPred(&test2);
  afficheBis(l2);
  printf("\n");

  videBis(&l2);

  ListeBis l3;
  initVideBis(&l3);

  for (int i = 5; i >= 0; i--) {
    empileBis(i, &l3);
  }

  printf("La liste doit etre de la forme : [0, 1, 2, 3, 4, 5]\n");
  afficheBis(l3);
  ListeBis *test3 = l3->suivant->suivant->suivant->suivant->suivant->pred;
  printf("Le nombre pointe est : %d\n", (*test3)->nombre);
  printf("La liste doit etre de la forme : [0, 1, 2, 3, 4]\n");
  retireBlocPred(&test3);
  afficheBis(l3);
  printf("\n");

  videBis(&l3);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup(Liste l) {
  printf("Double Affichage \n");
  affiche_rec(l);
  affiche_iter(l);

  printf("Longueur en double %d %d \n\n", longueur_rec(l), longueur_iter(l));
}

int main(int argc, char **argv) {

  test_zero123();
  test_plusCourte();
  test_nb0avantK();
  test_NombreDe0ApresRetroPositionK();
  test_FctBegaye();
  test_ProcBegaye();
  test_permutation();
  test_listeBis();

  return 0;
}
