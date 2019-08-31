#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

/* 3-D triangle vertex. */

struct vertex {
  glm::vec3 pos;
  glm::vec2 texcoord;
};

/* A mesh. */

enum mesh_vab {
  POSITION_VB,
  TEXCOORD_VB,
  NUM_BUFFERS
};

struct mesh {
  struct vertex *vertices;
  unsigned int num_vertices;
  GLuint vertex_array_object;
  GLuint vertex_array_buffers[NUM_BUFFERS];
};

extern void mesh_init(struct mesh *);
extern void mesh_draw(struct mesh *);
extern void mesh_finish(struct mesh *);

#endif
