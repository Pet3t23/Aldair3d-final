#pragma once
#include "MathEngine.h"

class Vector3 {
public:

    // Valores de las coordenadas x, y, z.
    float x, y, z;

    /**
     * @brief Constructor por defecto
     * Inicializa las coordenadas del los vectores desde 0
    */
    Vector3() : x(0), y(0), z(0) {}

    /**
     * @brief Constructor parametrizado.
     * Inicializa las coordenadas de los vectores de los valores dados.
    */
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Sobrecarga del operador para la suma de 2 vectores.
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Sobrecarga del operador para la resta de 2 vectores.
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Sobrecarga del operador para la multiplicaci?n de un vector por un escalar.
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Calcula la magnitud del vector.
     * La magnitud se calcula como la ra?z cuadrada de la suma de los cuadrados de sus componentes.
     * Se calcular la ra?z cuadrada a trav?s de MathEngine.h.
    */
    float magnitude() const {
        return  MathEngine::sqrt(x * x + y * y + z * z);
    }

    /**
     * @brief M?todo para normalizar el vector.
     * Devuelve un vector en la misma direcci?n pero con magnitud 1.
     * Si el vector tiene magnitud 0, devuelve un vector con componentes (0, 0).
    */
    Vector3 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector3(0, 0, 0);
        }
        return Vector3(x / mag, y / mag, z / mag);
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