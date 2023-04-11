xhost +local:docker

if [[ "$(docker images -q checkers 2> /dev/null)" == "" ]]; then
  docker build -t checkers .
fi

docker run -d --rm --env="DISPLAY" --net=host checkers

