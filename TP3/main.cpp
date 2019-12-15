#include "hvrp.hpp"



int main() {
	srand(0);
	//T_instance instance_type1;
	T_instance instance_type2;
	T_tour_geant tour_geant;
	T_tournee tournee;
	T_solution sol;
	
	//lire_instance_type1("instacentest.txt", instance_type1);

	lire_instance_type2("instances/paris.txt", instance_type2);
	
	tour_geant_ppv(instance_type2, tour_geant);
	afficher_tour_geant(tour_geant);
	
	//rotation(tournee, 2, 14);
	
	
	//afficher_tournee(tournee);
	
	SPLIT(tour_geant, sol, instance_type2);
	/*
	for (int i = 0; i < sol.nb_tournees; i++)
	{
		afficher_tournee(sol.liste_tournees[i]);
  	}*/
	
	afficher_tournee(sol.liste_tournees[0]);

	//operateur_2_opt(instance_type2, sol.liste_tournees[0], 20); // a l'air ok ? jsp on n'a pas le cout des tournees de base
	//rotation(sol.liste_tournees[0], 1, 4);
	//deplacement_sommet(instance_type2, sol.liste_tournees[0]);
	afficher_tournee(sol.liste_tournees[0]);


	return 0;
}
