#pragma once

#include "components/simple_scene.h"
#include "EntityCollection.h"
#include "components/text_renderer.h"


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

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        int randl;
        float colorR, colorG;
        float angularStep;
        EntityCollection arr;
        EntityCollection moneystars;
        float rotate;
        float size;
        int hp;
        int money;
        float hexSpawnCycle;
        float hexY;
        int toRemove;
        std::string hexColor;
        float moneySpawnCycle;
        float dist;
        int moveable;
        int x, y;
        int rx1, rx2, rx3, rx4;
        int ry1, ry2, ry3, ry4;
        int place;
        int launch;
        int cost, posX, posY;
        float time_passed;
        int attackBuff;
        int upgradeCost;
        float scaleFactor, scaleFactor2;
        float cooldown;
        int lawnmowerCost;
        int clicked;
        gfxc::TextRenderer* textRenderer;
        int displace, copy;
    };
}   // namespace m1