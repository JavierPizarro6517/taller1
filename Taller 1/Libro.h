#pragma once
#include "MaterialBibliografico.h"
#include <string>

class Libro : public MaterialBibliografico {
private:
    std::string fechaPublicacion;
    std::string resumen;

public:
    Libro(std::string titulo, std::string isbn, std::string autor, std::string fechaPublicacion, std::string resumen);
    void mostrarInformacion() const override;
};
