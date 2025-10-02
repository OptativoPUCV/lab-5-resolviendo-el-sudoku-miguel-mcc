#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}
/*
aca verificamos si el estado del sudoku es valido en este caso que:
no se repitan numeros en las filas, columnas y subcuadros 3x3
para luego retornar 1 si es valido y 0 en caso contrario
*/
int is_valid(Node* n){
  int i, j , k, p;

  // aca revisaremos las filas
  for (i = 0 ; i < 9; i++) {
    int seen[10] = {0}; //  un arreglo para ver si ya vimos un numero
    for (j = 0 ; j < 9 ; j++){
      int val = n->sudo[i][j];
      if (val != 0) {
        if (seen[val]) {  // esto si esta repetido
          return 0;
        }
        seen[val] = 1;
      }
    }
  }

  // aca revisaremos las columnas
  for (j = 0 ; j < 9; j++) {
    int seen[10] = {0};
    for (i = 0 ; i < 9 ; i++){
      int val = n->sudo[i][j];
      if (val != 0){
        if(seen[val]){
          return 0;
        }
        seen[val] = 1;
      }
    }
  }

  // aca revisaremos los subcuadros 3x3
  for (k = 0 ; k < 3 ; k++){
    int seen[10] = {0};
    for (p = 0 ; p < 9 ; p++){
      int i = 3 * (k/3) + (p/3); // aca vemos  la fila dentro del subcuadro
      int j = 3 * (k%3) + (p%3);  // aca vemos la columna dentro del subcuadro
      int val = n->sudo[i][j];
      if (val != 0){
        if (seen[val]){
          return 0;
        }
        seen[val] = 1;
      }
    }
  }
  return 1;  // si paso todas las pruebas retornamos 1
}

/*
aca generamos los nodos adyacentes y con esto:
buscamos la primera celda vacia (0) y probamos con numeros del 1 al 9
y luego se agregan los que sean validos
*/

List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j, found=0;

    // aca buscamos en la primera celda vacia
    for (i = 0 ; i < 9 && !found; i++){
      for (j = 0 ; j < 9 && !found ; j++){
        if (n->sudo[i][j] == 0){        // aca encontramos una celda vacia
          found = 1;
          
          // aca probamos con numeros del 1 al 9
          for (int val = 1 ; val <= 9 ; val++){
            Node* new = copy(n);
            new->sudo[i][j] = val;
            if (is_valid(new)){   // aca si es valido entonces lo agregamos a la lista 
              pushBack(list, new);
            } else {
                free(new);  // y si no es valido liberamos la memoria
            }
          }
        }
      }
    }
    return list;  // aca retornamos la lista de nodos adyacentes
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}
