#include <glm/ext/matrix_transform.hpp>
#include "shape.hpp"
#include "app/app.hpp"

void ui::shape::invoke() {
    this->m_p_shader->invoke();
    this->m_p_buffer->invoke();
}

void ui::shape::draw(const glm::vec4 &rect, const glm::vec4 &color, float angle) {
    this->m_mat4x4_model = glm::mat4(1.0f);
    this->m_mat4x4_model = glm::translate(this->m_mat4x4_model, {rect.x + (rect.z / 2), rect.y + (rect.w / 2), 0.0f});
    this->m_mat4x4_model = glm::rotate(this->m_mat4x4_model, angle, {0.0f, 0.0f, 1.0f});
    this->m_mat4x4_model = glm::translate(this->m_mat4x4_model, {-(rect.x + (rect.z / 2)), -(rect.y + (rect.w / 2)), 0.0f});
    this->m_mat4x4_model = app::core::mat4x4ortho * this->m_mat4x4_model;

    this->m_p_shader->set_uniform_mat4("uProjectionModelMatrix", &this->m_mat4x4_model[0][0]);
    this->m_p_shader->set_uniform_vec4("uRect", &rect[0]);
    this->m_p_shader->set_uniform_vec4("uColor", &color[0]);

    this->m_p_buffer->draw();
}

void ui::shape::revoke() {
    this->m_p_buffer->revoke();
    this->m_p_shader->revoke();
}
