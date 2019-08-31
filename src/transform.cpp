#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "transform.h"

/* Initialize a transform with some values. */

void
transform_init(struct transform *t, glm::vec3 pos, glm::vec3 rot,
               glm::vec3 scale) {
  t->pos = pos;
  t->rot = rot;
  t->scale = scale;
}

/* Construct the matrix for 3-D vertex manipulation. OpenGL refers to it as the
   model matrix. */

glm::mat4
construct_model_matrix(struct transform *t) {
  glm::mat4 pos_matrix;
  glm::mat4 rot_matrix, rot_x_matrix, rot_y_matrix, rot_z_matrix;
  glm::mat4 scale_matrix;
  /* Get the position matrix. */
  pos_matrix = glm::translate(t->pos);
  /* We now need to build the rotation matrix out of the elements
     N.B. that this isn't the best way and should be done with quaternions. */
  rot_x_matrix = glm::rotate(t->rot.x, glm::vec3(1, 0, 0));
  rot_y_matrix = glm::rotate(t->rot.y, glm::vec3(0, 1, 0));
  rot_z_matrix = glm::rotate(t->rot.z, glm::vec3(0, 0, 1));
  rot_matrix = rot_z_matrix * rot_y_matrix * rot_x_matrix;
  /* Finally we can get the scale, then combine and return. */
  scale_matrix = glm::scale(t->scale);
  return pos_matrix * rot_matrix * scale_matrix;
}

void
transform_finish(struct transform *t) {
  
}
