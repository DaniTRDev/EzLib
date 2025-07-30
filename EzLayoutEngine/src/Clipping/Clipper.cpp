#include "Clipping/Clipper.h"

Clipper::Clipper() : m_physicalSize(), m_pos(), m_size()
{
}

Clipper::Clipper(Vec2 physicalSize, Vec2 startingPos, Vec2 startingSize)
    : m_physicalSize(physicalSize), m_pos(startingPos), m_size(startingSize)
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

bool Clipper::containsPhysically(const Vec2 &pos) const
{
    /* Save variables that are going to be used more than once. Theoretically compiler would optimize this,
     * but we can't assume it. Since this will be called VERY, VERY, VERY OFTEN anything that can be made faster is
     * used.
     */
    uint32_t thisX = m_pos.getX();
    uint32_t thisY = m_pos.getY();
    
    uint32_t otherX = pos.getX();
    uint32_t otherY = pos.getY();

    return (otherX >= thisX) && (otherY >= thisY) && (otherX <= (thisX + m_physicalSize.getX())) &&
           (otherY <= (thisY + m_physicalSize.getY()));
}

bool Clipper::resize(const Vec2 &newSize)
{
    m_size = newSize;
    return m_size <= m_physicalSize;
}

bool Clipper::resizePhysically(const Vec2 &newSize)
{
    m_physicalSize = newSize;
    return m_size <= m_physicalSize;
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
