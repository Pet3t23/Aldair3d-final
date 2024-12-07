#include "BaseApp.h"
#include <SFML/Graphics.hpp>
#include "Window.h"

// Declaramos un puntero a la ventana globalmente si es necesario.
sf::RenderWindow* window = nullptr; // Inicializaci�n de window

int main() {
    // Creamos una instancia de BaseApp, que probablemente maneja la l�gica del ciclo de vida de la aplicaci�n.
    BaseApp app;

    // Ejecutamos la aplicaci�n, que puede manejar la ventana y el ciclo de actualizaci�n/renderizado.
    return app.run();
}
