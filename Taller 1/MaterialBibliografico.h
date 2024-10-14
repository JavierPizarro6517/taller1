#ifndef MATERIALBIBLIOGRAFICO_H
#define MATERIALBIBLIOGRAFICO_H

#include <string>

class MaterialBibliografico {
protected:
    std::string titulo;
    std::string isbn;
    std::string autor;
    bool prestado;

public:
    MaterialBibliografico(std::string titulo, std::string isbn, std::string autor);
    
    virtual ~MaterialBibliografico() = default;

    bool estaPrestado() const;
    void prestar();
    void devolver();

    std::string getTitulo() const;
    std::string getAutor() const;

    virtual void mostrarInformacion() const = 0; // Método virtual puro
};

#endif
