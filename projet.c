#include <stdio.h>
void menu(){
    void produits_en_stock();
    void ajouter_produit();
    void supprimer_produit();
    void historique();
    void rechercher_produit();
    void modifier_produit();
    void description_produit(char nom_produit[20]);
    int a;
    printf(" veuillez choisir s il vous plait : \nsi vous voulez ajouter un produit===>1 \nsi vous voulez supprimer un produit===2\nsi vous vouler voir l historique===>3\n" ) ;
    scanf("%d", &a) ;
    if ((a!=1)&&(a!=2)&&(a!=3)){
        printf("votre choix est incorrect, veuillez repeter l operation\n" );
//on supprime la page dans cmd
        menu() ;}
    else {
        if (a==1) {ajouter_produit();}
        else {
            if (a==2){supprimer_produit();}
            else {historique();}
        }
    }
} 

void ajouter_produit(){
    void produit_achete();
    void produit_vendu();
    int b,c;
    printf( "veuillez choisir s il vous plaît  le type de transaction : \nsi vous voulez ajouter un produit achete ===>1 \nsi vous voulez ajouter un produit vendu ===2" ) ;
    scanf("%d", &b) ;
    if ((b!=1)&& (b!=2)){
        printf("votre choix est incorrect. \n si vous voulez repeter l operation tapez ===>1\n si vous voulez retourner au menu tapez ===>2 ");
        scanf("%d",&c);
        if (c==1){ ajouter_produit();}
        else {
            if ( c==2){menu();}
            else printf("choix invalide");
        }
    }
    else {
        if (b==1){ produit_achete();}
        else {produit_vendu();}
    }
}
void supprimer_produit(){
    printf("supprimer");
}
void produit_achete(){
    printf("achete");
}
void produit_vendu(){
    printf("vendu");
}
void historique(){
    printf("historique");
}
void produits_en_stock(){
    printf("en stock");
}
void rechercher_produit(){
    printf("rechercher");
}
void modifier_produit(){
    printf("modifier");
}
void description_produit(char nom_produit[20]){
    printf("description");
}

int main(){
    void menu();
    menu();
return 0;
}
