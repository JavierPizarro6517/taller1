#include <iostream>
#include "Usuario.h"
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"

void agregarUsuario(Usuario listaUsuarios[], int& cantidadUsuarios, Usuario& usuario);
void mostrarMateriales(MaterialBibliografico* biblioteca[], int cantidadLibros);
void buscarMaterialTitulo(MaterialBibliografico* biblioteca[],int cantidadLibros,std::string titulo);
void buscarMaterialAutor(MaterialBibliografico* biblioteca[], int cantidadLibros,std::string autor);
bool buscarUsuario(Usuario listaUsuarios[], int& cantidadUsuarios, Usuario& usuario);
void eliminarUsuario(Usuario listaUsuarios[],int& cantidadUsuarios,Usuario& usuario);
MaterialBibliografico* buscarMaterialDevolver(MaterialBibliografico* materialesPrestados[], int numPrestados,std::string titulo);
MaterialBibliografico* buscarMaterialPrestar(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo);

#include <iostream>
#include <string>
#include "Usuario.h"
#include "Libro.h"
#include "Revista.h"

int main() {
    Usuario listaUsuarios[100];
    MaterialBibliografico* biblioteca[100] = {nullptr}; // Inicializa todos los punteros a nullptr
    int cantidadLibros = 0;
    int cantidadUsuarios = 0;
    
    while (true) {
        int opcion;
        std::cout << std::endl;
        std::cout << "Que opcion desea realizar?" << std::endl;
        std::cout << "1. Agregar material" << std::endl;
        std::cout << "2. Mostrar informacion de los materiales" << std::endl;
        std::cout << "3. Buscar material" << std::endl;
        std::cout << "4. Prestar o devolver material" << std::endl;
        std::cout << "5. Gestion de usuarios" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cin >> opcion;

        if (opcion == 1) {
            std::cout << std::endl;
            MaterialBibliografico* material = nullptr;

            if (cantidadLibros >= 100) {
                std::cout << "No se pueden agregar más Materiales" << std::endl;
            } else {
                std::string tipoMaterial;
                std::cout << "Que tipo de material desea agregar? (Libro/Revista)" << std::endl;
                std::cin >> tipoMaterial;

                if (tipoMaterial == "libro") {
                    std::string nombreLibro, isbn, autor, fechaPublicacion, resumen;
                    std::cout << "Ingrese el nombre del libro: ";
                    std::cin >> nombreLibro;
                    std::cout << "Ingrese el ISBN: ";
                    std::cin >> isbn;
                    std::cout << "Ingrese el autor: ";
                    std::cin >> autor;
                    std::cout << "Ingrese la fecha de publicacion: ";
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
                    std::cout << "Ingrese el numero de edicion: ";
                    std::cin >> numeroEdicion;
                    std::cout << "Ingrese el mes de publicacion: ";
                    std::cin >> mesPublicacion;

                    material = new Revista(nombreRevista, isbn, autor, numeroEdicion, mesPublicacion);
                
                } else {
                    std::cout << "Tipo de recurso no valido" << std::endl;
                }

                if (material != nullptr) { // Verifica si se creó el material
                    biblioteca[cantidadLibros] = material;
                    cantidadLibros++;
                    std::cout << std::endl;
                    std::cout << "Se ha agregado el material exitosamente!" << std::endl;
                }
            }

        } else if (opcion == 2) {
            std::cout << std::endl;
            std::cout << "Informacion de los libros en la biblioteca:" << std::endl;
            mostrarMateriales(biblioteca, cantidadLibros);

        } else if (opcion == 3) {
            std::cout << std::endl;
            std::string criterio;
            std::cout << "Bajo que criterio desea buscar material?" << std::endl;
            std::cout << "Titulo o autor" << std::endl;
            std::cin >> criterio;
            
            if (criterio == "titulo") {
                std::string titulo;
                std::cout << "Ingrese el titulo del material que desea buscar" << std::endl;
                std::cin >> titulo;

                std::cout << std::endl;
                buscarMaterialTitulo(biblioteca, cantidadLibros, titulo);

            } else if (criterio == "autor") {
                std::string autor;
                std::cout << "Ingrese el autor del material que desea buscar" << std::endl;
                std::cin >> autor;

                std::cout << std::endl;
                buscarMaterialAutor(biblioteca, cantidadLibros, autor);
            }

        } else if (opcion == 4) {
            std::cout << std::endl;
            std::string nombre;
            int ID;
            std::cout << "Ingrese los datos del usuario" << std::endl;
            std::cout << "Nombre: ";
            std::cin >> nombre;
            std::cout << "ID: ";
            std::cin >> ID;

            Usuario usuario(nombre, ID);
            bool encontrado = buscarUsuario(listaUsuarios,cantidadUsuarios,usuario);



            if (encontrado) {
                std::cout<<std::endl;
                std::cout<<"Usuario encontrado!"<<std::endl;
                std::cout<<std::endl;
                std::string opcionPrestar;
                std::cout << "Que opción desea realizar (prestar/devolver) material?" << std::endl;
                std::cin >> opcionPrestar;


                if (opcionPrestar == "prestar") {
                    std::string titulo;
                    std::cout << "Ingrese el titulo del material que desea prestar" << std::endl;
                    std::cin >> titulo;

                    MaterialBibliografico* material = buscarMaterialPrestar(biblioteca, cantidadLibros, titulo);
                    if (material != nullptr) {
                        std::cout << std::endl;
                        usuario.prestarMaterial(material);
                        std::cout<<"con el titulo"<<material->getTitulo()<<std::endl;
                        
                    } else {
                        std::cout << std::endl;
                        std::cout << "No se encontro el material que desea prestar" << std::endl;
                    }
                   

                } else if (opcionPrestar == "devolver") {
                    std::string titulo;
                    std::cout << "Ingrese el título del material que desea devolver" << std::endl;
                    std::cin >> titulo;
                    std::cout << std::endl;
                    
                    MaterialBibliografico* material = buscarMaterialDevolver(usuario.getMaterialesPrestados(), usuario.getNumPrestados(), titulo);
                    std::cout<<"el titulo del material es"<<material->getTitulo()<<std::endl;

                    if(material!=nullptr){
                        if (cantidadLibros < 100) {
                            std::cout << std::endl;
                            usuario.devolverMaterial(material);
                            std::cout<<"el titulo del material es"<<material->getTitulo()<<std::endl;
                        } else {
                            std::cout << std::endl;
                            std::cout << "El material no pudo ser devuelto. BIBLIOTECA LLENA" << std::endl;
                        }
                    }
                    
                   
                }
            } else {
                std::cout << std::endl;
                std::cout << "No se ha encontrado el usuario ingresado" << std::endl;
            }

        } else if (opcion == 5) {
            std::cout << std::endl;
            std::cout << "Que accion desea realizar?" << std::endl;
            std::cout << "1. Crear usuario" << std::endl;
            std::cout << "2. Buscar usuario" << std::endl;
            std::cout << "3. Eliminar usuario" << std::endl;

            int opcion2;
            std::cin >> opcion2;
            
            std::string nombre;
            int ID;
            std::cout << std::endl;

            if (opcion2 == 1) {
                
                std::cout << "Ingrese los datos del usuario que desea agregar" << std::endl;
                std::cout << "Nombre: ";
                std::cin >> nombre;
                std::cout << "ID: ";
                std::cin >> ID;

                Usuario usuario(nombre, ID);
                agregarUsuario(listaUsuarios, cantidadUsuarios, usuario);
                std::cout << std::endl;
                std::cout << "Usuario ingresado!" << std::endl;

            } else if (opcion2 == 2) {

                std::cout << "Ingrese los datos del usuario que desea buscar" << std::endl;
                std::cout << "Nombre: ";
                std::cin >> nombre;
                std::cout << "ID: ";
                std::cin >> ID;
                Usuario usuario(nombre, ID);

                bool encontrado=buscarUsuario(listaUsuarios,cantidadUsuarios,usuario);
                std::cout << std::endl;
                if(encontrado){
                    std::cout << "El usuarios se encuentra en la lista de usuarios"<<std::endl;
                }else{
                    std::cout << "El usuario no se encuentra en la lista de usuarios"<<std::endl;
                }
            } else if (opcion2 == 3) {
                std::cout << "Nombre: ";
                std::cin >> nombre;
                std::cout << "ID: ";
                std::cin >> ID;
                Usuario usuario(nombre, ID);

                bool encontrado=buscarUsuario(listaUsuarios,cantidadUsuarios,usuario);
                std::cout << std::endl;
                if(encontrado){
                    eliminarUsuario(listaUsuarios,cantidadUsuarios,usuario);
                    std::cout<<"Se elimino el usuario correctamente"<<std::endl;
                }else{
                    std::cout<<"No se encontro el usuario indicado"<<std::endl;
                }
            }

        } else if (opcion == 6) {
            std::cout << "Saliendo del menu..." << std::endl;
            break;

        } else {
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }

    }

    // Limpiar la lista de materiales en la biblioteca antes de salir
    for (int i = 0; i < cantidadLibros; i++) {
        delete biblioteca[i];
    }

    return 0;
}

    
    




