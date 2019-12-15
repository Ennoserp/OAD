#include "hvrp.hpp"



int main() {
	srand(time(0));
	//T_instance instance_type1;
	T_instance instance_type2;
	T_tour_geant tour_geant;
	T_tour_geant tour_geant2;
	T_solution sol;
	
	//lire_instance_type1("instacentest.txt", instance_type1);

	lire_instance_type2("paris.txt", instance_type2);

	tour_geant_ppv(instance_type2, tour_geant);
	tour_geant_ordre_num(instance_type2, tour_geant2);
	afficher_tour_geant(tour_geant);
	afficher_tour_geant(tour_geant2);
	
	//rotation(tournee, 2, 14);
	
	//operateur_2_opt(instance_type2, tournee, 20); // a l'air ok ? jsp on n'a pas le cout des tournees de base
	//afficher_tournee(tournee);

	SPLIT(tour_geant, sol, instance_type2);
	

	//operateur 2 opt sur toutes les tournees
	
	for (int i = 0; i < sol.nb_tournees; i++)
	{
		afficher_tournee(sol.liste_tournees[i]);
		operateur_2_opt(instance_type2, sol.liste_tournees[i], 15);
		afficher_tournee(sol.liste_tournees[i]);
		std::cout << std::endl << std::endl << std::endl << std::endl;
  	}
	

	// operateur 2 opt inter tournees avec la formule du cout = instance.liste_types[tournee.type_camion].cf + dist * instance.liste_types[tournee.type_camion].cv;
	/*
	for (int i = 0; i < sol.nb_tournees; i++) {
		afficher_tournee(sol.liste_tournees[i]);
		for (int j = i + 1; j < sol.nb_tournees; j++) {
			operateur_2_opt_inter_tournee(instance_type2, sol.liste_tournees[i], sol.liste_tournees[j], 15);
		}
	}
	std::cout << std::endl << std::endl << std::endl << std::endl;
	for (int i = 0; i < sol.nb_tournees; i++) {
		afficher_tournee(sol.liste_tournees[i]);
	}	
	*/
	


	// 2_opt_inter avec mauvaise formule ?
	/*
	for (int i = 0; i < sol.nb_tournees; i++) {
		afficher_tournee(sol.liste_tournees[i]);
		for (int j = i + 1; j < sol.nb_tournees; j++) {
			operateur_2_opt_inter_tournee_bis(instance_type2, sol.liste_tournees[i], sol.liste_tournees[j], 15);
		}
	}
	std::cout << std::endl << std::endl << std::endl << std::endl;
	for (int i = 0; i < sol.nb_tournees; i++) {
		afficher_tournee(sol.liste_tournees[i]);
	}	
	*/


	

	return 0;
}
