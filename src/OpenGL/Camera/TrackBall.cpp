#include "TrackBall.hpp"

TrackBall::TrackBall(glm::vec3 pointLook, float distance):
    Camera(pointLook + distance * glm::vec3(1,0,0), glm::vec3(-1,0,0), glm::vec3(0,1,0)),
    m_pointLook{pointLook}, m_distance{distance}, m_yaw{YAW}, m_pitch{PITCH}
{
    updateCameraVectors();
    name_camera="TrackBall";
}

void TrackBall::mouseMovement(float xOffset, float yOffset, bool constraint){
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    if(constraint){
        if(m_pitch>89) m_pitch = 89;
        if(m_pitch<-89) m_pitch = -89;
    }

    updateCameraVectors();
}

void TrackBall::mouseMovementMiddle(float xOffset, float yOffset) {
    xOffset *= m_mouseSensitivity * 0.1f;
    yOffset *= m_mouseSensitivity * 0.1f;

    m_pointLook = m_pointLook + m_right * xOffset;
    m_pointLook = m_pointLook + m_worldUp * yOffset;
    m_position = m_pointLook - m_front*m_distance;

    updateCameraVectors();
}

void TrackBall::mouseScroll(float offset){
    m_distance -= (m_factorDistance/10)*offset;
    if(m_distance<0.2) m_distance=0.2;
    m_position=m_pointLook-m_front*m_distance;
}

void TrackBall::keyboard(Movement, float){
}

void TrackBall::updateCameraVectors(){
    glm::vec3 front;
    float yaw = glm::radians(m_yaw);
    float pitch = glm::radians(m_pitch);
    front.x = std::cos(yaw) * std::cos(pitch);
    front.y = std::sin(pitch);
    front.z = std::sin(yaw) * std::cos(pitch);
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front,m_worldUp));
    m_up = glm::normalize(glm::cross(m_right,m_front));

    m_position = m_pointLook - m_front*m_distance;
}

void TrackBall::fitScene(AABB aabb){
    m_pointLook = aabb.center();

    m_yaw = YAW;
    m_pitch = PITCH;

    m_worldUp = glm::vec3(0,1,0);

    float fovH = glm::radians( getAspect()* getFOV() );
    float fov = glm::radians( getFOV() );

    float r = 0.5f * glm::length(aabb.max() - aabb.min());
    float x = r / std::tan(fov/2.0);
    float y = r / std::tan(fovH/2.0);

    m_distance = std::max(std::max(x,y), (float)0.001);
    m_factorDistance = m_distance;

    updateCameraVectors();
}

void TrackBall::fitScene(std::vector<BasicModel> models){
  glm::vec3 min = glm::vec3(9999999999999999.f,9999999999999999.f,9999999999999999.f);
  glm::vec3 max = -min;
  //Get AABB of the whole scene
  for(const auto& model : models){
      glm::vec3 modelMin = model.aabb().min();
      glm::vec3 modelMax = model.aabb().max();

      min.x = min.x > modelMin.x ? modelMin.x : min.x;
      min.y = min.y > modelMin.y ? modelMin.y : min.y;
      min.z = min.z > modelMin.z ? modelMin.z : min.z;

      max.x = max.x < modelMax.x ? modelMax.x : max.x;
      max.y = max.y < modelMax.y ? modelMax.y : max.y;
      max.z = max.z < modelMax.z ? modelMax.z : max.z;
    }
  AABB sceneAABB(min,max);
  fitScene(sceneAABB);
}
