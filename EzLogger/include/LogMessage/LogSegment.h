#ifndef EZLOGGER_LOGSEGMENT_H
#define EZLOGGER_LOGSEGMENT_H

#include "EzLibCommon.h"

struct SimpleColor
{
    uint8_t color;       // Color code.
    uint8_t modificator; // Modificator of the color.
};

/**
 * Define a specialization formatter so that std::format can properly serialize SimpleColor objects.
 */
template <> struct std::formatter<SimpleColor>
{
    /**
     * Defines the parser of the fmt string for this formatter. No extra format is needed so it just advances
     * the fmt string iterator to the end of the '{}' sentence.
     * @param ctx
     * @return An iterator to the end of the sub-format string.
     */
    constexpr auto parse(std::format_parse_context &ctx)
    {
        auto it = ctx.begin();
        while (it != ctx.end() && *it != '}')
            ++it;

        return it;
    }

    /**
     * Formats the given object into the output context.
     * @param obj
     * @param ctx
     * @return An iterator to the new end of the output string.
     */
    auto format(SimpleColor obj, std::format_context &ctx) const
    {
        if (obj.modificator == 0)
        {
            // Special "colors".
            return std::format_to(ctx.out(), "\033[{}m", obj.color);
        }
        else
        {
            // Regular colors.
            return std::format_to(ctx.out(), "\033[{}{}m", obj.modificator, obj.color);
        }
    }
};

namespace Colors
{
inline SimpleColor reset = {.color = 0, .modificator = 0};     // Regular Text Color Reset
inline SimpleColor bold = {.color = 1, .modificator = 0};      // Regular Text Bold
inline SimpleColor dim = {.color = 2, .modificator = 0};       // Regular Text Dim
inline SimpleColor italic = {.color = 3, .modificator = 0};    // Regular Text Italic
inline SimpleColor underline = {.color = 4, .modificator = 0}; // Regular Text Underline
inline SimpleColor blink = {.color = 5, .modificator = 0};     // Regular Text Blink
// inline SimpleColor unused = {.color = 6, .modificator = 0};    // UNUSED
inline SimpleColor reverse = {.color = 7, .modificator = 0}; // Regular Text Reverse
inline SimpleColor hidden = {.color = 8, .modificator = 0};  // Regular Text Hidden
inline SimpleColor strike = {.color = 9, .modificator = 0};  // Regular Text Strike

inline SimpleColor black = {.color = 0, .modificator = 3};   // Regular Text Color Black
inline SimpleColor red = {.color = 1, .modificator = 3};     // Regular Text Color Red
inline SimpleColor green = {.color = 2, .modificator = 3};   // Regular Text Color Green
inline SimpleColor yellow = {.color = 3, .modificator = 3};  // Regular Text Color Yellow
inline SimpleColor blue = {.color = 4, .modificator = 3};    // Regular Text Color Blue
inline SimpleColor magenta = {.color = 5, .modificator = 3}; // Regular Text Color Magenta
inline SimpleColor cyan = {.color = 6, .modificator = 3};    // Regular Text Color Cyan
inline SimpleColor white = {.color = 7, .modificator = 3};   // Regular Text Color White

inline SimpleColor brBlack = {.color = 0, .modificator = 9};   // Bright Text Color Black
inline SimpleColor brRed = {.color = 1, .modificator = 9};     // Bright Text Color Red
inline SimpleColor brGreen = {.color = 2, .modificator = 9};   // Bright Text Color Green
inline SimpleColor brYellow = {.color = 3, .modificator = 9};  // Bright Text Color Yellow
inline SimpleColor brBlue = {.color = 4, .modificator = 9};    // Bright Text Color Blue
inline SimpleColor brMagenta = {.color = 5, .modificator = 9}; // Bright Text Color Magenta
inline SimpleColor brCyan = {.color = 6, .modificator = 9};    // Bright Text Color Cyan
inline SimpleColor brWhite = {.color = 7, .modificator = 9};   // Bright Text Color White

inline SimpleColor bgBlack = {.color = 0, .modificator = 4};   // Regular Background Color Black
inline SimpleColor bgRed = {.color = 1, .modificator = 4};     // Regular Background Color Red
inline SimpleColor bgGreen = {.color = 2, .modificator = 4};   // Regular Background Color Green
inline SimpleColor bgYellow = {.color = 3, .modificator = 4};  // Regular Background Color Yellow
inline SimpleColor bgBlue = {.color = 4, .modificator = 4};    // Regular Background Color Blue
inline SimpleColor bgMagenta = {.color = 5, .modificator = 4}; // Regular Background Color Magenta
inline SimpleColor bgCyan = {.color = 6, .modificator = 4};    // Regular Background Color Cyan
inline SimpleColor bgWhite = {.color = 7, .modificator = 4};   // Regular Background Color White

inline SimpleColor bgBrBlack = {.color = 0, .modificator = 10};   // Bright Background Color Black
inline SimpleColor bgBrRed = {.color = 1, .modificator = 10};     // Bright Background Color Red
inline SimpleColor bgBrGreen = {.color = 2, .modificator = 10};   // Bright Background Color Green
inline SimpleColor bgBrYellow = {.color = 3, .modificator = 10};  // Bright Background Color Yellow
inline SimpleColor bgBrBlue = {.color = 4, .modificator = 10};    // Bright Background Color Blue
inline SimpleColor bgBrMagenta = {.color = 5, .modificator = 10}; // Bright Background Color Magenta
inline SimpleColor bgBrCyan = {.color = 6, .modificator = 10};    // Bright Background Color Cyan
inline SimpleColor bgBrWhite = {.color = 7, .modificator = 10};   // Bright Background Color White
} // namespace Colors

/**
 * Class that contains information about a "piece" of the LogMessage.
 */
class LogSegment
{
  public:
    /**
     * Creates the object with the given text.
     * @param text
     */
    explicit LogSegment(const std::string &text);

    /**
     * Creates the object from the given format (uses std::format).
     * @tparam FmtString
     * @tparam Args
     * @param fmt
     * @param args
     */
    template <typename... Args> LogSegment(const char *fmt, Args &&...args)
    {
        m_text = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
    }

    /**
     * Destroys the object.
     */
    ~LogSegment();

    /**
     * Appends the colors to the internal color vector.
     * @tparam Args
     * @param colors
     * @return
     */
    template <typename... Args>
        requires((std::is_same_v<std::decay_t<Args>, SimpleColor> && ...))
    LogSegment &colorize(Args &&...colors)
    {
        m_colors.reserve(m_colors.size() + sizeof...(Args));
        (m_colors.emplace_back(std::forward<Args>(colors)), ...);
        return *this;
    }

    /**
     * Returns the colors of the segment.
     * @return const std::vector<SimpleColor>&
     */
    [[nodiscard]] const std::vector<SimpleColor> &getColors() const;

    /**
     * Returns the text of the segment.
     * @return const std::string&
     */
    [[nodiscard]] const std::string &getText() const;

    /**
     * Returns the text colorized, with background ana text colors.
     * Also appends the "RESET" color code at the end.
     * @return std::string
     */
    [[nodiscard]] std::string getColorized() const;

  private:
    std::string m_text;
    std::vector<SimpleColor> m_colors;
};

#endif // EZLOGGER_LOGSEGMENT_H
