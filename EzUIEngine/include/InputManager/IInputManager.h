#ifndef EZLIB_IINPUTMANAGER_H
#define EZLIB_IINPUTMANAGER_H

#include "EzLibCommon.h"
#include "InputData.h"

/**
 * Basic interface that defined how an InputManager should look like.
 */
class IInputManager
{
  public:
    
    virtual ~IInputManager() = default;

    /**
     * Pushes the input to a queue used by the input manager. Receiver will handle the given input when it's time.
     * @param data
     */
    virtual void pushInput(std::unique_ptr<InputData> data) = 0;
    
};

#endif // EZLIB_IINPUTMANAGER_H
