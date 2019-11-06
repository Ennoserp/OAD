#include "Jobshop.hpp"

using namespace std;

int lire_fichier(string nom_fichier, T_instance& instance) {
	ifstream fichier(nom_fichier);
	fichier >> instance.nb_piece;
	fichier >> instance.nb_machine;

	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			fichier >> instance.m[i][j];
			fichier >> instance.p[i][j];
		}
	}
	fichier.close();
	instance.NT = instance.nb_machine * instance.nb_piece;
	return 1;
}


void afficher_instance(T_instance& instance) {
	cout << "nombre de pieces : " << instance.nb_piece << endl;
	cout << "nombre de machines : " << instance.nb_machine << endl;

	cout << "tableau des machines" << endl;
	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			cout << instance.m[i][j] << " ";
		}
		cout << endl;
	}

	cout << "tableau des durees" << endl;
	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			cout << instance.p[i][j] << " ";
		}
		cout << endl;
	}
}


void creer_prime(T_instance& instance) {
	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			instance.m_prim[j + i * instance.nb_machine] = instance.m[i][j];
			instance.p_prim[j + i * instance.nb_machine] = instance.p[i][j];
		}
	}
}


void evaluer(T_solution& sol, T_instance& instance) {
	//initialisation des variables
	int ind_j;
	int machine;
	int prec;
	int pos;

	int T[n_max][m_max];
	int MP[m_max];

	//initialisation des tableaux
	for (int i = 0; i < instance.nb_piece; ++i) {
		for (int j = 0; j < instance.nb_machine; ++j) {
			T[i][j] = i * instance.nb_machine + j + 1;
		}
	}
	for (int i = 0; i < instance.nb_machine; ++i) {
		MP[i] = 0;
	}

	//algo
	for (int i = 1; i <= instance.NT; i++) {
		ind_j = sol.V[i];

		instance.N[ind_j] = instance.N[ind_j] + 1;
		pos = T[ind_j-1][instance.N[ind_j]-1];

		if (instance.N[ind_j] > 1) { //alors on est deja passe par la
			prec = pos - 1;
			if (sol.st[prec] + instance.p_prim[prec] > sol.st[pos]) {
				sol.st[pos] = sol.st[prec] + instance.p_prim[prec];
				sol.pred[pos] = prec;
			}
		}

		machine = instance.m_prim[pos-1]; // kekun a [pos] et pas [pos -1]


		if (MP[machine] != 0) {
			prec = MP[machine];
			if (sol.st[prec] + instance.p_prim[prec] > sol.st[pos]) {
				sol.st[pos] = sol.st[prec] + instance.p_prim[prec];
				sol.pred[pos] = prec;
			}
		}
		MP[machine] = pos;
	}

  for (int i = 1; i <= instance.nb_piece; i++)
  {
    prec = i * instance.nb_machine - 1;
    if (sol.st[prec] + instance.p_prim[prec] > sol.total)
    {
      sol.dernier_sommet = prec;
      sol.total = sol.st[prec] + instance.p_prim[prec];
    }
  }

}


void recherche_locale(T_solution& sol, T_instance& instance) {
  int nb_iteration = 0;
	int itmax = 200;// nb d'iterations maximal
	int temp;
	int i = sol.dernier_sommet;
	int j = sol.pred[i];
	int position_i = sol.V[i];
	int position_j = sol.V[j];
	
	while((j != -1 ) && (nb_iteration < itmax)) // != -1
	{
		nb_iteration++;
		if(instance.m_prim[i] == instance.m_prim[j])
		{
			//Calculer la position de i et de j pour faire la permutation
      position(instance, sol, i, j, position_i, position_j);

      T_solution solution_nouv;
      init_solution(instance, solution_nouv);

      copie(sol.V,solution_nouv.V);
			solution_nouv.V[position_i] = sol.V[position_j];
			solution_nouv.V[position_j] = sol.V[position_i];

			evaluer(sol, instance);

			if (solution_nouv.total < sol.total)
			{
				sol = solution_nouv;
				i = sol.dernier_sommet;
				j = sol.pred[i];
			}
			else
			{
				i = j;
				j = sol.pred[i];
			}
		}
		else
		{
			i = j;
			j = sol.pred[j];
		}
	}


}


void generer_vecteur_alea(T_solution& sol, T_instance& instance) {

	int nb_restant = instance.nb_piece;
	int x; //var aléatoire entre 1 et nb_restant
	int indice = 0;
	int TN[m_max]; //TN[i] = i
	int NN[m_max]; //tableau contenant le nb de fois qu'il reste à appeler la pièce i

	for (int i = 0; i < instance.nb_piece; i++) { //initialisation du tableau TN
		TN[i] = i + 1;
		NN[i] = instance.nb_machine;
	}
	cout << endl;

	while (nb_restant > 0) {

		x = rand() % nb_restant + 1;
		sol.V[indice] = TN[x - 1];
		indice++;
		NN[x - 1]--;

		if (NN[x - 1] == 0) { //si une case est vide on "reduit" la taille du tableau

			TN[x - 1] = TN[nb_restant - 1];
			NN[x - 1] = NN[nb_restant - 1];
			nb_restant--;
		}
	}
}


void afficher_vecteur(T_solution& sol, T_instance& instance) { // affiche le vecteur de Bierwith de la solution
	cout << "V= ";
	for (int i = 0; i < 9; i++) {
		cout << sol.V[i] << " ";
	}
	cout << endl;
}

void copie(int Tableau_Original[], int Tableau_Copie[])
{
	for (int a = 0; a < 11 ; a++) // V' = V
	{
		Tableau_Copie[a] = Tableau_Original[a];
	}
}



void init_solution(T_instance& instance, T_solution& solution)
{
	int i, j;

	generer_vecteur_alea(solution, instance);

	for (i = 0; i < instance.nb_piece; i++)
	{
		solution.n[i] = 0;
	}

	for (i = 0; i < instance.nb_machine; i++)
	{
		solution.MP[i] = -1;
	}

	for (i = 0; i < instance.nb_piece; i++)
	{
		for (j = 0; j < instance.nb_machine; j++)
		{
			solution.T[i][j] = i * instance.nb_machine + j;
			solution.st[i * instance.nb_machine + j] = 0;
			solution.pred[i * instance.nb_machine + j] = -1;
		}
	}
	solution.total = 0;
}

void position(T_instance& instance, T_solution& sol, int i, int j, int& Posi, int& Posj)
{
	int Pi = i / instance.nb_machine;
	int Pj = j / instance.nb_machine;

	int occ_i = 0;
	int occ_j = 0;

	int Mai = i % instance.nb_machine;
	int Maj = j % instance.nb_machine;

	Posi = 0;
	while (occ_i != Mai || sol.V[Posi] != Pi)
	{
		if (sol.V[Posi] == Pi)
			occ_i++;
		Posi++;
	}

	Posj = 0;
	while (occ_j != Maj || sol.V[Posj] != Pj)
	{
		if (sol.V[Posj] == Pj)
			occ_j++;
		Posj++;
	}
}
