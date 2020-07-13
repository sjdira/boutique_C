#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include"client.h"
#include"produit.h"
#include"commande.h"

void gestionCommande();

struct date
{
    unsigned int j ;
    unsigned int m ;
    unsigned int a ;
};

typedef struct date Date ;

struct commande
{
	unsigned int id ;
	unsigned int idclient ;
	unsigned int codeproduit;
	float prixproduit;
	int quantite;
	Date datedecommande ;
	struct commande * svt ;
    struct commande * pre ;

};

typedef struct commande commande;

static unsigned int CCM = 0 ;
static unsigned int CF = 0 ;

void C_CM()
{
	commande cmd;
	FILE *f ;

	f = fopen("commande","r");

	while(fscanf(f,"%u %u %u %d %d %d %d", &cmd.id,  &cmd.idclient, &cmd.codeproduit, &cmd.quantite ,&cmd.datedecommande.j,&cmd.datedecommande.m,&cmd.datedecommande.a ) != EOF)
	{
		CCM = cmd.id;
	}
}

commande * saisircommande()
{
    FILE * f, * g;
    client clt;
    produit prd;
    commande * cmd;
    int foundc = 0 , foundp = 0;

    cmd = (commande*)malloc(sizeof(commande));

    if(cmd == NULL)
    {
        printf("probleme de memoire\n");
        exit(-1);
    }

    cmd->id = ++CCM ;
    printf("\n=> Code commande  : %u ", cmd->id);

    do
    {
        printf("\n=> Saisir code client qui veut effectuer la commande  : ");
        scanf("%u" , &cmd->idclient);

        f = fopen("Clients","r");

        if(f == NULL)
        {
            printf("\nLe fichier des clients n'existe pas\n");
            exit(-1);
        }

        while( !feof(f) && foundc == 0 )
        {
            fscanf(f,"%u %s %s %s %s", &clt.code, clt.nom, clt.prenom, clt.adresse, clt.tel);

            if(clt.code == cmd->idclient)
            {
                foundc = 1;
            }
        }

        fclose(f);

        if (foundc == 0)
        {
            printf("\nLe code %u n'existe pas dans le fichier des clients\n", cmd->idclient);
        }
    }
    while(foundc != 1);

    do
    {

        printf("\n=> Saisir code de produit desire                      : ");
        scanf("%u" , &cmd->codeproduit);

        g = fopen("Produit","r");

        if(g == NULL)
        {
            printf("\nLe fichier des produits n'existe pas\n");
            exit(-1);
        }

        while( !feof(g) && foundp == 0 ){

            fscanf(g,"%u %s %f %f", &prd.code, prd.designationProduit, &prd.prixUnitaireProduit, &prd.tvaProduit);

            if(prd.code == cmd->codeproduit)
            {
                foundp = 1;
            }
        }

        fclose(g);

        if ( foundp == 0)
        {
            printf("\nLe code %u n'existe pas dans le fichier des produits\n", cmd->codeproduit);
        }

    }
    while (foundp != 1);

    do
    {
        printf("\n=> Saisir la quantite                                 : ");
        scanf("%d" , &cmd->quantite);
    }
    while( cmd->quantite <= 0);

    printf("\n=> Saisir la date de commmande");
    printf("\n=> jour  : ");
    scanf("%d", &cmd->datedecommande.j);
    printf("\n=> mois  : ");
    scanf("%d",&cmd->datedecommande.m);
    printf("\n=> annee : ");
    scanf("%d",&cmd->datedecommande.a);
    cmd->svt = NULL;
    cmd->pre = NULL;

    return cmd;
}

commande * ajoutercommande_DL(commande *liste)
{
    commande * cmd ;

    cmd = saisircommande() ;

    liste->pre = cmd ;
    cmd->svt = liste ;
    liste = cmd ;

    return liste ;
}

commande * ajoutercommande_FL(commande *liste)
{
    commande * cmd , * P ;

    cmd = saisircommande();

    for(P = liste ; P->svt != NULL ; P = P->svt);

    P->svt = cmd;
    cmd->pre = P;

    return liste;
}

