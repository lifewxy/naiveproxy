#!/bin/sh

. "$COMMON/platform.sh"

set -e

# To update checksums on version change run this from the tests/ directory
# make update-cli-tests

if [ -n "$NON_DETERMINISTIC" ] || [ -z "$hasMT" ]; then
    # Skip tests if we have a non-deterministic build
    cat "$CLI_TESTS/determinism/multithread.sh.stdout.exact"
    exit 0
fi

for level in 1 3 7 19; do
    for file in $(ls files/); do
        file="files/$file"
        echo "level $level, file $file"
        zstd -T2 -q -$level $file -c | md5hash
    done
done

for file in $(ls files/); do
    file="files/$file"
    echo "level 1, long=18, file $file"
    zstd --long=18 -T2 -q -1 $file -c | md5hash
    echo "level 19, long=18, file $file"
    zstd --long=18 -T2 -q -19 $file -c | md5hash
done

for file in $(ls files/); do
    file="files/$file"
    echo "Vary number of threads on $file"
    zstd -qf -1 $file -o $file.zst.good

    zstd -qf -T1 -1 $file
    $DIFF $file.zst $file.zst.good

    zstd -qf -T2 -1 $file
    $DIFF $file.zst $file.zst.good

    zstd -qf -T4 -1 $file
    $DIFF $file.zst $file.zst.good
done
