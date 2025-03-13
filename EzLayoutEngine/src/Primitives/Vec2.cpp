#include "Primitives/Vec2.h"

Vec2::Vec2() : m_x(0), m_y(0)
{
}

Vec2::Vec2(uint32_t component) : m_x(component), m_y(component)
{
}

Vec2::Vec2(uint32_t x, uint32_t y) : m_x(x), m_y(y)
{
}

uint32_t Vec2::getX() const
{
    return m_x;
}

uint32_t Vec2::getY() const
{
    return m_y;
}

void Vec2::add(uint32_t x, uint32_t y)
{
    m_x += x;
    m_y += y;
}

void Vec2::addX(uint32_t x)
{
    m_x += x;
}

void Vec2::addY(uint32_t y)
{
    m_y += y;
}

void Vec2::divide(uint32_t x, uint32_t y)
{
    m_x /= x;
    m_y /= y;
}

void Vec2::divideX(uint32_t x)
{
    m_x /= x;
}

void Vec2::divideY(uint32_t y)
{
    m_y /= y;
}

void Vec2::getX(uint32_t &x) const
{
    x = m_x;
}

void Vec2::getY(uint32_t &y) const
{
    y = m_y;
}

void Vec2::multiply(uint32_t x, uint32_t y)
{
    m_x *= x;
    m_y *= y;
}

void Vec2::multiplyX(uint32_t x)
{
    m_x *= x;
}

void Vec2::multiplyY(uint32_t y)
{
    m_y *= y;
}

void Vec2::sub(uint32_t x, uint32_t y)
{
    m_x -= x;
    m_y -= y;
}

void Vec2::subX(uint32_t x)
{
    m_x -= x;
}

void Vec2::subY(uint32_t y)
{
    m_y -= y;
}

void Vec2::update(uint32_t x, uint32_t y)
{
    m_x = x;
    m_y = y;
}

void Vec2::updateX(uint32_t x)
{
    m_x = x;
}

void Vec2::updateY(uint32_t y)
{
    m_y = y;
}

bool Vec2::operator==(const Vec2 &other) const
{
    return (m_x == other.m_x) && (m_y == other.m_y);
}

Vec2 Vec2::operator+(const uint32_t &component) const
{
    // Redefined not to add 1 extra call. Performance-wise.
    return Vec2(m_x + component, m_y + component);
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(m_x + other.m_x, m_y + other.m_y);
}

Vec2 Vec2::operator-(const uint32_t &component) const
{
    return Vec2(m_x - component, m_y - component);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(m_x - other.m_x, m_y - other.m_y);
}

Vec2 Vec2::operator*(const uint32_t &component) const
{
    return Vec2(m_x * component, m_y * component);
}

Vec2 Vec2::operator*(const Vec2 &other) const
{
    return Vec2(m_x * other.m_x, m_y * other.m_y);
}

Vec2 Vec2::operator/(const uint32_t &component) const
{
    return Vec2(m_x / component, m_y / component);
}

Vec2 Vec2::operator/(const Vec2 &other) const
{
    return Vec2(m_x / other.m_x, m_y / other.m_y);
}

void Vec2::operator+=(const uint32_t &component)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x += component;
    m_y += component;
}

void Vec2::operator+=(const Vec2 &other)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x += other.m_x;
    m_y += other.m_y;
}

void Vec2::operator-=(const uint32_t &component)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x -= component;
    m_y -= component;
}

void Vec2::operator-=(const Vec2 &other)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x -= other.m_x;
    m_y -= other.m_y;
}

void Vec2::operator*=(const uint32_t &component)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x *= component;
    m_y *= component;
}

void Vec2::operator*=(const Vec2 &other)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x *= other.m_x;
    m_y *= other.m_y;
}

void Vec2::operator/=(const uint32_t &component)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x /= component;
    m_y /= component;
}

void Vec2::operator/=(const Vec2 &other)
{
    // Redefined not to add 1 extra call. Performance-wise.
    m_x /= other.m_x;
    m_y /= other.m_y;
}
