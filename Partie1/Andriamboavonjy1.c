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

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () { 
    float e = 1.0;
    int n = 1;
    float denom = 1.0;

    while(1){
        // Calcul de 1/n!
        float term = 1.0 / denom;

        // Condition d'arrêt de la boucle infinie
        if (term < 1e-12) break;  // Utiliser une valeur plus petite pour les double

        e += term;
        n++;

        denom *= n;
    
    }
    
      return e ; 
  }

/*************************************************/

double Edouble () { 
    double e = 1.0;
    int n = 1;
    double denom = 1.0;

    while(1){
        // Calcul de 1/n!
        double term = 1.0 / denom;

        // Condition d'arrêt de la boucle infinie
        if (term < 1e-15) break;  // Utiliser une valeur plus petite pour les double

        e += term;
        n++;
        
        denom *= n;
    
    }
      return e ; 
  }
  
/*************************************************/

// On a e = 0.000000
long double Elongdouble () {
    long double e = 1.0;
    int n = 1;
    long double term = 1.0;

    while (1) {
        // Calcul de 1/n!
        term /= n;

        // Condition d'arrêt de la boucle infinie
        if (term < 1e-25) break;  // Utiliser une valeur plus petite pour les long double

        e += term;
        n++;
    }
    
      return e ; 
    }

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

//  La suite ne converge vers 0 jusqu a y 9, elle remonte apres

void afficheYfloat (int n) {
  printf("Pour les float de la suite yn :\n");
  // Calcul de la valeur de e
  float e = Efloat();

  // Initialisation de y0 
  float yn = e - 1;  

  printf("y0 = %f\n", yn);

  for (int i = 1; i < n; i++) {
    yn = i * yn - 1;
    printf("y%d = %f\n", i, yn);
  }
  printf("\n");
}

/*************************************************/

//  La suite ne converge vers 0 jusqu a y 16, elle remonte apres
void afficheYdouble (int n) {
  printf("Pour les double de la suite yn :\n");
  // Calcul de la valeur de e
  double e = Edouble();

  // Initialisation de y0 
  double yn = e - 1;  

  printf("y0 = %lf\n", yn);

  for (int i = 1; i < n; i++) {
    yn = i * yn - 1;
    printf("y%d = %lf\n", i, yn);
  }
  printf("\n");
}

/*************************************************/

// Affiche toujours 0.000 a cause de Elongdouble()
void afficheYlongdouble (int n) {
  printf("Pour les long double de la suite yn :\n");
  // Calcul de la valeur de e
  long double e = Elongdouble();

  // Initialisation de y0 
  long double yn = e - 1;  

  printf("y0 = %Lf\n", yn);

  for (int i = 1; i < n; i++) {
    yn = i * yn - 1;
    printf("y%d = %Lf\n", i, yn);
  }
  printf("\n");
}


/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/


// ne depasse pas 10^4
double power1 (double x, long n) { 
  if (n == 0) then 
    return 1.0;
  else if (n > 0) then{
    return power1(x, n - 1) * x;
  }
  else
    // Cas ou n est negatif
    return 1.0 / power1(x, -n);
  }

/*************************************************/

// Lente : rame 10s en 9, puis un peu plus en 10

double power2a (double x, long n) { 
  if (x == 0.0 && n <= 0) {
        // Gestion du cas x = 0 et n <= 0 (0^0 ou division par zéro)
        return 1.0;
  }
  double r = 1.0;
  // n positif
  if (n > 0) then {
    for (int i = 0; i < n; i++){
      r *= x;
    }
  }
  
  // n negatif
  else {
    for (int i = 0; i < -n; i++) {
      r /= x;
    }
  }
  return r ; 
  }

/*************************************************/

// Lente : rame 10s en 9, puis un peu plus en 10

double power2b (double x, long n) {
 
  double r = 1.0;

  while (n > 0) {
    r *= x;
    n--;
  }

  return r; 
}

/*************************************************/

// Ne depasse pas N=10^4

void pow3(double x, int n, double *r) {
  if (n == 0) then
      return;
  else {
      *r *= x;
      pow3(x, n - 1, r);
  }
}

double power3 (double x, long n) { 
  double r = 1.0;
  pow3(x, n, &r);
  return r;
}

/*************************************************/

// ne depasse pas 10^4

double pow4(double x, int n, double r) {
  if (n == 0) then
   return r;
  else {
    return pow4(x, n - 1, r * x);
  }
}

