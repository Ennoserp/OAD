#ifndef HVRP
#define HVRP

#include <iostream>

const int nmaxtournee = 50;				// nombre maximal de tourn�es r�alis�es
const int nmax = 500;					// nombre max de sommets
const int nmaxtype = 10;				// nombre maximal de types de camions
const int namx_som_par_tournee = 30;	// pas repr�sentatif
const int it_max = 15;					// nombre max de coups autoris�s pour le mouvement 2-opt

typedef struct T_type_camion {
	int   nb;							// nombre de camions
	int   capacite;						// capacite de ce type de camions
	int   cf;							// co�t fixe ex: 10�
	float cv;							// co�t variable ex: 0.1�/km
}T_type_camion;


typedef struct T_instance {
	int    nb_client;						// nombre de clients
	int    qte[nmax + 1];					// tableau des quantit�s � pr�lever
	double distance[nmax + 1][nmax + 1];    // matrices des distances
	int    nbtypecam;						// nombre de types de camions dans cette instance
	int    V_som[6] = { 99999 };
	T_type_camion liste_types[nmaxtype];
}T_instance;


typedef struct T_tournee {
	int   type_camion;					// type du camion sur la tourn�e
	int   nb_sauts;						// nombre de villes visit�es pendant la tourn�e
	int   liste_sauts[100];				// matrice des sauts /!\ � modifier

	float cout;							// cout de la tourn�e en euros
	int	  volume;						// volume d�plac� par la tourn�e
}T_tournee;


typedef struct T_solution {
	int		  cout_total;				// cout total de la solution en euros
	int       nb_tournees;				// nombre de tourn�es dans cette instance
	T_tournee liste[nmaxtournee];		// liste des tourn�es � r�aliser
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