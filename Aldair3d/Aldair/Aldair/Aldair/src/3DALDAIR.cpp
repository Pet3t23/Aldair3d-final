#include "BaseApp.h"
#include <SFML/Graphics.hpp>
#include "Window.h"

// Declaramos un puntero a la ventana globalmente si es necesario.
sf::RenderWindow* window = nullptr; // Inicialización de window

int main() {
    // Creamos una instancia de BaseApp, que probablemente maneja la lógica del ciclo de vida de la aplicación.
    BaseApp app;

    // Ejecutamos la aplicación, que puede manejar la ventana y el ciclo de actualización/renderizado.
    return app.run();
}
