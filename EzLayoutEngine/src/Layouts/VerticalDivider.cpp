#include "Layouts/VerticalDivider.h"

const Vec2 &VerticalDivider::getSizePerElement(const Vec2 &physicalSize, uint32_t numDivisions)
{
    return Vec2(physicalSize.getX() / numDivisions, physicalSize.getY());
}

void VerticalDivider::getNextPositionForElement(uint32_t elementId, uint32_t numElements, const Vec2 &elementSize,
                                                const Vec2 &initialPos, Vec2 &pos)
{
    pos.addX(elementSize.getX());
}
