﻿#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



class Card{
  private:
    int cardNumber;// l'identifiant de la carte (voir la liste complète).

    int instanceId;//  l'identifiant représentant l'instance de la carte (il peut y avoir plusieurs instances de la même carte dans une même partie).

    int location;// 0 : dans la main du joueur actif  1 : sur le plateau de jeu, du côté du joueur actif  -1 : sur le plateau de jeu, du côté de son adversaire

    int cardType;// toujours 0 dans cette ligue.

    int cost;// le coût en mana d'une carte,

    int attack;// les caractéristiques d'attaque d'une créature.

    int defense;// les caractéristiques de défense d'une créature.

    string abilities;// de taille 6: à ignorer dans cette ligue.

    int myHealthChange;
    int opponentHealthChange;
    int cardDraw;

  public:
    Card(){};
    ~Card() {};
    Card(int cardNumber, int instanceId, int location, int cardType, int cost, int attack, int defense, string abilities, int myHealthChange, int opponentHealthChange, int cardDraw){
      this->cardNumber = cardNumber;
      this->instanceId = instanceId;
      this->location = location;
      this->cardType = cardType;
      this->cost = cost;
      this->attack = attack;
      this->defense = defense;
      this->abilities = abilities;
      this->myHealthChange = myHealthChange;
      this->opponentHealthChange = opponentHealthChange;
      this->cardDraw = cardDraw;
    }

    int getCost(){
      return this->cost;
    }

    int getAttack(){
      return this->attack;
    }

    int getDefense(){
      return this->defense;
    }

    int getLocation(){
      return this->location;
    }

    int getInstanceId(){
      return this->instanceId;
    }

    int getCardNumber(){
      return this->cardNumber;
    }
};


class Player{
  private:
    int playerHealth; // le total de PVs restants du joueur.

    int playerMana; //  le mana maximum du joueur.

    int playerDeck; // le nombre de cartes dans le deck du joueur

    int playerRune;

    int playerDraw;

    int opponentHand; // pour le nombre total de cartes dans la main de l'adversaire. Ces cartes sont cachées jusqu'à qu'elles soient jouées.

    int opponentActions; // pour la quantité d'actions effectuées par l'adversaire lors du tour précédent.

    string cardNumberAndAction; // : pour chaque action de l'adversaire, une chaîne de caractères cardNumberAndAction contenant l'identifiant cardNumber de la carte jouée, puis un espace, puis l'action associée à la carte (voir la section Actions possibles).
   
    std::vector<Card> mainActuelle {}; // tableau de carte contant notre main

    std::vector<Card> plateau {}; // // tableau de carte contant le plateau 

    std::vector<Card> playerDeckCard {}; // tableau de carte contant notre liste de carte de nore deck en fonction de carte choisis lors du draft

    std::vector<int> manaCourbe {0,0,0,0,0,0,0}; // tableau representant la courbe de mana actuelle

  public:
  Player(){};
  ~Player(){};
  Player(int playerHealth, int playerMana, int playerDeck, int playerRune, int playerDraw){
    this->playerHealth = playerHealth;
    this->playerMana = playerMana;
    this->playerDeck = playerDeck;
    this->playerRune = playerRune;
    this->playerDraw = playerDraw;
  }

  // Player Mana Courbe
  void setManaCourbe(int p, int c){
    this->manaCourbe.at(p) = c;
  }

  vector<int> getManaCourbe(){
    return this->manaCourbe;
  }

  // Player Deck
  void setPlayerDeckCard(Card p){
    this->plateau.push_back(p);
  }

  vector<Card> getPlayerDeckCard(){
    return this->playerDeckCard;
  }

  // Plateau
  void setPlateau(Card p){
    this->plateau.push_back(p);
  }

  vector<Card> getPlateau(){
    return this->plateau;
  }

  void clearPlateau(){
    this->plateau.clear();
  }
  

  // Main 
  void setMainActuelle(Card p){
    this->mainActuelle.push_back(p);
  }
  
  void clearMain(){
    this->mainActuelle.clear();
  }

  vector<Card> getMainActuelle(){
    return this->mainActuelle;
  }

  // Action Ennemi
  void setCardNumberAndAction(string cardNumberAndAction){
    this->cardNumberAndAction = cardNumberAndAction;
  }

