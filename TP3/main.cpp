#include "hvrp.hpp"



int main() {
	srand(time(0));
	T_instance instance_type1;
	T_instance instance_type2;
	T_tournee tournee;
	lire_instance_type1("instacentest.txt", instance_type1);
	lire_instance_type2("paris.txt", instance_type2);

	tour_geant_ordre_num(instance_type2, tournee);
	afficher_tournee(tournee);
	return 0;
}
