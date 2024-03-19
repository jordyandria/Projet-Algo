

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
/*       UnPlusDeuxEgalTrois                     */
/*                                               */
/*************************************************/

bool UnPlusDeuxEgalTrois(Liste L){

    if (estVide(L)) then
        return true;

    else{

        if(!estVide(suite(L))) then {
            Liste L2 = suite(L);

            if(!estVide(suite(L2))) then {
                return premier(suite(L2)) == premier(L) + premier(L2);
            }

            else {
                return premier(L2) + premier(L) == 0;
            }

        }

        else {
            return premier(L) == 0;
        }

    }
}

/*************************************************/
// Affichage pour la fonction UnPlusDeuxEgalTrois
void UPDET(Liste L){
    if (UnPlusDeuxEgalTrois(L)){
        printf("UnPlusDeuxEgalTrois est vrai\n\n");
    }
    else{
        printf("UnPlusDeuxEgalTrois est faux\n\n");
    }
}

/*************************************************/
/*                                               */
/*          Croissante                           */
/*                                               */
/*************************************************/

bool Croissante(Liste L){
    if (estVide(L)) then
        return true;
    else
        // ici on demande strictement croissante alors plusieurs elements a la suite ne peuvent etre egaux
        if( (!estVide(suite(L))) AND (premier(L) >= premier(suite(L))) )then 
            return false;
        else
            return Croissante(suite(L));
}

/*************************************************/
void AfficheCroissante(Liste L){
   if (Croissante(L)){
        printf("La liste est croissante\n\n");
    }
    else{
        printf("La liste n est pas strictement croissante\n\n");
    } 
}

/*************************************************/
/*                                               */
/*          NombreMemePosition                   */
/*                                               */
/*************************************************/

/********Version Rec non terminale****************/
int NombreMemePosition1(Liste L1, Liste L2){
    if (estVide(L1) OR estVide(L2)) then
        return 0;
    else
        if (premier(L1) == premier(L2)) then
            return 1 + NombreMemePosition1(suite(L1), suite(L2));
        else
            return NombreMemePosition1(suite(L1), suite(L2));
}

/*********Version iterative***********************/
int NombreMemePosition2(Liste L1, Liste L2){
    int cpt = 0;
    Liste l1 = L1;
    Liste l2 = L2;
    while ((!estVide(l1)) AND !estVide(l2)) {
        if (premier(l1) == premier(l2)) then 
           cpt++;
        l1 = suite(l1);
        l2 = suite(l2);
    }
    return cpt;
}

/****Version avec sous-fonction rec terminale*****/
int NMP3(Liste L1, Liste L2, int n){
    if (estVide(L1) OR estVide(L2)) then
        return n;
    else
        if (premier(L1) == premier(L2)) then
            return NMP3(suite(L1), suite(L2), n+1);
        else
            return NMP3(suite(L1), suite(L2), n);
}

int NombreMemePosition3(Liste L1, Liste L2){
    return NMP3(L1, L2, 0);
}

/***Version avec sous-procedure rec terminale*****/
void NMP4(Liste L1, Liste L2, int *n){
    if (!estVide(L1) AND !estVide(L2)) then {
        if (premier(L1) == premier(L2)) then
            (*n)++;
        NMP4(suite(L1), suite(L2), n);
    }
}

int NombreMemePosition4(Liste L1, Liste L2){
    int n = 0;
    NMP4(L1, L2, &n);
    return n;
}


/*************************************************/
int NombreMemePosition(Liste L1, Liste L2, int i){
    switch (i)
    {
    case 1 : return NombreMemePosition1(L1, L2);
    case 2 : return NombreMemePosition2(L1, L2);
    case 3 : return NombreMemePosition3(L1, L2);
    case 4 : return NombreMemePosition4(L1, L2);
    
    default: return 0;
    }
}

/*************************************************/
/*                                               */
/*          FonctVireDernier                     */
/*                                               */
/*************************************************/

