#ifndef JOBSHOP
#define JOBSHOP

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

const int n_max=50;
const int m_max=50;
const int max = n_max * m_max +2;


/*											    */
/*					STRUCTURES					*/
/*												*/

typedef struct T_instance {

	int nb_piece; //nb pieces
	int nb_machine; //nb machines
	int NT;// = nb_machine * nb_piece; //nb opérations

	int m[n_max][m_max];
	int p[n_max][m_max];

	int p_prim[max]; //contient les durées que chaque pièce passe sur les machines dans l'ordre où elles rencontrent les machines ex: 10 / 5 / 4 /30
	int m_prim[max]; //contient les numéros des machines (ordonnées) sur lesquelles passent les pièces

	int N[n_max] = { 0 }; //N[i]: nb de fois qu'on a rencontré la pièce i dans le vecteur V;

}T_instance;


typedef struct T_solution {

	int V[max]; //vecteur de Bierwith
	int st[max] = { 0 }; //tableau des starting time
	int pred[max] = { -1 }; //tableau des prédécesseurs
	int T[m_max][n_max];
	int n[m_max];
	int MP[m_max];
	int total;
	int dernier_sommet;
}T_solution;



/*											    */
/*					PROTOTYPES					*/
/*												*/


int lire_fichier(std::string, T_instance&);
void afficher_instance(T_instance&);
void creer_prime(T_instance&);

void evaluer(T_solution&, T_instance&);
void recherche_locale(T_solution& sol, T_instance& instance);
void generer_vecteur_alea(T_solution&, T_instance&);
void afficher_vecteur(T_solution&, T_instance&);
void copie(int Tableau_Original[], int Tableau_Copie[]);
void init_solution(T_instance& instance, T_solution& solution);
void position(T_instance& instance, T_solution& sol, int i, int j, int& Posi, int& Posj);



#endif