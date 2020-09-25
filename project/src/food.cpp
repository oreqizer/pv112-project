#include <cstdlib>
#include <vector>

#include "settings.hpp"

#include "food.hpp"

glm::vec3 Food::render() { return position; }

void Food::generate(const std::vector<glm::vec3> &blocked) {
  std::vector<glm::vec3> options;
  for (int i = 0; i < int(Settings::Size); i++) {
    for (int j = 0; j < int(Settings::Size); j++) {
      for (int k = 0; k < int(Settings::Size); k++) {
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
