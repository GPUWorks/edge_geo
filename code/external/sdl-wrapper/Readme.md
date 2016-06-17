### SDL Wrappers

These are my SDL2 wrappers I use.

## Useage

it fairly easy to use, but might end up being too rigid for your uses as I have stripped it down for my uses.

Its meant to be fairly close to SDL and not some deep abstaction.

```cpp
// Setting up the things.
sdl::window window(width, height, is_fullscreen, "name of window");
sdl::input input(window);
sdl::og_context ogl_context();
```

Its should to call `think()` on these objects, to allow them to update state. After that you should call `sdl::message_pump()` to allow the modules to check for messages they are interested in.

```cpp
window.think();
input.think();
ogl_context.think();

sdl::message_pump();
```

## Tested On

- Windows
- Mac

I haven't tried this on other platforms but assume it should work bar maybe setting the resolution on platforms with fixed resolutions.