#include <iostream>
#include <fstream>
#include <time.h>
#include "Jobshop.hpp"

using namespace std;


int main() {

	srand(time(0));
	//T_instance instance;
	//T_solution sol;

  
	//lire_fichier("test.txt", instance);
	//generer_vecteur_alea(sol, instance);
	
	clock_t start, end;

	  srand(time(0));
	std::cout << "Fichier     " << "Taille   " << "Temps obtenu   " << "Duree" << std::endl;
	  T_instance instance;
	  T_solution sol;

	std::string tab[] = {"la01.txt", "la02.txt", "la03.txt", "la04.txt", "la05.txt", "la06.txt", "la07.txt", "la08.txt", "la09.txt", "la10.txt", "la16.txt", "la26.txt", "la35.txt", "la36.txt"};
	  int size_tab = sizeof(tab) / sizeof(std::string);

	  for(int i = 0; i < size_tab ; i++)
	  {
		  start = clock();

		  lire_fichier(tab[i], instance);

		  init_solution(instance, sol);

		  evaluer(sol, instance);

		  recherche_locale(sol, instance);

		  end = clock();

		  std::cout << tab[i] << "    " << instance.nb_piece << "x" << instance.nb_machine << "     " << sol.total << "            " << ((double)end - start) / CLOCKS_PER_SEC << "s" << std::endl;
	  }
	

	//afficher_instance(instance); //fonctionnel
	//creer_prime(instance); //fonctionnel

	//generer_vecteur_alea(sol, instance);
	//copie(V1, sol.V);
	//afficher_vecteur(sol, instance);
	//evaluer(sol, instance);

	for (int i = 0; i < 5; i++)
	{
		cout << sol.pred[i] << " ";
	}

	return 1;
}