void mostrarMateriales(MaterialBibliografico* biblioteca[], int cantidadLibros){
    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i] != nullptr) { // Verifica que el puntero no sea nulo
            biblioteca[i]->mostrarInformacion(); // Llama al método para mostrar información del material
        }
    }
}

void buscarMaterialTitulo(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo) {
    bool encontrado=false; 

    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i]!=nullptr && biblioteca[i]->getTitulo()==titulo) {
            encontrado = true;

            if (biblioteca[i]->estaPrestado()) {
                std::cout<<"El material "<<titulo<<" esta prestado."<<std::endl;
            } else {
                std::cout<<"El material "<<titulo<<" esta disponible en la biblioteca."<<std::endl;
            }
            break; // Rompemos el bucle una vez encontrado
        }
    }

    if (!encontrado) {
        std::cout<<"El material con titulo "<<titulo<<" no se encuentra en la biblioteca."<<std::endl;
    }
}

void buscarMaterialAutor(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string autor) {
    bool encontrado=false; 

    for(int i=0; i<cantidadLibros; i++) {
        if(biblioteca[i]!=nullptr && biblioteca[i]->getAutor()==autor) {
            encontrado=true;

            std::cout<<"Material encontrado por el autor: "<<autor<<std::endl;
            std::cout<<"Titulo: "<<biblioteca[i]->getTitulo()<<std::endl;

            if(biblioteca[i]->estaPrestado()) {
                std::cout<<"El material '"<<biblioteca[i]->getTitulo()<<"' esta prestado."<<std::endl;
            } else {
                std::cout<<"El material '"<<biblioteca[i]->getTitulo()<<"' esta disponible en la biblioteca."<<std::endl;
            }
            break;
        }
    }

    if(!encontrado) {
        std::cout<<"No se encontro material del autor '"<<autor<<"' en la biblioteca."<<std::endl;
    }
}


