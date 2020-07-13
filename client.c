#include<stdio.h>
#include"login.h"
#include<stdlib.h>
#include"client.h"
#include"produit.h"

void gestionClient();

static unsigned int CC;
int nbrC, choix, i;

void C_C()
{
	client c;
	FILE *f ;
	int i;

	f = fopen("Clients","r");

	if(f == NULL)
    {
        printf("\nLe fichier des factures n'existe pas\n");
        exit(-1);
    }

	while(fscanf(f,"%u %s %s %s %s", &c.code, c.nom,c.prenom, c.adresse, c.tel) != EOF)
	{
		CC = c.code;
	}
}

client * saisirClient()
{
    client * clt;
    clt = (client*)malloc(sizeof(client));

    if(clt == NULL)
	{
        printf("\nprobleme de memoire\n");
        exit(-1);
    }

    clt->code = ++CC ;
    printf("\n=> Code client : %u ", clt->code);
    printf("\n=> Saisir le nom du client     : ");
    gets(clt->nom);
    printf("\n=> Saisir le prenom du client  : ");
    gets(clt->prenom);
    printf("\n=> Saisir l'adresse du client  : ");
    gets(clt->adresse);
    printf("\n=> Saisir le telephone         : ");
    gets(clt->tel);
    clt->svt = NULL;
    clt->pre = NULL;

    return clt;
}

client * ajouterClient_DL(client * liste)
{
    client * clt ;

    clt = saisirClient() ;

    liste->pre = clt ;
    clt->svt = liste ;
    liste = clt ;

    return liste ;
}

client * ajouterClient_FL(client * liste)
{
    client * clt , * C ;

    clt = saisirClient();

    for(C = liste ; C->svt != NULL ; C = C->svt);

    C->svt = clt;
    clt->pre = C;

    return liste;
}


client * sauvegarde(client * clt)
{
	do
	{
		printf("\nEntrer le nombre des clients : ");
		scanf("%d", &nbrC);
		getchar();
	}
	while(nbrC < 1);

	clt = saisirClient();

	if(nbrC > 1)
	{
        do
        {
            printf("\n1. Ajouter les clients en debut de liste");
            printf("\n2. Ajouter les clients en fin de liste\n");
            printf("\nSaisir votre choix [1 2] : ") ;
            scanf("%d", &choix);
            getchar();
		}
	    while( choix != 1 && choix != 2);
	}

	if(choix == 1)
	{
		for (i = 1 ; i < nbrC ; i++)
		{
			clt = ajouterClient_DL(clt);
        }
	}

	if(choix == 2)
	{
		for (i = 1 ; i < nbrC ; i++)
		{
			clt = ajouterClient_FL(clt);
		}
	}

	return clt;
}

void afficherClient_G(client * liste)
{
    client * clt;
    int i , e;

    clt = liste;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t**************************************** La liste des clients ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1,6);
	printf("Code Client");
	gotoxy(21,6);
	printf("Nom");
	gotoxy(41,6);
	printf("Prenom");
	gotoxy(61,6);
	printf("Adresse");
	gotoxy(81,6);
	printf("telephone\n");

	for( i = 0 ; i < 100 ; i++)
	{
		printf("-");
	}

	e = 8;

    while(clt != NULL)
	{
		gotoxy(1 , e);
		printf("%u", clt->code);
		gotoxy(21 , e);
		printf("%s", clt->nom);
		gotoxy(41 , e);
		printf("%s", clt->prenom);
		gotoxy(61 , e);
		printf("%s", clt->adresse);
		gotoxy(81 , e);
		printf("%s", clt->tel);
		clt = clt->svt;
		e++;
	}

	printf("\n");

	for( i = 0 ; i < 100 ; i++)
		printf("-");

	printf("\t\t\n\n\nClic entrer .....");
	getch();
}

