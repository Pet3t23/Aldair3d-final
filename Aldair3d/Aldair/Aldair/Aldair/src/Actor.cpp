#include "Actor.h"

/**
 * @brief Constructor de la clase Actor.
 * Inicializa el nombre del actor y configura sus componentes básicos como
 * la forma (ShapeFactory) y la transformación (Transform).
 *
 * @param actorName Nombre del actor.
 */
Actor::Actor(std::string actorName)
    : m_name(std::move(actorName)) { // Inicialización directa del nombre

    // Crear y agregar componente de forma (ShapeFactory)
    auto shapeComponent = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shapeComponent);

    // Crear y agregar componente de transformación (Transform)
    auto transformComponent = EngineUtilities::MakeShared<Transform>();
    addComponent(transformComponent);
}

/**
 * @brief Actualiza el estado del actor.
 * Sincroniza la posición, rotación y escala del componente ShapeFactory
 * con los valores del componente Transform.
 *
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void Actor::update(float deltaTime) {
    // Obtener componentes necesarios
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    // Si ambos componentes están disponibles, sincronizar valores
    if (transform && shape) {
        shape->setPosition(Vector2(transform->getPosition().x, transform->getPosition().y));
        shape->setRotation(transform->getRotation().x);
        shape->setScale(Vector2(transform->getScale().x, transform->getScale().y));
    }
}

/**
 * @brief Renderiza el actor en la ventana.
 * Si existe un componente ShapeFactory, lo dibuja en la ventana proporcionada.
 *
 * @param window Referencia a la ventana donde se dibujará el actor.
 */
void Actor::render(Window& window) {
    for (const auto& component : components) {
        auto shape = component.dynamic_pointer_cast<ShapeFactory>();
        if (shape) {
            window.draw(*shape->getShape());
        }
    }
}

/**
 * @brief Método para liberar recursos del actor.
 * Actualmente está vacío, pero puede ser extendido para realizar limpieza.
 */
void Actor::destroy() {
    // Implementación futura si es necesario.
}

/**
 * @brief Obtiene el nombre actual del actor.
 *
 * @return Nombre del actor.
 */
std::string Actor::getName() const {
    return m_name;
}

/**
 * @brief Establece un nuevo nombre para el actor.
 *
 * @param newName Nuevo nombre a asignar.
 */
void Actor::setName(const std::string& newName) {
    m_name = newName;
}
