#include <iostream>
#include "hvrp.hpp"



int main() {
	T_instance instance_type1;
	T_instance instance_type2;
	lire_instance_type1("instacentest.txt", instance_type1);
	lire_instance_type2("paris.txt", instance_type2);

	plus_proches_voisins(instance_type1, 0);

	return 0;
}
