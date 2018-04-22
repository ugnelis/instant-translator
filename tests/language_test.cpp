#include <gtest/gtest.h>
#include "utils/language.h"

TEST(Language, getCode)
{
    Language language;
    ASSERT_EQ("lt", language.getCode("Lithuanian"));
}
