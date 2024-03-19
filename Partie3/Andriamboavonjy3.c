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
/*          definition type image                */
/*                                               */
/*************************************************/

typedef struct bloc_image{
    bool quatre;
    struct bloc_image *hg, *hd, *bg, *bd;
}bloc_image;

typedef bloc_image *image;

/*************************************************/
/*                                               */
/*         definitions pour la Pile              */
/*                                               */
/*************************************************/
typedef struct CharBlock {
    char data;
    struct CharBlock *next;
} CharBlock;

typedef CharBlock *CharStack;

void pushChar(CharStack *stack, char data) {
    CharBlock *newBlock = (CharBlock *)malloc(sizeof(CharBlock));
    newBlock->data = data;
    newBlock->next = *stack;
    *stack = newBlock;
}

char popChar(CharStack *stack) {
    CharBlock *temp = *stack;
    char data = temp->data;
    *stack = temp->next;
    free(temp);
    return data;
}

bool estVideChar(CharStack stack) {
    return stack == NULL;
}


/*************************************************/
/*                                               */
/*          Fonction et Procedures               */
/*                                               */
/*************************************************/

image Blanc(){
    image blanc = (image)malloc(sizeof(bloc_image));
    blanc->quatre = false;
    blanc->hg = NULL;
    blanc->hd = NULL;
    blanc->bg = NULL;
    blanc->bd = NULL;
    return blanc;
}

image Noir(){
    return NULL;
}

image Compose(image i0, image i1, image i2, image i3){
    image resultat = (image)malloc(sizeof(bloc_image));
    resultat->quatre = true;
    resultat->hg = i0;
    resultat->hd = i1;
    resultat->bg = i2;
    resultat->bd = i3;
    return resultat;
}

void Affichage(image i){
    if(i == NULL){
        printf("X");
    }
    else if(i->quatre == false){
        printf("o");
    }
    else{
        Affichage(i->hg);
        Affichage(i->hd);
        Affichage(i->bg);
        Affichage(i->bd);
        printf("*");
    }
}

void AffichageProfondeur(image i) {
    static int profondeur = 0;

    if (i == NULL) {
        printf("X%d ", profondeur);
    } 
    
    else if (i->quatre == false) {
        printf("o%d ", profondeur);
    } 
    
    else {
        
        profondeur++;
        AffichageProfondeur(i->hg);
        AffichageProfondeur(i->hd);
        AffichageProfondeur(i->bg);
        AffichageProfondeur(i->bd);
        profondeur--;
        printf("*%d ", profondeur);
        
    }
    
}

image BisLecture(CharStack *stack){
    if(!estVideChar(*stack)){
        char caractere = popChar(stack);

        if(caractere == 'X'){
            return Noir();
        }
        else if(caractere == 'o'){
            return Blanc();
        }
        else if(caractere == '*'){
            image bd = BisLecture(stack);
            image bg = BisLecture(stack);
            image hd = BisLecture(stack);
            image hg = BisLecture(stack);
            return Compose(hg, hd, bg, bd);
        }
    }
}


image Lecture() {

    CharStack stack = NULL;
    char caractere;

    while (caractere != '!') {
        caractere = getchar();

        if (caractere == 'X' || caractere == 'o' || caractere == '*') {
            pushChar(&stack, caractere);
        }
    }
    
    return BisLecture(&stack);
}


bool EstNoire(image i){
    if(i == NULL){
        return true;
    }
    else if(i->quatre == false){
        return false;
    }
    else{
        return EstNoire(i->hg) && EstNoire(i->hd) && EstNoire(i->bg) && EstNoire(i->bd);
    }
}

bool EstBlanc(image i){
    if(i == NULL){
        return false;
    }
    else if(i->quatre == false){
        return true;
    }
    else{
        return EstBlanc(i->hg) && EstBlanc(i->hd) && EstBlanc(i->bg) && EstBlanc(i->bd);
    }
}

float Aire(image i){
    if(i == NULL){
        return 1;
    }
    else if(i->quatre == false){
        return 0;
    }
    else{
        return 0.25*(Aire(i->hg)) + 0.25*(Aire(i->hd)) + 0.25*(Aire(i->bg)) + 0.25*(Aire(i->bd));
    }
}

image TriangleBD(int p){
    if(p == 0){
        return Blanc();
    }
    else if(p > 0){
        return Compose(Blanc(), TriangleBD(p-1), TriangleBD(p-1), Noir());
    }
}

