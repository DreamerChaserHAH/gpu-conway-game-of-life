# GPU Conway Game of Life

> An experiment on executing conway game of life using shaders inside web browser using raylib and C++ WASM

<img width="1411" alt="image" src="https://github.com/DreamerChaserHAH/gpu-conway-game-of-life/assets/109950820/673dc78a-115e-46b2-ba7e-a92ef10320bf">

## How to run

1. Import all git submodules after cloning the repo
```
git submodule update --init --recursive
```

(Make sure you have emsdk installed)
2. Compile the project with emcmake
```
mkdir build
cd build
emcmake cmake ..
emmake make
```

3. Run the project
```
npx serve
```

Visit your web browser by typing in the url
