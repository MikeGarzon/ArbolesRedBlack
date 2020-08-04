#ifndef NODORJ_H
#define NODORJ_H

class Node {
public:
  int val;
  bool color;
  Node *izq, *der, *padre;

  Node *tio();
  Node *hermano();
  bool esIzq();
  void abajo(Node *nuevo);
  bool hijoRojo(); //Este lo uso para balancearlo

  };

  Node(int val) : val(val) {
    padre = izq = der = NULL; //Mas facil tener padre que buscarpadre cada rato

    //COLOR 1: ROJO
    //COLOR 0: NEGRO
    color = 1;
  }

  Node *tio() { //NODO TIO

    if (padre == NULL or padre->padre == NULL)
      return NULL;

    if (padre->esIzq())
      return padre->padre->der;
    else
      return padre->padre->izq;
  }

  bool esIzq() { return this == padre->izq; }  //Para saber si esta en la izq


  Node *hermano() { //NODO HERMANO
    if (padre == NULL)
      return NULL;

    if (esIzq())
      return padre->der;

    return padre->izq;
  }

  void abajo(Node *nuevo) { //reemplaza el nodo y lo pone un nivel abajo
    if (padre != NULL) {
      if (esIzq()) {
        padre->izq = nuevo;
      } else {
        padre->der = nuevo;
      }
    }
    nuevo->padre = padre;
    padre = nuevo;
  }

  bool hijoRojo() {
    return (izq != NULL and izq->color == 1) or
           (der != NULL and der->color == 1);
  }



#endif