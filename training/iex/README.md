# Contest kit for C programmers

Documentation: English in [docs/en](docs/en), Ukrainian in [docs/uk](docs/uk) (документація українською).

- [docs/en/handbook.md](docs/en/handbook.md) — the manual: algorithms needed for IEEEXtreme tasks, with C examples and references ([українською](docs/uk/handbook.md)).
- [docs/en/tasks.md](docs/en/tasks.md) / [docs/en/tasks.csv](docs/en/tasks.csv) — the 252 tasks of the IEEEXtreme practice archive (10.0–19.0) classified by topic and skill ([українською](docs/uk/tasks.md), [CSV](docs/uk/tasks.csv)).
- [lib/](lib) — helper library: 29 headers, static memory, under 100 kB in total.
- [examples/](examples) — complete solutions of classic problems with sample input and expected output.
- [tools/bundle.py](tools/bundle.py) — inlines the used headers into one file for submission.
- [tools/gen_tasks.py](tools/gen_tasks.py) + [tools/skills_uk.txt](tools/skills_uk.txt) — generate the task tables in both languages.

```sh
cc -std=c11 -O2 -Wall -I lib examples/dijkstra.c -lm -o dijkstra && ./dijkstra < examples/dijkstra.in
python3 tools/bundle.py examples/dijkstra.c > submit.c        # single file for the judge
```

Tests:

```sh
cc -std=c11 -O2 -Wall -Wextra -I lib tests/test_lib.c -lm -o test_lib && ./test_lib
sh tests/run_examples.sh
```

Regenerating the task tables (`docs/*/tasks.md`, `docs/*/tasks.csv`) after changing the data in
`tools/gen_tasks.py` (statistics, topics, English key skills) or the Ukrainian key skills in
`tools/skills_uk.txt` (one `idx|text` line per task, same `idx` as in the script) — always run both:

```sh
python3 tools/gen_tasks.py docs/en en
python3 tools/gen_tasks.py docs/uk uk
```

The handbooks (`docs/*/handbook.md`) are written by hand: when you change one, make the same change in
the other language.
