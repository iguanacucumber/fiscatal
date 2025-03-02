## dependencies

- [Raylib](https://github.com/raysan5/raylib)
- [Raygui](https://github.com/raysan5/raygui)

### Install those depencies

First clone this repo:

```sh
git clone --depth 1 --recurse-submodules https://github.com/iguanacucumber/fiscatal
```

```sh
paru -S --noconfirm raylib
# OR
make deps # Compile a Wayland version of raylib if needed
# Overide your system raylib !!!
```

## Build

```sh
make setup # Update build config
make # Compile
```
