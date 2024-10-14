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
    MaterialBibliografico(const std::string& titulo, const std::string& isbn, const std::string& autor);
    virtual ~MaterialBibliografico() {}

    virtual void mostrarInformacion() const = 0; // Método virtual puro

    std::string getTitulo() const;
    std::string getISBN() const;
    std::string getAutor() const;
    bool estaPrestado() const;
    void prestar();
    void devolver();
};

#endif
