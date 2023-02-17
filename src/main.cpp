#include <SDL2/SDL.h>
#include "app/app.hpp"
#include <glm/ext/matrix_transform.hpp>

int32_t main(int32_t, char**) {
    app::core runtime {};
    return runtime.run();
}