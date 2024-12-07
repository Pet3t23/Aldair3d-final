#include "Window.h"

/**
 * Constructor de la clase Window.
 * Inicializa una ventana SFML, RenderTexture e ImGui.
 *
 * @param width Ancho de la ventana.
 * @param height Alto de la ventana.
 * @param title Título de la ventana.
 */
Window::Window(int width, int height, const std::string& title) {
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (!m_window) {
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");
    }
    else {
        MESSAGE("Window", "Window", "OK");
    }

    // Inicializar ImGui con SFML.
    ImGui::SFML::Init(*m_window);

    // Crear RenderTexture con las mismas dimensiones que la ventana.
    if (!m_renderTexture.create(width, height)) {
        ERROR("Window", "RenderTexture", "CHECK CREATION");
    }
}

/**
 * Destructor de la clase Window.
 * Libera recursos de ImGui y la ventana.
 */
Window::~Window() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);
}

/**
 * Maneja los eventos de la ventana, como el cierre y el redimensionamiento.
 */
void Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::Resized: {
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            m_view = m_window->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_window->setView(m_view);

            // Actualizar RenderTexture si la ventana cambia de tamaño.
            if (!m_renderTexture.create(width, height)) {
                ERROR("Window", "RenderTexture", "CHECK RESIZE CREATION");
            }
            break;
        }
        }
    }
}

/**
 * Limpia el contenido de la ventana y el RenderTexture.
 */
void Window::clear() {
    if (m_window) {
        m_window->clear();
    }
    else {
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
    }

    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.clear();
    }
}

/**
 * Muestra el contenido de la ventana en la pantalla.
 */
void Window::display() {
    if (m_window) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

/**
 * Verifica si la ventana está abierta.
 *
 * @return `true` si la ventana está abierta, `false` de lo contrario.
 */
bool Window::isOpen() const {
    return m_window ? m_window->isOpen() : false;
}

/**
 * Dibuja un objeto en la RenderTexture.
 *
 * @param drawable Referencia al objeto SFML a dibujar.
 */
void Window::draw(const sf::Drawable& drawable) {
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);
    }
}

/**
 * Obtiene el puntero a la ventana SFML.
 *
 * @return Puntero a la ventana SFML.
 */
sf::RenderWindow* Window::getWindow() {
    return m_window;
}

/**
 * Finaliza el renderizado en la RenderTexture.
 */
void Window::renderToTexture() {
    m_renderTexture.display();
}

/**
 * Muestra la RenderTexture en una ventana de ImGui.
 */
void Window::showInImGui() {
    const sf::Texture& texture = m_renderTexture.getTexture();
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    // Ventana de ImGui con título dinámico.
    ImGui::Begin("Renderizado Principal", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Resolución: %dx%d", texture.getSize().x, texture.getSize().y);
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture.getNativeHandle())), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

/**
 * Actualiza ImGui con el deltaTime.
 */
void Window::update() {
    deltaTime = clock.restart();
    ImGui::SFML::Update(*m_window, deltaTime);
}

/**
 * Renderiza ImGui en la ventana SFML.
 */
void Window::render() {
    ImGui::SFML::Render(*m_window);
}

/**
 * Libera los recursos asociados a la ventana.
 */
void Window::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);
}
