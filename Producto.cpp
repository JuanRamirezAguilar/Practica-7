#include "Producto.hpp"

#include <string.h>

Producto::Producto() {}
Producto::Producto(int cla, const char nomP[], double pre) {
    clave = cla;
    strcpy(nomProd, nomP);
    precio = pre;
}

void Producto::setClave(int valorClave) {
    clave = valorClave;
}

void Producto::setNombre(const char * valorNombre) {
    strcpy(nomProd, valorNombre);
}

void Producto::setPrecio(double valorPrecio) {
    precio = valorPrecio;
}

int Producto::getClave() {
    return clave;
}

const char * Producto::getNombre() {
    return nomProd;
}

double Producto::getPrecio() {
    return precio;
}

double Producto::regresaPrecio () {
    return precio;
}

bool Producto::operator==(const Producto & comparado) {
    return clave == comparado.clave;
}

bool Producto::operator!=(const Producto & comparado) {
    return !(*this == comparado);
}

bool Producto::operator < (const Producto & comparado) {
    return clave < comparado.clave;
}

bool Producto::operator > (const Producto & comparado) {
    return !(*this < comparado);
}

std::istream &operator >> (std::istream& lee, Producto& objProducto) {
    std::cout << std::endl << std::endl << "Ingresa clave del producto: ";
    lee >> objProducto.clave;
    std::cout << std::endl << std::endl << "Ingresa nombre del producto: ";
    lee >> objProducto.nomProd;
    std::cout << std::endl << std::endl << "Ingrese precio: ";
    lee >> objProducto.precio;

    return lee;
}

std::ostream &operator << (std::ostream &escribe, const Producto &objProducto) {
    escribe << "Datos del producto:" <<std::endl;
    escribe << std::endl << "Clave: " << objProducto.clave;
    escribe << std::endl << "Nombre: " << objProducto.nomProd;
    escribe << std::endl << "Precio: " << objProducto.precio;

    return escribe;
}