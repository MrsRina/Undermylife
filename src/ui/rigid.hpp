#ifndef APP_UI_RIGID_H
#define APP_UI_RIGID_H

#include <glm/glm.hpp>

namespace ui {
    typedef struct rigid {
        glm::vec2 position {};
        glm::vec2 size {};
        float angle {};
    } rigid;
}

#endif