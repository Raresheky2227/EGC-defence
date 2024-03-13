#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <string>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "components/text_renderer.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    hexSpawnCycle = 600;
    moveable = -1;
    x = 500;
    y = 500;
    time_passed = 0;
    upgradeCost = 10;
    attackBuff = 0;
    cooldown = 0;
    lawnmowerCost = 10;

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 50;
    money = 5;
    hp = 3;
    moneySpawnCycle = 0;

    rx1 = 100;
    rx2 = 300;
    rx3 = 500;
    rx4 = 700;
    ry1 = 600;
    ry2 = 600;
    ry3 = 600;
    ry4 = 600;

    colorR = 0;
    colorG = 1;

    scaleFactor = 1;
    scaleFactor2 = 1;

    // Initialize angularStep
    angularStep = 0;

    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "PixeloidMono-d94EV.ttf"), 40);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, squareSide / 2, squareSide * 4, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);//end of garden
    Mesh* lawnmower = object2D::CreateRectangle("lawnmower", corner, squareSide / 2, squareSide * 4, glm::vec3(0, 0, 1), true);
    AddMeshToList(lawnmower);//blue rectangle of death

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);//turret places
    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(1, 1, 1));
    AddMeshToList(square2);//white empty square
    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide - 1, glm::vec3(colorR, colorG, 0), true);
    AddMeshToList(square3);//cooldown

    Mesh* heart = object2D::CreateHeart("heart", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(heart);//hp

    Mesh* hex1 = object2D::CreateHex("hex1", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(hex1);//yellow
    Mesh* hex2 = object2D::CreateHex("hex2", corner, squareSide, glm::vec3(0.1, 0.1, 1), true);
    AddMeshToList(hex2);//blue
    Mesh* hex3 = object2D::CreateHex("hex3", corner, squareSide, glm::vec3(0.4, 0, 0.7), true);
    AddMeshToList(hex3);//purple
    Mesh* hex4 = object2D::CreateHex("hex4", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(hex4);//orange

    Mesh* moneystar = object2D::CreateStar("moneystar", corner, 4, glm::vec3(0.7, 0.5, 0.4), true);
    AddMeshToList(moneystar);//money
    Mesh* goldenstar = object2D::CreateStar("goldenstar", corner, 3, glm::vec3(1, 0.7, 0), true);
    AddMeshToList(goldenstar);//golden
    Mesh* star1 = object2D::CreateStar("star1", corner, 1, glm::vec3(1, 1, 0), true);
    AddMeshToList(star1);//yellow
    Mesh* star2 = object2D::CreateStar("star2", corner, 1, glm::vec3(0.1, 0.1, 1), true);
    AddMeshToList(star2);//blue
    Mesh* star3 = object2D::CreateStar("star3", corner, 1, glm::vec3(0.4, 0, 0.7), true);
    AddMeshToList(star3);//purple
    Mesh* star4 = object2D::CreateStar("star4", corner, 1, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(star4);//orange

    Mesh* rhombus1 = object2D::CreateRhombus("rhombus1", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(rhombus1);//yellow
    Mesh* rhombus2 = object2D::CreateRhombus("rhombus2", corner, squareSide, glm::vec3(0.1, 0.1, 1), true);
    AddMeshToList(rhombus2);//blue
    Mesh* rhombus3 = object2D::CreateRhombus("rhombus3", corner, squareSide, glm::vec3(0.4, 0, 0.7), true);
    AddMeshToList(rhombus3);//purple
    Mesh* rhombus4 = object2D::CreateRhombus("rhombus4", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(rhombus4);//orange
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.1, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);


}


void Tema1::Update(float deltaTimeSeconds)
{
    if (cooldown > 0) 
        cooldown -= deltaTimeSeconds;
    else 
        cooldown = 0;

    time_passed += deltaTimeSeconds;
    launch = 0;
    displace = 0;
    copy = money;
    if (!hexSpawnCycle) {
        randl = rand() % 20;
        hexSpawnCycle = (600 - (rand() % (120 + (int)glm::log(time_passed + 3) * 10) + 1) - ((int)time_passed) * 2) * 2;
        if (randl < 2) {
            arr.addEntity(Entity("hex", rand() % 4, 0, 0, 3, 1280, 0, 0, 1, 0));
            arr.addEntity(Entity("hex", rand() % 4, 0, 0, 3, 1280, 1, 0, 1, 0));
            arr.addEntity(Entity("hex", rand() % 4, 0, 0, 3, 1280, 2, 0, 1, 0));
            hexSpawnCycle += 200;
        }
        else 
            arr.addEntity(Entity("hex", rand() % 4, 0, 0, 3, 1280, rand() % 3, 0, 1, 0));
    }
    hexSpawnCycle--;
    if (hexSpawnCycle < 0) hexSpawnCycle = 0;
    toRemove = -1;

    if (!moneySpawnCycle) {
        //while (moneystars.getEntityCount() > 0) {
        //    moneystars.removeEntity(0);
        //}
        if (moneystars.getEntityCount() == 0) {
            moneystars.addEntity(Entity("moneystar", 69, 0, 0, 1, rand() % 1280, rand() % 720, 0, 0, 0));
            moneystars.addEntity(Entity("moneystar", 69, 0, 0, 1, rand() % 1280, rand() % 720, 0, 0, 0));
            moneystars.addEntity(Entity("moneystar", 69, 0, 0, 1, rand() % 1280, rand() % 720, 0, 0, 0));
        }
        moneySpawnCycle = 100;
    }
    moneySpawnCycle--;

    for (int i = 0; i < arr.getEntityCount(); i++) {
        if (arr.getEntity(i).getType() == "hex") {
            modelMatrix = glm::mat3(1);
            arr.getEntity(i).setAngularMotion(arr.getEntity(i).getAngularMotion() + deltaTimeSeconds * 4);
            switch ((int)arr.getEntity(i).getY())
            {
            case 0:
                hexY = 100;
                break;
            case 1:
                hexY = 250;
                break;
            default:
                hexY = 400;
                break;
            }

            switch ((int)arr.getEntity(i).getColor())
            {
            case 0:
                hexColor = "hex1";
                break;
            case 1:
                hexColor = "hex2";
                break;
            case 2:
                hexColor = "hex3";
                break;
            default:
                hexColor = "hex4";
                break;
            }
            if (!arr.getEntity(i).getIsDying()) {
                arr.getEntity(i).setX(arr.getEntity(i).getX() - deltaTimeSeconds * (70 + time_passed) / 5 * arr.getEntity(i).getHP());
            }
            modelMatrix *= transform2D::Translate(arr.getEntity(i).getX(), hexY);
            modelMatrix *= transform2D::Scale(arr.getEntity(i).getHexDeathScaleFactor(), arr.getEntity(i).getHexDeathScaleFactor());
            modelMatrix *= transform2D::Rotate(arr.getEntity(i).getAngularMotion());
            RenderMesh2D(meshes[hexColor], shaders["VertexColor"], modelMatrix);
            if (!arr.getEntity(i).getIsDying()) {
                for (int j = 0; j < arr.getEntityCount(); j++) {
                    if (arr.getEntity(j).getType() == "star" &&
                        arr.getEntity(j).getColor() == arr.getEntity(i).getColor() &&
                        glm::abs(arr.getEntity(i).getX() - arr.getEntity(j).getX()) < 30 &&
                        arr.getEntity(i).getY() == arr.getEntity(j).getY()) {

                        arr.getEntity(i).setHP(arr.getEntity(i).getHP() - 1);
                        arr.removeEntity(j);
                    }

                    if (arr.getEntity(j).getType() == "turret" &&
                        arr.getEntity(j).getIsDying() == 0 &&
                        glm::abs(arr.getEntity(i).getX() - arr.getEntity(j).getX()) < 50 &&
                        arr.getEntity(i).getY() == arr.getEntity(j).getY()) {

                        arr.getEntity(j).setHP(0);
                        arr.getEntity(i).setHP(arr.getEntity(i).getHP() - 1);
                    }

                    if (arr.getEntity(j).getType() == "lawnmower" &&
                        glm::abs(arr.getEntity(i).getX() - arr.getEntity(j).getX()) < 60) {

                        arr.getEntity(i).setHP(0);
                        arr.getEntity(j).setHP(arr.getEntity(j).getHP() - 3);
                    }
                }
            }
            if ((arr.getEntity(i).getHP() == 0 || arr.getEntity(i).getX() < 30) && arr.getEntity(i).getIsDying() == 0) {
                arr.getEntity(i).setIsDying(1);
            }
            if (arr.getEntity(i).getIsDying() && arr.getEntity(i).getHexDeathScaleFactor() >= 0) {
                arr.getEntity(i).setHexDeathScaleFactor(arr.getEntity(i).getHexDeathScaleFactor() - 0.05);
            }
            if (arr.getEntity(i).getHexDeathScaleFactor() <= 0) {
                toRemove = i;
                if (arr.getEntity(i).getX() < 30)
                    hp--;
            }
        }
        if (arr.getEntity(i).getType() == "turret") {
            launch = 0;
            modelMatrix = glm::mat3(1);
            switch ((int)arr.getEntity(i).getColor())
            {
            case 0:
                hexColor = "rhombus1";
                break;
            case 1:
                hexColor = "rhombus2";
                break;
            case 2:
                hexColor = "rhombus3";
                break;
            default:
                hexColor = "rhombus4";
                break;
            }

            switch ((int)arr.getEntity(i).getY())
            {
            case 0:
                hexY = 100;
                break;
            case 1:
                hexY = 250;
                break;
            default:
                hexY = 400;
                break;
            }
            modelMatrix *= transform2D::Translate(arr.getEntity(i).getX(), hexY);
            for (int j = 0; j < arr.getEntityCount(); j++) {
                if (arr.getEntity(j).getType() == "hex" && arr.getEntity(j).getColor() == arr.getEntity(i).getColor() && arr.getEntity(j).getY() == arr.getEntity(i).getY()) {
                    launch = 1;
                }
            }
            if (!arr.getEntity(i).getTurretSpawnCycle() && launch)
                arr.addEntity(Entity("star", arr.getEntity(i).getColor(), 0, 0, 1, arr.getEntity(i).getX() + 40, arr.getEntity(i).getY(), 0, 0, 0));
            modelMatrix *= transform2D::Scale(arr.getEntity(i).getHexDeathScaleFactor(), arr.getEntity(i).getHexDeathScaleFactor());
            RenderMesh2D(meshes[hexColor], shaders["VertexColor"], modelMatrix);
            launch = 0;
            if (arr.getEntity(i).getIsDying() == 0 && arr.getEntity(i).getHP() == 0) {
                arr.getEntity(i).setIsDying(1);
            }
            if (arr.getEntity(i).getIsDying() && arr.getEntity(i).getHexDeathScaleFactor() >= 0) {
                arr.getEntity(i).setHexDeathScaleFactor(arr.getEntity(i).getHexDeathScaleFactor() - 0.04);
            }
            if (arr.getEntity(i).getHexDeathScaleFactor() <= 0) {
                toRemove = i;
            }
            if (!arr.getEntity(i).getTurretSpawnCycle())
                arr.getEntity(i).setTurretSpawnCycle(150 - attackBuff);
            arr.getEntity(i).setTurretSpawnCycle(arr.getEntity(i).getTurretSpawnCycle() - 1);
        }
        if (arr.getEntity(i).getType() == "star") {
            modelMatrix = glm::mat3(1);
            switch ((int)arr.getEntity(i).getColor())
            {
            case 0:
                hexColor = "star1";
                break;
            case 1:
                hexColor = "star2";
                break;
            case 2:
                hexColor = "star3";
                break;
            default:
                hexColor = "star4";
                break;
            }

            switch ((int)arr.getEntity(i).getY())
            {
            case 0:
                hexY = 100;
                break;
            case 1:
                hexY = 250;
                break;
            default:
                hexY = 400;
                break;
            }
            if (!arr.getEntity(i).getIsDying()) {
                arr.getEntity(i).setX(arr.getEntity(i).getX() + deltaTimeSeconds * 200 * (attackBuff / 30 + 1));
            }
            arr.getEntity(i).setAngularMotion(arr.getEntity(i).getAngularMotion() - deltaTimeSeconds * 4);
            modelMatrix *= transform2D::Translate(arr.getEntity(i).getX(), hexY);
            modelMatrix *= transform2D::Rotate(arr.getEntity(i).getAngularMotion());
            RenderMesh2D(meshes[hexColor], shaders["VertexColor"], modelMatrix);
        }
        if (arr.getEntity(i).getType() == "lawnmower") {
            modelMatrix = glm::mat3(1);
            if (!arr.getEntity(i).getIsDying()) {
                arr.getEntity(i).setX(arr.getEntity(i).getX() + deltaTimeSeconds * 200);
            }
            modelMatrix *= transform2D::Translate(arr.getEntity(i).getX(), arr.getEntity(i).getY());
            modelMatrix *= transform2D::Scale(arr.getEntity(i).getHexDeathScaleFactor(), arr.getEntity(i).getHexDeathScaleFactor());
            RenderMesh2D(meshes["lawnmower"], shaders["VertexColor"], modelMatrix);

            if (arr.getEntity(i).getX() > 1280) {
                arr.getEntity(i).setIsDying(1);
            }
            if (arr.getEntity(i).getIsDying() && arr.getEntity(i).getHexDeathScaleFactor() >= 0) {
                arr.getEntity(i).setHexDeathScaleFactor(arr.getEntity(i).getHexDeathScaleFactor() - 0.04);
            }
            if (arr.getEntity(i).getHexDeathScaleFactor() <= 0) {
                toRemove = i;
            }
        }
    }
    for (int i = 0; i < moneystars.getEntityCount(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(moneystars.getEntity(i).getX(), moneystars.getEntity(i).getY());
        moneystars.getEntity(i).setAngularMotion(moneystars.getEntity(i).getAngularMotion() + 4 * deltaTimeSeconds);
        modelMatrix *= transform2D::Rotate(moneystars.getEntity(i).getAngularMotion());
        RenderMesh2D(meshes["moneystar"], modelMatrix, glm::vec3(1, 0, 1));
    }

    x = 938;
    y = 565;
    modelMatrix = glm::mat3(1);
    if (!copy) {
        displace += 33;
    }
    while (copy) {
        copy /= 10;
        displace += 27;
    }
    x += displace;
    textRenderer->RenderText(to_string(money).append(" "), 920.0f, 720 - 580, 1.0f, glm::vec3(0.7, 0.5, 0.4));
        modelMatrix *= transform2D::Translate(x, y);
        RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);


    x = 950;
    y = 675;
    for (int i = 0; i < hp; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y);
        x += 120;
        modelMatrix *= transform2D::Scale(15, 15);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(820, 680);
    modelMatrix *= transform2D::Scale(scaleFactor, scaleFactor);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(820, 680);
    modelMatrix *= transform2D::Rotate(0.33);
    modelMatrix *= transform2D::Scale(2 * scaleFactor, 2 * scaleFactor);
    RenderMesh2D(meshes["goldenstar"], shaders["VertexColor"], modelMatrix);


    x = 845;
    y = 610;
    if (upgradeCost != 30) {
        if (money >= upgradeCost) {
            colorR = 0;
            colorG = 1;
        }
        else {
            colorR = 1;
            colorG = 0;
        }
        textRenderer->RenderText(to_string(upgradeCost).append(" "), 775.0f, 720 - 625, 1.0f, glm::vec3(colorR, colorG, 0));
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y);
        RenderMesh2D(meshes["moneystar"], modelMatrix, glm::vec3(colorR, colorG, 0));
    }
    else textRenderer->RenderText("MAX", 782.5f, 720 - 625, 1.0f, glm::vec3(1, 0, 0));


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(820, 540);
    modelMatrix *= transform2D::Scale(scaleFactor2, scaleFactor2);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    colorR = 1;
    colorG = 1 - cooldown / 10;

    if (!cooldown) {
        colorG = 1;
        colorR = 0;
    }
    modelMatrix *= transform2D::Translate(820, 540 - (1 - colorG) * 50);
    modelMatrix *= transform2D::Scale(scaleFactor2, scaleFactor2 * colorG);
    RenderMesh2D(meshes["square3"], modelMatrix, glm::vec3(colorR, colorG, 0));

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(820, 540);
    modelMatrix *= transform2D::Scale(0.25 * scaleFactor2, 0.245 * scaleFactor2);
    RenderMesh2D(meshes["lawnmower"], shaders["VertexColor"], modelMatrix);

    x = 845;
    y = 470;
    if (money >= lawnmowerCost) {
        colorR = 0;
        colorG = 1;
    }
    else {
        colorR = 1;
        colorG = 0;
    }
    textRenderer->RenderText(to_string(lawnmowerCost).append(" "), 775.0f, 720 - 485, 1.0f, glm::vec3(colorR, colorG, 0));
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x, y);
    RenderMesh2D(meshes["moneystar"], modelMatrix, glm::vec3(colorR, colorG, 0));



    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 250);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 600);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(rx1, ry1);
    RenderMesh2D(meshes["rhombus1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 600);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(280, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(320, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(rx2, ry2);
    RenderMesh2D(meshes["rhombus2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 600);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(480, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(520, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(rx3, ry3);
    RenderMesh2D(meshes["rhombus3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 600);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(660, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(740, 530);
    modelMatrix *= transform2D::Rotate(0.33);
    RenderMesh2D(meshes["moneystar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(rx4, ry4);
    RenderMesh2D(meshes["rhombus4"], shaders["VertexColor"], modelMatrix);




    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 100);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 250);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 400);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 100);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 250);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 400);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 100);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 250);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 400);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    if (hp <= 0) window->Close();
}


