#include "Tema1.h"
#include "object2D.h"
#include "transform2D.h"
#include "enemy.h"

#include <vector>
#include <iostream>
#include <random>

using namespace std;
using namespace m1;

Tema1::Tema1()
{

}


Tema1::~Tema1()
{

}

double startTime = Engine::GetElapsedTime();

void Tema1::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    
    randomRange = 2000;
    lives = 3;
    srand(time(0));

    enemies = {
        purpleEnemy,
        orangeEnemy,
        blueEnemy,
        yellowEnemy,
        yellowEnemy2
    };

    turrets = {
        &turretOne,
        &turretTwo,
        &turretThree,
        &turretFour,
        &turretFive,
        &turretSix,
        &turretSeven,
        &turretEight,
        &turretNine
    };

    turretRenders = {
        &renderYellowTurret,
        &renderBlueTurret,
        &renderOrangeTurret,
        &renderPurpleTurret,
    };

    Mesh* heart = object2D::CreateSquares("heart", glm::vec3(0, 0, 0), 150, glm::vec3(1, 0, 0), true);
    AddMeshToList(heart);

    Mesh* selectBox = object2D::CreateSquares("selectBox", glm::vec3(0, 0 ,0), 200, glm::vec3(1, 1, 1), false);
    AddMeshToList(selectBox);

    Mesh* square = object2D::CreateSquares("square1", glm::vec3(0, 0, 0), 200, glm::vec3(1, 1, 1), true);
    AddMeshToList(square);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", glm::vec3(0, 0, 0), 750, 100, glm::vec3(1, 0, 0.25), true);
    AddMeshToList(rectangle);

    Mesh* yellowTurret = object2D::CreateDiamond("yellowTurret", glm::vec3(0, 0, 0), 100, glm::vec3(1, 1, 0), true);
    Mesh* blueTurret = object2D::CreateDiamond("blueTurret", glm::vec3(0, 0, 0), 100, glm::vec3(0, 0, 1), true);
    Mesh* purpleTurret = object2D::CreateDiamond("purpleTurret", glm::vec3(0, 0, 0), 100, glm::vec3(0.5, 0, 1.0), true);
    Mesh* orangeTurret = object2D::CreateDiamond("orangeTurret", glm::vec3(0, 0, 0), 100, glm::vec3(1, 0.5, 0), true);

    AddMeshToList(yellowTurret);
    AddMeshToList(blueTurret);
    AddMeshToList(purpleTurret);
    AddMeshToList(orangeTurret);

    purpleEnemy.createMesh("purpleEnemy", glm::vec3(0, 0, 0), 50, glm::vec3(0.5, 0, 1.0), glm::vec3(0, 0, 1), true);
    orangeEnemy.createMesh("orangeEnemy", glm::vec3(0, 0, 0), 50, glm::vec3(1.0, 0.5, 0), glm::vec3(0.5, 1, 0.5), true);
    blueEnemy.createMesh("blueEnemy", glm::vec3(0, 0, 0), 50, glm::vec3(0, 0, 1.0), glm::vec3(0.5, 0.5, 1), true);
    yellowEnemy.createMesh("yellowEnemy", glm::vec3(0, 0, 0), 50, glm::vec3(1, 1, 0), glm::vec3(0.5, 0.5, 1), true);
    yellowEnemy2.createMesh("yellowEnemy2", glm::vec3(0, 0, 0), 50, glm::vec3(1, 1, 0), glm::vec3(0.5, 0.5, 1), true);

    AddMeshToList(purpleEnemy.getMesh());
    AddMeshToList(orangeEnemy.getMesh());
    AddMeshToList(blueEnemy.getMesh());
    AddMeshToList(yellowEnemy.getMesh());
    AddMeshToList(yellowEnemy2.getMesh());

    Mesh* star = object2D::CreateStar("star", glm::vec3(0, 0, 0), 20, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(star);
}

