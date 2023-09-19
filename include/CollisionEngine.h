//
// Created by Conni Bilham on 25/07/2023.
//

#ifndef INC_2D_ENGINE_COLLISIONENGINE_H
#define INC_2D_ENGINE_COLLISIONENGINE_H

#include "vec3.hpp"
#include "glm.hpp"
#include "logging.h"

class BoxCollider;
class CollisionEngine {
public:
    CollisionEngine() {

    }
    glm::vec3 test;


    static unsigned int side(glm::vec2 A, glm::vec2 B, glm::vec2 P);

    static bool isInside(BoxCollider A, glm::vec3 P);
};

class BoxCollider {

public:
    glm::vec3 A = {};
    glm::vec3 B;
    glm::vec3 C;
    glm::vec3 D;

    bool contains(glm::vec3 P) {
        const int aUV = 1;
        const int bUV = 1;
        const int cUV = 1;
        const int dUV = 1;

        auto a = CollisionEngine::side(A, B, P);
        if(a != aUV) {
            logging::info("Side check for A to B failed");
        }
        auto b = CollisionEngine::side(B, C, P);
        if(b != bUV) {
            logging::info("Side check for B to C failed");
        }
        auto c = CollisionEngine::side(C, D, P);
        if(c != cUV) {
            logging::info("Side check for C to D failed");
        }
        auto d = CollisionEngine::side(D, A, P);
        if(d != dUV) {
            logging::info("Side check for D to A failed");
        }

        // TODO: Return a value
    }
};


#endif //INC_2D_ENGINE_COLLISIONENGINE_H
