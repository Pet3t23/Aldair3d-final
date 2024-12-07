#pragma once
#include "Prerequisites.h"
#include "Component.h"

class Window;

class 
Entity {
public:

  // Destructor virtual.
  virtual
  ~Entity() = default;

  /**
   * @brief Metodo virtual puro para actualizar la entidad.
   * deltaTime El tiempo transcurrido desde la �ltima actualizacio
   n.
   */
  virtual void 
  update(float deltaTime) = 0;

	/**
   * @brief Metodo virtual puro para renderizar la entidad.
   * Window Contexto del dispositivo para operaciones graficas.
   */
  virtual void 
  render(Window& window) = 0;

  /**
   * @brief Agrega un componente a la entidad.
   * Puntero compartido al componente que se va a agregar.
   */
  template <typename T>
  void addComponent(EngineUtilities::TSharedPointer <T> component) {
      static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
      components.push_back(component.template dynamic_pointer_cast<Component>());
  }



  /**
   * @brief Obtiene un componente de la entidad.
   * Tipo T del componente que se va a obtener.
   */
  template<typename T>
  EngineUtilities::TSharedPointer<T>
      getComponent() {
      for (auto& component : components) {
          EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
          if (specificComponent) {
              return specificComponent;
          }
      }
      return EngineUtilities::TSharedPointer<T>();
  }

protected:
    bool isActive;
    int id;

    std::vector<EngineUtilities::TSharedPointer <Component>> components;
};