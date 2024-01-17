#include <iostream> 
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "SparseMatrix.h"
#include "ArgumentManager.h"

using namespace std; 

int main(int argc, char *argv[]) {

  ArgumentManager am(argc, argv);
  ifstream fin(am.get("input"));
  ofstream fout(am.get("output"));

  //ifstream fin("input3.txt");
  //ofstream fout("output3.txt");

  
  //---intaking operation & matrix size to see if we can do it---//
  char operation;
  int numRows1, numCols1;
  int row, col, value;
  string line;
  fin >> operation;
  fin >> numRows1 >> numCols1;
  fin.ignore();
  
  
  //---creating header & internal nodes, filling non-zeros, and printing first matrix---//
  LinkedList m1Header(numRows1, numCols1);
  SparseMatrix matrix1(numRows1, numCols1);
  while(getline(fin, line)){
    if(line.length() == 0){
      break;
    }
    stringstream st(line);
    st >> row >> col >> value;
    matrix1.Insert(row, col, value);
  }
  //matrix1.Print(cout);
  //cout << endl;
  

  //---checking which operating and creating matrix 2 header & internal nodes---//
  if(operation == 'T'){
    SparseMatrix transposeMatrix = matrix1.transpose();
    transposeMatrix.Print(fout);
  }
  else if(operation == '+' || operation == '*'){
    //creating second matrix with header and internal nodes (if operation + or *)
    int numRows2, numCols2;
    fin >> numRows2 >> numCols2;
    fin.ignore();
    
    LinkedList m2Header(numRows2, numCols2);
    SparseMatrix matrix2(numRows2, numCols2);
    while(getline(fin, line)){
      if(line.length() == 0){
        break;
      }
      stringstream st(line);
      st >> row >> col >> value;
      matrix2.Insert(row, col, value);
    }
    //matrix2.Print(cout);
    //cout << endl;


    //--- make new header and internal node matrix. execute if possible. return if not.---//
    if(operation == '+' && (numRows1 != numRows2 || numCols1 != numCols2)){
      fout << "Invalid Matrix Operation" << endl;
      return 0;
    }
    else if(operation == '*' && (numCols1 != numRows2)){
      fout << "Invalid Matrix Operation" << endl;
      return 0;
    }
    else{
      //make new matrix of proper solution size before redirecting
      //for + use size of m1 or m2, for * use m1rows and m2cols
      if(operation == '+'){
        LinkedList m3Header(numRows1, numCols1);
        SparseMatrix matrix3;
        matrix3 = matrix1 + matrix2;
        matrix3.Print(fout);
      }
      else if(operation == '*'){
        LinkedList m4Header(numRows1, numCols2);
        SparseMatrix matrix4;
        matrix4 = matrix1 * matrix2;
        matrix4.Print(fout);
      }
    }
  }
  else{
    fout << "Invalid Matrix Operation" << endl;
    return 0;
  }

  return 0;
}
