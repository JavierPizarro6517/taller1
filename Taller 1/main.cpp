#include <iostream>
#include "Usuario.h"
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"
#include <fstream>

void mostrarMateriales(MaterialBibliografico* biblioteca[], int cantidadLibros);
void buscarMaterialTitulo(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo);
void buscarMaterialAutor(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string autor);
MaterialBibliografico* buscarMaterialDevolver(MaterialBibliografico* materialesPrestados[], int numPrestados, std::string titulo);
MaterialBibliografico* buscarMaterialPrestar(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo);
void cargarDatos(MaterialBibliografico* biblioteca[], int& totalMateriales, Usuario* usuarios[], int& totalUsuarios, const std::string& filename);
void guardarDatos(MaterialBibliografico* biblioteca[], int totalMateriales, Usuario* usuarios[], int totalUsuarios, const std::string& filename);

int main() {
    Usuario* usuario = nullptr; 
    MaterialBibliografico* biblioteca[100] = {nullptr}; // Inicializa todos los punteros a nullptr
    Usuario* usuarios[100] = {nullptr}; // Inicializa todos los punteros a nullptr
    int cantidadLibros = 0;
    int cantidadUsuarios = 0;

    while (true) {
        int opcion;
        std::cout << std::endl;
        std::cout << "¿Qué opción desea realizar?" << std::endl;
        std::cout << "1. Agregar material" << std::endl;
        std::cout << "2. Mostrar información de los materiales" << std::endl;
        std::cout << "3. Buscar material" << std::endl;
        std::cout << "4. Prestar o devolver material" << std::endl;
        std::cout << "5. Gestión de usuarios" << std::endl;
        std::cout << "6. Guardar datos" << std::endl;
        std::cout << "7. Cargar datos" << std::endl;
        std::cout << "8. Salir" << std::endl;

        std::cin >> opcion;

        if (opcion == 1) {
            MaterialBibliografico* material = nullptr;

            if (cantidadLibros >= 100) {
                std::cout << "No se pueden agregar más materiales" << std::endl;
            } else {
                std::string tipoMaterial;
                std::cout << "¿Qué tipo de material desea agregar? (Libro/Revista)" << std::endl;
                std::cin >> tipoMaterial;

                if (tipoMaterial == "libro") {
                    std::string nombreLibro, isbn, autor, fechaPublicacion, resumen;
                    std::cout << "Ingrese el nombre del libro: ";
                    std::cin >> nombreLibro;
                    std::cout << "Ingrese el ISBN: ";
                    std::cin >> isbn;
                    std::cout << "Ingrese el autor: ";
                    std::cin >> autor;
                    std::cout << "Ingrese la fecha de publicación: ";
                    std::cin >> fechaPublicacion;
                    std::cout << "Ingrese el resumen: ";
                    std::cin >> resumen;

                    material = new Libro(nombreLibro, isbn, autor, fechaPublicacion, resumen);
                } else if (tipoMaterial == "revista") {
                    std::string nombreRevista, isbn, autor, mesPublicacion;
                    int numeroEdicion;
                    std::cout << "Ingrese el nombre de la revista: ";
                    std::cin >> nombreRevista;
                    std::cout << "Ingrese el ISBN: ";
                    std::cin >> isbn;
                    std::cout << "Ingrese el autor: ";
                    std::cin >> autor;
                    std::cout << "Ingrese el número de edición: ";
                    std::cin >> numeroEdicion;
                    std::cout << "Ingrese el mes de publicación: ";
                    std::cin >> mesPublicacion;

                    material = new Revista(nombreRevista, isbn, autor, numeroEdicion, mesPublicacion);
                } else {
                    std::cout << "Tipo de recurso no válido" << std::endl;
                }

                biblioteca[cantidadLibros] = material;
                cantidadLibros++;
                std::cout << "Se ha agregado el material exitosamente!" << std::endl;
            }
        } else if (opcion == 2) {
            std::cout << "Información de los libros en la biblioteca" << std::endl;
            mostrarMateriales(biblioteca, cantidadLibros);
        } else if (opcion == 3) {
            std::string criterio;
            std::cout << "Bajo qué criterio desea buscar material" << std::endl;
            std::cout << "Título o autor" << std::endl;
            std::cin >> criterio;

            if (criterio == "titulo") {
                std::string titulo;
                std::cout << "Ingrese el título del material que desea buscar" << std::endl;
                std::cin >> titulo;

                buscarMaterialTitulo(biblioteca, cantidadLibros, titulo);
            } else if (criterio == "autor") {
                std::string autor;
                std::cout << "Ingrese el autor del material que desea buscar" << std::endl;
                std::cin >> autor;

                buscarMaterialAutor(biblioteca, cantidadLibros, autor);
            }
        } else if (opcion == 4) {
            delete usuario; // Limpiar el usuario anterior

            std::cout << "Verifique su usuario para hacer el préstamo o devolución del material/es" << std::endl;
            std::string nombre;
            int ID;

            std::cout << "Ingrese nombre: " << std::endl;
            std::cin >> nombre;
            std::cout << "Ingrese ID: " << std::endl;
            std::cin >> ID;

            usuario = new Usuario(nombre, ID);

            std::cout << "Usuario ingresado!" << std::endl;

            std::string opcionPrestamo;
            std::cout << "¿Desea (Prestar/devolver) material?" << std::endl;
            std::cin >> opcionPrestamo;

            if (opcionPrestamo == "prestar") {
                std::string titulo;
                std::cout << "Ingrese el título del material que desea prestar" << std::endl;
                std::cin >> titulo;

                MaterialBibliografico* material = buscarMaterialPrestar(biblioteca, cantidadLibros, titulo);
                if (material == nullptr) {
                    std::cout << "No se encontró el material" << std::endl;
                } else {
                    usuario->prestarMaterial(material);
                }
            } else if (opcionPrestamo == "devolver") {
                std::string titulo;
                std::cout << "Ingrese el título del material que desea devolver" << std::endl;
                std::cin >> titulo;

                MaterialBibliografico* material = buscarMaterialDevolver(usuario->getMaterialesPrestados(), usuario->getNumPrestados(), titulo);
                if (material != nullptr) {
                    usuario->devolverMaterial(material);
                } else {
                    std::cout << "El material no pudo ser devuelto. No se encontró en los materiales prestados." << std::endl;
                }
            }
        } else if (opcion == 5) {
            // Aquí puedes implementar la gestión de usuarios si es necesario
            std::cout << "Gestión de usuarios aún no implementada." << std::endl;
        } else if (opcion == 6) {
            std::string filename;
            std::cout << "Ingrese el nombre del archivo para guardar los datos: ";
            std::cin >> filename;
            guardarDatos(biblioteca, cantidadLibros, usuarios, cantidadUsuarios, filename);
        } else if (opcion == 7) {
            std::string filename;
            std::cout << "Ingrese el nombre del archivo para cargar los datos: ";
            std::cin >> filename;
            cargarDatos(biblioteca, cantidadLibros, usuarios, cantidadUsuarios, filename);
        } else if (opcion == 8) {
            std::cout << "Saliendo del menú..." << std::endl;
            break;
        } else {
            std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    }

    delete usuario; // Limpiar el último usuario creado 

    for (int i = 0; i < cantidadLibros; i++) { // Limpiar la biblioteca
        delete biblioteca[i];
    }

    for (int i = 0; i < cantidadUsuarios; i++) { // Limpiar los usuarios
        delete usuarios[i];
    }

    return 0;
}

void mostrarMateriales(MaterialBibliografico* biblioteca[], int cantidadLibros) {
    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i] != nullptr) { // Verifica que el puntero no sea nulo
            biblioteca[i]->mostrarInformacion(); // Llama al método para mostrar información del material
        }
    }
}

