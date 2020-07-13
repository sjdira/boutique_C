typedef struct Produit
{
	unsigned int code ;
	char designationProduit[30] ;
	float prixUnitaireProduit ;
	float tvaProduit ;
	struct Produit * svt ;
	struct Produit * pre ;
} produit;

void gestionProduit();
int nbrLignepr();
