#ifndef ARBOLRN_H
#define ARBOLRN_H

#include <iostream>
#include "nodoRJ.h"

using namespace std;

//COLOR 1: ROJO
//COLOR 0: NEGRO

class ArbolRN {
  Node *raiz;

  void rotaIzq(Node *n) {
    Node *nuevoP = n->der; // nuevoP ahora hijo derecho
	if (n == raiz)raiz = nuevoP;

    n->abajo(nuevoP); n->der = nuevoP->izq;

    if (nuevoP->izq != NULL)
      nuevoP->izq->padre = n;

    nuevoP->izq = n;
  }

  void rotaDer(Node *n) {
    Node *nuevoP = n->izq; // nuevoP ahora hijo izquierdo
    if (n == raiz)raiz = nuevoP;

    n->abajo(nuevoP); n->izq = nuevoP->der;

    if (nuevoP->der != NULL)
      nuevoP->der->padre = n;

    nuevoP->der = n;
  }

  void cambiaColor(Node *n1, Node *n2) {
    bool aux;
    aux = n1->color;
    n1->color = n2->color;
    n2->color = aux;
  }

  void cambiaValor(Node *x, Node *y) {
    int aux;
    aux = x->val;
    x->val = y->val;
    y->val = aux;
  }

//Balanceamos si quedan dos rojos juntos (Regla D)
  void balance(Node *n) {
	if (n == raiz) {
      n->color = 0;
      return;
    }

    Node *padre = n->padre,
    	 *abuelo = padre->padre,
         *tio = n->tio();

    if (padre->color != 0) {
      if (tio != NULL && tio->color == 1) {
        padre->color = 0; tio->color = 0; abuelo->color = 1;
        balance(abuelo);

      }else{
        if (padre->esIzq()) {
          if (n->esIzq()) {
            cambiaColor(padre, abuelo);

          }else{
            rotaIzq(padre);
            cambiaColor(n, abuelo);
          }
          rotaDer(abuelo);

        }else{
          if (n->esIzq()) {
            rotaDer(padre);
            cambiaColor(n, abuelo);

          }else{
            cambiaColor(padre, abuelo);
          }
          rotaIzq(abuelo);
        }
      }
    }
  }

  Node *hijo(Node *m) { //NODO MAS IZQUIERDO
    Node *aux = m;

    while (aux->izq != NULL) aux = aux->izq;
    return aux;
  }

  //Esta funcion la creo para los diferentes casos cuando queremos eliminar
  Node *remplazo(Node *x) {
    if (x->izq != NULL and x->der != NULL) //CUANDO TIENE DOS HIJOS-----------TODO-------------
      return hijo(x->der);

    if (x->izq == NULL and x->der == NULL) return NULL;

    if (x->izq != NULL) return x->izq;
    else return x->der;
  }

  //Creo mi propio metodo, el de pseudocodigo tenia bugs
  void eliminarNodo(Node *n) {
    Node *nuevo = remplazo(n);

    //Verificamos si ambos son rojos, para arreglarlo
    bool rojos = ((nuevo == NULL or nuevo->color == 0) and (n->color == 0));
    Node *padre = n->padre;

    if (nuevo == NULL) {
      if (n == raiz) {raiz = NULL;}
      else
      {
        if (rojos){arreglar(n);}
        else { if (n->hermano() != NULL) n->hermano()->color = 1;}

        if (n->esIzq()) {padre->izq = NULL;}
        else {padre->der = NULL;}
      }

      delete n;
      return;
    }

    if (n->izq == NULL or n->der == NULL){
      if (n == raiz){
        n->val = nuevo->val;
        n->izq = n->der = NULL;
        delete nuevo;}
      else
      {
        if (n->esIzq()) {padre->izq = nuevo;}
        else {padre->der = nuevo;}
        delete n;

        nuevo->padre = padre;
        if (rojos) {arreglar(nuevo);}
        else {nuevo->color = 0;}
      }

      return;
    }

    cambiaValor(nuevo, n);
    eliminarNodo(nuevo);
  }

  void arreglar(Node *x) { // Para cuando tenemos dos Negros //Perdon por tantos if :(
    if (x == raiz)
      return;

    Node *hermano = x->hermano(), *padre = x->padre;

    if (hermano == NULL){
      arreglar(padre);}
    else{
      if (hermano->color == 1) {
        padre->color = 1;
        hermano->color = 0;
        if (hermano->esIzq()) {rotaDer(padre);}
        else {rotaIzq(padre);}
        arreglar(x);
		}
		else{
        if (hermano->hijoRojo()) {
          if (hermano->izq != NULL and hermano->izq->color == 1) {
            if (hermano->esIzq()) {
              hermano->izq->color = hermano->color;
              hermano->color = padre->color;
              rotaDer(padre);

			} else {
              hermano->izq->color = padre->color;
              rotaDer(hermano);
              rotaIzq(padre);

            }
          } else {
            if (hermano->esIzq()) {
              hermano->der->color = padre->color;
              rotaIzq(hermano);
              rotaDer(padre);

            } else {
              hermano->der->color = hermano->color;
              hermano->color = padre->color;
              rotaIzq(padre);

            }
          }
          padre->color = 0;
        } else {
          hermano->color = 1;
          if (padre->color == 0)
            arreglar(padre);
          else
            padre->color = 0;
        }
      }
    }
  }


  void inorden(Node *x) {
    if (x == NULL)
      return;
    inorden(x->izq);
    cout << x->val << " ";
    inorden(x->der);
  }

public:
  // constructor
  ArbolRN() { raiz = NULL; }

  Node *buscar(int n) {
    Node *aux = raiz;
    while (aux != NULL) {
      if (n < aux->val) {
        if (aux->izq == NULL)
          break;
        else
          aux = aux->izq;
      } else if (n == aux->val) {
        break;
      } else {
        if (aux->der == NULL)
          break;
        else
          aux = aux->der;
      }
    }

    return aux;
  }

  void insertar(int n) {
    Node *nuevo = new Node(n);
    if (raiz == NULL) {
      nuevo->color = 0;
      raiz = nuevo;
    } else {
      Node *aux = buscar(n);

      if (aux->val == n) {//Por si ya existe (clave unica)
        return;
      }

      nuevo->padre = aux;

      if (n < aux->val)
        aux->izq = nuevo;
      else
        aux->der = nuevo;

      balance(nuevo); //Verificamos si se daña el arbol
    }
  }

  void eliminar(int n) {//El eliminar publico (este si pide una clave)
    if (raiz == NULL)
      return;

    Node *d = buscar(n);

    if (d->val != n) {
      cout << "No existe" << endl;
      return;
    }
    eliminarNodo(d);
  }

  void imprimir() {
    cout << "Inorden: " << endl;
    if (raiz == NULL)
      cout << "Arbol vacio" << endl;
    else
      inorden(raiz);
    cout << endl;
  }

};

#endif