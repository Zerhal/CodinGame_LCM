CodinGame_LCM

Code CPP pour Legend of Code and Magic.


Ce puzzle se déroule en ligues.
Les ligues Bois doivent être considérées comme un tutoriel pour apprendre les différentes règles du jeu. 
En ligue Bronze, toutes les règles sont débloquées et alors débute le challenge, le vrai.
 
Objectif
Constituer un paquet de cartes, combattre un adversaire avec ces cartes, et réduire ses points de vie (PV) de 30 à 0.
 
Règles du jeu
Ce jeu de cartes à deux joueurs se joue en deux phases: une phase de "Draft" et une phase de Bataille.
Pendant la phase de Draft, chaque joueur doit constituer un "deck" (paquet) de 30 cartes.
Une fois que le Draft est terminé, les decks des deux joueurs sont mélangés.
Pendant la Bataille, le plateau de jeu est divisé en deux : un côté pour chaque joueur.
Pour réduire les PVs de son adversaire, le joueur doit utiliser ses cartes pour lui infliger des dégâts.
 
Le Draft
À chaque tour (pendant 30 tours), un choix de 3 cartes est proposé aux deux joueurs. Les joueurs sélectionnent la carte qu'ils veulent ajouter à leur deck en utilisant la commande PICK suivi de 0, 1 ou 2.
Par défaut, la commande PASS sélectionnera la première carte.
Les deux joueurs peuvent choisir la même carte, ils recevront chacun une copie.
 
La Bataille
Pioche des cartes
Le premier joueur commence avec 4 cartes en main, alors que son adversaire commence avec 5.
À chaque tour, le joueur actif pioche la première carte de son deck.
Chaque joueur possède des runes qui ont un impact sur la pioche de cartes. 
Néanmoins, les runes doivent être ignorées dans les ligues Bois. Plus de détails en ligue Bronze.
La mana
La mana est nécessaire pour jouer les cartes en main.
Le premier joueur commence avec 1 mana maximum, le deuxième commence avec un bonus de 1, donc avec 2 mana maximum.
Chaque joueur peut dépenser autant de mana par tour que de mana maximum.
Le deuxième joueur perds son bonus de 1 mana maximum dès lors qu'il dépense toute sa mana disponible en un tour.
A chaque tour, le joueur actif obtient un mana maximum additionel, à moins d'en avoir déjà 12 (ou 13si le jouer a encore son bonus).
 
Les types de cartes
Dans cette ligue, il n'y a qu'un type de carte : les Créatures. 

Créatures
"Invoquer une créature" signifie jouer une carte de créature sur son côté du plateau de jeu depuis sa main.
Chaque joueur invoque des créatures, en payant leur coût en mana, qui ensuite pourront attaquer l'adversaire. Elles sont aussi un moyen de défense contre les créatures adverses.
Une créature est définie par son coût en mana, ainsi que par ses caractéristiques d'attaque et de défense.
Par défaut, une créature ne peut pas attaquer le tour où elle est invoquée. 
Une créature ne peut attaquer qu'une seule fois par tour.
Lorsqu'une créature en attaque une autre, chacune inflige autant de dégâts que son attaque à la défense de l'autre créature. Si une créature attaque un joueur, elle lui inflige directement ses dégâts d'attaque.
Si les PVs d'une créature tombent à 0 ou moins, alors elle est retirée du jeu.
 
Gameplay
Actions possibles
SUMMON id pour invoquer une créature
ATTACK id1 id2 pour attaquer la créature id2 avec la créature id1.
ATTACK id -1 pour attaquer l'adversaire avec la créature id.
PASS pour passer son tour.
Un joueur peut faire autant d'actions valides qu'il le désire pendant un tour. Les commandes doivent êtres séparées entre elles par un point-virgule (;).

