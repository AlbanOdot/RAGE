#ifndef TRACKBALL_HPP
#define TRACKBALL_HPP

/**
 * \file TrackBall.hpp
 * \brief Simple trackball camera
 */

#include "Camera.hpp"



#define YAW -90
#define PITCH 0

class TrackBall : public Camera
{
public:
    TrackBall(glm::vec3 pointLook = glm::vec3(0,0,0), float distance = 3);

    void mouseMovement(float xOffset, float yOffset, bool  constraint = true) override;
    void mouseMovementMiddle(float xOffset, float yOffset) override;
    void mouseScroll(float offset) override;
    void keyboard(Movement movement, float deltatime) override;
    void updateCameraVectors() override;

    void fitScene(AABB aabb) override;
    void fitScene(std::vector<BasicModel> models) override;

    glm::vec3 m_pointLook;
    float m_distance;
    float m_yaw, m_pitch;
};

#endif // TRACKBALL_HPP
