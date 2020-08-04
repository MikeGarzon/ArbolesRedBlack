#include "ArbolRN.h"

int main() {
  ArbolRN b;

  b.insertar(7);
  b.insertar(3);
  b.insertar(18);
  b.insertar(10);
  b.insertar(22);
  b.insertar(8);
  b.insertar(11);
  b.insertar(26);
  b.insertar(2);
  b.insertar(6);
  b.insertar(13);

  b.imprimir();

  cout<<endl<<"Eliminando 18, 11, 3, 10, 22"<<endl;

  b.eliminar(18);
  b.eliminar(11);
  b.eliminar(3);
  b.eliminar(10);
  b.eliminar(22);

  b.imprimir();
  return 0;
}
