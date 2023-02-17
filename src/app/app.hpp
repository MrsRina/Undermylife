#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "gpu/opengl_shader.hpp"
#include "gpu/opengl_tools.hpp"
#include "ui/rigid.hpp"
#include "ui/shape.hpp"

namespace app {
    class core {
    protected:
        bool m_mainloop {true};
        int32_t m_screen[2] {800, 600};

        SDL_Window *m_p_sdl_win {};
        SDL_GLContext m_gl_context {};
        float m_angle {};

        gpu::shader *m_p_main_shader {};
        gpu::buffering m_buffer {};
        ui::shape m_shape {};
        std::vector<ui::rigid> m_loaded_rigid_list {};

        void on_event(SDL_Event &sdl_event);
        void on_update();
        void on_render();
    public:
        static glm::mat4 mat4x4ortho;

        void process_matrices();
        int32_t run();
    };
}

#endif