#pragma once 
#include "LinkedList.h"
#include <iostream>
#include <fstream>

using namespace std;

struct iNode {
  //val at position, coordinates, and pointers
  int data; 
  int xPos, yPos;
  iNode* next; 
  iNode* prev;  
  iNode* above;
  iNode* below;
};

class SparseMatrix : public LinkedList{
  public:
    SparseMatrix();
    SparseMatrix(int numRows, int numCols); //overloaded create base sized matrix
    void Insert(int row, int col, int value); //assign non zero values
    int GetData(int row, int col); //return data at coordinate
    SparseMatrix transpose(); //transpose single matrix
    SparseMatrix operator+(SparseMatrix& rhs); //add matrices of same size
    SparseMatrix operator*(SparseMatrix& rhs); //mult matrices (m1 cols = m2 rows)
    void Print(ostream &out); //print resulting matrix

  private:
    iNode* head;
    int numRows, numCols;
};

SparseMatrix::SparseMatrix(){
  head = nullptr;
}


//creates basic linked list filled with zeroes
//links next, prev, above, and below based on placement
SparseMatrix::SparseMatrix(int nRows, int nCols){
  head = nullptr;
  numRows = nRows;
  numCols = nCols;
  
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      iNode* temp = new iNode();
      temp->data = 0;
      temp->xPos = i;
      temp->yPos = j;
      temp->next = nullptr;
      temp->prev = nullptr;
      temp->above = nullptr;
      temp->below = nullptr;
      if(head == nullptr){
          head = temp;
      }
      else{
        iNode* previous = head;
        while(previous->next != nullptr) {
            previous = previous->next;
        } 
        temp->prev = previous;
        temp->next = previous->next;
        temp->below = previous->below;
        temp->above = previous->above;
        previous->next = temp;
      }
    }
  }
}


//inserts correct numbers in their positions (already linked in all directions)
void SparseMatrix::Insert(int row, int col, int value){
  iNode* current = head;
  iNode* previous = nullptr;
  
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      if(current->xPos == row && current->yPos == col){
        current->data = value;
      }
      
      if(row == 0){
        current->above = nullptr;
      }
      if(row == numRows-1){
        current->below = nullptr;
      }
      if(col == 0){
        current->prev = nullptr;
      }
      
      if(current->next != nullptr){
        current = current->next;
      }
    }
  }
}

int SparseMatrix::GetData(int row, int col){
  iNode* current = head;
  int result;
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      if(current->xPos == row && current->yPos == col){
        result = current->data;
      }
      if(current->next != nullptr){current = current->next;}
    }
  }
  return result;
}

SparseMatrix SparseMatrix::transpose(){
  SparseMatrix result(numCols, numRows);

  iNode* current = head;
  int temp;

  for(int row = 0; row < numRows; row++){
    for(int col = 0; col < numCols; col++){
      if(current->xPos == row && current->yPos == col){
        temp = current->data;
        result.Insert(col, row, temp);
      }
      if(current->next != nullptr){current = current->next;}
    }
  }
  return result;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix& rhs){
  SparseMatrix result(numRows, numCols);

  iNode* current = head;
  int temp;
  
  for(int row = 0; row < numRows; row++){
    for(int col = 0; col < numCols; col++){
      if(current->xPos == row && current->yPos == col){
        temp = current->data + rhs.GetData(row, col);
        result.Insert(row, col, temp);
      }
      if(current->next != nullptr){current = current->next;}
    }
  }
  return result;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix& rhs){
  //i = numCols1/numRows2
  //j = numCols2
  //k = numRows1

  SparseMatrix result(numRows, rhs.numCols);

  iNode* current = head;
  int temp = 0;

  for(int k = 0; k < numRows; k++){
    temp = 0;
    for(int j = 0; j < rhs.numCols; j++){
      for(int i = 0; i < numCols; i++){
          temp += this->GetData(k, i) * rhs.GetData(i, j);
          result.Insert(k, j, temp);
      }
      temp = 0;
    }
  }
  return result;    
}

void SparseMatrix::Print(ostream &out) {
  iNode* current = head;
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      if(current->xPos == i && current->yPos == j){
        if(j == numCols-1){
          out << current->data;
        }
        else{
          out << current->data << ", ";
        }
        if(current->next != nullptr){current = current->next;}
      }
    }
  out << endl;
  }
}
