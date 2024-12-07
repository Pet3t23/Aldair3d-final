#pragma once
#include "Prerequisites.h"

class
Window {
public:
  Window() = default;
  Window(int width, int height, const std::string& title);
  ~Window();

  // Procesa los eventos de la ventana y actualiza el estado de esta.
  void
  handleEvents();

  // Limpia el contenido de la ventana con el color predeterminado.
  void
  clear();

  // Muestra el contenido de la ventana en la pantalla.
  void
  display();

  // Verifica si la ventana sigue abierta.
  bool
  isOpen() const;

 /**
  * @brief Dibuja un objeto que puede ser dibujado en la ventana.
  * drawable Referencia a un objeto SFML que puede ser dibujado.
  */
  void
  draw(const sf::Drawable& drawable);

 /**
  * @brief Obtiene el objeto interno SFML RenderWindow.
  * Un puntero al objeto interno SFML RenderWindow.
  */
  sf::RenderWindow*
  getWindow();

  // Funcion de inicializacion.
  void
  init();

  // Funcion que se actualiza por frame.
  void
  update();

  // Funcion de renderizado.
  void
  render();

  // Libera los recursos utilizados por la ventana.
  void
  destroy();

  // Permite renderizar los objetos gr�ficos a una textura.
  void
  renderToTexture();

  // Muestra el contenido de la ventana en ImGui.
  void
  showInImGui();

private:
  sf::RenderWindow* m_window; // Puntero al objeto `RenderWindow` de SFML.
  sf::View m_view; // Vista de la ventana para manejar la perspectiva de visualización.

public:
  sf::RenderTexture m_renderTexture; // Textura para renderizar el contenido.
  sf::Time deltaTime; // Tiempo transcurrido entre frames.
  sf::Clock clock; // Reloj para calcular el tiempo transcurrido entre frames.
};