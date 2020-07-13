#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include"client.h"
#include"Produit.h"

void login();

void mainmenu();

void gotoxy(short x, short y)
{
	COORD pos = {x , y} ;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
}

void welcome()
{
	gotoxy(15,6);
	printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
	gotoxy(15,7);
	printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
	gotoxy(15,8);
	printf("        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	gotoxy(15,9);
	printf("        =*                              Bienvenue                            *=");
	gotoxy(15,10);
	printf("        =*                                 sur                               *=");
	gotoxy(15,11);
	printf("        =*                                notre                              *=");
	gotoxy(15,12);
	printf("        =*                               systeme                             *=");
	gotoxy(15,13);
	printf("        =*                             de boutique                           *=");
	gotoxy(15,14);
	printf("        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	gotoxy(15,15);
	printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
	gotoxy(15,16);
	printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
	gotoxy(28,22);
	printf(" clic entrer pour continuer .....");
	getch();
	login();
}

void login()
{
    int a = 0 , i = 0;
    char uname[10] , c = ' ';
    char pword[10] , code[10];
    char user[10] = "admin";
    char pass[10] = "admin123";

	do
	{
        system("cls");
        printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb LOGIN \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
        printf(" \n\n\n\n                        USERNAME : ");
        scanf("%s", &uname);
        printf(" \n\n                        PASSWORD : ");

        while(i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            if(c == 13)
                break;
            else
                printf("*");

            i++;
        }
        pword[i] = '\0';

        i = 0;
            if(strcmp(uname,"admin") == 0 && strcmp(pword,"admin123") == 0)
            {
                printf("  \n\n\n\t\t        BIENVENUE AU SYSTEME GESTION BOUTIQUE !!!! LOGIN IS SUCCESSFUL");
                printf("\n\n\nCONNEXION EN COURS. ATTENDS SVP ... \n");
                for(i=0; i<3; i++)
                {
                    printf(".");
                    Sleep(500);
                }
                printf("\n\n\n\n\t\t\tPress any key to continue...");
                getch();
                break;
            }
            else
            {
                printf("\n\n        SORRY !!!!  LOGIN OR PASSWORD IS WRONG press any key to retry");
                a++;
                getch();
            }
    }
	while(a <= 2);

	if (a > 2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");
		getch();
    }

    system("cls");
    mainmenu();
}



void mainmenu()
{
    int choice;

    do
    {
        system("cls");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        gotoxy(55 , 2);
        printf("MENU");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        gotoxy(30 , 9);
        printf("\t1: La gestion des clients");
        gotoxy(30 , 12);
        printf("\t2: La gestion des produits");
        gotoxy(30 , 15);
        printf("\t3: La gestion des commandes et factures");
        gotoxy(30 , 18);
        printf("\t4: Quitter ");
        gotoxy(30 , 23);
        printf("\t\t Saisir votre choix [1 4] : ") ;
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                system("cls");
                gestionClient();
                break;
            case 2:
                system("cls");
                gestionProduit();
                break;
            case 3:
                system("cls");
                gestionCommande();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("choix invalide\n");
        }
    }while(choice != 4);
}
