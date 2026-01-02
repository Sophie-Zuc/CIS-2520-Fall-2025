/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 10/31/25
*/

#include "header.h"

//Function prototypes
void maxHeapDown(int nodeIndex, int *** heapArray);
void freeArray(int ** heapArray);

//Main function
int main( int argc, char **argv ) {

  int rowsRead = 0;
  int check = 0;
  int endCheck = 0;
  int i,j;

  //Create 2D array to store f.dat contents
  int ** heapArray = malloc(20*sizeof(int*));

  for (i = 0; i < 20; i++){

    heapArray[i] = malloc(10*sizeof(int));

  }

  //Open f.dat file
  FILE *fptr;
  fptr = fopen("f.dat", "r");

  //Throw error if file does not exist
  if (fptr == NULL) {
    fprintf( stderr, "Error opening file.\n");
    freeArray(heapArray);
    exit(EXIT_FAILURE);
  }

  //Read each row from the file into the 2D array
  while (rowsRead < 20){
    check = fscanf(fptr,"%d %d %d %d %d %d %d %d %d %d",&heapArray[rowsRead][0],&heapArray[rowsRead][1],&heapArray[rowsRead][2],&heapArray[rowsRead][3],&heapArray[rowsRead][4],&heapArray[rowsRead][5],&heapArray[rowsRead][6],&heapArray[rowsRead][7],&heapArray[rowsRead][8],&heapArray[rowsRead][9]);
    //Throw an error if any row does not contain 10 integers
    if (check < 10){
      fprintf( stderr, "Error reading file.\n");
      fclose(fptr);
      freeArray(heapArray);
      exit(EXIT_FAILURE);
    }

    rowsRead++;

  }

  //Checking and throwing an error if there are more than 20 rows in the f.dat file
  check = fscanf(fptr,"%d",&endCheck);

  if (!(check == 0) && !(check == EOF)){
    fprintf( stderr, "Error reading file.\n");
    fclose(fptr);
    freeArray(heapArray);
    exit(EXIT_FAILURE);
  }

  fclose(fptr);

  //Percolating down every non-leaf node in reverse order
  for (i = (20 - 2)/ 2; i >= 0; i--) {
    maxHeapDown(i, &heapArray);
  }

  //Printing final array
  for (i = 0; i < 20; i++){

    for (j = 0; j < 10; j++){

      //Ensuring correct two digit formatting
      if (heapArray[i][j] >= 0 && heapArray[i][j] <= 9){
        fprintf(stdout, "0%d ", heapArray[i][j]);
      }
      else {
        fprintf(stdout, "%d ", heapArray[i][j]);
      }

    }

    printf("\n");

  }

  //Free the 2D array
  freeArray(heapArray);

}

//Function definition to free 2D array
void freeArray(int ** heapArray){

  int i;

  for (i = 0; i < 20; i++){
    free(heapArray[i]);
  }

  free(heapArray);

}

//Max heap down function definition
void maxHeapDown(int nodeIndex, int *** heapArray){

  //Initializing current node index as the index of the node with the largest key
  int largestKeyIndex = nodeIndex;
  //Calculating indices for the current node's left and right children
  int leftChildIndex = 2*nodeIndex+1;
  int rightChildIndex = 2*nodeIndex+2;

  //Setting largest key index to left child if it's in range and larger than the current node's key
  if (leftChildIndex < 20 && ((*heapArray)[leftChildIndex][0] + (*heapArray)[leftChildIndex][1] + (*heapArray)[leftChildIndex][2]) > ((*heapArray)[largestKeyIndex][0] + (*heapArray)[largestKeyIndex][1] + (*heapArray)[largestKeyIndex][2])){
    largestKeyIndex = leftChildIndex;
  }

  //Setting largest key index to left child if it's in range and larger than the current largest key
  if (rightChildIndex < 20 && ((*heapArray)[rightChildIndex][0] + (*heapArray)[rightChildIndex][1] + (*heapArray)[rightChildIndex][2]) > ((*heapArray)[largestKeyIndex][0] + (*heapArray)[largestKeyIndex][1] + (*heapArray)[largestKeyIndex][2])){
    largestKeyIndex = rightChildIndex;
  }

  //If one of the children's keys was larger than the current node, swap them
  if (largestKeyIndex != nodeIndex){

    int temp[10];
    int i;

    //Loop to swap all the contents of the rows
    for (i = 0; i < 10; i++){

      temp[i] = (*heapArray)[largestKeyIndex][i];
      (*heapArray)[largestKeyIndex][i] = (*heapArray)[nodeIndex][i];
      (*heapArray)[nodeIndex][i] = temp[i];

    }

    //Recursive call after swap
    maxHeapDown(largestKeyIndex, heapArray);

  }

}
