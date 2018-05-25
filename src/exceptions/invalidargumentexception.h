#ifndef INSTANT_TRANSLATOR_INVALIDARGUMENTEXCEPTION_H
#define INSTANT_TRANSLATOR_INVALIDARGUMENTEXCEPTION_H

#include <QException>

/**
 * Invalid argument exception.
 */
class InvalidArgumentException : public QException {
public:
    inline void raise() const { throw *this; }

    inline InvalidArgumentException *clone() const { return new InvalidArgumentException(*this); }
};

#endif //INSTANT_TRANSLATOR_INVALIDARGUMENTEXCEPTION_H
