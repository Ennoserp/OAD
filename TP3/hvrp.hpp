#ifndef HVRP
#define HVRP

#include <iostream>

const int nmaxtournee = 50;				// nombre maximal de tournées réalisées
const int nmax = 500;					// nombre max de sommets
const int nmaxtype = 10;				// nombre maximal de types de camions
const int namx_som_par_tournee = 30;	// pas représentatif


typedef struct T_type_camion {
	int nb;								// nombre de camions
	int capacite;						// capacite de ce type de camions
	int cf;								// coût fixe ex:10€
	float cv;							// coût variable ex: 0.1€/km
}T_type_camion;


typedef struct T_instance {
	int nb_client;						// nombre de clients
	int qte[nmax + 1];					// tableau des quantités à prélever
	double distance[nmax + 1][nmax + 1];// matrices des distances
	int nbtypecam;						// nombre de types de camions dans cette instance
	T_type_camion liste_types[nmaxtype];
	int sauts[100];						// pour plus proches voisins
}T_instance;


typedef struct T_tournee {
	int nb_sauts;						// nombre de villes visitées pendant la tournée
	int liste_sauts[100];				// matrice des sauts /!\ à modifier
	int camion;							// nombre de camions sur la tournée
	float cout;							// cout de la tournée
}T_tournee;


typedef struct T_solution {
	int nb_tournees;					// nombre de tournées dans cette instance
	T_tournee liste[nmaxtournee];		// liste des tournées à réaliser
}T_solution;



void lire_instance_type1(std::string nom_fichier, T_instance& instance);
void lire_instance_type2(std::string nom_fichier, T_instance& instance);
void operateur_2_opt_inter_tournee();
void operateur_2_opt();
void plus_proches_voisins(T_instance& instance, int depart);


#endif