commande * sauvegardecm(commande * cmd)
{
    int nbrC, i;
    unsigned int choix;

    do
    {
        printf("\nEntrer le nombre des commandes : ");
        scanf("%d", &nbrC);
        getchar();
    }
    while(nbrC < 1);

	cmd = saisircommande();

	if(nbrC > 1)
	{
	    do
        {
            printf("\n1. Ajouter les commandes en debut de liste");
            printf("\n2. Ajouter les commandes en fin de liste\n");
            printf("\nSaisir votre choix [1 2] : ") ;
            scanf("%u", &choix);
            getchar();
	    }
	    while( choix != 1 && choix != 2);
	}

	if(choix == 1)
	{
		for (i = 1 ; i < nbrC ; i++)
		{
			cmd = ajoutercommande_DL(cmd);
			getchar();
		}
	}

	if(choix == 2)
	{
		for (i = 1 ; i < nbrC ; i++)
		{
			cmd = ajoutercommande_FL(cmd);
			getchar();
		}
	}

	return cmd;
}

void affichercommande_G(commande * liste)
{
    commande * cmd;

    cmd = liste;

    int i , e;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t************************************** La liste des commandes ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1,6);
	printf("Commande");
	gotoxy(21,6);
	printf("Client");
	gotoxy(41,6);
	printf("Produit");
	gotoxy(61,6);
	printf("Quantite");
	gotoxy(81,6);
	printf("La date\n");

	for( i = 0 ; i < 100 ; i++)
	{
		printf("-");
	}

	e = 8;

    while(cmd != NULL)
	{
		gotoxy(1 , e);
		printf("%u", cmd->id);
		gotoxy(21 , e);
		printf("%u", cmd->idclient);
		gotoxy(41 , e);
		printf("%u", cmd->codeproduit);
		gotoxy(61 , e);
		printf("%d", cmd->quantite);
		gotoxy(81 , e);
		printf("%d / %d / %d", cmd->datedecommande.j,cmd->datedecommande.m,cmd->datedecommande.a);
		cmd = cmd->svt;
		e++;
	}

	printf("\n");

	for( i = 0 ; i < 100 ; i++)
		printf("-");

	printf("\t\t\n\n\nClic entrer .....");
	getch();
}


void affichercommande_D(commande *liste)
{
    commande * cmd;

    cmd = liste;

    int i , e;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t************************************** La liste des commandes ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1,6);
	printf("Code commande");
	gotoxy(21,6);
	printf("Code Client");
	gotoxy(41,6);
	printf("Code produit");
	gotoxy(61,6);
	printf("Quantite");
	gotoxy(81,6);
	printf("La date\n");

	for( i = 0 ; i < 100 ; i++)
	{
		printf("-");
	}

	e = 8;

	if(cmd)
    {
        for(cmd = liste ; cmd->svt ; cmd = cmd->svt);
    }

    while(cmd != NULL)
	{
		gotoxy(1 , e);
		printf("%u", cmd->id);
		gotoxy(21 , e);
		printf("%u", cmd->idclient);
		gotoxy(41 , e);
		printf("%u", cmd->codeproduit);
		gotoxy(61 , e);
		printf("%d", cmd->quantite);
		gotoxy(81 , e);
		printf("%d / %d / %d", cmd->datedecommande.j,cmd->datedecommande.m,cmd->datedecommande.a);
		cmd = cmd->pre;
		e++;
	}

	printf("\n");

	for( i = 0 ; i < 100 ; i++)
		printf("-");

	printf("\t\t\n\n\nClic entrer .....");
	getch();
}

