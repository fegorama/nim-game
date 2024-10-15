# Nim Game
Nim is a mathematical game of strategy in which two players take turns removing (or "nimming") objects from distinct heaps or piles.

https://en.wikipedia.org/wiki/Nim

## Build and run
mkdir ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build . --verbose && ./src/nim-game

## Install
mkdir ./build
cd ./build
cmake .. && sudo cmake --build . --target install --verbose

## Run
nim-game

