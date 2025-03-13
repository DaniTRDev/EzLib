#include "Clipping/Clipper.h"

Clipper::Clipper(Vec2 startingPos, Vec2 startingSize) : m_pos(startingPos), m_size(startingSize)
{
}

bool Clipper::contains(const Vec2 &pos) const
{
    /* Save variables that are going to be used more than once. Theoretically compiler would optimize this,
     * but we can't assume it. Since this will be called VERY, VERY, VERY OFTEN anything that can be made faster is
     * used.
     */
    uint32_t thisX = m_pos.getX();
    uint32_t thisY = m_pos.getY();
    
    uint32_t otherX = pos.getX();
    uint32_t otherY = pos.getY();
    
    return (otherX >= thisX) && (otherY >= thisY) && (otherX <= (thisX + m_size.getX())) &&
           (otherY <= (thisY + m_size.getY()));
}

bool Clipper::resize(const Vec2 &newSize)
{
    if (newSize.getX() < m_pos.getX() || newSize.getY() < m_size.getY())
        return false;

    m_size = newSize;
    return true;
}

const Vec2 &Clipper::getPos() const
{
    return m_pos;
}

const Vec2 &Clipper::getSize() const
{
    return m_size;
}

void Clipper::grow(const Vec2 &size)
{
    m_size += size;
}

void Clipper::move(const Vec2 &newPos)
{
    m_pos = newPos;
}
