#include <stdio.h>
void menu(){
    void ajouter_article();
    void supprimer_article();
    void historique();

    int a;
    printf(" veuillez choisir s il vous plait : \nsi vous voulez ajouter un article===>1 \nsi vous voulez supprimer un article===2\nsi vous vouler voir l historique===>3\n" ) ;
    scanf("%d", &a) ;
    if ((a!=1)&&(a!=2)&&(a!=3)){
        printf("votre choix est incorrect, veuillez repeter l operation\n" );
//on supprime la page dans cmd
        menu() ;}
    else {
        if (a==1) {ajouter_article();}
        else {
            if (a==2){supprimer_article();}
            else {historique();}
        }
    }
} 

void ajouter_article(){
    void article_achete();
    void article_vendu();
    int b,c;
    printf( "veuillez choisir s il vous plaît  le type de transaction : \nsi vous voulez ajouter un article achete ===>1 \nsi vous voulez ajouter un article vendu ===2" ) ;
    scanf("%d", &b) ;
    if ((b!=1)&& (b!=2)){
        printf("votre choix est incorrect. \n si vous voulez repeter l operation tapez ===>1\n si vous voulez retourner au menu tapez ===>2 ");
        scanf("%d",&c);
        if (c==1){ ajouter_article();}
        else {
            if ( c==2){menu();}
            else printf("choix invalide");
        }
    }
    else {
        if (b==1){ article_achete();}
        else {article_vendu();}
    }
}
void supprimer_article(){
    printf("supprimer");
}
void article_achete(){
    printf("achete");
}
void article_vendu(){
    printf("vendu");
}
void historique(){
    printf("historique");
}
int main(){
    void menu();
    menu();
return 0;
}