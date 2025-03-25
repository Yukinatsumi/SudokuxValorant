#pragma once

#include<vector>

#include "Vector2f.hpp"
#include "Mouse.hpp"
#include "Square.hpp"

using namespace std;

class Board
{
public:
    Board(Vector2f pStartPoint, vector<SDL_Texture*>& pSquareTextures);
    void resize(Vector2f pStartPoint, float newSize);
    void restart();
    void updateSelected(Mouse& mouse);
    void update(Mouse& mouse);
    Vector2f& getStartPoint();
    vector<Square>& getSquares();
    float getSquareSize();
    void setAllSquareColor(int r, int g, int b, int a);
    void setSelectedSquareValue(char key);
private:
    vector<SDL_Texture*> squareTextures;
    vector<Square> squares;
    Vector2f startPoint;
    float squareSize;
    vector<string> generateProblem();
};
