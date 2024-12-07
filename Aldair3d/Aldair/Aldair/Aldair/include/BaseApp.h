#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"
#include "GUI.h"
#include "Services/NotificationSystem.h"
#include "Services/ResourceManager.h"

class
BaseApp {
public:
  BaseApp() = default;
  ~BaseApp();

  // Funcion encargada de ejecutar la aplicacion en main.
  int
  run();

  // Funcion de inicializacion.
  bool
  initialize();

  // Funcion que se actualiza por frame.
  void
  update();

  // Funcion de renderizado.
  void
  render();

  // Libera los recursos utilizados por la aplicación.
  void
  cleanup();

  /**
   * @brief Actualiza el movimiento del actor especificado.
   * Esta función gestiona el movimiento de un actor en función del
   * tiempo transcurrido.
   */
  void
  updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
  sf::Clock clock;
  sf::Time deltaTime;

  Window* m_window; // Puntero a la ventana donde se dibujan los elementos
  EngineUtilities::TSharedPointer<Actor> Triangle;
  EngineUtilities::TSharedPointer<Actor> Circle;
  EngineUtilities::TSharedPointer<Actor> Track;

  // Lista de actores en la escena
  std::vector< EngineUtilities::TSharedPointer<Actor>> m_actors;

  //Array para la actividad de los puntos
  Vector2 points[9];
  int m_currentPoint = 0;
  int m_currentActor = 0;

  // Texturas para los elementos en escena
  sf::Texture texture;
  sf::Texture Mario;

  // Interfaz grafica de usuario
  GUI m_GUI;
};