#include "MaterialBibliografico.h"

MaterialBibliografico::MaterialBibliografico(std::string titulo, std::string isbn, std::string autor)
    : titulo(titulo), isbn(isbn), autor(autor), prestado(false) {}

bool MaterialBibliografico::estaPrestado() const {
    return prestado;
}

void MaterialBibliografico::prestar() {
    prestado = true;
}

void MaterialBibliografico::devolver() {
    prestado = false;
}

std::string MaterialBibliografico::getTitulo() const {
    return titulo;
}

std::string MaterialBibliografico::getAutor() const {
    return autor;
}