void Arrondit(image *i, int p){
    if(((*i) != NULL) && ((*i) -> quatre == true)){
        if(p == 0){
            if(Aire(*i) >= 0.5){
                *i = Noir();
            }
            else{
                *i = Blanc();
            }
        }
        else {
            Arrondit(&((*i)->hg), p-1);
            Arrondit(&((*i)->hd), p-1);
            Arrondit(&((*i)->bg), p-1);
            Arrondit(&((*i)->bd), p-1);
        }
    }
}

bool MemeDessin(image i1, image i2){
    if((i1 == NULL) || (i2 == NULL)){
        if((i1 == NULL) && (i2 == NULL)){
            return true;
        }
        else if(i1 == NULL){
            return EstNoire(i2);
        }
        else{
            return EstNoire(i1);
        }
    }
    else if((i1->quatre == false) || (i2->quatre == false)){
        if((i1->quatre == false) && (i2->quatre == false)){
            return true;
        }
        else if(i1->quatre == false){
            return EstBlanc(i2);
        }
        else{
            return EstBlanc(i1);
        }
    }
    else{
        return (MemeDessin(i1->hg, i2->hg) && MemeDessin(i1->hd, i2->hd) && MemeDessin(i1->bg, i2->bg) && MemeDessin(i1->bd, i2->bd));
    }
}

void InterUnion(image *i1, image *i2){
    image tmp1 = *i1;
    image tmp2 = *i2;

    if((tmp1 == NULL) && (tmp2 != NULL)){
        if(tmp2->quatre == false){
            *i1 = Blanc();
            *i2 = Noir();
        }
        else if(tmp2->quatre == true){
            *i1 = tmp2;
            *i2 = tmp1;
        }
    }
    else if((tmp2 != NULL) && (tmp2->quatre == false)){
        *i1 = Blanc();
        *i2 = tmp1;
    }
    else if((tmp1 != NULL) && (tmp1->quatre == true) && (tmp2 != NULL)){
        InterUnion(&((*i1)->hg), &((*i2)->hg));
        InterUnion(&((*i1)->hd), &((*i2)->hd));
        InterUnion(&((*i1)->bg), &((*i2)->bg));
        InterUnion(&((*i1)->bd), &((*i2)->bd));
    }
}

bool EstDamier(image i){
    if((i != NULL) && (i->quatre == true)){
        if((i->hg->quatre == false) && (i->hd == NULL) && (i->bg == NULL) && (i->bd->quatre == false)){
            return true;
        }
        else{
            return EstDamier(i->hg) && EstDamier(i->hd) && EstDamier(i->bg) && EstDamier(i->bd);
        }
    }
    else{
        return false;
    }
}

int CompteDamiers(image i){
    if((i == NULL) || (i->quatre == false)){
        return 0;
    }
    else if(!(EstDamier(i))){
        return 0;
    }
    else if(EstDamier(i)){
        return 1 + CompteDamiers(i->hg) + CompteDamiers(i->hd) + CompteDamiers(i->bg) + CompteDamiers(i->bd);
    }
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

int main(int argc, char *argv[]){

    // image i1 = Compose(Noir(),Blanc(),Noir(),Noir());
    // image i2 = Compose(Noir(),Noir(),Blanc(),i1);
    // image i3 = Compose(Noir(),i2,Blanc(),Noir());
    // image i4 = Compose(Blanc(),Blanc(),Noir(),Blanc());
    // image i = Compose(Noir(),i4,Blanc(),i3);
    // Affichage(i);
    // printf("\n");
    // AffichageProfondeur(i);

    // image i = Lecture();
    // Affichage(i);
    // printf("\n");
    // AffichageProfondeur(i);
    // printf("\n");
    // printf("%d\n",EstNoire(i));
    // printf("%d\n",EstBlanc(i));
    // printf("%.3f\n",Aire(i));
    // image t = TriangleBD(3);
    // Affichage(t);

    // image a = Lecture();
    // Affichage(a);
    // printf("\n");
    // Arrondit(&a, 2);
    // Affichage(a);

    // image i1 = Lecture();
    // Affichage(i1);
    // printf("\n");
    // int c;
    // while ((c = getchar()) != EOF && c != '\n');

    // image i2 = Lecture();
    // Affichage(i2);
    // printf("\n");
    // printf("%d\n", MemeDessin(i1,i2));

    // image i1 = Lecture();
    // Affichage(i1);
    // printf("\n");
    // int c;
    // while ((c = getchar()) != EOF && c != '\n');

    // image i2 = Lecture();
    // Affichage(i2);
    // printf("\n");
    // InterUnion(&i1, &i2);
    // Affichage(i1);
    // printf("\n");
    // Affichage(i2);

    image i = Lecture();
    Affichage(i);
    printf("\n");
    printf("%d\n", EstDamier(i));
    printf("%d\n", CompteDamiers(i));
    
    return 0;
}
