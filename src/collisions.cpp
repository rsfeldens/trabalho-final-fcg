#include "collisions.h"
// Headers das bibliotecas OpenGL
#include <glad/glad.h>  // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h> // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>

namespace collisions
{
    bool checkCollisionCube(glm::vec3 obj1_min, glm::vec3 obj1_max, glm::vec3 obj2_min, glm::vec3 obj2_max)
    {
        // sobreposição nos eixos X, Y e Z
        bool overlapX = (obj1_min.x <= obj2_max.x && obj1_max.x >= obj2_min.x);
        bool overlapY = (obj1_min.y <= obj2_max.y && obj1_max.y >= obj2_min.y);
        bool overlapZ = (obj1_min.z <= obj2_max.z && obj1_max.z >= obj2_min.z);

        return (overlapX && overlapY && overlapZ);
    }

    bool checkCollisionCubePlane(glm::vec3 obj1_min, float planeY)
    {
        return obj1_min.y <= planeY;
    }

    // FONTE: Gemini
    bool checkCollisionSphereCube(glm::vec3 box_min, glm::vec3 box_max, glm::vec3 sphere_center, float sphere_radius)
    {
        float closestX = std::max(box_min.x, std::min(sphere_center.x, box_max.x));
        float closestY = std::max(box_min.y, std::min(sphere_center.y, box_max.y));
        float closestZ = std::max(box_min.z, std::min(sphere_center.z, box_max.z));

        glm::vec3 closestPoint(closestX, closestY, closestZ);
        float distance = glm::distance(sphere_center, closestPoint);

        return distance < sphere_radius;
    }
}