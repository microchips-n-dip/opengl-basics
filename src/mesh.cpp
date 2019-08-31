#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "mesh.h"

/* Initialize a mesh. */

void
mesh_init(struct mesh *mesh) {
  /* Create and bind array object. */
  glGenVertexArrays(1, &mesh->vertex_array_object);
  glBindVertexArray(mesh->vertex_array_object);
  /* Create arrays to copy buffers for OpenGL. */
  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> texcoords;
  positions.reserve(mesh->num_vertices);
  texcoords.reserve(mesh->num_vertices);
  unsigned int i;
  for (i = 0; i < mesh->num_vertices; i++) {
    positions.push_back(mesh->vertices[i].pos);
    texcoords.push_back(mesh->vertices[i].texcoord);
  }
  /* Prepare position buffers. */
  glGenBuffers(NUM_BUFFERS, mesh->vertex_array_buffers);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_array_buffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, mesh->num_vertices * sizeof(glm::vec3),
               &positions[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  /* Prepare texture coordinate buffers. */
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_array_buffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, mesh->num_vertices * sizeof(glm::vec2),
               &texcoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
  /* Unbind array object. */
  glBindVertexArray(0);
}

/* Draw a mesh. */

void
mesh_draw(struct mesh *mesh) {
  glBindVertexArray(mesh->vertex_array_object);
  glDrawArrays(GL_TRIANGLES, 0, mesh->num_vertices);
  glBindVertexArray(0);
}

/* Destroy a mesh. */

void
mesh_finish(struct mesh *mesh) {
  glDeleteVertexArrays(1, &mesh->vertex_array_object);
}

