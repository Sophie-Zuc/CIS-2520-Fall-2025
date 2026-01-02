/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 10/31/25
*/

#include "header.h"

//Node structure
struct node{

  struct node * left;
  char * contents;
  struct node * right;

};

//Function prototypes
struct node * parseString (char *, int *, struct node ***);
void printPostorder (struct node * node);
void freeNode (struct node *);

//Main functions
int main( int argc, char **argv ) {

  //Dynamic array to save pointers to memory and free it in error cases
  int size = 0;
  struct node ** saveArray = NULL;

  //Parsing the string and assigning the first node in the tree to the root
  struct node * root = parseString(argv[1], &size, &saveArray);
  //Printing the tree in postorder
  printPostorder(root);
  printf("\n");
  //Freeing memory
  freeNode(root);
  free(saveArray);

}

//Printing in postorder function definition
void printPostorder (struct node * node){

  //Base case to return if passed a null pointer
  if (node == NULL){

    return;

  }
  //Printing the left subtree and then the right subtree recursively, then the root
  printPostorder(node->left);
  printPostorder(node->right);
  printf("%s ",node->contents);

}

//Function definition to free the arithmetic tree
void freeNode (struct node * node){

  //Base case to return if passed a null pointer
  if (node == NULL){
    return;
  }
  //Recursively freeing left subtree
  if (node->left != NULL){
    freeNode(node->left);
  }
  //Recursively freeing right subtree
  if (node->right != NULL){
    freeNode(node->right);
  }
  //Freeing the root
  free(node->contents);
  free(node);

}

//Parse string function definition
struct node * parseString (char * string, int * size, struct node *** saveArray){

  int i;
  int openingCount = 0;
  int closingCount = 0;

  //Count the number of parentheses in the passed string
  for (i = 0; string[i] != '\0'; i++){

    if (string[i] == '('){
      openingCount++;
    }
    else if (string[i] == ')'){
      closingCount++;
      //If there are more closing parentheses than opening at any point, throw an error and free any memory
      if (closingCount > openingCount){
        int s;
        fprintf( stderr, "Error: syntax error.\n" );
        for (s = 0; s < *size; s++){
          free(((*saveArray)[s])->contents);
          free((*saveArray)[s]);
        }
        free(*saveArray);
        exit(EXIT_FAILURE);
      }
    }

  }

  //If there are a different number of opening and closing parentheses, throw an error and free any memory
  if (openingCount != closingCount){
        int s;
        fprintf( stderr, "Error: syntax error.\n" );
        for (s = 0; s < *size; s++){
          free(((*saveArray)[s])->contents);
          free((*saveArray)[s]);
        }
        free(*saveArray);
        exit(EXIT_FAILURE);
  }