MaterialBibliografico* buscarMaterialPrestar(MaterialBibliografico* biblioteca[], int cantidadLibros, std::string titulo) {
    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i] != nullptr && biblioteca[i]->getTitulo() == titulo) {
            return biblioteca[i]; // Retorna el puntero al material encontrado
        }
    }
    return nullptr; // Retorna nullptr si no se encuentra el material
}

MaterialBibliografico* buscarMaterialDevolver(MaterialBibliografico* materialesPrestados[], int numPrestados, std::string titulo) {
    for (int i = 0; i < numPrestados; i++) {
        if (materialesPrestados[i] != nullptr) {
            std::cout << "Buscando en material prestado: " << materialesPrestados[i]->getTitulo() << std::endl;
            if (materialesPrestados[i]->getTitulo() == titulo) {
                std::cout << "Material encontrado: " << titulo << std::endl;
                return materialesPrestados[i];
            }
        }
    }
    std::cout << "No se encontro el material para devolver: " << titulo << std::endl;
    return nullptr;
}


void agregarUsuario(Usuario listaUsuarios[], int& cantidadUsuarios, Usuario& usuario) {//ese int va con ref por que asi se cambia la variable de afuera de cantidadUsuarios ya que adentro hay solo una copia de la variable
                                                                                            //por ende si cambio la variable sin ref no se cambiaria la de afuera
    if (cantidadUsuarios < 100) {
        listaUsuarios[cantidadUsuarios] = usuario;
        cantidadUsuarios++;
    } else {
        std::cout << "No se pueden agregar mas usuarios. Limite alcanzado." << std::endl;
    }
}

