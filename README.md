# MINI-NON-RT (miniRT)

A small ray tracer written in **C**, built with **MiniLibX (minilibx-linux)**.  
This project parses a `.rt` scene file and renders it in a window.

## Features

### Mandatory
- Scene parsing from `.rt` files
- Basic objects: **sphere**, **plane**, **cylinder**
- Ambient + point light shading
- Camera & viewport rendering
- Basic transforms/rotation and hooks (keyboard/mouse) for interaction (depending on your implementation)

### Bonus (if built)
- Bonus renderer target (`miniRT_bonus`)
- Extra objects / textures / advanced vectors (based on the bonus sources)

## Repository layout (high level)

- `mand/` — mandatory implementation (sources + headers)
- `bonus/` — bonus implementation (sources + headers)
- `scenes_mand/` — example mandatory scenes
- `scenes_bonus/` — example bonus scenes
- `MLX/` — MiniLibX Linux (auto-cloned by the Makefile if missing)
- `minirt.c`, `minirt.h` — main entry/header (mandatory)
- `minirt_bonus.c`, `minirt_bonus.h` — main entry/header (bonus)

## Requirements

On Linux you typically need X11 development packages to build MiniLibX:
- `libx11-dev`
- `libxext-dev`
- `xorg`/X11 headers (varies by distro)

Your Makefile links with:
- `-lX11 -lXext -lm`

## Build

### Mandatory
```bash
make
```

This produces: `miniRT`

### Bonus
```bash
make bonus
```

This produces: `miniRT_bonus`

### Clean
```bash
make clean
make fclean
make re
```

## Run

```bash
./miniRT scenes_mand/<scene>.rt
```

Bonus (if built):
```bash
./miniRT_bonus scenes_bonus/<scene>.rt
```

## Scene format

This project expects **`.rt`** scene files (42 miniRT format).  
Check the `scenes_mand/` and `scenes_bonus/` folders for examples.

## Notes

- The Makefile will fetch **minilibx-linux** into `./MLX` automatically if the folder is missing/empty.
- If you run into MLX build issues, ensure your X11 dependencies are installed and you’re compiling on Linux.

## Author

- GitHub: `ibrahimesseddyq`
