#include "Mouse.hpp"

// Lưu tạo độ con trỏ chuột
Mouse::Mouse()
{
    SDL_GetMouseState(&x, &y);
}

// Cập nhật hoành độ con trỏ chuột
int Mouse::getX()
{
    SDL_GetMouseState(&x, &y);
    return x;
}

// Cập nhật tung độ con trỏ chuột
int Mouse::getY()
{
    SDL_GetMouseState(&x, &y);
    return y;
}

// Lưu tọa độ con trỏ chuột ở dạng vector
Vector2f Mouse::getPos()
{
    SDL_GetMouseState(&x, &y);
    return Vector2f(x, y);
}

// Kiểm tra vị trí con trỏ chuột
bool Mouse::isInsideEntity(Entity& entity)
{
    Vector2f currentPos = getPos();
    return
    (currentPos.x >= entity.getPosition().x && currentPos.x <= entity.getPosition().x + entity.getWidth()
    && currentPos.y >= entity.getPosition().y && currentPos.y <= entity.getPosition().y + entity.getHeight());
}
