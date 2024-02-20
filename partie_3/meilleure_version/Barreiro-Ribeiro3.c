#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                Sucre syntaxique               */
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
/*          Definition type image                */
/*                                               */
/*************************************************/

typedef struct bloc_image {
  bool toutnoir;
  struct bloc_image *fils[4];
} bloc_image;

typedef bloc_image *image;

/*************************************************/
/*                                               */
/*                 Declarations                  */
/*                                               */
/*************************************************/

void Libere(image);
void LibereFils(image);
int Power(int, int);

image Construit_Blanc();
image Construit_Noir();
image Construit_Composee(image, image, image, image);

void AffichageNorm(image);
void AffichageNormBis(image);
void AffichageProf(image);
void AffichageProfBis(int, image);

image Lecture();

bool EstBlanc(image);
bool EstNoir(image);

image Diagonale(int);

image QuartDeTour(image);

void Negatif(image *);

void SimplifieProfP(int, image *);

bool Incluse(image, image);

int HautMaxBlanc(image);
void HautMaxBlancBis(image, int *, bool *);

void BlanchitProfP(image *, int, int, int);
void BlanchitProfPBis(image *, int, int, int);

image Chute(image);

/*************************************************/
/*                                               */
/*                Briques de base                */
/*                                               */
/*************************************************/

void Libere(image img) {
  if (img == NULL) {
    then return;
  } else if (img->toutnoir) {
    then free(img);
  } else {
    Libere((img->fils)[0]);
    Libere((img->fils)[1]);
    Libere((img->fils)[2]);
    Libere((img->fils)[3]);
    free(img);
  }
}

void LibereFils(image img) {
  if (img == NULL OR img->toutnoir)
    then return;
  else {
    for (int i = 0; i < 4; ++i) {
      Libere((img->fils)[i]);
      (img->fils)[i] = NULL;
    }
  }
}

int Power(int x, int n) {
  double r = 1;
  while (n != 0) {
    if (n % 2 == 1) {
      then r = r * x;
    }
    n = n / 2;
    x = x * x;
  }
  return r;
}

