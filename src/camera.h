#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

struct camera {
  glm::mat4 perspective;
  glm::vec3 position;
  glm::vec3 forward;
  glm::vec3 up;
};

extern void
camera_init(struct camera *, glm::vec3, float, float, float, float);

/* Compute the projection matrix from the camera properties. */

inline glm::mat4
get_view_projection(struct camera *camera) {
  glm::vec3 pos_with_fwd = camera->position + camera->forward;
  return camera->perspective * glm::lookAt(camera->position, pos_with_fwd,
                                           camera->up);
}

#endif
