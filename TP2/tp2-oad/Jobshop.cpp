#include "Jobshop.hpp"
using namespace std;
/********************************************************************************************/
/*																							*/
/**/
/*																							*/
/* Entrée:				-*/
/*																							*/
/* Sortie:				-*/
/*																							*/
/********************************************************************************************/



/********************************************************************************************/
/*																							*/
/*  Procédure permettant de lire un fichier texte d'instance et d'initialiser une instance  */
/*																							*/
/* Entrée:				-nom_fichier				Nom du fichier texte à ouvrir			*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void lire_fichier(string nom_fichier, T_instance& instance) {
	ifstream fichier(nom_fichier);
	fichier >> instance.nb_piece;
	fichier >> instance.nb_machine;

	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			fichier >> instance.m_prim[i * instance.nb_machine + j];
			fichier >> instance.p_prim[i * instance.nb_machine + j];
		}
	}
	fichier.close();
	instance.NT = instance.nb_machine * instance.nb_piece;
}

/********************************************************************************************/
/*																							*/
/*   Procédure permettant d'afficher l'odre des machines sur lesquelles les pièces passent  */
/*   ainsi que les durées des opérations.													*/
/*																							*/
/* Entrée:				-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void afficher_instance(T_instance& instance) {
	cout << "nombre de pieces : " << instance.nb_piece << endl;
	cout << "nombre de machines : " << instance.nb_machine << endl;

	cout << "tableau des machines" << endl;
	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			cout << instance.m_prim[i * instance.nb_machine + j] << " ";
		}
		cout << endl;
	}

	cout << "tableau des durees" << endl;
	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			cout << instance.p_prim[i * instance.nb_machine + j] << " ";
		}
		cout << endl;
	}
}

/********************************************************************************************/
/*																							*/
/* Procédure permettant de créer une solution du Job-Shop à partir d'un vecteur de Bierwirth*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void evaluer(T_solution& sol, T_instance& instance) {
	// Initialisation des variables
	int ind_j, machine, prec, pos;
	int MP[m_max] = { -1 };														// MP[i]: numéro de la dernière opération éffectuée sur la machine i


	// Algorithme
	for (int i = 0; i < instance.NT; i++) {


		ind_j = sol.V[i];
		instance.N[ind_j] = instance.N[ind_j] + 1;
		pos = sol.T[ind_j][instance.N[ind_j]-1];

		if (instance.N[ind_j] > 1) {									// Alors on a déjà réalisé une opération sur la pièce i
			prec = pos - 1;
			if (sol.st[prec] + instance.p_prim[prec] > sol.st[pos]) {
				sol.st[pos] = sol.st[prec] + instance.p_prim[prec];
				sol.pred[pos] = prec;
			}
		}

		machine = instance.m_prim[pos];									// Numéro de la machine à utiliser

		if (MP[machine] != 1) {
			prec = MP[machine];
			if (sol.st[prec] + instance.p_prim[prec] > sol.st[pos]) {
				sol.st[pos] = sol.st[prec] + instance.p_prim[prec];
				sol.pred[pos] = prec;
			}
		}
		MP[machine] = pos;
	}


	//
	for (int i = 1; i <= instance.nb_piece; i++) {
		prec = i * instance.nb_machine - 1;
		if (sol.st[prec] + instance.p_prim[prec] > sol.total) {
			sol.dernier_sommet = prec;
			sol.total = sol.st[prec] + instance.p_prim[prec];
		}
	}

}

/********************************************************************************************/
/*																							*/
/*   Procédure permettant d'optimiser une solution obtenue à partir du vecteur de Bierwirth  */
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void recherche_locale(T_solution& sol, T_instance& instance) {
	int nb_iteration = 0;
	int itmax = 200;// nb d'iterations maximal
	int i = sol.dernier_sommet;
	int j = sol.pred[i];
	int position_i;
	int position_j;
	
	while((j != 0 ) && (nb_iteration < itmax)) {
		nb_iteration++;
		if(instance.m_prim[i] == instance.m_prim[j]) {

			//Calculer la position de i et de j pour faire la permutation
			position(sol, instance, i, j, position_i, position_j);

			T_solution solution_nouv;
			init_solution(solution_nouv, instance);
			copie(sol.V,solution_nouv.V, instance);
			solution_nouv.V[position_i] = sol.V[position_j];
			solution_nouv.V[position_j] = sol.V[position_i];

			evaluer(solution_nouv, instance);

			if (solution_nouv.total < sol.total) {
				sol = solution_nouv;
				i = sol.dernier_sommet;
				j = sol.pred[i];
			}
			else {
				i = j;
				j = sol.pred[i];
			}
		}
		else {
			i = j;
			j = sol.pred[j];
		}
	}


}

