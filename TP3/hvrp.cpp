#include "hvrp.hpp"

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

	for (int i = 0; i <= instance.nb_client; i++)//on r�cup les coords
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
	int j = i, stop = 0, temp;								// j : indice de tri   ;   stop : valeur d'arr�t   ;   temp : valuer temporaire
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
	for (int k = 0; k <= instance.nb_client; k++)	// k : num�ro du sommet courant
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


void tour_geant_ppv(T_instance& instance, T_tour_geant& tournee) {
	tournee.liste_sauts[0] = 0;							// on part de l'entrep�t
	int Px = 1;											// position du sommet dans L (???)
	int nr = instance.nb_client;
	int x;
	int M[nmax] = { 0 };
	int L[nmax];

	for (int i = 0; i <= instance.nb_client; i++) {
		L[i] = i;
	}

	for (int i = 1; i < instance.nb_client + 1; i++) { 
		x = tournee.liste_sauts[i - 1];
		M[x] = 1;
		L[Px] = L[nr];
		nr--;

		trouver_proches_voisins(instance, M, x);
		tournee.liste_sauts[i] = instance.V_som[0];
		tournee.nb_sauts++;
	}
	tournee.nb_sauts++;
	tournee.liste_sauts[tournee.nb_sauts] = 0;
}


void tour_geant_ppvrand(T_instance& instance, T_tour_geant& tournee) {
	tournee.liste_sauts[0] = 0;							// on part de l'entrep�t
	int Px = 1;											// position du sommet dans L (???)
	int nr = instance.nb_client;
	int x = 0;
	int M[nmax] = { 0 };
	int L[nmax];

	for (int i = 0; i <= instance.nb_client; i++) {
		L[i] = i;
	}

	for (int i = 1; i < instance.nb_client + 1; i++) { 
		x = tournee.liste_sauts[i - 1];
		M[x] = 1;
		L[Px] = L[nr];
		nr--;

		trouver_proches_voisins(instance, M, x);
		tournee.liste_sauts[i] = instance.V_som[choix_voisin_aleatoire(nr)];
		tournee.nb_sauts++;
	}
	tournee.nb_sauts++;
	tournee.liste_sauts[tournee.nb_sauts] = 0;
	
}


void tour_geant_ordre_num(T_instance& instance, T_tour_geant& tournee) {
	tournee.liste_sauts[0] = 0;							// on part de l'entrepot
	for (int i = 1; i < instance.nb_client + 1; i++) { 
		tournee.liste_sauts[i] = i;
		tournee.nb_sauts++;
	}
	tournee.nb_sauts++;
	tournee.liste_sauts[tournee.nb_sauts] = 0;
}


int choix_voisin_aleatoire(int nb_sommets_restants) {
	int stop = 0, l = 1;
	int a;
	int retour = 0;
	int i = 0;
	while (stop != 1) {
		a = rand() % 100;
		if (a < 80) {
			stop = 1;
		}
		else {
			i++;
			if (i == 4 || i == nb_sommets_restants) {
				retour = nb_sommets_restants;
				stop = 1;
			}
		}
	}
	return retour;
}


void afficher_tournee(T_tournee tournee)
{
	std::cout << std::endl << "------ TOURNEE ------" << std::endl;
	std::cout << "Nombre de sauts : " << tournee.nb_sauts << std::endl;
	std::cout << "Cout de la tournee : " << tournee.cout << std::endl;
	std::cout << "Volume de la tournee : " << tournee.volume << std::endl;
	std::cout << "Type camion : " << tournee.type_camion << std::endl;

	for (int i = 0; i <= tournee.nb_sauts + 1; i++) {
		std::cout << tournee.liste_sauts[i] << " ";
	}
}


void afficher_tour_geant(T_tour_geant tournee) 
{
	std::cout << std::endl << "------ TOUR GEANT ------" << std::endl;
	std::cout << "Nombre de sauts : " << tournee.nb_sauts << std::endl;
	for (int i = 0; i <= tournee.nb_sauts; i++) {
		std::cout << tournee.liste_sauts[i] << " ";
	}
}


void rotation(T_tournee& tournee, int i, int j) //ok
{
	int temp=0;
	temp = tournee.liste_sauts[i + 1];
	tournee.liste_sauts[i + 1] = tournee.liste_sauts[j];
	tournee.liste_sauts[j] = temp;
	for (int k = 1; k <= (j - i - 1)/2; k++) {
		temp = tournee.liste_sauts[i + k + 1];
		tournee.liste_sauts[i + k + 1] = tournee.liste_sauts[j - k];
		tournee.liste_sauts[j - k] = temp;
	}
}

