#include<iostream>
#include<vector>

#include "Vector2f.hpp"
#include "Square.hpp"

//Tạo đối tượng Square vị trí (0, 0) và ko có texture
Square::Square()
    : Entity(Vector2f(0, 0), 0, 0, nullptr)
{}

Square::Square(Vector2f pPos, int pRow, int pColumn, int pValue, int pCorrectValue, SDL_Texture* pTexture)
    : Entity(pPos, 40, 40, pTexture)
{
    row = pRow;
    groupRow = row / 3;
    column = pColumn;
    groupColumn = column / 3;
    value = pValue;
    correctValue = pCorrectValue;
    selected = false;
    color.fill(255);
    pencil.fill(false);
}

// Nguyên tắc game
void Square::generateRelatives(std::vector<Square>& squares)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(!(i == row && j == column))
            {
                if(i == row || j == column) relatives.push_back(&squares[9 * i + j]);
                else if(squares[9 * i + j].getGroupRow() == groupRow && squares[9 * i + j].getGroupColumn() == groupColumn) relatives.push_back(&squares[9 * i + j]);
            }
        }
    }
    for(int k = 0; k < 81; k++)
    {
        if(value != 0 && squares[k].getValue() == value)
        {
            relatives.push_back(&squares[k]);
        }
    }
}

// Cập nhật giá trị điền vào ô
void Square::updateAnswer(int pValue, int pCorrectValue)
{
    value = pValue;
    correctValue = pCorrectValue;
}

// Kiểm tra đáp án sai
bool Square::isAnswerFalse()
{
    return (value != 0) && (value != correctValue);
}

// Kiểm tra ô sai(do sai nguyên tắc game)
bool Square::isRedTexture()
{
    bool isRelativeFalse = false;
    for(Square* r : relatives)
    {
        if(r->isAnswerFalse() && r->getValue() == value) isRelativeFalse = true;
    }
    return (value != 0) && (isAnswerFalse() || isRelativeFalse);
}

void Square::select()
{
    selected = true;
}

void Square::deselect()
{
    selected = false;
}

int Square::getValue()
{
    return value;
}

int Square::getRow()
{
    return row;
}

int Square::getColumn()
{
    return column;
}

int Square::getGroupRow()
{
    return groupRow;
}

int Square::getGroupColumn()
{
    return groupColumn;
}

std::array<int, 4>& Square::getColor()
{
    return color;
}

std::vector<Square*> Square::getRelatives()
{
    return relatives;
}

bool Square::isSelected()
{
    return selected;
}

void Square::setTexture(SDL_Texture* pTexture)
{
    texture = pTexture;
}

void Square::setSize(float pSize)
{
    width = pSize;
    height = pSize;
}

// Cập nhật màu ô Sudoku
void Square::setColor(int r, int g, int b, int a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

void Square::writePen(int pValue)
{
    pencil.fill(false);
    value = pValue;
}
