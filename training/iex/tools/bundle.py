#!/usr/bin/env python3
"""Inline the lib/ headers used by a solution into one file for submission.

Contest systems accept a single source file. Write your solution with
    #include "graph.h"
and run
    python3 tools/bundle.py my_solution.c > submit.c
Every lib header is pasted once (in dependency order); system headers
such as <stdio.h> are left as they are.
"""
import pathlib
import re
import sys

LIB = pathlib.Path(__file__).resolve().parent.parent / "lib"
INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')


def expand(path, seen, out):
    for line in path.read_text().splitlines():
        m = INCLUDE.match(line)
        if m and (LIB / m.group(1)).exists():
            name = m.group(1)
            if name not in seen:
                seen.add(name)
                out.append(f"/* ===== {name} ===== */")
                expand(LIB / name, seen, out)
            continue
        out.append(line)


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: bundle.py solution.c > submit.c")
    out = []
    expand(pathlib.Path(sys.argv[1]), set(), out)
    print("\n".join(out))


if __name__ == "__main__":
    main()
