#ifndef PIXEL_H
#define PIXEL_H
#pragma once
#include "Enviroment.h"
#include <utility>

class Pixel
{
public:
    Pixel() = default;
    Pixel(std::pair<int, int> p_xy, unsigned int p_hight, Enviroment p_env):
        m_xy(p_xy), m_hight(p_hight), m_env(p_env){}
    Enviroment getEnv() const;
    int getX() const;
    int getY() const;
    std::pair<int, int> getXy() const;
    unsigned int getHight() const;

private:
    std::pair<int, int> m_xy;
    unsigned int m_hight;
    Enviroment m_env;
};

#endif // PIXEL_H
