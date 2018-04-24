#include <gtest/gtest.h>
#include <QStringList>
#include "utils/language.h"

TEST(Language, getCode) {
    Language language;
    ASSERT_EQ("lt", language.getCode("Lithuanian"));
}

TEST(Language, getName) {
    Language language;
    ASSERT_EQ("Lithuanian", language.getName("lt"));
}

TEST(Language, getLanguages) {
    Language language;
    QStringList codesList;
    codesList.append("lt");
    codesList.append("en");
    QStringList languagesList = language.getLanguages(codesList);
    ASSERT_EQ(2, languagesList.size());
    ASSERT_EQ("Lithuanian", languagesList.at(0));
    ASSERT_EQ("English", languagesList.at(1));
}

TEST(Language, getCodes) {
    Language language;
    QStringList languagesList;
    languagesList.append("Lithuanian");
    languagesList.append("English");
    QStringList codesList = language.getCodes(languagesList);
    ASSERT_EQ(2, languagesList.size());
    ASSERT_EQ("lt", codesList.at(0));
    ASSERT_EQ("en", codesList.at(1));
}
