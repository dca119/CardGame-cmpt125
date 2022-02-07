#include "gameObjects.h"


//a function that initializes all the fields of a Deck.
// For each suit, the values of the cards are
// ‘A’, ‘2’, ‘3’, …, ‘9’, ,'T', ‘J’, ‘Q’, ‘K’.
void initializeDeck(Deck* theDeck, char* brandName){
  /*
  Start initializing the values and suits of the cards with a for loop to repeat
  4 times because of the 4 suits. Also, use a for loop for cards values
  2-9 for efficiency.
  */
  for (int j=0; j<4; j++){
    theDeck->cards[0+(j*13)].value = 'A';
    for (int i=1; i<9; i++){
      theDeck->cards[i+(j*13)].value = 49+i;
    }
    theDeck->cards[9+(j*13)].value = 'T';
    theDeck->cards[10+(j*13)].value = 'J';
    theDeck->cards[11+(j*13)].value = 'Q';
    theDeck->cards[12+(j*13)].value = 'K';
    for (int k=0; k<13; k++){
      theDeck->cards[k+(j*13)].suit = j;
    }
  }
}

//a function that shuffles the deck
void shuffleDeck(Deck* theDeck){
  /*
  Shuffle the deck by using a for loop to swap the cards 
  randomly by using rand() to generate random indexes.
  Credits: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
           Answer by: John Leehey
  */
  unsigned int i;
  for (i = 0; i < 52 - 1; i++){
    unsigned int j = i + rand() / (RAND_MAX / (52 - i) + 1);
    char temp = theDeck->cards[j].value;
    char temp1 = theDeck->cards[j].suit;
    theDeck->cards[j].value = theDeck->cards[i].value;
    theDeck->cards[j].suit = theDeck->cards[i].suit;
    theDeck->cards[i].value = temp;
    theDeck->cards[i].suit = temp1;
  }
}

//a function that prints the content of a Deck.
//accepts a second bool parameter:
//if true, print face up, if false, print face down.
//if the card is won by a player, leave it blank.
void printDeck(const Deck* theDeck, bool faceUp){
  /*
  First print the brand of the deck. Then, use a for loop to print 
  all 52 cards of the deck. First print the value of the card then,
  use conditionals to see which suit the card has and print accordingly.
  Also, print a newline every 13 cards.
  */
  if (faceUp){
    printf("   ");
    for (int i=0; i<13; i++){
      printf("%c  ",i+97);
    }
    printf("\n");
    int counter = 0;
    for (int i=0; i<52; i++){
      if (i%13==0&&i<50){
        printf("%d ",counter);
        counter++;
      }
      printf("%c",theDeck->cards[i].value);
      if(theDeck->cards[i].suit == 0){
        printf("\u2660 ");
      }
      else if(theDeck->cards[i].suit == 1){
        printf("\u2661 ");
      }
      else if(theDeck->cards[i].suit == 2){
        printf("\u2663 ");
      }
      else if(theDeck->cards[i].suit == 3){
        printf("\u2662 ");
      }
      if ((i+1)%13==0){
        printf("\n");
      }
    }
  }
  else{
    // Printing the alphabet index
    printf("   ");
    for (int i=0; i<13; i++){
      printf("%c  ",i+97);
    }
    printf("\n");
    int counter = 0;
    for (int i=0; i<52; i++){
      // Printing the numerical index
      if (i%13==0&&i<50){
        printf("%d ",counter);
        counter++;
      }
      // Checking if the card is taken or not
      if (theDeck->cards[i].value=='0'){
        printf("   ");
      }
      else {
        printf("%c\u218C ", '?');
      }
      if ((i+1)%13==0){
        printf("\n");
      }
    }
  }
}


//a function that initializes all the fields of a Player.
void initializePlayer(Player* thePlayer, char* theName){
  thePlayer->cardsWon = 0;
  thePlayer->name = theName;
  thePlayer->winPile.head = NULL;
  thePlayer->winPile.tail = NULL;
}

//a function clears the winning pile of the player by calling the necessary
// function on a Card_LList.
void clearPlayer(Player* thePlayer){
  clearCard_LList(&thePlayer->winPile);
}
