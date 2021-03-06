# The Legend of Zelda: Oracle of Light

### By gnidmoo

- This game is a Zelda fangame, based on the *Oracle of* series on GBC

![](http://img15.hostingpics.net/pics/255623Capturedcrande20141005181925.png)

## Keys

- A : <kbd>W</kbd> (or <kbd>Z</kbd> on QWERTY keyboards)
- B : <kbd>X</kbd>
- Start : <kbd>Enter</kbd>
- Select : <kbd>Backspace</kbd>
- Directional keys: <kbd>&larr;</kbd> <kbd>&uarr;</kbd> <kbd>&darr;</kbd> <kbd>&rarr;</kbd>

## How to compile

- Dependencies:
    - [CMake](http://www.cmake.org/download/)
    - [SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
    - OpenGL >= 2.1, [glm](http://sourceforge.net/projects/ogl-math/files/latest/download?source=files)
    - [glew](http://sourceforge.net/projects/glew/files/latest/download) *(only required for Windows)*
	- _Linux users: Check your distribution repositories for packages._
- **GCC Users:** There's a [bug](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=55914) in GCC < 4.9, so the code won't compile. Please install at least GCC 4.9.
- Run `cmake .` at the root of the game folder
- Run `make`, wait, run the game and enjoy!

