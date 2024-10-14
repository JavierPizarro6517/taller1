#include "Libro.h"
#include <iostream>

Libro::Libro(std::string titulo, std::string isbn, std::string autor, std::string fechaPublicacion, std::string resumen)
    : MaterialBibliografico(titulo, isbn, autor), fechaPublicacion(fechaPublicacion), resumen(resumen) {}

void Libro::mostrarInformacion() const {
    std::cout << "Libro - Titulo: " << titulo << ", Autor: " << autor << ", ISBN: " << isbn
              << ", Fecha de Publicacion: " << fechaPublicacion << ", Resumen: " << resumen << std::endl;
}
