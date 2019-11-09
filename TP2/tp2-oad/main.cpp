#include <iostream>
#include <fstream>
#include <time.h>
#include "Jobshop.hpp"

using namespace std;


int main() {

	
	/*
	T_instance instance;
	T_solution sol;
	srand(0);
	lire_fichier("la01.txt", instance);
	generer_vecteur_alea(sol, instance);
	*/
	
	  clock_t start, end;
	  std::cout << "Fichier     " << "Taille   " << "Temps obtenu   " << "Duree" << std::endl;
	  T_instance instance;
	  T_solution sol;

	  std::string tab[] = {"la01.txt", "la02.txt", "la03.txt", "la04.txt", "la05.txt", "la06.txt", "la07.txt", "la08.txt", "la09.txt", "la10.txt", "la16.txt", "la26.txt", "la35.txt", "la36.txt"};
	  int size_tab = sizeof(tab) / sizeof(std::string);

	  for(int i = 0; i < size_tab ; i++)
	  {
		  start = clock();
		  time_t srand(time(0));
		  lire_fichier(tab[i], instance);
		  //afficher_instance(instance);
		  
		  init_solution(sol, instance);

		  evaluer(sol, instance);

		  recherche_locale(sol, instance);

		  GRASP(instance, sol);

		  end = clock();

		  std::cout << tab[i] << "    " << instance.nb_piece << "x" << instance.nb_machine << "     " << sol.total << "            " << ((double)end - start) / CLOCKS_PER_SEC << "s" << std::endl;
		
	  }

	return 1;
}