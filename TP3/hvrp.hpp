#ifndef HVRP
#define HVRP

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

const int nmaxtournee = 50;				// nombre maximal de tournées réalisées
const int nmax = 500;					// nombre max de sommets
const int nmaxtype = 10;				// nombre maximal de types de camions
const int namx_som_par_tournee = 30;	// pas représentatif
const int it_max = 15;					// nombre max de coups autorisés pour le mouvement 2-opt

typedef struct T_type_camion {
	int   nb = 0;							// nombre de camions
	int   capacite = 0;						// capacite de ce type de camions
	int   cf = 0;							// coût fixe ex: 10€
	float cv = 0;							// coût variable ex: 0.1€/km
}T_type_camion;


typedef struct T_instance {
	int    nb_client = 0;					// nombre de clients
	int    qte[nmax + 1] = { 0 };			// tableau des quantités à prélever
	double distance[nmax + 1][nmax + 1];    // matrices des distances
	int    nbtypecam = 0;					// nombre de types de camions dans cette instance
	int    V_som[6] = { 0 };				//liste permettant de mémoriser les plus proches voisins d'un sommet
	T_type_camion liste_types[nmaxtype];
}T_instance;


typedef struct T_tournee {
	int   type_camion = 0;					// type du camion sur la tournée
	int   nb_sauts = 0;						// nombre de villes visitées pendant la tournée
	int   liste_sauts[100];	    			// matrice des sauts /!\ à modifier

	float cout = 0.;						// cout de la tournée en euros
	int	  volume = 0;						// volume déplacé par la tournée
}T_tournee;


typedef struct T_solution {
	int		  cout_total = 0;				// cout total de la solution en euros
	int       nb_tournees = 0;				// nombre de tournées dans cette instance
	T_tournee liste[nmaxtournee];	    	// liste des tournées à réaliser
}T_solution;



void lire_instance_type1(std::string nom_fichier, T_instance& instance);
void lire_instance_type2(std::string nom_fichier, T_instance& instance);
void operateur_2_opt_inter_tournee();
void operateur_2_opt(T_instance& instance, T_tournee& tournee, int it_max);
void initialiser_voisins(T_instance& instance);
void trouver_proches_voisins(T_instance& instance,int sommets_restants[], int depart);
void tri(T_instance& instance, int i, int depart);
void rotation(T_tournee& tournee, int i, int j);
void tour_geant_ppv(T_instance& instance, T_tournee& tournee);
void tour_geant_ppvrand(T_instance& instance, T_tournee& tournee);
void tour_geant_ordre_num(T_instance& instance, T_tournee& tournee);
void afficher_tournee(T_tournee tournee);
int choix_voisin_aleatoire(int nb_sommets_restants);

void init_tournee(T_tournee tournee);
void evaluer_tournee(T_tournee tournee);
void copier_tournee(T_tournee tournee_A, T_tournee tournee_B);

#endif