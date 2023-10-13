#include <iostream>
#include <fstream>
#include <windows.h>

#include "Lista.h"
#include "Producto.hpp"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define NAMEFILE "prod_electronicos.dat"

enum OPCIONES {REGISTRAR = 1, BAJA, VERIFICAR, IMPRIMIR, SALIR};

using namespace std;

// Definicion de funciones
int menu();
void registrar(Lista<Producto>&);
void baja(Lista<Producto>&);
void verificar(Lista<Producto>&);
void imprimir(Lista<Producto>&);
void salir(Lista<Producto>&);
void Default();
void pausa();

void crearArchivo();
Lista<Producto> cargarArchivo();

int main () {
    SetConsoleOutputCP(CP_UTF8);

    // Se busca si el archivo existe, si no, lo crea.
    crearArchivo();

    // Se cargan los archivos a la lista.
    Lista<Producto> misProductos = cargarArchivo();

    int opcPrograma;
    do {
        system(CLEAR);
        switch (opcPrograma = menu()) {
            case REGISTRAR: registrar(misProductos); break;
            case BAJA: baja(misProductos); break;
            case VERIFICAR: verificar(misProductos); break;
            case IMPRIMIR: imprimir(misProductos); break;
            case SALIR: salir(misProductos); break;
            default: Default(); break;
        }
    } while (opcPrograma != 5);

    return 0;
}

// Implementacion de funciones
// Menu
int menu() {
    int opcMenu;

    cout << "Bienvenido al sistema de registro de productos electrónicos" <<endl<<endl;

    cout << "1. Registrar un nuevo producto" <<endl;
    cout << "2. Dar de baja un producto" <<endl;
    cout << "3. Verificar si un producto ya fue registrado" <<endl;
    cout << "4. Imprimir la lista de productos registrados" <<endl;
    cout << "5. Salir" <<endl<<endl;

    cout << "Elige tu opción: ";
    cin >> opcMenu;

    return opcMenu;
}

// Registrar un producto
void registrar(Lista<Producto> & lista) {
    Producto productoAIngresar;
    int claveAux;
    string nombreAux;
    float precioAux;

    bool claveEstaRepetida = true;
    system(CLEAR);
    // El bucle while sirve para revisar que la clave, no exista en la lista.
    while (claveEstaRepetida) {
        system(CLEAR);
        cout << "Ingresa clave del producto: ";
        cin >> claveAux;
        productoAIngresar.setClave(claveAux);
        if (lista.buscar(productoAIngresar) == nullptr) {
            claveEstaRepetida = false;
        }
        if (claveEstaRepetida) {
            cout << endl << "La clave del prodcuto ya esta registrada, intentalo de nuevo..."; pausa();
        }
    }    
    
    cout << "Ingresa nombre del producto: ";
    fflush(stdin);
    getline(cin, nombreAux);

    cout << "Ingrese precio: ";
    cin >> precioAux;

    productoAIngresar.setNombre(nombreAux.c_str());
    productoAIngresar.setPrecio(precioAux);

    lista.insertar(productoAIngresar);
    cout << endl << "Producto agregado existosamente."; pausa();
    lista.organizar();
}

// Dar de baja un producto.
void baja(Lista<Producto> & lista) {
    if (!lista.vacia()) {
        int claveAux;
        Producto productoABorrar;
        Nodo<Producto> * direccion;
        
        system(CLEAR);
        cout << endl << "Dame la clave del producto que quieres borrar: ";
        cin >> claveAux;
        
        productoABorrar.setClave(claveAux);
        direccion = lista.buscar(productoABorrar);

        if (direccion) {
            int opcBorrar;
            cout << endl << "Seguro que quieres borrar este producto?" <<endl;
            cout << direccion->get_dato() <<endl<<endl;

            cout << "1) Si." <<endl;
            cout << "2) No." <<endl<<endl;
            cout << "Elige tu opción: ";
            cin >> opcBorrar;

            if (opcBorrar == 1) {
                lista.eliminar(direccion);
                cout << endl << "Producto borrado exitosamente."; pausa();
                if (!lista.vacia()) {lista.organizar();}
            }
        } else {
            cout << endl << "No se encontro un producto con esa clave."; pausa();
        }
    } else {
        cout << endl << "La lista esta vacia de productos, prueba agregando un producto."; pausa();
    }
}

// Verificar si un producto esta registrado.
void verificar(Lista<Producto>& lista) {
    int claveAux;
    Producto productoABuscar;
    Nodo<Producto> * direccion;
    
    system(CLEAR);
    cout << endl << "Dame la clave del producto que quieres verificar si ya existe: ";
    cin >> claveAux;
    
    productoABuscar.setClave(claveAux);
    direccion = lista.buscar(productoABuscar);

    if (direccion) {
        cout << endl << "Producto Encontrado:" <<endl;
        cout << direccion->get_dato();
        pausa();
    } else {
        cout << endl << "No se encontro un producto con esa clave."; pausa();
    }
}

// Al salir del programa la lista guarda los datos de la lista al archivo.
void salir(Lista<Producto>& lista) {
    ofstream archivoProducto;

    // Abrimos los archivos
    archivoProducto.open(NAMEFILE, ios_base::out | ios_base::binary);
    // Revisa si los archivos se abrieron correctamente
    if (!archivoProducto.is_open()) {
        throw ios_base::failure("Error al abrir el archivo.");
    }

    // Revisa si la lista no esta vacia.
    while (!lista.vacia()) {
        Producto productoAux = lista.pri()->get_dato();
        archivoProducto.write(reinterpret_cast<char*>(&productoAux), sizeof(Producto));
        lista.eliminar(lista.pri());
    }
    // Se cierra el archivo.
    archivoProducto.close();
    cout << "Datos guardados exitosamente..." <<endl; pausa();
    // Se libera el espacio de la lista.
    lista.~Lista();
}

// Crea el archivo de los productos.
void crearArchivo() {
    // Se crean los archivos de los productos.
    ifstream archivoProductos;

    if (!ifstream(NAMEFILE)) {
        // Si no existen, crea los archivos.
        ofstream createFile(NAMEFILE);
        createFile.close();
    }
}

// Carga los productos del archivo a la lista.
Lista<Producto> cargarArchivo() {
    Lista<Producto> listaAux;
    ifstream archivoProducto;

    // Se abren los archivos
    archivoProducto.open(NAMEFILE, ios::in | ios::binary);   
    if (!archivoProducto.is_open()) {
        throw ios_base::failure("No se pudo abrir los archivos.");
    }

    // Revisa si el archivo no esta vacio.
    if (!(archivoProducto.peek() == std::ifstream::traits_type::eof())) {

        // Se cargan los datos del archivo binario
        Producto productoTemp;
        while (archivoProducto.read(reinterpret_cast<char*>(&productoTemp), sizeof(Producto))) {
                listaAux.insertar(productoTemp);
        }
    }
    archivoProducto.close();
    
    return listaAux;
}

// imprime los productos de la lista.
void imprimir(Lista<Producto>& lista) {
    system(CLEAR);
    lista.imprimir(false);
    pausa();
}

// Mustra un mensaje de error en el menu.
void Default() {
    cout << endl << "Error al escoger una opcion, intentalo de nuevo..."; pausa();
}

// Pausa del programa.
void pausa () { cin.clear(); cin.sync(); cin.ignore(); }