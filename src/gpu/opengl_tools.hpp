#ifndef APP_GPU_OPENGL_TOOLS_H
#define APP_GPU_OPENGL_TOOLS_H

#include <glm/glm.hpp>
#include <GL/GLEW.h>
#include <map>

namespace gpu {
    class buffering {
    protected:
        std::map<uint32_t, uint32_t> m_buffer_map {};
        uint32_t m_vbo {};
    public:
        int32_t m_primitive[2] {GL_TRIANGLES, GL_UNSIGNED_BYTE};
        int32_t m_stride[3] {};

        int32_t m_buffer_info[2] {};
        bool m_indexing_rendering {};

        void invoke() {
            if (this->m_vbo == 0) {
                glGenVertexArrays(1, &this->m_vbo);
            }

            glBindVertexArray(this->m_vbo);
        }

        void bind(uint32_t key, const glm::ivec2 &buffer_type) {
            uint32_t &buffer {this->m_buffer_map[key]};
            if (buffer == 0) {
                glGenBuffers(1, &buffer);
            }

            if (buffer_type.x == GL_ELEMENT_ARRAY_BUFFER) {
                this->m_indexing_rendering = true;
            }

            glBindBuffer(buffer_type.x, buffer);
            this->m_buffer_info[0] = buffer_type.x;
            this->m_buffer_info[1] = buffer_type.y;
        }

        template<typename t>
        void send(int32_t size, const t *p_data, uint32_t mode) {
            glBufferData(this->m_buffer_info[0], size, p_data, mode);
        }

        template<typename t>
        void edit(const glm::ivec2 &stride, const t *p_data) {
            glBufferSubData(this->m_buffer_info[0], stride.x, stride.y, p_data);
        }

        void attach(int32_t location, int32_t vec, const glm::ivec2 &stride = {0, 0}) {
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(location, vec, this->m_buffer_info[1], GL_FALSE, stride.x, (void*) (int64_t) stride.y);
        }

        void unbind() const {
            glBindBuffer(this->m_buffer_info[0], 0);
        }

        void revoke() const {
            glBindVertexArray(0);
        }

        void draw() {
            if (this->m_indexing_rendering) {
                glDrawElements(this->m_primitive[0], this->m_stride[0], this->m_primitive[1], (void*) (int64_t) this->m_stride[1]);
            } else {
                glDrawArrays(this->m_primitive[0], this->m_stride[0], this->m_stride[1]);
            }
        }
    };
}

#endif