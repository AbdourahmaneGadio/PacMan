# Projet Pacman

## Travail accompli :
	
	- Changement des caractères du fichier plan, en cases
	- Affichage du plateau (Pacman, fantôme, bonus, et boules à gober)
	- Déplacement de Pacman avec les touches du clavier
	- Déplacement lorsque Pacman passe dans un tunnel
	- Déplacement du fantôme

## Problèmes rencontrés :

	- Le fantôme n'arrive pas à sortir de sa position initial
	- Difficulté à stopper les déplacements des fantômes, lorsque Pacman mange un bonus
	- Difficulté pour le changement du niveau

## Bugs connus :

	- Pacman devenait noir lorsqu'il se deplacait (Erreur de segmentation)
	- Il n'y avait pas de déplacements (Actualisation du plateau)
	- Le plateau bloquait lorsque Pacman passait dans un tunnel (Erreur de segmentation)	


## Idées originales :

	- Pacman clignote en jaune/rouge lorsqu'il mange un bonus (Idée non réalisée)
	
## Utilisation :

Installer les composants graphiques, avec : "sudo apt-get install libsdl1.2debian libsdl1.2-dev libsdl-ttf2.0-0 libsdl-ttf2.0-dev"

Compiler le code avec : gcc lib/libgraphique.c src/main.c -o nomDuFichier

Lancer le jeu avec : ./resultat data/nomDuNiveau.txt

Ex : ./resultat data/official.txt