void buscarMaterialTitulo(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo) {
    bool encontrado = false; 

    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i] != nullptr && biblioteca[i]->getTitulo() == titulo) {
            encontrado = true;

            if (Libro* libro = dynamic_cast<Libro*>(biblioteca[i])) {
                libro->mostrarInformacion();
            } else if (Revista* revista = dynamic_cast<Revista*>(biblioteca[i])) {
                revista->mostrarInformacion();
            }
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró el material con el título: " << titulo << std::endl;
    }
}

void buscarMaterialAutor(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string autor) {
    bool encontrado = false;

    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i] != nullptr && biblioteca[i]->getAutor() == autor) {
            encontrado = true;

            if (Libro* libro = dynamic_cast<Libro*>(biblioteca[i])) {
                libro->mostrarInformacion();
            } else if (Revista* revista = dynamic_cast<Revista*>(biblioteca[i])) {
                revista->mostrarInformacion();
            }
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ningún material del autor: " << autor << std::endl;
    }
}

MaterialBibliografico* buscarMaterialDevolver(MaterialBibliografico* materialesPrestados[], int numPrestados, std::string titulo) {
    for (int i = 0; i < numPrestados; i++) {
        if (materialesPrestados[i]->getTitulo() == titulo) {
            return materialesPrestados[i];
        }
    }
    return nullptr;
}

