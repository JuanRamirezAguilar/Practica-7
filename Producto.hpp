#ifndef PRODUCTO_HPP
#define PRODUCTO_HPP

#include <iostream>

class Producto {
    private:
        int clave;
        char nomProd[64];
        double precio;

    public:
        Producto();
        Producto(int, const char[], double);

        void setClave(int valorClave);
        void setNombre(const char* valorNombre);
        void setPrecio(double valorPrecio);

        int getClave();
        const char* getNombre();
        double getPrecio();

        double regresaPrecio();
        
        bool operator == (const Producto &comparado);
        bool operator != (const Producto &comparado);
        bool operator < (const Producto &comparado);
        bool operator > (const Producto &comparado);

        friend std::istream &operator >> (std::istream&, Producto&);
        friend std::ostream &operator << (std::ostream&, const Producto&);
};

#endif // PRODUCTO_HPP