void afficherClient_D(client *liste)
{
    client * clt;
    int i , e;

    clt = liste;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t**************************************** La liste des clients ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1 , 6);
	printf("Code Client");
	gotoxy(21 , 6);
	printf("Nom");
	gotoxy(41 , 6);
	printf("Prenom");
	gotoxy(61 , 6);
	printf("Adresse");
	gotoxy(81 , 6);
	printf("telephone\n");

	for( i = 0 ; i < 100 ; i++)
	{
		printf("-");
	}

	e = 8;

	if(clt)
    {
        for(clt = liste ; clt->svt ; clt = clt->svt);
    }

    while(clt != NULL)
	{
		gotoxy(1 , e);
		printf("%u", clt->code);
		gotoxy(21 , e);
		printf("%s", clt->nom);
		gotoxy(41 , e);
		printf("%s", clt->prenom);
		gotoxy(61 , e);
		printf("%s", clt->adresse);
		gotoxy(81 , e);
		printf("%s", clt->tel);
		clt = clt->pre;
		e++;
	}

	printf("\n");

	for(i = 0 ; i < 100 ; i++)
		printf("-");

	printf("\t\t\n\n\nClic entrer .....");
	getch();
}

void modifier(client *liste , unsigned int code)
{
    client *C;

    C = liste ;

    if(C == NULL)
    {
        printf("\nLa liste des clients est vide\n", code);
    }

    while(C)
	{
		if(code == C->code)
		{
	        getchar();
			printf("\n=> Saisir le nom du client       : ");
    		gets(C->nom);
    		printf("\n=> Saisir le prenom du client    : ");
    		gets(C->prenom);
    		printf("\n=> Saisir l'adresse du client    : ");
    		gets(C->adresse);
			printf("\n=> Saisir le telephone du client : ");
   			gets(C->tel);

			break;
		}
		else
		{
			C = C->svt;
		}

        if(C == NULL)
        {
            printf("\nLe code %u n'existe pas dans la liste des clients\n", code);
        }
	}
}

client * supprimerClient_DL(client *liste){
    client *C = liste;

    if(liste->svt)
    {
    	liste = liste->svt;
	    C->svt = NULL;
	    liste->pre = NULL;
	    free(C);
	}
	else
	{
		liste = NULL;
	}

	return liste;
}

void supprimerClient(client * C){
    client * C1 , * C2 ;

    C1 = C->pre ;
    C2 = C->svt ;
    C1->svt = C2 ;
    C->pre = NULL ;
    C->svt = NULL ;

    if(C2)
	{
    	C2->pre = C1;
    }

    free(C);
}

client *supprimer(client *liste , unsigned int code)
{
	client *C;

	C = liste;

    while(C && code != C->code)
    {
        C = C->svt;
    }

    if(C == NULL)
    {
        printf("\nLe code %u n'existe pas dans la liste des clients\n", code);
    }
    else
    {
        if(code == C->code)
        {
            if(C == liste)
            {
                liste = supprimerClient_DL(liste);
            }
            else
            {
                supprimerClient(C);
            }
        }
    }

    return liste;
}

void enregistrer(client *T)
{
    FILE *f;
    client *C;

    f = fopen("Clients","a+");

    if(f == NULL)
	{
        printf("pb memory\n");
        exit(-1);
    }

    for(C = T ; C ; C = C->svt)
	{
    	fprintf(f,"%u \t %s \t %s \t %s \t %s \n", C->code,  C->nom, C->prenom, C->adresse, C->tel);
    }

    fclose(f);

	printf("\nLa liste est enregistre\n");
}

