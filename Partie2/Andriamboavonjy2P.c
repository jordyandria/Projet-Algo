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
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

int compteurMallocListe = 0;
int compteurMallocListeListes = 0;

void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    compteurMallocListe++;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
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

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}


/*************************************************/
/*                                               */
/*          Permutations                         */
/*                                               */
/*************************************************/

typedef struct ListeP {
    Liste p;
    struct ListeP *suivant;
} ListeP;

typedef ListeP *ListeListes;

void initVideP(ListeListes *LL){
    *LL = NULL;
}

bool estVideP(ListeListes LL){
    return LL == NULL;
}

Liste premierP(ListeListes LL){
    if(estVideP(LL)){
        return NULL;
    }
    else{
        return LL -> p;
    }
}

ListeListes suiteP(ListeListes LL){
    if(estVideP(LL)){
        return NULL;
    }
    else{
        return LL -> suivant;
    }
}

ListeListes ajouteP(Liste L, ListeListes LL){
    ListeListes tmp = (ListeListes)malloc(sizeof(ListeP));
    tmp -> p = L;
    tmp -> suivant = LL;
    compteurMallocListeListes++;
    return tmp;
}

void empileP(Liste L, ListeListes *LL){
    *LL = ajouteP(L, *LL);
}

void depileP(ListeListes *LL){
    ListeListes tmp = *LL;
    *LL = suiteP(*LL);
    free(tmp);
}

void VideListP(ListeListes *LL) {
    while (!estVideP(*LL)) {
        ListeListes tmp = *LL;
        *LL = suiteP(*LL);
        free(premierP(tmp)->suivant);
        free(tmp); 
    }
}

void affiche(Liste l){
    if(estVide(l))
        printf("");
    else
    {
        printf("%d ", premier(l));
        affiche(suite(l));
    }
}

void affiche_liste(Liste l){
    printf("[ ");
    affiche(l);
    printf("]");
}

void afficheP(ListeListes LL){
    printf("[ ");
    ListeListes LL2 = LL;
    while(NOT estVideP(LL2)){
        affiche_liste(premierP(LL2));
        printf(" ");
        LL2 = suiteP(LL2);
    }
    printf("]\n");
}

/*************************************************/
ListeListes AETTL(int x, ListeListes LL){
    ListeListes res;
    res = (ListeListes)malloc(sizeof(ListeP));
    compteurMallocListeListes++;
    initVideP(&res);

    if(estVideP(LL)){
        return res;
    }

    else{
        return ajouteP(ajoute(x, premierP(LL)), AETTL(x, suiteP(LL)));
    }
}

ListeListes ATP(int x, Liste L){
    ListeListes res;
    res = (ListeListes)malloc(sizeof(ListeP));
    compteurMallocListeListes++;
    initVide(&(res -> p));
    res -> suivant = NULL;

    if(estVide(L)){
        res -> p = ajoute(x, L);
        return res;
    }

    else{
        return ajouteP(ajoute(x, L), AETTL(premier(L), ATP(x, suite(L))));
    }

}

ListeListes Concat(ListeListes L1, ListeListes L2){
    if(estVideP(L1)){
        return L2;
    }

    else{
        return ajouteP(premierP(L1), Concat(suiteP(L1), L2));
    }

}

ListeListes ATLTP(int x, ListeListes LL){
    ListeListes res;
    res = (ListeListes)malloc(sizeof(ListeListes));
    compteurMallocListeListes++;
    initVideP(&res);

    if(estVideP(LL)){
        return res; 
    }

    else{
        return Concat (ATP(x, premierP(LL)), ATLTP(x, suiteP(LL)));
    }
}

ListeListes Permutations(int n){
    ListeListes res;
    res = (ListeListes)malloc(sizeof(ListeListes));
    compteurMallocListeListes++;
    initVide(&(res -> p));
    res -> suivant = NULL;
    
    if(n == 0){
        return res;
    }  

    else{
        return ATLTP(n, Permutations(n - 1));
    }

}



/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

int main(int argc, char** argv){
    //Test sur les ListeListes
    Liste liste1 = ajoute(1, ajoute(2, ajoute(3, NULL)));
    Liste liste2 = ajoute(4, ajoute(5, NULL));
    Liste liste3 = ajoute(6, ajoute(7, ajoute(8, NULL)));

    ListeListes LL = ajouteP(liste1, ajouteP(liste2, ajouteP(liste3, NULL)));
    printf("Test de ListeListes\n");
    afficheP(LL);
    printf("Nombre de malloc pour Liste : %d\n", compteurMallocListe);
    printf("Nombre de malloc pour ListeListes : %d\n", compteurMallocListeListes);
    VideListP(&LL);

    compteurMallocListe = 0;
    compteurMallocListeListes = 0;

    //Test Fonction Permutations
    printf("Test Permutations\n");
    LL = Permutations(3);
    afficheP(LL);
    printf("Nombre de malloc pour Liste : %d\n", compteurMallocListe);
    printf("Nombre de malloc pour ListeListes : %d\n", compteurMallocListeListes);


    return 0;
}