/********Version Rec non terminale****************/
Liste FonctVireDernier1(Liste L) {
    if (estVide(L) OR estVide(suite(L))) then {
        Liste LL;
        initVide(&LL);
        return LL;
    } else {
        return ajoute(premier(L), FonctVireDernier1(suite(L)));
    }
}

/*********Version iterative***********************/
Liste FonctVireDernier2(Liste L){
    Liste LL;
    initVide(&LL);
    
    if (estVide(L)) then
        return LL;

    Liste *copie, *P;
    copie = &L;
    P = &LL;
    while(NOT estVide(suite(*copie))){
        empile(premier(*copie),P);
        copie = &(*copie) -> suivant;
        P = &(*P) -> suivant;
    }

    return LL;
}

/*************************************************/
Liste FonctVireDernier(Liste L, int i){
    switch(i){
        case 1 : return FonctVireDernier1(L);
        case 2 : return FonctVireDernier2(L);
        default : return NULL;
    }
}

/*************************************************/
/*                                               */
/*       AjouteDevantPremierZero                 */
/*                                               */
/*************************************************/

void AjouteDevantPremierZero(Liste *L, int x){

    if(estVide(*L)){
        empile(x, L);
    }
    else{
        if(premier(*L) == 0){
            empile(x, L);
        }
        else{
            AjouteDevantPremierZero(&(*L) -> suivant, x);
        }
    }
}

/*************************************************/
/*                                               */
/*       AjouteDevantDernierZero                 */
/*                                               */
/*************************************************/

/********Version Rec avec arg out*****************/

void ADDZ1 (Liste *L, int x, bool *vu){

    if(NOT estVide(*L)){
        if (premier(*L) == 0){
            *vu = true;
        }

        ADDZ1(&(*L) -> suivant, x, vu);
        if(premier(*L) == 0 AND *vu){
            *vu = false;
            empile(x, L);
        }
        
    }
    
    else{
        if (NOT *vu){
            empile(x, L);
        }
    }

}

void AjouteDevantDernierZeroRec1(Liste *L, int x){
    bool vu = false;
    ADDZ1(L, x, &vu);
}


/********Version Rec terminale********************/
void ADDZ2 (Liste *L, int x, Liste *M){
    if (estVide(*L)) {
        if(NOT estVide(*M)) then
            empile(x, M);
        else
            empile(x, L);
    }
    else{
        if (premier(*L) == 0) then
            ADDZ2(&(*L) -> suivant, x, L);
        else
            ADDZ2(&(*L) -> suivant, x, M);
    }
}

void AjouteDevantDernierZeroRec2(Liste *L, int x){
    Liste M;
    initVide(&M);
    ADDZ2(L, x, &M);
}

/*********Version iterative***********************/
void AjouteDevantDernierZeroIter(Liste *L, int x){
    Liste *P;
    P = L;
    Liste *M;
    M = NULL;
    while(NOT estVide(*P)){
        if(premier(*P) == 0) then
            M = P;
        P = &(*P) -> suivant;
    }
    if (M != NULL) then
        empile(x, M);
    else{
        empile(x, P);
    }
}

/*************************************************/
void AjouteDevantDernierZero(Liste *L, int x, int i){
    switch (i)
    {
        case 1: AjouteDevantDernierZeroRec1(L, x); break;
        case 2: AjouteDevantDernierZeroRec2(L, x); break;
        case 3: AjouteDevantDernierZeroIter(L, x); break;
        default : break;
    }
} 


/*************************************************/
/*                                               */
/*                   Tic                         */
/*                                               */
/*************************************************/

void Tic(Liste *L){
    if(NOT estVide(*L)){
        if(NOT estVide(suite(*L))){
            if((premier(*L) == 0) AND (premier(suite(*L)) == 0)){
                depile(L);
                Tic(L);
            }
            else if((premier(*L) == 0) AND (premier(suite(*L)) != 0)) then
                depile(L);
            else if(premier(*L) != 0){
                empile(0, L);
                Tic(&(*L) -> suivant -> suivant);
            }
        }
        else{
            if(premier(*L) == 0)
                depile(L);
            else{
                empile(0, L);
            }
        }
    }
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
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
    printf("]\n");
}