void rotation_inter_tournee(T_tournee& tournee1, T_tournee& tournee2, int i, int j) {//ok
	int temp = 0;
	T_tournee temp1, temp2;

	init_tournee(temp1);
	init_tournee(temp2);
	copier_tournee(tournee1, temp1);
	copier_tournee(tournee2, temp2);
	vider_tournee_sup_i(tournee1, i);
	vider_tournee_sup_i(tournee2, j);

	for (int k = 1; k <= tournee2.nb_sauts - j; k++) 
	{
		tournee1.liste_sauts[i + k] = temp2.liste_sauts[j + k];
	}

	for (int k = 1; k <= tournee1.nb_sauts - i; k++)
	{
		tournee2.liste_sauts[j + k] = temp1.liste_sauts[i + k];
	}

	temp = tournee1.nb_sauts;
	tournee1.nb_sauts = i +  tournee2.nb_sauts - j;
	tournee2.nb_sauts = j + temp - i;

}


void vider_tournee_sup_i(T_tournee& tournee, int i) 
{
	for (int k = i + 1; k <= tournee.nb_sauts; k++) 
	{
		tournee.liste_sauts[k] = 0;
	}
}


void operateur_2_opt(T_instance instance,T_tournee& tournee)
{
	double delta1, delta2, beta1, beta2, gamma;

	for (int i = 1; i <= tournee.nb_sauts - 2; i++)
	{
		delta1 = instance.distance[tournee.liste_sauts[i]][tournee.liste_sauts[i + 1]];

		for (int j = i + 2; j <= tournee.nb_sauts; j++) 
		{
			delta2 = instance.distance[tournee.liste_sauts[j]][tournee.liste_sauts[j + 1]];
			beta1 = instance.distance[tournee.liste_sauts[i]][tournee.liste_sauts[j]];
			beta2 = instance.distance[tournee.liste_sauts[i + 1]][tournee.liste_sauts[j + 1]];
			gamma = beta1 + beta2 - delta1 - delta2;

			if (gamma < 0) 
			{
				tournee.cout = tournee.cout + gamma;
				rotation(tournee, i, j);
			}
		}
	}	
}


void operateur_2_opt_inter_tournee(T_instance instance, T_tournee& tournee1, T_tournee& tournee2) 
{
	int dist_temp = 0, v1 = 0, v2 = 0, capatemp = 0;
	int dist_1 = 0, dist_2 = 0;
	double cout_1 = 0., cout_2 = 0.;
		
	for (int i = 1; i <= tournee1.nb_sauts - 1; i++) 
	{
		dist_1 = 0;
		v1 = 0;
		for (int u = 0; u < i; u++) 
		{
			dist_1 = dist_1 + instance.distance[tournee1.liste_sauts[u]][tournee1.liste_sauts[u + 1]];
			v1 = v1 + instance.qte[tournee1.liste_sauts[u + 1]];
		}
		dist_temp = dist_1;
		capatemp = v1;
		for (int j = 1; j <= tournee2.nb_sauts - 1; j++) 
		{
			dist_2 = 0;
			v2 = 0;
			dist_1 = dist_temp;
			v1 = capatemp;

			for (int u = 0; u < j; u++) 
			{
				dist_2 = dist_2 + instance.distance[tournee2.liste_sauts[u]][tournee2.liste_sauts[u + 1]];
				v2 = v2 + instance.qte[tournee2.liste_sauts[u + 1]];
			}


			dist_1 = dist_1 + instance.distance[tournee1.liste_sauts[i]][tournee2.liste_sauts[j + 1]];
			v1 = v1 + instance.qte[tournee1.liste_sauts[j + 1]];
			for (int k = 1; k <= tournee2.nb_sauts - j; k++) 
			{
				dist_1 = dist_1 + instance.distance[tournee2.liste_sauts[j + k]][tournee2.liste_sauts[j + k + 1]];
				v1 = v1 + instance.qte[tournee1.liste_sauts[j + k + 1]];
			}


			dist_2 = dist_2 + instance.distance[tournee2.liste_sauts[j]][tournee1.liste_sauts[i + 1]];
			v2 = v2 + instance.qte[tournee2.liste_sauts[i + 1]];
			for (int k = 1; k <= tournee1.nb_sauts - i; k++) 
			{
				dist_2 = dist_2 + instance.distance[tournee1.liste_sauts[i + k]][tournee1.liste_sauts[i + k + 1]];
				v2 = v2 + instance.qte[tournee2.liste_sauts[i + k + 1]];
			}

			cout_1 = instance.liste_types[tournee1.type_camion].cf + (dist_1/100) * instance.liste_types[tournee1.type_camion].cv;
			cout_2 = instance.liste_types[tournee2.type_camion].cf + (dist_2/100) * instance.liste_types[tournee2.type_camion].cv;

			if (((cout_1 <= tournee1.cout) && (cout_2 <= tournee2.cout)) && ((v1 <= instance.liste_types[tournee1.type_camion].capacite) && (v2 <= instance.liste_types[tournee2.type_camion].capacite)))
			{
				tournee1.cout = cout_1;
				tournee2.cout = cout_2;
				instance.liste_types[tournee1.type_camion].capacite = v1;
				instance.liste_types[tournee2.type_camion].capacite = v2;
				rotation_inter_tournee(tournee1, tournee2, i, j);
			}
		}
	}	
}


