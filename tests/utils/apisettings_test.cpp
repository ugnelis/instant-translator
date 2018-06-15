#include <gtest/gtest.h>
#include <stdexcept>
#include <QApplication>
#include <QSettings>
#include <QString>
#include "utils/apisettings.h"

TEST(APISettingsTests, APISettings_checkIfValuesIsNotSet_True) {
    APISettings apiSettings;
    ASSERT_EQ("", apiSettings.getName());
    ASSERT_EQ("", apiSettings.getFullName());
    ASSERT_EQ("", apiSettings.getApiKey());
    ASSERT_EQ("", apiSettings.getTextType());
    ASSERT_EQ("", apiSettings.getDefaultSourceLanguage());
    ASSERT_EQ("", apiSettings.getDefaultTargetLanguage());
}

TEST(APISettingsTests, APISettings_checkIfValuesIsSet_True) {
    APISettings apiSettings(nullptr, "google", "Google Translate API");
    ASSERT_EQ("google", apiSettings.getName());
    ASSERT_EQ("Google Translate API", apiSettings.getFullName());
    ASSERT_EQ("", apiSettings.getApiKey());
    ASSERT_EQ("", apiSettings.getTextType());
    ASSERT_EQ("", apiSettings.getDefaultSourceLanguage());
    ASSERT_EQ("", apiSettings.getDefaultTargetLanguage());
}

TEST(APISettingsTests, setName_checkIfNameIsSet_True) {
    APISettings apiSettings;
    apiSettings.setName("google");

    ASSERT_EQ("google", apiSettings.getName());
}

TEST(APISettingsTests, setFullName_checkIfFullNameIsSet_True) {
    APISettings apiSettings;
    apiSettings.setFullName("Google Translate API");

    ASSERT_EQ("Google Translate API", apiSettings.getFullName());
}

TEST(APISettingsTests, setApiKey_checkIfApiKeyIsSet_True) {
    APISettings apiSettings;
    apiSettings.setApiKey("API_KEY");

    ASSERT_EQ("API_KEY", apiSettings.getApiKey());
}

TEST(APISettingsTests, setTextType_checkIfTextTypeIsSet_True) {
    APISettings apiSettings;
    apiSettings.setTextType("text");

    ASSERT_EQ("text", apiSettings.getTextType());
}

TEST(APISettingsTests, getDefaultSourceLanguage_checkIfDefaultSourceLanguageIsSet_True) {
    APISettings apiSettings;
    apiSettings.setDefaultSourceLanguage("lt");

    ASSERT_EQ("lt", apiSettings.getDefaultSourceLanguage());
}

TEST(APISettingsTests, getDefaultTargetLanguage_checkIfDefaultTargetLanguageIsSet_True) {
    APISettings apiSettings;
    apiSettings.setDefaultTargetLanguage("en");

    ASSERT_EQ("en", apiSettings.getDefaultTargetLanguage());
}

TEST(APISettingsTests, readSettings_checkIfValuesAreRead_True) {
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("unit_tests");

    QSettings settings;

    QString name = "test";
    QString fullName = "Test";
    QString apiKey = "SOME_API_KEY";
    QString textType = "html";
    QString defaultSourceLanguage = "lv";
    QString defaultTargetLanguage = "et";
    settings.setValue(name + "/key", apiKey);
    settings.setValue(name + "/text_type", textType);
    settings.setValue(name + "/source", defaultSourceLanguage);
    settings.setValue(name + "/target", defaultTargetLanguage);

    APISettings apiSettings(nullptr, name, fullName);
    apiSettings.readSettings();

    settings.clear();

    ASSERT_EQ(name, apiSettings.getName());
    ASSERT_EQ(fullName, apiSettings.getFullName());
    ASSERT_EQ("SOME_API_KEY", apiSettings.getApiKey());
    ASSERT_EQ(textType, apiSettings.getTextType());
    ASSERT_EQ(defaultSourceLanguage, apiSettings.getDefaultSourceLanguage());
    ASSERT_EQ(defaultTargetLanguage, apiSettings.getDefaultTargetLanguage());
}

TEST(APISettingsTests, readSettings_nameIsNotSet_ExceptionThrown) {

    APISettings apiSettings;
    try {
        apiSettings.readSettings();
        FAIL();
    } catch (const std::invalid_argument &e) {
        ASSERT_EQ(std::string("API name has not been set."), e.what());
    }
}

TEST(APISettingsTests, writeSettings_checkIfValuesAreWritten_True) {
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("unit_tests");

    QSettings settings;

    QString name = "test";
    QString fullName = "Test";
    QString apiKey = "SOME_API_KEY";
    QString textType = "html";
    QString defaultSourceLanguage = "lv";
    QString defaultTargetLanguage = "et";

    APISettings apiSettings(nullptr, name, fullName);
    apiSettings.setApiKey(apiKey);
    apiSettings.setTextType(textType);
    apiSettings.setDefaultSourceLanguage(defaultSourceLanguage);
    apiSettings.setDefaultTargetLanguage(defaultTargetLanguage);
    apiSettings.writeSettings();

    QString actualApiKey = settings.value(name + "/key").toString();
    QString actualTextType = settings.value(name + "/text_type").toString();
    QString actualDefaultSourceLanguage = settings.value(name + "/source").toString();
    QString actualDefaultTargetLanguage = settings.value(name + "/target").toString();

    settings.clear();

    ASSERT_EQ(apiKey, actualApiKey);
    ASSERT_EQ(textType, actualTextType);
    ASSERT_EQ(defaultSourceLanguage, actualDefaultSourceLanguage);
    ASSERT_EQ(defaultTargetLanguage, actualDefaultTargetLanguage);
}

TEST(APISettingsTests, writeSettings_nameIstNotSet_ExceptionThrown) {

    APISettings apiSettings;
    try {
        apiSettings.writeSettings();
        FAIL();
    } catch (const std::invalid_argument &e) {
        ASSERT_EQ(std::string("API name has not been set."), e.what());
    }
}
