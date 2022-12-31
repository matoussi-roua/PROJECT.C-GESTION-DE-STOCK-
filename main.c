#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>


struct Product {
  char name[100];
  int quantity;
  float price;
};

struct date {
  char d[256];
  char m[256];
  int y;
};


int day(void)
{   int res;
    time_t s, val = 1;
    struct tm* current_time;
    
    s = time(NULL);
    
    current_time = localtime(&s);
    res = current_time->tm_mday;
    return res;
}


int month(void)
{
    time_t s, val = 1;
    struct tm* current_time;
    
    s = time(NULL);
    
    current_time = localtime(&s);
    
    return current_time->tm_mon + 1;
}


int year(void)
{
    int res;
    time_t s, val = 1;
    struct tm* current_time;
    
    s = time(NULL);
    
    current_time = localtime(&s);
    res=current_time->tm_year + 1900;
    return res;
}


struct date get_date() {
  struct date dt;
  sprintf(dt.d,"%d",day());
  switch (month())
    {
    case 1:
        sprintf(dt.m,"%s","January");
    case 2:
        sprintf(dt.m,"%s","Februrary");
    case 3:
        sprintf(dt.m,"%s","March");
    case 4:
        sprintf(dt.m,"%s","April");
    case 5:
        sprintf(dt.m,"%s","May");
    case 6:
        sprintf(dt.m,"%s","June");
    case 7:
        sprintf(dt.m,"%s","July");
    case 8:
        sprintf(dt.m,"%s","August");
    case 9:
        sprintf(dt.m,"%s","September");
    case 10:
        sprintf(dt.m,"%s","October");
    case 11:
        sprintf(dt.m,"%s","November");
    case 12:
        sprintf(dt.m,"%s","December");
    }
  dt.y = year();
  return dt;
}


void show_all(void) {

  // Ouvrez le fichier en mode "lecture"
  FILE *fp = fopen("products.txt", "r");
  
  // Créez une variable pour stocker chaque ligne lue dans le fichier
  char line[100];
  int main();
  struct stat st;
  stat("products.txt", &st); 
  if ((st.st_size == 0) || (fp == NULL)){
    printf("Your Stock is Empty!");
    main();
    }
  printf("\n\t\t            ***ALL EXISTING PRODUCTS***\n");
  printf("\t\t  ================================================\n");    
  
  // Utilisez fgets() pour lire chaque ligne du fichier
  while (fgets(line, 100, fp) != NULL) {
    // Séparez les informations sur le produit en utilisant strtok()
    int s;
    char *product_name = strtok(line, ",");
    // Si le nom du produit correspond à celui recherché, affichez les informations
        printf("\t\t                    NAME : %-10s\n",product_name);
        printf("\t\t  ================================================\n");

  }
  
  // Fermez le fichier
  fclose(fp);
}


void addH(char name[],char descrip[], int quan,char d[], char m[],int y ){
    //ajouter a archives de histories d'entres et de sorties
    char destination[100] ;
    char destination2[100] ;
    char file_name[256];
    char info[256];
    
    DIR *dir;
    FILE *file;
    //creation de dossier archives si n'existe pas
    dir = opendir("./ARCHIVES");
    if (dir == NULL) {
        mkdir("./ARCHIVES");
    }

    //creation de directory path selon l'annee , le mois et le jour
    sprintf(destination, "./ARCHIVES/%d",y);
    dir = opendir(destination);
    if (dir == NULL) {
        mkdir(destination);
    }

    
    sprintf(destination2, "%s/%s",destination,m);
    dir = opendir(destination2);
    if (dir == NULL) {
        
        mkdir(destination2);
    }
    
    sprintf(file_name, "%s/%s.txt", destination2,d);
    file = fopen(file_name, "a");
    
    sprintf(info, "THE PRODUCT :%s  %s IN %s/%s/%d", name,descrip,d,m,y);
    fprintf(file,"%s\n",info);

    fclose(file);
    closedir(dir);

}


