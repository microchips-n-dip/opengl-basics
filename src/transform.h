#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

struct transform {
  glm::vec3 pos;
  glm::vec3 rot;
  glm::vec3 scale;
};

extern void transform_init(struct transform *, glm::vec3, glm::vec3,
                           glm::vec3);
extern void transform_finish(struct transform *);

/* Construct the matrix for 3-D vertex manipulation. OpenGL refers to it as the
   model matrix. */

extern glm::mat4 construct_model_matrix(struct transform *);

#endif
