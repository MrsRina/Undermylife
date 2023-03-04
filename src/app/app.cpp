#include "app.hpp"
#include "util/util.hpp"
#include "ui/shape.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 app::core::mat4x4ortho {};

void app::core::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_QUIT: {
            this->m_mainloop = false;
            break;
        }

        case SDL_WINDOWEVENT: {
            if (sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                this->m_screen[0] = sdl_event.window.data1;
                this->m_screen[1] = sdl_event.window.data2;
                this->process_matrices();
            }
        }
    }
}

void app::core::on_update() {
    glViewport(0, 0, this->m_screen[0], this->m_screen[1]);
}

void app::core::on_render() {
    float s {glm::sin(this->m_angle)};

    glClearColor(s, s, s, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec4 rect {};
    glm::vec4 color {this->m_angle, 1.0f, 1.0f, 1.0f};

    this->m_p_main_shader->invoke();
    this->m_buffer.invoke();

    glm::mat4 perspective = glm::perspective(glm::radians(90.0f), (float) this->m_screen[0] / (float) this->m_screen[1], 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);

    this->m_angle += 0.01f;
    glm::vec3 pos {-1, -0.5f, -3};

    model = glm::translate(model, pos);

    model = glm::scale(model, glm::vec3(2.0f));
    model = perspective * model;

    this->m_p_main_shader->set_uniform_mat4("uMVP", &model[0][0]);
    this->m_p_main_shader->set_uniform_vec4("uColor", &color[0]);

    glPointSize(1.0F);
    this->m_buffer.draw();
    this->m_buffer.revoke();
}

int32_t app::core::run() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    this->m_p_sdl_win = SDL_CreateWindow("Welcome to Undermylife!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_screen[0], this->m_screen[1], SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    this->m_gl_context = SDL_GL_CreateContext(this->m_p_sdl_win);

    glewExperimental = GL_TRUE;
    glewInit();
    SDL_GL_SetSwapInterval(1);

    SDL_Event sdl_event {};
    uint64_t interval {1000 / 60};

    util::log("Welcome to Undermylife!");
    this->process_matrices();

    this->m_p_main_shader = new gpu::shader("main.overlay");
    gpu::create(this->m_p_main_shader, {
            {"./shaders/overlay.vert", GL_VERTEX_SHADER},
            {"./shaders/overlay.frag", GL_FRAGMENT_SHADER}
    });

    glm::vec3 volume {256, 4, 256};
    std::vector<float> vertices {};

    for (int32_t x = 0; x < volume.x; x++) {
        for (int32_t y = 0; y < volume.y; y++) {
            for (int32_t z = 0; z < volume.z; z++) {
                vertices.push_back((float) x / (float) volume.x);
                vertices.push_back((float) y / (float) volume.y);
                vertices.push_back((float) z / (float) volume.z);
            }
        }
    }

    this->m_buffer.invoke();
    this->m_buffer.m_primitive[0] = GL_POINTS;
    this->m_buffer.m_stride[1] = vertices.size();

    this->m_buffer.bind(0, {GL_ARRAY_BUFFER, GL_FLOAT});
    this->m_buffer.send<float>(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    this->m_buffer.attach(0, 3, {0, 0});
    this->m_buffer.revoke();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    while (this->m_mainloop) {
        while (SDL_PollEvent(&sdl_event)) {
            this->on_event(sdl_event);
        }

        this->on_update();
        this->on_render();

        SDL_GL_SwapWindow(this->m_p_sdl_win);
        SDL_Delay(interval);
    }

    return 0;
}

void app::core::process_matrices() {
    app::core::mat4x4ortho = glm::ortho(0.0f, static_cast<float>(this->m_screen[0]), static_cast<float>(this->m_screen[1]), 0.0f);
}