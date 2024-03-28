#pragma once

#include <string>
#include "Tema1.h"
#include "projectile.h"

#include <vector>
#include <iostream>


class turret {
    float turretX, turretY, scale, projectileSpeed, rotationSpeed;
    Mesh* mesh;
    bool canPlaceTurret, canShoot, isShooting, hasTarget, killProjectile, hasBeenShot, isDead;
    std::string color;
    projectile projectile;
    enemy* target;
    std::list<enemy> enemiesApproaching;
    double currentTime, deltaTime, startTime;

    public:
        turret() {
            canPlaceTurret = false;
            canShoot = false;
            isShooting = false;
            hasTarget = false;
            killProjectile = false;
            hasBeenShot = false;
            scale = 1.0f;
            isDead = false;
            projectileSpeed = 275.0f;
            rotationSpeed = 5.0f;
        }

        turret(std::string color) {
            this->color = color;
        }

        std::list<enemy> getEnemiesApproaching() {
            return this->enemiesApproaching;
        }

        double getStarTime() {
            return this->startTime;
        }

        double getCurrentTime() {
            return this->currentTime;
        }

        double getDeltaTime() {
            return this->deltaTime;
        }

        bool getIsDead() {
            return this->isDead;
        }

        bool getHasBeenShot() {
            return this->hasBeenShot;
        }

        float getScale() {
            return this->scale;
        }

        std::string getColor() {
            return this->color;
        }

        enemy* getTarget() {
            return this->target;
        }

        bool getHasTarget() {
            return this->hasTarget;
        }

        bool getIsShooting() {
            return this->isShooting;
        }

        bool getCanShoot() {
            return this->canShoot;
        }

        float getTurretX() {
            return this->turretX;
        }

        float getTurretY() {
            return this->turretY;
        }

        bool getCanPlaceTurret() {
            return canPlaceTurret;
        }

        void setStartTime(double startTime) {
            this->startTime = startTime;
        }

        void setCurrentTime(double currentTime) {
            this->currentTime = currentTime;
        }

        void setDeltaTime(double deltaTime) {
            this->deltaTime = deltaTime;
        }

        void setColor(std::string color) {
            this->color = color;
        }

        void setIsDead(bool isDead) {
            this->isDead = isDead;
        }

        void setScale(float scale) {
            this->scale = scale;
        }

        void setHasBeenShot(bool hasBeenShot) {
            this->hasBeenShot = hasBeenShot;
        }

        void addTarget(enemy& enemy) {
            this->enemiesApproaching.push_back(enemy);
        }

        void setHasTarget(bool hasTarget) {
            this->hasTarget = hasTarget;
        }

        void setTarget(enemy* target) {
            this->target = target;
        }

        void setIsShooting(bool isShooting) {
            this->isShooting = isShooting;
        }

        void setCanShoot(bool canShoot) {
            this->canShoot = canShoot;
        }

        void setCanPlaceTurret(bool canPlaceTurret) {
            this->canPlaceTurret = canPlaceTurret;
        }

        void setTurretX(float turretX) {
            this->turretX = turretX;
            projectile.setProjectileX(turretX + 100);
        }

        void setTurretY(float turretY) {
            this->turretY = turretY;
        }

        void createMesh() {
            mesh = object2D::CreateDiamond("turret", glm::vec3(0, 0, 0), 100, glm::vec3(0.5, 0.25, 1), true);
        }

        Mesh* getMesh() {
            return mesh;
        }

        glm::mat3 placeTurret(float deltaTimeSeconds) {
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(turretX, turretY);
            modelMatrix *= transform2D::Scale(scale, scale);
            return modelMatrix;


        }

        glm::mat3 shootProjectile(float deltaTimeSeconds, std::list<enemy*>& enemiesOnRow) {
            
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(projectile.getProjectileX(), turretY + 100);
            modelMatrix *= transform2D::Rotate(projectile.getAngle());

            if (!enemiesOnRow.empty()) {
                enemy* enemyShot = enemiesOnRow.front();
                hasBeenShot = true;

                if (hasBeenShot) {
                    if (glm::distance(projectile.getProjectileX(), enemyShot->getEnemyX()) < 70) {
                        enemiesOnRow.pop_front();
                        enemyShot->setIsDead(true);
                        killProjectile = true;
                    } 
                }

            }

            std::cout<<hasBeenShot<<std::endl;

            if (projectile.getProjectileX() < 2600 && (!killProjectile || hasBeenShot)) {
                projectile.setProjectileX(projectile.getProjectileX() + deltaTimeSeconds * projectileSpeed);
                projectile.setAngle(projectile.getAngle() - deltaTimeSeconds * rotationSpeed);
                projectile.setScale(1.0f);
            } else if (projectile.getProjectileX() >= 2600) {
                hasBeenShot = false;
            }

            if (killProjectile || !hasBeenShot) {
                projectile.setScale(0.0f);
                projectile.setProjectileX(turretX + 100);
                setHasTarget(false);
                killProjectile = false;
                hasBeenShot = false;
                modelMatrix *= transform2D::Scale(projectile.getScale(), projectile.getScale());
            }

            return modelMatrix;
        }
};