#pragma once
class Window;

// Tipos de componentes disponibles en el juego.
enum 
ComponentType {
	NONE = 0, 
	TRANSFORM = 1,
	SPRITE = 2,
	RENDERER = 3,
	PHYSICS = 4,
	AUDIOSOURCE = 5,
	SHAPE = 6,
	TEXTURE = 7
};

/**
 * @brief Clase base abstracta para todos los componentes del juego.
 * La clase Component define la interfaz b�sica que todos los componentes deben implementar,
 * permitiendo actualizar y renderizar el componente, as� como obtener su tipo.
 */
class 
Component {
public:

	// Constructor por defecto.
	Component() = default;
	
	// Constructor con tipo de componente.	
	Component(const ComponentType type) : m_type(type) {}

	// Destructor virtual.
	virtual
	~Component() = default;

	/**
	 * @brief Metodo virtual puro para actualizar el componente.
	 * El tiempo transcurrido desde la ultima actualizaci�n.
	 */
	virtual void
	update(float deltaTime) = 0;

	/**
	 * @brief Metodo virtual puro para renderizar el componente.
	 * Contexto del dispositivo para operaciones graficas.
	 */
	virtual void
	render(Window window) = 0;

  // Obtiene el tipo del componente.
  ComponentType 
  getType() const { return m_type; }

protected:
	ComponentType m_type; // Tipo de Componente.
};