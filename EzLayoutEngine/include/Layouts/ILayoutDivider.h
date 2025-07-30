#ifndef EZLIB_ILAYOUTDIVIDER_H
#define EZLIB_ILAYOUTDIVIDER_H

#include "EzLibCommon.h"
#include "Primitives/Vec2.h"

/**
 * This interface contains methods that will be used when a layout is divided. It's responsible of calculating
 * each element's new size and each position (given an initial position) for elements inside a layout.
 */
class ILayoutDivider
{
  public:
    /**
     * Returns the size per element given a physical size.
     * @param physicalSize
     * @param numDivisions
     * @return Vec2
     */
    virtual const Vec2 &getSizePerElement(const Vec2 &physicalSize, uint32_t numDivisions) = 0;

    /**
     * Increment pos accordingly to this type of division and given the element size (previously calculated at
     * getSizePerElement). For ex: Horizontal layouts will only increment the Y coord by the size of the element.
     * @param elementId Only used for Grids, it's the only reasonable way to know where to position a grid element.
     * @param numElements Only used for Grids,it's the only reasonable way to know where to position a grid element.
     * @param elementSize
     * @param initialPos
     * @param pos
     * @return Vec2
     */
    virtual void getNextPositionForElement(uint32_t elementId, uint32_t numElements, const Vec2 &elementSize,
                                           const Vec2 &initialPos, Vec2 &pos) = 0;
};

#endif // EZLIB_ILAYOUTDIVIDER_H
