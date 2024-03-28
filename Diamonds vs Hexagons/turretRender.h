#pragma once

#include <string>
#include "Tema1.h"

#include <vector>
#include <iostream>

class turretRender {
    bool render;
    std::string color;

    public:
        turretRender(bool render, std::string color) {
            this->render = render;
            this->color = color;
        }

        bool getRender() {
            return this->render;
        }

        std::string getColor() {
            return this->color;
        }

        void setRender(bool render) {
            this->render = render;
        }

        void setColor(std::string color) {
            this->color = color;
        }
};