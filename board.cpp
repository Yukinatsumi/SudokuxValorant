#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

#include "Vector2f.hpp"
#include "Mouse.hpp"
#include "Square.hpp"
#include "Board.hpp"
using namespace std;
#define CORRECT_TEXTURE(x) squareTextures[x.getValue()]
#define WRONG_TEXTURE(x) squareTextures[x.getValue() + 9]
// lấy 1 tập game Sudoku ngẫu nhiên từ file sudoku.csv
vector<string> Board::generateProblem()
{
    const int random = (rand() % 1000) + 1; // lấy 1 trong 1000 dòng Sudoku ngẫu nhiên từ file sudoku.csv
    // đọc line đã chọn, dừng khi gặp line random
    string chosenLine;
    vector<string> chosenProblem;
    ifstream problemData("res/dev/sudoku.csv");
    for(int i = 1; getline(problemData, chosenLine); i++)
    {
        if(i == random) break;
    }
    chosenProblem.push_back(chosenLine.substr(0, 81)); // bỏ 81 dữ liệu đầu tiên vào game( màn hình bắt đầu)
    chosenProblem.push_back(chosenLine.substr(82));// 81 kí tự sau là đáp án của bài toán.
    return chosenProblem;
}

// cập nhật vị trí con trỏ đang chỉ
void Board::resize(Vector2f pStartPoint, float newSize)
{
    startPoint = pStartPoint;
    squareSize = newSize;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j].setSize(newSize);
            squares[9 * i + j].setPosition(startPoint.x + j * newSize, startPoint.y + i * newSize);
        }
    }
}

// reset sang bảng game mới
void Board::restart()
{
    const vector<string> chosenProblem = generateProblem();
    for(int i = 0; i < 81; i++)
    {
        cout << chosenProblem[1].at(i);
        if(i % 3 == 2) cout << " ";
        if(i % 9 == 8) cout << endl;
        if(i % 27 == 26) cout << endl;
    }
    cout << "=================================" << endl;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j].updateAnswer(chosenProblem[0].at(9 * i + j) - '0', chosenProblem[1].at(9 * i + j) - '0');
            squares[9 * i + j].setTexture(squareTextures[chosenProblem[0].at(9 * i + j) - '0']);
        }
    }
}

// xác định vị trí mới nhất mà người dùng nhấn chuột vào
void Board::updateSelected(Mouse& mouse)
{
    bool noSquareSelected = true;
    for(Square& s : squares)
    {
        if(mouse.isInsideEntity(s))
        {
            for(Square& other : squares) other.deselect();
            s.select();
            noSquareSelected = false;
        }
    }
    if(noSquareSelected)
    {
        for(Square& s : squares) s.deselect();
    }
}

// thay đổi màu sắc cho vị trí người chơi nhấn chuột vào
void Board::update(Mouse& mouse)
{
    for(Square& s : squares)
    {
        if(mouse.isInsideEntity(s))
        {
            for(Square* r : s.getRelatives())
            {
                if(r->getColor()[0] != 147 && r->getColor()[0] != 112) r->setColor(200, 200, 200, 255);
            }
            if(s.getColor()[0] != 147 && s.getColor()[0] != 112) s.setColor(165, 165, 165, 255);
        }
        if(s.isSelected())
        {
            for(Square* r : s.getRelatives()) r->setColor(150, 198, 249, 255);
            s.setColor(120, 163, 214, 255);
        }
        s.setTexture(!s.isRedTexture() ? CORRECT_TEXTURE(s) : WRONG_TEXTURE(s)); // kiểm tra ô
    }
}

Vector2f& Board::getStartPoint()
{
    return startPoint;
}

vector<Square>& Board::getSquares()
{
    return squares;
}

float Board::getSquareSize()
{
    return squareSize;
}
 // cập nhật màu cho tất cả các ô
void Board::setAllSquareColor(int r, int g, int b, int a)
{
    for(Square& s : squares)
    {
        s.setColor(r, g, b, a);
    }
}

// cập nhât giá trị trong ô
void Board::setSelectedSquareValue(char key)
{
    if(key == '\b' || (key >= '1' && key <= '9')) // chỉ nhập các số 1 -> 9 và dấu cách(để delete giá trị đã nhập)
    {
        for(Square& s : squares)
        {
            if(s.isSelected()) s.writePen((key == '\b') ? 0 : key - '0');
        }
    }
}

Board::Board(Vector2f pStartPoint, vector<SDL_Texture*>& pSquareTextures) // Tao man hình bắt đầu của game Sudoku
{
    const vector<string> chosenProblem = generateProblem(); // tạo 1 ván game Sudoku ngẫu nhiên từ hàm generateProblem()
    //In ra màn hình trạng thái ban đầu (9 x 9 = 81)
    for(int i = 0; i < 81; i++)
    {
        cout << chosenProblem[1].at(i);
        if(i % 3 == 2) cout << " ";
        if(i % 9 == 8) cout << endl;
        if(i % 27 == 26) cout << endl;
    }
    cout << "=================================" << endl;
    // xác định kích thước từng ô vuông
    startPoint = pStartPoint;
    squareSize = 40;
    squares.resize(81);
    // gán texture cho từng ô
    squareTextures.assign(pSquareTextures.begin(), pSquareTextures.end());
    // gán giá trị từ file excel sudoku vào các ô
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++) squares[9 * i + j] = Square(Vector2f(startPoint + Vector2f(j * squareSize, i * squareSize)), i, j, chosenProblem[0].at(9 * i + j) - '0', chosenProblem[1].at(9 * i + j) - '0', squareTextures[chosenProblem[0].at(9 * i + j) - '0']);
    }
    // thiết lạp mối quan hệ của mỗi hàng dọc với nhau, mỗi hàng ngang với nhau, mỗi vùng 3x3 theo nguyên tắc game.
    for(Square& s : squares)
    {
        s.generateRelatives(squares);
    }
}
