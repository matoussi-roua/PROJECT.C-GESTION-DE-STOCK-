#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Product {
  char name[100];
  int quantity;
  double price;
};













void update_product(char *name, int new_quantity, float new_price) {/*
  // Ouvrez le fichier en mode "lecture"
  FILE *fp = fopen("products.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Créez un fichier temporaire pour stocker les lignes mises à jour
  FILE *temp_fp = fopen("temp.txt", "w");
  if (temp_fp == NULL) {
    printf("Error creating temporary file!\n");
    exit(1);
  }

  // Créez une variable pour stocker chaque ligne lue dans le fichier
  char line[100];

  // Utilisez fgets() pour lire chaque ligne du fichier
  while (fgets(line, 100, fp) != NULL) {
    // Séparez les informations sur le produit en utilisant strtok()
    char *product_name = strtok(line, ",");
    char *quantity_str = strtok(NULL, ",");
    char *price_str = strtok(NULL, ",");

    // Si le nom du produit correspond à celui à mettre à jour, utilisez les nouvelles informations
    if (strcmp(product_name, name) == 0) {
      fprintf(temp_fp, "%s,%d,%.2f\n", name, new_quantity, new_price);
    }
    else {
      // Sinon, écrivez la ligne dans le fichier temporaire sans modification
      fprintf(temp_fp, "%s", line);
    }
  }

  // Fermez les fichiers
  fclose(fp);
  fclose(temp_fp);

  // Supprimez le fichier original
  remove("products.txt");

  // Renommez le fichier temporaire en "products.txt"
  rename("temp.txt", "products.txt");*/
}








struct Product search_product(char *name) {/*
  // Ouvrez le fichier en mode "lecture"
  FILE *fp = fopen("products.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Créez une variable de type Product pour stocker les informations sur le produit
  struct Product p;
  p.name[0] = '\0';
  p.quantity = 0;
  p.price = 0.0;

  // Créez une variable pour stocker chaque ligne lue dans le fichier
  char line[100];

  // Utilisez fgets() pour lire chaque ligne du fichier
  while (fgets(line, 100, fp) != NULL) {
    // Séparez les informations sur le produit en utilisant strtok()
    char *product_name = strtok(line, ",");
    char *quantity_str = strtok(NULL, ",");
    char *price_str = strtok(NULL, ",");

    // Si le nom du produit correspond à celui recherché, mettez à jour la variable de type Product
    if (strcmp(product_name, name) == 0) {
      strcpy(p.name, product_name);
      p.quantity = atoi(quantity_str);
      p.price = atof(price_str);
      break;
    }
  }

  // Fermez le fichier
  fclose(fp);

  return p;*/
}
//hedhom mrygliiiin**************************************************************************************************************************

