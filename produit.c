#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include"client.h"
#include"Produit.h"

void gestionProduit();

static unsigned int CP = 0 ;
int nbrP, choix, i;

void C_P()
{
	produit prd;
	FILE *f ;

	f = fopen("Produit","r");

	if(f == NULL)
    {
        printf("\nLe fichier des produits n'existe pas\n");
        exit(-1);
    }

	while(fscanf(f,"%u %s %f %f", &prd.code, prd.designationProduit, &prd.prixUnitaireProduit, &prd.tvaProduit) != EOF)
	{
		CP = prd.code;
	}
}

produit * saisirProduit()
{
    produit * prd;
    prd = (produit*)malloc(sizeof(produit));

    if(prd == NULL)
	{
        printf("pb memory\n");
        exit(-1);
    }

    prd->code = ++CP ;
    printf("\n=> Code produit : %u ", prd->code);
    printf("\n=> Saisir la designation du produit     : ");
    gets(prd->designationProduit);

    do
    {
        printf("\n=> Saisir le prix unitaire du produit   : ");
        scanf("%f",&prd->prixUnitaireProduit);
    }
    while(prd->prixUnitaireProduit <= 0);

    do
    {
        printf("\n=> Saisir la TVA du produit entre 0 et 1 : ");
        scanf("%f",&prd->tvaProduit);
    }
    while(prd->tvaProduit <= 0 || prd->tvaProduit >= 1);

    prd->svt = NULL;
    prd->pre = NULL;

    return prd;
}

produit * ajouterProduit_DL(produit *liste)
{
    produit * prd ;

    prd = saisirProduit() ;

    liste->pre = prd ;
    prd->svt = liste ;
    liste = prd ;

    return liste ;
}

produit * ajouterProduit_FL(produit *liste)
{
    produit * prd , *P ;

    prd = saisirProduit();

    for(P = liste ; P->svt != NULL ; P = P->svt);
    P->svt = prd;
    prd->pre = P;

	return liste;
}


produit * sauvegardepr(produit * prd)
{
	do
	{
		printf("\nEntrer le nombre des produits : ");
		scanf("%d", &nbrP);
		getchar();
	}
	while(nbrP < 1);

	prd = saisirProduit();

	if(nbrP > 1)
	{
	    do
        {
            printf("\n1. Ajouter les produits en debut de liste");
            printf("\n2. Ajouter les produits en fin de liste\n");
            printf("\nSaisir votre choix [1 2] : ") ;
            scanf("%d", &choix);
            getchar();
		}
	    while( choix != 1 && choix != 2);
	}

	if(choix == 1)
	{
		for (i = 1 ; i < nbrP ; i++)
		{
			prd = ajouterProduit_DL(prd);
			getchar();
		}
	}

	if(choix == 2)
	{
		for (i = 1 ; i < nbrP ; i++)
		{
			prd = ajouterProduit_FL(prd);
			getchar();
		}
	}

	return prd;
}

void afficherProduit_G(produit * liste)
{
    produit * prd;

    prd = liste;

    int i,e;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t*************************************** La liste des produits ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1 , 6);
	printf("Code Produit");
	gotoxy(21 , 6);
	printf("Designation");
	gotoxy(41 , 6);
	printf("prix");
	gotoxy(61 , 6);
	printf("tva\n");

	for(i = 0 ; i < 70 ; i++)
	{
		printf("-");
	}

	e=8;

    while(prd != NULL)
	{
		gotoxy(1 , e);
		printf("%i" , prd->code);
		gotoxy(21 , e);
		printf("%s", prd->designationProduit);
		gotoxy(41, e);
		printf("%f", prd->prixUnitaireProduit);
		gotoxy(61 , e);
		printf("%f" , prd->tvaProduit);
		prd = prd->svt;
		e++;
	}

	printf("\n");

	for(i = 0 ; i < 70 ; i++)
		printf("-");

	printf("\t\t\n\n\nClic entrer .....");
	getch();
}


