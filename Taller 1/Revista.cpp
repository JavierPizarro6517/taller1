#include "Revista.h"
#include <iostream>

Revista::Revista(std::string titulo, std::string isbn, std::string autor, int numeroEdicion, std::string mesPublicacion)
    : MaterialBibliografico(titulo, isbn, autor), numeroEdicion(numeroEdicion), mesPublicacion(mesPublicacion) {}

void Revista::mostrarInformacion() const {
    std::cout << "Revista - Titulo: " << titulo << ", Autor: " << autor << ", ISBN: " << isbn
              << ", Numero de Edicion: " << numeroEdicion << ", Mes de Publicacion: " << mesPublicacion << std::endl;
}