  string getCardNumberAndAction(){
    return this->cardNumberAndAction;
  }

  // Nb d'Action
  void setOpponentActions(int opponentActions){
    this->opponentActions = opponentActions;
  }

  int getOpponentActions(){
    return this->opponentActions;
  }
  
  // Nb de Carte Main Ennemi
  void setOpponentHand(int opponentHand){
    this->opponentHand = opponentHand;
  }

  int getOpponentHand(){
    return this->opponentHand;
  }

  // Vie Joueur
  int getPlayerHealth(){
    return this->playerHealth;
  }

  void setPlayerHealth(int pdv){
    this->playerHealth = pdv;
  }

  // Mana Joueur
  int getPlayerMana(){
    return this->playerMana;
  }

  void setPlayerMana(int mana){
    this->playerMana = mana;
  }

  // Nb Carte Joueur
  int getPlayerDeck(){
    return this->playerDeck;
  }

  void setPlayerDeck(int deck){
    this->playerDeck = deck;
  }

  // Nb Rune Joueur
  int getPlayerRune(){
    return this->playerRune;
  }
  
  void setPlayerRune(int rune){
    this->playerRune = rune;
  }

  // Nb Carte A Piocher
  int getPlayerDraw(){
    return this->playerDraw;
  }

  void setPlayerDraw(int draw){
    this->playerDraw = draw;
  }
};
// Comparaison des carte pour le choix lors du Darft
int compareCard(Card* ptr_c1, Card* ptr_c2, Card* ptr_c3, int nbTour){

  Card c1 = *ptr_c1;
  Card c2 = *ptr_c2;
  Card c3 = *ptr_c3;

  int bestCard = 1;
  int cost1 = c1.getCost();
  int cost2 = c2.getCost();
  int cost3 = c3.getCost();

  float attack1 = c1.getAttack();
  float attack2 = c2.getAttack();
  float attack3 = c3.getAttack();

  float defense1 = c1.getDefense();
  float defense2 = c2.getDefense();
  float defense3 = c3.getDefense();

  if(cost1 > 0 && cost2 > 0 && cost3 > 0){ 
    float rate1 = (defense1+attack1)/cost1;
    float rate2 = (defense2+attack2)/cost2;
    float rate3 = (defense3+attack3)/cost3;
    cerr << rate1 << endl;
    if(nbTour < 31){
      if((rate1 > rate2 && rate1 > rate3)){
        bestCard = 0;
        cerr << bestCard << endl;
      }else if((rate2 > rate1 && rate2 > rate3)){
        bestCard = 1;
        cerr << bestCard << endl;
      }else if((rate3 > rate1 && rate3 > rate2)){
        bestCard = 2;
        cerr << bestCard << endl;
      }else if(defense1 >= attack1 && (rate1 > rate2 && rate1 > rate3)){
        bestCard = 0;
        cerr << bestCard << endl;
      }else if(defense2 >= attack2 && (rate2 > rate1 && rate2 > rate3)){
        bestCard = 1;
        cerr << bestCard << endl;
      }else if(defense3 >= attack3 && (rate3 > rate1 && rate3 > rate2)){
        bestCard = 2;
        cerr << bestCard << endl;
      } 
    }
  }
  return bestCard;
}
// init des joueurs avant de commencer la partie.
Player zerhal = Player();
Player ennemi = Player();
int main()
{
    int nbTour = 1;
    // game loop
    while (1) {
      // pour chaque joueur mise de leur stat actuelle.
        for (int i = 0; i < 2; i++) {
            int playerHealth;
            int playerMana;
            int playerDeck;
            int playerRune;
            int playerDraw;
            cin >> playerHealth >> playerMana >> playerDeck >> playerRune >> playerDraw; cin.ignore();
            if(i == 0){
              zerhal.setPlayerHealth(playerHealth);
              zerhal.setPlayerMana(playerMana);
              zerhal.setPlayerDeck(playerDeck);
              zerhal.setPlayerRune(playerRune);
              zerhal.setPlayerDraw(playerDraw);
            }else if(i == 1){
              ennemi.setPlayerHealth(playerHealth);
              ennemi.setPlayerMana(playerMana);
              ennemi.setPlayerDeck(playerDeck);
              ennemi.setPlayerRune(playerRune);
              ennemi.setPlayerDraw(playerDraw);
            }
        }
       // pas encore d'utilité a ca... 
        int opponentHand;
        int opponentActions;
        string cardNumberAndAction;
        cin >> opponentHand >> opponentActions; cin.ignore();
        ennemi.setOpponentHand(opponentHand);
        ennemi.setOpponentActions(opponentActions);
        for (int i = 0; i < opponentActions; i++) {
            getline(cin, cardNumberAndAction);
        }
        ennemi.setCardNumberAndAction(cardNumberAndAction);
        int cardCount;
        cin >> cardCount; cin.ignore();

        // si on a passer la phase de draft
        if(nbTour > 30){
          string actionZerhal;
          zerhal.clearPlateau();
          ennemi.clearPlateau();
          zerhal.clearMain();
          for (int i = 0; i < cardCount; i++) {
            int cardNumber;
            int instanceId;
            int location;
            int cardType;
            int cost;
            int attack;
            int defense;
            string abilities;
            int myHealthChange;
            int opponentHealthChange;
            int cardDraw;
            cin >> cardNumber >> instanceId >> location >> cardType >> cost >> attack >> defense >> abilities >> myHealthChange >> opponentHealthChange >> cardDraw; cin.ignore();
            Card carte = Card(cardNumber, instanceId, location, cardType, cost, attack, defense, abilities, myHealthChange, opponentHealthChange, cardDraw);
            // on établie ou chaque carte sont situé !
            if(location == 0){
              zerhal.setMainActuelle(carte);
            }else if(location == 1){
              zerhal.setPlateau(carte);
            }else{
              ennemi.setPlateau(carte);
            }
            //  gestion nul de la summon en attendant de réfléchir a un algo correct...
            cerr << "card cost " + to_string(carte.getCost()) + " zerhal vie = " + to_string(zerhal.getPlayerHealth()) << endl;
            if(carte.getLocation() == 0 && zerhal.getPlateau().size() < 6){
              if(carte.getCost() <= zerhal.getPlayerMana()){
                int id = carte.getInstanceId();
                cerr << "id : " + to_string(id) << endl;
                actionZerhal = "SUMMON " + to_string(id);
              }
            }else if(carte.getLocation() == 1){
              
            }
          }
          if(actionZerhal.length() < 5){
            actionZerhal = "PASS";
          }
          cout << actionZerhal  << endl;
          
        //durant la phase de draft           
        }else if(nbTour <= 30){
          int nbCarteDraft (1);
          Card carte1 = Card();
          Card carte2 = Card();
          Card carte3 = Card();
          int actionZ;
          for (int i = 0; i < cardCount; i++) {
              int cardNumber;
              int instanceId;
              int location;
              int cardType;
              int cost;
              int attack;
              int defense;
              string abilities;
              int myHealthChange;
              int opponentHealthChange;
              int cardDraw;
              cin >> cardNumber >> instanceId >> location >> cardType >> cost >> attack >> defense >> abilities >> myHealthChange >> opponentHealthChange >> cardDraw; cin.ignore();
              if(nbCarteDraft == 1){
                carte1 = Card(cardNumber, instanceId, location, cardType, cost, attack, defense, abilities, myHealthChange, opponentHealthChange, cardDraw);
              }else if(nbCarteDraft == 2){
                carte2 = Card(cardNumber, instanceId, location, cardType, cost, attack, defense, abilities, myHealthChange, opponentHealthChange, cardDraw);
              }else if(nbCarteDraft == 3){
                carte3 = Card(cardNumber, instanceId, location, cardType, cost, attack, defense, abilities, myHealthChange, opponentHealthChange, cardDraw);
              }
              nbCarteDraft++;
          }

          Card *ptr_carte1 (0);
          Card *ptr_carte2 (0);
          Card *ptr_carte3 (0);

          
          ptr_carte1 = &carte1;
          ptr_carte2 = &carte2;
          ptr_carte3 = &carte3;


          Card cardX1 = *ptr_carte2;
          //resultat de la comparaison
          actionZ = compareCard(ptr_carte1, ptr_carte2, ptr_carte3, nbTour);
          cout << "PICK " << actionZ  << endl; 
          
          cerr << nbTour << endl;
        }
        nbTour++;
    }
}