#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>

#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<ctime>

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "Entity.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Vector2f.hpp"

using namespace std;

#define WINDOW_WIDTH window.getWidth()
#define WINDOW_HEIGHT window.getHeight()
#define SQUARE_SIZE SDL_min(WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18)
#define BOARD_START_X (WINDOW_WIDTH - 9 * SQUARE_SIZE) * 0.5
#define BOARD_START_Y 120

int main(int argc, char *argv[])
{
    // Khởi tạo SDL, SDL_image
    if(SDL_Init(SDL_INIT_EVERYTHING) > 0) cout << "[ERROR] Failed Init: " << SDL_GetError() << endl;
    if(!IMG_Init(IMG_INIT_PNG)) cout << "[ERROR] Failed Image Init: " << SDL_GetError() << endl;
    // Tạo con trỏ chuột
    SDL_Cursor* SDL_CURSOR_ARROW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_Cursor* SDL_CURSOR_HAND = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    // Tạo số random
    srand(time(NULL));
    // Kích thước màn hình game là 540x810
    RenderWindow window("SUDOKU X VALORANT", 540, 810);
    // Ảnh của màn hình nền và nút restart
    SDL_Texture* backgroundTexture = window.loadTexture("res/images/yuki.jpg");
    SDL_Texture* restartButtonTexture = window.loadTexture("res/images/restart.png");
    // Tạo đối tượng màn hình nền và nút restart
    Entity background(Vector2f(0, 0), window.getWidth(), window.getHeight(), backgroundTexture);
    Entity restartButton(Vector2f(25, 25), 30, 30, restartButtonTexture);
    // Lấy tên của các hình ảnh tượng trưng cho các số.
    vector<SDL_Texture*> numberTextures;
    window.loadTextures("res/dev/texture_list.txt", numberTextures);
    // Tạo bảng Sudoku
    Board board(Vector2f(BOARD_START_X, BOARD_START_Y), numberTextures);
    bool isRunning = true;
    Mouse mouse; // Đối tượng trạng thái con trỏ chuột
    SDL_Event event;
    while(isRunning)
    {
        int startTick = SDL_GetTicks(); // Lấy thời gian bắt đầu
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: // thoát game nếu người chơi đóng window
                    isRunning = false;
                    break;
                // Xử lý sự kiện thay đổi size của window
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        window.updateSize();
                        background.setWidth(WINDOW_WIDTH);
                        background.setHeight(WINDOW_HEIGHT);
                        board.resize(Vector2f(BOARD_START_X, BOARD_START_Y), SQUARE_SIZE);
                    }
                    break;
                // Xử lý sự kiện click chuột
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        if(mouse.isInsideEntity(restartButton))
                        {
                            board.restart();
                        }
                        board.updateSelected(mouse);
                    }
                    break;
                // Xử lý sự kiện nhập giá trị vào ô
                case SDL_KEYDOWN:
                    board.setSelectedSquareValue(event.key.keysym.sym);
                    break;

                default:
                    break;
            }
        }
        // Đổi trạng thái của chuột trên nút restart
        if(mouse.isInsideEntity(restartButton)) SDL_SetCursor(SDL_CURSOR_HAND);
        else SDL_SetCursor(SDL_CURSOR_ARROW);

        window.clearScreen();
        window.render(background);
        window.render(restartButton);
        // Cập nhật màu của ô
        board.setAllSquareColor(255, 255, 255, 255);
        board.update(mouse);
        // Vẽ bảng Sudoku lên window
        window.render(board);
        window.display();
        int frameTicks = SDL_GetTicks() - startTick;
        if(frameTicks < 1000 / window.getRefreshRate()) SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }
    // Thoát chương trình và giải phòng SDL khi người chơi đóng cửa số
    window.clean();
    SDL_Quit();

    return 0;
}



