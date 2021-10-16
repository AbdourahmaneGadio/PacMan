/******************************************************************************/
/* MAIN.h                                                                     */
/******************************************************************************/
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "../lib/libgraphique.h"
#include "./partie.h" // on a besoin de connaître la structure Partie

#define DEBUG 1

#endif

/******************************************************************************/
/* DECLARATIONS DES FONCTIONS                                                 */
/******************************************************************************/

void caractere2cases(char p);

void affichage_plateau(Partie p);

Partie deplacement_pacman(Partie p);

Partie tunnel_pacman(Partie p);

Partie deplacement_fantomes(Partie p);

/*Partie bonus(Partie p);*/

/*void changement_de_niveau(Partie p);*/

/******************************************************************************/
/* DEFINITIONS DES FONCTIONS                                                  */
/******************************************************************************/
	

Point position;

	
/*Change les caractères en cases                                               */
void caractere2cases(char p)
	{
	switch(p)	
		{	
		case '*': //Si le Caractère est un "*" (Mur)	
			dessiner_rectangle(position, 40, 40, blue);
			break;					
		case 'P': //Si le Caractère est un "P" (Pacman)	
			dessiner_rectangle(position, 40, 40, yellow);
			break;						
		case 'F': //Si le Caractère est un "F" (Fantôme)	
			dessiner_rectangle(position, 40, 40, pink);
			break;					
		case 'B': //Si le Caractère est un "B" (Bonus)	
			dessiner_rectangle(position, 40, 40, orange);
			break;			
		case ' ': //Si le Caractère est du vide
			dessiner_rectangle(position, 40, 40, black);	
			break;			
		case '.': //Si le Caractère est un "." (Boules à gober)
			dessiner_rectangle(position, 40, 40, yellowgreen);	
			break;	
		}	
	}

/* Affiche le plateau                                                         */
void affichage_plateau(Partie p)
    {  		
	int i,j;	
    for(i=0;i!=p.L;i++)     //Pour x lignes
        {
        for(j=0;j!=p.C;j++) //Pour x colonnes
			{
			position.x = j * (800 / p.C); //Met le plateau à la taille de la fenêtre
			position.y = i * (600 / p.L);	
			caractere2cases(p.plateau[i][j]);		
			}	
		}	
	}


/* Déplacement Pacman                                                         */
Partie deplacement_pacman(Partie p)
    {
	if ( (attendre_touche() == SDLK_LEFT) && (p.plateau[p.pacman.l][p.pacman.c - 1] != '*') )		 //Si Flèche gauche et pas de mur à gauche
		{
		p.pacman.c -= 1; 								//On décale Pacman sur la gauche
		p.plateau[p.pacman.l][p.pacman.c] = 'P'; 		//On met un caractère "P", la où se trouve actuellement Pacman		
		p.plateau[p.pacman.l][p.pacman.c + 1] = ' '; 	//On met un caractère " ", la où était Pacman
		}
	else if ( (attendre_touche() == SDLK_RIGHT) && (p.plateau[p.pacman.l][p.pacman.c + 1] != '*') ) //Si Flèche droite et pas de mur à droite
		{
		p.pacman.c += 1;								//On décale Pacman sur la droite
		p.plateau[p.pacman.l][p.pacman.c] = 'P'; 		
		p.plateau[p.pacman.l][p.pacman.c - 1] = ' '; 		
		}
	else if ( (attendre_touche() == SDLK_UP) && (p.plateau[p.pacman.l - 1][p.pacman.c] != '*') )    //Si Flèche haut et pas de mur en haut
		{
		p.pacman.l -= 1;								//On décale Pacman en haut
		p.plateau[p.pacman.l][p.pacman.c] = 'P'; 		
		p.plateau[p.pacman.l + 1][p.pacman.c] = ' '; 	
		}
	else if ( (attendre_touche() == SDLK_DOWN) && (p.plateau[p.pacman.l + 1][p.pacman.c] != '*') )  //Si Flèche bas et pas de mur en bas
		{
		p.pacman.l += 1;								//On décale Pacman en bas
		p.plateau[p.pacman.l][p.pacman.c] = 'P'; 		
		p.plateau[p.pacman.l - 1][p.pacman.c] = ' '; 	
		}
	return p;				
	}
	
	
/*Fait passer Pacman de l'autre côté du tunnel*/	
Partie tunnel_pacman(Partie p)
		{
		if (p.pacman.c == -1) //Si Pacman va à la gauche du tunnel
			{
			p.pacman.c = p.C;	  						//On lui donne la valeur de la dernière colonne
		    p.plateau[p.pacman.l][p.pacman.c] = 'P'; 	//On met Pacman à la droite du tunnel
		    p.plateau[p.pacman.l][0] = ' '; 			//On met du vide la où était Pacman
			}	
		else if (p.pacman.c == p.C + 1) //Si Pacman va à la droite du tunnel
			{
			p.pacman.c = 0;								//On lui donne la valeur de la première colonne
		    p.plateau[p.pacman.l][p.pacman.c] = 'P';    //On met Pacman à la gauche du tunnel
		    p.plateau[p.pacman.l][0] = ' '; 			
			}	
		return p;    					
		}
	


/* Déplacement Fantômes                                                        */
Partie deplacement_fantomes(Partie p)
    {
	int nbf;	
	for(nbf=0;nbf!=NBFANTOMES;nbf++)     //Pour x fantômes
        {		
		if ( (p.fantomes[nbf].c > p.pacman.c) && (p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c - 1] != '*') )		 //Si le fantôme dépasse Pacman de x cases à droite et pas de mur
			{	
			p.fantomes[nbf].c -= 1; 										//On décale le fantôme sur la gauche
			p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c] = 'F';			//On met un caractère "F", la où se trouve actuellement le fantôme
			p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c + 1] = ' ';		//On met un caractère " ", la où était le fantôme
			}
		else if ( (p.fantomes[nbf].c < p.pacman.c) && (p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c + 1] != '*') ) //Si le fantôme dépasse Pacman de x cases à gauche et pas de mur
			{	
			p.fantomes[nbf].c += 1; 										//On décale le fantôme sur la droite
			p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c] = 'F';			
			p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c - 1] = ' ';		
			}
		else if ( (p.fantomes[nbf].l > p.pacman.l) && (p.plateau[p.fantomes[nbf].l + 1][p.fantomes[nbf].c] != '*') ) //Si le fantôme dépasse Pacman de x cases en haut et pas de mur
			{	
			p.fantomes[nbf].l += 1; 										//On décale le fantôme en bas
			p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c] = 'F';			
			p.plateau[p.fantomes[nbf].l - 1][p.fantomes[nbf].c] = ' ';		
			}
		else if ( (p.fantomes[nbf].l < p.pacman.l) && (p.plateau[p.fantomes[nbf].l - 1][p.fantomes[nbf].c] != '*') ) //Si le fantôme dépasse Pacman de x cases en haut et pas de mur
			{
			p.fantomes[nbf].l -= 1; 										//On décale le fantôme sur la gauche
			p.plateau[p.fantomes[nbf].l][p.fantomes[nbf].c] = 'F';			
			p.plateau[p.fantomes[nbf].l + 1][p.fantomes[nbf].c] = ' ';		
			}
		}
	return p;	
	}


/*Bonus*/
/*Partie bonus(Partie p)
	{		
	if (p.nbbonus == p.nbbonus - 1) //Si le nombre de bonus a diminué de 1	
		attente(2000);				//On fait attendre les fantômes
	return p;	
	}
*/

/*Changement de niveau lorsque Pacman gagne*/
/*void changement_de_niveau(Partie p)
	{
	}
*/ 
