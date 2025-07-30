#include "Layouts/GridDivider.h"

const Vec2 &GridDivider::getSizePerElement(const Vec2 &physicalSize, uint32_t numDivisions)
{
    return Vec2(physicalSize.getX() / numDivisions, physicalSize.getY() / numDivisions);
}

void GridDivider::getNextPositionForElement(uint32_t elementId, uint32_t numElements, const Vec2 &elementSize,
                                            const Vec2 &initialPos, Vec2 &pos)
{
    uint32_t col = elementId % numElements;
    
    if (col < (numElements - 1))
    {
        // Next element is also in this row.
        pos.addX(elementSize.getX());
    }
    else
    {
        // Next element is on a different row. Reset X position and add Y.
        pos.updateX(initialPos.getX());
        pos.addY(elementSize.getY());
    }
}
