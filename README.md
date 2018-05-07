# CLIWeather

Command line weather application using the OpenWeatherMap API to fetch, format, and display data

### Usage

CLIWeather requires you to have an OpenWeatherMap account, and thus an API key. This key is stored in userData.txt,
and the program will prompt you to input it when you first run the program (or if userData.txt otherwise does not exist).

A default location is also stored in userData.txt, and it is the location's data that will be loaded if no arguments are supplied
to the program. You will be prompted for this in the same manner if userData.txt does not exist.

Currently, CLIWeather is only available for Linux.

Example usage:

- `./cliweather` for use with default user data
- `./cliweather [CITY]` or `./cliweather [CITY,COUNTRY CODE]` for specific user data

### Dependencies

CLIWeather makes use of https://github.com/nlohmann/json for processing and parsing of JSON data.

CLIWeather uses [cUrl](https://curl.haxx.se/) to download weather data.

If you compile CLIWeather on your own, it must be compiled with C++ 11.

### Installation

Installation script coming soon!
