#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"
#include "Transform.h"

class
Actor : Entity {
public:
Actor() = default;

// Constructor por defecto.
Actor(std::string actorName);

  // Destructor virtual.
  virtual
  ~Actor() = default;

  /*
  * @brief Actualiza al actor.
  * @param deltaTime El tiempo transcurrrido desde la ultima actualizacion.
  */
  void
  update(float deltaTime) override;

  /*
  * @brief Renderiza al actor
  * @param window Contexto del dispositivo para operaciones graficas.
  */
  void
  render(Window& window) override;

  // Destruye el actor y libera los recursos asociados.
  void
  destroy();

  // Funcion para obtener �nicamente el nombre del actor.
  std::string
  getName() const;

  // Permite la modificaci�n del nombre del actor.
  void
  setName(const std::string& newName);

 /**
  * @brief Obtiene un componente espec�fico del actor.
  * @tparam T Tipo del componente que se va a obtener.
  * @return Puntero compartido al componente, o nullptr si no se encuentra.
  */
  template <typename T>
  EngineUtilities::TSharedPointer<T>
  getComponent();

private:
  std::string m_name = "Actor";
};

/*
  * El proposito de esta funcion es buscar y devolver yn componente especofico de un
  * actor utilizando el tipo de componente especofico como argumentos de la plantilla.
  * Si el componente no se encuentra, la funcion devuelve nullptr.
  */
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : components) {
    EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  // Devuelve un TSharedPointer vacio si no se encuentra el componente.
  return EngineUtilities::TSharedPointer<T>();
}