/********************************************************************************************/
/*																							*/
/*					Procédure permettant de générer un vecteur de Birwirth					*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void generer_vecteur_alea(T_solution& sol, T_instance& instance) {

	int nb_restant = instance.nb_piece;
	int x;															// Variable aléatoire entre 1 et nb_restant
	int indice = 0;
	int TN[m_max];													// TN[i] = i
	int NN[m_max];													// NN[i]: nombre de fois qu'il reste à appeler la pièce i

	for (int i = 0; i < instance.nb_piece; i++) {					// Initialisation du tableau TN (et NN)
		TN[i] = i;
		NN[i] = instance.nb_machine;
	}

	while (nb_restant > 0) {
		x = rand() % nb_restant + 1;
		sol.V[indice] = TN[x - 1];
		indice++;
		NN[x - 1]--;

		if (NN[x - 1] == 0) {										// Si une case est vide on "réduit" la taille du tableau
			TN[x - 1] = TN[nb_restant - 1];
			NN[x - 1] = NN[nb_restant - 1];
			nb_restant--;
		}
	}
}

/********************************************************************************************/
/*																							*/
/*					Procédure permettant d'afficher le vecteur de Bierwirth					*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void afficher_vecteur(T_solution& sol, T_instance& instance) {
	cout << "V= ";
	for (int i = 0; i < instance.NT; i++) {
		cout << sol.V[i] << " ";
	}
	cout << endl;
}

/********************************************************************************************/
/*																							*/
/*				Procédure permettant de copier les valeurs d'un tableau original			*/
/*				vers un tableau_copie														*/
/*																							*/
/* Entrée:				-Tableau_Original[]:		Tableau que l'on souhaite copier		*/
/*						-Tableau_Copie:				Copie du tableau original				*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void copie(int Tableau_Original[], int Tableau_Copie[], T_instance& instance) {
	for (int a = 0; a < instance.NT ; a++)  {
		Tableau_Copie[a] = Tableau_Original[a];
	}
}


/********************************************************************************************/
/*																							*/
/*				Procédure permettant d'initialiser une solution au Job-Shop					*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void init_solution(T_solution& sol, T_instance& instance) {

	generer_vecteur_alea(sol, instance);

	for (int i = 0; i <= instance.nb_piece; i++) {
		instance.N[i] = 0;
	}

	for (int i = 0; i < instance.nb_machine; i++) {
		sol.MP[i] = -1;
	}

	for (int i = 0; i < instance.nb_piece; i++) {
		for (int j = 0; j < instance.nb_machine; j++) {
			sol.T[i][j] = i * instance.nb_machine + j;
			sol.st[i * instance.nb_machine + j] = 0;
			sol.pred[i * instance.nb_machine + j] = -1;
		}
	}
	sol.total = 0;
}


/********************************************************************************************/
/*																							*/
/*				Procédure permettant de calculer les positions des sommets i et j			*/		
/*				dans le vecteur de Bierwirth pour faire la permutation des sommets			*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*						-i:							Position de i							*/
/*						-j:							Position de j							*/
/*						-Posi:						Position de i dans le vecteur			*/
/*						-Posj:						Position de j dans le vecteur			*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void position(T_solution& sol, T_instance& instance, int i, int j, int& Posi, int& Posj) {
	int Pi = i / instance.nb_machine;
	int Pj = j / instance.nb_machine;

	int occ_i = 0;
	int occ_j = 0;

	int Mai = i % instance.nb_machine;
	int Maj = j % instance.nb_machine;

	Posi = 0;
	while (occ_i != Mai || sol.V[Posi] != Pi) {
		if (sol.V[Posi] == Pi)
			occ_i++;
		Posi++;
	}

	Posj = 0;
	while (occ_j != Maj || sol.V[Posj] != Pj) {
		if (sol.V[Posj] == Pj)
			occ_j++;
		Posj++;
	}
}




/********************************************************************************************/
/*																							*/
/*				Procédure permettant d'initialiser la table de hachage						*/
/*																							*/
/* Entrée:				-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*						-hash:						Table de hachage						*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
void init_hash(T_instance instance, int* hash) {
	for (int i = 0; i < instance.nb_piece * instance.nb_machine; i++) {
		hash[i] = 0;
	}
}


/********************************************************************************************/
/*																							*/
/*					Procédure permettant de vérifier qu'une solution						*/	
/*					générée ne l'a pas déjà été												*/
/*																							*/
/* Entrée:				-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*						-hash:						Table de hachage						*/
/*																							*/
/* Sortie:				-Aucune																*/
/*																							*/
/********************************************************************************************/
int tester_double(T_solution& sol, T_instance instance, int* hash) {
	int k = h(sol, instance);

	if (!hash[k]) {
		hash[k] = 1;
		return 1;				// La solution n'a pas été générée
	}
	else {
		return 0;				// La solution a déjà été générée
	}
}