void deplacement_sommet(T_instance ins, T_tournee& tournee) {
	int dist = 0;
	int indI = 1;
	int indJ = 3;
	int minDist;
	bool amelioration = false;
	
	for (int i = 1; i <= tournee.nb_sauts; i++) //compte les sommets (hors dépôt)
	{
		
		for (int j = 1; j <= tournee.nb_sauts + 1; j++)//compte les arcs
		{
			dist = 0;

			if (i != j && i != j + 1) {
				dist -= ins.distance[tournee.liste_sauts[i - 1]][tournee.liste_sauts[i]];
				dist -= ins.distance[tournee.liste_sauts[i]][tournee.liste_sauts[i + 1]];
				dist -= ins.distance[tournee.liste_sauts[j]][tournee.liste_sauts[j + 1]];

				dist += ins.distance[tournee.liste_sauts[i - 1]][tournee.liste_sauts[i + 1]];
				dist += ins.distance[tournee.liste_sauts[j]][tournee.liste_sauts[i]];
				dist += ins.distance[tournee.liste_sauts[i]][tournee.liste_sauts[j+1]];
				if (dist < 0 && dist < minDist)
				{
					minDist = dist;
					indI = i;
					indJ = j;
					amelioration = true;
				}
			}			
		}
	}

	if (!amelioration) {
		//on déplace le sommet indI à l'emplacement indJ
		int s = tournee.liste_sauts[indI];
		for (int i = indI; i < indJ; i++)
		{
			tournee.liste_sauts[i] = tournee.liste_sauts[i + 1];
		}
		tournee.liste_sauts[indJ] = s;
		tournee.cout += dist * ins.liste_types[tournee.type_camion].cv;
	}
}


void init_tournee(T_tournee& tournee) {
	tournee.type_camion = 0;
	tournee.cout = 0;
	tournee.volume = 0;
	tournee.nb_sauts = 0;
	for (int i = 0; i < 100; i++)
	{
		tournee.liste_sauts[i] = 0;
	}	
}


void copier_tournee(T_tournee tournee_A, T_tournee& tournee_B) //remplace la tournee B par la tournee A
{
	tournee_B.type_camion = tournee_A.type_camion;
	tournee_B.cout = tournee_A.cout;
	tournee_B.volume = tournee_A.volume;
	tournee_B.nb_sauts = tournee_A.nb_sauts;
	for (int i = 0; i < tournee_A.nb_sauts + 1; i++)
	{
		tournee_B.liste_sauts[i] = tournee_A.liste_sauts[i];
	}
}


void evaluer_tournee(T_tournee& tournee, T_instance instance) //pour calculer la distance d'une tournee
{
	int dist = 0;
	int volume = 0;
	for (int i = 0; i < tournee.nb_sauts + 1; i++)
	{
		dist += instance.distance[tournee.liste_sauts[i]][tournee.liste_sauts[i + 1]];
		volume += instance.qte[tournee.liste_sauts[i + 1]];
	}
	tournee.cout = instance.liste_types[tournee.type_camion].cf + (dist/100) * instance.liste_types[tournee.type_camion].cv;
	tournee.volume = volume;
}