int main(int argc, char** argv)
{

    if(false){
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);

    }


/********* UnPlusDeuxEgalTrois *******************/

    if(true){

        printf("/*************************************************/\n");

        printf("Test fonction UnPlusDeuxEgalTrois\n\n");

        Liste l1;
        initVide(&l1);
        empile(29, &l1);
        empile(4, &l1);
        empile(8, &l1);
        empile(5, &l1);
        empile(3, &l1);
        affiche_liste(l1);
        UPDET(l1);

        Liste l2;
        initVide(&l2);
        empile(-2, &l2);
        empile(2, &l2);
        affiche_liste(l2);
        UPDET(l2);

        Liste l3;
        initVide(&l3);
        affiche_liste(l3);
        UPDET(l3);

        Liste l4;
        initVide(&l4);
        empile(1, &l4);
        empile(7, &l4);
        empile(3, &l4);
        empile(2, &l4);
        affiche_liste(l4);
        UPDET(l4);

        Liste l5;
        initVide(&l5);
        empile(2, &l5);
        empile(2, &l5);
        affiche_liste(l5);
        UPDET(l5);

    }

/*************** Croissante **********************/

    if(true){

        printf("/*************************************************/\n");

        printf("Test fonction Croissante\n\n");

        Liste l1;
        initVide(&l1);
        empile(5, &l1);
        empile(4, &l1);
        empile(3, &l1);
        empile(2, &l1);
        empile(1, &l1);
        affiche_liste(l1);
        AfficheCroissante(l1);

        Liste l2;
        initVide(&l2);
        empile(8, &l2);
        empile(6, &l2);
        empile(4, &l2);
        empile(2, &l2);
        empile(0, &l2);
        affiche_liste(l2);
        AfficheCroissante(l2);

        Liste l3;
        initVide(&l3);
        empile(-1, &l3);
        empile(-2, &l3);
        empile(-3, &l3);
        empile(-4, &l3);
        empile(-5, &l3);
        affiche_liste(l3);
        AfficheCroissante(l3);

        Liste l4;
        initVide(&l4);
        empile(5, &l4);
        empile(4, &l4);
        empile(4, &l4);
        empile(3, &l4);
        empile(2, &l4);
        empile(1, &l4);
        empile(1, &l4);
        affiche_liste(l4);
        AfficheCroissante(l4);

        Liste l5;
        initVide(&l5);
        empile(1, &l5);
        empile(1, &l5);
        empile(2, &l5);
        empile(3, &l5);
        empile(3, &l5);
        empile(4, &l5);
        empile(5, &l5);
        affiche_liste(l5);
        AfficheCroissante(l5);

        Liste l6;
        initVide(&l6);
        empile(5, &l6);
        empile(2, &l6);
        empile(4, &l6);
        empile(3, &l6);
        empile(1, &l6);
        empile(2, &l6);
        affiche_liste(l6);
        AfficheCroissante(l6);
    
    }

