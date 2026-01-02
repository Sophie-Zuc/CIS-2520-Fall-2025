/*
Name: Sophie Zuccolo
Login: szuccolo
Student ID: 1293676
Date: 10/31/25
*/

#include "header.h"
#include <math.h>

//Node structure
struct node{

  struct node * left;
  char * contents;
  struct node * right;

};

//Function prototypes
struct node * parseString (char *, int *, struct node ***);
void searchInOrder (struct node * node, int * variables);
float evaluate (struct node * node, struct node ** head, float variableArray[]);
void freeNode (struct node *);

//Main functions
int main( int argc, char **argv ) {

  //Dynamic array to save pointers to memory and free it in error cases
  int size = 0;
  //Variable to indicate the presence of variables in the expression tree
  int variables = 0;
  int i;
  char whichVariable;
  float answer;
  struct node ** saveArray = NULL;

  //Array to hold the contents of each variable, will be -1 if uninitialized
  float variableArray[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

  //Parsing the string and assigning the first node in the tree to the root
  struct node * root = parseString(argv[1], &size, &saveArray);

  //Check if expression contains a variable
  searchInOrder(root,&variables);

  //Parsing second command line argument if the expression contains variables
  if (variables == 1){

    //Throw an error if there's no second argument
    if (argv[2] == NULL){
      fprintf( stderr, "Error: undefined argument.\n");
      freeNode(root);
      free(saveArray);
      exit(EXIT_FAILURE);
    }

    //Loop to go through each variable defined in the string
    for (i = 0; argv[2][i] != '\0'; i++){

      //Skip past semicolons
      if (argv[2][i] == ';'){
        i++;
      }

      //Throw error if first character not an x
      if (argv[2][i] != 'x'){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      i++;

      //Throw error if second character not a valid variable number
      if (!(((int)argv[2][i] >= 49) && ((int)argv[2][i] <= 57))){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      //Save the character of the variable number
      whichVariable = argv[2][i];
      variableArray[((int) whichVariable)-49] = 0;
      i++;

      //Throw error if third character not an equals sign
      if (argv[2][i] != '='){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      i++;

      //Throw error if fourth character not a valid number
      if (!(((int)argv[2][i] >= 48) && ((int)argv[2][i] <= 57))){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      //Add value to float
      variableArray[((int) whichVariable)-49] += (((int)argv[2][i])-48);

      i++;

      //Throw error if fifth character not a decimal point
      if (argv[2][i] != '.'){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      i++;

      //Throw error if sixth character not a valid number
      if (!(((int)argv[2][i] >= 48) && ((int)argv[2][i] <= 57))){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      //Add value to float
      variableArray[((int) whichVariable)-49] += ((float)(((int)argv[2][i])-48)/10);

      i++;

      //Throw error if seventh character not a valid number
      if (!(((int)argv[2][i] >= 48) && ((int)argv[2][i] <= 57))){
        fprintf( stderr, "Error: syntax error.\n" );
        freeNode(root);
        free(saveArray);
        exit(EXIT_FAILURE);
      }

      //Add value to float
      variableArray[((int) whichVariable)-49] += ((float)(((int)argv[2][i])-48)/100);

    }

  }

  //No errors during tree creation, free backup array
  free(saveArray);
  //Call evaluate function to evaluate the result of the expression
  answer = evaluate(root, &root, variableArray);

  //Print result with proper rounding
  printf( "%4.2f\n", round(answer*100.0)/100.0 );

  //Free the tree
  freeNode(root);

}

//Search for variables function definition
void searchInOrder (struct node * node, int * variables){

  //Base case if passed a null pointer
  if (node == NULL){

    return;

  }
  //Search recursively in left subtree
  searchInOrder(node->left, variables);
  //Search root contents for if it's a variable
  if (node->contents[0] == 'x'){
    *variables = 1;
  }
  //Search recursively in right subtree
  searchInOrder(node->right, variables);

}

//Evaluate function definition
float evaluate (struct node * node, struct node ** head, float variableArray[]){

  if (node->contents[0] == '+'){ //Case for if the node is a + operator, call recursively for left and right

    float leftOperand = evaluate(node->left,head,variableArray);
    float rightOperand = evaluate(node->right,head,variableArray);
    return leftOperand + rightOperand;

  }
  else if (node->contents[0] == '-'){ //Case for if the node is a - operator, call recursively for left and right

    float leftOperand = evaluate(node->left,head,variableArray);
    float rightOperand = evaluate(node->right,head,variableArray);
    return leftOperand - rightOperand;

  }
  else if (node->contents[0] == '*'){ //Case for if the node is a * operator, call recursively for left and right

    float leftOperand = evaluate(node->left,head,variableArray);
    float rightOperand = evaluate(node->right,head,variableArray);
    return leftOperand * rightOperand;

  }
  else if (node->contents[0] == '/'){ //Case for if the node is a / operator, call recursively for left and right

    float leftOperand = evaluate(node->left,head,variableArray);
    float rightOperand = evaluate(node->right,head,variableArray);
    //Throw error if right operand is 0, can't divide by 0
    if (rightOperand == 0){
      fprintf( stderr, "Error: division by zero.\n");
      freeNode(*head);
      exit(EXIT_FAILURE);
    }
    return leftOperand / rightOperand;

  }
  else if (node->contents[0] == 'x'){ //Case for if the node is a variable

    char whichVariable = node->contents[1];

    //Throw error if the variable is undefined
    if (variableArray[((int) whichVariable)-49] == -1){

      fprintf( stderr, "Error: undefined argument.\n");
      freeNode(*head);
      exit(EXIT_FAILURE);

    }
    else {

      //Return the value of the variable stored in the array by the parser
      return variableArray[((int) whichVariable)-49];

    }

  }
  else {

    //Case for if the node is a float, parse the value from the string
    float parsed = 0;

    parsed += ((float)(((int)(node->contents[0]))-48));
    parsed += ((float)(((int)(node->contents[2]))-48)/10);
    parsed += ((float)(((int)(node->contents[3]))-48)/100);

    return parsed;

  }

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
