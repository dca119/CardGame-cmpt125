/*
CMPT 125 Assignment 4 Game
Author: David Choi
Student ID: 301438847
SFU email: david_choi_4@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01).
Description: This is the source code for the game. It implements the main
function that is the driver of the program. In also includes a clear function
that attemps to "push" the face up print up beyond the screen.
*/

#include <stdio.h>
#include <stdlib.h> //for the use of system and srand and rand
#include "gameObjects.h"
#include "gameFunctions.h"

#define MAX_CHAR_NUMBER 16 //each input should have at most 15 characters

//a helper function that clears the screen, works for both unix and Windows,
//though behaviour might be different.
//reference: https://stackoverflow.com/questions/2347770/
//            how-do-you-clear-the-console-screen-in-c
void clear() {
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("printf '\33[H\33[2J'");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

int main() {
  //set the random seed to 0, it'll generate the same sequence
  //normally it is srand(time(NULL)) so the seed is different in every run
  //using 0 makes it deterministic so it is easier to mark
  //do not change it
  srand(0);

  //variables to store user input
  char userInput1[MAX_CHAR_NUMBER];
  char userInput2[MAX_CHAR_NUMBER];
  int whereInDeck = 0; //handy for indexing which card based on user input
  int whereInDeck1 = 0; //handy for indexing which card based on user input

  //set up the players
  Player player1, player2;
  initializePlayer(&player1, "Player 1");
  initializePlayer(&player2, "Player 2");
  Player* currentPlayer = &player1; //this pointer remembers who's turn it is


  //set up the deck: initalize & shuffle
  Deck myDeck;
  initializeDeck(&myDeck, "Bicycle");
  shuffleDeck(&myDeck);

  printDeck(&myDeck, true); //print the shuffled deck, face up
  printf("\n");
  clear(); //clear the screen

  /*
  Implement this part for the game to work.
  It is essentially a do-while loop that repeatedly print the deck,
  ask for user inputs, and do some checking. Ends if someone wins.
  */
  do {
    /////////////////////
    // 1 Round
    ////////////////////
    //Step 1: print the shuffled deck, face down
    printDeck(&myDeck, false);
    printf("\n");


    //Step 2: print who's turn it is by showing the player's name
    printf("%s's turn.\n",currentPlayer->name);


    //Step 3.1 get first input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
    do{
      printf("Pick the first card you want to turn (e.g., 0 a) then press enter: ");
      scanf(" %[^\n]",userInput1);
    } while (!checkPlayerInput(&myDeck, currentPlayer, userInput1[0], userInput1[2]));
    whereInDeck = (userInput1[0]-48)*13+(userInput1[2]-97);


    //Step 3.2: get second input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
    do{
      printf("Pick the second card you want to turn (e.g., 1 b) then press enter: ");
      scanf(" %[^\n]",userInput2);
    } while (!checkPlayerInput(&myDeck, currentPlayer, userInput2[0], userInput2[2]));
    whereInDeck1 = (userInput2[0]-48)*13+(userInput2[2]-97);
    

    //Step 4: print the 2 cards the player picks
    printf("\nFirst card picked: ");
    int suit1 = myDeck.cards[whereInDeck].suit;
    int value1 = myDeck.cards[whereInDeck].value;
    if (suit1 == 0){
      printf("%c\u2660 \n",value1);
    }
    else if(suit1 == 1){
      printf("%c\u2661 \n",value1);
    }
    else if(suit1 == 2){
      printf("%c\u2663 \n",value1);
    }
    else if(suit1 == 3){
      printf("%c\u2662 \n",value1);
    }

    printf("Second card picked: ");
    int suit2 = myDeck.cards[whereInDeck1].suit;
    int value2 = myDeck.cards[whereInDeck1].value;
    if (suit2 == 0){
      printf("%c\u2660 \n",value2);
    }
    else if(suit2 == 1){
      printf("%c\u2661 \n",value2);
    }
    else if(suit2 == 2){
      printf("%c\u2663 \n",value2);
    }
    else if(suit2 == 3){
      printf("%c\u2662 \n",value2);
    }
  
  
    //Step 5: call the checkForMatch function to see if the player has picked
    // a matching pair. If so, print the corresponding message and add the cards
    // to the player's winning pile (Player.winPile).
    // Keep the current player as a match leads to an extra round.
    // Otherwise, print the corresponding message and switch player.
    if (suit1==suit2&&value1==value2){
      printf("Error: Both cards are the same.\n");
    }
    if(!checkForMatch(&myDeck, currentPlayer,suit1, suit2, value1, value2)){
      printf("\n%s has not found a match.\n", currentPlayer->name);
      if (currentPlayer->name == player1.name){
        currentPlayer = &player2;
      }
      else {
        currentPlayer = &player1;
      }
    }
    else{
      printf("\n%s found a match! Earns an extra turn.\n", currentPlayer->name);
      addCardToPlayer(currentPlayer, &myDeck.cards[whereInDeck]);
      addCardToPlayer(currentPlayer, &myDeck.cards[whereInDeck1]);
    }
  } while (!checkForWinner(&myDeck));


  //Step 6: find out who won the game and announce the winner
  printf("%s has won %d cards.\n",player1.name,player1.cardsWon);
  printf("%s has won %d cards.\n",player2.name,player2.cardsWon);
  if (player1.cardsWon>player2.cardsWon){
    printf("%s has won!\n",player1.name);
  }
  else if (player1.cardsWon==player2.cardsWon){
    printf("It is a tie!\n");
  }
  else {
    printf("%s has won!\n",player2.name);
  }


  //Step 7: clean up player's winning piles
  clearPlayer(&player1);
  clearPlayer(&player2);
  
  return 0;
}
