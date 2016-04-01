#!/bin/bash
find $(pwd) -name "main" | xargs -t -i rm -rf {}
find $(pwd) -name "a.out" | xargs -t -i rm -rf {}
