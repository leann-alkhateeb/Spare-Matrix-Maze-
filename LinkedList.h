#pragma once
#include <iostream>
#include <fstream>

using namespace std;

/*
NOTES:
1. Creates header nodes using numRows and numCols, linked right and down 
2. InternalList.h inherited from this base class, linked up, down, left, and right

NODE POINTERS:
next node: points to row, col+1, denoted current->next
prev node: points to row, col-1, denored current->prev
above node: points to row-1, col, denoted current->above
below node: points to row+1, col, denoted current->below
*/

struct Node {
  //'data' holds val at position, nodes for 4 directions
  int data, xPos, yPos; 
  Node* next; 
  Node* prev;  
  Node* above;
  Node* below;
};

class LinkedList {
private: 
    int pos; //FOR HEADER NODE (ROW/COL NUM)
    int size; //size of matrix (might need 2 vals for rows and cols)
    int numRows; //row position value
    int numCols; //column position value 
    Node* head; //beginning of list
    Node* other; //vertical link node? 

public:
    LinkedList();
    LinkedList(int, int); //header nodes: overload it for row and col length
    ~LinkedList(); //destructor
    bool CheckSize(int, int, int, int, char); //check if sizes match for operations, takes in sizes and operation
    void AddAtHead(int value); //will be placed at spot 0,0
    void Print(ostream &out); //print function 
    void Insert(int row, int col, int value); //insert val at correct coordinate
};

LinkedList::LinkedList(){
  head = nullptr;
  other = nullptr;
  size = 0;
}

//CREATING HEADER NODES: X POS FOR DOWN (ROWS), Y POS FOR RIGHT (COLS)
//LINK DOWN AND RIGHT
LinkedList::LinkedList(int nRows, int nCols) {
  head = nullptr;
  other = nullptr;
  numRows = nRows;
  numCols = nCols;
  
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      Node* tempRow = new Node();
      Node* tempCol = new Node();
      tempRow->data = i;
      tempCol->data = j;
      tempRow->next = nullptr;
      if(head == nullptr){
        head = tempRow;
        other = tempCol;
      }
      else{
        Node* previousRow = head;
        Node* previousCol = other;
        while(previousRow->next != nullptr){
          while(previousCol->below != nullptr){
          previousRow = previousRow->next;
          previousCol = previousCol->below;
          }
        }
        tempRow->next = previousRow->next;
        previousRow->next = tempRow;
        tempCol->next = previousCol->below;
        previousCol->below = tempCol;
      }
    }
  }
}

//DESTRUCTOR
LinkedList::~LinkedList() {
    //cout << "destructor called" << endl;
    Node* current = head;
    while(current != nullptr){
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

//CHECK IF RIGHT SIZE BEFORE OPERATING + OR *
bool LinkedList::CheckSize(int m1rows, int m1cols, int m2rows, int m2cols, char operation) {
    bool canOperate;
    if(operation == '+'){
      if(m1rows == m2rows && m1cols == m2cols){
        canOperate = true;
      }
    }
    else if(operation == '*'){
      if(m1cols == m2rows){
        canOperate = true;
      }
    }
  return canOperate;
}

//ADD TO BEGINNING 
void LinkedList::AddAtHead(int value) {
    Node* temp = new Node();
    temp->data = value;
    temp->next = nullptr;
    temp->prev = nullptr;
    
    if (head == nullptr) {
        head = temp;
    }
    else {
        temp->next = head;
        head = temp;
    }
    size++;
}

//PRINT HEADER NODES
void LinkedList::Print(ostream &out) {
  Node* current = head;
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      if(current->xPos == i && current->yPos == j){
        out << current->data << " ";
      }
      if(current->next != nullptr){current = current->next;}
    }
    out << endl;
  }
}

//INSERT HEADER NODES (CAN JUST DO IN CONSTRUCTOR)
void LinkedList::Insert(int row, int col, int value){
  Node* current = head;
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      if(current->xPos == row && current->yPos == col){
        current->data = value;
      }
      if(current->next != nullptr){current = current->next;}
    }
  }
}
