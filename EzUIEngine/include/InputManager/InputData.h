#ifndef EZLIB_INPUTDATA_H
#define EZLIB_INPUTDATA_H

#include "EzLibCommon.h"

/**
 * Represents a key of the keyboard OR mouse.
 */
enum class InputKey : uint16_t
{
    InputKey_Begin = 0, // Thanks to ImGui for this idea. Allows iterating over the enumeration easily.

    // Arrows
    Left,
    Right,
    Up,
    Down,

    // Near-numpad keys.
    PageUp,
    PageDown,
    Home,
    End,
    Insert,
    Delete, // Also called Supr in some keyboards.

    // Special keys on the keyboard.
    Space,      // Big bar
    Enter,      // Not needed explanation.
    Escape,     // ^^
    LeftCtrl,   // ^^
    LeftShift,  // ^^
    LeftAlt,    // ^^
    LeftSuper,  // On some keyboards this is either FN or WINDOWS.
    RightCtrl,  // Not needed explanation.
    RightShift, // ^^
    RightAlt,   // ^^
    RightSuper, // On some keyboards this is either WINDOWS or FN (the contrary to LeftSuper).
    Menu,       // Menu key, opens dialog when pressed on files (in the case of Windows).

    // Numpad keys.
    Numpad_Number_0,
    Numpad_Number_1,
    Numpad_Number_2,
    Numpad_Number_3,
    Numpad_Number_4,
    Numpad_Number_5,
    Numpad_Number_6,
    Numpad_Number_7,
    Numpad_Number_8,
    Numpad_Number_9,
    
    // Regular keyboard letters.
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    
    // Regular keyboard numbers.
    Number_0,
    Number_1,
    Number_2,
    Number_3,
    Number_4,
    Number_5,
    Number_6,
    Number_7,
    Number_8,
    Number_9,

    InputKey_End // Same as ""_Begin
};

/**
 * Basic structure that defines input data, will be used by InputManager.
 */
struct InputData
{
};

#endif // EZLIB_INPUTDATA_H
