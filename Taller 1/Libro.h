#ifndef LIBRO_H
#define LIBRO_H

#include "MaterialBibliografico.h"
#include <iostream>

class Libro : public MaterialBibliografico {
private:
    std::string fechaPublicacion;
    std::string resumen;

public:
    Libro(const std::string& titulo, const std::string& isbn, const std::string& autor,
          const std::string& fechaPublicacion, const std::string& resumen);

    void mostrarInformacion() const override;

    std::string getFechaPublicacion() const {
        return fechaPublicacion;
    }

    std::string getResumen() const {
        return resumen;
    }
};

#endif