void add_product(struct Product p1) {
    
    struct Product p;
    p = (struct Product) p1;

    // Ouvrez le fichier en mode "append" pour ajouter des données à la fin du fichier
    FILE *fp;
    fp = fopen("products.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Écrivez les informations sur le produit dans le fichier
    fprintf(fp, "%s,%d,%f\n", p.name, p.quantity, p.price);

    // Fermez le fichier
    fclose(fp);

    //Enregistrer l'operation dans historique
    struct date dt = get_date();

    addH(p.name,"ADDED TO THE STOCK",p.quantity,dt.d,dt.m,dt.y);
}


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
        char *quantity_str = strtok(NULL, ",");
        char *price_str = strtok(NULL, ",");

    
        // Si le nom du produit ne correspond pas à celui à supprimer, écrivez la ligne dans le fichier temporaire
        if (strcmp(product_name, name) != 0) {
            fprintf(temp_fp, "%s,%s,%s", product_name, quantity_str, price_str);
        }
    }

    // Fermez les fichiers
    fclose(fp);
    fclose(temp_fp);

    // Supprimez le fichier original
    remove("./products.txt");

    // Renommez le fichier temporaire en "products.txt"
    rename("./temp.txt", "./products.txt");

    //Enregistrer l'operation dans historique
    struct date dt = get_date();

    addH(name,"DELETED FROM THE STOCK",0,dt.d,dt.m,dt.y);
}



