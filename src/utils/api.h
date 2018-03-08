#ifndef INSTANT_TRANSLATOR_API_H
#define INSTANT_TRANSLATOR_API_H

#include <string>

/**
 * Interface for API classes.
 */
class API {
public:
    /**
     * Translate given input.
     * @param input input string.
     * @return output string.
     */
    virtual std::string translate(const std::string &input) const = 0;
};

#endif // INSTANT_TRANSLATOR_API_H
