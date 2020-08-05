#ifndef NODORJ_H
#define NODORJ_H

class Nodo { //COLOR 1/true: ROJO //COLOR 0/false: NEGRO
public:
  int val;
  bool color;
  Nodo *izq, *der, *padre; //Mas facil tener padre que buscarpadre cada rato

  Nodo *tio();
  Nodo *hermano();
  bool esIzq();
  void abajo(Nodo *nuevo);
  bool hijoRojo(); //Este lo uso para balancearlo

  Nodo(int val) : val(val) {
    padre = izq = der = NULL;
    color = 1;}
  };

Nodo *Nodo::tio() { //NODO TIO
	if (padre == NULL or padre->padre == NULL)
	  return NULL;

	if (padre->esIzq())
	  return padre->padre->der;
	else
	  return padre->padre->izq;
}

bool Nodo::esIzq() { return this == padre->izq; }  //Para saber si esta en la izq


Nodo *Nodo::hermano() { //NODO HERMANO
	if (padre == NULL)
	  return NULL;

	if (esIzq())
	  return padre->der;

	return padre->izq;
}

void Nodo::abajo(Nodo *nuevo) { //reemplaza el nodo y lo pone un nivel abajo
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

bool Nodo::hijoRojo() {
	return (izq != NULL and izq->color == 1) or
	       (der != NULL and der->color == 1);
}

#endif