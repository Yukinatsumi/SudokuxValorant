
#pragma once

#include<array>
#include<vector>

#include "Vector2f.hpp"
#include "Entity.hpp"

using namespace std;

class Square : public Entity
{
public:
    Square();
    Square(Vector2f pPos, int pRow, int pColumn, int pValue, int pCorrectValue, SDL_Texture* pTexture);
    void generateRelatives(vector<Square>& squares);
    void updateAnswer(int pValue, int pCorrectValue);
    bool isAnswerFalse();
    bool isRedTexture();
    void select();
    void deselect();
    int getValue();
    int getRow();
    int getColumn();
    int getGroupRow();
    int getGroupColumn();
    array<int, 4>& getColor();
    vector<Square*> getRelatives();
    bool isSelected();
    void setTexture(SDL_Texture* pTexture);
    void setSize(float pSize);
    void setColor(int r, int g, int b, int a);
    void writePen(int pValue);
    void writePencil(int pValue);
private:
    int value, correctValue;
    int row, column, groupRow, groupColumn;
    bool selected;
    array<int, 4> color;
    array<bool, 9> pencil;
    vector<Square*> relatives;
};
