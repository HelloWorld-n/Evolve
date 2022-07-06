# REQUIREMENTS

```shell
sudo apt-get install libsdl2-*
sudo apt-get install clang
```

# RUN

```shell
clang++ main.cpp $(pkg-config --cflags --libs sdl2)
./a.out
```