void afficher_fichier()
{
	FILE *f;
    client clt;
    int i , e;

    f = fopen("Clients","r");

    if(f == NULL){
        printf("\nLe fichier des clients n'existe pas\n");
        exit(-1);
    }

    system("cls");
	system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t*************************************** Le fichier des clients *****************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1 , 6);
	printf("Code Client");
	gotoxy(21 , 6);
	printf("Nom");
	gotoxy(41 , 6);
	printf("Prenom");
	gotoxy(61 , 6);
	printf("Adresse");
	gotoxy(81 , 6);
	printf("telephone\n");

	for( i = 0 ; i < 100 ; i++)
	{
		printf("-");
	}

	e = 8;

	while(fscanf(f,"%u  %s %s %s %s", &clt.code, clt.nom, clt.prenom, clt.adresse, clt.tel) != EOF)
	{
		gotoxy(1 , e);
		printf("%u" , clt.code);
		gotoxy(21 , e);
		printf("%s", clt.nom);
		gotoxy(41, e);
		printf("%s", clt.prenom);
		gotoxy(61 , e);
		printf("%s" , clt.adresse);
		gotoxy(81 , e);
		printf("%s" , clt.tel);

		e++;
	}

    fclose(f);

	printf("\n");

	for(i = 0 ; i < 100 ; i++)
		printf("-");
}

void chercher_fichier(unsigned int code)
{
	FILE * f;
	client clt;

	int found = 0;

    f = fopen("Clients","r");

    if(f == NULL)
	{
        printf("\nLe fichier des clients n'existe pas\n");
        exit(-1);
    }

    while( !feof(f) && found == 0 )
	{
        fscanf(f,"%u  %s %s %s %s", &clt.code, clt.nom, clt.prenom, clt.adresse, clt.tel);

        if(clt.code == code)
        {
        	found = 1;
		}
    }

    if (found == 1)
    {
		printf("\n=> Le code du client      : %u", clt.code);
        printf("\n=> Le nom du client       : %s", clt.nom);
        printf("\n=> Le prenom du client    : %s", clt.prenom);
        printf("\n=> L'adresse du client    : %s", clt.adresse);
		printf("\n=> Le telephone du client : %s\n", clt.tel);
	}
	else
	{
		printf("\nLe code %u n'existe pas dans le fichier des clients\n", code);
	}

    fclose(f);

}

void gestionClient()
{
	client * liste;
    unsigned int choix, code;

    liste = NULL;

    do
    {
        system("cls");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        gotoxy(55 , 2);
        printf("MENU CLIENTS");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        printf("\n\n\n\t\t\t0: Ajouter les clients\n");
        printf("\t\t\t1: Affichage des clients de gauche a droite\n");
        printf("\t\t\t2: Affichage des clients de droite a gauche\n");
        printf("\t\t\t3: Modifier un client\n");
        printf("\t\t\t4: Supprimer un client\n\n");
        printf("\t\t\t5: Enregistrer les clients dans un fichier\n");
        printf("\t\t\t6: Afficher le fichier des clients\n");
        printf("\t\t\t7: Chercher dans le fichier des clients\n\n");
        printf("\t\t\t8: Retour\n");
        printf("\n\n\t\t\t\t Saisir votre choix [0 8] : ") ;
        scanf("%u",&choix);

        switch(choix)
        {
            case 0:
                system("cls");
                C_C();
                liste = sauvegarde(liste);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 1:
                afficherClient_G(liste);
                break;
            case 2:
                afficherClient_D(liste);
                break;
            case 3:
                system("cls");
                printf("\n\t => Donner le code du client a modifier : ");
                scanf("%u", &code);
                modifier(liste, code);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 4:
                system("cls");
                printf("\n\t => Donner le code du client a supprimer : ");
                scanf("%u", &code);
                liste = supprimer(liste,code);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 5:
                system("cls");
                enregistrer(liste);
                liste = NULL;
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 6:
                system("cls");
                afficher_fichier();
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 7:
                system("cls");
                printf("\n\t => Donner le code du client a chercher : ");
                scanf("%u", &code);
                chercher_fichier(code);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 8:
                mainmenu();
                break;
            default:
                printf("choix invalide\n");
                break;
        }
    }
    while(choix != 8);

	exit(0);
}
