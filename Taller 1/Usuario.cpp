#include "Usuario.h"
#include <iostream>

Usuario::Usuario() : nombre(""), id(0), numPrestados(0) {
    for (int i = 0; i < 5; ++i) {
        materialesPrestados[i] = nullptr;
    }
}

Usuario::Usuario(std::string nombreUsuario, int id) : nombre(nombreUsuario), id(id), numPrestados(0) {
    for (int i = 0; i < 5; ++i) {
        materialesPrestados[i] = nullptr;
    }
}

void Usuario::prestarMaterial(MaterialBibliografico* material) {
    if (numPrestados >= 5) {
        std::cout << "Ya se ha alcanzado el limite de 5 materiales prestados." << std::endl;  
        return;     
    }
    if (material->estaPrestado()) {
        std::cout << "El material ya está prestado." << std::endl;
        return;
    }
    materialesPrestados[numPrestados++] = material;
    material->prestar();
    std::cout << "Se ha prestado el material exitosamente!" << std::endl;
}

void Usuario::devolverMaterial(MaterialBibliografico* material) {
    bool encontrado = false;

    for (int i = 0; i < numPrestados; ++i) {
        if (materialesPrestados[i] == material) {
            encontrado = true;
            material->devolver();  

            for (int j = i; j < numPrestados - 1; ++j) {
                materialesPrestados[j] = materialesPrestados[j + 1];
            }

            materialesPrestados[numPrestados - 1] = nullptr; 
            numPrestados--;

            std::cout << "El material fue devuelto correctamente!" << std::endl;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "El material no se encuentra en la lista de materiales prestados." << std::endl;
    }
}

MaterialBibliografico** Usuario::getMaterialesPrestados() {
    return materialesPrestados; 
}

int Usuario::getNumPrestados() const {
    return numPrestados;
}

int Usuario::getID() const {
    return id;
}

