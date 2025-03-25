#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<vector>

#include "Entity.hpp"
#include "Square.hpp"
#include "Board.hpp"

using namespace std;

class RenderWindow
{
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);
    void loadTextures(const char* filePath, vector<SDL_Texture*>& o_list);
    int getRefreshRate();
    int getWidth();
    int getHeight();
    void updateSize();
    void clean();
    void clearScreen();
    void renderBox(Vector2f position, float width, float height);
    void render(Entity& entity);
    void render(Square& square);
    void render(Board& board);
    void display();
    void showMessageBox(const char* message);

private:
    SDL_Window* window;
    int windowWidth, windowHeight;
    SDL_Renderer* renderer;
};
