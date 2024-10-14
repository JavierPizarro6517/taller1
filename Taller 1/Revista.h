#ifndef REVISTA_H
#define REVISTA_H

#include "MaterialBibliografico.h"
#include <iostream>

class Revista : public MaterialBibliografico {
private:
    int numeroEdicion;
    std::string mesPublicacion;

public:
    Revista(const std::string& titulo, const std::string& isbn, const std::string& autor,
            int numeroEdicion, const std::string& mesPublicacion);

    void mostrarInformacion() const override;

    int getNumeroEdicion() const {
        return numeroEdicion;
    }

    std::string getMesPublicacion() const {
        return mesPublicacion;
    }
};

#endif
