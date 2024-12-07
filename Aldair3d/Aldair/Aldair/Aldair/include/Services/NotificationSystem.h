#pragma once
#include "Prerequisites.h"

class
NotificationService {
private:
  /**
   * @brief Constructor privado para evitar instancias múltiples.
   */
  NotificationService() = default;

public:
  /**
  * @brief Accede a la instancia singleton mediante un unique_ptr.
  * @return Referencia a la instancia de NotificationService.
  */
  static
  NotificationService& getInstance() {
    static std::unique_ptr<NotificationService> instance(new NotificationService());
    return *instance;
  }

  /**
   * @brief Agrega un mensaje de notificación.
   * @param errType Tipo de error de la notificación.
   * @param message Mensaje a agregar.
   */
  void 
  addMessage(ConsolErrorType errType, const std::string& message) {
    m_programMessages[errType] = message;
  }

  /**
   * @brief Muestra todos los mensajes en consola.
   */
  void 
  showAllMessages() const {
    for (const auto& pair : m_programMessages) {
      std::cout << "Code: " << pair.first << " - Message: " << pair.second << std::endl;
    }
  }

  /**
   * @brief Obtiene un mensaje según el código de error.
   * @param errType Tipo de error del mensaje.
   */
  std::string 
  getMessage(ConsolErrorType errType) const {
    auto it = m_programMessages.find(errType);
    if (it != m_programMessages.end()) {
      return it->second;
    }
    return "Message not found";
  }

  /**
   * @brief Guarda los mensajes en un archivo.
   * @param filename Nombre del archivo donde se guardarán los mensajes.
   */
  void
  saveMessagesToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
      std::cerr << "No se pudo abrir el archivo para guardar los mensajes." << std::endl;
      return;
    }

    /**
     * @brief Para cada "m_programMessages", escribe el código de error
     * (`pair.first`) y el mensaje correspondiente (`pair.second`).
     */
    for (const auto& pair : m_programMessages) {
      file << "Code: " << pair.first << " - Message: " << pair.second << "\n";
    }

    /**
    *  @brief Tras escribir los mensajes cierra el archivo para guardarlos y liberar recursos
    */
    file.close();
    std::cout << "Mensajes guardados en el archivo: " << filename << std::endl;
  }

  /**
   * @brief Obtiene las notificaciones almacenadas.
   */
  std::map<ConsolErrorType, std::string>& getNotifications() {
    return m_programMessages;
  }

private:
  /**
   * @brief Obtiene un color para la notificación dependiendo del tipo de mensaje
   */
  ImVec4 getColorForSeverity(ConsolErrorType errorType) const {
    switch (errorType) {
    case ConsolErrorType::NORMAL:
      return ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Gris claro
    case ConsolErrorType::WARNING:
      return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Amarillo
    case ConsolErrorType::ERROR:
      return ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Rojo
    default:
      return ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Blanco
    }
  }

  // Mapa para almacenar los mensajes del progeama
  std::map<ConsolErrorType, std::string> m_programMessages;
};