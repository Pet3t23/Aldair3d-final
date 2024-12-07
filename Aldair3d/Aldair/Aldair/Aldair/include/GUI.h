#pragma once
#include "Prerequisites.h"
#include "Actor.h"
#include "Services/NotificationSystem.h"

class Window;

class
GUI {
public:

  GUI() = default;
  ~GUI() = default;

  // Inicializa la configuración y los recursos necesarios para la GUI.
  void
  init();

  // Actualiza los elementos de la GUI en cada frame.
  void
  update();

  // Renderiza la GUI en pantalla.
  void
  render();

  // Libera los recursos utilizados por la GUI.
  void
  destroy();

  // Configura el estilo visual de la interfaz de usuario.
  void
  setupGUIStyle();

 /**
  * @brief Muestra la consola de mensajes de error y advertencias.
  * La consola muestra mensajes categorizados según su tipo (error, advertencia, información),
  * proporcionando una interfaz para el seguimiento de mensajes del programa.
  */
  void
  console(std::map<ConsolErrorType, std::string> programMessages);

 /**
  * @brief Muestra un menú jerárquico de actores en la escena.
  * Permite al usuario seleccionar y visualizar los actores cargados en la aplicación.
  */
  void
  hierarchy(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

 /**
  * @brief Muestra el panel de inspector para el actor seleccionado.
  * Proporciona detalles y propiedades editables del actor actualmente seleccionado.
  */
  void
  inspector();

  // Permite manipular dos valores flotantes en la interfaz grafica.
  void
  vec2Control(const std::string& label,
      float* values,
      float resetValues = 0.0f,
      float columnWidth = 100.0f);

private:
  EngineUtilities::TSharedPointer<Actor> selectedActor;
};