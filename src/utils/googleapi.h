#ifndef INSTANT_TRANSLATOR_GOOGLEAPI_H
#define INSTANT_TRANSLATOR_GOOGLEAPI_H

#include <string>
#include "api.h"

/**
 * Google Translate API implementation class.
 */
class GoogleAPI : public API {
public:
    /**
     * Constructor.
     */
    GoogleAPI();

    /**
     * Destructor.
     */
    ~GoogleAPI();

    /**
     * Translate given input.
     * @param input input string.
     * @return output string.
     */
    std::string translate(const std::string &input) const override;
};

#endif // INSTANT_TRANSLATOR_GOOGLEAPI_H
