#ifndef ARBOLRN_H
#define ARBOLRN_H

#include <iostream>
#include "nodoRJ.h"

using namespace std;

//COLOR 1: ROJO
//COLOR 0: NEGRO
//EN ESTE CODIGO USO RECURSIVIDAD; LA PROFE DIO PERMISO

class ArbolRN {
  Nodo *raiz;

  void rotaIzq(Nodo *n);
  void rotaDer(Nodo *n);
  void balance(Nodo *n);
  void arreglar(Nodo *x);
  void cambiaValor(Nodo *x, Nodo *y);
  void cambiaColor(Nodo *n1, Nodo *n2);
  void eliminarNodo(Nodo *n);
  Nodo *hijo(Nodo *m);
  Nodo *remplazo(Nodo *x);
  void inorden(Nodo *x);
  void preorden(Nodo *x);
  void posorden(Nodo *x);

  public:
  	ArbolRN() { raiz = NULL; };
  	Nodo *buscar(int n);
  	void insertar(int n);
  	void eliminar(int n);
  	void imprimir();
};

Nodo *ArbolRN::hijo(Nodo *m) { //NODO MAS IZQUIERDO
	Nodo *aux = m;

	while (aux->izq != NULL) aux = aux->izq;
	return aux;
}

void ArbolRN::rotaIzq(Nodo *n) {
	Nodo *nuevoP = n->der; // nuevoP ahora hijo derecho
	if (n == raiz)raiz = nuevoP;

	n->abajo(nuevoP); n->der = nuevoP->izq;

	if (nuevoP->izq != NULL)
	  nuevoP->izq->padre = n;

	nuevoP->izq = n;
}

void ArbolRN::rotaDer(Nodo *n) {
	Nodo *nuevoP = n->izq; // nuevoP ahora hijo izquierdo
	if (n == raiz)raiz = nuevoP;

	n->abajo(nuevoP); n->izq = nuevoP->der;

	if (nuevoP->der != NULL)
	  nuevoP->der->padre = n;

	nuevoP->der = n;
}

//Balanceamos si quedan dos rojos juntos (Regla D)
void ArbolRN::balance(Nodo *n) {
	if (n == raiz) {
	  n->color = 0;
	  return;
	}

	Nodo *padre = n->padre,
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

void ArbolRN::cambiaColor(Nodo *n1, Nodo *n2) {
	bool aux;
	aux = n1->color;
	n1->color = n2->color;
	n2->color = aux;
}

void ArbolRN::cambiaValor(Nodo *x, Nodo *y) {
	int aux;
	aux = x->val;
	x->val = y->val;
	y->val = aux;
}

//Esta funcion la creo para los diferentes casos cuando queremos eliminar
Nodo *ArbolRN::remplazo(Nodo *x) {
	if (x->izq != NULL and x->der != NULL){
	  Nodo *aux = x->der;
	  while (aux->izq != NULL){aux = aux->izq;}
	return aux;}

	if (x->izq == NULL and x->der == NULL) return NULL;

	if (x->izq != NULL) return x->izq;
	else return x->der;
}

//Creo mi propio metodo, el de pseudocodigo tenia bugs con Nulos
void ArbolRN::eliminarNodo(Nodo *n) {
	Nodo *nuevo = remplazo(n);

	//Verificamos si ambos son rojos, para arreglarlo
	bool rojos = ((nuevo == NULL or nuevo->color == 0) and (n->color == 0));
	Nodo *padre = n->padre;

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

void ArbolRN::arreglar(Nodo *x) { // Para cuando tenemos dos Negros //Perdon por tantos if :(
	if (x == raiz)
	  return;

	Nodo *hermano = x->hermano(), *padre = x->padre;

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

Nodo *ArbolRN::buscar(int n) {
	Nodo *aux = raiz;
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

void ArbolRN::insertar(int n) {
	Nodo *nuevo = new Nodo(n);
	if (raiz == NULL) {
	  nuevo->color = 0;
	  raiz = nuevo;
	} else {
	  Nodo *aux = buscar(n);

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

void ArbolRN::eliminar(int n) {//El eliminar publico (este si pide una clave)
	if (raiz == NULL)
	  return;

	Nodo *d = buscar(n);

	if (d->val != n) {
	  cout << "No existe " << n << endl;
	  return;
	}
	eliminarNodo(d);
}

void ArbolRN::imprimir() {
	if (raiz == NULL)
	  cout << "Arbol vacio" << endl;
	else
	  cout << "Inorden: ";
	  inorden(raiz); cout << endl;
	  cout << "Preorden: ";
	  preorden(raiz); cout << endl;
	  cout << "Posorden: ";
	  posorden(raiz); cout << endl;
	cout << endl;
}

void ArbolRN::inorden(Nodo *x) {
	if (x == NULL)
	  return;
	inorden(x->izq);
	cout << x->val << " ";
	inorden(x->der);
}

void ArbolRN::preorden(Nodo *x) {
	if (x == NULL)
	  return;
	cout << x->val << " ";
	preorden(x->izq);
	preorden(x->der);
}

void ArbolRN::posorden(Nodo *x) {
	if (x == NULL)
	  return;
	posorden(x->izq);
	posorden(x->der);
	cout << x->val << " ";
}

#endif