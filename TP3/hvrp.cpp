 #include "hvrp.hpp"
#include <fstream>
#include <sstream>


void lire_instance_type1(std::string nom_fichier, T_instance &instance) {
	std::ifstream fichier(nom_fichier);
	
	std::string ligne;
	for (int i = 0; i < 5; ++i) {
		std::getline(fichier, ligne);
	}
	fichier >> instance.nb_client;
	fichier >> instance.nbtypecam;
	// on vire les 4 valeurs inutiles
	//for (int i = 1; i < 4; ++i) {
	//	fichier >> a;
	//}
	std::getline(fichier, ligne);
	for (int i = 0; i < instance.nbtypecam; i++) {
		fichier >> instance.liste_types[i].nb;
		fichier >> instance.liste_types[i].capacite;
		fichier >> instance.liste_types[i].cf;
		fichier >> instance.liste_types[i].cv;
	}

	int x[100], y[100];
	instance.qte[0] = 0;
	fichier >> x[0];
	fichier >> y[0];

	for (int i = 1; i < instance.nb_client + 1; i++)//on récup les coords
	{
		fichier >> x[i];
		fichier >> y[i];
		fichier >> instance.qte[i];
	}
	for (int i = 0; i < instance.nb_client + 1; i++)//on calcule et on remplit la matrice des distances
	{
		for (int j = 0; j < instance.nb_client + 1; j++)
		{
			instance.distance[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
		}
	}
}


void lire_instance_type2(std::string nom_fichier, T_instance& instance) {
	std::ifstream fichier(nom_fichier);
	int a;
	std::string ligne;

	for (int i = 0; i < 5; ++i) {

		std::getline(fichier, ligne);
	}
	fichier >> instance.nb_client;
	fichier >> instance.nbtypecam;
	std::getline(fichier, ligne);

	for (int i = 0; i < instance.nbtypecam; i++) {

		fichier >> instance.liste_types[i].nb;
		fichier >> instance.liste_types[i].capacite;
		fichier >> instance.liste_types[i].cf;
		fichier >> instance.liste_types[i].cv;
	}
	std::getline(fichier, ligne);
	std::getline(fichier, ligne);

	for (int i = 0; i <= instance.nb_client; i++)//on récup les coords
	{
		for (int j = 0;j <= instance.nb_client;j++) {
			fichier >> instance.distance[i][j];
		}
	}
	std::string ligne2;
	std::getline(fichier, ligne2);
	std::getline(fichier, ligne2);

	instance.qte[0] = 0;
	for (int i = 0; i < instance.nb_client; i++)
	{
		fichier >> a;
		fichier >> instance.qte[i+1];
	}
}


void tri(T_instance& instance, int i, int depart) {
	int j = i, stop = 0, temp;								// j : indice de tri   ;   stop : valeur d'arrêt   ;   temp : valuer temporaire
	while (j > 0 && stop != 1) {

		if (instance.distance[depart][instance.V_som[j]] < instance.distance[depart][instance.V_som[j-1]]) {
			temp = instance.V_som[j-1];
			instance.V_som[j-1] = instance.V_som[j];
			instance.V_som[j] = temp;
		}
		else {
			stop = 1;
		}
		j--;
	}
}


void initialiser_voisins(T_instance& instance) {
	for (int i = 0; i < 6;i++) {
		instance.V_som[i] = 99999;
	}
}


void trouver_proches_voisins(T_instance& instance, int liste_sommets_marques[], int depart)
{
	int i = 0;										// i : indice du tableau des voisins
	initialiser_voisins(instance);
	for (int k = 0; k <= instance.nb_client; k++)	// k : numéro du sommet courant
	{
		if (k != depart && liste_sommets_marques[k]==0) {

			instance.V_som[i] = k;
			tri(instance, i, depart);
			if (i < 5) {
				i++;
			}
		}
	}
}

// a faire
void tour_geant_ppv(T_instance& instance, T_tournee& tournee) {
	tournee.liste_sauts[0] = 0;							// on part de l'entrepôt
	int Px = 1;											// position du sommet dans L (???)
	int nr = 200;
	int x, y;
	int M[nmax] = { 0 };
	int L[nmax];

	for (int i = 0; i <= instance.nb_client; i++) {
		L[i] = i;
	}

	for (int i = 1; i < instance.nb_client + 1;i++) { // dans cours : for i = 2; ..
		x = tournee.liste_sauts[i - 1];
		M[x] = 1;
		L[Px] = L[nr];
		nr--;

		trouver_proches_voisins(instance,M , x);
		tournee.liste_sauts[i] = instance.V_som[0];
	}
}


void tour_geant_ppvrand(T_instance& instance, T_tournee tournee) {
	int a = 2;//a faire
}


void rotation(T_tournee tournee, int i, int j) {				//marche ptet pas :s, à tester
	int temp;
	for (int k = 1; k < j - i /2; k++) {
		temp = tournee.liste_sauts[i + k];
		tournee.liste_sauts[i + k] = tournee.liste_sauts[j - k];
		tournee.liste_sauts[j - k] = temp;
	}
	temp = tournee.liste_sauts[i];
	tournee.liste_sauts[i] = tournee.liste_sauts[j];
	tournee.liste_sauts[j] = temp;
}


void operateur_2_opt(T_instance& instance,T_tournee& tournee, int it_max)//on parle jamais du volume max
{
	int it = 0, delta1, delta2, beta1, beta2, gamma;
	while (it < it_max) {
		for (int i = 1; i <= instance.nb_client - 2;i++) {
			delta1 = instance.distance[instance.V_som[i]][instance.V_som[i + 1]];		// D_b,a
			for (int j = i + 2; j <= instance.nb_client;j++) {
				delta2 = instance.distance[instance.V_som[j]][instance.V_som[j + 1]];
				beta1 = instance.distance[instance.V_som[i]][instance.V_som[j]];
				beta2 = instance.distance[instance.V_som[i + 1]][instance.V_som[j + 1]];
				gamma = beta1 + beta2 - delta1 - delta2;
				if (gamma < 0) {
					tournee.cout = tournee.cout + gamma;
					rotation(tournee, i, j);
				}
			}
		}
	}
}


void operateur_2_opt_inter_tournee()
{
	// attention! est-ce que la ocnfiguration est faisable ? sachant que les véhicules ne sont plus les mêmes
	// les capa ont changé et les couts fixe/variables ont changé !
}