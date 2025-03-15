#ifndef EZLIB_EZVEC2_H
#define EZLIB_EZVEC2_H

#include "EzLibCommon.h"

/**
 * This class represents a basic 2d vector. Since this is supposed to be a 2D renderer for an UI,
 * this vector can be represented with 2 integer components.
 *
 * This vector can be used to represent coordinates or sizes.
 */
class Vec2
{
  public:
    /**
     * Default constructor, sets coordinates to 0.
     */
    Vec2();

    /**
     * Creates the object and sets both components (m_x and m_y) to component.
     * @param component
     */
    explicit Vec2(uint32_t component);

    /**
     * Craetes the object and set components from given parameters.
     * @param x
     * @param y
     */
    Vec2(uint32_t x, uint32_t y);

    /**
     * Returns the X component.
     * @return uint32_t
     */
    uint32_t getX() const;

    /**
     * Returns the Y component.
     * @return  uint32_t
     */
    uint32_t getY() const;

    /**
     * Adds given components to the ones on this object.
     * @param x
     * @param y
     */
    void add(uint32_t x, uint32_t y);

    /**
     * Adds given x component to the ones on this object.
     * @param x
     */
    void addX(uint32_t x);

    /**
     * Adds given y component to the ones on this object.
     * @param y
     */
    void addY(uint32_t y);

    /**
     * Divides this object's components by the ones given.
     * @param x
     * @param y
     */
    void divide(uint32_t x, uint32_t y);
    
    /**
     * Divides this object's x component by the one given.
     * @param x
     */
    void divideX(uint32_t x);
    
    /**
     * Divides this object's y component by the one given.
     * @param y
     */
    void divideY(uint32_t y);
    
    /**
     * Returns the x component through an IN/OUT parameter.
     * @param y
     */
    void getX(uint32_t &x) const;

    /**
     * Returns the y component through an IN/OUT parameter.
     * @param y
     */
    void getY(uint32_t &y) const;

    /**
     * Multiplies this object's components by the ones given.
     * @param x
     * @param y
     */
    void multiply(uint32_t x, uint32_t y);
    
    /**
     * Multiplies this object's x component by the one given.
     * @param x
     */
    void multiplyX(uint32_t x);
    
    /**
     * Multiplies this object's y component by the one given.
     * @param y
     */
    void multiplyY(uint32_t y);
    
    /**
     * Subtracts given components to this object's components.
     * @param x
     * @param y
     */
    void sub(uint32_t x, uint32_t y);

    /**
     * Subtracts given x component to this object's component.
     * @param x
     */
    void subX(uint32_t x);
    
    /**
     * Subtracts given y to this object's component.
     * @param y
     */
    void subY(uint32_t y);
    
    /**
     * Updates both components to the ones given in parameters.
     * @param x
     * @param y
     */
    void update(uint32_t x, uint32_t y);

    /**
     * Updates x component to the one given in parameter.
     * @param x
     */
    void updateX(uint32_t x);

    /**
     * Updates y component to the one given in parameter.
     * @param y
     */
    void updateY(uint32_t y);

    // Operators
    /**
     * Returns true if this object is equal to other (components).
     * @param other
     * @return bool
     */
    bool operator==(const Vec2 &other) const;
    
    /**
     * Returns true if this object BOTH components are < than other components.
     * @param other
     * @return
     */
    bool operator<(const Vec2 &other) const;
    
    /**
     * Returns true if this object BOTH components are > than other components.
     * @param other
     * @return
     */
    bool operator>(const Vec2 &other) const;
    
    /**
     * Returns true if this object BOTH components are <= than other components.
     * @param other
     * @return
     */
    bool operator<=(const Vec2 &other) const;
    
    /**
     * Returns true if this object BOTH components are >= than other components.
     * @param other
     * @return
     */
    bool operator>=(const Vec2 &other) const;
    
    /**
     * Returns a new Vec2 with the addition of the components of this object and component.
     * @param component
     * @return Vec2
     */
    Vec2 operator+(const uint32_t &component) const;
    
    /**
     * Returns a new Vec2 with the addition of the components of this object and others.
     * @param other
     * @return Vec2
     */
    Vec2 operator+(const Vec2 &other) const;
    
    /**
     * Returns a new Vec2 with the substraction of the components of this object and component.
     * @param component
     * @return Vec2
     */
    Vec2 operator-(const uint32_t &component) const;
    
    /**
     * Returns a new Vec2 with the substraction of the components of this object and others.
     * @param other
     * @return Vec2
     */
    Vec2 operator-(const Vec2 &other) const;
    
    /**
     * Returns a new Vec2 with the product of the components of this object and component.
     * @param component
     * @return Vec2
     */
    Vec2 operator*(const uint32_t &component) const;
    
    /**
     * Returns a new Vec2 with the product of the components of this object and others.
     * @param other
     * @return Vec2
     */
    Vec2 operator*(const Vec2 &other) const;
    
    /**
     * Returns a new Vec2 with the division of the components of this object and component.
     * @param component
     * @return Vec2
     */
    Vec2 operator/(const uint32_t &component) const;
    
    /**
     * Returns a new Vec2 with the division of the components of this object and others.
     * @param other
     * @return Vec2
     */
    Vec2 operator/(const Vec2 &other) const;
    
    /**
     * Adds component to this object's components.
     * @param component
     */
    void operator+=(const uint32_t &component);
    
    /**
     * Adds other components to this object's components.
     * @param other
     */
    void operator+=(const Vec2 &other);
    
    /**
     * Subtracts component to this object's components.
     * @param component
     */
    void operator-=(const uint32_t &component);
    
    /**
     * Substracts other components to this object's components.
     * @param other
     */
    void operator-=(const Vec2 &other);
    
    /**
     * Multiplies this object's components by component.
     * @param component
     */
    void operator*=(const uint32_t &component);
    
    /**
     * Multiplies this object's components by other components.
     * @param other
     */
    void operator*=(const Vec2 &other);
    
    /**
     * Divides this object's components by component.
     * @param component
     */
    void operator/=(const uint32_t &component);
    
    /**
     * Divides this object's components by other components.
     * @param other
     */
    void operator/=(const Vec2 &other);
    
  private:
    uint32_t m_x;
    uint32_t m_y;
};

#endif // EZLIB_EZVEC2_H
