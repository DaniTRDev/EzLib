#ifndef EZLIB_VERTICALDIVIDER_H
#define EZLIB_VERTICALDIVIDER_H

#include "EzLibCommon.h"
#include "ILayoutDivider.h"

/**
 * Represents a basic divider that will divide the size on numDivision columns.
 */
class VerticalDivider : public ILayoutDivider
{
  public:
    /**
     * Returns the size per element given a physical size. Will return {physicalSize.x / numDivisions, physicalSize.y}
     * @param physicalSize
     * @param numDivisions
     * @return Vec2
     */
    const Vec2 &getSizePerElement(const Vec2 &physicalSize, uint32_t numDivisions) override;

    /**
     * Increment pos accordingly to this type of division and given the element size (previously calculated at
     * getSizePerElement). Will only increment the X coord by the size of the element.
     * @param elementId Only used for Grids, it's the only reasonable way to know where to position a grid element.
     * @param numElements Only used for Grids,it's the only reasonable way to know where to position a grid element.
     * @param elementSize
     * @param initialPos
     * @param pos
     * @return Vec2
     */
    void getNextPositionForElement(uint32_t elementId, uint32_t numElements, const Vec2 &elementSize,
                                   const Vec2 &initialPos, Vec2 &pos) override;
};

#endif // EZLIB_VERTICALDIVIDER_H
