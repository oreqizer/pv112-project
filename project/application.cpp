#include <iostream>

#include "src/audio.hpp"

#include "application.hpp"

const float scaleCube = 2;
const glm::vec3 scaleCubeVec = glm::vec3(scaleCube);

const float lightConeCos = 0.95f;

const float alphaSnake = 1.0f;
const float alphaWall = 0.025f;

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  game = new Game();

  Audio::play(Audio::background, true);

  printInit();

  // --------------------------------------------------------------------------
  // Initialize UBO Data
  // --------------------------------------------------------------------------

  // Camera
  camera.setDistance(settings::size * scaleCube * 2);
  camera.setEyeOffset(Game::center * scaleCubeVec);

  uboCamera.position = glm::vec4(camera.getEyePosition(), 1.0f);
  uboCamera.view = glm::lookAt(camera.getEyePosition(), Game::center * scaleCubeVec, glm::vec3(0.0f, 1.0f, 0.0f));
  uboCamera.projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.01f, 1000.0f);

  // Lights
  glm::vec4 ambient(0.2f);
  glm::vec4 diffuse(0.5f);
  glm::vec4 specular(1.0f);

  auto arenaSize = settings::size * scaleCube;

  lights.push_back({glm::vec4(0, arenaSize, 0, 1.0), glm::vec4(0.5, -1, 0.5, lightConeCos), ambient, diffuse, specular});
  lights.push_back({glm::vec4(arenaSize, arenaSize, 0, 1.0), glm::vec4(-0.5, -1, 0.5, lightConeCos), ambient, diffuse, specular});
  lights.push_back({glm::vec4(0, arenaSize, arenaSize, 1.0), glm::vec4(0.5, -1, -0.5, lightConeCos), ambient, diffuse, specular});
  lights.push_back({glm::vec4(arenaSize, arenaSize, arenaSize, 1.0), glm::vec4(-0.5, -1, -0.5, lightConeCos), ambient, diffuse, specular});

  // Initial walls
  fillWalls();

  // --------------------------------------------------------------------------
  // CREATE BUFFERS
  // --------------------------------------------------------------------------

  glCreateBuffers(1, &bufferCamera);
  glNamedBufferStorage(bufferCamera, sizeof(CameraUBO), &uboCamera, GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferLights);
  glNamedBufferStorage(bufferLights, lights.size() * sizeof(LightUBO), lights.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferSnake);
  glNamedBufferStorage(bufferSnake, settings::size * settings::size * settings::size * sizeof(SnakeUBO), snake.data(),
                       GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferWalls);
  glNamedBufferStorage(bufferWalls, walls.size() * sizeof(WallUBO), walls.data(), GL_DYNAMIC_STORAGE_BIT);

  glGenVertexArrays(1, &vaoGui);
  glGenBuffers(1, &vboGui);

  glBindVertexArray(vaoGui);
  glBindBuffer(GL_ARRAY_BUFFER, vboGui);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);  
}

Application::~Application() {
  glDeleteProgram(programSnake);

  glDeleteBuffers(1, &bufferCamera);
  glDeleteBuffers(1, &bufferLights);
  glDeleteBuffers(1, &bufferSnake);
  glDeleteBuffers(1, &bufferWalls);
}

void Application::update() { game->update(); }

void Application::render() {
  // =====
  // TODOs
  // =====
  //
  // 3. https://learnopengl.com/In-Practice/2D-Game/Audio
  // 4. GUI https://stackoverflow.com/questions/5898922/i-have-a-problem-about-opengl-glut-glutstrokecharacter-the-code-did-not-work

  // --------------------------------------------------------------------------
  // UPDATE UBOS
  // --------------------------------------------------------------------------

  // Camera
  uboCamera.position = glm::vec4(camera.getEyePosition(), 1.0f);
  uboCamera.view = glm::lookAt(camera.getEyePosition(), Game::center * scaleCubeVec, glm::vec3(0.0f, 1.0f, 0.0f));

  glNamedBufferSubData(bufferCamera, 0, sizeof(CameraUBO), &uboCamera);

  // Snake
  fillSnake();

  glNamedBufferSubData(bufferSnake, 0, snake.size() * sizeof(SnakeUBO), snake.data());

  // --------------------------------------------------------------------------
  // DRAW THE SCENE
  // --------------------------------------------------------------------------
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, this->width, this->height);

  // === 1. BLEND ===
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Snake and food
  glEnable(GL_DEPTH_TEST);

  glUseProgram(programSnake);

  glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferCamera);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferLights);

  auto alphaSnakeUniform = glGetUniformLocation(programSnake, "alpha");

  glUniform1f(alphaSnakeUniform, alphaSnake);

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferSnake);
  glBindVertexArray(cube.get_vao());
  glDrawElementsInstanced(cube.get_mode(), static_cast<GLsizei>(cube.get_indices_count()), GL_UNSIGNED_INT, nullptr,
                          static_cast<GLsizei>(snake.size()));

  glDisable(GL_DEPTH_TEST);

  // Walls
  glUseProgram(programWall);

  glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferCamera);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferLights);

  auto alphaWallUniform = glGetUniformLocation(programWall, "alpha");
  auto sizeUniform = glGetUniformLocation(programWall, "size");
  auto timeUniform = glGetUniformLocation(programWall, "time");

  glUniform1f(alphaWallUniform, alphaWall);
  glUniform1i(sizeUniform, settings::size);
  glUniform1f(timeUniform, glfwGetTime());

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferWalls);
  glBindVertexArray(cube.get_vao());
  glDrawElementsInstanced(cube.get_mode(), static_cast<GLsizei>(cube.get_indices_count()), GL_UNSIGNED_INT, nullptr,
                          static_cast<GLsizei>(walls.size()));

  // Gui
  glUseProgram(programText);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

  if (game->state == GameState::Crashed) {
    printRIP();
  } else {
    printScore(game->snake->score());
  }
}

