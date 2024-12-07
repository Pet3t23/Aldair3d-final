#include "ShapeFactory.h"

/**
 * @brief Crea una figura según el tipo especificado.
 *
 * @param shapeType El tipo de figura a crear:
 * - CIRCLE: Crea un círculo.
 * - RECTANGLE: Crea un rectángulo.
 * - TRIANGLE: Crea un triángulo (utilizando un círculo con 3 lados).
 *
 * @return Un puntero a la figura creada o nullptr si el tipo no es válido.
 */
sf::Shape* ShapeFactory::createShape(ShapeType shapeType) {
    m_ShapeType = shapeType;

    // Eliminar la figura actual si existe antes de crear una nueva.
    if (m_shape) {
        delete m_shape;
    }

    switch (shapeType) {
    case NONE:
        return nullptr;

    case CIRCLE:
        return createCircle();

    case RECTANGLE:
        return createRectangle();

    case TRIANGLE:
        return createTriangle();

    default:
        return nullptr;
    }
}

// Crea un círculo de radio 10.
sf::Shape* ShapeFactory::createCircle() {
    sf::CircleShape* circle = new sf::CircleShape(10.0f);
    m_shape = circle;
    return circle;
}

// Crea un rectángulo de tamaño 100x50.
sf::Shape* ShapeFactory::createRectangle() {
    sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
    m_shape = rectangle;
    return rectangle;
}

// Crea un triángulo utilizando un círculo con 3 lados y radio 50.
sf::Shape* ShapeFactory::createTriangle() {
    sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);  // 3 lados
    m_shape = triangle;
    return triangle;
}

// Define la posición de la figura en coordenadas (x, y).
void ShapeFactory::setPosition(float x, float y) {
    if (m_shape) {
        m_shape->setPosition(x, y);
    }
}

// Define la posición de la figura usando un vector del tipo Vector2.
void ShapeFactory::setPosition(const Vector2& position) {
    if (m_shape) {
        m_shape->setPosition(position.x, position.y);
    }
}

// Establece la rotación de la figura en grados.
void ShapeFactory::setRotation(float angle) {
    if (m_shape) {
        m_shape->setRotation(angle);
    }
}

// Establece la escala de la figura usando un vector del tipo Vector2.
void ShapeFactory::setScale(const Vector2& scl) {
    if (m_shape) {
        m_shape->setScale(scl.x, scl.y);
    }
}

// Cambia el color de relleno de la figura.
void ShapeFactory::setFillColor(const sf::Color& color) {
    if (m_shape) {
        m_shape->setFillColor(color);
    }
}

