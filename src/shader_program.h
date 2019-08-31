#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

/* A simple string util. */

struct string {
  char *txt;
  unsigned int len;
};

/* Shaders. */

#define NUM_SHADERS 2

enum uniforms {
  UNI_TRANSFORM,
  NUM_UNIFORMS
};

struct shader_program {
  GLuint program;
  struct string shader_buffers[NUM_SHADERS];
  GLuint shaders[NUM_SHADERS];
  GLuint uniforms[NUM_UNIFORMS];
};

extern void shader_program_init(struct shader_program *, const char *);
extern void shader_program_bind(struct shader_program *);
extern void shader_program_update(struct shader_program *, struct transform *,
                                  struct camera *);
extern void shader_program_finish(struct shader_program *);

#endif
