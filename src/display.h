#ifndef DISPLAY_H
#define DISPLAY_H

struct sdl {
  SDL_Window *window;
  SDL_GLContext glcontext;
};

/* Initialize SDL and set up the window. */

void
display_init(struct sdl *sdl, int width, int height) {
  SDL_Init(SDL_INIT_EVERYTHING);
  /* SDL allocate RGBA bits. */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  /* Set up dual buffering. */
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  /* Create a window. */
  sdl->window = SDL_CreateWindow("Hello, world", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height,
                                 SDL_WINDOW_OPENGL);
  /* Create an OpenGL context. */
  sdl->glcontext = SDL_GL_CreateContext(sdl->window);
  /* Initialize GLEW. */
  GLenum status = glewInit();
  if (status != GLEW_OK)
    std::cerr << "GLEW failed to initialize!" << std::endl;
}

/* Update the window. */

#define DISP_EXIT_CODE 0x01

unsigned int
display_update(struct sdl *sdl) {
  SDL_GL_SwapWindow(sdl->window);
  SDL_Event e;
  unsigned int code = 0;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT)
      code |= DISP_EXIT_CODE;
  }
  return code;
}

/* Destroy the window and quit SDL. */

void
display_finish(struct sdl *sdl) {
  /* Close everything. */
  SDL_GL_DeleteContext(sdl->glcontext);
  SDL_DestroyWindow(sdl->window);
  SDL_Quit();
}

#endif
