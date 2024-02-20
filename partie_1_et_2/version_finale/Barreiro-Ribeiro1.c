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
/*                déclarations                   */
/*                                               */
/*************************************************/

double e();

double suite_xe(int n);

double power1(double x, long long int n);
double power1bis(double x, long long int n);
double power2a(double x, long long int n);
double power2b(double x, long long int n);
double power3(double x, long long int n);
void power3bis(double x, long long int n, double *r);
double power4(double x, long long int n);
double power4bis(double x, long long int n, double r);
double power5(double x, long long int n);
double power6(double x, long long int n);
double power7(double x, long long int n);
double power8(double x, long long int n);
double power8bis(double x, long long int n, double r);
double power9(double x, long long int n);
void power9bis(double x, long long int n, double *r);
double power10(double x, long long int n);

long ackermann_rec(int m, int n);
long ackermann_itrec(int m, int n);

double suite_xn_it(int n);
double suite_xn_rec(int n);
double suite_xn_rec_sf(int n);
double suite_xn_sf(int n, double res);
double suite_xn_rec_sp(int n);
void suite_xn_sp(int n, double *r);

/*************************************************/
/*                                               */
/*                calcul de e                    */
/*                                               */
/*************************************************/

double e() {
  double n = 1;
  double e = 2;
  for (int i = 2; (1 / n) > 0.00001; i++) {
    n *= i;
    e += (1 / n);
  }
  return e;
}

void test_e() {
  printf("---------------------------------------------------------------------"
         "---\n");
  printf("Test du calcul de e\n\n");

  printf("e est égal à %f\n", e());

  printf("---------------------------------------------------------------------"
         "---\n");
}

/*************************************************/
/*                                               */
/*                suite x0 = e - 1               */
/*                                               */
/*************************************************/

/**
 * Quand on utilise un float, a partir de x39 on a plus de valeur, on a -inf.
 * Ceci peut s'expliquer par le fait qu'un float a une precision limite, a
 * partir de x39 on a surement depasse cette valeur max. C'est pour cela que
 * lorsque qu'on utilise un double (qui a 2x plus de precision qu'un float) on
 * peut calculer au moins jusqu'a x49. De plus, à partir d'un certain rang (x23)
 * il n'y a plus de precision apres les virgules, en effet il n'y a plus que des
 * 0.
 **/
double suite_xe(int n) {
  double x = e() - 1;
  for (int i = 1; i <= n; i++) {
    x = i * x - 1;
  }
  return x;
}

void test_suite_xe() {
  printf("---------------------------------------------------------------------"
         "---\n");
  printf("Test de la suite_xe\n\n");

  for (int i = 0; i < 50; i++) {
    printf("x%d = %f\n", i, suite_xe(i));
  }

  printf("---------------------------------------------------------------------"
         "---\n");
}

/*************************************************/
/*                                               */
/*              power                            */
/*                                               */
/*************************************************/

double power1(double x, long long int n) {
  if (n < 0) {
    then if (x == 0) {
      then printf("division par 0 non defini, renvoi de 0 a la place");
      return 0;
    }
    else {
      x = 1 / x;
      n *= -1;
    }
  }
  return power1bis(x, n);
}

double power1bis(double x, long long int n) {
  if (n == 0) {
    then return 1;
  } else {
    return power1(x, n - 1) * x;
  }
}

double power2a(double x, long long int n) {
  if (n < 0) {
    then if (x == 0) {
      then printf("division par 0 non defini, renvoi de 0 a la place");
      return 0;
    }
    else {
      x = 1 / x;
      n *= -1;
    }
  }
  double r = 1;
  for (long i = 1; i <= n; i++) {
    r = r * x;
  }
  return r;
}

double power2b(double x, long long int n) {
  if (n < 0) {
    then if (x == 0) {
      then printf("division par 0 non defini, renvoi de 0 a la place");
      return 0;
    }
    else {
      x = 1 / x;
      n *= -1;
    }
  }
  double r = 1;
  while (n > 0) {
    r = r * x;
    n--;
  }
  return r;
}

double power3(double x, long long int n) {
  double r = 1;
  power3bis(x, n, &r);
  return r;
}

void power3bis(double x, long long int n, double *r) {
  if (n == 0) {
    then return;
  } else {
    *r = *r * x;
    power3bis(x, n - 1, r);
  }
}

double power4(double x, long long int n) { return power4bis(x, n, 1); }

double power4bis(double x, long long int n, double r) {
  if (n == 0) {
    then return r;
  } else {
    return power4bis(x, n - 1, r * x);
  }
}

double power5(double x, long long int n) {
  if (n == 0) {
    then return 1;
  } else {
    if (n % 2 == 0) {
      then return power5(x, n / 2) * power5(x, n / 2);
    } else {
      return power5(x, n / 2) * power5(x, n / 2) * x;
    }
  }
}

double power6(double x, long long int n) {
  if (n == 0) {
    then return 1;
  } else {
    double y = power6(x, n / 2);
    if (n % 2 == 0) {
      then return y * y;
    } else {
      return y * y * x;
    }
  }
}

