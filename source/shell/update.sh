#!/bin/bash

pushd ../pm/
git pull
popd

cmake .
make

