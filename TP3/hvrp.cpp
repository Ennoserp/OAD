#include "hvrp.hpp"
#include <fstream>
#include <sstream>


void lire_instance_type1(std::string nom_fichier, T_instance &instance) {
	std::ifstream fichier(nom_fichier);
	int a;
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

void plus_proches_voisins(T_instance& instance, int depart)
{
	int i = 0, j = 0;
	int min = 0;
	int compteur = 0;
	int V_som[6];
	for (int i = 0; i <= instance.nb_client ; i++)
	{
		if (i != depart)
		{

		}
	}
}

void operateur_2_opt()
{
	// recopier le cours: easy : 2 boucles for
}

void operateur_2_opt_inter_tournee()
{
	// attention! est-ce que la ocnfiguration est faisable ? sachant que les véhicules ne sont plus les mêmes
	// les capa ont changé et les couts fixe/variables ont changé !
}