#include "application.hpp"

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

Application::~Application() { glDeleteProgram(main_program); }

void Application::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TIPS: Always use f after floating numbers, e.g 1.0f. This helps in avoiding glm template errors
  // Tak 5.1: Setup camera
  //           1. Choose camera position (for example 1.5f, 2.0f, -8.0f is good to see all our objects) as glm::vec3
  //           2. Create perspective matrix using glm::perspective(float field_of_view, float aspect_ratio, float near, float far);
  //              - glm works in radians by default, you can convert degrees to radians using glm::radians(degrees)
  //              - aspect_ratio is width of the window divided by height of the window
  //              - near and far planes should be: positive, near < far, near should be much smaller than 1.0f, e.g 0.01f
  //           3. Create view matrix using glm::lookAt(glm::vec3 eye_position, glm::vec3 look_at_position, glm::vec3 up_vector);
  //           4. Leave model matrix as identity for now
  glm::vec3 eye = glm::vec3(1.5f, 2.0f, -8.0f);
  glm::mat4 perspective = glm::perspective(glm::radians(60.0f), float(width) / float(height), 0.01f, 200.0f);
  glm::mat4 view = glm::lookAt(eye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  // Tak 5.1: Upload MVP matrices to `program`
  glProgramUniformMatrix4fv(main_program, 0, 1, GL_FALSE, glm::value_ptr(perspective));
  glProgramUniformMatrix4fv(main_program, 1, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
  glProgramUniformMatrix4fv(main_program, 2, 1, GL_FALSE, glm::value_ptr(view));

  // Tak 5.2: Set uniform data for light and upload camera(eye) position to 'program'
  glProgramUniform3f(main_program, 3, eye.x, eye.y, eye.z);

  glProgramUniform4f(main_program, 4, 0.0f, 3.0f, 0.0f, 0.0f);

  glProgramUniform3f(main_program, 5, 0.2f, 0.2f, 0.2f);
  glProgramUniform3f(main_program, 6, 1.0f, 1.0f, 1.0f);
  glProgramUniform3f(main_program, 7, 0.0f, 0.0f, 0.0f);

  // Tak 5.2: Set uniform data for material
  // (Remember: it's ambient, diffuse, specular and additionally shininess for material)
  glProgramUniform3f(main_program, 8, 0.2f, 0.2f, 0.2f);
  glProgramUniform3f(main_program, 9, 0.5f, 0.5f, 0.5f);
  glProgramUniform3f(main_program, 10, 0.0f, 0.0f, 0.0f);
  glProgramUniform1f(main_program, 11, 4.0f);

  glUseProgram(main_program);

  // Tak 5.1: Separate each object by moving them to different locations using 
  //          glm::translate(glm::mat4 matrix_to_translate, glm::vec3)
  //          Play with other glm functions of the same form: 
  //            - rotate (mat4x4 matrix_to_rotate, float angle, glm::vec3 axis_to_rotate_around)
  //            - translate (mat4x4 matrix_to_translate, glm::vec3 move_by_vector)
  glProgramUniformMatrix4fv(main_program, 1, 1, GL_FALSE, glm::value_ptr(glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f))));
  cube.draw();

  glProgramUniformMatrix4fv(main_program, 1, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f))));
  sphere.draw();

  glProgramUniformMatrix4fv(main_program, 1, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f))));
  teapot.draw();
}

void Application::on_resize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}
void Application::on_mouse_move(GLFWwindow *window, double x, double y) {}
void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) {}
void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_F:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    case GLFW_KEY_L:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    }
  }
}