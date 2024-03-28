#pragma once

#include <string>
#include "object2D.h"
#include "Tema1.h"
#include "transform2D.h"

#include <vector>
#include <iostream>

class projectile {
    std::string color;
    float projectileX, projectileY, angle, scale;
    bool isShot;

    public:

        projectile() {
            angle = 0;
            scale = 1.0f;
            isShot = false;
        }

        float getProjectileX() {
            return projectileX;
        }

        float getProjectileY() {
            return projectileY;
        }

        float getAngle() {
            return angle;
        }

        float getScale() {
            return scale;
        }

        bool getIsShot() {
            return this->isShot;
        }

        void setIsShot(bool isShot) {
            this->isShot = isShot;
        }

        void setProjectileX(float projectileX) {
            this->projectileX = projectileX;
        }

        void setProjectileY(float projectileY) {
            this->projectileY = projectileY;
        }

        void setAngle(float angle) {
            this->angle = angle;
        }

        void setScale(float scale) {
            this->scale = scale;
        }
};