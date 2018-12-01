#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define GL_GLEXT_PROTOTYPES 1

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp):
    m_position{position}, m_front{front}, m_worldUp{worldUp},
    m_movementSpeed{SPEED}, m_mouseSensitivity{SENSITIVITY}, m_zoom{ZOOM},
    name_camera{"NO NAME"}, m_zNear{0.1f}, m_zFar{500.f}
{
    updateCameraVectorsInit();
    m_factorDistance = glm::length(position);
}

#include <Eigen/Core>

glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjMatrix(){
    return glm::perspective(glm::radians(m_zoom), (float)m_width / (float)m_height, m_zNear, m_zFar);
}

glm::mat4 Camera::GetProjViewMatrix(){
    return GetProjMatrix() * GetViewMatrix();
}

Ray Camera::getRayFromScreen(float x, float y) {
    glm::vec3 u = glm::unProject(glm::vec3(x,m_height-y,m_zNear),GetViewMatrix(),GetProjMatrix(),glm::vec4(0,0,m_width,m_height));
    Ray r(m_position,u-m_position);
    return r;
}

void Camera::updateCameraVectorsInit(){
    m_front = glm::normalize(m_front);
    m_right = glm::normalize(glm::cross(m_front,m_worldUp));
    m_up = glm::normalize(glm::cross(m_right,m_front));
}

void Camera::resizeCamera(int width, int height){
    m_width=width;
    m_height=height;
}

float Camera::getAspect() {
    return (float)m_width/(float)m_height;
}

float Camera::getFOV() {
    return m_zoom;
}