bool buscarUsuario(Usuario listaUsuarios[], int& cantidadUsuarios, Usuario& usuario) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (listaUsuarios[i].getID() == usuario.getID()) {
            return true;
        }
    }
    return false; 
}

void eliminarUsuario(Usuario listaUsuarios[], int&cantidadUsuarios, Usuario& usuario){
    for (int i = 0; i<cantidadUsuarios; i++){
        if(listaUsuarios[i].getID()==usuario.getID()){
            for(int j=i;j<cantidadUsuarios-1;j++){
                listaUsuarios[j]=listaUsuarios[j+1];
            }
            cantidadUsuarios--;
        }
    }

   
}

/*
void cargarDatos(MaterialBibliografico* biblioteca[], int& totalMateriales, Usuario* usuarios[], int& totalUsuarios, const std::string& filename) {
    std::ifstream archivo(filename);

    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string tipo;
    while (std::getline(archivo, tipo, ',')) {
        if (tipo == "Libro") {
            // Leer atributos de un libro
            std::string nombre, isbn, autor, fechaPublicacion, resumen;
            std::getline(archivo, nombre, ',');
            std::getline(archivo, isbn, ',');
            std::getline(archivo, autor, ',');
            std::getline(archivo, fechaPublicacion, ',');
            std::getline(archivo, resumen);

            biblioteca[totalMateriales++] = new Libro(nombre, isbn, autor, fechaPublicacion, resumen);
        }
        else if (tipo == "Revista") {
            // Leer atributos de una revista
            std::string nombre, isbn, autor, mesPublicacion;
            int numEdicion;
            std::getline(archivo, nombre, ',');
            std::getline(archivo, isbn, ',');
            std::getline(archivo, autor, ',');
            archivo >> numEdicion;
            archivo.ignore();  // Ignorar la coma
            std::getline(archivo, mesPublicacion);

            biblioteca[totalMateriales++] = new Revista(nombre, isbn, autor, numEdicion, mesPublicacion);
        }
        else if (tipo == "Usuario") {
            // Leer atributos de un usuario
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
        const Libro* libro = dynamic_cast<const Libro*>(biblioteca[i]);
        if (libro) {
            archivo << "Libro," << libro->getTitulo() << "," 
                    << libro->getISBN() << "," 
                    << libro->getAutor() << "," 
                    << libro->getFechaPublicacion() << "," 
                    << libro->getResumen() << std::endl;
        }

        const Revista* revista = dynamic_cast<const Revista*>(biblioteca[i]);
        if (revista) {
            archivo << "Revista," << revista->getTitulo() << "," 
                    << revista->getISBN() << "," 
                    << revista->getAutor() << "," 
                    << revista->getNumeroEdicion() << "," 
                    << revista->getMesPublicacion() << std::endl;
        }
    }

    // Guardar los usuarios
    for (int i = 0; i < totalUsuarios; i++) {
        archivo << "Usuario," << usuarios[i]->getNombre() << "," << usuarios[i]->getId();
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
*/