void Tema1::FrameEnd()
{
    if (toRemove != -1) {
        arr.removeEntity(toRemove);
    }
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (window->KeyHold(GLFW_KEY_SPACE)) {
        
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    switch (moveable)
    {
    case 0:
        rx1 = mouseX;
        ry1 = 720 - mouseY;
        break;
    case 1:
        rx2 = mouseX;
        ry2 = 720 - mouseY;
        break;
    case 2:
        rx3 = mouseX;
        ry3 = 720 - mouseY;
        break;
    case 3:
        rx4 = mouseX;
        ry4 = 720 - mouseY;
        break;
    default:
        break;
    }
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    clicked = 1;
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        for (int i = moneystars.getEntityCount() - 1; i >= 0; i--) {
            if (glm::abs(mouseX - moneystars.getEntity(i).getX()) < 30 && glm::abs((720 - mouseY) - moneystars.getEntity(i).getY()) < 30) {
                money++;
                moneystars.removeEntity(i);
                clicked = 0;
            }
        }
        if (glm::abs(720 - mouseY - 600) < 50 && clicked) {
            if (glm::abs(mouseX - 100) < 50)
                moveable = 0;
            if (glm::abs(mouseX - 300) < 50)
                moveable = 1;
            if (glm::abs(mouseX - 500) < 50)
                moveable = 2;
            if (glm::abs(mouseX - 700) < 50)
                moveable = 3;
        }
        if (glm::abs(720 - mouseY - 680) < 50 && glm::abs(mouseX - 820) < 50 && money >= upgradeCost && attackBuff < 120 && clicked) {
            scaleFactor = 0.5;
        }

        if (glm::abs(720 - mouseY - 540) < 50 && glm::abs(mouseX - 820) < 50 && money >= lawnmowerCost && cooldown == 0 && clicked) {
            scaleFactor2 = 0.5;
        }
    }
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for (int i = 0; i < arr.getEntityCount(); i++) {
            if (arr.getEntity(i).getType() == "turret" && glm::abs(arr.getEntity(i).getX() - mouseX) < 50 && glm::abs(720 - mouseY - (100 + 150 * arr.getEntity(i).getY())) < 50 && clicked) {
                arr.getEntity(i).setIsDying(1);
            }
        }
    }

    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    place = 1;
    posX = -1;
    posY = -1;
    if (glm::abs(720 - mouseY - 400) < 50)
        posY = 2;
    if (glm::abs(720 - mouseY - 250) < 50)
        posY = 1;
    if (glm::abs(720 - mouseY - 100) < 50)
        posY = 0;
    if (glm::abs(mouseX - 400) < 50)
        posX = 400;
    if (glm::abs(mouseX - 250) < 50)
        posX = 250;
    if (glm::abs(mouseX - 100) < 50)
        posX = 100;
    for (int i = 0; i < arr.getEntityCount(); i++) {
        if (arr.getEntity(i).getType() == "turret" && arr.getEntity(i).getX() == posX && arr.getEntity(i).getY() == posY)
            place = 0;
    }
    if (moveable == 0)
        cost = 1;
    if (moveable == 1 || moveable == 2)
        cost = 2;
    if (moveable == 3)
        cost = 3;
    if (place && money >= cost && posX > -1 && posY > -1 && moveable > -1) {
        arr.addEntity(Entity("turret", moveable, 0, 0, 1, posX, posY, 100, 1, 0));
        money -= cost;
    }
    switch (moveable)
    {
    case 0:
        rx1 = 100;
        ry1 = 600;
        break;
    case 1:
        rx2 = 300;
        ry2 = 600;
        break;
    case 2:
        rx3 = 500;
        ry3 = 600;
        break;
    case 3:
        rx4 = 700;
        ry4 = 600;
        break;
    default:
        break;
    }
    if (scaleFactor != 1) {
        scaleFactor = 1;
        money -= upgradeCost;
        attackBuff += 30;
        upgradeCost += 5;
    }

    if (scaleFactor2 != 1) {
        scaleFactor2 = 1;
        money -= lawnmowerCost;
        cooldown = 10;
        arr.addEntity(Entity("lawnmower", 0, 0, 0, 300, 0, 250, 0, 1, 0));
    }
    moveable = -1;
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
