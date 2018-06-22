# instant-translator
[![Build Status](https://travis-ci.org/ugnelis/instant-translator.svg?branch=master)](https://travis-ci.org/ugnelis/instant-translator)
[![Coverage Status](https://coveralls.io/repos/github/ugnelis/instant-translator/badge.svg?branch=master)](https://coveralls.io/github/ugnelis/instant-translator?branch=master)

Translate words and sentences instantly. Program uses APIs of various translators.

## What Does the App Solve?
### Context
Currently, I live in the country whose language I only know the basics.

### Problem
Most of the things are in local language. So, it is necessary to adapt quickly by searching for the meanings of the words or the sentences in various applications (WEB based, desktop based).

### Solution to the Problem
Desktop application that is able to translate the content of web pages and dekstop-based applications in the app by clicking on the desired button.

## Screenshot
![Screenshot](screenshot.png)

## Supported APIs
* [Google Translate API](https://cloud.google.com/translate/)
* [Microsoft Translator API](https://www.microsoft.com/en-us/translator/translatorapi.aspx)

## How to Use?
### Add an API Key
First of all, you need to get API key for desired API. Then it can be added in *Settings* dialog (in menu *File*->*Settings*)

### Configuration File
Configuration file can be found in:
* In Linux: `$HOME/.config/instant_translator/instant_translator.ini`
* In Windows: `%APPDATA%\instant_translator\instant_translator.ini`

Configuration file example:
``` ini
[General]
default_api=google

[google]
key=API_KEY
text_type=text
source=lt
target=en

[microsoft]
key=API_KEY
text_type=plain
source=lt
target=en

[temp]
key=API_KEY
text_type=text
source=de
target=lt
```

### Turn On Logs
In this project gflags library isn't used. That is why environment variable `GLOG_logtostderr` has to be set in order to see logs.
```bash
GLOG_logtostderr=1 ./instant_translator
```

### Translate by Pressing the Keyboard
Currently, it's made that when clipboard (copy or cut operation) is changed then the app translates the text.

## Minimum Software Requirements
* A desktop operating system that supports Qt.
* Qt 5.3+
* gcc 4.8+
