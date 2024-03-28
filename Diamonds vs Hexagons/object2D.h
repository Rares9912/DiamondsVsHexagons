#pragma once

#include <string>

#include "core/gpu/mesh.h"

namespace object2D
{

    Mesh* CreateSquares(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string &name, glm::vec3 bottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string &name, glm::vec3 origin, float length, glm::vec3 firstColor, glm::vec3 secondColor, bool fill = false);
    Mesh* CreateStar(const std::string &name, glm::vec3 origin, float length, glm::vec3 color, bool fill = false);
}
