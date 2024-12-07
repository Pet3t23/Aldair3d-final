#pragma once
#include "MathEngine.h"

class Vector4 {
public:

    // Valores de las coordenadas x, y, z y w.
    float x, y, z, w;

    /**
     * @brief Constructor por defecto
     * Inicializa las coordenadas del los vectores desde 0
    */
    Vector4() : x(0), y(0), z(0), w(0) {}

    /**
     * @brief Constructor parametrizado.
     * Inicializa las coordenadas de los vectores de los valores dados.
    */
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    // Sobrecarga del operador para la suma de 2 vectores.
    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Sobrecarga del operador para la resta de 2 vectores.
    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Sobrecarga del operador para la multiplicaci?n de un vector por un escalar
    Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    /**
     * @brief Calcula la magnitud del vector.
     * La magnitud se calcula como la ra?z cuadrada de la suma de los cuadrados de sus componentes.
     * Se calcular la ra?z cuadrada a trav?s de MathEngine.h.
    */
    float magnitude() const {
        return MathEngine::sqrt(x * x + y * y + z * z + w * w);
    }

    /**
     * @brief M?todo para normalizar el vector.
     * Devuelve un vector en la misma direcci?n pero con magnitud 1.
     * Si el vector tiene magnitud 0, devuelve un vector con componentes (0, 0).
    */
    Vector4 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector4(0, 0, 0, 0);
        }
        return Vector4(x / mag, y / mag, z / mag, w / mag);
    }

    // M?todo para devolver un puntero a los datos no constantes.
    float* data() {
        return &x;
    }

    // M?todo para devolver un puntero a los datos constantes.
    const float* data() const {
        return &x;
    }
};