void Tema1::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::SpawnEnemy(float deltaTimeSeconds) {

    for (enemy& enemy : enemies) {
        enemy.setCurrentTime(Engine::GetElapsedTime());
        enemy.setDeltaTime(enemy.getCurrentTime() - startTime);

        if (enemy.getDeltaTime() > 1 + rand() % randomRange && !enemy.getCanSpawnEnemy()) {
        enemy.setSpawnEnemy(true);
        enemy.setScale(1.0f);

        switch (1 + rand() % 3) {
            case 1: {
                enemiesOnFirstRow.push_back(&enemy);
                enemy.setEnemyY(125);
                break;
            }
            case 2: {
                enemiesOnSecondRow.push_back(&enemy);
                enemy.setEnemyY(400);
                break;
            }    
            case 3: {
                enemiesOnThirdRow.push_back(&enemy);
                enemy.setEnemyY(675);
                break;
            }
            default: 
                break;
            }
    }

        if (enemy.getCanSpawnEnemy()) {
            modelMatrix = enemy.spawnEnemy(deltaTimeSeconds);
            if (enemy.getScale() <= 0.0f) {
                if (enemy.getEnemyX() <= 100) {
                    lives--;
                }
                startTime = enemy.getCurrentTime();
                if (enemy.getEnemyY() == 125) {
                    enemiesOnFirstRow.remove(&enemy);
                }

                if (enemy.getEnemyY() == 400) {
                    enemiesOnSecondRow.remove(&enemy);
                }

                if (enemy.getEnemyY() == 675) {
                    enemiesOnThirdRow.remove(&enemy);
                }
            }
            RenderMesh2D(meshes[enemy.getColor()], shaders["VertexColor"], modelMatrix);

        }
    }
}

