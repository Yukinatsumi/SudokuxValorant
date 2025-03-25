#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "Entity.hpp"
#include "Vector2f.hpp"

using namespace std;

// khởi tạo 1 Entity
Entity::Entity(Vector2f pos, float pWidth, float pHeight, SDL_Texture* tex)
    :position(pos), texture(tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 1200;
    currentFrame.h = 1200;
    width = pWidth;
    height = pHeight;
}

// Trả về vị trí entity
Vector2f& Entity::getPosition()
{
    return position;
}

// Trả về texture của đối tượng
SDL_Texture* Entity::getTexture()
{
    return texture;
}

// Trả về vùng textture được hiển thị
SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}

float Entity::getWidth()
{
    return width;
}

float Entity::getHeight()
{
    return height;
}

//Update vị trí đối tượng
void Entity::setPosition(float pX, float pY)
{
    position.x = pX;
    position.y = pY;
}

void Entity::setWidth(float pWidth)
{
    width = pWidth;
}

void Entity::setHeight(float pHeight)
{
    height = pHeight;
}