  //Case for if the string has no brackets, a single variable or float
  if ((openingCount == 0) && (closingCount == 0)){

    //Case for if it is a variable
    if (string[0] == 'x'){

      //Throw an error if variable number isn't in range
      if (!(((int)string[1] >= 49) && ((int)string[1] <= 57))){
        //Error
        int s;
        fprintf( stderr, "Error: syntax error.\n" );
        for (s = 0; s < *size; s++){
          free(((*saveArray)[s])->contents);
          free((*saveArray)[s]);
        }
        free(*saveArray);
        exit(EXIT_FAILURE);
      }
      else {
        if (string[2] == '\0'){

          //Make a new node, make the contents the variable
          struct node * newNode = malloc(sizeof(struct node));
          newNode->contents = malloc(sizeof(char)*3);
          newNode->contents[0] = string[0];
          newNode->contents[1] = string[1];
          newNode->contents[2] = '\0';
          newNode->left = NULL;
          newNode->right = NULL;

          //Saving pointer to the node to free memory in case of error
          (*size)++;
          (*saveArray) = realloc((*saveArray),sizeof(struct node *) * (*size));
          (*saveArray)[(*size)-1] = newNode;

          return newNode;

        }
        else {
          //Error
          int s;
          fprintf( stderr, "Error: syntax error.\n" );
          for (s = 0; s < *size; s++){
            free(((*saveArray)[s])->contents);
            free((*saveArray)[s]);
          }
          free(*saveArray);
          exit(EXIT_FAILURE);
        }
      }

    }
    else if (((int)string[0] >= 48) && ((int)string[0] <= 57)){ //Case for if it is a float

      //Throw error if next character isn't a decimal point
      if (string[1] != '.'){
        //Error
        int s;
        fprintf( stderr, "Error: syntax error.\n" );
        for (s = 0; s < *size; s++){
          free(((*saveArray)[s])->contents);
          free((*saveArray)[s]);
        }
        free(*saveArray);
        exit(EXIT_FAILURE);
      }
      else {
        if (!(((int)string[2] >= 48) && ((int)string[2] <= 57))){ //Throw error if next character isn't a number
          //Error
          int s;
          fprintf( stderr, "Error: syntax error.\n" );
          for (s = 0; s < *size; s++){
            free(((*saveArray)[s])->contents);
            free((*saveArray)[s]);
          }
          free(*saveArray);
          exit(EXIT_FAILURE);
        }
        else {
          if (!(((int)string[3] >= 48) && ((int)string[3] <= 57))){ //Throw error if next character isn't a number
            //Error
            int s;
            fprintf( stderr, "Error: syntax error.\n" );
            for (s = 0; s < *size; s++){
              free(((*saveArray)[s])->contents);
              free((*saveArray)[s]);
            }
            free(*saveArray);
            exit(EXIT_FAILURE);
          }
          else {

            if (string[4] == '\0'){

              //Make a new node, make the contents the float
              struct node * newNode = malloc(sizeof(struct node));
              newNode->contents = malloc(sizeof(char)*5);
              newNode->contents[0] = string[0];
              newNode->contents[1] = string[1];
              newNode->contents[2] = string[2];
              newNode->contents[3] = string[3];
              newNode->contents[4] = '\0';
              newNode->left = NULL;
              newNode->right = NULL;

              //Saving pointer to the node to free memory in case of error
              (*size)++;
              (*saveArray) = realloc((*saveArray),sizeof(struct node *) * (*size));
              (*saveArray)[(*size)-1] = newNode;

              return newNode;

            }
            else{
              //Error
              int s;
              fprintf( stderr, "Error: syntax error.\n" );
              for (s = 0; s < *size; s++){
                free(((*saveArray)[s])->contents);
                free((*saveArray)[s]);
              }
              free(*saveArray);
              exit(EXIT_FAILURE);
            }

          }

        }

      }

    }
    else {
      //Error
      int s;
      fprintf( stderr, "Error: syntax error.\n" );
      for (s = 0; s < *size; s++){
        free(((*saveArray)[s])->contents);
        free((*saveArray)[s]);
      }
      free(*saveArray);
      exit(EXIT_FAILURE);
    }

  }
  else if ((openingCount == 1) && (closingCount == 1)) { //Case if only one pair of brackets

   int operatorIndex = -1;

    //Find operator
    for (i = 0; string[i] != '\0'; i++){

      if ((string[i] == '+') || (string[i] == '-') || (string[i] == '*') || (string[i] == '/')){

        operatorIndex = i;
        break;

      }

    }
    //Throw error if no operator
    if (operatorIndex == -1) {
      //Error
      int s;
      fprintf( stderr, "Error: syntax error.\n" );
      for (s = 0; s < *size; s++){
        free(((*saveArray)[s])->contents);
        free((*saveArray)[s]);
      }
      free(*saveArray);
      exit(EXIT_FAILURE);
    }
    else {

      int j;

      //Make new node, make the contents the operator
      struct node * newNode = malloc(sizeof(struct node));
      newNode->contents = malloc(sizeof(char)*2);
      newNode->contents[0] = string[operatorIndex];
      newNode->contents[1] = '\0';

      //Saving pointer to the node to free memory in case of error
      (*size)++;
      (*saveArray) = realloc((*saveArray),sizeof(struct node *) * (*size));
      (*saveArray)[(*size)-1] = newNode;

      //Save the contents to the left of the operator
      char leftOperand[operatorIndex];
      for (j = 0; j < operatorIndex-1; j++){
        leftOperand[j] = string[j+1];
      }
      leftOperand[operatorIndex-1] = '\0';

      //Save the contents to the right of the operator
      char rightOperand[strlen(string)-operatorIndex-1];
      for (j = 0; j < (strlen(string)-operatorIndex-2); j++){
        rightOperand[j] = string[j+operatorIndex+1];

      }
      rightOperand[strlen(string)-operatorIndex-2] = '\0';

      //Recursive calls to parse the strings to the left and right of the operator
      newNode->left = parseString(leftOperand,size,saveArray);
      newNode->right = parseString(rightOperand,size,saveArray);
      return newNode;

    }

  }
  else {
    //Call recursively for versions with nested brackets
    openingCount = 0;

    //Special case for if there's an unested operand at the beginning of the expression
    for (i = 0; string[i] != '\0'; i++){

      if (string[i] == '('){
        openingCount++;
      }

      if (((string[i] == '+') || (string[i] == '-') || (string[i] == '*') || (string[i] == '/')) && (openingCount == 1)){

        int j;

        //Make new node, make the contents the operator
        struct node * newNode = malloc(sizeof(struct node));
        newNode->contents = malloc(sizeof(char)*2);
        newNode->contents[0] = string[i];
        newNode->contents[1] = '\0';

        //Saving pointer to the node to free memory in case of error
        (*size)++;
        (*saveArray) = realloc((*saveArray),sizeof(struct node *) * (*size));
        (*saveArray)[(*size)-1] = newNode;

        //Save the contents to the left of the operator
        char leftOperand[i];
        for (j = 0; j < i-1; j++){
          leftOperand[j] = string[j+1];
        }
        leftOperand[i-1] = '\0';

        //Save the contents to the right of the operator
        char rightOperand[strlen(string)-i-1];
        for (j = 0; j < (strlen(string)-i-2); j++){
          rightOperand[j] = string[j+i+1];

        }
        rightOperand[strlen(string)-i-2] = '\0';

        //Recursive calls to parse the strings to the left and right of the operator
        newNode->left = parseString(leftOperand,size,saveArray);
        newNode->right = parseString(rightOperand,size,saveArray);
        return newNode;

      }

    }

    openingCount = 0;
    closingCount = 0;

    //Case where the first operand is a parenthesized expression
    for (i = 0; string[i] != '\0'; i++){

      //Counting parentheses
      if (string[i] == '('){
        openingCount++;
      }
      else if (string[i] == ')'){
        closingCount++;
      }

      //Finding operator location in the string
      if ((openingCount-1 == closingCount) && closingCount != 0){

        //Parse
        int j;
        int operatorIndex = i+1;

        //Make new node, make the contents the operator
        struct node * newNode = malloc(sizeof(struct node));
        newNode->contents = malloc(sizeof(char)*2);
        newNode->contents[0] = string[operatorIndex];
        newNode->contents[1] = '\0';

        //Saving pointer to the node to free memory in case of error
        (*size)++;
        (*saveArray) = realloc((*saveArray),sizeof(struct node *) * (*size));
        (*saveArray)[(*size)-1] = newNode;

        //Save the contents to the left of the operator
        char leftOperand[operatorIndex];
        for (j = 0; j < operatorIndex-1; j++){
          leftOperand[j] = string[j+1];
        }
        leftOperand[operatorIndex-1] = '\0';

        //Save the contents to the right of the operator
        char rightOperand[strlen(string)-operatorIndex-1];
        for (j = 0; j < (strlen(string)-operatorIndex-2); j++){
          rightOperand[j] = string[j+operatorIndex+1];
        }
        rightOperand[strlen(string)-operatorIndex-2] = '\0';

        //Recursive calls to parse the strings to the left and right of the operator
        newNode->left = parseString(leftOperand,size,saveArray);
        newNode->right = parseString(rightOperand,size,saveArray);
        return newNode;

      }

    }

  }

  //Error
  int s;
  fprintf( stderr, "Error: syntax error.\n" );
  for (s = 0; s < *size; s++){
    free(((*saveArray)[s])->contents);
    free((*saveArray)[s]);
  }
  free(*saveArray);
  exit(EXIT_FAILURE);

}
