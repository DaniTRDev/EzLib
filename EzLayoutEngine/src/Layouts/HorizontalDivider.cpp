#include "Layouts/HorizontalDivider.h"

const Vec2 &HorizontalDivider::getSizePerElement(const Vec2 &physicalSize, uint32_t numDivisions)
{
    return Vec2(physicalSize.getX(), physicalSize.getY() / numDivisions);
}

void HorizontalDivider::getNextPositionForElement(uint32_t elementId, uint32_t numElements, const Vec2 &elementSize,
                                                  const Vec2 &initialPos, Vec2 &pos)
{
    pos.addY(elementSize.getY());
}
