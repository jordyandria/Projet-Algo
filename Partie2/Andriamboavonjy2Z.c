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
/*          definition type listeZ               */
/*                                               */
/*************************************************/

typedef struct BlocZ{
    struct BlocZ** prev;
    struct BlocZ* next;
    int nombre;
}BlocZ;

typedef struct ListeZ{
    BlocZ*** access;
}ListeZ;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVide(ListeZ *L){
    L -> access = NULL ;
}

bool estVide(ListeZ L){
    return L.access == NULL;
}

// cette fonction affiche la liste mais a l envers
void affiche(ListeZ L){

    if(estVide(L)){
        printf("[]");
    }

    else{  
        printf("[ ");
        BlocZ ***courant = L.access;
        courant = &(*(*courant))->prev;
        do{
            printf("%d ", (*(*courant)) -> next -> nombre);
            courant = &((*(*courant) ) -> next) -> prev;
        }while(*courant != (*(*L.access)) -> prev);
        printf("]");
    }
    

    printf("\n");

}



/*************************************************/
void ZAjouteAvant(int x, ListeZ *L){
    BlocZ *nouv = (BlocZ *)malloc(sizeof(BlocZ));
    nouv->nombre = x;
    
    if(estVide(*L)){
        nouv -> next = nouv;
        nouv -> prev = &(nouv->next);
        L -> access  =  &(nouv->prev);
    }

    else{
        nouv -> next = (*(*(*L->access)) -> prev ) -> next;
        nouv -> prev = &((*(*(*L->access)) -> prev) -> next);
        (*(*(*L -> access)) -> prev) -> next = nouv;
        nouv -> next -> prev = &(nouv -> next);
        L->access = &(nouv->prev);
    }

}


int main(int argc, char** argv){

    ListeZ L;
    initVide(&L);
    printf("Ma fonction pour l affichage affiche les listes a l envers\n");
    printf("Liste Vide : \n");
    affiche(L);
    ZAjouteAvant(42, &L);
    printf("Ajoute 42 :\n");
    affiche(L);
    ZAjouteAvant(93, &L);
    printf("Ajoute 93 :\n");
    affiche(L);
    ZAjouteAvant(17, &L);
    printf("Ajoute 17 :\n");
    affiche(L);
    ZAjouteAvant(20, &L);
    printf("Ajoute 20 :\n");
    affiche(L);
    return 0;
}
