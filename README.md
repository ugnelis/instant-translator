# instant-translator [![Build Status](https://travis-ci.org/ugnelis/instant-translator.svg?branch=master)](https://travis-ci.org/ugnelis/instant-translator) [![Coverage Status](https://coveralls.io/repos/github/ugnelis/instant-translator/badge.svg?branch=master)](https://coveralls.io/github/ugnelis/instant-translator?branch=master)
Translate words and sentences instantly. Program uses various translator APIs.

## What Does the App Solve?
### Context
I am a in the country whose language I know only the basics.

### Problem
Most things are in local language. It was necessary to quickly search words or sentences quickly, not only on the WEB pages but also in various dekstop applications.

### Solution to the Problem
I have made a desktop application that can translate both web pages and dekstop-based applications and translate that text into the program by clicking on the desired button.

## Screenshot
![Screenshot](screenshot.png)

## Supported APIs
* [Google Translate API](https://cloud.google.com/translate/)

## How to Use?
### Add API key
First of all, you need to get API key for desired API. Then put it in [src/resources/configs/api.ini](src/resources/configs/api.ini) file.
Example:
``` ini
[google]
key=AsjSAXXX
format=text
```

### Translate by Pressing the Keyboard
Currently, it's made that when clipboard (copy or cut operation) is changed then the app translates the text.

## Minimum Software Requirements
* A desktop operating system that supports Qt.
* Qt 5.3+
* gcc 4.8+
