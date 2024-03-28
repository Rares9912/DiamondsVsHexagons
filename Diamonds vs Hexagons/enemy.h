#pragma once

#include <string>
#include "Tema1.h"
#include "object2D.h"
#include "transform2D.h"

#include <vector>
#include <iostream>

class enemy {
    // int lives;
    std::string color;
    Mesh* mesh;
    bool canSpawnEnemy, isDead;
    float enemyX, enemyY, scale, scaleSpeed, enemySpeed;
    double currentTime, deltaTime;

    public:
        void createMesh(const std::string &name, glm::vec3 origin, float length, glm::vec3 firstColor, glm::vec3 secondColor, bool fill) {
            mesh = object2D::CreateHexagon(name, origin, length, firstColor, secondColor, fill);
        }

        Mesh* getMesh() {
            return mesh;
        }

        enemy(std::string color) {
            canSpawnEnemy = false;
            enemyX = 2500;
            scale = 1.0f;
            this->color = color;
            isDead = false;
            scaleSpeed = 1.5f;
            enemySpeed = 300.0f;
        }

        double getCurrentTime() {
            return currentTime;
        }

        double getDeltaTime() {
            return deltaTime;
        }

        float getEnemyX() {
            return enemyX;
        }

        float getEnemyY() {
            return enemyY;
        }

        bool getCanSpawnEnemy() {
            return canSpawnEnemy;
        }

        float getScale() {
            return scale;
        }

        bool getIsDead() {
            return this->isDead;
        }

        std::string getColor() {
            return color;
        }

        void setCurrentTime(double currentTime) {
            this->currentTime = currentTime;
        }

        void setDeltaTime(double deltaTime) {
            this->deltaTime = deltaTime;
        }

        void setSpawnEnemy(bool canSpawnEnemy) {
            this->canSpawnEnemy = canSpawnEnemy;
        }

        void setScale (float scale) {
            this->scale = scale;
        }

        void setEnemyY (float enemyY) {
            this->enemyY = enemyY;
        }

        void setIsDead (bool isDead) {
            this->isDead = isDead;
        }

        glm::mat3 spawnEnemy(float deltaTimeSeconds) {
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemyX, enemyY);
            if (enemyX > 100 && !isDead) {
                enemyX -= deltaTimeSeconds * enemySpeed;
            } else {
                if (scale > 0.0f) {
                    scale -= deltaTimeSeconds * scaleSpeed;
                } else {
                    scale = 0.0f;
                    setSpawnEnemy(false);
                    enemyX = 2500;
                    isDead = false;
                }
                modelMatrix *= transform2D::Scale(scale, scale);
            }
            return modelMatrix;
            
        }

};