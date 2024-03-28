#pragma once

#include "components/simple_scene.h"
#include "enemy.h"
#include "turret.h"
#include "turretRender.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void SpawnEnemy(float deltaTimeSeconds);
        void PlaceGameScene();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        enemy purpleEnemy = enemy("purpleEnemy"); 
        enemy orangeEnemy = enemy("orangeEnemy"); 
        enemy blueEnemy = enemy("blueEnemy");
        enemy yellowEnemy = enemy("yellowEnemy");
        enemy yellowEnemy2 = enemy("yellowEnemy2");
        turret turretOne, turretTwo, turretThree, turretFour, turretFive, turretSix,
        turretSeven, turretEight, turretNine;
        glm::mat3 modelMatrix;
        float turretPosX, turretPosY;
        int randomRange, lives;
        std::list<enemy> enemies;
        std::list<enemy*> enemiesOnFirstRow;
        std::list<enemy*> enemiesOnSecondRow;
        std::list<enemy*> enemiesOnThirdRow;
        std::list<turret*> turrets;
        std::list<turretRender*> turretRenders;
        turretRender renderYellowTurret = turretRender(false, "yellowTurret");
        turretRender renderBlueTurret = turretRender(false, "blueTurret");
        turretRender renderOrangeTurret = turretRender(false, "orangeTurret");
        turretRender renderPurpleTurret = turretRender(false, "purpleTurret");
        
    };
}