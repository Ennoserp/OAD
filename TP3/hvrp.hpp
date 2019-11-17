#ifndef HVRP
#define HVRP

#include <iostream>

const int nmaxtournee = 50;				// nombre maximal de tournées réalisées
const int nmax = 500;					// nombre max de sommets
const int nmaxtype = 10;				// nombre maximal de types de camions
const int namx_som_par_tournee = 30;	// pas représentatif
const int it_max = 15;					// nombre max de coups autorisés pour le mouvement 2-opt

typedef struct T_type_camion {
	int   nb;							// nombre de camions
	int   capacite;						// capacite de ce type de camions
	int   cf;							// coût fixe ex: 10€
	float cv;							// coût variable ex: 0.1€/km
}T_type_camion;


typedef struct T_instance {
	int    nb_client;						// nombre de clients
	int    qte[nmax + 1];					// tableau des quantités à prélever
	double distance[nmax + 1][nmax + 1];    // matrices des distances
	int    nbtypecam;						// nombre de types de camions dans cette instance
	int    V_som[6] = { 99999 };
	T_type_camion liste_types[nmaxtype];
}T_instance;


typedef struct T_tournee {
	int   type_camion;					// type du camion sur la tournée
	int   nb_sauts;						// nombre de villes visitées pendant la tournée
	int   liste_sauts[100];				// matrice des sauts /!\ à modifier

	float cout;							// cout de la tournée en euros
	int	  volume;						// volume déplacé par la tournée
}T_tournee;


typedef struct T_solution {
	int		  cout_total;				// cout total de la solution en euros
	int       nb_tournees;				// nombre de tournées dans cette instance
	T_tournee liste[nmaxtournee];		// liste des tournées à réaliser
}T_solution;



void lire_instance_type1(std::string nom_fichier, T_instance& instance);
void lire_instance_type2(std::string nom_fichier, T_instance& instance);
void operateur_2_opt_inter_tournee();
void operateur_2_opt(T_instance& instance, T_tournee& tournee, int it_max);
void initialiser_voisins(T_instance& instance);
void plus_proches_voisins(T_instance& instance, int depart);
void tri(T_instance& instance, int i, int depart);
void rotation(T_tournee tournee, int i, int j);
void tour_geant(T_instance& instance, T_tournee& tournee);


#endif