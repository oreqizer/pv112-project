#include <vector>

#include "settings.hpp"

#include "food.hpp"

std::vector<Mesh> Food::render() {
    // TODO
}

void Food::generate(const std::vector<glm::vec3> &blocked) {
    std::vector<glm::vec3> options;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
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

    auto index = rand() % options.size();

    position = options[index];
}