double power4 (double x, long n) {
  return pow4(x, n, 1.0);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

// bien plus rapide et fonctionne du a la complexite reduite

double power6 (double x, long n) { 
  if (n == 0) then
    return 1.0;

  double y = power6(x, n / 2);

  if (n % 2 == 0) then
    return y * y;
  else {
    return y * y * x;
  }
}

/*************************************************/

// rapide et fonctionne

double power7 (double x, long n) {
  if (n == 0) then 
    return 1.0;
  else if (n % 2 == 0) then
      return power7(x * x, n / 2);
  else {
    return power7(x * x, n / 2) * x;
  }
}

/*************************************************/

// Optimisation de la recursivite terminale

double pow8(double x, int n, double r) {
  if (n == 0) then
    return r;
  else if (n % 2 == 0) then 
    return pow8(x * x, n / 2, r);
  else 
     return pow8(x * x, n / 2, r * x);
}

double power8 (double x, long n) { 
  return pow8(x, n, 1.0);
}

/*************************************************/

// Rapide et immediat

void pow9(double x, int n, double *r) {
  if (n == 0) then
     return;
  else if (n % 2 == 1) then
    *r *= x;

  pow9(x * x, n / 2, r);
}

double power9 (double x, long n) {
  double r = 1.0;
  pow9(x, n, &r);
  return r;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

// rend 0.000000
long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/


/*************************************************/
// ma fonction A1 fait un out of memory des A(5)

int A1(int m, int n) {
  if (m == 0) then
    return n + 1;
  else if (n == 0) then
    return A1(m - 1, 1);
  else
    return A1(m - 1, A1(m, n - 1));
}

int Ackermann1 (int m) { 
  return A1(m, 0);
}

/*************************************************/

// a A(6) tourne dans le vide
int A2(int m, int n) {
  if (m == 0) then
    return n + 1;
  else {
    int r = 1;
    for (int i = 1; i <= n + 1; i++) {
      r = A2(m - 1, r);
    }
    return r;
  }
}

int Ackermann2 (int m) { 
  return A2(m, 0);
}

/*************************************************/

// j ai un out of memory a A(5)
int A3(int m, int n){
  while (m > 0) {
    if (n == 0) then
      n = 1;
    else {
      n = A3(m, n - 1);
    }
    m--;
  }
  return n + 1;
}

int Ackermann3 (int m) { 
  return A3(m, 0);
}

/*************************************************/

int A4(int m, int n){

  int stack[100000];
  int result = n;
  int i = 0;
  stack[0] = m;
  
  while (1) {
  
    if (i < 0) {
      break;
    }
  
    if (stack[i] > 0 && result > 0) {
      stack[i + 1] = stack[i];
      stack[i]--;
      result--;
      i++;
    } 
    
    else if (stack[i] > 0 && result == 0) {
      stack[i]--;
      result = 1;
    } 
    
    else if (stack[i] == 0) {
      result++;
      i--;
    }

  }
  
  return result;

} 

int Ackermann4 (int m) {
  return A4(m, 0);
}

/*************************************************/

// pas vraiment d idee pour celle ci
int Ackermann5 (int m) { return 0 ; }

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : 
    // pour qu il affiche le reste comme il bloque a 5
    if(m == 5) then
      return 65533;
    return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : 
    // pour qu il affiche le reste comme il bloque a 5
    if(m == 5) then
      return 65533;
    return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}

/*************************************************/
/*                                               */
/*            Suite X                            */
/*                                               */
/*************************************************/

/************  Log 2 Entier   **************************/
int ln2(int n) {
  if (n == 1) then
    return 0;
  else 
    return 1 + ln2(n / 2);  
}

/*************************************************/
int Xiter(int n) {
  int xn = 2;
  
  if (n == 0) then
    return xn;
  else 
    while(n >= 1){
      xn = xn + ln2(xn);
      n--;
    } 

  return xn;
}

/*************************************************/
int Xrec(int n) {
  if (n == 0) then
    return 2;
  else {
    int xn = Xrec(n - 1);
    return xn + ln2(xn);
  }
}

/*************************************************/
int X2(int n, int xn){
  if (n == 0) then
    return xn;
  else
    return X2(n-1, xn + ln2(xn));
}

int Xrec2(int n){
  return X2(n, 2);
}

/*************************************************/
void X3(int n, int * xn){
  if(n == 0) then{
    *xn = 2;
  }
  else {
    X3(n - 1, xn);
    *xn = *xn + ln2(*xn);
  }
}

int Xrec3(int n){
  int xn;
  X3(n, &xn);
  return xn;
}

/*************************************************/
int AfficheX(int n, int i){
  switch (i)
  {
    case 1 : return Xiter(n);
    case 2 : return Xrec(n);
    case 3 : return Xrec2(n);
    case 4 : return Xrec3(n); 

    default: return 0;
  }
}


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (true) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (true) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (true) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (true) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        printf("\n");
        
}

if (true) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (true) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        printf("\n") ;
        
        for(i=1 ; i<=2 ; i++)
        printf("Power %d dit que power(-2,4) vaut %.5lf \n", i, power(-2,4,i) ) ;
        printf("\n") ;

        for(i=1 ; i<=2 ; i++)
        printf("Power %d dit que power(-2,-2) vaut %.5lf \n", i, power(-2,-2,i) ) ;
        printf("\n") ;
    
}

        
if (true) {  

        i=6 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (true) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
                
if (true) { 
 
        for(i=1 ; i<=5 ; i++)  // numéro de version
        
        // modifier a 4 pour que ca marche pour toute
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;

        printf("\n");
}

/******************    suite Xn     *******************************/
if (true) {
        
        printf("Pour la suite Xn : \n");
        for(i=1; i<=4 ; i++)

        printf("X%d(100) = %d\n", i, AfficheX(100, i));


}

/***********************************************************************/




  return 0;
}
