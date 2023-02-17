#include "opengl_shader.hpp"
#include "util/util.hpp"

bool gpu::create(gpu::shader *p_shader, const std::vector<gpu::resource> &resources) {
    if (p_shader == nullptr || resources.empty()) {
        return util::warning("Invalid shader create, null or empty resources.");
    }

    std::string shader_src {};
    std::vector<uint32_t> compiled_shader_list {};
    int32_t status {};

    for (const auto &resource : resources) {
        shader_src = resource.m_in;
        if (!resource.m_src && util::readfile(resource.m_in, shader_src)) {
            break;
        }

        uint32_t shader {glCreateShader(resource.m_stage)};
        const char *p_src {shader_src.data()};
        glShaderSource(shader, 1, &p_src, nullptr);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &status);
            std::string msg {}; msg.resize(status);
            glGetShaderInfoLog(shader, status, nullptr, msg.data());

            shader_src = "Failed to compile shader '";
            shader_src += p_shader->m_name;
            shader_src += "'!\n";
            shader_src += msg;

            util::warning(shader_src);
            break;
        }

        compiled_shader_list.push_back(shader);
    }

    bool keep {compiled_shader_list.size() == resources.size()};
    uint32_t program {p_shader->get()};

    for (uint32_t &shaders : compiled_shader_list) {
        if (keep) {
            glAttachShader(program, shaders);
        }

        glDeleteShader(shaders);
    }

    if (keep) {
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        if (status == GL_FALSE) {
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &status);
            std::string msg {}; msg.resize(status);
            glGetProgramInfoLog(program, status, nullptr, msg.data());

            shader_src = "Failed to link program '";
            shader_src += p_shader->m_name;
            shader_src += "'!\n";
            shader_src += msg;
            return util::warning(shader_src);
        } else {
            shader_src = "Successfully created program '";
            shader_src += p_shader->m_name;
            shader_src += "'!\n";
            return util::log(shader_src);
        }
    }

    return false;
}
