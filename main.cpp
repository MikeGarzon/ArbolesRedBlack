/* INTEGRANTES:
    Maicol Andres Garzon Fonseca 20172020011
    Luis Felipe Corredor Espinosa 20171020056
*/

#include "ArbolRN.h"

int main() {
  ArbolRN b;

  b.insertar(50);
  b.insertar(60);
  b.insertar(18);
  b.insertar(10);
  b.insertar(25);
  b.insertar(05);
  b.insertar(75);
  b.insertar(80);
  b.insertar(19);
  b.insertar(40);
  b.insertar(100);
  b.insertar(45);
  b.insertar(13);

  b.imprimir();

  cout<<"Eliminando..."<<endl;
  b.eliminar(01); //Verificando la no existencia
  b.eliminar(12);
  b.eliminar(50);
  b.eliminar(25);
  b.eliminar(18);

  b.imprimir();

  return 0;
}
