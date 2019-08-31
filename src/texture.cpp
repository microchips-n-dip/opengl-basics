#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "stb_image.h"

#include "texture.h"

/* Initialize a texture and load it into GPU memory. */

void
texture_init(struct texture *texture, const char *filename) {
  /* Load an image with STBI. */
  int width, height, num_components;
  unsigned char *image_data = stbi_load(filename, &width, &height,
                                        &num_components, 4);
  if (!image_data)
    std::cerr << "error: could not load image data" << std::endl;
  /* Allocate and bind the texture to load it into the GPU memory. */
  glGenTextures(1, &texture->texture);
  glBindTexture(GL_TEXTURE_2D, texture->texture);
  /* Set some optional texture parameters. */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  /* Pass the data to the GPU. */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image_data);
  /* Free the image data in RAM. */
  stbi_image_free(image_data);
}

/* Bind a texture for use. */

void
texture_bind(struct texture *texture, unsigned int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, texture->texture);
}

/* Clean up a texture. */

void
texture_finish(struct texture *texture) {
  glDeleteTextures(1, &texture->texture);
}