/*********** NombreMemePosition ******************/

    if(true){

        printf("/*************************************************/\n");

        printf("Test fonction NombreMemePosition\n\n");

        Liste l1, l2, l3, l4;

        initVide(&l1);
        empile(2, &l1);
        empile(9, &l1);
        empile(2, &l1);
        empile(4, &l1);
        empile(3, &l1);
        empile(0, &l1);
        empile(9, &l1);
        empile(6, &l1);
        empile(3, &l1);

        initVide(&l2);
        empile(5, &l2);
        empile(2, &l2);
        empile(2, &l2);
        empile(2, &l2);
        empile(2, &l2);
        empile(2, &l2);
        empile(2, &l2);
        empile(2, &l2);
        empile(0, &l2);
        empile(6, &l2);
        empile(9, &l2);
        empile(3, &l2);

        printf("L1 : ");
        affiche_liste(l1);
        printf("L2 : ");
        affiche_liste(l2);

        for(int i = 1; i <= 4; i++){
            printf("NombreMemePosition%d(L1,L2) = %d\n", i, NombreMemePosition(l1, l2, i));
        }

        printf("\n");

        initVide(&l3);
        empile(5, &l3);
        empile(2, &l3);
        empile(2, &l3);
        empile(2, &l3);
        empile(2, &l3);
        empile(9, &l3);
        empile(2, &l3);
        empile(4, &l3);
        empile(3, &l3);
        empile(0, &l3);
        empile(9, &l3);
        empile(6, &l3);
        empile(3, &l3);

        initVide(&l4);
        empile(2, &l4);
        empile(9, &l4);
        empile(4, &l4);
        empile(3, &l4);
        empile(2, &l4);
        empile(2, &l4);
        empile(2, &l4);
        empile(2, &l4);

        printf("L3 : ");
        affiche_liste(l3);
        printf("L4 : ");
        affiche_liste(l4);

        for(int i = 1; i <= 4; i++){
            printf("NombreMemePosition%d(L3,L4) = %d\n", i, NombreMemePosition(l3, l4, i));
        }

        printf("\n");

        VideListe(&l4);
        printf("L3 : ");
        affiche_liste(l3);
        printf("L4 : ");
        affiche_liste(l4);

        for(int i = 1; i <= 4; i++){
            printf("NombreMemePosition%d(L3,L4) = %d\n", i, NombreMemePosition(l3, l4, i));
        }

        printf("\n");


    }

/*************FonctVireDernier********************/

    if(true){

        printf("/*************************************************/\n");

        printf("Test fonction FonctVireDernier\n\n");

        Liste l1, l2, l3, l4;

        initVide(&l1);
        empile(2, &l1);
        empile(9, &l1);
        empile(2, &l1);
        empile(4, &l1);
        empile(3, &l1);
        empile(0, &l1);
        empile(9, &l1);
        empile(6, &l1);
        empile(3, &l1);

        initVide(&l2);

        initVide(&l3);
        empile(4, &l3);

        initVide(&l4);
        empile(4, &l4);
        empile(0, &l4);

        printf("L1 : \n");
        affiche_liste(l1);

        for(int i = 1; i <= 2; i++){
            printf("FonctVireDernier%d(L1) = \n", i);
            affiche_liste(FonctVireDernier(l1, i));
        }

        printf("\n");

        printf("L2 : \n");
        affiche_liste(l2);
        for(int i = 1; i <= 2; i++){
            printf("FonctVireDernier%d(L2) : \n", i);
            affiche_liste(FonctVireDernier(l2, i));
        }

        printf("\n");

        printf("L3 : \n");
        affiche_liste(l3);
        for(int i = 1; i <= 2; i++){
            printf("FonctVireDernier%d(L3) : \n", i);
            affiche_liste(FonctVireDernier(l3, i));
        }

        printf("\n");

        printf("L4 : \n");
        affiche_liste(l4);
        for(int i = 1; i <= 2; i++){
            printf("FonctVireDernier%d(L4) : \n", i);
            affiche_liste(FonctVireDernier(l4, i));
        }

        printf("\n");

    }