double power7(double x, long long int n) {
  if (n == 0) {
    then return 1;
  } else {
    if (n % 2 == 0) {
      then return power7(x * x, n / 2);
    } else {
      return power7(x * x, n / 2) * x;
    }
  }
}

double power8(double x, long long int n) { return power8bis(x, n, 1); }

double power8bis(double x, long long int n, double r) {
  if (n == 0) {
    then return r;
  } else {
    if (n % 2 == 0) {
      then return power8bis(x * x, n / 2, r);
    } else {
      return power8bis(x * x, n / 2, r * x);
    }
  }
}

double power9(double x, long long int n) {
  double r = 1;
  power9bis(x, n, &r);
  return r;
}

void power9bis(double x, long long int n, double *r) {
  if (n == 0) {
    then return;
  } else {
    if (n % 2 == 1) {
      then *r = *r * x;
    }
    power9bis(x * x, n / 2, r);
  }
}

double power10(double x, long long int n) {
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
  printf("--------------------------------------------------------------------"
         "----\n");
  printf("Test des fonctions power\n\n");

  // Si pas de commentaire, alors resultat immediat

  // power1(0, -1);
  printf("%f\n", power1(-5, 7));
  printf("%f\n", power1(5, 7));

  printf("%f\n", power1((1 + 1. / 100), 100));
  printf("%f\n", power1((1 + 1. / 1000), 1000));
  printf("%f\n", power1((1 + 1. / 10000), 10000));

  // segmentation fault
  //  printf("%f\n", power1((1 + 1. / 1000000000), 1000000000));
  // segmentation fault
  // printf("%f\n", power1((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power1(-5, -5));

  // power2a(0, -1);
  printf("%f\n", power2a(-5, 7));
  printf("%f\n", power2a(5, 7));

  printf("%f\n", power2a((1 + 1. / 100), 100));
  printf("%f\n", power2a((1 + 1. / 1000), 1000));
  printf("%f\n", power2a((1 + 1. / 10000), 10000));

  // rame un peu
  // printf("%f\n", power2a((1 + 1. / 1000000000), 1000000000));
  // tourne sans donner de resultat
  // printf("%f\n", power2a((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power2a(-5, -5));

  // power2b(0, -1);
  printf("%f\n", power2b(-5, 7));
  printf("%f\n", power2b(5, 7));

  printf("%f\n", power2b((1 + 1. / 100), 100));
  printf("%f\n", power2b((1 + 1. / 1000), 1000));
  printf("%f\n", power2b((1 + 1. / 10000), 10000));

  // rame un peu
  // printf("%f\n", power2b((1 + 1. / 1000000000), 1000000000));
  // tourne sans donner de resultat
  // printf("%f\n", power2b((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power2b(-5, -5));

  printf("%f\n", power3((1 + 1. / 100), 100));
  printf("%f\n", power3((1 + 1. / 1000), 1000));
  printf("%f\n", power3((1 + 1. / 10000), 10000));

  // segmentation fault
  // printf("%f\n", power3((1 + 1. / 1000000000), 1000000000));
  // segmentation fault
  // printf("%f\n", power3((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power4((1 + 1. / 100), 100));
  printf("%f\n", power4((1 + 1. / 1000), 1000));
  printf("%f\n", power4((1 + 1. / 10000), 10000));

  // segmentation fault
  // printf("%f\n", power4((1 + 1. / 1000000000), 1000000000));
  // segmentation fault
  // printf("%f\n", power4((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power5((1 + 1. / 100), 100));
  printf("%f\n", power5((1 + 1. / 1000), 1000));
  printf("%f\n", power5((1 + 1. / 10000), 10000));

  // rame un peu
  // printf("%f\n", power5((1 + 1. / 1000000000), 1000000000));
  // tourne sans donner de resultat
  // printf("%f\n", power5((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power6((1 + 1. / 100), 100));
  printf("%f\n", power6((1 + 1. / 1000), 1000));
  printf("%f\n", power6((1 + 1. / 10000), 10000));

  printf("%f\n", power6((1 + 1. / 1000000000), 1000000000));
  printf("%f\n", power6((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power7((1 + 1. / 100), 100));
  printf("%f\n", power7((1 + 1. / 1000), 1000));
  printf("%f\n", power7((1 + 1. / 10000), 10000));

  printf("%f\n", power7((1 + 1. / 1000000000), 1000000000));
  printf("%f\n", power7((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power8((1 + 1. / 100), 100));
  printf("%f\n", power8((1 + 1. / 1000), 1000));
  printf("%f\n", power8((1 + 1. / 10000), 10000));

  printf("%f\n", power8((1 + 1. / 1000000000), 1000000000));
  printf("%f\n", power8((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power9((1 + 1. / 100), 100));
  printf("%f\n", power9((1 + 1. / 1000), 1000));
  printf("%f\n", power9((1 + 1. / 10000), 10000));

  printf("%f\n", power9((1 + 1. / 1000000000), 1000000000));
  printf("%f\n", power9((1 + 1. / 1000000000000), 1000000000000));

  printf("%f\n", power10((1 + 1. / 100), 100));
  printf("%f\n", power10((1 + 1. / 1000), 1000));
  printf("%f\n", power10((1 + 1. / 10000), 10000));

  printf("%f\n", power10((1 + 1. / 1000000000), 1000000000));
  printf("%f\n", power10((1 + 1. / 1000000000000), 1000000000000));

  /** En général, on peut observer que la suite (1 + 1/N)^N tend vers e.
   * Il ne semble pas y avoir d'opimisation de  la récursivité terminal, les
   * fonctions récursives terminal calculant x^n en mulitipliant x n fois avec
   * lui plante pour les mêmes puissances de 10 ( n >= 5) que les fonctions
   * récursives simples calculant de la même manière x^n
   **/

  printf("--------------------------------------------------------------------"
         "----\n");
}

/*************************************************/
/*                                               */
/*              Ackermann                        */
/*                                               */
/*************************************************/

long ackermann_rec(int m, int n) {
  if (m == 0) {
    then return n + 1;
  } else {
    if (n == 0) {
      then return ackermann_rec(m - 1, 1);
    } else {
      return ackermann_rec(m - 1, ackermann_rec(m, n - 1));
    }
  }
}

long ackermann_itrec(int m, int n) {
  if (m == 0) {
    then return n + 1;
  } else {
    long r = 1;
    for (int i = 1; i <= n + 1; i++) {
      r = ackermann_itrec(m - 1, r);
    }
    return r;
  }
}

void test_ackermann() {
  printf("---------------------------------------------------------------------"
         "---\n");
  printf("Test de la fonction Ackermann\n\n");
  // Si pas de commentaire, alors resultat immediat

  for (int i = 0; i <= 4; i++) {
    long res = ackermann_rec(i, 0);
    printf("A(%d,0)=%ld\n", i, res);
  }

  // A(5,0) rame
  // printf("A(%d,0)=%ld\n", 5, ackermann_rec(5, 0));

  // A(6,0) tourne sans donner de resultat
  // printf("A(%d,0)=%ld\n", 6, ackermann_rec(6, 0));

  for (int i = 0; i <= 4; i++) {
    long res = ackermann_itrec(i, 0);
    printf("A(%d,0)=%ld\n", i, res);
  }

  // A(5,0) rame un peu (moins qu'avec ackermann_rec)
  // printf("A(%d,0)=%ld\n", 5, ackermann_itrec(5, 0));

  // A(6,0) tourne sans donner de resultat
  // printf("A(%d,0)=%ld\n", 6, ackermann_itrec(6, 0));

  // La version itrec en plus efficace que la version rec. A(5,0) est calcule
  // plus rapidement avec itrec

  /** En laissant tourner on se rend compte que pour la version itero-recursif
   * A(6, 0) donne 'Process returned -1073741571 (0xC00000FD), ce qui signifie
   * qu'il y a un stack-overflow (Out-of-memory)
   **/

  printf("---------------------------------------------------------------------"
         "---\n");
}

/*************************************************/
/*                                               */
/*      Suite xn= xn-1 + 2 / xn-1                */
/*                                               */
/*************************************************/

double suite_xn_it(int n) {
  double x = 1;
  for (int i = 1; i <= n; i++) {
    x = x + (2 / x);
  }
  return x;
}

double suite_xn_rec(int n) {
  if (n == 0) {
    then return 1;
  } else {
    double cal = suite_xn_rec(n - 1);
    return cal + (2 / cal);
  }
}

double suite_xn_rec_sf(int n) { return suite_xn_sf(n, 1); }

double suite_xn_sf(int n, double res) {
  if (n == 0) {
    then return res;
  } else {
    return suite_xn_sf(n - 1, res + (2 / res));
  }
}

double suite_xn_rec_sp(int n) {
  double r = 1;
  suite_xn_sp(n, &r);
  return r;
}

void suite_xn_sp(int n, double *r) {
  if (n == 0) {
    then return;
  } else {
    *r = *r + (2 / *r);
    suite_xn_sp(n - 1, r);
  }
}

void test_suite_xn() {
  printf("---------------------------------------------------------------------"
         "---\n");
  printf("Test de la suite_xn\n\n");

  printf("X100 = %f\n", suite_xn_it(100));

  printf("X100 = %f\n", suite_xn_rec(100));

  printf("X100 = %f\n", suite_xn_rec_sf(100));

  printf("X100 = %f\n", suite_xn_rec_sp(100));

  printf("---------------------------------------------------------------------"
         "---\n");
}

/*************************************************/
/*                                               */
/*           main                                */
/*                                               */
/*************************************************/

int main(int argc, char **argv) {

  test_e();
  test_suite_xe();
  test_power();
  test_ackermann();
  test_suite_xn();

  return 0;
}
