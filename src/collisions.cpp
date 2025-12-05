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
    bool checkCollisionCuboid(glm::vec3 obj1_min, glm::vec3 obj1_max, glm::vec3 obj2_min, glm::vec3 obj2_max)
    {
        // sobreposição nos eixos X, Y e Z
        bool overlapX = (obj1_min.x <= obj2_max.x && obj1_max.x >= obj2_min.x);
        bool overlapY = (obj1_min.y <= obj2_max.y && obj1_max.y >= obj2_min.y);
        bool overlapZ = (obj1_min.z <= obj2_max.z && obj1_max.z >= obj2_min.z);

        return (overlapX && overlapY && overlapZ);
    }

    bool checkCollisionCuboidPlane(glm::vec3 obj1_min, float planeY)
    {
        return obj1_min.y <= planeY;
    }

    // FONTE: Gemini
    bool checkCollisionSphereCuboid(glm::vec3 box_min, glm::vec3 box_max, glm::vec3 sphere_center, float sphere_radius)
    {
        float closestX = std::max(box_min.x, std::min(sphere_center.x, box_max.x));
        float closestY = std::max(box_min.y, std::min(sphere_center.y, box_max.y));
        float closestZ = std::max(box_min.z, std::min(sphere_center.z, box_max.z));

        glm::vec3 closestPoint(closestX, closestY, closestZ);
        float distance = glm::distance(sphere_center, closestPoint);

        return distance < sphere_radius;
    }

    bool checkCollisionSegmentCuboid(glm::vec3 p0, glm::vec3 p1, glm::vec3 box_min, glm::vec3 box_max)
    {
        glm::vec3 dir = p1 - p0;
        glm::vec3 invDir = 1.0f / dir;

        float t1 = (box_min.x - p0.x) * invDir.x;
        float t2 = (box_max.x - p0.x) * invDir.x;

        float tmin = std::min(t1, t2);
        float tmax = std::max(t1, t2);

        float t1y = (box_min.y - p0.y) * invDir.y;
        float t2y = (box_max.y - p0.y) * invDir.y;

        tmin = std::max(tmin, std::min(t1y, t2y));
        tmax = std::min(tmax, std::max(t1y, t2y));

        float t1z = (box_min.z - p0.z) * invDir.z;
        float t2z = (box_max.z - p0.z) * invDir.z;

        tmin = std::max(tmin, std::min(t1z, t2z));
        tmax = std::min(tmax, std::max(t1z, t2z));

        if (tmax < tmin || tmin > 1.0f || tmax < 0.0f)
        {
            return false;
        }

        return true;
    }
}