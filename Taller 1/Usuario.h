#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "MaterialBibliografico.h"

class Usuario {
private:
    std::string nombre;
    int id;
    int numPrestados;
    MaterialBibliografico* materialesPrestados[5];

public:
    Usuario();
    Usuario(std::string nombreUsuario, int id);

    void prestarMaterial(MaterialBibliografico* material);
    void devolverMaterial(MaterialBibliografico* material);

    MaterialBibliografico** getMaterialesPrestados();
    int getNumPrestados() const;
    int getID() const;

};

#endif
