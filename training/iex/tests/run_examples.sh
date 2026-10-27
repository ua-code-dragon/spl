#!/bin/sh
# Build every example twice (with -I lib and as a bundled single file),
# run it on examples/NAME.in and compare with examples/NAME.out.
# Usage: sh tests/run_examples.sh        (from the repository root)
set -u
ROOT=$(cd "$(dirname "$0")/.." && pwd)
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
CFLAGS="-std=c11 -O2 -Wall -Wextra -pedantic"
pass=0
fail=0

for src in "$ROOT"/examples/*.c; do
    name=$(basename "$src" .c)
    [ "$name" = judge_guess ] && continue
    if ! cc $CFLAGS -I "$ROOT/lib" "$src" -lm -o "$TMP/$name" 2> "$TMP/err"; then
        echo "FAIL $name: compile"; cat "$TMP/err"; fail=$((fail + 1)); continue
    fi
    python3 "$ROOT/tools/bundle.py" "$src" > "$TMP/$name.bundled.c"
    if ! cc $CFLAGS "$TMP/$name.bundled.c" -lm -o "$TMP/$name.bundled" 2> "$TMP/err"; then
        echo "FAIL $name: bundled file does not compile"; cat "$TMP/err"; fail=$((fail + 1)); continue
    fi
    if [ "$name" = guess ]; then                      # interactive: talk to the local judge
        cc $CFLAGS "$ROOT/examples/judge_guess.c" -o "$TMP/judge"
        ok=1
        for args in "1 1" "100 1" "100 100" "1000000000000 777777777777"; do
            rm -f "$TMP/to_judge" "$TMP/to_sol"
            mkfifo "$TMP/to_judge" "$TMP/to_sol"
            "$TMP/$name" < "$TMP/to_sol" > "$TMP/to_judge" &
            # open order matters: the judge opens to_sol (write) first, which pairs
            # with the solution's read of to_sol; otherwise both block forever
            "$TMP/judge" $args > "$TMP/to_sol" < "$TMP/to_judge" 2> "$TMP/verdict" || ok=0
            wait
        done
        if [ $ok = 1 ]; then pass=$((pass + 1)); echo "ok   $name (interactive)"; else fail=$((fail + 1)); echo "FAIL $name"; cat "$TMP/verdict"; fi
        continue
    fi
    ok=1
    for bin in "$TMP/$name" "$TMP/$name.bundled"; do
        "$bin" < "$ROOT/examples/$name.in" > "$TMP/out" 2>&1
        diff -u "$ROOT/examples/$name.out" "$TMP/out" > "$TMP/diff" || { ok=0; break; }
    done
    if [ $ok = 1 ]; then
        pass=$((pass + 1)); echo "ok   $name"
    else
        fail=$((fail + 1)); echo "FAIL $name ($(basename "$bin"))"; cat "$TMP/diff"
    fi
done
echo "$pass passed, $fail failed"
[ $fail = 0 ]
