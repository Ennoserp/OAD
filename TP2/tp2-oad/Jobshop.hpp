#ifndef JOBSHOP
#define JOBSHOP

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

const int n_max=50;									// Nombre max de pièces
const int m_max=30;									// Nombre max de machines
const int max = n_max * m_max;						// Nombre d'opérations éffectuées maximal

const int taille_hash = 99999; // ctrl+v

/************************************************/
/*											    */
/*					STRUCTURES					*/
/*												*/
/************************************************/

typedef struct T_instance {

	int nb_piece;									// Nombre de pièces
	int nb_machine;									// Nombre de machines
	int NT;											// = nb_machine * nb_piece (nombre d'opérations effectuées)
	int p_prim[max];								// Contient les durées que chaque pièce passe sur les machines dans l'ordre où elles rencontrent les machines ex: 10 / 5 / 4 /30
	int m_prim[max];								// Contient les numéros des machines (ordonnées) sur lesquelles passent les pièces
	int N[n_max] = { 0 };							// N[i]: nombre de fois que l'on a rencontré la pièce i dans le vecteur V;

}T_instance;


typedef struct T_solution {

	int V[max];										// Vecteur de Bierwith
	int st[max] = { 0 };							// Tableau des starting time
	int pred[max] = { -1 };							// Tableau des prédécesseurs
	int T[m_max][n_max];							// T[i][j] = numéro de l'opération pour la j-ème opération sur la pièce i
	int MP[m_max];
	int total;										// Coût total
	int dernier_sommet;	// ctrl+v
}T_solution;



/************************************************/
/*												*/
/*					PROTOTYPES					*/
/*												*/
/************************************************/


void lire_fichier(std::string, T_instance&);
void afficher_instance(T_instance&);
void creer_prime(T_instance&);

void evaluer(T_solution&, T_instance&);
void recherche_locale(T_solution& sol, T_instance& instance);
void generer_vecteur_alea(T_solution&, T_instance&);
void afficher_vecteur(T_solution&, T_instance&);
void copie(int Tableau_Original[], int Tableau_Copie[], T_instance& instance);
void init_solution(T_solution& sol, T_instance& instance);
void position(T_solution& sol, T_instance& instance, int i, int j, int& Posi, int& Posj);


// CC ctrl+v

int h(T_instance& instance, T_solution& sol);
void init_hash(T_instance instance, int* hash);
int tester_double(T_instance instance, T_solution& s, int* hash);
T_solution generer_voisin(T_instance instance, T_solution& sol);
void GRASP(T_instance instance, T_solution& sol);


#endif