void Application::fillWalls() {
  walls.clear();

  auto wallPositions = game->world->render();

  auto time = glfwGetTime();

  for (auto pos : wallPositions) {
    auto position = pos * scaleCubeVec;

    auto distance = glm::distance(glm::vec3(0.0), position);
    auto translate = glm::translate(glm::mat4(1.0), position);

    walls.push_back({
        translate,      // position
        glm::vec4(1.0), // ambient
        glm::vec4(1.0), // diffuse
        glm::vec4(1.0), // specular
        glm::vec4(distance, 0.0, 0.0, 0.0),
    });
  }
}

void Application::fillSnake() {
  snake.clear();

  auto foodPosition = game->food->render();
  auto snakePositions = game->snake->render();

  auto ambient = game->state == GameState::Crashed ? glm::vec4(1.0, 0, 0, 1.0) : glm::vec4(1.0);
  auto diffuse = game->state == GameState::Crashed ? glm::vec4(1.0, 0, 0, 1.0) : glm::vec4(1.0);
  auto specular = game->state == GameState::Crashed ? glm::vec4(1.0, 0, 0, 4.0) : glm::vec4(1.0, 1.0, 1.0, 4);

  snake.push_back({
      glm::translate(glm::mat4(1.0), foodPosition * scaleCubeVec),
      glm::vec4(0.25),
      glm::vec4(1.0),
      glm::vec4(1.0, 1.0, 1.0, 4),
  });

  for (auto pos : snakePositions) {
    auto position = pos * scaleCubeVec;
    auto translate = glm::translate(glm::mat4(1.0), position);

    snake.push_back({
        translate,
        ambient,
        diffuse,
        specular,
    });
  }
}

void Application::printScore(int score) {
  std::string text = std::to_string(score);
  glm::vec3 color(1.0f);

  float x = -0.02;
  float y = -0.9;
  float scale = 0.002;

  auto characters = game->gui->characters;
  // activate corresponding render state
  glUniform3f(glGetUniformLocation(programText, "textColor"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vaoGui);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = characters[*c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
    // update VBO for each character
    float vertices[6][4] = {
        { xpos,     ypos + h,   0.0f, 0.0f },            
        { xpos,     ypos,       0.0f, 1.0f },
        { xpos + w, ypos,       1.0f, 1.0f },

        { xpos,     ypos + h,   0.0f, 0.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos + w, ypos + h,   1.0f, 0.0f }           
    };
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vboGui);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::printRIP() {
  std::string text = "[SPACE to restart]";
  glm::vec3 color(1.0f);

  float x = -0.35;
  float y = -0.9;
  float scale = 0.002;

  auto characters = game->gui->characters;
  // activate corresponding render state
  glUniform3f(glGetUniformLocation(programText, "textColor"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vaoGui);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = characters[*c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
    // update VBO for each character
    float vertices[6][4] = {
        { xpos,     ypos + h,   0.0f, 0.0f },            
        { xpos,     ypos,       0.0f, 1.0f },
        { xpos + w, ypos,       1.0f, 1.0f },

        { xpos,     ypos + h,   0.0f, 0.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos + w, ypos + h,   1.0f, 0.0f }           
    };
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vboGui);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::printInit() {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

  FT_Face face = game->gui->face;

  for (unsigned char c = 0; c < 128; c++) {
    // load character glyph
    auto err = FT_Load_Char(face, c, FT_LOAD_RENDER);
    if (err) {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph: " << err << std::endl;
      continue;
    }

    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);

    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // now store character for later use
    Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                           glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x};

    game->gui->characters.insert(std::pair<char, Character>(c, character));
  }
}

void Application::onResize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;
}

void Application::onMouseMove(GLFWwindow *window, double x, double y) { camera.onMouseMove(x, y); }

void Application::onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_W:
      game->snake->turn(Arrow::Top);
      break;
    case GLFW_KEY_S:
      game->snake->turn(Arrow::Bottom);
      break;
    case GLFW_KEY_D:
      game->snake->turn(Arrow::Left);
      break;
    case GLFW_KEY_A:
      game->snake->turn(Arrow::Right);
      break;
    case GLFW_KEY_E:
      game->snake->turn(Arrow::Back);
      break;
    case GLFW_KEY_Q:
      game->snake->turn(Arrow::Forward);
      break;
    case GLFW_KEY_SPACE:
      game->reset();
      break;
    }
  }
}