void modifiercm(commande *liste , unsigned int id)
{
    commande *c;
    client clt;
    produit prd;
    FILE * f, * g;
    int foundc = 0 , foundp = 0;

    c = liste ;

    if(c == NULL)
    {
        printf("\nLa liste des commandes est vide\n");
    }

    while(c)
	{
		if(id == c->id)
		{
            do
            {
                printf("\n=> Saisir nouveau code client qui veut effectuer la commande  : ");
                scanf("%u",&c->idclient);

                f = fopen("Clients","r");

                if(f == NULL)
                {
                    printf("\nLe fichier des clients n'existe pas\n");
                    exit(-1);
                }

                while( !feof(f) && foundc == 0 )
                {
                    fscanf(f,"%u %s %s %s %s", &clt.code, clt.nom, clt.prenom, clt.adresse, clt.tel);

                    if(clt.code == c->idclient)
                    {
                        foundc = 1;
                    }
                }

                fclose(f);

                if (foundc == 0)
                {
                    printf("\nLe code %u n'existe pas dans le fichier des clients\n", c->idclient);
                }
            }
            while(foundc != 1);

            do
            {
                printf("\n=> saisir a nouveau code de produit desire                    : ");
                scanf("%u",&c->codeproduit);

                g = fopen("Produit","r");

                if(g == NULL)
                {
                    printf("\nLe fichier des produits n'existe pas\n");
                    exit(-1);
                }

                while( !feof(g) && foundp == 0 ){

                    fscanf(g,"%u %s %f %f", &prd.code, prd.designationProduit, &prd.prixUnitaireProduit, &prd.tvaProduit);

                    if(prd.code == c->codeproduit)
                    {
                        foundp = 1;
                    }
                }

                fclose(g);

                if ( foundp == 0)
                {
                    printf("\nLe code %u n'existe pas dans le fichier des produits\n", c->codeproduit);
                }

            }
            while (foundp != 1);

            do
            {
                printf("\n=> Saisir a nouveau la quantite                               : ");
                scanf("%d",&c->quantite);
            }
            while( c->quantite <= 0 );

            printf("\n=> Saisir la date de commmande  MAJ");
            printf("\n=> jour  : ");
            scanf("%d",&c->datedecommande.j);
            printf("\n=> mois  : ");
            scanf("%d",&c->datedecommande.m);
            printf("\n=> annee : ");
            scanf("%d",&c->datedecommande.a);

			break;
		}
		else
		{
			c = c->svt;
		}

        if(c == NULL)
        {
            printf("\nLe code %u n'existe pas dans la liste des commandes\n", id);
        }
	}
}

commande * supprimercommande_DL(commande *liste){

    commande *c = liste;

    if(liste->svt)
    {
    	liste = liste->svt;
	    c->svt = NULL;
	    liste->pre = NULL;
	    free(c);
	}
	else
	{
		liste = NULL;
	}

    return liste;
}

void supprimercommande(commande * c){

    commande * c1 , * c2 ;

    c1 = c->pre ;
    c2 = c->svt ;
    c1->svt = c2 ;
    c->pre = NULL ;
    c->svt = NULL ;

    if(c2)
    {
    	c2->pre = c1;
    }

    free(c);
}

commande *supprimercm(commande *liste , unsigned int id)
{
	commande *c;

	c = liste;

    while(c && id != c->id)
	{
        c=c->svt;
    }

    if(c == NULL)
    {
        printf("\nLe code %u n'existe pas dans la liste des clients\n", id);
    }
    else
    {
        if(id == c->id)
        {
            if(c == liste)
            {
                liste = supprimercommande_DL(liste);
            }
            else
            {
                supprimercommande(c);
            }
        }
    }

    return liste;
}

void enregistrercm(commande * T){

    FILE * f;
    commande * c;

    f=fopen("commande","a+");

    if(f == NULL)
    {
        printf("pb memory\n");
        exit(-1);
    }

    for(c = T ; c ; c = c->svt)
    {
    	fprintf(f,"%u \t %u \t %u \t %d \t %d \t %d \t %d  \n", c->id,  c->idclient, c->codeproduit, c->quantite,c->datedecommande.j,c->datedecommande.m,c->datedecommande.a);
    }
    fclose(f);
    printf("\nLa liste est enregistre \n");
}

