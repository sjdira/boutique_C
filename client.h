typedef struct Client
{
	unsigned int code ;
	char nom[30] ;
    char prenom[15];
    char adresse[30];
    char tel[20];
	struct Client * pre;
    struct Client * svt;
}client;

void gestionClient();
int nbrLigne();
