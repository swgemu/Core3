#!/bin/bash -x
if [ ! -f ./env-run ]; then
    cp -v ./default-env ./env-run
fi

source ./env-run

docker build --no-cache --progress=plain -t ${IMAGE} .

docker image inspect --format='{{range $index, $value := .Config.Env}}{{printf "%s\n" $value}}{{end}}' ${IMAGE} | sed -e '/^$/d' > ./env-base
