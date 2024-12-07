#pragma once
#include "Prerequisites.h"
#include "Texture.h"

class ResourceManager {
private:
    ResourceManager() = default;

    ~ResourceManager() = default;

    // Deshabilitar copia y asignación
    ResourceManager(const ResourceManager&) = delete; /**< Constructor de copia eliminado. */
    ResourceManager& operator=(const ResourceManager&) = delete; /**< Operador de asignación eliminado. */

public:
    /**
     * @brief Obtiene la instancia única del ResourceManager.
     * Referencia al Singleton ResourceManager.
     */
    static ResourceManager& getInstance() {
        static ResourceManager instance; // Instancia única del Singleton
        return instance;
    }

    /**
     * @brief Carga una textura en el administrador de recursos si no existe.
     * @param fileName Nombre del archivo de la textura.
     * @param extension Extensión del archivo de textura.
     * @return `true` si la textura ya estaba cargada o se cargó correctamente.
     */
    bool loadTexture(const std::string& fileName, const std::string& extension) {
        // Verificar si la textura ya está cargada
        if (m_textures.find(fileName) != m_textures.end()) {
            return true; // La textura ya existe
        }
        // Crear y cargar la textura
        EngineUtilities::TSharedPointer<Texture> texture = 
            EngineUtilities::MakeShared<Texture>(fileName, extension);
        m_textures[fileName] = texture; // Almacenar la textura
        return true; // Retornar éxito
    }

    /**
     * @brief Obtiene una textura por su nombre. Si no existe, se retorna una textura por defecto.
     * Un puntero compartido a la textura solicitada o a una textura por defecto.
     */
    EngineUtilities::TSharedPointer<Texture> getTexture(const std::string& fileName) {
        // Verificar si la textura existe en el mapa
        auto it = m_textures.find(fileName);
        if (it != m_textures.end()) {
            return it->second; // Devolver la textura existente
        }

        // Log de advertencia: textura no encontrada
        std::cout << "Texture not found: " << fileName << std::endl;

        // Crear y cargar una textura por defecto
        EngineUtilities::TSharedPointer<Texture> texture = 
            EngineUtilities::MakeShared<Texture>("Default", "png");
        m_textures["Default"] = texture; // Almacenar la textura por defecto
        return texture; // Devolver la textura por defecto
    }

private:
    // Almacena todas las texturas cargadas con sus nombres como claves.
    std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};
