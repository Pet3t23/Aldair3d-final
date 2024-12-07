#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

class
Transform : public Component {

public:

  Transform() : position(0.0f, 0.0f),
    rotation(0.0f, 0.0f),
    scale(1.0f, 1.0f),
    Component(ComponentType::TRANSFORM) {}

  virtual
  ~Transform() = default;

 /**
  * @brief Actualiza el componente de malla.
  * deltaTime El tiempo transcurrido desde la Ultima actualizaci�n.
  */
  void
  update(float deltaTime) override {}

 /**
  * @brief Renderiza el componente de malla.
  * deviceContext Contexto del dispositivo para operaciones gr�ficas.
  */
  void
  render(Window window) override {}

  // Establece la posición del objeto.
  void
  setPosition(const Vector2& _position) {
    position = _position;
  }

  // Establece la nueva rotación del objeto.
  void
  setRotation(const Vector2& _rotation) {
    rotation = _rotation;
  }

  // Establece la nueva escala del objeto.
  void
  setScale(const Vector2& _scale) {
    scale = _scale;
  }

  // Obtiene la posicion del objeto.
  Vector2
  getPosition() {
    return position;
  }

  // Devuelve una referencia a los datos de la posici�n del objeto.
  float*
  getPosData() {
    return &position.x;
  }

  // Obtiene la rotación actual del objeto.
  Vector2
  getRotation() {
    return rotation;
  }

  // Devuelve una referencia a los datos de la rotaci�n del objeto.
  float*
  getRotData() {
    return &rotation.x;
  }

  // Obtiene la escala actual del objeto.
  Vector2
  getScale() {
    return scale;
  }

  // Devuelve una referencia a los datos de la escala del objeto.
  float*
  getSclData() {
    return &scale.x;
  }

  // Metodo para establecer la posicion, rotacion y escala del objeto.
  void 
  setTransform(const Vector2& pos, const Vector2& rot, const Vector2& scl) {
  position = pos;
  rotation = rot;
  scale = scl;
  }


 /**
  * @brief Función que mueve el objeto hacia una posición objetivo con una velocidad específica.
  *
  * @param targetPosition La posición objetivo hacia la cual se mueve el objeto.
  * @param speed La velocidad de movimiento.
  * @param deltaTime El tiempo transcurrido desde la última actualización.
  * @param range La distancia mínima antes de que el movimiento hacia el objetivo se detenga.
  */
  void
  Seek(const Vector2& targetPosition,
      float speed,
      float deltaTime,
      float range) {
    Vector2 direction = (targetPosition) - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > range) {
      direction /= length;  // Normaliza el vector
      position += direction * speed * deltaTime;
    }
  }

  // Libera los recursos asociados al componente.
  void
  destroy();

private:
  Vector2 position; // Posici�n del objeto
  Vector2 rotation; // Rotaci�n del objeto
  Vector2 scale;	// Escala del objeto
};