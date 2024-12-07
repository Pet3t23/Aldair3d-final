#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

class
ShapeFactory : public Component {
public:
  ShapeFactory() = default;

  virtual
  ~ShapeFactory() = default;

  // Constructor que inicializa ShapeFactory con un tipo de forma específico.
  ShapeFactory(ShapeType shapeType) :
  m_shape(nullptr), m_ShapeType(ShapeType::EMPTY), Component(ComponentType::SHAPE) {}

  sf::Shape*
  createShape(ShapeType shapeType);

 /**
  * @brief Actualiza el componente de malla.
  * @param deltaTime El tiempo transcurrido desde la ultima actualizaci�n.
  */
  void
  update(float deltaTime) override {};

  /**
   * @brief Renderiza el componente de malla.
   * @param deviceContext Contexto del dispositivo para operaciones graficas.
   */
  void
  render(Window window) override {};

  // Establece la posición de x y y.
  void
  setPosition(float x, float y);

  /**
   * @brief Obtiene la posici�n del componente
   * Establece la posición de la forma usando un vector2 
   * (de la libreria matematica).
   */
  void
  setPosition(const Vector2& position);

  // Establece el color de relleno de la forma.
  void
  setFillColor(const sf::Color& color);

  // Establece la rotación de la forma.
  void
  setRotation(float angle);

  // Establece la escala de la forma.
  void
  setScale(const Vector2& scl);

  // Obtiene un puntero a la forma actual.
  sf::Shape*
  getShape() {
    return m_shape;
  }

private:
  sf::Shape* m_shape; // Puntero a la forma gráfica creada.
  ShapeType m_ShapeType; // Tipo de forma que se está gestionando.
};