#ifndef HVRP
#define HVRP

#include <iostream>

const int nmaxtournee = 50;				// nombre maximal de tourn�es r�alis�es
const int nmax = 500;					// nombre max de sommets
const int nmaxtype = 10;				// nombre maximal de types de camions
const int namx_som_par_tournee = 30;	// pas repr�sentatif


typedef struct T_type_camion {
	int nb;								// nombre de camions
	int capacite;						// capacite de ce type de camions
	int cf;								// co�t fixe ex:10�
	float cv;							// co�t variable ex: 0.1�/km
}T_type_camion;


typedef struct T_instance {
	int nb_client;						// nombre de clients
	int qte[nmax + 1];					// tableau des quantit�s � pr�lever
	double distance[nmax + 1][nmax + 1];// matrices des distances
	int nbtypecam;						// nombre de types de camions dans cette instance
	T_type_camion liste_types[nmaxtype];
	int sauts[100];						// pour plus proches voisins
}T_instance;


typedef struct T_tournee {
	int nb_sauts;						// nombre de villes visit�es pendant la tourn�e
	int liste_sauts[100];				// matrice des sauts /!\ � modifier
	int camion;							// nombre de camions sur la tourn�e
	float cout;							// cout de la tourn�e
}T_tournee;


typedef struct T_solution {
	int nb_tournees;					// nombre de tourn�es dans cette instance
	T_tournee liste[nmaxtournee];		// liste des tourn�es � r�aliser
}T_solution;



void lire_instance_type1(std::string nom_fichier, T_instance& instance);
void lire_instance_type2(std::string nom_fichier, T_instance& instance);
void operateur_2_opt_inter_tournee();
void operateur_2_opt();
void plus_proches_voisins(T_instance& instance, int depart);


#endif