void delete_product(char name[100]) {
  // Ouvrez le fichier en mode "lecture"
    FILE *fp ;
    fp= fopen("products.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Créez un fichier temporaire pour stocker les lignes à conserver
    FILE *temp_fp ;
    temp_fp= fopen("temp.txt", "a");
    if (temp_fp == NULL) {
        printf("Error creating temporary file!\n");
        exit(1);
    }

  // Créez une variable pour stocker chaque ligne lue dans le fichier
    char line[100];

  // Utilisez fgets() pour lire chaque ligne du fichier
  while (fgets(line, 100, fp) != NULL) {
    // Séparez les informations sur le produit en utilisant strtok()
char *product_name = strtok(line, ",");

    // Si le nom du produit ne correspond pas à celui à supprimer, écrivez la ligne dans le fichier temporaire
    if (strcmp(product_name, name) != 0) {
        printf("oui");
      fprintf(temp_fp, "%s", line);
    }
  }

  // Fermez les fichiers
  fclose(fp);
  fclose(temp_fp);

  // Supprimez le fichier original
  remove("products.txt");

  // Renommez le fichier temporaire en "products.txt"
  rename("temp.txt", "products.txt");
}


void add_product(struct Product p) {
  FILE *file_products;
  file_products= fopen("products.txt", "a");
  if (file_products == NULL) {
    printf("Error!\n");
  }
  else{
    fprintf(file_products, "%s,%d,%.3lf\n", p.name, p.quantity, p.price);
    fclose(file_products);
  }
}



void display_product(char name[100]) {
  int test=0;
  FILE *file_products;
  file_products= fopen("products.txt", "a");
  fclose(file_products);
  file_products= fopen("products.txt", "r");

  if (file_products == NULL) {
    printf("Error!\n");
    exit(1);
  }

  // Créez une variable pour stocker chaque ligne lue dans le fichier
  char line[100];

  // Utilisez fgets() pour lire chaque ligne du fichier
  while (fgets(line, 100, file_products) != NULL) {
    // Séparez les informations sur le produit en utilisant strtok()
    int s;
    char *product_name = strtok(line, ",");
    char *quantity_str = strtok(NULL, ",");
    char *price_str = strtok(NULL, ",");
    // Si le nom du produit correspond à celui recherché, affichez les informations
    if (strcmp(product_name, name) == 0) {
      test=1;

      printf("\n\t\t            ***PRODUCT'S DESCRIPTION***\n");
      printf("\t\t  ================================================\n");
      printf("\t\t          NAME         ||     %-10s\n",product_name);
      printf("\t\t  ================================================\n");
      printf("\t\t          QUANTITY     ||     %s\n",quantity_str);
      printf("\t\t  ================================================\n");
      printf("\t\t          PRICE        ||     %s\n",price_str);
      printf("\t\t  ================================================");  
      break; 
    }
    }
  if (test==0){
    printf("\t\t           **THE PRODUCT DOESN'T EXIST**");
  }
  fclose(file_products);
}




int main() {
  printf("\n");
	printf("\t\t\t  ================================\n");
	printf("\t\t\t     STOCK-MANAGER PROGRAM\n");
	printf("\t\t\t  ================================\n\n");

    while (1) {
        // Affichez le menu
        printf("\n\n\t\t\t   \t     ***MENU***          \n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 1. Add product          |\n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 2. Display product      |\n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 3. Delete product       |\n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 4. Update product       |\n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 5. Search product       |\n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 6. Exit                 |\n");
        printf("\t\t\t   ------------------------------");
        printf("\nEnter your choice: ");

        // Lit le choix de l'utilisateur
        int choice;
        scanf("%d", &choice);

        // Selon le choix de l'utilisateur, appelez la fonction correspondante
        switch (choice) {
          case 1:;
            // Ajouter un produit
            struct Product p ;
            char name[100];
            int quantity;
            double price;
            printf("\n\t\t                ***ADD PRODUCT***\n");
            printf("\t\t  ================================================\n");
            printf("\t\t          NAME         ||     ");
            scanf("%s",	&name);
            printf("\t\t  ================================================\n");
            printf("\t\t          QUANTITY     ||     ");
            scanf("%d", &quantity);
            printf("\t\t  ================================================\n");
            printf("\t\t          PRICE        ||     ");
            scanf("%lf", &price);
            printf("\t\t  ================================================\n");
            strcpy(p.name,name);
            p.quantity=quantity;
            p.price=price;
            add_product(p);
            break;
          case 2:;
            // Afficher la description d'un produit
            char nom[100];
            printf("Enter product name: ");
            scanf("%s",&nom);
            display_product(nom);
            break;
          case 3:;
            char name_3[100];
            // Supprimer un produit
            printf("Enter product name: ");
            scanf("%s", name_3);
            delete_product(name_3);
            break;
        /*case 4:
            // Modifier un produit
            printf("Enter product name: ");
            scanf("%s", name);
            printf("Enter new quantity: ");
            int quantit;
            scanf("%d", &quantit);
            printf("Enter new price: ");
            float pric;
            scanf("%f", &pric);
            update_product(name, quantity, price);
            break;
        case 5:
            // Rechercher un produit
            printf("Enter product name: ");
            scanf("%s", name);
            struct Product p1 = search_product(name);
            printf("Product: %s\n", p.name);
            printf("Quantity: %d\n", p.quantity);
            printf("Price: %.2f\n", p.price);
            break;*/
        case 6:
            // Quitter l'application
            return 0;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}