Fin d'une partie
La partie se termine une fois que les PVs d'un des joueurs atteint 0 ou moins.
Conditions de victoire
Réduire les points de vie de votre adversaire (PVs) de 30 à 0 ou moins.
Conditions de défaite
Votre total de PVs est réduit à 0 ou moins.
Votre code ne répond pas dans les temps ou retourne une commande non reconnue.

 
Détails avancés
Cette section sera disponible en ligue Bronze, de même que le code source du jeu. 

 
Protocole du jeu
Entrée pour un tour de jeu
2 premières lignes : pour chaque joueur, playerHealth, playerMana, playerDeck et playerRune:
Un entier playerHealth : le total de PVs restants du joueur.
Un entier playerMana : le mana maximum du joueur.
Un entier playerDeck : le nombre de cartes dans le deck du joueur. Pendant la phase de Draft, le deuxième joueur a toujours moins de cartes dans son deck que le premier joueur.
Un entier playerRune : à ignorer dans cette ligue
Integer playerDraw: à ignorer dans cette ligue.
Les données d'entrée du joueur actif sont données en premier suivi de l'entrée correspondant à son adversaire.

Pendant la phase de Draft, playerMana vaut toujours 0.

Ligne suivante :
Un entier opponentHand pour le nombre total de cartes dans la main de l'adversaire. Ces cartes sont cachées jusqu'à qu'elles soient jouées.
Un entier opponentActions pour la quantité d'actions effectuées par l'adversaire lors du tour précédent.
opponentActions lignes suivantes : pour chaque action de l'adversaire, une chaîne de caractères cardNumberAndAction contenant l'identifiant cardNumber de la carte jouée, puis un espace, puis l'action associée à la carte (voir la section Actions possibles).

Ligne suivante : un entier cardCount, le nombre total de cartes sur le plateau de jeu et dans la main du joueur actif.

cardCount lignes suivantes : pour chaque carte, cardNumber, instanceId, location, cardType, cost, attack, defense, abilities, myhealthChange, opponentHealthChange et cardDraw:
Un entier cardNumber : l'identifiant de la carte (voir la liste complète).
Un entier instanceId : l'identifiant représentant l'instance de la carte (il peut y avoir plusieurs instances de la même carte dans une même partie).
Un entier location:
0 : dans la main du joueur actif
1 : sur le plateau de jeu, du côté du joueur actif
-1 : sur le plateau de jeu, du côté de son adversaire
Un entier cardType: toujours 0 dans cette ligue.
Un entier cost : le coût en mana d'une carte,
Un entier attack : les caractéristiques d'attaque d'une créature.
Un entier defense : les caractéristiques de défense d'une créature.
Un String abilities de taille 6: à ignorer dans cette ligue.
Un entier myHealthChange : à ignorer dans cette ligue.
Un entier opponentHealthChange : à ignorer dans cette ligue.
Un entier cardDraw : à ignorer dans cette ligue.
Sortie pour un tour de jeu du Draft
PICK nb où nb vaut 0, 1 ou 2 pour choisir l'une des trois cartes proposées à ajouter dans son deck.
PASS pour ne rien faire (sélectionne la première carte par défaut).
Sortie pour un tour de jeu de la Bataille
Les actions disponibles sont les suivantes :
SUMMON id pour invoquer une créature ayant pour identifiant (d'instance) id depuis la main du joueur.
ATTACK idAttacker idTarget pour attaquer une créature adverse d'identifiant (d'instance) idTarget ou l'adversaire (identifiant -1) avec une créature d'identifiant (d'instance) idAttacker.
PASS pour ne rien faire et passer son tour.
Chaque joueur peut utiliser plusieurs de ces commandes en les séparant par un point-virgule ;. 
Chaque joueur peut ajouter du texte à la suite de ses commandes. Les messages seront affichés par le lecteur de parties.

Exemple : SUMMON 3;ATTACK 4 5 yolo; ATTACK 8 -1 no fear.
Contraintes
0 ≤ cost ≤ 12
0 ≤ créatures sur un côté du plateau de jeu ≤ 6
0 ≤ cartes en main ≤ 8

Temps de réponse pour le premier tour du Draft ≤ 1000ms
Temps de réponse pour le premier tour de la Bataille ≤ 1000ms
Temps de réponse pour un tour ≤ 100ms

Qu'est-ce qui vous attend dans les ligues supérieures ?
Voici les règles supplémentaires à débloquer dans les ligues supérieures :
En Bois 2, certaines créatures ont des capacité spéciales.
En Bois 1, les joueurs peuvent jouer un nouveau type de carte : les objets.
En Bronze, plus de capacités spéciales !

Etat : Incomplet 

progression actuelle : 10 % 