void afficher_fichiercm()
{
	FILE * f;
    commande cmd;

	int i,e;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t************************************ Le fichier des commandes ******************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(1 , 6);
	printf("Commande");
	gotoxy(21 , 6);
	printf("Client");
	gotoxy(41 , 6);
	printf("Produit");
	gotoxy(61 , 6);
	printf("Quantite");
	gotoxy(81 , 6);
	printf("Date\n");

	for(i = 0 ; i < 100 ; i++)
	{
		printf("-");
	}

	e=8;

	f = fopen("commande","r");

	if(f == NULL)
    {
        printf("\nLe fichier des commandes n'existe pas\n");
        exit(-1);
    }

    while(fscanf(f,"%u %u %u %d %d %d %d", &cmd.id,  &cmd.idclient, &cmd.codeproduit, &cmd.quantite ,&cmd.datedecommande.j,&cmd.datedecommande.m,&cmd.datedecommande.a ) != EOF)
	{
		gotoxy(1 , e);
		printf("%u" , cmd.id);
		gotoxy(21 , e);
		printf("%u", cmd.idclient);
		gotoxy(41, e);
		printf("%u", cmd.codeproduit);
		gotoxy(61 , e);
		printf("%d" , cmd.quantite);
		gotoxy(81 , e);
		printf("%d/%d/%d" , cmd.datedecommande.j,cmd.datedecommande.m,cmd.datedecommande.a);
		e++;
	}

    fclose(f);

	printf("\n");

	for(i = 0 ; i < 100 ; i++)
		printf("-");

}

void chercher_fichiercm(unsigned int id)
{
	FILE * f;
	commande cmd;

	int found = 0;

    f = fopen("commande","r");

    if(f == NULL)
    {
        printf("\nLe fichier des commandes n'existe pas\n");
        exit(-1);
    }

    while( !feof(f) && found == 0 ){

        fscanf(f,"%u %u %u %d %d %d %d", &cmd.id,  &cmd.idclient, &cmd.codeproduit, &cmd.quantite ,&cmd.datedecommande.j,&cmd.datedecommande.m,&cmd.datedecommande.a);

        if(cmd.id == id)
        {
        	found = 1;
		}
    }

    if (found == 1)
    {
        printf("\n=> ID commande                : %u", cmd.id);
        printf("\n=> ID client                  : %u", cmd.idclient);
        printf("\n=> Code du produit            : %u", cmd.codeproduit);
        printf("\n=> La quantite de la commande : %d", cmd.quantite);
		printf("\n=> La date de commande        : %d / %d / %d ", cmd.datedecommande.j,cmd.datedecommande.m,cmd.datedecommande.a);

	}
	else
	{
		printf("\nLe code %u n'existe pas dans le fichier des commandes\n", id);
	}

    fclose(f);
}

void C_F()
{
    int quantite, ccommande , idPdt;
    unsigned int C_facture;
	float prix_unitaire, prix, tva_prix, prix_toutale, tva;

	FILE *f ;

	f = fopen("facture","r");

    if(f == NULL)
    {
        printf("\nLe fichier des factures n'existe pas\n");
        exit(-1);
    }

	while(fscanf(f,"%u %d %d %d %f %f %f %f %f", &C_facture , &ccommande, &idPdt , &quantite, &prix_unitaire, &tva, &prix, &tva_prix, &prix_toutale ) != EOF)
	{
		CF = C_facture;
	}
}