void test_power() {

  printf("---------------------------------------\n");
  printf("Test de Power\n\n");

  if (Power(0, 0) == 1) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (Power(0, 1) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (Power(1, 0) == 1) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (Power(1, 1) == 1) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (Power(5, 0) == 1) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (Power(5, 1) == 5) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (Power(5, 5) == 3125) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*            Constructeurs_Couleurs             */
/*                                               */
/*************************************************/

image Construit_Blanc() { return NULL; }

void test_construit_blanc() {

  printf("---------------------------------------\n");
  printf("Test de Construit_Blanc\n\n");

  image img = Construit_Blanc();
  if (img == NULL) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  Libere(img);

  printf("---------------------------------------\n");
}

image Construit_Noir() {
  image img = (image)malloc(sizeof(bloc_image));
  img->toutnoir = TRUE;
  for (int i = 0; i < 4; ++i) {
    (img->fils)[i] = NULL;
  }
  return img;
}

void test_construit_noir() {

  printf("---------------------------------------\n");
  printf("Test de Construit_Noir\n\n");

  image img = Construit_Noir();

  if (img ISNOT NULL) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (img->toutnoir == TRUE) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  for (int i = 0; i < 4; i++) {
    if (img->fils[i] == NULL) {
      then printf("ok\n");
    } else {
      printf("ERREUR\n");
    }
  }

  Libere(img);

  printf("---------------------------------------\n");
}

image Construit_Composee(image i1, image i2, image i3, image i4) {
  image img = (image)malloc(sizeof(bloc_image));
  img->toutnoir = FALSE;
  (img->fils)[0] = i1;
  (img->fils)[1] = i2;
  (img->fils)[2] = i3;
  (img->fils)[3] = i4;
  return img;
}

void test_construit_composee() {

  printf("---------------------------------------\n");
  printf("Test de Construit_Composee\n\n");

  image img = Construit_Composee(NULL, NULL, NULL, NULL);

  if (img ISNOT NULL) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (img->toutnoir ISNOT TRUE) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  for (int i = 0; i < 4; i++) {
    if (img->fils[i] == NULL) {
      then printf("ok\n");
    } else {
      printf("ERREUR\n");
    }
  }

  image img2 = Construit_Composee(Construit_Noir(), Construit_Noir(),
                                  Construit_Noir(), Construit_Noir());

  if (img2 ISNOT NULL) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  if (img2->toutnoir ISNOT TRUE) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  for (int i = 0; i < 4; i++) {
    if (img2->fils[i] ISNOT NULL) {
      then printf("ok\n");
    } else {
      printf("ERREUR\n");
    }
  }

  Libere(img);
  Libere(img2);

  printf("---------------------------------------\n");
}

void test_construit_couleur() {
  test_construit_blanc();
  test_construit_noir();
  test_construit_composee();
}

/*************************************************/
/*                                               */
/*                  Affichages                   */
/*                                               */
/*************************************************/

void AffichageNorm(image img) {
  AffichageNormBis(img);
  printf("\n");
}

void AffichageNormBis(image img) {
  if (img == NULL) {
    then printf("B");
  } else if (img->toutnoir) {
    then printf("N");
  } else {
    printf("(");
    for (int i = 0; i < 4; ++i) {
      AffichageNormBis((img->fils)[i]);
    }
    printf(")");
  }
}

void test_affichage_norm() {

  printf("---------------------------------------\n");
  printf("Test de AffichageNorm\n\n");

  image img = Construit_Blanc();
  printf("Doit afficher B: ");
  AffichageNorm(img);

  image img2 = Construit_Noir();
  printf("Doit afficher N: ");
  AffichageNorm(img2);

  image img3 = Construit_Composee(
      Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                         Construit_Blanc(), Construit_Noir()),
      Construit_Composee(Construit_Blanc(), Construit_Blanc(), Construit_Noir(),
                         Construit_Blanc()),
      Construit_Composee(Construit_Blanc(), Construit_Noir(), Construit_Blanc(),
                         Construit_Blanc()),
      Construit_Composee(Construit_Noir(), Construit_Blanc(), Construit_Blanc(),
                         Construit_Blanc()));
  printf("Doit afficher ((BBBN)(BBNB)(BNBB)(NBBB)): ");
  AffichageNorm(img3);

  Libere(img);
  Libere(img2);
  Libere(img3);

  printf("---------------------------------------\n");
}

void AffichageProf(image img) {
  AffichageProfBis(0, img);
  printf("\n");
}

void AffichageProfBis(int n, image img) {
  if (img == NULL) {
    then printf("B%d ", n);
  } else if (img->toutnoir) {
    then printf("N%d ", n);
  } else {
    printf("( ");
    for (int i = 0; i < 4; ++i) {
      AffichageProfBis(n + 1, (img->fils)[i]);
    }
    printf(") ");
  }
}

void test_affichage_prof() {

  printf("---------------------------------------\n");
  printf("Test de AffichageProf\n\n");

  image img = Construit_Blanc();
  printf("Doit afficher B0: ");
  AffichageProf(img);

  image img2 = Construit_Noir();
  printf("Doit afficher N0: ");
  AffichageProf(img2);

  image img3 = Construit_Composee(
      Construit_Noir(),
      Construit_Composee(Construit_Blanc(), Construit_Blanc(), Construit_Noir(),
                         Construit_Blanc()),
      Construit_Blanc(),
      Construit_Composee(
          Construit_Noir(),
          Construit_Composee(
              Construit_Noir(), Construit_Noir(), Construit_Blanc(),
              Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                 Construit_Noir(), Construit_Noir())),
          Construit_Blanc(), Construit_Noir()));
  printf(
      "Doit afficher ( N1 ( B2 B2 N2 B2 ) B1 ( N2 ( N3 N3 B3 ( N4 B4 N4 N4 ) "
      ") B2 N2 ) ): ");
  AffichageProf(img3);

  Libere(img);
  Libere(img2);
  Libere(img3);

  printf("---------------------------------------\n");
}