void Tema1::PlaceGameScene() {

    if (lives >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1800, 1200);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    if (lives >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(2000, 1200);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    if (lives == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(2200, 1200);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(75, 1200);
    RenderMesh2D(meshes["selectBox"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(375, 1200);
    RenderMesh2D(meshes["selectBox"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(675, 1200);
    RenderMesh2D(meshes["selectBox"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(975, 1200);
    RenderMesh2D(meshes["selectBox"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(175, 1200);
    RenderMesh2D(meshes["yellowTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(475, 1200);
    RenderMesh2D(meshes["blueTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(775, 1200);
    RenderMesh2D(meshes["orangeTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1075, 1200);
    RenderMesh2D(meshes["purpleTurret"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(175, 25);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 25);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(725, 25);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(175, 300);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 300);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(725, 300);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(175, 575);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 575);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(725, 575);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(25, 25);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
}

void Tema1::Update(float deltaTimeSeconds) {
    if (lives >= 1) {
        PlaceGameScene();
        SpawnEnemy(deltaTimeSeconds);

        for (turretRender* render : turretRenders) {
            if (render->getRender()) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(turretPosX, turretPosY);
                RenderMesh2D(meshes[render->getColor()], shaders["VertexColor"], modelMatrix);
            }
        }

        for (turret* turret : turrets) {
            if (turret->getCanPlaceTurret() && !turret->getIsDead()) {
                turret->setCurrentTime(Engine::GetElapsedTime());
                turret->setDeltaTime(turret->getCurrentTime() - turret->getStarTime());

                if (turret->getTurretY() == 25) {
                    modelMatrix = turret->placeTurret(deltaTimeSeconds);
                    RenderMesh2D(meshes[turret->getColor()], shaders["VertexColor"], modelMatrix);

                    if (!enemiesOnFirstRow.empty()) {
                        enemy* enemyShot = enemiesOnFirstRow.front();
                        if (glm::distance(enemyShot->getEnemyX(), turret->getTurretX()) < 150) {
                            turret->setIsDead(true);
                        }

                        if (turret->getDeltaTime() > 1) {
                            turret->setHasBeenShot(true);
                            turret->setStartTime(turret->getCurrentTime());
                        }
                    } 
                    
                    if (turret->getHasBeenShot()) {
                        modelMatrix = turret->shootProjectile(deltaTimeSeconds, enemiesOnFirstRow);
                        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
                    }
                }

                if (turret->getTurretY() == 300) {
                    modelMatrix = turret->placeTurret(deltaTimeSeconds);
                    RenderMesh2D(meshes[turret->getColor()], shaders["VertexColor"], modelMatrix);

                    if (!enemiesOnSecondRow.empty()) {
                        enemy* enemyShot = enemiesOnSecondRow.front();
                        if (glm::distance(enemyShot->getEnemyX(), turret->getTurretX()) < 150) {
                            turret->setIsDead(true);
                        }
                        if (turret->getDeltaTime() > 1) {
                            turret->setHasBeenShot(true);
                            turret->setStartTime(turret->getCurrentTime());
                        }
                    } 
                    
                    if (turret->getHasBeenShot()) {
                        modelMatrix = turret->shootProjectile(deltaTimeSeconds, enemiesOnSecondRow);
                        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
                    }
                }

                if (turret->getTurretY() == 575) {
                    modelMatrix = turret->placeTurret(deltaTimeSeconds);
                    RenderMesh2D(meshes[turret->getColor()], shaders["VertexColor"], modelMatrix);

                     if (!enemiesOnThirdRow.empty()) {
                        enemy* enemyShot = enemiesOnThirdRow.front();
                        if (glm::distance(enemyShot->getEnemyX(), turret->getTurretX()) < 150) {
                            turret->setIsDead(true);
                        }
                        if (turret->getDeltaTime() > 1) {
                            turret->setHasBeenShot(true);
                            turret->setStartTime(turret->getCurrentTime());
                        }
                    } 
                    
                    if (turret->getHasBeenShot()) {
                        modelMatrix = turret->shootProjectile(deltaTimeSeconds, enemiesOnThirdRow);
                        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
                    }
                }
        
            } else if (turret->getIsDead()) {
                if (turret->getScale() > 0.0f) {
                    turret->setScale(turret->getScale() - deltaTimeSeconds * 1.5f);
                } else {
                    turret->setScale(0.0f);
                }
                modelMatrix = turret->placeTurret(deltaTimeSeconds);
                RenderMesh2D(meshes[turret->getColor()], shaders["VertexColor"], modelMatrix);
            }
        }
    }
    
}

void Tema1::FrameEnd() {

}

void Tema1::OnInputUpdate(float deltaTime, int mods) {

}

void Tema1::OnKeyPress(int key, int mods) {

}

void Tema1::OnKeyRelease(int key, int mods) {

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    mouseX = (2 * mouseX);
    mouseY = ( (720 - mouseY) * 2 );

    for (turretRender* render : turretRenders) {
        if (render->getRender()) {
            turretPosX = mouseX;
            turretPosY = mouseY;
            break;
        }
    }

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    mouseX *= 2;
    mouseY = (720 - mouseY) * 2;

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT))
	{
        if (mouseY > 1200 && mouseY < 1400) {

            for (turretRender* render : turretRenders) {
                if (mouseX > 75 && mouseX < 275 && render->getColor() == "yellowTurret") {
                    render->setRender(true);
                    break;
                }

                if (mouseX > 375 && mouseX < 575 && render->getColor() == "blueTurret") {
                    render->setRender(true);
                    break;
                }

                if (mouseX > 675 && mouseX < 875 && render->getColor() == "orangeTurret") {
                    render->setRender(true);
                    break;
                }

                if (mouseX > 975 && mouseX < 1175 && render->getColor() == "purpleTurret") {
                    render->setRender(true);
                    break;
                }
            }
            
        }

        for (turretRender* render : turretRenders) {
            if (render->getRender()) {
                turretPosX = mouseX;
                turretPosY = mouseY;
                break;
            }
        }

	}

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        if (mouseY > 25 && mouseY < 225) {

            if (mouseX > 175 && mouseX < 375) {
                turretOne.setCanPlaceTurret(false);
            }

            if (mouseX > 450 && mouseX < 650) {
                turretTwo.setCanPlaceTurret(false);
            }

            if (mouseX > 725 && mouseX < 925) {
                turretThree.setCanPlaceTurret(false);
            }
        }

        if (mouseY > 300 && mouseY < 500) {
            if (mouseX > 175 && mouseX < 375) {
                turretFour.setCanPlaceTurret(false);
            }

            if (mouseX > 450 && mouseX < 650) {
                turretFive.setCanPlaceTurret(false);
            }

            if (mouseX > 725 && mouseX < 925) {
                turretSix.setCanPlaceTurret(false);
            }
        }

        if (mouseY > 575 && mouseY < 775) {
            if (mouseX > 175 && mouseX < 375) {
                turretSeven.setCanPlaceTurret(false);
            }

            if (mouseX > 450 && mouseX < 650) {
                turretEight.setCanPlaceTurret(false);
            }

            if (mouseX > 725 && mouseX < 925) {
                turretNine.setCanPlaceTurret(false);
            }
        }
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    mouseX *= 2;
    mouseY = (720 - mouseY) * 2;

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {

        for (turretRender* render : turretRenders) {
            if (render->getRender()) {
                render->setRender(false);

                if (mouseY > 25 && mouseY < 225) {
                    if (mouseX > 175 && mouseX < 375 && !turretOne.getCanPlaceTurret()) {
                        turretOne.setCanPlaceTurret(true);
                        turretOne.setTurretX(275);
                        turretOne.setTurretY(25);
                        turretOne.setColor(render->getColor());
                        turretOne.setStartTime(Engine::GetElapsedTime());
                    }

                    if (mouseX > 450 && mouseX < 650 && !turretTwo.getCanPlaceTurret()) {
                        turretTwo.setCanPlaceTurret(true);
                        turretTwo.setTurretX(550);
                        turretTwo.setTurretY(25);
                        turretTwo.setColor(render->getColor());
                        turretTwo.setStartTime(Engine::GetElapsedTime());
                    }

                    if (mouseX > 725 && mouseX < 925 && !turretThree.getCanPlaceTurret()) {
                        turretThree.setCanPlaceTurret(true);
                        turretThree.setTurretX(825);
                        turretThree.setTurretY(25);
                        turretThree.setColor(render->getColor());
                        turretThree.setStartTime(Engine::GetElapsedTime());
                    }
                }

                if (mouseY > 300 && mouseY < 500) {
                    if (mouseX > 175 && mouseX < 375 && !turretFour.getCanPlaceTurret()) {
                        turretFour.setCanPlaceTurret(true);
                        turretFour.setTurretX(275);
                        turretFour.setTurretY(300);
                        turretFour.setColor(render->getColor());
                        turretFour.setStartTime(Engine::GetElapsedTime());
                    }

                    if (mouseX > 450 && mouseX < 650 && !turretFive.getCanPlaceTurret()) {
                        turretFive.setCanPlaceTurret(true);
                        turretFive.setTurretX(550);
                        turretFive.setTurretY(300);
                        turretFive.setColor(render->getColor());
                        turretFive.setStartTime(Engine::GetElapsedTime());
                    }

                    if (mouseX > 725 && mouseX < 925 && !turretSix.getCanPlaceTurret()) {
                        turretSix.setCanPlaceTurret(true);
                        turretSix.setTurretX(825);
                        turretSix.setTurretY(300);
                        turretSix.setColor(render->getColor());
                        turretSix.setStartTime(Engine::GetElapsedTime());
                    }
                }

                if (mouseY > 575 && mouseY < 775) {
                     if (mouseX > 175 && mouseX < 375 && !turretSeven.getCanPlaceTurret()) {
                        turretSeven.setCanPlaceTurret(true);
                        turretSeven.setTurretX(275);
                        turretSeven.setTurretY(575);
                        turretSeven.setColor(render->getColor());
                        turretSeven.setStartTime(Engine::GetElapsedTime());
                    }

                    if (mouseX > 450 && mouseX < 650 && !turretEight.getCanPlaceTurret()) {
                        turretEight.setCanPlaceTurret(true);
                        turretEight.setTurretX(550);
                        turretEight.setTurretY(575);
                        turretEight.setColor(render->getColor());
                        turretEight.setStartTime(Engine::GetElapsedTime());
                    }

                    if (mouseX > 725 && mouseX < 925 && !turretNine.getCanPlaceTurret()) {
                        turretNine.setCanPlaceTurret(true);
                        turretNine.setTurretX(825);
                        turretNine.setTurretY(575);
                        turretNine.setColor(render->getColor());
                        turretNine.setStartTime(Engine::GetElapsedTime());
                    }
                }
                break;
            }
        }
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}

void Tema1::OnWindowResize(int width, int height) {
    
}
