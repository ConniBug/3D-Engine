//
// Created by Conni Bilham on 25/07/2023.
//

#include "CollisionEngine.h"

unsigned int CollisionEngine::side(glm::vec2 A, glm::vec2 B, glm::vec2 P) {
    auto d = (P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x);

    if(d == 0)
        return 0;
    else
        return d > 0 ? 1 : 2;
}

bool CollisionEngine::isInside(BoxCollider A, glm::vec3 P) {

}

