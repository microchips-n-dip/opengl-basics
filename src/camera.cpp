#include "camera.h"

/* Initialize a camera. */

void
camera_init(struct camera *camera, glm::vec3 pos, float fov, float aspect,
            float z_near, float z_far) {
  camera->perspective = glm::perspective(fov, aspect, z_near, z_far);
  camera->position = pos;
  camera->forward = glm::vec3(0, 0, 1);
  camera->up = glm::vec3(0, 1, 0);
}
