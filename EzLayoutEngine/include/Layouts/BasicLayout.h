#ifndef EZLIB_BASICLAYOUT_H
#define EZLIB_BASICLAYOUT_H

#include "EzLibCommon.h"
#include "ILayout.h"
#include "ILayoutDivider.h"

/**
 * This class implements common operations for all layout objects.
 */
class BasicLayout : public ILayout
{
  public:
    /**
     * Creates a basic layout with the given clipper. Divider can't be null.
     * @param clipper
     * @param divider
     */
    explicit BasicLayout(const Clipper &clipper, const std::shared_ptr<ILayoutDivider> &divider);

    /**
     * Creates a basic layout, initializing the clipper with given pos and initial physical size. Divider can't be
     * null.
     * @param pos
     * @param size
     * @param divider
     */
    BasicLayout(const Vec2 &pos, const Vec2 &size, const std::shared_ptr<ILayoutDivider> &divider);

    /**
     * Destroys this object and frees resources.
     */
    ~BasicLayout() override;
    
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
    bool resize(bool resizePhysically, const Vec2 &newSize) override;

    /**
     * Divides this layout element on numDivisions sub elements. If layout is already divided, it will try to move and
     * resize them individually to fit the new size.
     *
     * WARNING: If numDivisions is < than the current division size, elements starting from the RIGHT will be deleted
     * to fit the new size. By default new elements will be using the same layout as their parent.
     *
     * If numDivisions > that the current division size, new elements will be added and everything will be resized.
     * @param numDivisions
     */
    void divide(uint32_t numDivisions) override;

    /**
     * Sets the new position of the layout element.
     * @param pos
     */
    void move(const Vec2 &pos) override;

    /**
     * Sets a new divider for the layout, WARNING WILL RESIZE ELEMENTS!
     * @param divider
     */
    void setDivider(std::shared_ptr<ILayoutDivider> divider);
    
    /**
     * Returns the position of the element. Divide must have been called previously for correct results (not nullptr).
     * @param element
     * @return std::shared_ptr<ILayout>
     */
    std::shared_ptr<ILayout> getElement(size_t element) override;

  private:
    Clipper m_clipper; // Used to control clip region of this element.
    std::shared_ptr<ILayoutDivider> m_divider;
    std::vector<std::shared_ptr<ILayout>> m_elements; // Elements contained on this layout.
};

#endif // EZLIB_BASICLAYOUT_H