void afficherProduit_D(produit *liste)
{
    produit * P;

    P = liste;

    int i,e;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t*************************************** La liste des produits ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1 , 6);
	printf("Code Produit");
	gotoxy(21 , 6);
	printf("Designation");
	gotoxy(41 , 6);
	printf("prix");
	gotoxy(61 , 6);
	printf("tva\n");

	for(i = 0 ; i < 70 ; i++)
	{
		printf("-");
	}

	e = 8;

	if(P)
    {
        for(P = liste ; P->svt ; P = P->svt);
    }

    while(P != NULL)
	{
		gotoxy(1 , e);
		printf("%i" , P->code);
		gotoxy(21 , e);
		printf("%s" , P->designationProduit);
		gotoxy(41 , e);
		printf("%f" , P->prixUnitaireProduit);
		gotoxy(61 , e);
		printf("%f" , P->tvaProduit);
		P = P->pre;
		e++;
	}

	printf("\n");

	for(i = 0 ; i < 70 ; i++)
		printf("-");

	printf("\t\t\n\n\nClic entrer .....");
	getch();
}

void modifierpr(produit *liste , unsigned int code)
{
    produit *P;

    P = liste ;

    if(P == NULL)
    {
        printf("\nLa liste des produits est vide\n");
    }

    while(P)
	{
		if(code == P->code)
		{
	        getchar();
			printf("\n=> Saisir la nouvel designation du produit   : ");
    		gets(P->designationProduit);
    		do
            {
                printf("\n=> Saisir le nouveau prix unitaire du produit: ");
                scanf("%f",&P->prixUnitaireProduit);
            }
			while(P->prixUnitaireProduit <= 0);
			do
            {
                printf("\n=> Saisir la nouvel TVA du produit           : ");
                scanf("%f",&P->tvaProduit);
            }
            while(P->tvaProduit <= 0 || P->tvaProduit >= 1);

			break;
		}
		else
		{
			P = P->svt;
		}

        if(P == NULL)
        {
            printf("Le code %u n'existe pas dans la liste des produits\n", code);
        }
	}
}


produit * supprimerProduit_DL(produit *liste){

    produit *P = liste;

    if(liste->svt)
    {
    	liste = liste->svt;
	    P->svt = NULL;
	    liste->pre = NULL;
	    free(P);
	}
	else
	{
		liste = NULL;
	}

    return liste;
}

void supprimerProduit(produit * P){
    produit * P1 , * P2 ;

    P1 = P->pre ;
    P2 = P->svt ;
    P1->svt = P2 ;
    P->pre = NULL ;
    P->svt = NULL ;

    if(P2)
	{
    	P2->pre = P1;
    }

    free(P);
}

produit *supprimerpr(produit *liste , unsigned int code)
{
	produit *P;

	P = liste;

    while(P && code != P->code)
    {
        P = P->svt;
    }

    if(P == NULL)
    {
        printf("\nLe code %u n'existe pas dans la liste des produits\n", code);
    }
    else
    {
        if(code == P->code)
        {
            if(P == liste)
            {
                liste = supprimerProduit_DL(liste);
            }
            else
            {
                supprimerProduit(P);
            }
        }
    }

    return liste;
}

void enregistrerpr(produit *T)
{
    FILE *f;
    produit *P;

	f=fopen("Produit","a+");

    if(f == NULL)
	{
        printf("\n Le fichier des produits n'existe pas\n");
        exit(-1);
    }

    for(P = T ; P ; P = P->svt)
	{
    	fprintf(f,"%u \t %s \t %f \t %f \n", P->code,  P->designationProduit, P->prixUnitaireProduit, P->tvaProduit);
    }

	fclose(f);

	printf("La liste est enregistre \n");
	printf("\t\t\n\n\nClic entrer .....");
    getch();
}