void test_affichages() {
  test_affichage_norm();
  test_affichage_prof();
}

/*************************************************/
/*                                               */
/*                   Lecture                     */
/*                                               */
/*************************************************/

image Lecture() {
  char c;
  scanf(" %c", &c);
  while (c != 'B' AND c != 'N' AND c != '(')
    scanf(" %c", &c); // On ne prend en compte que les caractere indiquant la
                      // nature d'une image
  if (c == 'B') {
    then return NULL;
  } else if (c == 'N') {
    then return Construit_Noir();
  } else { // on a forcement à ce stade que c = '(' car on a testé pour 'B', 'N'
           // et les autres caracteres ont ete ignores auparavant.
    then image i4 = Lecture();
    image i3 = Lecture();
    image i2 = Lecture();
    image i1 = Lecture();
    while (c != ')')
      scanf("%c", &c); // les images de profondeur superieur a zero se finisse
                       // par une ')'
    return Construit_Composee(i4, i3, i2, i1);
  }
}

void test_lecture() {

  printf("---------------------------------------\n");
  printf("Test de Lecture\n\n");

  image img = Lecture();
  AffichageNorm(img);

  Libere(img);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*                EstCouleur                     */
/*                                               */
/*************************************************/

bool EstBlanc(image img) {
  if (img == NULL) {
    then return TRUE;
  } else if (img->toutnoir) {
    then return FALSE;
  } else {
    return EstBlanc((img->fils)[0]) && EstBlanc((img->fils)[1]) &&
           EstBlanc((img->fils)[2]) && EstBlanc((img->fils)[3]);
  }
}

void test_est_blanc() {

  printf("---------------------------------------\n");
  printf("Test de EstBlanc\n\n");

  image img = Construit_Blanc();
  if (EstBlanc(img)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img2 = Construit_Noir();
  if (NOT EstBlanc(img2)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img3 = Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                  Construit_Blanc(), Construit_Blanc());
  if (EstBlanc(img3)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img4 = Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                  Construit_Blanc(), Construit_Noir());
  if (NOT EstBlanc(img4)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img5 = Construit_Composee(
      Construit_Composee(
          Construit_Blanc(), Construit_Blanc(), Construit_Blanc(),
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Blanc())),
      Construit_Blanc(), Construit_Blanc(), Construit_Blanc());
  if (EstBlanc(img5)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img6 = Construit_Composee(
      Construit_Composee(
          Construit_Blanc(), Construit_Blanc(), Construit_Blanc(),
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Noir())),
      Construit_Blanc(), Construit_Blanc(), Construit_Blanc());
  if (NOT EstBlanc(img6)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);

  printf("---------------------------------------\n");
}

bool EstNoir(image img) {
  if (img == NULL) {
    then return FALSE;
  } else if (img->toutnoir) {
    then return TRUE;
  } else {
    return EstNoir((img->fils)[0]) && EstNoir((img->fils)[1]) &&
           EstNoir((img->fils)[2]) && EstNoir((img->fils)[3]);
  }
}

void test_est_noir() {

  printf("---------------------------------------\n");
  printf("Test de EstNoir\n\n");

  image img = Construit_Noir();
  if (EstNoir(img)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img2 = Construit_Blanc();
  if (NOT EstNoir(img2)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img3 = Construit_Composee(Construit_Noir(), Construit_Noir(),
                                  Construit_Noir(), Construit_Noir());
  if (EstNoir(img3)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img4 = Construit_Composee(Construit_Noir(), Construit_Noir(),
                                  Construit_Noir(), Construit_Blanc());
  if (NOT EstNoir(img4)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img5 = Construit_Composee(
      Construit_Composee(Construit_Noir(), Construit_Noir(), Construit_Noir(),
                         Construit_Composee(Construit_Noir(), Construit_Noir(),
                                            Construit_Noir(),
                                            Construit_Noir())),
      Construit_Noir(), Construit_Noir(), Construit_Noir());
  if (EstNoir(img5)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img6 = Construit_Composee(
      Construit_Composee(Construit_Noir(), Construit_Noir(), Construit_Noir(),
                         Construit_Composee(Construit_Noir(), Construit_Noir(),
                                            Construit_Noir(),
                                            Construit_Blanc())),
      Construit_Noir(), Construit_Noir(), Construit_Noir());
  if (NOT EstNoir(img6)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);

  printf("---------------------------------------\n");
}

void test_est_couleur() {
  test_est_blanc();
  test_est_noir();
}

/*************************************************/
/*                                               */
/*                 Diagonale                     */
/*                                               */
/*************************************************/

image Diagonale(int p) {
  if (p == 0) {
    then return Construit_Noir();
  }
  return Construit_Composee(Diagonale(p - 1), Construit_Blanc(),
                            Construit_Blanc(), Diagonale(p - 1));
}

void test_diagonale() {

  printf("---------------------------------------\n");
  printf("Test de Diagonale\n\n");

  image img = Diagonale(0);
  printf("Doit afficher N: ");
  AffichageNorm(img);

  image img2 = Diagonale(1);
  printf("Doit afficher (NBBN): ");
  AffichageNorm(img2);

  image img3 = Diagonale(3);
  printf("Doit afficher (((NBBN)BB(NBBN))BB((NBBN)BB(NBBN))): ");
  AffichageNorm(img3);

  Libere(img);
  Libere(img2);
  Libere(img3);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*               QuartDeTour                     */
/*                                               */
/*************************************************/

image QuartDeTour(image img) {
  if (img == NULL) {
    then return Construit_Blanc();
  } else if (img->toutnoir) {
    then return Construit_Noir();
  } else {
    return Construit_Composee(
        QuartDeTour((img->fils)[2]), QuartDeTour((img->fils)[0]),
        QuartDeTour((img->fils)[3]), QuartDeTour((img->fils)[1]));
  }
}

void test_quart_de_tour() {

  printf("---------------------------------------\n");
  printf("Test de QuartDeTour\n\n");

  image img = Construit_Blanc();
  image img5 = QuartDeTour(img);
  printf("Doit afficher B: ");
  AffichageNorm(img5);

  image img2 = Construit_Noir();
  image img6 = QuartDeTour(img2);
  printf("Doit afficher N: ");
  AffichageNorm(img6);

  image img3 = Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                  Construit_Blanc(), Construit_Noir());
  image img7 = QuartDeTour(img3);
  printf("Doit afficher (BNNB): ");
  AffichageNorm(img7);

  image img4 = Construit_Composee(
      Construit_Composee(Construit_Blanc(), Construit_Noir(), Construit_Noir(),
                         Construit_Noir()),
      Construit_Blanc(),
      Construit_Composee(Construit_Noir(), Construit_Noir(), Construit_Blanc(),
                         Construit_Blanc()),
      Construit_Noir());
  image img8 = QuartDeTour(img4);
  printf("Doit afficher ((BNBN)(NBNN)NB): ");
  AffichageNorm(img8);

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);
  Libere(img7);
  Libere(img8);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*                  Negatif                      */
/*                                               */
/*************************************************/

void Negatif(image *img) {
  if (*img == NULL) {
    then *img = Construit_Noir();
  } else if ((*img)->toutnoir) {
    then Libere(*img);
    *img = Construit_Blanc();
  } else {
    Negatif(&((*img)->fils)[0]);
    Negatif(&((*img)->fils)[1]);
    Negatif(&((*img)->fils)[2]);
    Negatif(&((*img)->fils)[3]);
  }
}

void test_negatif() {

  printf("---------------------------------------\n");
  printf("Test de Negatif\n\n");

  image img = Construit_Blanc();
  Negatif(&img);
  printf("Doit afficher N: ");
  AffichageNorm(img);

  image img2 = Construit_Noir();
  Negatif(&img2);
  printf("Doit afficher B: ");
  AffichageNorm(img2);

  image img3 = Construit_Composee(
      Construit_Composee(Construit_Noir(), Construit_Blanc(), Construit_Noir(),
                         Construit_Noir()),
      Construit_Blanc(), Construit_Noir(), Construit_Blanc());
  Negatif(&img3);
  printf("Doit afficher ((BNBB)NBN): ");
  AffichageNorm(img3);

  Libere(img);
  Libere(img2);
  Libere(img3);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*               SimplifieProfP                  */
/*                                               */
/*************************************************/

void SimplifieProfP(int p, image *img) {
  if (p == 0) {
    if (EstBlanc(*img)) {
      then Libere(*img);
      *img = NULL;
    } else if (EstNoir(*img)) {
      then LibereFils(*img);
      (*img)->toutnoir = TRUE;
    }
    return;
  } else {
    --p;
    for (int i = 0; i < 4; ++i)
      SimplifieProfP(p, &(((*img)->fils)[i]));
  }
}

void test_simplifie_prof_p() {

  printf("---------------------------------------\n");
  printf("Test de SimplifieProfP\n\n");

  image img = Construit_Blanc();
  SimplifieProfP(0, &img);
  printf("Doit afficher B: ");
  AffichageNorm(img);

  image img2 = Construit_Noir();
  SimplifieProfP(0, &img2);
  printf("Doit afficher N: ");
  AffichageNorm(img2);

  image img3 = Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                  Construit_Blanc(), Construit_Blanc());
  SimplifieProfP(0, &img3);
  printf("Doit afficher B: ");
  AffichageNorm(img3);

  image img4 = Construit_Composee(Construit_Noir(), Construit_Noir(),
                                  Construit_Noir(), Construit_Noir());
  SimplifieProfP(0, &img4);
  printf("Doit afficher N: ");
  AffichageNorm(img4);

  image img5 = Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                  Construit_Blanc(), Construit_Blanc());
  SimplifieProfP(1, &img5);
  printf("Doit afficher (BBBB): ");
  AffichageNorm(img5);

  image img6 = Construit_Composee(Construit_Noir(), Construit_Noir(),
                                  Construit_Noir(), Construit_Noir());
  SimplifieProfP(1, &img6);
  printf("Doit afficher (NNNN): ");
  AffichageNorm(img6);

  image img7 = Construit_Composee(
      Construit_Noir(),
      Construit_Composee(
          Construit_Noir(), Construit_Blanc(),
          Construit_Composee(
              Construit_Noir(), Construit_Noir(),
              Construit_Composee(Construit_Noir(), Construit_Noir(),
                                 Construit_Noir(), Construit_Noir()),
              Construit_Noir()),
          Construit_Blanc()),
      Construit_Composee(
          Construit_Noir(), Construit_Blanc(), Construit_Noir(),
          Construit_Composee(
              Construit_Noir(), Construit_Blanc(), Construit_Noir(),
              Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                 Construit_Blanc(), Construit_Blanc()))),
      Construit_Composee(
          Construit_Blanc(), Construit_Blanc(),
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Blanc()),
          Construit_Blanc()));
  SimplifieProfP(2, &img7);
  printf("Doit afficher (N(NBNB)(NBN(NBN(BBBB)))(BBBB)): ");
  AffichageNorm(img7);

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);
  Libere(img7);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*                  Incluse                      */
/*                                               */
/*************************************************/

bool Incluse(image img1, image img2) {
  if (img1 == NULL OR EstNoir(img2)) {
    then return TRUE;
  } else if (img1->toutnoir) {
    then return FALSE;
  } else {
    for (int i = 0; i < 4; ++i) {
      if ((img2 AND NOT Incluse((img1->fils)[i],
                                (img2->fils)[i]))OR NOT EstBlanc(img1)) {
        then return FALSE;
      }
    }
    return TRUE;
  }
}

void test_incluse() {

  printf("---------------------------------------\n");
  printf("Test de Incluse\n\n");

  image img = Construit_Blanc();
  image img2 = Construit_Noir();
  if (Incluse(img, img2)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (NOT Incluse(img2, img)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img3 = Construit_Noir();
  image img4 = Construit_Noir();
  if (Incluse(img3, img4)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (Incluse(img4, img3)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img5 = Construit_Composee(
      Construit_Composee(
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Blanc()),
          Construit_Noir(), Construit_Blanc(), Construit_Noir()),
      Construit_Blanc(), Construit_Noir(),
      Construit_Composee(
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Noir(), Construit_Noir()),
          Construit_Blanc(), Construit_Blanc(),
          Construit_Composee(Construit_Noir(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Noir())));

  image img6 = Construit_Composee(
      Construit_Composee(Construit_Blanc(), Construit_Noir(), Construit_Noir(),
                         Construit_Noir()),
      Construit_Composee(Construit_Blanc(), Construit_Blanc(), Construit_Noir(),
                         Construit_Blanc()),
      Construit_Composee(Construit_Noir(), Construit_Noir(), Construit_Noir(),
                         Construit_Noir()),
      Construit_Composee(Construit_Noir(), Construit_Blanc(), Construit_Noir(),
                         Construit_Composee(Construit_Noir(), Construit_Noir(),
                                            Construit_Noir(),
                                            Construit_Blanc())));

  if (NOT Incluse(img5, img6)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }
  if (NOT Incluse(img6, img5)) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*              HautMaxBlanc                     */
/*                                               */
/*************************************************/

int HautMaxBlanc(image img) {
  int h;
  bool c;
  HautMaxBlancBis(img, &h, &c);
  return h;
}

void HautMaxBlancBis(image img, int *h, bool *c) {
  if (img == NULL) {
    then *h = 0;
    *c = TRUE;
  } else if (img->toutnoir) {
    then *h = -1;
    *c = FALSE;
  } else {
    *c = TRUE;
    *h = -1;
    for (int i = 0; i < 4; ++i) {
      int h1;
      bool c1;
      HautMaxBlancBis((img->fils)[i], &h1, &c1);
      if (*h < h1) {
        then *h = h1;
      }
      if (NOT c1) {
        then *c = FALSE;
      }
    }
    if (*c) {
      *h = *h + 1;
    }
  }
}

void test_haut_max_blanc() {

  printf("---------------------------------------\n");
  printf("Test de HautMaxBlanc\n\n");

  image img = Construit_Noir();
  if (HautMaxBlanc(img) == -1) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img2 = Construit_Blanc();
  if (HautMaxBlanc(img2) == 0) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img3 = Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                  Construit_Blanc(), Construit_Blanc());
  if (HautMaxBlanc(img3) == 1) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img4 = Construit_Composee(
      Construit_Blanc(), Construit_Blanc(), Construit_Blanc(),
      Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                         Construit_Blanc(), Construit_Blanc()));
  if (HautMaxBlanc(img4) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img5 = Construit_Composee(
      Construit_Blanc(), Construit_Blanc(),
      Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                         Construit_Blanc(), Construit_Blanc()),
      Construit_Composee(
          Construit_Blanc(), Construit_Blanc(), Construit_Blanc(),
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Blanc())));
  if (HautMaxBlanc(img5) == 3) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img6 = Construit_Composee(
      Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                         Construit_Blanc(), Construit_Blanc()),
      Construit_Noir(),
      Construit_Composee(Construit_Blanc(), Construit_Noir(), Construit_Blanc(),
                         Construit_Noir()),
      Construit_Composee(
          Construit_Noir(), Construit_Blanc(), Construit_Noir(),
          Construit_Composee(
              Construit_Noir(), Construit_Blanc(),
              Construit_Composee(
                  Construit_Blanc(), Construit_Blanc(),
                  Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                     Construit_Blanc(), Construit_Blanc()),
                  Construit_Composee(
                      Construit_Blanc(), Construit_Blanc(), Construit_Blanc(),
                      Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                         Construit_Blanc(),
                                         Construit_Blanc()))),
              Construit_Noir())));
  if (HautMaxBlanc(img6) == 3) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  image img7 = Construit_Composee(
      Construit_Blanc(), Construit_Blanc(),
      Construit_Composee(
          Construit_Noir(), Construit_Noir(), Construit_Noir(),
          Construit_Composee(
              Construit_Blanc(),
              Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                                 Construit_Blanc(), Construit_Blanc()),
              Construit_Blanc(), Construit_Blanc())),
      Construit_Blanc());
  if (HautMaxBlanc(img7) == 2) {
    then printf("ok\n");
  } else {
    printf("ERREUR\n");
  }

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);
  Libere(img7);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*              BlanchitProfP                    */
/*                                               */
/*************************************************/

void BlanchitProfP(image *img, int p, int x, int y) {
  BlanchitProfPBis(img, Power(2, p), x, y);
}

void BlanchitProfPBis(image *img, int p, int x, int y) {
  if (p == 1) {
    then Libere(*img);
    *img = NULL;
  } else {
    int coord = 0;
    if (y <= p / 2 - 1)
      coord = 2;
    else
      y = y % (p / 2);
    if (x > p / 2 - 1) {
      coord += 1;
      x = x % (p / 2);
    }
    if (*img) {
      then if ((*img)->toutnoir) {
        then(*img)->toutnoir = FALSE;
        ((*img)->fils)[0] = Construit_Noir();
        ((*img)->fils)[1] = Construit_Noir();
        ((*img)->fils)[2] = Construit_Noir();
        ((*img)->fils)[3] = Construit_Noir();
      }
      BlanchitProfPBis(&(((*img)->fils))[coord], p / 2, x, y);
    }
  }
}

void test_blanchit_prof_p() {

  printf("---------------------------------------\n");
  printf("Test de BlanchitProfP\n\n");

  image img = Construit_Blanc();
  BlanchitProfP(&img, 0, 0, 0);
  printf("Doit afficher B: ");
  AffichageNorm(img);

  image img2 = Construit_Noir();
  BlanchitProfP(&img2, 0, 0, 0);
  printf("Doit afficher B: ");
  AffichageNorm(img2);

  image img3 = Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                  Construit_Noir(), Construit_Blanc());
  BlanchitProfP(&img3, 2, 1, 3);
  printf("Doit afficher ((NBNN)BNB): ");
  AffichageNorm(img3);

  image img4 = Construit_Composee(
      Construit_Composee(Construit_Noir(),
                         Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                            Construit_Noir(), Construit_Noir()),
                         Construit_Noir(), Construit_Noir()),
      Construit_Blanc(), Construit_Noir(), Construit_Blanc());
  BlanchitProfP(&img4, 2, 1, 3);
  printf("Doit afficher ((NBNN)BNB): ");
  AffichageNorm(img4);

  image img5 = Construit_Composee(
      Construit_Blanc(),
      Construit_Composee(
          Construit_Blanc(),
          Construit_Composee(
              Construit_Blanc(),
              Construit_Composee(Construit_Blanc(), Construit_Noir(),
                                 Construit_Blanc(), Construit_Blanc()),
              Construit_Noir(), Construit_Blanc()),
          Construit_Noir(), Construit_Blanc()),
      Construit_Noir(),
      Construit_Composee(Construit_Blanc(), Construit_Noir(),
                         Construit_Composee(Construit_Blanc(),
                                            Construit_Blanc(), Construit_Noir(),
                                            Construit_Blanc()),
                         Construit_Blanc()));
  BlanchitProfP(&img5, 3, 7, 7);
  printf("Doit afficher (B(B(BBNB)NB)N(BN(BBNB)B)): ");
  AffichageNorm(img5);

  image img6 = Construit_Composee(
      Construit_Blanc(),
      Construit_Composee(
          Construit_Blanc(),
          Construit_Composee(
              Construit_Blanc(),
              Construit_Composee(Construit_Blanc(), Construit_Noir(),
                                 Construit_Blanc(), Construit_Blanc()),
              Construit_Noir(), Construit_Blanc()),
          Construit_Noir(), Construit_Blanc()),
      Construit_Noir(),
      Construit_Composee(Construit_Blanc(), Construit_Noir(),
                         Construit_Composee(Construit_Blanc(),
                                            Construit_Blanc(), Construit_Noir(),
                                            Construit_Blanc()),
                         Construit_Blanc()));
  BlanchitProfP(&img6, 1, 1, 0);
  printf("Doit afficher (B(B(B(BNBB)NB)NB)NB): ");
  AffichageNorm(img6);

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*                   Chute                       */
/*                                               */
/*************************************************/

