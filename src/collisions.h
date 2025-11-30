#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <glad/glad.h>  // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h> // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace collisions
{
    bool checkCollisionCube(glm::vec3 obj1_min, glm::vec3 obj1_max, glm::vec3 obj2_min, glm::vec3 obj2_max);
    bool checkCollisionCubePlane(glm::vec3 obj1_min, float planeY);
    bool checkCollisionSphereCube(glm::vec3 box_min, glm::vec3 box_max, glm::vec3 sphere_center, float sphere_radius);

}

#endif // COLLISIONS_H