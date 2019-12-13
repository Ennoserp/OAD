#include "hvrp.hpp"



int main() {
	srand(time(0));
	T_instance instance_type1;
	T_instance instance_type2;
	T_tour_geant tournee;
	lire_instance_type1("instacentest.txt", instance_type1);
	lire_instance_type2("paris.txt", instance_type2);

	//tour_geant_ordre_num(instance_type2, tournee);
	tour_geant_ppvrand(instance_type2, tournee);
	//afficher_tournee(tournee);
	
	//rotation(tournee, 2, 14);
	
	//operateur_2_opt(instance_type2, tournee, 20); // a l'air ok ? jsp on n'a pas le cout des tournees de base
	//afficher_tournee(tournee);
	return 0;
}
