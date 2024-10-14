#pragma once
#include "MaterialBibliografico.h"
#include <string>

class Revista: public MaterialBibliografico{
    private:
        int numeroEdicion;
        std::string mesPublicacion;

    public:
        Revista(std::string titulo, std::string isbn, std::string autor, int numeroEdicion, std::string mesPublicacion);
        void mostrarInformacion() const override;
};
