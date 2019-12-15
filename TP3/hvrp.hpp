#ifndef HVRP
#define HVRP

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

const int nmaxtournee = 50;				// nombre maximal de tournées réalisées
const int nmax = 500;					// nombre max de sommets
const int nmaxtype = 10;				// nombre maximal de types de camions
const int nmax_som_par_tournee = 30;	// pas représentatif
const int it_max = 15;					// nombre max de coups autorisés pour le mouvement 2-opt

const int NB_TOUR_MAX = 100;			//nombre de tour maximal où on fait tourner les opérateurs


typedef struct T_camion {
	int   nb = 0;							// nombre de camions
	int   capacite = 0;						// capacite de ce type de camions
	int   cf = 0;							// coût fixe ex: 10€
	float cv = 0;							// coût variable ex: 0.1€/km
}T_camion;


typedef struct T_instance {
	int    nb_client = 0;					// nombre de clients
	int    qte[nmax + 1] = { 0 };			// tableau des quantités à prélever
	double distance[nmax + 1][nmax + 1];    // matrices des distances
	int    nbtypecam = 0;					// nombre de types de camions dans cette instance
	int    V_som[6] = { 0 };				//liste permettant de mémoriser les plus proches voisins d'un sommet
	T_camion liste_types[nmaxtype];
}T_instance;


typedef struct T_tournee {
	int   type_camion = 0;					// type du camion sur la tournée
	int   nb_sauts = 0;						// nombre de villes visitées pendant la tournée
	int   liste_sauts[100] = { 0 };	    			// matrice des sauts /!\ à modifier

	double cout = 0.;						// cout de la tournée en euros
	int	  volume = 0;						// volume déplacé par la tournée
}T_tournee;


typedef struct T_label {
	int capacite = 0;
	double prix = 0;
	int pere[100] = { 0 };
	int nb_peres = 0;
	int reste_camions[10] = { 0 };
	int nb_sauts[100] = { 0 };
	bool labels =  false;
	int type_camion[100] = { -1 };
}T_label;


typedef struct T_tour_geant {
	int nb_sauts = 0;
	int liste_sauts[100];
	T_label liste_labels[100][100]; 
	int nb_labels[100] = { 0 };
}T_tour_geant;


typedef struct T_solution {
	int		  cout_total = 0;				// cout total de la solution en euros
	int       nb_tournees = 0;				// nombre de tournées dans cette instance
	T_tournee liste_tournees[nmaxtournee];	    	// liste des tournées à réaliser
}T_solution;

void lire_instance_type1(std::string nom_fichier, T_instance& instance);

void lire_instance_type2(std::string nom_fichier, T_instance& instance);

void operateur_2_opt_inter_tournee_bis(T_instance& instance, T_tournee& tournee1, T_tournee& tournee2, int it_max);

void operateur_2_opt(T_instance instance, T_tournee& tournee);

void deplacement_sommet(T_instance ins, T_tournee& tournee);

void initialiser_voisins(T_instance& instance);

void trouver_proches_voisins(T_instance& instance,int sommets_restants[], int depart);

void tri(T_instance& instance, int i, int depart);

void rotation(T_tournee& tournee, int i, int j);
void rotation_inter_tournee(T_tournee& tournee1, T_tournee& tournee2, int i, int j);

void vider_tournee_sup_i(T_tournee& tournee, int i);

void tour_geant_ppv(T_instance& instance, T_tour_geant& tournee);
void tour_geant_ppvrand(T_instance& instance, T_tour_geant& tournee);
void tour_geant_ordre_num(T_instance& instance, T_tour_geant& tournee);

void operateur_2_opt_inter_tournee(T_instance& instance, T_tournee& tournee1, T_tournee& tournee2, int it_max);

void afficher_tournee(T_tournee tournee);

void afficher_tour_geant(T_tour_geant tournee);

int choix_voisin_aleatoire(int nb_sommets_restants);

void init_tournee(T_tournee& tournee);

void copier_tournee(T_tournee tournee_A, T_tournee& tournee_B);

void evaluer_tournee(T_tournee& tournee, T_instance instance);

void copier_label(T_label l1, T_label& l2);

bool domine(T_label l1, T_label l2, T_instance ins);

void tri_labels(T_tour_geant& tg, int indice_sommet);

void SPLIT(T_tour_geant& tour_geant, T_solution& sol, T_instance& instance);

void recherche_locale(T_instance ins, T_solution sol);

#endif