MaterialBibliografico* buscarMaterialPrestar(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo) {
    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i] != nullptr && biblioteca[i]->getTitulo() == titulo) {
            return biblioteca[i];
        }
    }
    return nullptr;
}

void cargarDatos(MaterialBibliografico* biblioteca[], int& totalMateriales, Usuario* usuarios[], int& totalUsuarios, const std::string& filename) {
    std::ifstream archivo(filename);

    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string tipo;
    while (std::getline(archivo, tipo, ',')) {
        if (tipo == "Libro") {
            std::string nombre, isbn, autor, fechaPublicacion, resumen;
            std::getline(archivo, nombre, ',');
            std::getline(archivo, isbn, ',');
            std::getline(archivo, autor, ',');
            std::getline(archivo, fechaPublicacion, ',');
            std::getline(archivo, resumen);

            biblioteca[totalMateriales++] = new Libro(nombre, isbn, autor, fechaPublicacion, resumen);
        } else if (tipo == "Revista") {
            std::string nombre, isbn, autor, mesPublicacion;
            int numEdicion;
            std::getline(archivo, nombre, ',');
            std::getline(archivo, isbn, ',');
            std::getline(archivo, autor, ',');
            archivo >> numEdicion;
            archivo.ignore();  // Ignorar la coma
            std::getline(archivo, mesPublicacion);

            biblioteca[totalMateriales++] = new Revista(nombre, isbn, autor, numEdicion, mesPublicacion);
        } else if (tipo == "Usuario") {
            std::string nombreUsuario;
            int id;
            std::getline(archivo, nombreUsuario, ',');
            archivo >> id;
            archivo.ignore();  // Ignorar la coma

            Usuario* usuario = new Usuario(nombreUsuario, id);

            // Cargar materiales prestados
            for (int i = 0; i < 5; i++) {
                std::string materialPrestado;
                std::getline(archivo, materialPrestado, ',');
                if (materialPrestado != "null") {
                    // Asignar el material prestado buscando en la biblioteca
                    for (int j = 0; j < totalMateriales; j++) {
                        if (biblioteca[j]->getTitulo() == materialPrestado) {
                            usuario->prestarMaterial(biblioteca[j]);
                            break;
                        }
                    }
                }
            }
            usuarios[totalUsuarios++] = usuario;
        }

        archivo.ignore();  // Ignorar el salto de línea
    }

    archivo.close();
}

void guardarDatos(MaterialBibliografico* biblioteca[], int totalMateriales, Usuario* usuarios[], int totalUsuarios, const std::string& filename) {
    std::ofstream archivo(filename);

    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    // Guardar los materiales (Libros y Revistas)
    for (int i = 0; i < totalMateriales; i++) {
        // Verificar si es un libro o una revista
        if (Libro* libro = dynamic_cast<Libro*>(biblioteca[i])) {
            archivo << "Libro," << libro->getTitulo() << "," 
                    << libro->getISBN() << "," 
                    << libro->getAutor() << "," 
                    << libro->getFechaPublicacion() << "," 
                    << libro->getResumen() << std::endl;
        }

        if (Revista* revista = dynamic_cast<Revista*>(biblioteca[i])) {
            archivo << "Revista," << revista->getTitulo() << "," 
                    << revista->getISBN() << "," 
                    << revista->getAutor() << "," 
                    << revista->getNumeroEdicion() << "," 
                    << revista->getMesPublicacion() << std::endl;
        }
    }

    // Guardar los usuarios
    for (int i = 0; i < totalUsuarios; i++) {
        archivo << "Usuario," << usuarios[i]->getNombre() << "," << usuarios[i]->getID();
        for (int j = 0; j < 5; j++) {
            if (usuarios[i]->getMaterial(j) != nullptr) {
                archivo << "," << usuarios[i]->getMaterial(j)->getTitulo();
            } else {
                archivo << ",null";
            }
        }
        archivo << std::endl;
    }

    archivo.close();
}