#ifndef APP_GPU_OPENGL_SHADER_H
#define APP_GPU_OPENGL_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <map>
#include <vector>

namespace gpu {
    class shader {
    protected:
        uint32_t m_id {};
    public:
        std::string m_name {};

        shader(std::string_view name) : m_id(glCreateProgram()), m_name(name.data()) {}
        ~shader() {
            glDeleteProgram(this->m_id);
        }

        void invoke() const {
            glUseProgram(this->m_id);
        }

        void set_uniform_vec4(std::string_view name, const float *p_data) const {
            glUniform4fv(glGetUniformLocation(this->m_id, name.data()), GL_TRUE, p_data);
        }

        void set_uniform_mat4(std::string_view name, const float *p_data) const {
            glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.data()), GL_TRUE, GL_FALSE, p_data);
        }

        void revoke() const {
            glUseProgram(0);
        }

        uint32_t &get() {
            return this->m_id;
        }
    };

    typedef struct resource {
        std::string m_in {};
        uint32_t m_stage {};
        bool m_src {};
    } resource;

    bool create(gpu::shader *p_shader, const std::vector<gpu::resource> &resources);
}

#endif