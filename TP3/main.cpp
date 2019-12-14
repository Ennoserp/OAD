#include "hvrp.hpp"



int main() {
	srand(0);
	//T_instance instance_type1;
	T_instance instance_type2;
	T_tour_geant tour_geant;
	T_solution sol;
	
	//lire_instance_type1("instacentest.txt", instance_type1);

	lire_instance_type2("paris.txt", instance_type2);

	tour_geant_ppv(instance_type2, tour_geant);
	afficher_tour_geant(tour_geant);
	
	//rotation(tournee, 2, 14);
	
	//operateur_2_opt(instance_type2, tournee, 20); // a l'air ok ? jsp on n'a pas le cout des tournees de base
	//afficher_tournee(tournee);

	SPLIT(tour_geant, sol, instance_type2);
	for (int i = 0; i < sol.nb_tournees; i++)
	{
		afficher_tournee(sol.liste_tournees[i]);
  	}
	return 0;
}