/********************************************************************************************/
/*																							*/
/*			Procédure permettant de calculer la fonction de hachage d'une solution			*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-hash:						Valeur de la fonction de hachage		*/
/*																							*/
/********************************************************************************************/
int h(T_solution& sol, T_instance& instance) {
	int hash = 0;
	for (int j = 0; j < instance.nb_piece * instance.nb_machine; j++) {
		hash += sol.st[j];
	}
	hash = hash % taille_hash;
	return hash;
}


/********************************************************************************************/
/*																							*/
/*					Procédure permettant de créer le voisin d'une solution					*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-solution_nouv:				Voisin de la solution sol				*/
/*																							*/
/********************************************************************************************/
T_solution generer_voisin(T_solution& sol, T_instance instance) {
	int rand1, rand2;
	T_solution solution_nouv;
	init_solution(solution_nouv, instance);

	for (int k = 0; k <= instance.NT; k++) {
		solution_nouv.V[k] = sol.V[k];
	}

	rand1 = std::rand() % (instance.nb_piece * instance.nb_machine);
	rand2 = std::rand() % (instance.nb_piece * instance.nb_machine);

	solution_nouv.V[rand1] = solution_nouv.V[rand2];
	solution_nouv.V[rand2] = solution_nouv.V[rand1];

	return solution_nouv;
}


/********************************************************************************************/
/*																							*/
/*		Procédure permettant de créer plusieurs voisin d'une solution pour la modifier 		*/
/*		et la faire converger vers une solition dite optimale						 		*/
/*																							*/
/* Entrée:				-sol						Variable contenant les données de la	*/
/*													solution obtenue						*/
/*						-instance:					Variable contenant les données			*/
/*													du Job-Shop								*/
/*																							*/
/* Sortie:				-solution_nouv:				Voisin de la solution sol				*/
/*																							*/
/********************************************************************************************/
void GRASP(T_solution& sol, T_instance instance) {
	T_solution tableau_voisins[5];
	int numero_voisin;
	int compteur;
	int hash[taille_hash];

	init_hash(instance, hash);

	for (int i = 0; i < 1000; i++) {
		numero_voisin = 0;
		compteur = 0;
		while (numero_voisin != 5 && compteur < 10) {
			T_solution solution_nouv = generer_voisin(sol, instance);
			init_solution(solution_nouv, instance);
			evaluer(solution_nouv, instance);
			recherche_locale(solution_nouv, instance);

			if (tester_double(solution_nouv, instance, hash)) { // Alors la solution n'a jamais été générée
				tableau_voisins[numero_voisin] = solution_nouv;
				numero_voisin++;
			}
			else {
				compteur++;
			}
		}

		for (int j = 1; j < numero_voisin; j++) {
			if (tableau_voisins[j].total < sol.total) {
				sol = tableau_voisins[j];
			}
		}
	}
}
