#ifndef APP_UI_SHAPE_H
#define APP_UI_SHAPE_H

#include "gpu/opengl_tools.hpp"
#include "gpu/opengl_shader.hpp"

namespace ui {
    class shape {
    protected:
        glm::mat4 m_mat4x4_model {};
    public:
        gpu::buffering *m_p_buffer {};
        gpu::shader *m_p_shader {};

        void invoke();
        void draw(const glm::vec4 &rect, const glm::vec4 &color, float angle = 0.0f);
        void revoke();
    };
}

#endif