void afficher_fichierpr()
{
	FILE *f;
    produit prd;

    int i,e;

    system("cls");
	printf("\n\t**********************************************************************************************************");
	printf("\n\t*************************************** Le fichier des produits ******************************************");
	printf("\n\t**********************************************************************************************************\n\n");


	gotoxy(1 , 6);
	printf("Code Produit");
	gotoxy(21 , 6);
	printf("Designation");
	gotoxy(41 , 6);
	printf("prix");
	gotoxy(61 , 6);
	printf("tva\n");

	for(i = 0 ; i < 70 ; i++)
	{
		printf("-");
	}

	e=8;

	f = fopen("Produit","r");

	if(f == NULL)
    {
        printf("\n Le fichier des produits n'existe pas\n");
        exit(-1);
    }

    while(fscanf(f,"%u %s %f %f", &prd.code, prd.designationProduit, &prd.prixUnitaireProduit, &prd.tvaProduit) != EOF)
	{
		gotoxy(1 , e);
		printf("%u" , prd.code);
		gotoxy(21 , e);
		printf("%s", prd.designationProduit);
		gotoxy(41, e);
		printf("%f", prd.prixUnitaireProduit);
		gotoxy(61 , e);
		printf("%f" , prd.tvaProduit);

		e++;
	}

    fclose(f);

	printf("\n");

	for(i = 0 ; i < 70 ; i++)
		printf("-");
}

void chercher_fichierpr(unsigned int code)
{
	FILE * f;
	produit prd;

	int found = 0;

    f = fopen("Produit","r");

    if(f == NULL){
        printf("\n Le fichier des produits n'existe pas\n");
        exit(-1);
    }

    while( !feof(f) && found == 0 ){

        fscanf(f,"%u %s %f %f", &prd.code, prd.designationProduit, &prd.prixUnitaireProduit, &prd.tvaProduit);

        if(prd.code == code)
        {
        	found = 1;
		}
    }

    if (found == 1)
    {
		printf("\n=> Le code                   : %u", prd.code);
        printf("\n=> La designation du produit : %s", prd.designationProduit);
        printf("\n=> Le prix du produit        : %f", prd.prixUnitaireProduit);
		printf("\n=> La TVA du produit         : %f\n", prd.tvaProduit);
	}
	else
	{
		printf("\nLe code %u n'existe pas dans la liste des produits\n", code);
	}

    fclose(f);

}

void gestionProduit()
{

	produit * liste;
    unsigned int choix, code;

    liste = NULL;

    do
    {
        system("cls");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        gotoxy(47 , 2);
        printf("MENU PRODUITS");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        printf("\n\n\n\t\t\t0: Ajouter des produit");
        printf("\n\t\t\t1: affichage des produits de gauche a droite");
        printf("\n\t\t\t2: affichage des produits de droite a gauche");
        printf("\n\t\t\t3: modifier un produit");
        printf("\n\t\t\t4: supprimer un produit\n");
        printf("\n\t\t\t5: enregistrer les produits dans un fichier");
        printf("\n\t\t\t6: afficher le fichier des produits");
        printf("\n\t\t\t7: Chercher dans le fichier des produits\n");
        printf("\n\t\t\t8: Retour");
        printf("\n\n\t\t\t\t Saisir votre choix [0 8] : ") ;
        scanf("%u",&choix);
        switch(choix)
        {
            case 0:
                system("cls");
                C_P();
                liste = sauvegardepr(liste);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 1:
                afficherProduit_G(liste);
                break;
            case 2:
                afficherProduit_D(liste);
                break;
            case 3:
                system("cls");
                printf("\n\t => Donner le code de produit a modifier : ");
                scanf("%u", &code);
                modifierpr(liste, code);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 4:
                system("cls");
                printf("\n\t => Donner le code de produit a supprimer : ");
                scanf("%u", &code);
                liste = supprimerpr(liste,code);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 5:
                system("cls");
                enregistrerpr(liste);
                liste = NULL;
                break;
            case 6:
                system("cls");
                afficher_fichierpr();
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 7:
                system("cls");
                printf("\n\t => Donner le code de produit a chercher : ");
                scanf("%u", &code);
                chercher_fichierpr(code);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 8:
                mainmenu();
                break;
            default:
                printf("\n\t\t\t\tChoix invalide\n");
                break;
        }
    }
    while(choix != 8);

	exit(0);
}
