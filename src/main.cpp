#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "display.h"
#include "mesh.h"
#include "transform.h"
#include "camera.h"
#include "shader_program.h"
#include "texture.h"

#define WIDTH 800
#define HEIGHT 600
#define ASPECT ((float) WIDTH / (float) HEIGHT)

int main(void) {
  /* Create the display. */
  struct sdl sdl;
  display_init(&sdl, WIDTH, HEIGHT);
  /* Create a triangle and mesh. */
  struct vertex vertices[] = {
    {glm::vec3(-0.5,  0.5, 0), glm::vec2(0.0, 0.0)},
    {glm::vec3( 0  , -0.5, 0), glm::vec2(0.5, 1.0)},
    {glm::vec3( 0.5,  0.5, 0), glm::vec2(1.0, 0.0)}
  };
  struct mesh mesh;
  mesh.vertices = vertices;
  mesh.num_vertices = 3;
  mesh_init(&mesh);
  /* Create a shader program. */
  struct shader_program sp;
  shader_program_init(&sp, "./res/basic_shader");
  /* Load a texture. */
  struct texture texture;
  texture_init(&texture, "./res/chable.jpg");
  /* Create a camera. */
  struct camera camera;
  camera_init(&camera, glm::vec3(0, 0, -3), 70.0f, ASPECT, 0.01f, 100.0f);
  /* Create a 3-D transform. */
  struct transform transform;
  float counter = 0;
  transform_init(&transform, glm::vec3(0, 0, 0), glm::vec3(0, 3.1415926, 0), glm::vec3(1, 1, 1));
  /* Run the window. */
  unsigned int status;
  while (1) {
    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader_program_bind(&sp);
    texture_bind(&texture, 0);
    float sin_counter = sinf(counter);
    float cos_counter = cosf(counter);
    transform.pos.x = sin_counter;
    transform.pos.y = sinf(counter * 20) * 0.1;
    //transform.rot.x = counter * 7;
    //transform.rot.y = counter * 10;
    //transform.rot.z = counter * 5;
    //transform.scale = glm::vec3(cos_counter, cos_counter, cos_counter);
    shader_program_update(&sp, &transform, &camera);
    mesh_draw(&mesh);
    counter += 0.01;
    status = display_update(&sdl);
    if (status & DISP_EXIT_CODE)
      goto _end;
  }
_end:
  texture_finish(&texture);
  shader_program_finish(&sp);
  mesh_finish(&mesh);
  display_finish(&sdl);
}
