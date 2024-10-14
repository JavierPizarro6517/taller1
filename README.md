Pablo López Saavedra
21.518.678-4
pablo.lopez01@alumnos.ucn.cl
Paralelo C2

Javier Pizarro Fleming
21.213.249-7
javier.pizarro@alumnos.ucn.cl
Paralelo C2

El programa se iniciaría y compilaría al escribir por consola:
g++ main.cpp MaterialBibliografico.cpp Revista.cpp Libro.cpp Usuario.cpp -o programa

Para iniciar el programa habría que escribir:

./programa

En las primeras lineas del main se crean 2 arreglos de 100 posiciones, uno de ellos se dedica a guardar los materiales bibliográficos (revistas y libros), y el otro se dedica a guardar los usuarios.

revista: {nombreRevista: "RevistaModa", isbn: 665544338811, autor: , numeroEdicion: , mesPublicacion: }

libro: {nombreLibro: ElQuijote, isbn: 1234567890, autor: "MiguelDeCervantes" , fechaPublicacion: "01/01/1605", resumen: "Narra las aventuras de un hidalgo que de tanto leer novelas, termina enloqueciendo"}

usuario: {nombre: PabloPizarro, id: 2233}
