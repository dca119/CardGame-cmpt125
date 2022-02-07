#include "gameFunctions.h"

//a function that adds the card to the player's winning pile by calling
// the appropriate function from card_LList and update the cards won.
// Also marks the card as taken ('0').
void addCardToPlayer(Player* thePlayer, Card* theCard){
  insertFrontCard_LList(&thePlayer->winPile, theCard);
  thePlayer->cardsWon++;
  theCard->value = '0';
  theCard->suit = '0';
}

//a function that checks if the user choice is valid:
// if any of the choices are invalid, report that and return false.
bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col){
  int index = ((row-48)*13+(col-97));
  if (row<48||row>51){
    printf("Error: The card you picked has invalid index(es).\n");
    return false;
  }
  else if (col<97||col>109){
    printf("Error: The card you picked has invalid index(es).\n");
    return false; 
  }
  else if (theDeck->cards[index].suit == '0'){
    printf("Error: The card you picked is already taken.\n");
    return false;
  }
  return true;
}

//a function that checks if there is a match:
// if the two choices are the same, report it and return false.
// if there is a match, return true; otherwise, return false.
bool checkForMatch(Deck* theDeck, Player* thePlayer,
                    char r1, char c1, char r2, char c2){
  if (r2==c2&&r1!=c1){
    return true;
  }
  return false;
}

//a function that checks if the game has a winner
// (all cards in the deck is taken)
bool checkForWinner(const Deck* theDeck){
  for (int i=0; i<52; i++){
    if(theDeck->cards[i].suit!='0'){
      return false;
    }
  }
  return true;
}
