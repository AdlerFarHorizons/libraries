Modified through pull requests from a forked repo only. See __Contribute__ below.


__Organization__: Arduino/Processing-accessible library folders directly at top level. Other libraries within appropriately named top level folders, e.g. Ruby, Python, C++, etc.

__Externally Sourced Libraries:__ Copied <u>_as-is without modification_</u> except for appropriate change to the containing folder name for IDE compatibility (e.g., Arduino and other Processing-based IDEs).

__Modified Externally Sourced Libraries:__ _Do not directly modify_ an externally sourced library. Make your own copy, rename it and then modify.

* At the least, add a few maningful characters to the original name. For example, "RADIOFH" is the "RADIO" library modified for Far Horizons use, and "HMC5883L_T" is the "HMC5883L" gyro library modified by Far Horizons for Teensy.
    
* At the least, add notes of what you did at the top of a readme file or the main header file. Be sure credit to the original source is retained and licensing requirements for such credit are honored.

__Modifying Far Horizons Libraries:__ Modify existing non-externallhy sourced libraries to fix a bug or extend functionality. Be careful to keep backward compatibiity and not use excessive additional RAM. If in doubt, create a new, renamed library instead.

__New Original Library__ Name it descriptively without making it too long. <em>Search the web, esp. GitHub for the name before using it</em>. We do not want to create a library that will cause confusion in the community. If the name is already taken, add "Alt", your initials, or something to the end if nothing else. Use UPPERCASE or CamelCase styles.
    
__Library Info Entry:__ Each library, externally sourced and otherwise, must have an entry in the LibraryInfo.md file.

__Contribute:__  Fork -> clone -> commit -> push -> pull request. See:

GitHub App: <a href="https://guides.github.com/activities/forking/" target="_blank">https://guides.github.com/activities/forking/</a>

Command Line: <a href="https://help.github.com/articles/fork-a-repo" target="_blank">https://help.github.com/articles/fork-a-repo</a>.

