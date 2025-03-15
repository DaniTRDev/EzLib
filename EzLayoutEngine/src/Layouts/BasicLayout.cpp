#include "Layouts/BasicLayout.h"

BasicLayout::BasicLayout(const Clipper &clipper, const std::shared_ptr<ILayoutDivider> &divider) : m_clipper(clipper), m_divider(divider)
{}

BasicLayout::BasicLayout(const Vec2 &pos, const Vec2 &size, const std::shared_ptr<ILayoutDivider> &divider)
    : m_clipper(size, pos, size), m_divider(divider)
{}

BasicLayout::~BasicLayout()
{
    m_divider.reset();
    m_elements.clear();
}

bool BasicLayout::resize(bool resizePhysically, const Vec2 &newSize)
{
    /**
     * We must take care of the 2 sizes of the clipping region:
     *  - Physical: This is part of the viewport of the clipping region, hence why its content CAN'T be grown and must
     *      be divided equally.
     *  - Clipped: This is the full size of the clipped region, this is untouched because we are moving the PHYSICAL
     *      window when rendering.
     */

    size_t elementCount = m_elements.size();
    Vec2 currentPos = m_clipper.getPos();
    Vec2 initialPos = currentPos;
    Vec2 newElementSize = m_divider->getSizePerElement(newSize, elementCount);

    for (size_t i = 0; i < elementCount; i++)
    {
        // Resize each element and move it to its new position in the viewport.
        std::shared_ptr<ILayout> element = m_elements[i];
        element->move(currentPos);
        element->resize(true, newElementSize);

        // Calculate next position.
        m_divider->getNextPositionForElement(i, elementCount, newElementSize, initialPos, currentPos);
    }

    if (resizePhysically)
        return m_clipper.resizePhysically(newSize); // Resize clipped region.

    return m_clipper.getSize() <= m_clipper.getPhysicalSize();
}

void BasicLayout::divide(uint32_t numDivisions)
{
    size_t previousSize = m_elements.size();

    if (numDivisions == previousSize)
        return; // No resizing is needed.

    if (numDivisions < previousSize)
    {
        // Remove elements starting from the right and resize remaining.
        m_elements.erase(m_elements.begin() + previousSize - numDivisions, m_elements.end());
    }
    else
    {
        // There are more elements than we have, create the new elements with default values.
        m_elements.reserve(numDivisions); // Prevent re-allocations after every push.
        for (size_t i = 0; i < (numDivisions - previousSize); i++)
        {
            /*
             * This for will only create NEW elements, existing elements won't be touched. Both created elements and
             * existing elements will be resized with the call to resize(...) below.
             */
            std::shared_ptr<BasicLayout> layout = std::make_shared<BasicLayout>(Vec2(), Vec2(), m_divider);
            m_elements.push_back(layout);
        }
    }

    // We don't need to resize this element on its own, only its sub elements.
    resize(false, m_clipper.getPhysicalSize());
}

void BasicLayout::move(const Vec2 &pos)
{
    Vec2 currentPos = m_clipper.getPos();

    if (currentPos == pos)
        return; // No need to move.

    size_t elementCount = m_elements.size();
    Vec2 elementSize = m_divider->getSizePerElement(m_clipper.getPhysicalSize(), elementCount);
    Vec2 initialPos = currentPos;

    for (size_t i = 0; i < m_elements.size(); i++)
    {
        // Resize each element and move it to its new position in the viewport.
        std::shared_ptr<ILayout> element = m_elements[i];
        element->move(currentPos);

        m_divider->getNextPositionForElement(i, elementCount, elementSize, initialPos, currentPos);
    }

    m_clipper.move(pos); // Update clipper too.
}

void BasicLayout::setDivider(std::shared_ptr<ILayoutDivider> divider)
{
    m_divider = divider;
    resize(false, m_clipper.getPhysicalSize());
}

std::shared_ptr<ILayout> BasicLayout::getElement(size_t element)
{
    if (element >= m_elements.size())
        return nullptr;

    return m_elements[element];
}