void copier_label(T_label l1, T_label& l2) 
{
	l2.capacite = l1.capacite;
	l2.prix = l1.prix;
	
	l2.labels = false;
	
	for (int i = 0; i < 100; i++)
	{
		l2.type_camion[i] = l1.type_camion[i];
		l2.nb_sauts[i] = l1.nb_sauts[i];
		l2.pere[i] = l1.pere[i];
		l2.nb_peres = l1.nb_peres;
	}
	for (int i = 0; i < 10; i++)
	{
		l2.reste_camions[i] = l1.reste_camions[i];
	}
}


bool domine(T_label l1, T_label l2, T_instance ins) // renvoie vrai si l1 domine l2, faux si non domination
{
	bool b = false;
	int compteur = 0;

	if (l1.prix <= l2.prix)
	{
		for (int i = 0; i < ins.nbtypecam; i++)
		{
			if (l1.reste_camions[i] >= l2.reste_camions[i]) {
				compteur++;
			}
		}
		if (compteur == ins.nbtypecam)
		{
			b = true;
		}	
	}
	return b;
}


void tri_labels(T_tour_geant& tg, int indice_sommet) {
	int j = 0; //compteur de labels pour le déplacement
	int nb_lab = 0;
	for (int i = 0; i < tg.nb_labels[indice_sommet]; i++)
	{
		if (!tg.liste_labels[indice_sommet][i].labels)//alors on déplace le label
		{
			if (i != j) //si i==j alors le label est à la bonne place
			{
				copier_label(tg.liste_labels[indice_sommet][i], tg.liste_labels[indice_sommet][j]);
			}
			j++;
			nb_lab++;
			
		}
	}
	tg.nb_labels[indice_sommet] = nb_lab;
}


void SPLIT(T_tour_geant& tour_geant, T_solution& sol, T_instance& instance) {

	T_label lab;
	double distance;
	int capacite;
	bool domination;
	//il faut mettre des labels sur le premier sommet avant le premier saut pour initialiser
	//init labels:
	for (int i = 0; i < instance.nbtypecam; i++)
	{
		lab.reste_camions[i] = instance.liste_types[i].nb;
	}
	copier_label(lab, tour_geant.liste_labels[0][0]);
	tour_geant.nb_labels[0]++;

	for (int i = 1; i < tour_geant.nb_sauts; i++)//on démarre bien à 1 et non à 0 car on ne compte pas le dépôt
	{
		distance = 0;
		capacite = 0;

		for (int j = i; j <= tour_geant.nb_sauts; j++)
		{
			distance += instance.distance[tour_geant.liste_sauts[i]][tour_geant.liste_sauts[j]];
			capacite += instance.qte[j];
			
			for (int k = 0; k < instance.nbtypecam; k++)
			{
				for (int labels = 0; labels < tour_geant.nb_labels[j-1]; labels++)
				{	
					int a;
					if (capacite <= instance.liste_types[k].capacite && tour_geant.liste_labels[i - 1][labels].reste_camions[k] > 0)//condition de capacite on passe pas si un camion est rempli et de ressources (si on n'a pas de camion dispo)
					{
						copier_label(tour_geant.liste_labels[i-1][labels], lab);
						//prix du chemin qu'on vient de parcourir auquel on ajoute le prix des chemins précédents
						lab.prix = instance.liste_types[k].cf + instance.liste_types[k].cv * ((distance + instance.distance[0][tour_geant.liste_sauts[i]] + instance.distance[tour_geant.liste_sauts[j]][0]) / 100);//on ajoute le départ et le retour au dépôt
						lab.capacite = capacite;											
						lab.reste_camions[k]--;
						

						lab.type_camion[lab.nb_peres] = k;
						lab.pere[lab.nb_peres] = i;
						lab.nb_sauts[lab.nb_peres] = j - i + 1;
						lab.nb_peres++;				
				

						int compteur_domi = 0;				//compteur pour la domination
						domination = false;					//variable égale à true si on doit ajouter le label qu'on traite
						if (tour_geant.nb_labels[j] != 0)	//s'il n'y a pas de label (0), on l'ajoute forcément
						{						
							for (int l = 0; l < tour_geant.nb_labels[j]; l++)//on regarde si on met le label
							{												//c'est a dire s'il n'est pas dominé par un autre
								if (domine(lab, tour_geant.liste_labels[j][l], instance))// si le label étudié domine un label présent
								{
									//on supprime le label
									tour_geant.liste_labels[j][l].labels = true;
									domination = true;
								}
								else if (!domine(tour_geant.liste_labels[j][l], lab, instance))//si le label étudié n'est pas dominé par un label présent
								{
									//si le label n'est pas dominé par tous les labels on doit l'ajouter
									compteur_domi++;									
								}
							}
							if (compteur_domi == tour_geant.nb_labels[j])
							{
								domination = true;
							}
						}
						else 
						{
							domination = true; //pas de label donc on doit l'ajouter
						}

						tri_labels(tour_geant, j);

						if (domination) 
						{
							//on insère le label				
							copier_label(lab, tour_geant.liste_labels[j][tour_geant.nb_labels[j]]);
							tour_geant.nb_labels[j]++;
						}
					}
				}
			}
		}
	}
	//on va chercher le label au cout le plus faible dans le dernier saut, ce qui nous donnera le chemin à emprunter
	copier_label(tour_geant.liste_labels[tour_geant.nb_sauts][0], lab);//changer le 0 !!! il faut chercher le meilleur label mais pour l'instant flemme

	//construction de la solution:
	T_tournee tour;
	int total = 1;
	lab.nb_sauts[lab.nb_peres - 1]--; //pour régler le problème avec le 0 mis à la fin du tour géant qui devient gênant ici.

	sol.cout_total = lab.prix;
	
	for (int i = 0; i < lab.nb_peres; i++)
	{
		init_tournee(tour);
		tour.type_camion = lab.type_camion[lab.nb_peres - i - 1];
		for (int j = 0; j < lab.nb_sauts[lab.nb_peres - i - 1]; j++)
		{
			tour.liste_sauts[j+1] = tour_geant.liste_sauts[tour_geant.nb_sauts - (j + total)];
			tour.nb_sauts++;
			
		}
		total += lab.nb_sauts[lab.nb_peres - i - 1];
		
		evaluer_tournee(tour, instance);

		copier_tournee(tour, sol.liste_tournees[sol.nb_tournees]);
		sol.nb_tournees++;
	}
}