/**********AjouteDevantPremierZero****************/

    if(true){

        printf("/*************************************************/\n");

        printf("Test de la fonction AjouteDevantPremierZero \n\n");

        int x = 11;

        Liste l1;
        initVide(&l1);
        empile(1, &l1);
        empile(0, &l1);
        empile(8, &l1);
        empile(0, &l1);
        empile(5, &l1);
        empile(0, &l1);
        empile(4, &l1);
        printf("L1 : \n");
        affiche_liste(l1);
        printf("AjouteDevantPremierZero(L1,%d) : \n", x);
        AjouteDevantPremierZero(&l1,x);
        affiche_liste(l1);

        printf("\n");
        
        Liste l2;
        initVide(&l2);
        empile(1, &l2);
        empile(3, &l2);
        empile(2, &l2);
        empile(5, &l2);
        empile(9, &l2);
        empile(4, &l2);
        printf("L2 : \n");
        affiche_liste(l2);
        printf("AjouteDevantPremierZero(L2,%d) : \n", x);
        AjouteDevantPremierZero(&l2,x);
        affiche_liste(l2);

        printf("\n");

        Liste l3; 
        initVide(&l3);
        printf("L3 : \n");
        affiche_liste(l3);
        printf("AjouteDevantPremierZero(L3,%d) : \n", x);
        AjouteDevantPremierZero(&l3,x);
        affiche_liste(l3);
        printf("\n");

        Liste l4;
        initVide(&l4);
        empile(1, &l4);
        empile(0, &l4);
        empile(8, &l4);
        empile(0, &l4);
        empile(5, &l4);
        empile(0, &l4);
        printf("L4 : \n");
        affiche_liste(l4);
        printf("AjouteDevantPremierZero(L4,%d) : \n", x);
        AjouteDevantPremierZero(&l4,x);
        affiche_liste(l4);

        printf("\n");

    }

/**********AjouteDevantDernierZero****************/

    if(true){
        
        printf("/*************************************************/\n");

        printf("Test de la fonction AjouteDevantDernierZero \n\n");
    
        int x = 11;
        Liste l1;
        initVide(&l1);
        empile(1, &l1);
        empile(0, &l1);
        empile(8, &l1);
        empile(0, &l1);
        empile(5, &l1);
        empile(0, &l1);
        empile(4, &l1);
        printf("L1 : \n");
        affiche_liste(l1);
        for(int i = 1; i<=3; i++){
            printf("AjouteDevantDernierZero%d(L1,%d) : \n", i, x);
            AjouteDevantDernierZero(&l1, x, i);
            affiche_liste(l1);
            VideListe(&l1);
            empile(1, &l1);
            empile(0, &l1);
            empile(8, &l1);
            empile(0, &l1);
            empile(5, &l1);
            empile(0, &l1);
            empile(4, &l1);
        }

        printf("\n");

        Liste l2;
        initVide(&l2);
        empile(1, &l2);
        empile(3, &l2);
        empile(2, &l2);
        empile(5, &l2);
        empile(9, &l2);
        empile(4, &l2);
        printf("L2 : \n");
        affiche_liste(l2);
        for(int i = 1; i<=3; i++){
            printf("AjouteDevantDernierZero%d(L2,%d) : \n", i, x);
            AjouteDevantDernierZero(&l2, x, i);
            affiche_liste(l2);
            VideListe(&l2);
            empile(1, &l2);
            empile(3, &l2);
            empile(2, &l2);
            empile(5, &l2);
            empile(9, &l2);
            empile(4, &l2);
        }

        printf("\n");

        Liste l3; 
        initVide(&l3);
        printf("L3 : \n");
        affiche_liste(l3);
        for(int i = 1; i<=3; i++){
            printf("AjouteDevantDernierZero%d(L3,%d) : \n", i, x);
            AjouteDevantDernierZero(&l3, x, i);
            affiche_liste(l3);
            VideListe(&l3);
        }

        printf("\n");

        Liste l4;
        initVide(&l4);
        empile(0, &l4);
        empile(8, &l4);
        empile(0, &l4);
        empile(5, &l4);
        empile(0, &l4);
        printf("L4 : \n");
        affiche_liste(l4);
        for(int i = 1; i<=3; i++){
            printf("AjouteDevantDernierZero%d(L4,%d) : \n", i, x);
            AjouteDevantDernierZero(&l4, x, i);
            affiche_liste(l4);
            VideListe(&l4);
            empile(0, &l4);
            empile(8, &l4);
            empile(0, &l4);
            empile(5, &l4);
            empile(0, &l4);
        }

        printf("\n");

    }

