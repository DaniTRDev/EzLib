#ifndef EZLIB_ILAYOUT_H
#define EZLIB_ILAYOUT_H

#include "EzLibCommon.h"
#include "Clipping/Clipper.h"
#include "Primitives/Vec2.h"

/**
 * This interface provides a set of operations that should be defined for a layout element.
 *
 * IMPORTANT: Clipper is ONLY used for this element. If divide is called, each sub element will contain their own
 * clipper. This is important because the entire element will be clipped as 1, and each sub element will be clipped
 * on its own.
 *
 * When resizing layouts they will ONLY affect the PHYSICAL size of the clipped region.
 */
class ILayout
{
  public:
    
    virtual ~ILayout() = default;
    
    /**
     * Resizes layout elements to the given physical size. Returns true if layout fits on new physical size.
     * If 'resizePhysically' is set will also update this layout's physical size.
     *
     * resizePhysically will be set to false when a layout only wants to resize its element but don't want to resize
     * itself (for example because a new element has been added / removed).
     * @param resizePhysically
     * @param newSize
     * @return bool
     */
    virtual bool resize(bool resizePhysically, const Vec2 &newSize) = 0;
  
    /**
     * Divides this layout element on numDivisions sub elements. If layout is already divided, it will try to move and
     * resize them individually to fit the new size.
     *
     * WARNING: If numDivisions is < than the current division size, elements starting from the RIGHT will be deleted
     * to fit the new size. By default new elements will be using the same layout as their parent.
     * @param numDivisions
     */
    virtual void divide(uint32_t numDivisions) = 0;
    
    /**
     * Sets the new position of the layout element.
     * @param pos
     */
    virtual void move(const Vec2 &pos) = 0;
    
    /**
     * Returns the position of the element. Divide must have been called previously for correct results (not nullptr).
     * @param element
     * @return std::shared_ptr<ILayout>
     */
    virtual std::shared_ptr<ILayout> getElement(size_t element) = 0;
};

#endif // EZLIB_ILAYOUT_H
