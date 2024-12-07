#pragma once
#include "MathEngine.h"

class Vector2 {
public:

    // Valores de las coordenadas x y y
    float x;
    float y;

    /**
     * @brief Constructor por defecto
     * Inicializa las coordenadas del los vectores desde 0
    */
    Vector2() : x(0), y(0) {}

    /**
     * @brief Constructor parametrizado.
     * Inicializa las coordenadas de los vectores de los valores dados.
    */
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}

    // Sobrecarga del operador para la suma de 2 vectores.
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Sobrecarga del operador +=
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Sobrecarga del operador para la resta de 2 vectores.
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Sobrecarga del operador para la multiplicaci�n de 2 vectores.
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Sobrecarga del operador /
    Vector2 operator/(float scalar) const {
        if (scalar != 0) {
            return Vector2(x / scalar, y / scalar);
        }
        return Vector2(0, 0); // Manejo de división por cero, si aplica
    }

    // Sobrecarga del operador /=
    Vector2& operator/=(float scalar) {
        if (scalar != 0) {
            x /= scalar;
            y /= scalar;
        }
        else {
            // Manejo de división por cero, si aplica
            x = 0;
            y = 0;
        }
        return *this;
    }

    /**
     * @brief Calcula la magnitud del vector.
     * La magnitud se calcula como la ra�z cuadrada de la suma de los cuadrados de sus componentes.
     * Se calcular la ra�z cuadrada a trav�s de MathEngine.h.
    */
    float magnitude() const {
        return MathEngine::sqrt(x * x + y * y);
    }

    /**
     * @brief M�todo para normalizar el vector.
     * Devuelve un vector en la misma direcci�n pero con magnitud 1.
     * Si el vector tiene magnitud 0, devuelve un vector con componentes (0, 0).
    */
    Vector2 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector2(0, 0);
        }
        return Vector2(x / mag, y / mag);
    }

    // M�todo para devolver un puntero a los datos no constantes.
    float* data() {
        return &x;
    }

    // M�todo para devolver un puntero a los datos constantes.
    const float*
        data() const {
        return &x;
    }
};