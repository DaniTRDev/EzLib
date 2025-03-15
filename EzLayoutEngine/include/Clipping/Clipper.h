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
     * Creates a clipper starting at 0 of size 0.
     */
    Clipper();

    /**
     * Creates a clipper at startingPos of virtual size startingSize and physical size physicalSize.
     * @param physicalSize
     * @param startingPos
     * @param startingSize
     */
    Clipper(Vec2 physicalSize, Vec2 startingPos, Vec2 startingSize);

    /**
     * Returns true if given position is within this clipped region.
     * @param pos
     * @return bool
     */
    bool contains(const Vec2 &pos) const;

    /**
     * Returns true if given position is within clipped region physical's box.
     * @param pos
     * @return bool
     */
    bool containsPhysically(const Vec2 &pos) const;
    
    /**
     * Resizes the clipped region. It doesn't check if given size is < current size. Returns true if clipped region
     * fits in the new size.
     * @param newSize
     * @return bool
     */
    bool resize(const Vec2 &newSize);
    
    /**
     * Resizes the physical size of the clipped region. If it was 0, nothing is done. Returns true if clipped size can
     * fit in the new physical size.
     * @param newSize
     * @return bool
     */
    bool resizePhysically(const Vec2 &newSize);
    
    /**
     * Returns the position of the clipped region.
     * @return Vec2
     */
    const Vec2 &getPos() const;

    /**
     * Returns the physical size of the clipped region.
     * @return
     */
    const Vec2 &getPhysicalSize() const;

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
    Vec2 m_physicalSize; /* Size of the viewport, unlike m_size this is not in a "virtual" space. It represents a
                          * physical size of the viewport. If set to 0, the entire clipped region is on a virtual space.
                          */
    Vec2 m_pos;
    Vec2 m_size;
};

#endif // EZLIB_CLIPPER_H
