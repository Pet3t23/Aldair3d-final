#include "BaseApp.h"

/**
 * @brief Destructor de la clase BaseApp.
 * Guarda los mensajes de notificación en un archivo de texto antes de liberar recursos.
 */
BaseApp::~BaseApp() {
    NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

/**
 * @brief Ciclo principal de la aplicación.
 * Inicializa los recursos necesarios, maneja eventos, actualiza el estado y renderiza cada cuadro.
 *
 * @return Código de retorno (0 si se ejecuta correctamente).
 */
int BaseApp::run() {
    NotificationService& notifier = NotificationService::getInstance();

    if (!initialize()) {
        notifier.addMessage(ConsolErrorType::ERROR,
            "Error en la inicialización, verifica las validaciones del método.");
        notifier.saveMessagesToFile("LogData.txt");
        ERROR("BaseApp", "run",
            "Error en la inicialización, verifica las validaciones del método.");
        return -1;
    }

    notifier.addMessage(ConsolErrorType::NORMAL,
        "Todos los programas se inicializaron correctamente.");
    m_GUI.init();

    while (m_window->isOpen()) {
        m_window->handleEvents();
        deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

/**
 * @brief Inicializa los recursos de la aplicación.
 * Configura la ventana principal, actores y texturas necesarias.
 *
 * @return `true` si la inicialización es exitosa; de lo contrario, `false`.
 */
bool BaseApp::initialize() {
    NotificationService& notifier = NotificationService::getInstance();
    ResourceManager& resourceManager = ResourceManager::getInstance();

    // Crear ventana principal
    m_window = new Window(1920, 1080, "Patas Engine");
    if (!m_window) {
        notifier.addMessage(ConsolErrorType::ERROR, "Error al crear la ventana, puntero nulo.");
        ERROR("BaseApp", "initialize", "Error al crear la ventana.");
        return false;
    }

    // Configurar waypoints
    initializeWaypoints();

    // Configurar actores
    if (!initializeActors(resourceManager, notifier)) {
        return false;
    }

    return true;
}

/**
 * @brief Actualiza el estado de la aplicación en cada cuadro.
 * Gestiona los actores y su interacción con los puntos de recorrido.
 */
void BaseApp::update() {
    m_window->update();

    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());

            if (actor->getName() == "Player") {
                updateMovement(m_window->deltaTime.asSeconds(), actor);
            }
        }
    }
}

/**
 * @brief Renderiza la ventana y los actores.
 * Dibuja cada actor, gestiona las interfaces gráficas y muestra el contenido en pantalla.
 */
void BaseApp::render() {
    NotificationService& notifier = NotificationService::getInstance();

    m_window->clear();
    for (const auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }

    m_window->renderToTexture();  // Finalizar el renderizado a la textura
    m_window->showInImGui();      // Mostrar en la interfaz gráfica (ImGui)
    m_GUI.console(notifier.getNotifications());
    m_GUI.inspector();
    m_GUI.hierarchy(m_actors);
    m_window->render();
    m_window->display();
}

/**
 * @brief Libera los recursos de la aplicación.
 * Limpia la ventana y elimina los punteros dinámicos.
 */
void BaseApp::cleanup() {
    if (m_window) {
        m_window->destroy();
        delete m_window;
        m_window = nullptr;
    }
}

/**
 * @brief Inicializa los waypoints utilizados para el movimiento de los actores.
 */
void BaseApp::initializeWaypoints() {
    points[0] = Vector2(720.0f, 350.0f);
    points[1] = Vector2(720.0f, 260.0f);
    points[2] = Vector2(125.0f, 50.0f);
    points[3] = Vector2(70.0f, 120.0f);
    points[4] = Vector2(70.0f, 450.0f);
    points[5] = Vector2(400.0f, 350.0f);
    points[6] = Vector2(550.0f, 500.0f);
    points[7] = Vector2(650.0f, 550.0f);
    points[8] = Vector2(720.0f, 450.0f);
}

/**
 * @brief Inicializa los actores principales (Track, Circle, Triangle).
 *
 * @param resourceManager Administrador de recursos para cargar texturas.
 * @param notifier Servicio de notificaciones para registrar errores.
 * @return `true` si todos los actores se inicializan correctamente.
 */
bool BaseApp::initializeActors(ResourceManager& resourceManager, NotificationService& notifier) {
    // Track
    if (!initializeActor("Track", ShapeType::RECTANGLE, Vector2(11.0f, 12.0f),
        "Circuit", resourceManager, notifier)) {
        return false;
    }

    // Circle
    if (!initializeActor("Player", ShapeType::CIRCLE, Vector2(1.0f, 1.0f),
        "Characters/tile000", resourceManager, notifier)) {
        return false;
    }

    // Triangle
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setTransform(Vector2(200.0f, 200.0f),
            Vector2(0.0f, 0.0f),
            Vector2(1.0f, 1.0f));
        m_actors.push_back(Triangle);
    }

    return true;
}

/**
 * @brief Configura un actor genérico con sus propiedades iniciales.
 *
 * @param name Nombre del actor.
 * @param shapeType Tipo de forma del actor.
 * @param scale Escala inicial del actor.
 * @param textureId ID de la textura en el ResourceManager.
 * @param resourceManager Administrador de recursos para cargar texturas.
 * @param notifier Servicio de notificaciones para registrar errores.
 * @return `true` si el actor se configura correctamente.
 */
bool BaseApp::initializeActor(const std::string& name, ShapeType shapeType,
    const Vector2& scale, const std::string& textureId,
    ResourceManager& resourceManager,
    NotificationService& notifier) {
    auto actor = EngineUtilities::MakeShared<Actor>(name);
    if (actor.isNull()) {
        notifier.addMessage(ConsolErrorType::ERROR,
            "Error al crear el actor: " + name);
        return false;
    }

    actor->getComponent<ShapeFactory>()->createShape(shapeType);
    actor->getComponent<Transform>()->setTransform(Vector2(0.0f, 0.0f),
        Vector2(0.0f, 0.0f),
        scale);

    if (!resourceManager.loadTexture(textureId, "png")) {
        notifier.addMessage(ConsolErrorType::ERROR,
            "Error al cargar la textura: " + textureId);
        return false;
    }

    auto texture = resourceManager.getTexture(textureId);
    if (texture) {
        actor->getComponent<ShapeFactory>()->getShape()->setTexture(&texture->getTexture());
    }

    m_actors.push_back(actor);
    return true;
}

/**
 * @brief Actualiza el movimiento de un actor siguiendo puntos de recorrido.
 *
 * @param deltaTime Tiempo de delta para sincronizar el movimiento.
 * @param circle Puntero compartido al actor que será movido.
 */
void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (!circle || circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    Vector2 targetPos = points[m_currentPoint];
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    Vector2 currentPos = transform->getPosition();
    float distanceToTarget = (targetPos - currentPos).magnitude();

    if (distanceToTarget < 10.0f) {
        m_currentPoint = (m_currentPoint + 1) % 9; // Circular traversal
    }
}
