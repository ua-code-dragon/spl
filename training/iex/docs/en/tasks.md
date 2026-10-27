# IEEEXtreme task archive by topic

All 252 tasks of the [IEEEXtreme practice community](https://csacademy.com/ieeextreme-practice/tasks/) on CS Academy (IEEEXtreme 10.0 to 19.0), grouped by the algorithmic skill they need.

How the topics were assigned:
- **tags**: CS Academy has its own topic tags for 63 of the tasks (11.0: 30, 13.0: 4, 14.0: 24, 15.0: 4, 18.0: 1); those are used as they are.
- **stmt**: every other task was classified by reading its statement. Treat these as a strong hint, not a guarantee: a task can need more than its listed skills.

Columns: **Ed.** edition, **Diff.** CS Academy difficulty (where given), **Solved** = accepted / tried users in the practice archive (higher = easier in practice), **Lib** = the headers of [`lib/`](../../lib) that cover the skill. The same data as a spreadsheet: [tasks.csv](tasks.csv).

Note: some 19.0 tasks show very small numbers (for example 6/8) because only a few people have tried them in the archive.

## Summary

| Topic | Primary | Total | What to know | Library |
|---|---:|---:|---|---|
| [Implementation and simulation](#implementation-and-simulation) | 17 | 23 | careful reading, simulation, ASCII output, edge cases | grid.h, io.h |
| [Strings](#strings) | 18 | 30 | ciphers, KMP, hashing, palindromes (Manacher), tries, Aho-Corasick, brackets | strutil.h, trie.h, hashmap.h |
| [Text and data processing](#text-and-data-processing) | 7 | 10 | IEEE Xplore tasks: parse JSON/CSV/XML-like input, group, sort, aggregate | hashmap.h, sort.h |
| [Reverse engineering and emulation](#reverse-engineering-and-emulation) | 6 | 8 | guess a hidden function from examples, emulate code / number formats | bits.h |
| [Math and number theory](#math-and-number-theory) | 25 | 47 | modular arithmetic, primes, gcd, fast exponentiation, formulas | numtheory.h, matrix.h, bignum.h |
| [Combinatorics and probability](#combinatorics-and-probability) | 17 | 32 | counting mod p, binomials, inclusion-exclusion, expectation, generating functions | combin.h, fft.h, dp.h |
| [Greedy and sorting](#greedy-and-sorting) | 19 | 29 | sort + greedy choice, exchange argument, intervals, heaps | sort.h, heap.h |
| [Binary search](#binary-search) | 3 | 11 | lower/upper bound, binary search on the answer | search.h |
| [Dynamic programming](#dynamic-programming) | 24 | 48 | knapsack, LIS/LCS, grid DP, bitmask DP, tree DP, counting DP | dp.h |
| [Graphs](#graphs) | 30 | 38 | BFS/DFS, shortest paths, MST, topological sort, SCC, bridges, matching, flow | graph.h, paths.h, flow.h, grid.h |
| [Trees](#trees) | 23 | 27 | rooting, subtree sizes, LCA, diameter, tree DP, HLD, Euler tour | tree.h |
| [Data structures](#data-structures) | 19 | 37 | prefix sums, Fenwick, segment tree (lazy), sparse table, DSU, monotonic stack/queue, hashing | fenwick.h, segtree.h, sparse.h, dsu.h, linear.h |
| [Geometry](#geometry) | 11 | 14 | cross product, polygon area, convex hull, point in polygon, Pick, sweep line | geom.h |
| [Game theory](#game-theory) | 4 | 7 | win/lose DP, minimax, Nim, Sprague-Grundy | game.h |
| [Interactive](#interactive) | 6 | 6 | query protocol, flushing, adaptive strategies | interactive.h |
| [Brute force and backtracking](#brute-force-and-backtracking) | 9 | 13 | enumeration, pruning, meet in the middle, state search | util.h |
| [Bit manipulation](#bit-manipulation) | 7 | 18 | masks, XOR tricks, subsets, XOR basis | bits.h |
| [Constructive](#constructive) | 7 | 13 | build any object that satisfies the rules; small cases first | - |

*Primary* counts each task once (by its main topic); *Total* counts every topic a task touches.

### By edition

| Topic | 10.0 | 11.0 | 12.0 | 13.0 | 14.0 | 15.0 | 16.0 | 17.0 | 18.0 | 19.0 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Implementation and simulation | 1 | 3 | 3 |  | 3 | 4 | 5 | 2 | 1 | 1 |
| Strings | 2 | 1 | 3 | 3 | 3 | 3 | 5 | 6 | 1 | 3 |
| Text and data processing |  |  | 1 | 1 | 1 | 2 | 1 | 2 | 1 | 1 |
| Reverse engineering and emulation |  |  | 2 |  | 1 | 1 |  | 2 | 1 | 1 |
| Math and number theory | 3 | 7 | 3 | 5 | 5 | 5 | 4 | 5 | 4 | 6 |
| Combinatorics and probability | 1 |  | 2 | 3 |  | 5 | 4 | 6 | 7 | 4 |
| Greedy and sorting | 3 | 3 | 2 | 6 | 2 | 2 | 3 |  | 4 | 4 |
| Binary search | 1 | 2 | 3 |  | 1 | 1 |  |  |  | 3 |
| Dynamic programming | 1 | 11 | 5 | 4 | 3 | 5 | 3 | 5 | 6 | 5 |
| Graphs | 3 | 8 | 3 | 2 | 4 | 2 | 5 | 5 | 2 | 4 |
| Trees |  | 1 | 3 | 4 | 2 | 4 | 2 | 3 | 4 | 4 |
| Data structures | 1 | 4 | 1 | 5 | 4 | 4 | 4 | 4 | 4 | 6 |
| Geometry | 1 | 1 |  | 2 | 2 | 3 | 1 | 1 | 3 |  |
| Game theory |  | 2 | 2 |  |  |  | 1 |  | 1 | 1 |
| Interactive |  | 1 | 3 | 1 |  | 1 |  |  |  |  |
| Brute force and backtracking | 2 | 2 | 1 | 1 | 2 |  | 2 |  | 3 |  |
| Bit manipulation | 1 | 3 | 2 | 1 | 2 | 2 | 1 | 1 | 1 | 4 |
| Constructive |  | 1 |  | 3 | 2 | 1 | 1 |  | 2 | 3 |
| **Tasks** | 13 | 30 | 24 | 27 | 26 | 25 | 25 | 25 | 28 | 29 |

### Suggested first tasks

Per topic, the three tasks most people solved in the practice archive (primary topic, at least 50 attempts):

- **Implementation and simulation**: [Memory Management](https://csacademy.com/ieeextreme-practice/task/memory-management/) (84%), [Game of Life 2020](https://csacademy.com/ieeextreme-practice/task/conway-gameoflife/) (75%), [Pizza Cutter](https://csacademy.com/ieeextreme-practice/task/pizza-cutter/) (71%)
- **Strings**: [Gaius Letters](https://csacademy.com/ieeextreme-practice/task/gaius-letters/) (83%), [Caesar Redux](https://csacademy.com/ieeextreme-practice/task/caesar_redux/) (55%), [Programmer's Poem](https://csacademy.com/ieeextreme-practice/task/Poetry/) (42%)
- **Text and data processing**: [Application Abuse](https://csacademy.com/ieeextreme-practice/task/application-abuse/) (59%), [Xplore](https://csacademy.com/ieeextreme-practice/task/xplore/) (57%), [Impact Factor](https://csacademy.com/ieeextreme-practice/task/impact-factor/) (42%)
- **Reverse engineering and emulation**: [Restaurant Cipher](https://csacademy.com/ieeextreme-practice/task/resaturant_cipher/) (85%), [IEEE754 Emulator](https://csacademy.com/ieeextreme-practice/task/ieee754-emulator/) (30%), [Magic Spell](https://csacademy.com/ieeextreme-practice/task/magic-spell/) (19%)
- **Math and number theory**: [Secure Elliptic Curve Point Addition](https://csacademy.com/ieeextreme-practice/task/secure-elliptic-curve-point-addition/) (95%), [Mosaic Decoration I](https://csacademy.com/ieeextreme-practice/task/mosaic1/) (86%), [Rigged Dice](https://csacademy.com/ieeextreme-practice/task/rigged-dice/) (62%)
- **Combinatorics and probability**: [N-Palindromes](https://csacademy.com/ieeextreme-practice/task/n-palindromes/) (60%), [Do you know Expectation?](https://csacademy.com/ieeextreme-practice/task/do-you-know-expectation/) (38%), [Alfa Pool](https://csacademy.com/ieeextreme-practice/task/alfa-pool/) (30%)
- **Greedy and sorting**: [Magic Wands](https://csacademy.com/ieeextreme-practice/task/magic-wands/) (91%), [Dog Walking](https://csacademy.com/ieeextreme-practice/task/dog-walking/) (83%), [Blackgate Penitentiary](https://csacademy.com/ieeextreme-practice/task/8761fb7efefcf1d890df1d8d91cae241/) (80%)
- **Binary search**: [The Twin Occurrence Quest](https://csacademy.com/ieeextreme-practice/task/the-twin-occurrence-quest/) (78%), [Crafting Wooden Tables](https://csacademy.com/ieeextreme-practice/task/crafting-wooden-tables/) (19%)
- **Dynamic programming**: [Painter's Dilemma](https://csacademy.com/ieeextreme-practice/task/painters-dilemma/) (82%), [BeetleBag](https://csacademy.com/ieeextreme-practice/task/ed8629419f140a5a2c923b049aba1224/) (64%), [Visit Egypt](https://csacademy.com/ieeextreme-practice/task/visit-egypt/) (57%)
- **Graphs**: [King's Order](https://csacademy.com/ieeextreme-practice/task/kings-order/) (89%), [Vangelis the Batbear and the Bubbles challenge](https://csacademy.com/ieeextreme-practice/task/979a09a0cd8c4e98dd0a690f39a55bd2/) (66%), [Invisible Ghosts](https://csacademy.com/ieeextreme-practice/task/invisible-ghosts/) (62%)
- **Trees**: [White knights and Black warriors](https://csacademy.com/ieeextreme-practice/task/white-knights-and-black-warriors/) (85%), [Icarus](https://csacademy.com/ieeextreme-practice/task/icarus/) (67%), [Rumour](https://csacademy.com/ieeextreme-practice/task/9ca8fafd184f553a903734761546a224/) (62%)
- **Data structures**: [Baker's Competition](https://csacademy.com/ieeextreme-practice/task/bakers-competition/) (40%), [Protecting the Hive](https://csacademy.com/ieeextreme-practice/task/protecting-the-hive/) (33%), [Long Lines](https://csacademy.com/ieeextreme-practice/task/long_lines/) (30%)
- **Geometry**: [Ellipse Art](https://csacademy.com/ieeextreme-practice/task/ellipse-art/) (72%), [Aeneas' cryptographic disc (4th c. B.C.)](https://csacademy.com/ieeextreme-practice/task/d48ada9a7213299f1b24b22b2fb9443f/) (67%), [Stick](https://csacademy.com/ieeextreme-practice/task/stick/) (45%)
- **Game theory**: [Stones](https://csacademy.com/ieeextreme-practice/task/stones/) (13%), [The Gold-diggers](https://csacademy.com/ieeextreme-practice/task/the-gold-diggers/) (9%), [Queen](https://csacademy.com/ieeextreme-practice/task/queen/) (6%)
- **Interactive**: [Troll Coder](https://csacademy.com/ieeextreme-practice/task/troll-coder/) (68%), [Concentration Game](https://csacademy.com/ieeextreme-practice/task/concentration-game/) (54%), [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) (14%)
- **Brute force and backtracking**: [Xtreme Fake Coins](https://csacademy.com/ieeextreme-practice/task/xtreme-fake-coins/) (57%), [Checkers Challenge](https://csacademy.com/ieeextreme-practice/task/checkers-challenge/) (56%), [Octopuses with Watches](https://csacademy.com/ieeextreme-practice/task/59d4aae501fe4ced9ffbf3737acd18a2/) (43%)
- **Bit manipulation**: [Bit Soccer](https://csacademy.com/ieeextreme-practice/task/bit-soccer/) (52%), [Shailesh's Triplet](https://csacademy.com/ieeextreme-practice/task/shailesh-s-triplet/) (51%), [RecXor](https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/) (50%)
- **Constructive**: [Hack the coach!](https://csacademy.com/ieeextreme-practice/task/hack-the-coach/) (69%), [Making a Tangram](https://csacademy.com/ieeextreme-practice/task/making-tangram/) (33%), [Maximum Sum](https://csacademy.com/ieeextreme-practice/task/04dfa70efd936271ae191cb1a97eb876/) (17%)

## Implementation and simulation

*careful reading, simulation, ASCII output, edge cases.* Library: grid.h, io.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 10 | [Memory Management](https://csacademy.com/ieeextreme-practice/task/memory-management/) |  | 119/141 | simulate FIFO and LRU page replacement |  | linear.h hashmap.h | stmt |
| 14 | [Game of Life 2020](https://csacademy.com/ieeextreme-practice/task/conway-gameoflife/) | EASY | 600/803 | Game of Life simulation |  | grid.h | tags |
| 16 | [Pizza Cutter](https://csacademy.com/ieeextreme-practice/task/pizza-cutter/) |  | 2528/3563 | normalise angles modulo 180, count distinct cuts | Geometry | sort.h | stmt |
| 11 | [Running Up Stairs](https://csacademy.com/ieeextreme-practice/task/96c8b1313edd72abf600facb0a14dbab/) | EASY | 1539/2739 | Fibonacci-like recurrence with big integers | Math | bignum.h | tags |
| 17 | [War Games](https://csacademy.com/ieeextreme-practice/task/war_games/) |  | 1422/2850 | card game with queues, draw detection by repeated states |  | linear.h hashmap.h | stmt |
| 16 | [What Language Am I Speaking?](https://csacademy.com/ieeextreme-practice/task/what-language-am-i-speaking/) |  | 464/1109 | evaluate a decision tree on character presence | Strings |  | stmt |
| 16 | [ASCII Dancer](https://csacademy.com/ieeextreme-practice/task/ascii-dancer/) |  | 921/2772 | simulate commands, print ASCII art |  |  | stmt |
| 15 | [Image Similarity](https://csacademy.com/ieeextreme-practice/task/image-similarity/) | EASY | 304/943 | all rotations/flips and translations, count overlapping pixels | Geometry | grid.h | stmt |
| 15 | [Word Search](https://csacademy.com/ieeextreme-practice/task/wordsearch/) | EASY | 183/594 | find words in 8 directions (trie for many words) | Strings | trie.h | stmt |
| 11 | [Game of Life](https://csacademy.com/ieeextreme-practice/task/d12a7784af1a3d3f6d88601c81a4bb81/) | MEDIUM | 205/1000 | cellular automaton on a torus (simulation) |  | grid.h | tags |
| 11 | [Elementary](https://csacademy.com/ieeextreme-practice/task/c787255968c972c653677a52599ecc2f/) | HARDEST | 71/470 | ad hoc word encoding, DP over the ways to split the word | DP |  | tags |
| 12 | [Infinite snakes and ladders](https://csacademy.com/ieeextreme-practice/task/infinite-snakes-and-ladders/) |  | 108/830 | board game simulation (snakes and ladders) |  |  | stmt |
| 16 | [Robot versus Fan](https://csacademy.com/ieeextreme-practice/task/robot-versus-fan/) | HARD | 58/660 | periodic dust path vs robot path: simulate up to the period (lcm) | Math | numtheory.h | stmt |
| 16 | [Pipeline](https://csacademy.com/ieeextreme-practice/task/pipeline/) |  | 53/1134 | design a 3D pipe network (construction / search on a 3D grid) | Constructive |  | stmt |
| 14 | [Furin Back](https://csacademy.com/ieeextreme-practice/task/furin-back/) | HARDEST | 17/393 | ad hoc |  |  | tags |
| 18 | [Welcome to IEEEXtreme 18.0](https://csacademy.com/ieeextreme-practice/task/welcome-ieeextreme-18/) |  | 0/4037 | print a message (warm-up) |  |  | stmt |
| 19 | [Welcome to IEEEXtreme 19.0](https://csacademy.com/ieeextreme-practice/task/welcome-to-ieeextreme-19/) |  | 0/4128 | print a message (warm-up) |  |  | stmt |

Also uses implementation and simulation: [Xtreme Fake Coins](https://csacademy.com/ieeextreme-practice/task/xtreme-fake-coins/) (12), [Drawing Rooted Binary Trees](https://csacademy.com/ieeextreme-practice/task/drawing-rooted-binary-trees/) (12), [IEEEXplore Indexing](https://csacademy.com/ieeextreme-practice/task/ieeexplore-indexing/) (14), [Spies of Red and Blue](https://csacademy.com/ieeextreme-practice/task/spies/) (15), [Rigged Dice](https://csacademy.com/ieeextreme-practice/task/rigged-dice/) (15), [Programmer's Poem](https://csacademy.com/ieeextreme-practice/task/Poetry/) (17)

## Strings

*ciphers, KMP, hashing, palindromes (Manacher), tries, Aho-Corasick, brackets.* Library: strutil.h, trie.h, hashmap.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 16 | [Gaius Letters](https://csacademy.com/ieeextreme-practice/task/gaius-letters/) |  | 3091/3742 | Caesar cipher (the statement itself is encrypted) |  |  | stmt |
| 17 | [Caesar Redux](https://csacademy.com/ieeextreme-practice/task/caesar_redux/) |  | 2438/4446 | Caesar cipher: detect plaintext vs ciphertext |  |  | stmt |
| 17 | [Programmer's Poem](https://csacademy.com/ieeextreme-practice/task/Poetry/) |  | 1049/2510 | rhyme scheme labelling (suffix comparison) | Implementation | hashmap.h | stmt |
| 11 | [Jarawi and The Interview](https://csacademy.com/ieeextreme-practice/task/6f960361da7beb7f3a083f4776c2cf79/) | MEDIUM | 428/1504 | subsequence queries: next-occurrence table + binary search | Binary search | strutil.h search.h | tags |
| 17 | [Labradoodle](https://csacademy.com/ieeextreme-practice/task/labradoodle/) |  | 515/1987 | blended words: prefix/suffix lookups in hash sets |  | hashmap.h trie.h | stmt |
| 13 | [Ave Caesar!](https://csacademy.com/ieeextreme-practice/task/ave-caesar/) |  | 200/936 | recursive validity of strings (split points, comparisons), memoisation |  | strutil.h | stmt |
| 19 | [Sequence Decomposition](https://csacademy.com/ieeextreme-practice/task/sequence-decomposition/) |  | 624/3108 | decompose into "112012" subsequences: greedy counters | Greedy |  | stmt |
| 14 | [Rotational Lights](https://csacademy.com/ieeextreme-practice/task/rotational-lights/) | MEDIUM | 199/1206 | KMP on cyclic patterns |  | strutil.h | tags |
| 14 | [Non-Overlapping Palindromes](https://csacademy.com/ieeextreme-practice/task/nonoverlapping-palindromes/) | MEDIUM | 182/1264 | Manacher: best palindrome ending before / starting after each position | DP | strutil.h | stmt |
| 18 | [Cheap Construction](https://csacademy.com/ieeextreme-practice/task/cheap-construction/) |  | 428/3106 | substring rules connect islands: hashing + DSU for every k | Graphs | strutil.h dsu.h | stmt |
| 17 | [Bad Passwords](https://csacademy.com/ieeextreme-practice/task/BadPasswords/) |  | 193/1612 | detect iterated passwords: common prefix/suffix, numeric and month sequences | Text processing |  | stmt |
| 10 | [Safety](https://csacademy.com/ieeextreme-practice/task/safety/) |  | 5/45 | substring equality under edits: rolling hash in a segment tree | Data structures | strutil.h segtree.h | stmt |
| 15 | [Expression Evaluation](https://csacademy.com/ieeextreme-practice/task/expression/) | MEDIUM | 151/1698 | expression parsing (recursive descent / two stacks), validity checks | Text processing | linear.h | stmt |
| 15 | [Image Convolution](https://csacademy.com/ieeextreme-practice/task/image-convolution/) | EASY | 38/499 | 2D pattern matching (row hashing / KMP) | Data structures | strutil.h | stmt |
| 12 | [Tweedledum's Nested Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledums-nested-brackets/) |  | 16/500 | bracket depth, counting re-insertions with prefix balances | Combinatorics | segtree.h | stmt |
| 16 | [Weird Reward](https://csacademy.com/ieeextreme-practice/task/weird-reward/) | HARD | 15/490 | expression grammar, DP over substrings that are valid expressions | DP | linear.h | stmt |
| 12 | [Tweedledee's Split Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledees-split-brackets/) |  | 28/1017 | split brackets into two valid sequences (stack, DP) | DP | dp.h | stmt |
| 17 | [Powerful Strings](https://csacademy.com/ieeextreme-practice/task/powerful-strings/) |  | 28/1707 | Aho-Corasick automaton + DP over length (sum of 2^occurrences) | Combinatorics | trie.h dp.h | stmt |

Also uses strings: [N-Palindromes](https://csacademy.com/ieeextreme-practice/task/n-palindromes/) (10), [Magic Spell](https://csacademy.com/ieeextreme-practice/task/magic-spell/) (12), [Yin Yang](https://csacademy.com/ieeextreme-practice/task/yin-yang/) (13), [Reshuffle Teams](https://csacademy.com/ieeextreme-practice/task/reshuffle-teams/) (13), [Coupon Codes](https://csacademy.com/ieeextreme-practice/task/coupon-codes/) (14), [Word Search](https://csacademy.com/ieeextreme-practice/task/wordsearch/) (15), [Palindrome Cutting](https://csacademy.com/ieeextreme-practice/task/palindrome-cutting/) (16), [Book Cipher](https://csacademy.com/ieeextreme-practice/task/book-cipher/) (16), [What Language Am I Speaking?](https://csacademy.com/ieeextreme-practice/task/what-language-am-i-speaking/) (16), [Restaurant Cipher](https://csacademy.com/ieeextreme-practice/task/resaturant_cipher/) (17), [EDPS](https://csacademy.com/ieeextreme-practice/task/edps/) (19), [Squared Gaps](https://csacademy.com/ieeextreme-practice/task/squared-gaps/) (19)

## Text and data processing

*IEEE Xplore tasks: parse JSON/CSV/XML-like input, group, sort, aggregate.* Library: hashmap.h, sort.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [Application Abuse](https://csacademy.com/ieeextreme-practice/task/application-abuse/) |  | 1893/3227 | parse logs, aggregate per user, detect rule violations |  | hashmap.h sort.h | stmt |
| 12 | [Xplore](https://csacademy.com/ieeextreme-practice/task/xplore/) |  | 455/792 | parse JSON records, compute authors' h-index, sort |  | sort.h hashmap.h | stmt |
| 13 | [Impact Factor](https://csacademy.com/ieeextreme-practice/task/impact-factor/) |  | 334/796 | parse JSON records, aggregate citations per year, compute impact factor |  | hashmap.h sort.h | stmt |
| 16 | [Book Cipher](https://csacademy.com/ieeextreme-practice/task/book-cipher/) |  | 307/1415 | strip XML tags, build the character grid, decode (r, c) pairs | Strings |  | stmt |
| 18 | [Disparate Data Sets](https://csacademy.com/ieeextreme-practice/task/disparate-datasets/) |  | 343/2645 | CSV parsing, joining records, filling missing fields |  | hashmap.h | stmt |
| 14 | [IEEEXplore Indexing](https://csacademy.com/ieeextreme-practice/task/ieeexplore-indexing/) | MEDIUM | 92/767 | parse records, build an inverted index | Implementation | hashmap.h sort.h | tags |
| 17 | [Thesaurus](https://csacademy.com/ieeextreme-practice/task/thesaurus/) |  | 9/604 | parse documents and a hierarchical thesaurus, map terms to top topics |  | hashmap.h | stmt |

Also uses text and data processing: [Xtreme Winners](https://csacademy.com/ieeextreme-practice/task/xtreme-winners/) (15), [Expression Evaluation](https://csacademy.com/ieeextreme-practice/task/expression/) (15), [Bad Passwords](https://csacademy.com/ieeextreme-practice/task/BadPasswords/) (17)

## Reverse engineering and emulation

*guess a hidden function from examples, emulate code / number formats.* Library: bits.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 17 | [Restaurant Cipher](https://csacademy.com/ieeextreme-practice/task/resaturant_cipher/) |  | 2983/3520 | deduce the encoding scheme from the examples | Strings |  | stmt |
| 18 | [IEEE754 Emulator](https://csacademy.com/ieeextreme-practice/task/ieee754-emulator/) |  | 986/3278 | emulate IEEE 754 single precision with lookup tables (bit fields) | Bits | bits.h | stmt |
| 12 | [Magic Spell](https://csacademy.com/ieeextreme-practice/task/magic-spell/) |  | 160/833 | discover the hidden string function from the examples | Strings |  | stmt |
| 19 | [Ladder](https://csacademy.com/ieeextreme-practice/task/ladder/) |  | 377/3556 | reproduce the output of a given Python program efficiently |  |  | stmt |
| 15 | [Xtreme Winners](https://csacademy.com/ieeextreme-practice/task/xtreme-winners/) |  | 31/2416 | code golf: map a team name to its edition with the shortest program | Text processing |  | stmt |
| 17 | [Dalvik](https://csacademy.com/ieeextreme-practice/task/dalvik/) |  | 19/1542 | read Dalvik (smali) bytecode and reimplement it efficiently |  |  | stmt |

Also uses reverse engineering and emulation: [Barrett Reduction](https://csacademy.com/ieeextreme-practice/task/barrett-reduction/) (12), [ARM Constant Multiplication](https://csacademy.com/ieeextreme-practice/task/arm/) (14)

## Math and number theory

*modular arithmetic, primes, gcd, fast exponentiation, formulas.* Library: numtheory.h, matrix.h, bignum.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [Secure Elliptic Curve Point Addition](https://csacademy.com/ieeextreme-practice/task/secure-elliptic-curve-point-addition/) |  | 4877/5159 | modular inverse, elliptic curve point addition |  | numtheory.h | stmt |
| 14 | [Mosaic Decoration I](https://csacademy.com/ieeextreme-practice/task/mosaic1/) | EASY | 2533/2931 | ceiling divisions and costs |  |  | tags |
| 15 | [Rigged Dice](https://csacademy.com/ieeextreme-practice/task/rigged-dice/) | EASY | 1234/1980 | likelihood comparison: count the sixes | Implementation |  | stmt |
| 14 | [Mosaic Decoration II](https://csacademy.com/ieeextreme-practice/task/mosaic2/) | EASY | 1025/1645 | arithmetic on tile counts |  |  | tags |
| 11 | [Fibonacci](https://csacademy.com/ieeextreme-practice/task/09f92a575cc006d4a6a7f525f370ec30/) | EASY | 1693/3179 | linear recurrence by matrix exponentiation | DP | matrix.h | tags |
| 10 | [P = NP?](https://csacademy.com/ieeextreme-practice/task/pvnp/) |  | 12/32 | bounds of rank sums with missing values (sorting, greedy) | Greedy | sort.h | stmt |
| 12 | [Barrett Reduction](https://csacademy.com/ieeextreme-practice/task/barrett-reduction/) |  | 148/604 | exact division by multiply-and-shift, 64/128-bit arithmetic | Bits, Reverse engineering | bits.h | stmt |
| 12 | [Product Rectangle](https://csacademy.com/ieeextreme-practice/task/product-rectangle/) |  | 188/936 | rectangle sum = (sum of A range)(sum of B range): max/min subarray sums (Kadane) | DP | dp.h | stmt |
| 13 | [Googolplex](https://csacademy.com/ieeextreme-practice/task/googolplex/) |  | 81/412 | huge exponent: cycle of 5^k mod 100 |  | numtheory.h | stmt |
| 14 | [Mosaic Decoration III](https://csacademy.com/ieeextreme-practice/task/mosaic3/) | EASY | 113/608 | arithmetic on tile counts |  |  | tags |
| 13 | [Infinite String](https://csacademy.com/ieeextreme-practice/task/infinite-string/) |  | 182/1002 | locate an index in the string of all words by length (powers of B) |  |  | stmt |
| 17 | [Happy Numbers](https://csacademy.com/ieeextreme-practice/task/happy_numbers/) |  | 690/4372 | happy numbers in a range: precompute small sums, digit DP | DP | dp.h | stmt |
| 12 | [Factorial Zeros](https://csacademy.com/ieeextreme-practice/task/factorial-zeros/) |  | 104/678 | Legendre's formula for base B (factorise B) + binary search on n | Binary search | numtheory.h search.h | stmt |
| 18 | [Power of three](https://csacademy.com/ieeextreme-practice/task/power-of-three/) |  | 684/4462 | is N a power of three (big N: logarithm / big integer) |  | bignum.h | stmt |
| 11 | [Math Challenge](https://csacademy.com/ieeextreme-practice/task/7df0da0b0477307be410f4772c739528/) | HARD | 276/2140 | a^C(b,c) mod p: exponent mod p-1 (Euler/Fermat), binomial mod composite (CRT) |  | numtheory.h combin.h | tags |
| 11 | [Quipu Function](https://csacademy.com/ieeextreme-practice/task/5802db6cc4107baa3e135d06a31494b5/) | HARD | 235/1910 | sieve, counting prime factors over ranges |  | numtheory.h | tags |
| 18 | [Sierpinski](https://csacademy.com/ieeextreme-practice/task/sierpinski/) |  | 145/1421 | Sierpinski / Pascal triangle mod 2: recursion on coordinates |  | combin.h | stmt |
| 14 | [Molecules](https://csacademy.com/ieeextreme-practice/task/molecules/) | HARD | 52/517 | chemical formulas: counting atoms, linear equations |  | matrix.h | tags |
| 13 | [Batchman and GCD](https://csacademy.com/ieeextreme-practice/task/batchman-and-gcd/) |  | 115/1457 | distinct GCDs of subsequences: check every d via its multiples (harmonic sum) |  | numtheory.h | stmt |
| 17 | [Rectangles](https://csacademy.com/ieeextreme-practice/task/rectangles/) |  | 45/765 | group sizes whose rectangles have coprime sides (gcd, factorisation) | Combinatorics | numtheory.h | stmt |
| 15 | [Arrays Count](https://csacademy.com/ieeextreme-practice/task/arrays-count/) | HARD | 5/307 | counting arrays from an OR expression (ad hoc counting) | Bits | combin.h | tags |
| 15 | [Beautiful Summation](https://csacademy.com/ieeextreme-practice/task/summation/) | HARD | 44/2702 | sum P^k k^Q mod M (M not prime): matrix power / divide and conquer with binomials |  | matrix.h combin.h | stmt |
| 18 | [Balls](https://csacademy.com/ieeextreme-practice/task/balls/) |  | 21/3607 | tiles hit by multiples: inclusion-exclusion over lcm with pruning | Combinatorics | numtheory.h | stmt |
| 15 | [Big Matrix Small Determinant](https://csacademy.com/ieeextreme-practice/task/big-matrix-small-determinant/) | HARD | 7/1254 | construct a matrix with a given determinant (recursion) | Constructive | matrix.h | tags |
| 10 | [Goldbach](https://csacademy.com/ieeextreme-practice/task/goldbach/) |  | 0/125 | primes: sieve / Miller-Rabin, sum of three primes |  | numtheory.h | stmt |

Also uses math and number theory: [Weighty Decisions](https://csacademy.com/ieeextreme-practice/task/weighty-decisions/) (10), [Pyramid](https://csacademy.com/ieeextreme-practice/task/5e98e4b17b3477e671568a437388fb7a/) (11), [Running Up Stairs](https://csacademy.com/ieeextreme-practice/task/96c8b1313edd72abf600facb0a14dbab/) (11), [Mister Counter](https://csacademy.com/ieeextreme-practice/task/3dd761f749054a509a0012c5beee0e35/) (11), [RecXor](https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/) (11), [Xtreme Rappers](https://csacademy.com/ieeextreme-practice/task/xtreme-rappers/) (13), [Lexical Addition](https://csacademy.com/ieeextreme-practice/task/lexical-addition/) (13), [Coin Collector](https://csacademy.com/ieeextreme-practice/task/coin-collector/) (14), [Polygon](https://csacademy.com/ieeextreme-practice/task/polygon/) (15), [My Treat](https://csacademy.com/ieeextreme-practice/task/my-treat/) (16), [Scheduler](https://csacademy.com/ieeextreme-practice/task/scheduler/) (16), [Robot versus Fan](https://csacademy.com/ieeextreme-practice/task/robot-versus-fan/) (16), [Queen](https://csacademy.com/ieeextreme-practice/task/queen/) (16), [He Loves Data Structures](https://csacademy.com/ieeextreme-practice/task/data_structures/) (17), [Dice](https://csacademy.com/ieeextreme-practice/task/dices/) (17), [Cool Sum](https://csacademy.com/ieeextreme-practice/task/coolsum/) (17), [Stick](https://csacademy.com/ieeextreme-practice/task/stick/) (18), [New Casino Game](https://csacademy.com/ieeextreme-practice/task/new-casino-game/) (19), [Become as One](https://csacademy.com/ieeextreme-practice/task/become-as-one/) (19), [Airline Traveling](https://csacademy.com/ieeextreme-practice/task/airline-traveling/) (19), [Baker's Competition](https://csacademy.com/ieeextreme-practice/task/bakers-competition/) (19), [Continued Fractions](https://csacademy.com/ieeextreme-practice/task/continued-fractions/) (19)

## Combinatorics and probability

*counting mod p, binomials, inclusion-exclusion, expectation, generating functions.* Library: combin.h, fft.h, dp.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [New Casino Game](https://csacademy.com/ieeextreme-practice/task/new-casino-game/) |  | 8/9 | expected value with random non-attacking rooks (linearity of expectation) | Math | combin.h | stmt |
| 10 | [N-Palindromes](https://csacademy.com/ieeextreme-practice/task/n-palindromes/) |  | 75/126 | count strings that become palindromes with exactly n changes (counting over mirrored pairs) | Strings | combin.h dp.h | stmt |
| 19 | [Do you know Expectation?](https://csacademy.com/ieeextreme-practice/task/do-you-know-expectation/) |  | 1288/3406 | E[X^K] for XOR of a random subset: X is uniform over the linear span | Bits | bits.h | stmt |
| 13 | [Alfa Pool](https://csacademy.com/ieeextreme-practice/task/alfa-pool/) |  | 169/567 | point totals with doubling winning streaks (counting DP) | DP | dp.h | stmt |
| 13 | [Ranged Alfa Pool](https://csacademy.com/ieeextreme-practice/task/ranged-alfa-pool/) |  | 114/387 | count tournament scenarios by point total (doubling streaks) | DP | dp.h | stmt |
| 18 | [Increasing table](https://csacademy.com/ieeextreme-practice/task/increasing-table/) |  | 1029/4436 | 2 x N increasing tables with row restrictions (ballot-style DP) | DP | dp.h combin.h | stmt |
| 17 | [Ordered Permutations](https://csacademy.com/ieeextreme-practice/task/ordered-permutations/) |  | 285/1418 | permutations with a given up/down pattern: O(n^2) DP with prefix sums | DP | dp.h | stmt |
| 19 | [Bitonic Sequences](https://csacademy.com/ieeextreme-practice/task/bitonic-sequences/) |  | 574/4441 | count bitonic compositions for every N (partition-style DP / generating functions) | DP | dp.h fft.h | stmt |
| 16 | [Array](https://csacademy.com/ieeextreme-practice/task/array/) |  | 132/1468 | count arrays with a given OR-expression length, modulo 4 | Bits | combin.h | stmt |
| 12 | [Friendly Sequences](https://csacademy.com/ieeextreme-practice/task/friendly-sequences/) |  | 17/397 | counting non-decreasing sequences under prefix-sum bounds (DP + prefix sums) | DP | dp.h | stmt |
| 17 | [Cool Sum](https://csacademy.com/ieeextreme-practice/task/coolsum/) |  | 46/2167 | binomial sums by residue mod 2^k (polynomial arithmetic mod x^(2^k) - 1) | Math | fft.h combin.h | stmt |
| 16 | [Palindrome Cutting](https://csacademy.com/ieeextreme-practice/task/palindrome-cutting/) |  | 33/1578 | arrays splittable into even palindromes: DP over primitive palindromes | Strings | combin.h dp.h | stmt |
| 15 | [Candy Shop](https://csacademy.com/ieeextreme-practice/task/candy-shop/) | HARDEST | 22/1331 | generating functions, FFT/NTT | DP | fft.h combin.h | tags |
| 18 | [Halving](https://csacademy.com/ieeextreme-practice/task/halving/) |  | 39/2740 | count permutations consistent with min/max halving rules | DP | combin.h | stmt |
| 17 | [Dice](https://csacademy.com/ieeextreme-practice/task/dices/) |  | 14/1489 | dice-sum probability via generating functions mod 998244353 (NTT) | Math | fft.h combin.h | stmt |
| 18 | [Increasing-decreasing permutations](https://csacademy.com/ieeextreme-practice/task/increasing-decreasing-permutation/) |  | 14/2929 | sum over permutations of minimal adjacent swaps (inversion counting mod M) |  | combin.h | stmt |
| 18 | [Bounded tuples](https://csacademy.com/ieeextreme-practice/task/bounded-tuples/) |  | 11/4059 | count integer assignments under sum constraints, detect infinity | Brute force | dp.h | stmt |

Also uses combinatorics and probability: [Tweedledum's Nested Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledums-nested-brackets/) (12), [Luck-i-flip](https://csacademy.com/ieeextreme-practice/task/luck-i-flip/) (13), [Coloring Tiles](https://csacademy.com/ieeextreme-practice/task/coloring-tiles/) (15), [Language Learning](https://csacademy.com/ieeextreme-practice/task/language-learning/) (15), [Xtreme Teams](https://csacademy.com/ieeextreme-practice/task/xtreme-teams/) (15), [Bus Company](https://csacademy.com/ieeextreme-practice/task/buscompany/) (15), [Queries on a Tree](https://csacademy.com/ieeextreme-practice/task/queries-on-a-tree/) (16), [Poker Tournament](https://csacademy.com/ieeextreme-practice/task/poker-tournament/) (16), [Powerful Strings](https://csacademy.com/ieeextreme-practice/task/powerful-strings/) (17), [Rectangles](https://csacademy.com/ieeextreme-practice/task/rectangles/) (17), [Combo Lock Redux](https://csacademy.com/ieeextreme-practice/task/combo_locks/) (17), [Balls](https://csacademy.com/ieeextreme-practice/task/balls/) (18), [This is not an optimization problem](https://csacademy.com/ieeextreme-practice/task/this-is-not-an-optimization-problem/) (18), [Queries](https://csacademy.com/ieeextreme-practice/task/queries/) (18), [Visit Egypt](https://csacademy.com/ieeextreme-practice/task/visit-egypt/) (19)

## Greedy and sorting

*sort + greedy choice, exchange argument, intervals, heaps.* Library: sort.h, heap.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [Magic Wands](https://csacademy.com/ieeextreme-practice/task/magic-wands/) |  | 4186/4603 | flip K consecutive: greedy left to right with a difference array |  |  | stmt |
| 10 | [Dog Walking](https://csacademy.com/ieeextreme-practice/task/dog-walking/) |  | 308/369 | sort, cut at the K-1 largest gaps |  | sort.h | stmt |
| 11 | [Blackgate Penitentiary](https://csacademy.com/ieeextreme-practice/task/8761fb7efefcf1d890df1d8d91cae241/) | EASY | 2655/3308 | sorting with ties, ranges of positions |  | sort.h | tags |
| 16 | [My Treat](https://csacademy.com/ieeextreme-practice/task/my-treat/) |  | 1451/1869 | minimum days to balance dinners (counting) | Math |  | stmt |
| 19 | [Palindrome Matrix](https://csacademy.com/ieeextreme-practice/task/palindrome-matrix/) |  | 3303/4559 | cells forced equal (DSU over mirrored positions), choose the median per group | Data structures | dsu.h sort.h | stmt |
| 14 | [Hotel Wiring](https://csacademy.com/ieeextreme-practice/task/hotel-wiring/) | EASY | 1564/2305 | sorting |  | sort.h | tags |
| 13 | [Minimum Permutation](https://csacademy.com/ieeextreme-practice/task/minimum-permutation/) |  | 1080/2568 | merge a sorted set into an array for the smallest permutation |  | sort.h | stmt |
| 12 | [Bear Sums](https://csacademy.com/ieeextreme-practice/task/bear-sums/) |  | 936/2298 | pair with a given sum: hash set or sort + two pointers | Data structures | hashmap.h sort.h | stmt |
| 16 | [Scheduler](https://csacademy.com/ieeextreme-practice/task/scheduler/) |  | 821/2185 | jobs of length 2^x on M workers, time mod 1e9+7 | Math | numtheory.h heap.h | stmt |
| 18 | [Brick stacks](https://csacademy.com/ieeextreme-practice/task/brick-stacks/) |  | 930/2619 | fewest stacks: sort + greedy with binary search (chains) |  | sort.h search.h | stmt |
| 18 | [Two Fridges](https://csacademy.com/ieeextreme-practice/task/two-fridges/) |  | 2039/5979 | two temperatures stabbing all intervals (sweep, try all values) | Brute force |  | stmt |
| 16 | [Scheduler Redux](https://csacademy.com/ieeextreme-practice/task/scheduler-redux/) |  | 551/1704 | jobs of length 2^x with equal lengths: heap of worker loads | Data structures | heap.h | stmt |
| 13 | [Xtreme Rappers](https://csacademy.com/ieeextreme-practice/task/xtreme-rappers/) |  | 948/3005 | maximum number of 3-word phrases from two word counts (formula) | Math |  | stmt |
| 13 | [Reshuffle Teams](https://csacademy.com/ieeextreme-practice/task/reshuffle-teams/) |  | 129/940 | group 4 teams around a table: all team orders x rotations with prefix counts | Strings |  | stmt |
| 15 | [Doctor's Appointments](https://csacademy.com/ieeextreme-practice/task/appointment/) | MEDIUM | 275/2436 | interval scheduling: sweep days, heap by deadline | Data structures | heap.h sort.h | stmt |
| 13 | [Lexical Addition](https://csacademy.com/ieeextreme-practice/task/lexical-addition/) |  | 277/2565 | shortest, then lexicographically smallest sum of terms from [A, B] | Math |  | stmt |
| 13 | [Unicornosaurus](https://csacademy.com/ieeextreme-practice/task/unicornosaurus/) |  | 78/740 | cover broken intervals with fewest powers (interval covering, sweep) | Data structures | sort.h | stmt |
| 13 | [Pair Swap Teams](https://csacademy.com/ieeextreme-practice/task/pair-swap-teams/) |  | 37/685 | minimum swaps to group teams on a circle (cycle counting over team orders) | Brute force | combin.h | stmt |
| 12 | [Make Distinct](https://csacademy.com/ieeextreme-practice/task/make-distinct/) |  | 44/1239 | minimal +-1 operations to make values distinct (sort, greedy with a heap) |  | sort.h heap.h | stmt |

Also uses greedy and sorting: [Painter's Dilemma](https://csacademy.com/ieeextreme-practice/task/painters-dilemma/) (10), [P = NP?](https://csacademy.com/ieeextreme-practice/task/pvnp/) (10), [Maximum Sum](https://csacademy.com/ieeextreme-practice/task/04dfa70efd936271ae191cb1a97eb876/) (11), [Octopuses with Watches](https://csacademy.com/ieeextreme-practice/task/59d4aae501fe4ced9ffbf3737acd18a2/) (11), [Poker Game](https://csacademy.com/ieeextreme-practice/task/poker-game/) (14), [Squad Game](https://csacademy.com/ieeextreme-practice/task/squad-game/) (15), [Digits swap](https://csacademy.com/ieeextreme-practice/task/digits-swap/) (18), [Another Sliding Window Problem](https://csacademy.com/ieeextreme-practice/task/another-sliding-window-problem/) (18), [Circular Permutation](https://csacademy.com/ieeextreme-practice/task/circular-permutation/) (19), [Sequence Decomposition](https://csacademy.com/ieeextreme-practice/task/sequence-decomposition/) (19)

## Binary search

*lower/upper bound, binary search on the answer.* Library: search.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [The Twin Occurrence Quest](https://csacademy.com/ieeextreme-practice/task/the-twin-occurrence-quest/) |  | 4548/5844 | first/last occurrence: lower and upper bound |  | search.h | stmt |
| 19 | [Circular Permutation](https://csacademy.com/ieeextreme-practice/task/circular-permutation/) |  | 5/7 | minimise the maximum circular move: try rotations and directions | Greedy | search.h | stmt |
| 14 | [Crafting Wooden Tables](https://csacademy.com/ieeextreme-practice/task/crafting-wooden-tables/) | EASY | 362/1921 | binary search on the answer |  | search.h | tags |

Also uses binary search: [Finding Shelter](https://csacademy.com/ieeextreme-practice/task/finding-shelter/) (10), [Jarawi and The Interview](https://csacademy.com/ieeextreme-practice/task/6f960361da7beb7f3a083f4776c2cf79/) (11), [Gotta Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/e610aba28810ebcf2d3998692269b5a0/) (11), [Telescope Scheduling](https://csacademy.com/ieeextreme-practice/task/telescope-scheduling/) (12), [Factorial Zeros](https://csacademy.com/ieeextreme-practice/task/factorial-zeros/) (12), [Gotta ~ Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/gotta-catch-em-all/) (12), [Chameleon Walk](https://csacademy.com/ieeextreme-practice/task/chameleon/) (15), [Stable Power Network](https://csacademy.com/ieeextreme-practice/task/stable-power-network/) (19)

## Dynamic programming

*knapsack, LIS/LCS, grid DP, bitmask DP, tree DP, counting DP.* Library: dp.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [Raju's Matrix Runs](https://csacademy.com/ieeextreme-practice/task/raju-s-matrix-runs/) |  | 9/9 | longest increasing path in a grid: DP over cells sorted by value | Graphs | grid.h sort.h | stmt |
| 10 | [Painter's Dilemma](https://csacademy.com/ieeextreme-practice/task/painters-dilemma/) |  | 208/255 | two brushes, minimise colour changes: DP over (position, other brush) | Greedy | dp.h | stmt |
| 11 | [BeetleBag](https://csacademy.com/ieeextreme-practice/task/ed8629419f140a5a2c923b049aba1224/) | EASY | 1533/2387 | 0/1 knapsack |  | dp.h | tags |
| 19 | [Visit Egypt](https://csacademy.com/ieeextreme-practice/task/visit-egypt/) |  | 1874/3273 | ordered ways to pay an amount (coin DP, order matters) | Combinatorics | dp.h | stmt |
| 17 | [Ice Cubes](https://csacademy.com/ieeextreme-practice/task/icecubes/) |  | 878/1827 | grid DP with a limit on consecutive "bad" cells |  | dp.h | stmt |
| 12 | [Lemons](https://csacademy.com/ieeextreme-practice/task/lemons/) |  | 868/1881 | worst-case optimal search on a line (egg-drop style minimax DP) |  | dp.h | stmt |
| 16 | [Travel Service](https://csacademy.com/ieeextreme-practice/task/travel-service/) |  | 713/1624 | refuelling decisions at stations: DP / Dijkstra over (station, state) | Graphs | paths.h dp.h | stmt |
| 12 | [Telescope Scheduling](https://csacademy.com/ieeextreme-practice/task/telescope-scheduling/) |  | 483/1156 | weighted interval scheduling: sort by end, DP + binary search | Binary search | dp.h search.h sort.h | stmt |
| 19 | [Squared Gaps](https://csacademy.com/ieeextreme-practice/task/squared-gaps/) |  | 1307/3403 | sequence alignment DP with a modified gap cost | Strings | dp.h | stmt |
| 11 | [Preparing for Xtreme 12.0](https://csacademy.com/ieeextreme-practice/task/72a7d67e7e18f4f7d033f7f5a5a09bef/) | MEDIUM | 326/939 | bitmask DP over subsets (exponential states) | Bits | dp.h bits.h | tags |
| 11 | [Gotta Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/e610aba28810ebcf2d3998692269b5a0/) | MEDIUM | 444/1495 | grid DP for minimal initial value, binary search on the answer | Binary search | dp.h search.h | tags |
| 11 | [The Fast and the Curious](https://csacademy.com/ieeextreme-practice/task/e1e444f71a2a7a69baf4c61ed756aa55/) | MEDIUM | 218/980 | DFS + DP on a graph | Graphs | graph.h dp.h | tags |
| 15 | [Language Learning](https://csacademy.com/ieeextreme-practice/task/language-learning/) | MEDIUM | 151/709 | distinct subsequences with an index gap > K (DP + prefix sums, last occurrence) | Combinatorics | dp.h hashmap.h | stmt |
| 15 | [Training Plan](https://csacademy.com/ieeextreme-practice/task/training-plan/) | MEDIUM | 77/373 | DP with "at most K consecutive" constraint (monotonic queue) |  | dp.h linear.h | stmt |
| 11 | [Pyramid](https://csacademy.com/ieeextreme-practice/task/5e98e4b17b3477e671568a437388fb7a/) | HARD | 121/714 | DP on a number triangle + closed formulas | Math | dp.h | tags |
| 18 | [Invertible Pairs](https://csacademy.com/ieeextreme-practice/task/invertible-pairs/) |  | 357/2120 | maximum subarray with optional sign flips of pairs (Kadane with states) |  | dp.h | stmt |
| 11 | [Sub Array Sum Problem](https://csacademy.com/ieeextreme-practice/task/46e8a03f242b875f1ae5fb84a3b4321f/) | HARD | 143/865 | sum of all subarray / submatrix sums by contribution, prefix sums |  | grid.h | tags |
| 16 | [Dream Team](https://csacademy.com/ieeextreme-practice/task/dream-team/) |  | 303/1960 | one player per position within budget (multiple-choice knapsack) | Brute force | dp.h | stmt |
| 11 | [Lion Territory](https://csacademy.com/ieeextreme-practice/task/15443fc9f89feb90bc30096f43b308af/) | HARD | 85/573 | grid DP, 2D prefix sums |  | dp.h grid.h | tags |
| 15 | [Coloring Tiles](https://csacademy.com/ieeextreme-practice/task/coloring-tiles/) | HARD | 16/227 | row-by-row DP over colour patterns (counting) | Combinatorics | dp.h | stmt |
| 13 | [Charlie New PC](https://csacademy.com/ieeextreme-practice/task/charlie-new-pc/) |  | 99/1476 | multiple-choice knapsack: one part per type, maximum cost within budget |  | dp.h | stmt |
| 13 | [Merchant Association](https://csacademy.com/ieeextreme-practice/task/merchant-association/) | HARDEST | 25/674 | tree DP | Trees | tree.h | tags |
| 14 | [Restaurant Reopening](https://csacademy.com/ieeextreme-practice/task/restaurant-reopening/) | HARDEST | 5/176 | bitmask DP (exponential states) | Bits | dp.h bits.h | tags |
| 14 | [Social Distancing in Class](https://csacademy.com/ieeextreme-practice/task/social-distancing/) | HARDEST | 9/526 | tree DP | Trees | tree.h | tags |

Also uses dynamic programming: [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) (11), [Fibonacci](https://csacademy.com/ieeextreme-practice/task/09f92a575cc006d4a6a7f525f370ec30/) (11), [Orienteering](https://csacademy.com/ieeextreme-practice/task/95352fd33b0e855d337b5b3ed85da3b6/) (11), [Elementary](https://csacademy.com/ieeextreme-practice/task/c787255968c972c653677a52599ecc2f/) (11), [Friendly Sequences](https://csacademy.com/ieeextreme-practice/task/friendly-sequences/) (12), [Product Rectangle](https://csacademy.com/ieeextreme-practice/task/product-rectangle/) (12), [Tweedledee's Split Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledees-split-brackets/) (12), [Ranged Alfa Pool](https://csacademy.com/ieeextreme-practice/task/ranged-alfa-pool/) (13), [Alfa Pool](https://csacademy.com/ieeextreme-practice/task/alfa-pool/) (13), [Non-Overlapping Palindromes](https://csacademy.com/ieeextreme-practice/task/nonoverlapping-palindromes/) (14), [Maximum Exploitation](https://csacademy.com/ieeextreme-practice/task/exploitation/) (15), [Candy Shop](https://csacademy.com/ieeextreme-practice/task/candy-shop/) (15), [Weird Reward](https://csacademy.com/ieeextreme-practice/task/weird-reward/) (16), [Polygon Cutting](https://csacademy.com/ieeextreme-practice/task/polygon-cutting/) (17), [Happy Numbers](https://csacademy.com/ieeextreme-practice/task/happy_numbers/) (17), [Ordered Permutations](https://csacademy.com/ieeextreme-practice/task/ordered-permutations/) (17), [Watershed](https://csacademy.com/ieeextreme-practice/task/watershed/) (17), [Triumvirates](https://csacademy.com/ieeextreme-practice/task/triumvirates/) (18), [Increasing table](https://csacademy.com/ieeextreme-practice/task/increasing-table/) (18), [Star Road](https://csacademy.com/ieeextreme-practice/task/star-road/) (18), [Halving](https://csacademy.com/ieeextreme-practice/task/halving/) (18), [Stones](https://csacademy.com/ieeextreme-practice/task/stones/) (18), [Four Piles](https://csacademy.com/ieeextreme-practice/task/four-piles/) (19), [Bitonic Sequences](https://csacademy.com/ieeextreme-practice/task/bitonic-sequences/) (19)

## Graphs

*BFS/DFS, shortest paths, MST, topological sort, SCC, bridges, matching, flow.* Library: graph.h, paths.h, flow.h, grid.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 18 | [King's Order](https://csacademy.com/ieeextreme-practice/task/kings-order/) |  | 3162/3547 | topological sort with priorities (heap), cycle detection |  | graph.h heap.h | stmt |
| 11 | [Vangelis the Batbear and the Bubbles challenge](https://csacademy.com/ieeextreme-practice/task/979a09a0cd8c4e98dd0a690f39a55bd2/) | EASY | 1924/2921 | cycle detection with DSU / DFS | Data structures | dsu.h graph.h | tags |
| 16 | [Invisible Ghosts](https://csacademy.com/ieeextreme-practice/task/invisible-ghosts/) | MEDIUM | 380/610 | BFS with the lexicographically smallest path, ghosts as multi-source BFS |  | graph.h grid.h | stmt |
| 11 | [Fill The Pixels](https://csacademy.com/ieeextreme-practice/task/bd45c86a844acd8ffc58b6a965cb0197/) | MEDIUM | 317/527 | flood fill on a pixel grid |  | grid.h | tags |
| 17 | [Watershed](https://csacademy.com/ieeextreme-practice/task/watershed/) |  | 795/1461 | water flow on a grid: process cells by decreasing elevation (DAG) | DP | grid.h sort.h | stmt |
| 10 | [Binary Quilts](https://csacademy.com/ieeextreme-practice/task/binary-quilts/) |  | 30/57 | BFS over 2^25 board states stored as bitmasks | Bits | graph.h bits.h | stmt |
| 10 | [Pirates](https://csacademy.com/ieeextreme-practice/task/pirates/) |  | 40/76 | label islands by flood fill, 0-1 BFS counting island crossings |  | grid.h paths.h | stmt |
| 11 | [Orienteering](https://csacademy.com/ieeextreme-practice/task/95352fd33b0e855d337b5b3ed85da3b6/) | MEDIUM | 266/515 | Dijkstra between control points + bitmask TSP | DP | paths.h dp.h | tags |
| 19 | [Stable Power Network](https://csacademy.com/ieeextreme-practice/task/stable-power-network/) |  | 2212/4347 | minimise max risk, then time: sort/binary search on risk + Dijkstra | Binary search | paths.h dsu.h | stmt |
| 19 | [Airline Traveling](https://csacademy.com/ieeextreme-practice/task/airline-traveling/) |  | 1852/3728 | exact total miles on a star of flights: parity and gcd reasoning | Math | numtheory.h graph.h | stmt |
| 16 | [Tourist Taxi Service](https://csacademy.com/ieeextreme-practice/task/tourist-taxi-service/) | MEDIUM | 116/297 | shortest rides starting with 5 distinct streets: Dijkstra on expanded states |  | paths.h | stmt |
| 16 | [Wireless Network](https://csacademy.com/ieeextreme-practice/task/wireless-network/) |  | 156/422 | minimum spanning tree with upgrade costs (Kruskal) |  | graph.h dsu.h | stmt |
| 11 | [Shuffle](https://csacademy.com/ieeextreme-practice/task/0186cd4b3a330dc501606737e090e0da/) | MEDIUM | 311/853 | maximum bipartite matching |  | flow.h | tags |
| 11 | [Collecting Gold](https://csacademy.com/ieeextreme-practice/task/333043935273ab966569971859d1835b/) | MEDIUM | 320/906 | Dijkstra shortest paths |  | paths.h | tags |
| 16 | [Random Mazes](https://csacademy.com/ieeextreme-practice/task/random-mazes/) |  | 98/278 | maze rules: connectivity and loops in regions (BFS / DSU) |  | graph.h dsu.h grid.h | stmt |
| 15 | [Chameleon Walk](https://csacademy.com/ieeextreme-practice/task/chameleon/) | MEDIUM | 120/416 | binary search on C + Dijkstra | Binary search | paths.h search.h | stmt |
| 17 | [Rumors](https://csacademy.com/ieeextreme-practice/task/rumors/) |  | 405/1660 | possible rumour sources: reachability, SCC condensation |  | graph.h | stmt |
| 19 | [Domino Path](https://csacademy.com/ieeextreme-practice/task/domino-path/) |  | 637/3377 | domino subsets forming a chain: Euler path (degrees + connectivity) over subsets | Bits | bits.h dsu.h | stmt |
| 13 | [Alfa Universe Weight Sorting](https://csacademy.com/ieeextreme-practice/task/alfa-universe-weight-sorting/) | HARD | 95/534 | known order pairs from comparisons: transitive closure / topological order |  | graph.h | stmt |
| 12 | [Gotta ~ Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/gotta-catch-em-all/) |  | 51/325 | binary search on time + bipartite matching (holes take two) | Binary search | flow.h search.h | stmt |
| 17 | [National Highway System](https://csacademy.com/ieeextreme-practice/task/national_highways/) |  | 161/1110 | edges in any MST: Kruskal by equal-weight groups + bridges |  | graph.h dsu.h | stmt |
| 12 | [Barter System](https://csacademy.com/ieeextreme-practice/task/barter-system/) |  | 154/1170 | exchange rates as products along paths (DFS / weighted DSU) |  | graph.h dsu.h | stmt |
| 13 | [Bearcity Renting](https://csacademy.com/ieeextreme-practice/task/bearcity-renting/) |  | 62/507 | streets that stay two-way in every strong orientation = bridges |  | graph.h | stmt |
| 17 | [Combo Lock Redux](https://csacademy.com/ieeextreme-practice/task/combo_locks/) |  | 58/522 | BFS shortest moves + number of shortest paths mod p | Combinatorics | graph.h | stmt |
| 14 | [Magical Stones I](https://csacademy.com/ieeextreme-practice/task/magical-stones/) | MEDIUM | 100/1162 | BFS over states |  | graph.h | tags |
| 14 | [Magical Stones II](https://csacademy.com/ieeextreme-practice/task/magical-stones-2/) | HARD | 29/433 | BFS over stone states, constructive answer | Constructive | graph.h bits.h | tags |
| 17 | [Theme Park](https://csacademy.com/ieeextreme-practice/task/theme_park/) |  | 19/296 | change costs without creating a negative cycle: Bellman-Ford / potentials |  | paths.h | stmt |
| 14 | [The Last of Us](https://csacademy.com/ieeextreme-practice/task/the-last-of-us/) | HARDEST | 4/95 | Dijkstra (output only task) |  | paths.h | tags |
| 15 | [The Tortoise and The Hare](https://csacademy.com/ieeextreme-practice/task/the-tortoise-and-the-hare/) | HARDEST | 23/999 | Dijkstra, choosing a city to block |  | paths.h | tags |
| 10 | [Finding Shelter](https://csacademy.com/ieeextreme-practice/task/finding-shelter/) |  | 0/41 | bottleneck assignment: binary search + bipartite matching, then min-cost matching | Binary search | flow.h search.h | stmt |

Also uses graphs: [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) (11), [Odd Cycle Check](https://csacademy.com/ieeextreme-practice/task/e21a405d32da71227e2d5fb313fd19d4/) (11), [The Fast and the Curious](https://csacademy.com/ieeextreme-practice/task/e1e444f71a2a7a69baf4c61ed756aa55/) (11), [The Gold-diggers](https://csacademy.com/ieeextreme-practice/task/the-gold-diggers/) (12), [Rescue Mission](https://csacademy.com/ieeextreme-practice/task/rescue-mission/) (14), [Travel Service](https://csacademy.com/ieeextreme-practice/task/travel-service/) (16), [Cheap Construction](https://csacademy.com/ieeextreme-practice/task/cheap-construction/) (18), [Raju's Matrix Runs](https://csacademy.com/ieeextreme-practice/task/raju-s-matrix-runs/) (19)

## Trees

*rooting, subtree sizes, LCA, diameter, tree DP, HLD, Euler tour.* Library: tree.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [White knights and Black warriors](https://csacademy.com/ieeextreme-practice/task/white-knights-and-black-warriors/) |  | 2438/2871 | distance from a path to the nearest white node: multi-source BFS + path minimum |  | tree.h graph.h | stmt |
| 18 | [Icarus](https://csacademy.com/ieeextreme-practice/task/icarus/) |  | 2430/3618 | build a binary tree that traps a walk (simulation + construction) | Constructive |  | stmt |
| 11 | [Rumour](https://csacademy.com/ieeextreme-practice/task/9ca8fafd184f553a903734761546a224/) | EASY | 1311/2126 | distance in an implicit complete binary tree via bit shifts (LCA) | Bits | bits.h | tags |
| 19 | [Beatrice and the Dream Tree](https://csacademy.com/ieeextreme-practice/task/beatrice-and-the-dream-tree/) |  | 1679/3848 | indistinguishable nodes: rooted tree hashing / automorphisms |  | tree.h hashmap.h | stmt |
| 12 | [Drawing Rooted Binary Trees](https://csacademy.com/ieeextreme-practice/task/drawing-rooted-binary-trees/) |  | 696/1828 | build a binary tree, ASCII drawing by in-order columns | Implementation |  | stmt |
| 15 | [Bridge Construction](https://csacademy.com/ieeextreme-practice/task/bridge/) | MEDIUM | 138/383 | join two trees: diameters and radii, max(d1, d2, r1 + r2 + 1) |  | tree.h | stmt |
| 15 | [Spies of Red and Blue](https://csacademy.com/ieeextreme-practice/task/spies/) | EASY | 297/918 | simulate information passing in two hierarchies (depths, events) | Implementation | tree.h | stmt |
| 13 | [Xranda and Tree](https://csacademy.com/ieeextreme-practice/task/xranda-and-tree/) |  | 197/991 | sum over pairs of the max edge on the path: Kruskal order + DSU sizes | Data structures | dsu.h | stmt |
| 13 | [The Lonely Shepherd](https://csacademy.com/ieeextreme-practice/task/lonely-shepherd/) |  | 78/400 | tree cut and toggles independent of the colouring (parity, tree DP) | Constructive | tree.h | stmt |
| 16 | [ANDman](https://csacademy.com/ieeextreme-practice/task/andman/) | HARDEST | 205/1177 | path products with point updates: HLD + segment tree (mod product) | Data structures | tree.h segtree.h | stmt |
| 12 | [Tree Fun](https://csacademy.com/ieeextreme-practice/task/tree-fun/) |  | 96/593 | path additions: difference on tree + LCA (or HLD), then maximum |  | tree.h | stmt |
| 17 | [He Loves Data Structures](https://csacademy.com/ieeextreme-practice/task/data_structures/) |  | 56/569 | subtree updates with Euler's totient: Euler tour + Fenwick/segment tree, sieve | Data structures, Math | tree.h fenwick.h numtheory.h | stmt |
| 16 | [Queries on a Tree](https://csacademy.com/ieeextreme-practice/task/queries-on-a-tree/) |  | 15/173 | sum over edge subsets of squared component sums, with updates | Combinatorics | tree.h | stmt |
| 13 | [Monokeros](https://csacademy.com/ieeextreme-practice/task/monokeros/) |  | 131/1548 | BST insertion depths: predecessor/successor in an ordered set (Fenwick tree) | Data structures | fenwick.h | stmt |
| 15 | [Bus Company](https://csacademy.com/ieeextreme-practice/task/buscompany/) | HARDEST | 31/377 | average path lengths per company: contribution counting on a tree | Combinatorics | tree.h | stmt |
| 19 | [Diameter Problem Again](https://csacademy.com/ieeextreme-practice/task/diameter-problem-again/) |  | 193/2772 | diameter of node sets with negative weights: segment tree of diameter endpoints + LCA | Data structures | tree.h segtree.h | stmt |
| 14 | [Identifying Infected](https://csacademy.com/ieeextreme-practice/task/identifying-infected/) | HARD | 63/912 | lowest common ancestor |  | tree.h | tags |
| 12 | [Organizational Chart](https://csacademy.com/ieeextreme-practice/task/organizational-chart/) |  | 36/593 | bounds of subtree sizes with missing reports (tree DP) |  | tree.h | stmt |
| 15 | [Xtreme Teleportation](https://csacademy.com/ieeextreme-practice/task/teleportation/) | HARDEST | 12/229 | bottleneck path queries: maximum spanning tree + LCA (or offline DSU) | Data structures | dsu.h tree.h | stmt |
| 18 | [Star Road](https://csacademy.com/ieeextreme-practice/task/star-road/) |  | 123/4816 | best path in a tree by restaurant stars (tree DP) | DP | tree.h | stmt |
| 18 | [Queries](https://csacademy.com/ieeextreme-practice/task/queries/) |  | 38/3067 | sum over edge subsets of squared component sums, with updates | Combinatorics | tree.h | stmt |
| 17 | [Tree Queries 2](https://csacademy.com/ieeextreme-practice/task/tree-queries-2/) |  | 4/343 | path scores with updates: HLD + segment tree of linear maps | Data structures | tree.h segtree.h | stmt |
| 18 | [This is not an optimization problem](https://csacademy.com/ieeextreme-practice/task/this-is-not-an-optimization-problem/) |  | 11/1714 | sum of Steiner tree weights over all k-subsets: edge contributions with binomials + NTT | Combinatorics | fft.h combin.h tree.h | stmt |

Also uses trees: [Merchant Association](https://csacademy.com/ieeextreme-practice/task/merchant-association/) (13), [Social Distancing in Class](https://csacademy.com/ieeextreme-practice/task/social-distancing/) (14), [Polygon Cutting](https://csacademy.com/ieeextreme-practice/task/polygon-cutting/) (17), [Hack the coach!](https://csacademy.com/ieeextreme-practice/task/hack-the-coach/) (19)

## Data structures

*prefix sums, Fenwick, segment tree (lazy), sparse table, DSU, monotonic stack/queue, hashing.* Library: fenwick.h, segtree.h, sparse.h, dsu.h, linear.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [Easy Sum](https://csacademy.com/ieeextreme-practice/task/easy-sum/) |  | 6/8 | sum over subarrays by thresholds per bit (two pointers, counting) | Bits | bits.h | stmt |
| 19 | [Become as One](https://csacademy.com/ieeextreme-practice/task/become-as-one/) |  | 9/12 | range check: merging equal values like binary carries (hashing / segment tree) | Math | segtree.h | stmt |
| 19 | [Baker's Competition](https://csacademy.com/ieeextreme-practice/task/bakers-competition/) |  | 1479/3718 | pair counting on segments: offline queries with a Fenwick tree | Math | fenwick.h | stmt |
| 13 | [Protecting the Hive](https://csacademy.com/ieeextreme-practice/task/protecting-the-hive/) |  | 145/436 | DSU on a hexagonal grid maintaining perimeters | Geometry | dsu.h | stmt |
| 17 | [Long Lines](https://csacademy.com/ieeextreme-practice/task/long_lines/) |  | 1150/3806 | count visible pairs with a monotonic stack |  | linear.h | stmt |
| 19 | [Continued Fractions](https://csacademy.com/ieeextreme-practice/task/continued-fractions/) |  | 932/3215 | global add / invert of fractions mod p as 2x2 matrix (Mobius) maps | Math | matrix.h numtheory.h | stmt |
| 11 | [Odd Cycle Check](https://csacademy.com/ieeextreme-practice/task/e21a405d32da71227e2d5fb313fd19d4/) | HARD | 186/649 | online bipartiteness check: DSU with parity | Graphs | dsu.h | tags |
| 11 | [Mister Counter](https://csacademy.com/ieeextreme-practice/task/3dd761f749054a509a0012c5beee0e35/) | HARD | 129/531 | permutation counting with a stack | Math | linear.h combin.h | tags |
| 15 | [Maximum Exploitation](https://csacademy.com/ieeextreme-practice/task/exploitation/) | MEDIUM | 180/965 | two non-overlapping rectangles: 2D prefix sums + best rectangle on each side | DP | grid.h | stmt |
| 14 | [Coupon Codes](https://csacademy.com/ieeextreme-practice/task/coupon-codes/) | MEDIUM | 172/960 | hashing of codes | Strings | hashmap.h | tags |
| 14 | [Rescue Mission](https://csacademy.com/ieeextreme-practice/task/rescue-mission/) | HARD | 100/677 | DSU, segment tree, maximum flow | Graphs | segtree.h dsu.h flow.h | tags |
| 16 | [Outpost](https://csacademy.com/ieeextreme-practice/task/outpost/) |  | 79/736 | max-area rectangle with max-min <= t: monotonic deques / sparse tables |  | linear.h sparse.h | stmt |
| 11 | [Knin](https://csacademy.com/ieeextreme-practice/task/a8030fdc5d7b32664ec5b9addc418f83/) | HARDEST | 44/445 | segment tree under a very low memory limit | Games | segtree.h | tags |
| 18 | [Rectangles and arrays](https://csacademy.com/ieeextreme-practice/task/rectangles-and-arrays-ieeextreme-18/) |  | 145/2572 | largest histogram rectangle with one change (monotonic stack, prefix/suffix) |  | linear.h | stmt |
| 13 | [Sic Semper Tyrannosaurus!](https://csacademy.com/ieeextreme-practice/task/sic-semper-tyrannosaurus/) | HARDEST | 17/333 | segment tree |  | segtree.h | tags |
| 16 | [Poker Tournament](https://csacademy.com/ieeextreme-practice/task/poker-tournament/) |  | 13/255 | range updates, counting member selections: segment tree of products | Combinatorics | segtree.h | stmt |
| 14 | [Parkour](https://csacademy.com/ieeextreme-practice/task/parkour/) | HARDEST | 12/280 | range minimum queries (sparse table) |  | sparse.h | tags |
| 18 | [Corporation](https://csacademy.com/ieeextreme-practice/task/corporation/) |  | 84/2726 | lazy segment tree: range assign + range add + sums |  | segtree.h | stmt |
| 18 | [Another Sliding Window Problem](https://csacademy.com/ieeextreme-practice/task/another-sliding-window-problem/) |  | 83/3187 | optimal pairing cost of windows (sorting, two pointers, data structures) | Greedy | sort.h | stmt |

Also uses data structures: [Safety](https://csacademy.com/ieeextreme-practice/task/safety/) (10), [Vangelis the Batbear and the Bubbles challenge](https://csacademy.com/ieeextreme-practice/task/979a09a0cd8c4e98dd0a690f39a55bd2/) (11), [Bear Sums](https://csacademy.com/ieeextreme-practice/task/bear-sums/) (12), [Monokeros](https://csacademy.com/ieeextreme-practice/task/monokeros/) (13), [Unicornosaurus](https://csacademy.com/ieeextreme-practice/task/unicornosaurus/) (13), [Xranda and Tree](https://csacademy.com/ieeextreme-practice/task/xranda-and-tree/) (13), [The Defensive Walls](https://csacademy.com/ieeextreme-practice/task/defensive-walls/) (14), [Image Convolution](https://csacademy.com/ieeextreme-practice/task/image-convolution/) (15), [Xtreme Teleportation](https://csacademy.com/ieeextreme-practice/task/teleportation/) (15), [Doctor's Appointments](https://csacademy.com/ieeextreme-practice/task/appointment/) (15), [ANDman](https://csacademy.com/ieeextreme-practice/task/andman/) (16), [Scheduler Redux](https://csacademy.com/ieeextreme-practice/task/scheduler-redux/) (16), [He Loves Data Structures](https://csacademy.com/ieeextreme-practice/task/data_structures/) (17), [Tree Queries 2](https://csacademy.com/ieeextreme-practice/task/tree-queries-2/) (17), [Different Xor Values](https://csacademy.com/ieeextreme-practice/task/different_xor/) (17), [Laser Defense](https://csacademy.com/ieeextreme-practice/task/laser-defense/) (18), [Diameter Problem Again](https://csacademy.com/ieeextreme-practice/task/diameter-problem-again/) (19), [Palindrome Matrix](https://csacademy.com/ieeextreme-practice/task/palindrome-matrix/) (19)

## Geometry

*cross product, polygon area, convex hull, point in polygon, Pick, sweep line.* Library: geom.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 10 | [Ellipse Art](https://csacademy.com/ieeextreme-practice/task/ellipse-art/) |  | 79/110 | area of a union of ellipses: numerical integration on a fine grid |  | geom.h | stmt |
| 11 | [Aeneas' cryptographic disc (4th c. B.C.)](https://csacademy.com/ieeextreme-practice/task/d48ada9a7213299f1b24b22b2fb9443f/) | EASY | 1031/1545 | distances between points on a circle (trigonometry) |  | geom.h | tags |
| 18 | [Stick](https://csacademy.com/ieeextreme-practice/task/stick/) |  | 2079/4660 | area of a union of overlapping equal squares (formula) | Math |  | stmt |
| 18 | [Laser Defense](https://csacademy.com/ieeextreme-practice/task/laser-defense/) |  | 1819/4209 | regions cut by beams: count intersections (inversions with Fenwick) + Euler formula | Data structures | fenwick.h geom.h | stmt |
| 17 | [Polygon Cutting](https://csacademy.com/ieeextreme-practice/task/polygon-cutting/) |  | 51/826 | pieces form a tree: max-weight independent set (tree DP), shoelace areas | Trees, DP | geom.h tree.h | stmt |
| 14 | [Linearly Separable Samples](https://csacademy.com/ieeextreme-practice/task/linearly-separable-samples/) | MEDIUM | 62/1270 | separating line test (convex hulls) |  | geom.h | tags |
| 15 | [Polygon](https://csacademy.com/ieeextreme-practice/task/polygon/) | HARD | 9/325 | lattice points of a 3D planar polygon: projection + Pick's theorem | Math | geom.h numtheory.h | stmt |
| 14 | [The Defensive Walls](https://csacademy.com/ieeextreme-practice/task/defensive-walls/) | HARDEST | 6/348 | sweep line with a segment tree | Data structures | geom.h segtree.h | tags |
| 15 | [Squad Game](https://csacademy.com/ieeextreme-practice/task/squad-game/) |  | 6/352 | form triangles minimising the total area (sorting, matching) | Greedy | geom.h | stmt |
| 13 | [Strictly Convex Pairs](https://csacademy.com/ieeextreme-practice/task/strictly-convex-pairs/) | HARDEST | 11/665 | strictly convex polygon: two pointers (rotating calipers) |  | geom.h | tags |
| 18 | [Triumvirates](https://csacademy.com/ieeextreme-practice/task/triumvirates/) |  | 4/3316 | group points into triples minimising stability (sorting + DP) | DP | geom.h | stmt |

Also uses geometry: [Protecting the Hive](https://csacademy.com/ieeextreme-practice/task/protecting-the-hive/) (13), [Image Similarity](https://csacademy.com/ieeextreme-practice/task/image-similarity/) (15), [Pizza Cutter](https://csacademy.com/ieeextreme-practice/task/pizza-cutter/) (16)

## Game theory

*win/lose DP, minimax, Nim, Sprague-Grundy.* Library: game.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [Four Piles](https://csacademy.com/ieeextreme-practice/task/four-piles/) |  | 7/8 | count Nim positions with XOR != 0 over ranges: digit DP over bits | DP | game.h bits.h | stmt |
| 18 | [Stones](https://csacademy.com/ieeextreme-practice/task/stones/) |  | 271/2157 | optimal winning probability: DP / minimax over states | DP | dp.h | stmt |
| 12 | [The Gold-diggers](https://csacademy.com/ieeextreme-practice/task/the-gold-diggers/) | HARD | 40/456 | two-player minimax over (positions, collected coins), BFS distances | Graphs | game.h graph.h | stmt |
| 16 | [Queen](https://csacademy.com/ieeextreme-practice/task/queen/) |  | 38/602 | Wythoff-like queen game with tolerance K: pattern of losing positions | Math | game.h | stmt |

Also uses game theory: [Knin](https://csacademy.com/ieeextreme-practice/task/a8030fdc5d7b32664ec5b9addc418f83/) (11), [Let’s Cheer Up Bob](https://csacademy.com/ieeextreme-practice/task/ca9bc49133da9c3c90df045f4ea8fdd3/) (11), [PIEEEXMan](https://csacademy.com/ieeextreme-practice/task/pieeexman/) (12)

## Interactive

*query protocol, flushing, adaptive strategies.* Library: interactive.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 12 | [Troll Coder](https://csacademy.com/ieeextreme-practice/task/troll-coder/) |  | 1575/2307 | recover a binary sequence from "correct bits" answers |  | interactive.h | stmt |
| 13 | [Concentration Game](https://csacademy.com/ieeextreme-practice/task/concentration-game/) |  | 583/1084 | memory card game: remember revealed cards |  | interactive.h | stmt |
| 11 | [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) | HARDEST | 90/656 | adaptive interactive game on a graph, DP over positions | Graphs, DP | interactive.h graph.h | tags |
| 15 | [Secret Boxes](https://csacademy.com/ieeextreme-practice/task/secret-boxes/) | HARD | 18/249 | adaptive interactive identification of boxes |  | interactive.h | stmt |
| 12 | [Troll Coder - Escape](https://csacademy.com/ieeextreme-practice/task/troll-coder-escape/) |  | 33/1041 | guess a binary sequence with few queries (adaptive group testing) |  | interactive.h | stmt |
| 12 | [PIEEEXMan](https://csacademy.com/ieeextreme-practice/task/pieeexman/) |  | 5/232 | interactive pursuit game on a grid, BFS distances | Games | interactive.h grid.h | stmt |

## Brute force and backtracking

*enumeration, pruning, meet in the middle, state search.* Library: util.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 12 | [Xtreme Fake Coins](https://csacademy.com/ieeextreme-practice/task/xtreme-fake-coins/) |  | 331/578 | brute force over coin pairs, check all weighings | Implementation |  | stmt |
| 10 | [Checkers Challenge](https://csacademy.com/ieeextreme-practice/task/checkers-challenge/) |  | 29/52 | DFS over capture sequences (backtracking) |  |  | stmt |
| 11 | [Octopuses with Watches](https://csacademy.com/ieeextreme-practice/task/59d4aae501fe4ced9ffbf3737acd18a2/) | MEDIUM | 334/781 | backtracking with pruning under a tight memory limit | Greedy |  | tags |
| 18 | [Digits swap](https://csacademy.com/ieeextreme-practice/task/digits-swap/) |  | 966/3103 | maximise a number with at most K digit swaps (DFS with pruning) | Greedy |  | stmt |
| 11 | [Let’s Cheer Up Bob](https://csacademy.com/ieeextreme-practice/task/ca9bc49133da9c3c90df045f4ea8fdd3/) | MEDIUM | 347/1258 | game-tree search (tic-tac-toe), backtracking | Games | game.h | tags |
| 14 | [Coin Collector](https://csacademy.com/ieeextreme-practice/task/coin-collector/) | MEDIUM | 74/660 | maximise rewards from coin sets: enumerate some set counts + greedy | Math |  | stmt |
| 10 | [Weighty Decisions](https://csacademy.com/ieeextreme-practice/task/weighty-decisions/) |  | 2/45 | minimum number of balance weighings (information bound + search) | Math |  | stmt |
| 14 | [Poker Game](https://csacademy.com/ieeextreme-practice/task/poker-game/) | HARD | 32/809 | backtracking over card hands | Greedy |  | tags |
| 16 | [Combo Locks](https://csacademy.com/ieeextreme-practice/task/combo-locks/) | HARD | 34/1208 | choose wheel letters to form many words (heuristic search) |  | trie.h | stmt |

Also uses brute force and backtracking: [Pair Swap Teams](https://csacademy.com/ieeextreme-practice/task/pair-swap-teams/) (13), [Dream Team](https://csacademy.com/ieeextreme-practice/task/dream-team/) (16), [Two Fridges](https://csacademy.com/ieeextreme-practice/task/two-fridges/) (18), [Bounded tuples](https://csacademy.com/ieeextreme-practice/task/bounded-tuples/) (18)

## Bit manipulation

*masks, XOR tricks, subsets, XOR basis.* Library: bits.h.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 12 | [Bit Soccer](https://csacademy.com/ieeextreme-practice/task/bit-soccer/) |  | 499/959 | OR of all player masks that are submasks of the target |  | bits.h | stmt |
| 19 | [Shailesh's Triplet](https://csacademy.com/ieeextreme-practice/task/shailesh-s-triplet/) |  | 2682/5278 | A + B + C = 2N and A ^ B ^ C = N: bitwise construction | Constructive | bits.h | stmt |
| 11 | [RecXor](https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/) | MEDIUM | 583/1172 | XOR of 1..n in O(1), XOR over a rectangle | Math | bits.h | tags |
| 17 | [Different Xor Values](https://csacademy.com/ieeextreme-practice/task/different_xor/) |  | 50/524 | sum over subarrays of a XOR-basis rank (linear basis per right end) | Data structures | bits.h | stmt |
| 15 | [Xtreme Teams](https://csacademy.com/ieeextreme-practice/task/xtreme-teams/) | MEDIUM | 117/1468 | count triples whose topic masks OR to all ones (mask counts, SOS DP) | Combinatorics | bits.h | stmt |
| 13 | [Luck-i-flip](https://csacademy.com/ieeextreme-practice/task/luck-i-flip/) |  | 51/697 | winning draws of bit-string bets (bitmask reasoning, counting) | Combinatorics | bits.h | stmt |
| 14 | [ARM Constant Multiplication](https://csacademy.com/ieeextreme-practice/task/arm/) | HARDEST | 7/340 | multiply by a constant with shifts and adds (search over expressions) | Reverse engineering | bits.h | tags |

Also uses bit manipulation: [Binary Quilts](https://csacademy.com/ieeextreme-practice/task/binary-quilts/) (10), [Preparing for Xtreme 12.0](https://csacademy.com/ieeextreme-practice/task/72a7d67e7e18f4f7d033f7f5a5a09bef/) (11), [Rumour](https://csacademy.com/ieeextreme-practice/task/9ca8fafd184f553a903734761546a224/) (11), [Barrett Reduction](https://csacademy.com/ieeextreme-practice/task/barrett-reduction/) (12), [Restaurant Reopening](https://csacademy.com/ieeextreme-practice/task/restaurant-reopening/) (14), [Arrays Count](https://csacademy.com/ieeextreme-practice/task/arrays-count/) (15), [Array](https://csacademy.com/ieeextreme-practice/task/array/) (16), [IEEE754 Emulator](https://csacademy.com/ieeextreme-practice/task/ieee754-emulator/) (18), [Easy Sum](https://csacademy.com/ieeextreme-practice/task/easy-sum/) (19), [Do you know Expectation?](https://csacademy.com/ieeextreme-practice/task/do-you-know-expectation/) (19), [Domino Path](https://csacademy.com/ieeextreme-practice/task/domino-path/) (19)

## Constructive

*build any object that satisfies the rules; small cases first.* Library: -.

| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |
|---|---|---|---|---|---|---|---|
| 19 | [EDPS](https://csacademy.com/ieeextreme-practice/task/edps/) |  | 6/7 | bracket sequence with given inner lengths (greedy, stack) | Strings | linear.h | stmt |
| 19 | [Hack the coach!](https://csacademy.com/ieeextreme-practice/task/hack-the-coach/) |  | 2947/4301 | construct a counter-test for a wrong root-from-LCA check | Trees | tree.h | stmt |
| 14 | [Making a Tangram](https://csacademy.com/ieeextreme-practice/task/making-tangram/) | MEDIUM | 158/475 | constructive partition of a grid |  |  | tags |
| 11 | [Maximum Sum](https://csacademy.com/ieeextreme-practice/task/04dfa70efd936271ae191cb1a97eb876/) | HARD | 136/809 | arrange numbers to maximise sum of neighbour products (sort, place from the middle) | Greedy | sort.h | tags |
| 13 | [Puzzle of Rooks](https://csacademy.com/ieeextreme-practice/task/puzzle-of-rooks/) |  | 25/341 | move rooks to targets without attacks within an operation budget |  |  | stmt |
| 18 | [Doubled Sequence](https://csacademy.com/ieeextreme-practice/task/doubled-sequence/) | MEDIUM | 41/2574 | Skolem/Langford-like sequence construction |  |  | tags |
| 13 | [Yin Yang](https://csacademy.com/ieeextreme-practice/task/yin-yang/) | HARDEST | 16/1588 | constructive balanced string | Strings |  | tags |

Also uses constructive: [The Lonely Shepherd](https://csacademy.com/ieeextreme-practice/task/lonely-shepherd/) (13), [Magical Stones II](https://csacademy.com/ieeextreme-practice/task/magical-stones-2/) (14), [Big Matrix Small Determinant](https://csacademy.com/ieeextreme-practice/task/big-matrix-small-determinant/) (15), [Pipeline](https://csacademy.com/ieeextreme-practice/task/pipeline/) (16), [Icarus](https://csacademy.com/ieeextreme-practice/task/icarus/) (18), [Shailesh's Triplet](https://csacademy.com/ieeextreme-practice/task/shailesh-s-triplet/) (19)

