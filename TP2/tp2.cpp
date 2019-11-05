/**
 * @file tp2.cpp
 * @author Rémi Valarcher - Antony Nifosi
 * @brief Implémentations des fonctions et tests pour l'optimisation de Job Shop
 * @version 1
 * @date 2019-11-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "tp2.hpp"

/**
 * @brief Procédure permettant de lire un fichier .txt et d'extraire les données décrivant un Job Shop
 * 
 * @param[in] nom_fichier nom du fichier .txt à lire
 * @param[out] instance variable stockant les données contenus dans le fichier .txt
 */
void lire_instance(std::string nom_fichier, instance_t& instance)
{
	std::ifstream f(nom_fichier);

	if (f)
	{
		f >> instance.n;
		f >> instance.m;

		for (int i = 0; i < instance.n; i++)
		{
			for (int j = 0; j < instance.m; j++)
			{
				f >> instance.M[i * instance.m + j];
				f >> instance.P[i * instance.m + j];
			}
		}
		f.close();
	}
}

/**
 * @brief Procédure permettant générer un vecteur de Bierwirth
 * 
 * @param[in] g variable stockant les données du Job Shop à traiter
 * @param[out] s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 */
void generer_VB(instance_t& g, solution_t& s)
{

	int T[max_piece];
	int n[max_piece];
	int size_t = g.n * g.m;
	int k = g.n;
	int i, j;

	for (i = 0; i < g.n; i++)
	{
		T[i] = i;
		n[i] = g.m;
	}

	j = 0;
	while (size_t > 0)
	{
		int rv = std::rand() % k;
		s.VB[j++] = T[rv];
		n[T[rv]]--;
		if (n[T[rv]] == 0)
		{
			T[rv] = T[k - 1];
			k--;
		}
		size_t--;
	}
}

/**
 * @brief Procédure permettant d'afficher le vecteur de Bierwirth passé en paramètre
 * 
 * @param s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 * @param instance variable stockant les données du Job Shop à traiter
 */
void afficher_VB(solution_t s, instance_t& instance)
{
	for (int i = 0; i < instance.n * instance.m; i++)
	{
		std::cout << s.VB[i] << std::endl;
	}
}

/**
 * @brief Procédure permettant de générer une solution du Job Shop à partir du vecteur de Bierwirth
 * 
 * @param[in] g variable stockant les données du Job Shop à traiter
 * @param[out] s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 */
void evaluer(instance_t& g, solution& s)
{
	int i, j, pos, prec, machine;

	for (i = 0; i < g.m * g.n; i++)
	{
		j = s.VB[i];

		pos = s.T[j][s.N[j]];
		s.N[j] = s.N[j] + 1;

		if (s.N[j] > 1) // On regarde si le sommet est le premier de la pièce
		{
			prec = pos - 1;
			if (s.ST[prec] + g.P[prec] > s.ST[pos])
			{
				s.ST[pos] = s.ST[prec] + g.P[prec];
				s.pred[pos] = prec;
			}
		}

		machine = g.M[pos];
		if (s.MP[machine] != -1) // On regarde si une pièce a utilisé la machine avant
		{
			prec = s.MP[machine];
			if (s.ST[prec] + g.P[prec] > s.ST[pos])
			{
				s.ST[pos] = s.ST[prec] + g.P[prec];
				s.pred[pos] = prec;
			}
		}
		s.MP[machine] = pos;
	}

	for (int i = 1; i <= g.n; i++)
	{
		prec = i * g.m - 1;
		if (s.ST[prec] + g.P[prec] > s.total)
		{
			s.last_sommet = prec;
			s.total = s.ST[prec] + g.P[prec];
		}
	}
}

/**
 * @brief Procédure permettant d'initialiser une solution et de générer un vecteur de Bierwirth
 * 
 * @param[in] g variable stockant les données du Job Shop à traiter
 * @param[out] s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 */
void init_solution(instance_t& g, solution_t& s)
{
	int i, j;

	generer_VB(g, s);

	for (i = 0; i < g.n; i++)
	{
		s.N[i] = 0;
	}

	for (i = 0; i < g.m; i++)
	{
		s.MP[i] = -1;
	}

	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.m; j++)
		{
			s.T[i][j] = i * g.m + j;
			s.ST[i * g.m + j] = 0;
			s.pred[i * g.m + j] = -1;
		}
	}
	s.total = 0;
}

/**
 * @brief Procédure calculants les positions des sommets dans le vecteur de Bierwirth
 * @param[in] g variable stockant les données du Job Shop à traiter
 * @param[in] s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de 
 * @param[in] i variable représentant la position dans le graphe du sommet 1 à inverser 
 * @param[in] j variable représentant la position dans le graphe du sommet 2 à inverser 
 * @param[out] Posi variable représentant la position dans le vecteur de Bierwirth du sommet 1
 * @param[out] Posj variable représentant la position dans le vecteur de Bierwirth du sommet 2
 */
void position(instance_t& g, solution_t& s, int i, int j, int& Posi, int& Posj)
{
	int Pi = i / g.m;
	int Pj = j / g.m;

	int occ_i = 0;
	int occ_j = 0;

	int Mai = i % g.m;
	int Maj = j % g.m;

	Posi = 0;
	while (occ_i != Mai || s.VB[Posi] != Pi)
	{
		if (s.VB[Posi] == Pi)
			occ_i++;
		Posi++;
	}

	Posj = 0;
	while (occ_j != Maj || s.VB[Posj] != Pj)
	{
		if (s.VB[Posj] == Pj)
			occ_j++;
		Posj++;
	}
}

