# Snake AI

![Build-Test workflow (cmake)](https://github.com/Dpbm/snake-ai/actions/workflows/cmake-build-test.yml/badge.svg)
![Docker Hub publish](https://github.com/Dpbm/snake-ai/actions/workflows/dockerhub.yml/badge.svg)
![GHRC publish](https://github.com/Dpbm/snake-ai/actions/workflows/ghrc.yml/badge.svg)

For this project, my idea was to explore some algorithms, such as genetic algorithms and Qubo, and 
technologies, like C++, and develop something I've always wanted to, all from scratch! 

The urge to build a snake game AI came after I watched some YouTube videos, which inspired me to create something different and just for fun, some of them are listed bellow:

[![Artificial Intelligence in Google's Dinosaur (English Sub)](https://img.youtube.com/vi/P7XHzqZjXQs/0.jpg)](https://youtu.be/P7XHzqZjXQs)
[![Rede Neural aprendendo a jogar o jogo da cobrinha (SNAKE)
](https://img.youtube.com/vi/awz1ghokP3k/0.jpg)](https://youtu.be/awz1ghokP3k)
[![MarI/O - Machine Learning for Video Games](https://img.youtube.com/vi/qv6UVOQ0F44/0.jpg)](https://youtu.be/qv6UVOQ0F44)


## Technologies

The Technologies used were:

* [git](https://git-scm.com/)
* [SDL2](https://www.libsdl.org/)
* [C++](https://isocpp.org/)
* [make](https://www.gnu.org/software/make/)/[cmake](https://cmake.org/)
* [googletest (ctest)](https://google.github.io/googletest/)
* [sh](https://www.gnu.org/software/bash/)
* [Github actions](https://docs.github.com/en/actions)
* [python 3.10](https://www.python.org/) (used to test the QUBO model)
* [pygame](https://www.pygame.org/)
* [docker](https://www.docker.com/)
* [docker compose](https://docs.docker.com/compose/)

## Usage

All the following usage ways are focused on `Ubuntu` based distros, so some steps may differ for different OS. Remember to check the tools documentation for your system. 

## Docker

The simplest way to run it, is by using Docker. 

First pull the image:
```bash
docker pull dpbm32/snake-ai

# or using the GHRC version
docker pull ghcr.io/dpbm/snake-ai:latest
```

Then you must grant access to your `XDisplay`.

```bash
xhost +local:root

# remeber revoking access after using it
xhost -local:root
```

Also, setup a docker volume for the neural network weights output.

```bash
docker volume create weights-out
```

Finally run the image:

```bash
docker run -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
           -v /path/to/your/weights/input/folder/optional/:/snake/weights_input/ \
           --mount source=weights-out,target=/snake/weights_output/ \
           -e DISPLAY=$DISPLAY \
           -e WPATH=/snake/weights_output/ \
           snake-ai
```

## Docker build local

Another way to do that is build the image by yourself. To do that run:

```bash
docker build -t snake-ai .
```

Then follow the steps after the `docker pull` from the [#docker section](#docker).

## Docker compose

Finally, There's a [compose file](compose.yaml) in the project directory that you can use to orchestrate the image requirements. 

After creating a volume and giving the `XDisplay` permissions, run:

```bash
docker compose up
```

## Dev Build

To build the and run the project, you must the following tools and libraries installed:

* [git](https://git-scm.com/)
* [SDL2](https://www.libsdl.org/)
* [C++](https://isocpp.org/)
* [make](https://www.gnu.org/software/make/)
* [cmake](https://cmake.org/)
* [sh](https://www.gnu.org/software/bash/)

Then, clone the project and run the `compilation script`:

```bash
git clone https://github.com/Dpbm/snake-ai
cd ./snake-ai
chmod +x ./compile.sh ./clean.sh
./clean.sh && ./compile.sh main.cpp
```

Finally, run the game:

```bash
LC_NUMERIC="C" ./build/snake

# or, if you want to set a different path to the output weights
LC_NUMERIC="C" WPATH="/path/to/save/the/weights/" ./build/snake

```


### Tests

In case you want to run the tests by your own, do the following:

```bash
cd build
ctest
```

### Qubo test

Finally, inside this repo, there's a subproject made in python to test the Qubo model and how we could use it to play snake game.
To access this piece of software:

Install the dependencies: 

```bash
pip install -r requirements.txt #use python>=3.10

#or using conda (recommended)
conda env create -f environment.yml
conda activate snake-ai
```

and run:

```bash
python ./pygame-qubo-test/main.py
```