void facture()
{
    float prix_toutale, prix_unitaire, tva, prix, tva_prix;
    int quantite, idPdt, ccommande;
    commande cmd;
    FILE * f, * g , * f2;
    produit prd ;
    int found = 0;
    int foundp = 0;
    commande *c;

    printf("\n Entrer le code de la commande : ");
    scanf ("%d", &ccommande);

    f = fopen("commande","r");

    if(f == NULL)
    {
        printf("\nLe fichier des commandes n'existe pas\n");
        exit(-1);
    }

    while( !feof(f) && found == 0 ){

        fscanf(f,"%u %u %u %d %d %d %d", &cmd.id,  &cmd.idclient, &cmd.codeproduit, &cmd.quantite ,&cmd.datedecommande.j,&cmd.datedecommande.m,&cmd.datedecommande.a);

        if(cmd.id == ccommande)
        {
        	found = 1;
		}
    }

    if (found == 1)
    {
        idPdt = cmd.codeproduit;
        quantite = cmd.quantite;

        g = fopen("Produit","r");

        if(g == NULL)
        {
            printf("\nLe fichier des produits n'existe pas\n");
            exit(-1);
        }

        while( !feof(g) && foundp == 0 ){

            fscanf(g,"%u %s %f %f", &prd.code, prd.designationProduit, &prd.prixUnitaireProduit, &prd.tvaProduit);

            if(prd.code == idPdt)
            {
                prix_unitaire = prd.prixUnitaireProduit;
                tva = prd.tvaProduit ;
            }
        }

        fclose(g);

        prix = quantite * prix_unitaire ;
        tva_prix = prix * tva ;
        prix_toutale = prix + tva_prix ;

        system("cls");
        printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb FACTURE \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
        printf("\n\n\n\t\t\t\tCode facture                : %u ", ++CF);
        printf("\n\n\t\t\t\tLe code du commande         : %d ", ccommande);
        printf("\n\n\t\t\t\tLe code du produit          : %d ", idPdt);
        printf("\n\n\t\t\t\tLa quantite                 : %d ", quantite);
        printf("\n\n\t\t\t\tLe prix unitaire de produit : %f ",prix_unitaire);
        printf("\n\n\t\t\t\tTVA du produit              : %f ",tva);
        printf("\n\n\t\t\t\t-------------------------------------") ;
        printf("\n\n\t\t\t\tPrix sans tax : %f ",prix);
        printf("\n\n\t\t\t\tTax totale    : %f ", tva_prix);
        printf("\n\n\t\t\t\t-------------------------------------\n");
        printf("\n\n\t\t\t\tPrix totale   : %f ", prix_toutale);

        f2 = fopen("facture","a+");

        if(f2 == NULL)
        {
            printf("\nLe fichier des factures n'existe pas\n");
            exit(-1);
        }

        fprintf(f2,"%u \t %d \t %d \t %d \t %f \t %f \t %f \t %f \t %f  \n",CF , ccommande, idPdt , quantite, prix_unitaire, tva, prix, tva_prix, prix_toutale);

        fclose(f2);
	}
	else
	{
		printf("\nLe code de commande n'existe pas dans le fichier commande\n");
	}

    fclose(f);
}

void afficher_facture()
{
	FILE *f ;
	int quantite, ccommande , idPdt , i , e;
	float prix_unitaire, prix, tva_prix, prix_toutale, tva;

    system("cls");
	printf("\n\t********************************************************************************************************");
	printf("\n\t************************************** Le fichier des factures *****************************************");
	printf("\n\t********************************************************************************************************\n\n");

	gotoxy(0 , 6);
	printf("Facture");
	gotoxy(12 , 6);
	printf("Commande");
	gotoxy(24 , 6);
	printf("Produit");
	gotoxy(36 , 6);
	printf("Quantite");
	gotoxy(48 , 6);
	printf("Prix Unitaire\n");
	gotoxy(64 , 6);
	printf("TVA\n");
	gotoxy(76 , 6);
	printf("Prix sans tax\n");
	gotoxy(94 , 6);
	printf("tax totale\n");
	gotoxy(108 , 6);
	printf("prix totale\n");

	for(i = 0 ; i < 120 ; i++)
	{
		printf("-");
	}

	e = 8;

	f = fopen("facture","r");

	if(f == NULL)
    {
        printf("pb memory\n");
        exit(-1);
    }

    while(fscanf(f,"%u %d %d %d %f %f %f %f %f", &CF , &ccommande, &idPdt , &quantite, &prix_unitaire, &tva, &prix, &tva_prix, &prix_toutale ) != EOF)
	{
		gotoxy(0 , e);
		printf("%u" , CF);
		gotoxy(12 , e);
		printf("%d", ccommande);
		gotoxy(24 , e);
		printf("%d", idPdt);
		gotoxy(36, e);
		printf("%d", quantite);
		gotoxy(48, e);
		printf("%f", prix_unitaire);
		gotoxy(64 , e);
		printf("%f" , tva);
		gotoxy(76, e);
		printf("%f" , prix);
		gotoxy(94 , e);
		printf("%f" , tva_prix);
		gotoxy(108 , e);
		printf("%f" , prix_toutale);
		e++;
	}

    fclose(f);

	printf("\n");

	for(i = 0 ; i < 120 ; i++)
		printf("-");
}