/**
 * @brief Procédure permettant d'optimiser une solution d'un Job Shop (comme par exemple une solution générée à partir d'un vecteur de Bierwirth)
 * 
 * @param g variable stockant les données du Job Shop à traiter
 * @param s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 */
void recherche_local(instance_t& g, solution_t& s)
{
	int i = s.last_sommet;
	int j = s.pred[i];

	int ite = 0;

	while (j != -1 && ite < ite_max)
	{
		if (g.M[i] == g.M[j])
		{
			int Posi, Posj;

			position(g, s, i, j, Posi, Posj);

			solution_t sP;
			init_solution(g, sP);

			for(int k = 0; k <= g.n * g.m; k++)
				sP.VB[k] = s.VB[k];

			sP.VB[Posi] = s.VB[Posj];
			sP.VB[Posj] = s.VB[Posi];

			evaluer(g, sP);

			if (sP.total < s.total)
			{
				s = sP;
				i = s.last_sommet;
				j = s.pred[i];
			}
			else
			{
				i = j;
				j = s.pred[i];
			}
		}
		else
		{
			i = j;
			j = s.pred[i];
		}
	}
}

/**
 * @brief Procédure permettant d'initialiser une table de hashage à 0
 * 
 * @param[in] g variable stockant les données du Job Shop à traiter
 * @param[out] hash tableau stockant la table de hashage
 */
void init_hash(instance_t g, int* hash)
{
	for(int i = 0; i < g.n * g.m; i++)
	{
		hash[i] = 0;
	}
}

/**
 * @brief Fonction qui vérifie que la solution n'a pas déjà été générée grace à la table de hashage
 * 
 * @param g variable stockant les données du Job Shop à traiter
 * @param s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 * @param hash tableau stockant la table de hashage
 * @return int 1 si la solution n'a pas été générée sinon retourne 0
 */
int tester_double(instance_t g, solution_t& s, int* hash)
{
	int k = h(g, s);
	
	if(!hash[k])
	{
		hash[k] = 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief Fonction qui calcule la fonction de hashage d'une solution
 * 
 * @param g variable stockant les données du Job Shop à traiter
 * @param s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 * @return int hash de la solution
 */
int h(instance_t& g, solution_t& s)
{
	int som = 0;
	for(int j = 0; j < g.n * g.m; j++)
	{
		som += s.ST[j];
	}

	return som % taille_hash;
}

/**
 * @brief Fonction qui génère un voisin d'une solution
 * 
 * @param g variable stockant les données du Job Shop à traiter
 * @param s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 * @return solution_t voisin d'une solution
 */
solution_t generer_voisin(instance_t g, solution_t& s)
{
	int rand1, rand2;
	solution_t sP;
	init_solution(g, sP);

	for(int k = 0; k <= g.n * g.m; k++)
		sP.VB[k] = s.VB[k];

	rand1 = std::rand() % (g.n * g.m);
	rand2 = std::rand() % (g.n * g.m);

	sP.VB[rand1] = s.VB[rand2];	
	sP.VB[rand2] = s.VB[rand1];

	return sP;
}

/**
 * @brief Procédure permettant d'optimiser une solution en générerant consécutivement des voisins de cette dernière censé converger vers une solution optimale
 * 
 * @param[in] g variable stockant les données du Job Shop à traiter
 * @param[out] s variable stockant les données du graphe généré à partir du Job Shop dont le vecteur de Bierwirth
 */
void GRASP(instance_t g, solution_t& s)
{
	solution_t tab[nombre_voisin];
	int voisin_obtenu, count;
	int hash[taille_hash];

	init_hash(g, hash);

	for(int i = 0; i < 1000; i++)
	{
		voisin_obtenu = 0;
		count = 0;
		while(voisin_obtenu != nombre_voisin && count < 10)
		{
			solution_t sP = generer_voisin(g, s);

			evaluer(g, sP);
 			recherche_local(g, sP);

			if(tester_double(g, sP, hash))
			{
				tab[voisin_obtenu] = sP;
				voisin_obtenu++;
			}
			else
			{
				count++;
			}
		}

		for(int j = 1; j < voisin_obtenu; j++)
		{
			if(tab[j].total < s.total)
			{
				s = tab[j];
			}
		}
	}
}

int main()
{
	clock_t start, end;

	instance_t g;
	solution_t s;

	std::srand(std::time(nullptr));

	std::cout << "Fichier     " << "Taille   " << "Temps obtenu   " << "Duree" << std::endl;

	/* Liste de tous les fichiers a traiter */
	std::string tab[] = {"la01.txt", "la02.txt", "la03.txt", "la04.txt", "la05.txt", "la06.txt", "la07.txt", "la08.txt", "la09.txt", "la10.txt", "la16.txt", "la26.txt", "la35.txt", "la36.txt"};
	int size_tab = sizeof(tab) / sizeof(std::string);
	
	for(int i = 0; i < size_tab ; i++)
	{
		start = clock();

		lire_instance(tab[i], g);

		init_solution(g, s);

		evaluer(g, s);
	
		recherche_local(g, s);

		GRASP(g, s);

		end = clock();

		std::cout << tab[i] << "    " << g.n << "x" << g.m << "     " << s.total << "            " << ((double)end - start) / CLOCKS_PER_SEC << "s" << std::endl;
	}

	return 0;
}

