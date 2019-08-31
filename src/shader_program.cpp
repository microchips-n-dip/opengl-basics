#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "transform.h"
#include "camera.h"
#include "shader_program.h"

static void load_shader_file(struct string *, const char *);
static GLuint create_shader(struct string, GLenum);

void
shader_program_init(struct shader_program *sp, const char *filename) {
  sp->program = glCreateProgram();
  const unsigned int len = strlen(filename);
  /* Create separate filenames. */
  char *vertex_filename = (char *) malloc(len + 3);
  char *fragment_filename = (char *) malloc(len + 3);
  *vertex_filename = '\0';
  strcat(vertex_filename, filename);
  strcat(vertex_filename, "_vs");
  *fragment_filename = '\0';
  strcat(fragment_filename, filename);
  strcat(fragment_filename, "_fs");
  /* Load the shader files. */
  load_shader_file(&sp->shader_buffers[0], vertex_filename);
  load_shader_file(&sp->shader_buffers[1], fragment_filename);
  /* Create shaders. */
  sp->shaders[0] = create_shader(sp->shader_buffers[0], GL_VERTEX_SHADER);
  sp->shaders[1] = create_shader(sp->shader_buffers[1], GL_FRAGMENT_SHADER);
  /* Attach the shaders to the program, link and validate. */
  unsigned int i;
  for (i = 0; i < NUM_SHADERS; i++)
    glAttachShader(sp->program, sp->shaders[i]);
  glBindAttribLocation(sp->program, 0, "position");
  glBindAttribLocation(sp->program, 1, "texcoord");
  glLinkProgram(sp->program);
  /* Check for errors */
  glValidateProgram(sp->program);
  /* Get our shader program's uniform variables. */
  sp->uniforms[UNI_TRANSFORM] = glGetUniformLocation(sp->program, "transform");
}

/* Load a shader file. */

static void
load_shader_file(struct string *buffer, const char *filename) {
  /* Open the file. */
  FILE *fp = fopen(filename, "r");
  if (!fp)
    std::cerr << "error: could not open " << filename << std::endl;
  /* Read the file into the buffer. */
  unsigned int size, total = 0, count;
  char *buf;
  size = 1024;
  buf = (char *) malloc(size);
  while ((count = fread(buf + total, 1, size - total, fp))) {
    total += count;
    if (total == size) {
      size += 1024;
      buf = (char *) realloc(buf, size);
    }
  }
  buffer->txt = buf;
  buffer->len = total;
}

/* Create and compile a shader. */

static GLuint
create_shader(struct string buffer, GLenum type) {
  GLuint shader = glCreateShader(type);
  if (shader == 0)
    std::cerr << "error: shader creation failed" << std::endl;
  /* Create some arrays because the way the OpenGL function takes strings is
     weird. */
  GLchar *shader_sources[1];
  GLint shader_source_lens[1];
  shader_sources[0] = buffer.txt;
  shader_source_lens[0] = buffer.len;
  glShaderSource(shader, 1, shader_sources, shader_source_lens);
  glCompileShader(shader);
  return shader;
}

/* Bind a shader program. */

void
shader_program_bind(struct shader_program *sp) {
  glUseProgram(sp->program);
}

/* Update the uniforms in a shader program. */

void
shader_program_update(struct shader_program *sp, struct transform *t,
                      struct camera *c) {
  glm::mat4 model = get_view_projection(c) * construct_model_matrix(t);
  glUniformMatrix4fv(sp->uniforms[UNI_TRANSFORM], 1, GL_FALSE, &model[0][0]);
}

/* Clean up after the shader program. */

void
shader_program_finish(struct shader_program *sp) {
  unsigned int i;
  for (i = 0; i < NUM_SHADERS; i++) {
    glDetachShader(sp->program, sp->shaders[i]);
    glDeleteShader(sp->shaders[i]);
  }
  glDeleteProgram(sp->program);
}
