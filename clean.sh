#!/bin/bash
find -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs -t -i rm -rf {}
