#include <gtest/gtest.h>
#include <stdexcept>
#include <QApplication>
#include <QSettings>
#include "utils/apisettings.h"
#include "utils/appsettings.h"

TEST(AppSettingsTests, addApiSettings_addValues_True) {
    AppSettings *appSettings = new AppSettings();

    APISettings *apiSettings1 = new APISettings(appSettings, "api_1", "API 1");
    appSettings->addApiSettings(apiSettings1);
    APISettings *apiSettings2 = new APISettings(appSettings, "api_2", "API 2");
    appSettings->addApiSettings(apiSettings2);

    EXPECT_EQ(2, appSettings->getApiSettingsList().count());
    delete appSettings;
}

TEST(AppSettingsTests, setDefaultApi_setDefaultApiWhichIsNotInList_True) {
    AppSettings *appSettings = new AppSettings();

    APISettings *apiSettings = new APISettings(appSettings, "api", "API");

    EXPECT_EQ(0, appSettings->getApiSettingsList().count());

    // Set default API.
    appSettings->setDefaultApi(apiSettings);

    EXPECT_EQ(1, appSettings->getApiSettingsList().count());
    EXPECT_EQ("api", appSettings->getDefaultApi()->getName());
    delete appSettings;
}

TEST(AppSettingsTests, setDefaultApi_setDefaultApiWhichIsInList_True) {
    AppSettings *appSettings = new AppSettings();

    APISettings *apiSettings1 = new APISettings(appSettings, "api_1", "API 1");
    appSettings->addApiSettings(apiSettings1);
    APISettings *apiSettings2 = new APISettings(appSettings, "api_2", "API 2");
    appSettings->addApiSettings(apiSettings2);

    // Set default API.
    appSettings->setDefaultApi(apiSettings2);

    EXPECT_EQ(2, appSettings->getApiSettingsList().count());
    EXPECT_EQ("api_2", appSettings->getDefaultApi()->getName());
    delete appSettings;
}

TEST(AppSettingsTests, setDefaultApi_setDefaultApiByName_True) {
    AppSettings *appSettings = new AppSettings();

    APISettings *apiSettings1 = new APISettings(appSettings, "api_1", "API 1");
    appSettings->addApiSettings(apiSettings1);
    APISettings *apiSettings2 = new APISettings(appSettings, "api_2", "API 2");
    appSettings->addApiSettings(apiSettings2);

    // Set default API.
    appSettings->setDefaultApi("api_1");

    EXPECT_EQ(2, appSettings->getApiSettingsList().count());
    EXPECT_EQ("api_1", appSettings->getDefaultApi()->getName());
    delete appSettings;
}

TEST(AppSettingsTests, setDefaultApi_apiDoesNotExist_ExceptionThrown) {
    AppSettings *appSettings = new AppSettings();
    try {
        appSettings->setDefaultApi("api_1");
        FAIL();
    } catch (const std::invalid_argument &e) {
        ASSERT_EQ(std::string("API with name 'api_1' does not exist."), e.what());
    }
    delete appSettings;
}

TEST(AppSettingsTests, save_checkIfValueIsWritten_True) {
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("unit_tests");

    AppSettings *appSettings = new AppSettings();

    APISettings *apiSettings1 = new APISettings(appSettings, "api_1", "API 1");
    appSettings->addApiSettings(apiSettings1);
    APISettings *apiSettings2 = new APISettings(appSettings, "api_2", "API 2");
    appSettings->addApiSettings(apiSettings2);

    // Set default API.
    appSettings->setDefaultApi("api_1");

    // Save.
    appSettings->save();

    // Read written value.
    QSettings settings;
    QString actualDefaultApi = settings.value("default_api").toString();
    settings.clear();

    // Test.
    EXPECT_EQ("api_1", actualDefaultApi);
    delete appSettings;
}

TEST(AppSettingsTests, save_defaultApiIsNotSet_True) {
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("instant_translator");
    QApplication::setApplicationName("unit_tests");

    AppSettings *appSettings = new AppSettings();

    APISettings *apiSettings1 = new APISettings(appSettings, "api_1", "API 1");
    appSettings->addApiSettings(apiSettings1);
    APISettings *apiSettings2 = new APISettings(appSettings, "api_2", "API 2");
    appSettings->addApiSettings(apiSettings2);

    // Save.
    appSettings->save();

    // Read written value.
    QSettings settings;
    QString actualDefaultApi = settings.value("default_api").toString();

    // Test.
    EXPECT_EQ("", actualDefaultApi);
    delete appSettings;
}
