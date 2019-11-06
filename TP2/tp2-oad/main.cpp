#include <iostream>
#include <fstream>
#include <time.h>
#include "Jobshop.hpp"

using namespace std;


int main() {
	srand(time(0));
	T_instance instance;
	T_solution sol;

	lire_fichier("test.txt", instance); //fonctionnel
	afficher_instance(instance); //fonctionnel
	creer_prime(instance); //fonctionnel
	
	//generer_vecteur_alea(sol, instance);
	//copie(V1, sol.V);
	//afficher_vecteur(sol, instance);
	evaluer(sol, instance);

	for (int i = 0; i < 5; i++)
	{
		cout << sol.pred[i] << " ";
	}

	return 1;
}