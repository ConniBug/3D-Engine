//
// Created by Conni Bilham on 11/07/2023.
//

#ifndef INC_2D_ENGINE_CAMERA_H
#define INC_2D_ENGINE_CAMERA_H

#define DEFAULT_YAW -90.0f
#define DEFAULT_PITCH 0.0f
#define DEFAULT_SPEED 2.5f
#define DEFAULT_SENSITIVITY 0.1f
#define DEFAULT_ZOOM 45.0f

#include "vec3.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "logging.h"


#include <iostream>

enum CAMERA_TYPE {
    NONE,
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 global_up;

    float yaw;
    float pitch;

    float movement_speed;
    float sprint_speed;
    float mouse_sensitivity;
    float fov;

    CAMERA_TYPE type;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = DEFAULT_YAW,
           float pitch = DEFAULT_PITCH,
           CAMERA_TYPE type = CAMERA_TYPE::NONE) {


        front = glm::vec3(0.0f, 0.0f, -1.0f);
        movement_speed = DEFAULT_SPEED;
        sprint_speed = movement_speed * 3;
        mouse_sensitivity = DEFAULT_SENSITIVITY;
        fov = DEFAULT_ZOOM;

        this->position = position;
        this->global_up = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->type = type;

        updateCamera();
    }

    glm::mat4 view_matrix() {
        return glm::lookAt(position, position + front, up);
    }

    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    void HandleKeyboard(CameraMovement direction, double delta_time, bool sprinting = false) {
        float velocity = this->movement_speed * delta_time * (sprinting ? this->sprint_speed : 1.);
        if (direction == FORWARD) {
            position += front * velocity;
        }
        if (direction == BACKWARD) {
            position -= front * velocity;
        }
        if (direction == LEFT) {
            position -= right * velocity;
        }
        if (direction == RIGHT) {
            position += right * velocity;
        }
    }

    void HandleMouseMovement(float x_offset, float y_offset, bool constrain_pitch = true) {
        this->yaw   += x_offset * this->mouse_sensitivity;
        this->pitch += y_offset * this->mouse_sensitivity;

//        const float pitch_max = 5.f;
//        const float yaw_max = 5.f;
//        if (this->pitch > pitch_max)
//            this->pitch = pitch_max;
//        if (this->pitch < -pitch_max)
//            this->pitch = -pitch_max;
//
//        if (this->yaw < -90.f - yaw_max) {
//            this->yaw = -90.f - yaw_max;
//        }
//        if (this->yaw > -90.f + yaw_max) {
//            this->yaw = -90.f + yaw_max;
//        }

        if(this->yaw > 360.f)
            this->yaw -= 360.f;
        if(this->yaw < -360.f)
            this->yaw += 360.f;

        updateCamera();
    }

    void HandleMouseScroll(double offset) {
        // Clamp zoom
        this->fov -= (float)offset;
        if (this->fov < 1.0f)
            this->fov = 1.0f;
        else if(this->fov > 120.0f)
            this->fov = 120.0f;
    }

    glm::mat4 getProjectionMatrix(float width, float height) {
        auto projection = glm::mat4(1.0f);
        if(this->type == CAMERA_TYPE::NONE) {
            logging::error("Camera::getProjectionMatrix() - Camera type not set");
            std::getchar();
            exit(-1);
        }
        switch (type) {
            case CAMERA_TYPE::ORTHOGRAPHIC:
                projection *= glm::ortho(0.0f, width, 0.0f, height, -100.0f, 100.0f);
                break;
            case CAMERA_TYPE::PERSPECTIVE:
                projection *= glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
                break;
            case NONE:
                break;
        }
        return projection;
    }

private:
    void updateCamera() {
        glm::vec3 front = {
                cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                sin(glm::radians(pitch)),
                sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        };
//        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//        front.y = sin(glm::radians(pitch));
//        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        this->front = glm::normalize(front);

        this->right = glm::normalize(glm::cross(this->front, this->global_up));
        this->up    = glm::normalize(glm::cross(this->right, this->front));
    }
};


#endif //INC_2D_ENGINE_CAMERA_H