void chercher_fichierf(unsigned int id)
{
	FILE * f;
	int quantite, ccommande , idPdt;
	float prix_unitaire, prix, tva_prix, prix_toutale, tva;

	int found = 0;

    f = fopen("facture","r");

    if(f == NULL)
    {
        printf("\nLe fichier des factures n'existe pas\n");
        exit(-1);
    }

    while( !feof(f) && found == 0 ){

        fscanf(f,"%u %d %d %d %f %f %f %f %f", &CF , &ccommande, &idPdt , &quantite, &prix_unitaire, &tva, &prix, &tva_prix, &prix_toutale );

        if(CF == id)
        {
        	found = 1;
		}
    }

    if (found == 1)
    {
        printf("\n=> ID facture                 : %u" , CF);
        printf("\n=> ID commande                : %d" , ccommande);
        printf("\n=> ID produit                 : %d" , idPdt);
        printf("\n=> La quantite de la commande : %d" , quantite);
        printf("\n=> Prix unitaire              : %f" , prix_unitaire);
        printf("\n=> TVA                        : %f" , tva);
        printf("\n=> Prix sans tax              : %f" , prix);
        printf("\n=> Tax total                  : %f" , tva_prix);
        printf("\n=> Prix total                 : %f" , prix_toutale);
	}
	else
	{
		printf("\nLe code %u n'existe pas dans le fichier des factures\n", id);
	}

    fclose(f);
}

void gestionCommande()
{
    commande * liste;
    unsigned int ch, choix, id;

    liste = NULL;

    do
    {
        system("cls");
        printf("\n-----------------------------------------------------------------------------------------------------------------------");
        gotoxy(40 , 2);
        printf("MENU COMMANDES ET FACTURES");
        printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n\n");
        printf("\t\t\t 0 : Ajouter une commande\n");
        printf("\t\t\t 1 : Affichage des commandes de gauche a droite\n");
        printf("\t\t\t 2 : Affichage des commandes de droite a gauche\n");
        printf("\t\t\t 3 : Modifier une commande\n");
        printf("\t\t\t 4 : Supprimer une commande\n\n");
        printf("\t\t\t 5 : Enregistrer les commandes dans le fichier\n");
        printf("\t\t\t 6 : Afficher le fichier des commandes\n");
        printf("\t\t\t 7 : Chercher dans le fichier des commande \n\n");
        printf("\t\t\t 8 : Generer une facture \n");
        printf("\t\t\t 9 : Afficher le fichier des factures \n");
        printf("\t\t\t10 : Chercher dans le fichier des factures \n\n");
        printf("\t\t\t11 : Retour\n");
        printf("\n\n\t\t\t\t Saisir votre choix [0 11] : ") ;
        scanf("%u",&ch);
        switch(ch)
        {
            case 0:
                system("cls");
                C_CM();
                liste = sauvegardecm(liste);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 1:
                affichercommande_G(liste);
                break;
            case 2:
                affichercommande_D(liste);
                break;
            case 3:
                system("cls");
                printf("\n\t => Donner le code de commande a modifier : ");
                scanf("%u", &id);
                modifiercm(liste, id);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 4:
                system("cls");
                printf("\n\t => Donner le code de commande a supprimer : ");
                scanf("%u", &id);
                liste = supprimercm(liste,id);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 5:
                system("cls");
                enregistrercm(liste);
                liste = NULL;
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 6:
                system("cls");
                afficher_fichiercm();
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 7:
                system("cls");
                printf("\n\t => Donner le code de commande a chercher : ");
                scanf("%u", &id);
                chercher_fichiercm(id);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 8:
                system("cls");
                C_F();
                facture();
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 9:
                system("cls");
                afficher_facture();
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 10:
                system("cls");
                printf("\n\t => Donner le code de la facture a chercher : ");
                scanf("%u", &id);
                chercher_fichierf(id);
                printf("\t\t\n\n\nClic entrer .....");
                getch();
                break;
            case 11:
                mainmenu();
                break;
            default:
                printf("choix invalide\n");
                break;
        }
    }
    while( choix != 11 );

    exit(0);
}
