#ifndef EZLIB_CLIPPER_H
#define EZLIB_CLIPPER_H

#include "EzLibCommon.h"
#include "Primitives/Vec2.h"

/**
 * This interface provides basic functionality for a clipper.
 * A basic clipper MUST be able to:
 *  - Know its position.
 *  - Know full clipped size.
 *  - Know if an element (coords) is inside the clipped region.
 */
class Clipper
{
  public:
    
    /**
     * Creates a clipper at startingPos of size startingSize.
     * @param startingPos
     * @param startingSize
     */
    Clipper(Vec2 startingPos, Vec2 startingSize);
    
    /**
     * Returns true if given position is within this clipped region.
     * @param pos
     * @return bool
     */
    bool contains(const Vec2 &pos) const;
    
    /**
     * Tries to resize the clipped region. If current region doesn't fit on new size false will be returned.
     * Returns true other-ways.
     * @param newSize
     * @return bool
     */
    bool resize(const Vec2 &newSize);
    
    /**
     * Returns the position of the clipped region.
     * @return Vec2
     */
    const Vec2 &getPos() const;
    
    /**
     * Returns the size of the clipped region.
     * @return
     */
    const Vec2 &getSize() const;
    
    /**
     * Grows current clipped region by size.
     * @param size
     */
    void grow(const Vec2 &size);
    
    /**
     * Moves the clipped region (sets m_pos).
     * @param newPos
     */
    void move(const Vec2 &newPos);
    
  private:
    Vec2 m_pos;
    Vec2 m_size;
};

#endif // EZLIB_CLIPPER_H