/*********************Tic*************************/

    if(true){

        printf("/*************************************************/\n");

        printf("Test fonction Tic\n\n");

        Liste l1;
        initVide(&l1);
        empile(1, &l1);
        empile(2, &l1);
        empile(0, &l1);
        empile(0, &l1);
        empile(9, &l1);
        empile(8, &l1);
        empile(0, &l1);
        empile(0, &l1);
        empile(0, &l1);
        empile(2, &l1);
        empile(7, &l1);
        empile(3, &l1);
        printf("L1 : \n");
        affiche_liste(l1);
        printf("Tic(L1) : \n");
        Tic(&l1);
        affiche_liste(l1);

        printf("\n");

        Liste l2;
        initVide(&l2);
        empile(1, &l2);
        empile(1, &l2);
        empile(2, &l2);
        empile(9, &l2);
        empile(8, &l2);
        empile(2, &l2);
        empile(7, &l2);
        empile(3, &l2);
        printf("L2 : \n");
        affiche_liste(l2);
        printf("Tic(L2) : \n");
        Tic(&l2);
        affiche_liste(l2);

        printf("\n");

        Liste l3;
        initVide(&l3);
        empile(1, &l3);
        empile(1, &l3);
        empile(2, &l3);
        empile(9, &l3);
        empile(8, &l3);
        empile(2, &l3);
        empile(7, &l3);
        empile(3, &l3);
        empile(0, &l3);
        empile(0, &l3);
        empile(0, &l3);
        empile(0, &l3);
        empile(0, &l3);
        printf("L3 : \n");
        affiche_liste(l3);
        printf("Tic(L3) : \n");
        Tic(&l3);
        affiche_liste(l3);

        printf("\n");
        Liste l4;
        initVide(&l4);
        empile(0, &l4);
        empile(0, &l4);
        empile(0, &l4);
        empile(0, &l4);
        empile(1, &l4);
        empile(1, &l4);
        empile(2, &l4);
        empile(9, &l4);
        empile(8, &l4);
        empile(2, &l4);
        empile(7, &l4);
        empile(3, &l4);
        printf("L4 : \n");
        affiche_liste(l4);
        printf("Tic(L4) : \n");
        Tic(&l4);
        affiche_liste(l4);

        printf("\n");

        Liste l5;
        initVide(&l5);
        printf("L5 : \n");
        affiche_liste(l5);
        printf("Tic(L5) : \n");
        Tic(&l5);
        affiche_liste(l5);

        printf("\n");

        Liste l6;
        initVide(&l6);
        empile(0, &l6);
        printf("L6 : \n");
        affiche_liste(l6);
        printf("Tic(L6) : \n");
        Tic(&l6);
        affiche_liste(l6);

        printf("\n");

        Liste l7;
        initVide(&l7);
        empile(2, &l7);
        printf("L7 : \n");
        affiche_liste(l7);
        printf("Tic(L7) : \n");
        Tic(&l7);
        affiche_liste(l7);

        printf("\n");

        Liste l8;
        initVide(&l8);
        empile(1, &l8);
        empile(0, &l8);
        empile(1, &l8);
        empile(0, &l8);
        empile(2, &l8);
        empile(0, &l8);
        empile(9, &l8);
        empile(0, &l8);
        empile(8, &l8);
        empile(0, &l8);
        empile(2, &l8);
        empile(0, &l8);
        empile(7, &l8);
        empile(0, &l8);
        empile(3, &l8);
        empile(0, &l8);
        printf("L8 : \n");
        affiche_liste(l8);
        printf("Tic(L8) : \n");
        Tic(&l8);
        affiche_liste(l8);

        printf("\n");

        Liste l9;
        initVide(&l9);
        empile(0, &l9);
        empile(0, &l9);
        empile(0, &l9);
        empile(0, &l9);
        empile(0, &l9);
        empile(0, &l9);
        printf("L9 : \n");
        affiche_liste(l9);
        printf("Tic(L9) : \n");
        Tic(&l9);
        affiche_liste(l9);

        printf("\n");
    }



/*************************************************/

    return 0;
}





