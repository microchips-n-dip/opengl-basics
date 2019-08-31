#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct texture {
  GLuint texture;
};

extern void texture_init(struct texture *, const char *);
extern void texture_bind(struct texture *, unsigned int);
extern void texture_finish(struct texture *);

#endif
