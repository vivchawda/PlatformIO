# PlatformIO for ESP32 

This repository hosts all projects for ESP32 chipset. Projects hosted here will be mainly using ESP-IDF, few with Arduino ESP support.
All are PlatformIO projects. These projects use Wemos Lolin board with OLED display, but any board with ESP32 chipset should work. 

Use the following instructions to install PlatformIO.

## Ubuntu:
### 1. Install Atom.io PPA for Ubuntu

"WebUpd8" maintains the unofficial PPA. Check here: https://launchpad.net/~webupd8team/+archive/ubuntu/atom

```
sudo add-apt-repository ppa:webupd8team/atom
```
### 2. Update package list and install Atom.io editor

```
sudo apt update; sudo apt install atom
```
If you are on an older release of Ubuntu, you might have to use `apt-get` in the command above.

### 3. Install PlatformIO-IDE for Atom
1. Launch Atom.io. By default the Welcome page should have been open, which will have a button to Install packages. If not, open Setup and launch the Package manager from there.

2. As a prerequisite, you will need `clang` on your system. This is for autocompletion of code. To install use this

```
sudo apt-get install clang
```

Search for `PlatformIO` and install the PlatformIO-IDE. This will take about 15-20 minutes on average. If you have not installed clang, or are following this guide from midway, you might get a prompt that Clang is not installed and it is needed for autocompletion. Check the section above on how to install `clang`.

Atom Dependencies should take about a year to finish installing. After it does, Atom will prompt you to re-launch the application.
There might be a few cleanup activities, during which you can have a shave and get ready for ESP32 programming.

# References
**Neil Kolban** has lots of info on ESP32. Check out his [Github](https://github.com/nkolban), his [repository](https://github.com/nkolban/esp32-snippets) on ESP32 and his [YouTube](https://www.youtube.com/channel/UChKn_BlaVrMrhEquPNI6HuQ) channel.

**pcbreflux** also has informative videos on his [YouTube](https://www.youtube.com/channel/UCvsMfEoIu_ZdBIgQVcY_AZA) channel.