bool bernoulli(float p)
{
	int retour = false, max_nb = 100000;
	float nb = (rand() % max_nb) / max_nb;
	if (nb < p)
	{
		retour = true;
	}
	return retour;
}


void recherche_locale(T_instance ins,T_solution sol) 
{
	float p1 = 0.5, p2 = 0.5, p3 = 0.5;
	int cout = 0, cout2 = 0;
	T_tournee tour;
	for (int i = 0; i < NB_TOUR_MAX; i++)
	{

		//premier opérateur:
		// 2-opt
		if (bernoulli(p1))
		{
			for (int j = 0; j < sol.nb_tournees; j++)
			{
				cout = sol.liste_tournees[j].cout;
				operateur_2_opt(ins, sol.liste_tournees[j]);

				if (sol.liste_tournees[j].cout < cout)
				{
					//recalcul du cout total
					sol.cout_total -= cout - sol.liste_tournees[j].cout;

					//le 2opt a amélioré la solution
					if (p1 < 1)
					{
						p1 += 0.05;
					}

				}
				else if (p1 > 0.10) {
					p1 -= 0.05;
				}
			}
		}

		//deuxieme opérateur:
		// déplacement de sommet
		if (bernoulli(p2))
		{
			for (int j = 0; j < sol.nb_tournees; j++)
			{
				cout = sol.liste_tournees[j].cout;
				deplacement_sommet(ins, sol.liste_tournees[j]);
				if (sol.liste_tournees[j].cout < cout)
				{
					//recalcul du cout total
					sol.cout_total -= cout - sol.liste_tournees[j].cout;

					//le déplacement a amélioré la solution
					if (p2 < 1)
					{
						p2 += 0.05;
					}

				}
				else if (p2 > 0.10) {
					p2 -= 0.05;
				}
			}
			
		}


		//troisième opérateur:
		// 2-opt inter-tournées
		if (bernoulli(p3))
		{
			for (int j = 0; j < sol.nb_tournees; j++)
			{
				for (int k = 0; k < sol.nb_tournees; k++)
				{
					if (j != k)
					{
						cout = sol.liste_tournees[j].cout;
						cout = sol.liste_tournees[k].cout;

						operateur_2_opt_inter_tournee(ins, sol.liste_tournees[j], sol.liste_tournees[k]); 

						if (sol.liste_tournees[j].cout < cout && sol.liste_tournees[k].cout < cout2)
						{
							//recalcul du cout total
							sol.cout_total -= cout - sol.liste_tournees[j].cout;

							//le déplacement a amélioré la solution
							if (p3 < 1)
							{
								p3 += 0.05;
							}

						}
						else if (p3 > 0.10) {
							p3 -= 0.05;
						}
					}
				}
			}
		}



	}
}