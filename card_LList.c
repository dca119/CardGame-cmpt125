#include "card_LList.h"
#include "gameObjects.h"

//a function that creates a new Card_LList, which is an empty linked list.
Card_LList* createCard_LList(){
  Card_LList* New = malloc(sizeof(Card_LList));
  if(New){
    New->head = NULL;
    New->tail = NULL;
  }
  return New;
}

//a function that removes all the nodes from the list
// by freeing them one by one. The result is an empty linked list.
void clearCard_LList(Card_LList* theList){
  Card_Node* destroy = theList->head;
  Card_Node* next;
  if (theList->head!=NULL){
    while(destroy!=NULL){
      next = destroy->next;
      free(destroy);
      destroy = next;
    }
  } 
  theList->head = NULL;
  theList->tail = NULL;
}

//a function that checks if the list is empty.
// If it is empty, return true; otherwise return false.
bool isEmptyCard_LList(Card_LList* theList){
  if (theList==NULL){
    return true;
  }
  if (theList->head==NULL||theList->tail==NULL){
    return true;
  }
  return false;
}

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertFrontCard_LList(Card_LList* theList, Card* theCard){
  Card_Node* front = malloc(sizeof(Card_Node));
  if (front){
    front->card = theCard;
    front->next = NULL;
  }
  if (theList->tail == NULL){
    theList->tail = front;
  }
  if (theList->head){
    front->next = theList->head;
  }
  theList->head = front;
}

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertEndCard_LList(Card_LList* theList, Card* theCard){
  Card_Node* front = malloc(sizeof(Card_Node));
  if (front){
    front->card = theCard;
    front->next = NULL;
  }
  if (theList->head == NULL){
    theList->head = front;
  }
  if (theList->tail){
    theList->tail->next = front;
  }
  theList->tail = front;
}

/*
A function that returns the address of the card stored in the node.
This method encapsulates the inner workings of the linked list and
there is no need to duplicate the card.
Freeing of the node memory is done here.
Checks cases of having only 0-1 node.
*/
Card* removeFrontCard_LList(Card_LList* theList){
  if (theList->head == NULL){
    return NULL;
  }
  Card* temp = theList->head->card;
  free(theList->head);
  if (theList->head->next == NULL){
    theList->head = NULL;
    theList->tail = NULL;
    return temp;
  }
  theList->head = theList->head->next;
  return temp;
}

/*
A function that returns the address of the card stored in the node.
This method encapsulates the inner workings of the linked list and
there is no need to duplicate the card.
Freeing of the node memory is done here.
Checks cases of having 0-2 nodes.
*/
Card* removeEndCard_LList(Card_LList* theList){
  if (theList->tail==NULL){
    return NULL;
  }
  if (theList->head->next==NULL){
    Card* lastNode = theList->head->card;
    theList->head = NULL;
    theList->tail = NULL;
    return lastNode;
  }
  Card_Node* temp = theList->head;
  if(theList->head->next->next!=NULL){
    while(temp->next->next != NULL){
      temp = temp->next;
    }
  }
  Card* lastNode = temp->next->card;
  free(temp->next);
  temp->next = NULL;
  theList->tail = temp;
  return lastNode;   
}