void display_product(char name[100]) {

  // Ouvrez le fichier en mode "lecture"
  FILE *fp = fopen("products.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Créez une variable pour stocker chaque ligne lue dans le fichier
  char line[100];
  int test_exist=0;
  int test_not_empty=0;
  // Utilisez fgets() pour lire chaque ligne du fichier
  while (fgets(line, 100, fp) != NULL) {
    test_not_empty=1;
    // Séparez les informations sur le produit en utilisant strtok()
    char *product_name = strtok(line, ",");
    char *quantity_str = strtok(NULL, ",");
    char *price_str = strtok(NULL, ",");
    // Si le nom du produit correspond à celui recherché, affichez les informations
    if (strcmp(product_name, name) == 0) {
        printf("\n\t\t            ***PRODUCT'S DESCRIPTION***\n");
        printf("\t\t  ================================================\n");
        printf("\t\t          NAME         ||     %-10s\n",product_name);
        printf("\t\t  ================================================\n");
        printf("\t\t          QUANTITY     ||     %s\n",quantity_str);
        printf("\t\t  ================================================\n");
        printf("\t\t          PRICE        ||     %s\n",price_str);
        printf("\t\t  ================================================");
        test_exist=1;
      
    }

  }
  if (test_not_empty==0){
    printf("\n\t\t                the file is empty\n");}
  else {
    if (test_exist==0){
      printf("\n\t\t            the product doesn't exist\n");
    }
  }


  // Fermez le fichier
  fclose(fp);
}


struct Product search_product(char name[100]) {
  // Ouvrez le fichier en mode "lecture"
  FILE *fp = fopen("products.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Créez une variable de type Product pour stocker les informations sur le produit
  struct Product p;
  p.name[0] = '\0';
  //p.name= '\0';
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
  return p;
}


int direc(const char *dest){
  //pour afficher les element du directory/dossier
	struct dirent *de; 
	DIR *dr; 
    dr= opendir(dest);
	if (dr == NULL) 
	{
		printf("DIRECTORY DOESN'T EXIST" );
        return 0;	
	}
	while ((de = readdir(dr)) != NULL){
            char *extension = strrchr(de->d_name, '.');
            if (extension != NULL) {
                *extension = '\0';
            }
			printf("%s\n", de->d_name);}
	closedir(dr);
  return 0;
}


void seeH(void){
    //pour etre capable de voir l'historie de notre entres et sorties
    char destination[100] ;
    char destination2[100] ;
    char file_name[256];
    char history;
    char d[256];
    char m[256];
    int y;
    
    FILE *file;
    printf("\n***ALL EXISTING YEARS***");
    direc("./ARCHIVES");
    printf("Enter the year : ");   
    scanf("%d", &y);
    sprintf(destination, "./ARCHIVES/%d",y);

    printf("\n***ALL EXISTING MONTHS***");
    direc(destination);
    printf("Enter the month : ");
    scanf("%s",&m);
    sprintf(destination2, "%s/%s",destination,m);

    printf("\n***ALL EXISTING DAYS***");
    direc(destination2);
    printf("Enter the day : ");
    scanf("%s",&d);
    printf("\n");
    sprintf(file_name, "%s/%s.txt", destination2,d);

    file = fopen(file_name, "r");
    
    while((history = fgetc(file)) != EOF)
      printf("%c", history);

    fclose(file);
}



void update_product(char name[100], int new_quantity, float new_price) {
  // Ouvrez le fichier en mode "lecture"
  FILE *fp = fopen("products.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Créez un fichier temporaire pour stocker les lignes mises à jour
  FILE *temp_fp;
  temp_fp=fopen("temp.txt", "a");
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
      fprintf(temp_fp, "%s,%d,%f\n", name, new_quantity, new_price);
      struct date dt = get_date();
      addH(name,"UPDATED",quantity_str,dt.d,dt.m,dt.y);
    }
    else {
      // Sinon, écrivez la ligne dans le fichier temporaire sans modification
      fprintf(temp_fp, "%s,%s,%s", product_name, quantity_str, price_str);

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
        printf("\t\t\t  |\t 6. Check history       |\n");
        printf("\t\t\t   ------------------------------\n");
        printf("\t\t\t  |\t 7. Exit                 |\n");
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
            float price;
            printf("\n\t\t                ***ADD PRODUCT***\n");
            printf("\t\t  ================================================\n");
            printf("\t\t          NAME         ||     ");
            scanf("%s",	&name);
            printf("\t\t  ================================================\n");
            printf("\t\t          QUANTITY     ||     ");
            scanf("%d", &quantity);
            printf("\t\t  ================================================\n");
            printf("\t\t          PRICE        ||     ");
            scanf("%f", &price);
            printf("\t\t  ================================================\n");
            strcpy(p.name,name);
            p.quantity=quantity;
            p.price=price;
            add_product(p);
            break;
        case 2:;
            // Afficher la description d'un produit
            show_all();
            char nom[100];
            printf("Enter product name: ");
            scanf("%s",&nom);
            display_product(nom);
            break;
        case 3:
            // Supprimer un produit
            show_all();
            printf("Enter product name: ");
            scanf("%s", name);
            delete_product(name);
            break;
        case 4:;
            // Modifier un produit
            int quantity4;
            float price4;
            char name4[100];
            show_all();
            printf("\t\t   ENTER PRODUCT NAME  ||     ");            
            scanf("%s", &name4);
            display_product(name4);
            printf("\n\t\t      NEW QUANTITY     ||     ");
            scanf("%d", &quantity4);
            printf("\t\t  ================================================\n");
            printf("\t\t      NEW PRICE        ||     ");
            scanf("%f", &price4);
            printf("\t\t  ================================================\n");

            update_product(name4, quantity4, price4);
            break;
        case 5:;
            // Rechercher un produit
            char name5[100];
            struct Product p1 ;

            printf("Enter product name: ");
            scanf("%s", &name5);
            p1= search_product(name5) ;
            if(p1.quantity != 0){
              printf("\n\t\t                ***THE PRODUCT EXISTS***\n");
              printf("\t\t  ================================================\n");
              printf("\t\t          NAME         ||   %s  \n",p1.name);
              printf("\t\t  ================================================\n");
              printf("\t\t          QUANTITY     ||   %d  \n",p1.quantity);
              printf("\t\t  ================================================\n");
              printf("\t\t          PRICE        ||   %f  \n",p1.price);
              printf("\t\t  ================================================\n");
            }
            else printf("\n\t\t            THE PRODUCT DOESN'T EXIST\n");
            break;
        case 6:
            //Voir le historie d'entres et de sorties
            seeH();
            break;
        case 7:
            // Quitter l'application
            /*return 0;*/
            exit(1);
        default:
            printf("INVALID CHOICE!\n");
            break;
        }
    }
}
