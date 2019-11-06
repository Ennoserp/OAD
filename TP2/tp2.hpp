#ifndef TP2_HPP
#define TP2_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

#define SIZE_VECTOR 4

const int max_piece = 50;
const int max_machine = 50;
const int ite_max = 200;
const float inf = 999;
const int nombre_voisin = 5;
const int taille_hash = 100000;


/**
 * @brief Structure stockant les données lues dans le fichier .txt
 */
typedef struct instance {
	int n;
	int m;
	int M[max_piece * max_machine];
	int P[max_piece * max_machine];
} instance_t;

/**
 * @brief Structure stockant les données relatives aux graphes en cours de traitement
 */
typedef struct solution
{
	int VB[max_machine * max_piece];
	int pred[max_machine * max_piece];
	int MP[max_machine];
	int T[max_machine][max_piece];
	int ST[max_machine * max_piece];
	int N[max_machine];
	int total;
	int last_sommet;
}solution_t;

void 		lire_instance		(std::string nom_fichier, instance_t& instance);
void 		afficher_VB			(solution_t s, instance_t& instance);
void 		evaluer				(instance_t& g, solution& s);
void 		init_solution		(instance_t& g, solution_t& s);
void 		position			(instance_t& g, solution_t& s, int i, int j, int& Posi, int& Posj);
void 		recherche_local		(instance_t& g, solution_t& s);
void 		init_hash			(instance_t g, int* hash);
int 		tester_double		(instance_t g, solution_t& s, int* hash);
int 		h					(instance_t& g, solution_t& s);
solution_t 	generer_voisin		(instance_t g, solution_t& s);
void 		GRASP				(instance_t g, solution_t& s);

#endif