image Chute(image img) { return Construit_Blanc(); }

void test_chute() {

  printf("---------------------------------------\n");
  printf("Test de Chute\n\n");

  printf("----- ! Fonction pas encore implanter ! -----\n\n");

  image img = Construit_Blanc();
  image img2 = Chute(img);
  printf("Doit afficher B: ");
  AffichageNorm(img2);

  image img3 = Construit_Noir();
  image img4 = Chute(img3);
  printf("Doit afficher N: ");
  AffichageNorm(img4);

  image img5 = Construit_Composee(
      Construit_Noir(),
      Construit_Composee(Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                            Construit_Noir(), Construit_Noir()),
                         Construit_Noir(), Construit_Blanc(),
                         Construit_Composee(Construit_Blanc(), Construit_Noir(),
                                            Construit_Blanc(),
                                            Construit_Noir())),
      Construit_Composee(
          Construit_Noir(),
          Construit_Composee(Construit_Noir(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Noir()),
          Construit_Composee(Construit_Blanc(), Construit_Noir(),
                             Construit_Noir(), Construit_Noir()),
          Construit_Composee(Construit_Noir(), Construit_Blanc(),
                             Construit_Noir(), Construit_Blanc())),
      Construit_Composee(
          Construit_Noir(), Construit_Noir(),
          Construit_Composee(Construit_Noir(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Blanc()),
          Construit_Composee(Construit_Blanc(), Construit_Noir(),
                             Construit_Blanc(), Construit_Noir())));
  image img6 = Chute(img5);
  printf("Doit afficher "
         "(((BNNN)(BBNB)N(NBNN))(B(BNBN)(BBNB)(BNBN))N((NBNN)NNN)): ");
  AffichageNorm(img6);

  image img7 = Construit_Composee(
      Construit_Noir(),
      Construit_Composee(Construit_Noir(), Construit_Blanc(),
                         Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                            Construit_Noir(),
                                            Construit_Blanc()),
                         Construit_Blanc()),
      Construit_Composee(
          Construit_Blanc(), Construit_Noir(), Construit_Blanc(),
          Construit_Composee(Construit_Blanc(), Construit_Blanc(),
                             Construit_Blanc(), Construit_Noir())),
      Construit_Composee(
          Construit_Noir(),
          Construit_Composee(
              Construit_Blanc(),
              Construit_Composee(Construit_Noir(), Construit_Blanc(),
                                 Construit_Blanc(), Construit_Noir()),
              Construit_Blanc(), Construit_Noir()),
          Construit_Noir(), Construit_Noir()));
  image img8 = Chute(img7);
  printf("Doit afficher ((B(BBBN)BN)((NBNB)BNB)N(N(B(BBNN)BN)NN)): ");
  AffichageNorm(img8);

  Libere(img);
  Libere(img2);
  Libere(img3);
  Libere(img4);
  Libere(img5);
  Libere(img6);
  Libere(img7);
  Libere(img8);

  printf("\n----- ! Fonction pas encore implanter ! -----\n\n");

  printf("---------------------------------------\n");
}

/*************************************************/
/*                                               */
/*                    Main                       */
/*                                               */
/*************************************************/

int main(int argc, char **argv) {

  test_power();
  test_construit_couleur();
  test_affichages();
  // test_lecture();
  test_est_couleur();
  test_diagonale();
  test_quart_de_tour();
  test_negatif();
  test_simplifie_prof_p();
  test_incluse();
  test_haut_max_blanc();
  test_blanchit_prof_p();
  test_chute();

  return 0;
}
