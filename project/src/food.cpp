#include <cstdlib>
#include <vector>

#include "settings.hpp"

#include "food.hpp"

glm::vec3 Food::render() { return position; }

void Food::generate(const std::vector<glm::vec3> &blocked) {
  std::vector<glm::vec3> options;
  for (int i = 0; i < settings::size; i++) {
    for (int j = 0; j < settings::size; j++) {
      for (int k = 0; k < settings::size; k++) {
        auto item = glm::vec3(i, j, k);

        bool ok = true;
        for (auto b : blocked) {
          if (b == item) {
            ok = false;
          }
        }

        if (ok) {
          options.push_back(item);
        }
      }
    }
  }

  auto index = std::rand() % options.size();

  position = options[index];
}
