#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <src/Math/ray.h>
#include <src/OpenGL/Object/Model/AABB.h>
#include "./src/OpenGL/Object/Model/Model.h"
#include <string>
#include <glm.hpp>

/**
 * \file Camera.hpp
 * \brief Mother class for camera
 *
 * Mother class for camera
 *
 */

#define ZOOM 45
#define SPEED 2.5
#define SENSITIVITY 0.25

enum Movement{FORWARD = 1, BACKWARD = 3, LEFT = 0, RIGHT = 2};

/**
 * \class Camera
 * \brief Mother class for camera
 */
class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(1,0,0), glm::vec3 front = glm::vec3(-1,0,0), glm::vec3 worldUp = glm::vec3(0,1,0));

    virtual void mouseMovement(float xOffset, float yOffset, bool constraint = true) = 0;
    virtual void mouseMovementMiddle(float xOffset, float yOffset) = 0;
    virtual void mouseScroll(float offset) = 0;
    virtual void keyboard(Movement movement, float deltatime) = 0;
    virtual void updateCameraVectors() = 0;

    virtual void fitScene(AABB aabb) = 0;
    virtual void fitScene(std::vector<Model> models) = 0;
    Ray getRayFromScreen(float x, float y);

    void updateCameraVectorsInit();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjMatrix();
    glm::mat4 GetProjViewMatrix();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_factorDistance;
    float m_zoom;

    std::string name_camera;

    void resizeCamera(int width, int height);
    int m_width, m_height;
    float getAspect();
    float getFOV();

private:
    float m_zNear;
    float m_zFar;
};

#endif // CAMERA_HPP
