#include "OutLogBuffers/ConsoleOutLogBuffer.h"

ConsoleOutLogBuffer::ConsoleOutLogBuffer(std::string_view consoleTitle)
    : m_didConsoleExist(false), m_originalConsoleMode(0), m_originalConsoleOutput(0), m_consoleHandle(-1),
      m_internalBuffer(nullptr), m_consoleTitle(consoleTitle)
{
}

ConsoleOutLogBuffer::~ConsoleOutLogBuffer()
{
    bool ret = close(); // compiler happy (remove nodiscard warning). Will be optimized.
    m_didConsoleExist = false;
    m_originalConsoleMode = 0;
    m_originalConsoleOutput = 0;
    m_consoleHandle = uint64_t(-1);
}

bool ConsoleOutLogBuffer::close()
{
#ifdef EZLIB_WORKING_WINDOWS
    SetConsoleMode(HANDLE(m_consoleHandle), m_originalConsoleMode);
    SetConsoleOutputCP(m_originalConsoleOutput);
    SetConsoleTitleA(m_originalConsoleTitle);

    if (!m_didConsoleExist)
        return FreeConsole(); // Console did not exist before buffer tried opening it.
#endif

    if (m_outBuffer.is_open())
        m_outBuffer.close();

    m_internalBuffer = nullptr;
    return true;
}

bool ConsoleOutLogBuffer::open()
{
#ifdef EZLIB_WORKING_WINDOWS
    /**
     * Some environments emulate the terminal (console) and our calls to GetStdHandle and AllocConsole | AttachConsole
     * will return true but nothing will happen if we write to the classical std::ofstream("CONOUT$")
     */
    if (m_didConsoleExist = AttachConsole(GetCurrentProcessId()); !m_didConsoleExist)
        AllocConsole();

    m_consoleHandle = uint64_t(GetStdHandle(STD_OUTPUT_HANDLE));

    if (HANDLE(m_consoleHandle) == INVALID_HANDLE_VALUE)
    {
        close();
        return false;
    }

    GetConsoleMode(HANDLE(m_consoleHandle), (DWORD *)&m_originalConsoleMode);
    m_originalConsoleOutput = GetConsoleOutputCP();
    GetConsoleTitleA(m_originalConsoleTitle, sizeof(m_originalConsoleTitle));

    DWORD newMode = m_originalConsoleMode;
    newMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    newMode &= ~(ENABLE_QUICK_EDIT_MODE); // prevent clicking in terminal from suspending our main thread
    SetConsoleMode(HANDLE(m_consoleHandle), newMode);
    SetConsoleOutputCP(CP_UTF8);

    if (m_consoleTitle.empty() || !SetConsoleTitleA(m_consoleTitle.data()))
    {
        close();
        return false;
    }

    FILE *fp = nullptr; // Redirect our stdio to the console.
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

#endif

#ifdef EZLIB_DEBUG
    // If we are in debug mode, we must redirect cout directly. This handles integrated terminals not logging anything.
    m_internalBuffer = std::cout.rdbuf();
#endif
    
    std::ios::sync_with_stdio();
    m_outBuffer.open("CONOUT$", std::ios_base::out | std::ios_base::app);
    m_internalBuffer = m_outBuffer.rdbuf(); // Tell our internal buffer to use cout's.

    if (!m_internalBuffer)
    {
        close();
        return false;
    }

    return true;
}

bool ConsoleOutLogBuffer::opened() const
{
    return m_internalBuffer;
}

bool ConsoleOutLogBuffer::write(const LogMessage &message)
{
    if (!m_internalBuffer)
        return false;

    std::string messageData = message.getColouredMessage() + "\n";
    std::streamsize written = m_internalBuffer->sputn(messageData.data(), std::streamsize(messageData.length()));

    m_internalBuffer->pubsync();
    return written == std::streamsize(messageData.length());
}
