#include "GUI.h"
#include "Window.h"
#include "imgui_internal.h"

// ----------------------------------------------------
// ** INICIALIZACIÓN DE LA GUI **
// ----------------------------------------------------

// Inicializa la GUI estableciendo el estilo de la interfaz.
void GUI::init() {
    // Establecer el estilo de la GUI
    setupGUIStyle();
}

// ----------------------------------------------------
// ** ACTUALIZACIÓN DE LA GUI **
// ----------------------------------------------------

// Actualiza el estado de la GUI.
void GUI::update() {
    // Se pueden agregar actualizaciones aquí en el futuro si es necesario.
}

// ----------------------------------------------------
// ** RENDERIZADO DE LA GUI **
// ----------------------------------------------------

// Renderiza la GUI en la ventana.
void GUI::render() {
    // Implementar el renderizado de la interfaz gráfica.
}

// ----------------------------------------------------
// ** DESTRUCCIÓN DE LA GUI **
// ----------------------------------------------------

// Libera los recursos y destruye la GUI.
void GUI::destroy() {
    // Limpiar y liberar recursos aquí si es necesario.
}

// ----------------------------------------------------
// ** CONFIGURACIÓN DEL ESTILO DE LA GUI **
// ----------------------------------------------------

// Configura el estilo y los colores de la GUI mediante ImGui.
void GUI::setupGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Configuración general de los bordes y tamaños
    style.WindowRounding = 8.0f;
    style.FrameRounding = 5.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 5.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.WindowPadding = ImVec2(10, 10);

    // Configuración de los colores (estilo Mario Galaxy)
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.1f, 1.0f);       // Fondo de ventana
    colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.4f, 1.0f);        // Fondo del título
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.6f, 1.0f);  // Fondo del título activo
    colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.2f, 1.0f);        // Fondo de cuadro
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4f, 0.4f, 0.9f, 0.6f); // Fondo de cuadro al pasar el cursor
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.6f, 0.6f, 1.0f, 0.6f);  // Fondo de cuadro activo
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.5f, 1.0f);         // Color de botón
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.7f, 1.0f);  // Color de botón al pasar el cursor
    colors[ImGuiCol_ButtonActive] = ImVec4(0.4f, 0.4f, 0.8f, 1.0f);   // Color de botón activo
    colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);           // Color de texto
    colors[ImGuiCol_Border] = ImVec4(0.6f, 0.6f, 0.9f, 0.7f);         // Color del borde
    colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f);      // Color de las marcas de selección
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.6f, 1.0f, 1.0f);     // Color del deslizador
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f); // Color del deslizador activo
}

// ----------------------------------------------------
// ** CONSOLE **
// ----------------------------------------------------

// Muestra la consola con los mensajes del programa.
void GUI::console(std::map<ConsolErrorType, std::string> programMessages) {
    ImGui::Begin("Console");
    for (const auto& pair : programMessages) {
        ImGui::Text("Code: %d - Message: %s", pair.first, pair.second.c_str());
    }
    ImGui::End();
}

// ----------------------------------------------------
// ** HIERARCHY **
// ----------------------------------------------------

// Muestra la jerarquía de actores en la interfaz y permite seleccionar un actor.
void GUI::hierarchy(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    NotificationService& notifier = NotificationService::getInstance();

    ImGui::Begin("Hierarchy");

    // Iterar sobre los actores disponibles y mostrarlos en la jerarquía.
    for (int i = 0; i < actors.size(); ++i) {
        auto& actor = actors[i];
        if (actor.isNull()) continue;

        ImGui::PushID(i);
        std::string displayName = std::to_string(i) + " - " + actor->getName();
        if (ImGui::Selectable(displayName.c_str(), selectedActor == actor)) {
            selectedActor = actor;
        }
        ImGui::PopID();
    }

    ImGui::Separator();
    ImGui::Spacing();

    // Botones para crear actores
    if (ImGui::Button("Create Circle")) {
        createActor(ShapeType::CIRCLE, "Circle", 100.0f, 100.0f);
    }

    if (ImGui::Button("Create Rectangle")) {
        createActor(ShapeType::RECTANGLE, "Rectangle", 200.0f, 150.0f);
    }

    if (ImGui::Button("Create Triangle")) {
        createActor(ShapeType::TRIANGLE, "Triangle", 150.0f, 200.0f);
    }

    ImGui::End();
}

// ----------------------------------------------------
// ** INSPECTOR **
// ----------------------------------------------------

// Muestra la ventana del Inspector y permite editar atributos del actor seleccionado.
void GUI::inspector() {
    if (selectedActor.isNull()) {
        return;
    }

    ImGui::Begin("Inspector");

    // Muestra el nombre del actor y permite modificarlo
    char objectName[128];
    std::string name = selectedActor->getName();
    std::copy(name.begin(), name.end(), objectName);
    objectName[name.size()] = '\0'; // Termina con null
    if (ImGui::InputText("Name", objectName, sizeof(objectName))) {
        selectedActor->setName(std::string(objectName));
    }

    // Modificar atributos de transformación (posición, rotación, escala)
    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {
        vec2Control("Position", transform->getPosData());
        vec2Control("Rotation", transform->getRotData());
        vec2Control("Scale", transform->getSclData());
    }

    ImGui::End();
}

// ----------------------------------------------------
// ** FUNCIONES AUXILIARES **
// ----------------------------------------------------

// Crea un nuevo actor con una forma específica y lo agrega a la lista de actores.
void GUI::createActor(ShapeType shapeType, const std::string& name, float x, float y) {
    auto actor = EngineUtilities::MakeShared<Actor>(name);
    if (!actor.isNull()) {
        actor->getComponent<ShapeFactory>()->createShape(shapeType);
        actor->getComponent<Transform>()->setTransform(Vector2(x, y), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
        actors.push_back(actor);

        NotificationService::getInstance().addMessage(ConsolErrorType::NORMAL, "Actor '" + name + "' created successfully.");
    }
}

// Control de valores 2D (posición, rotación, escala) con drag floats.
void GUI::vec2Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    // Mostrar controles de valores y botones de reset
    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.ItemSpacing.y;
    bool hasValueChanged = false;

    if (ImGui::DragFloat("X", &values[0], 0.1f)) {
        hasValueChanged = true;
    }
    ImGui::SameLine();
    if (ImGui::DragFloat("Y", &values[1], 0.1f)) {
        hasValueChanged = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        values[0] = resetValue;
        values[1] = resetValue;
        hasValueChanged = true;
    }

    ImGui::Columns(1);
    ImGui::PopStyleVar();

    if (hasValueChanged) {
        NotificationService::getInstance().addMessage(ConsolErrorType::NORMAL, label + " modified.");
    }

    ImGui::PopID();
}

