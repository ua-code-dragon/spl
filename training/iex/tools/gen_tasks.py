"""Generate the task tables docs/<lang>/tasks.md and docs/<lang>/tasks.csv.

Usage (from the repository root):
    python3 tools/gen_tasks.py docs/en en
    python3 tools/gen_tasks.py docs/uk uk

Data in this file:
    RAW    per task: statistics scraped from csacademy.com/ieeextreme-practice/tasks/ on 2026-10-26
    CLS    per task: topics (first = primary), key skills in English, library headers, source
    TOPICS, SHORT (English) and TOPICS_UK, SHORT_UK, DIFF_UK (Ukrainian): topic names
    TXT    every fixed sentence and column name of the output, per language
The Ukrainian key skills live in skills_uk.txt, one "idx|text" line per task with the same idx as CLS:
when you change a skill in CLS, change the same line there and regenerate both languages."""
import csv, sys, re, collections, pathlib

OUT = pathlib.Path(sys.argv[1])
LANG = sys.argv[2] if len(sys.argv) > 2 else "en"

# idx|url id|edition|difficulty|solved|tried|title   (scraped from csacademy.com/ieeextreme-practice/tasks/)
RAW = r"""0|6f960361da7beb7f3a083f4776c2cf79|11|MEDIUM|428|1504|Jarawi and The Interview
1|ed8629419f140a5a2c923b049aba1224|11|EASY|1533|2387|BeetleBag
2|04dfa70efd936271ae191cb1a97eb876|11|HARD|136|809|Maximum Sum
3|5e98e4b17b3477e671568a437388fb7a|11|HARD|121|714|Pyramid
4|333043935273ab966569971859d1835b|11|MEDIUM|320|906|Collecting Gold
5|72a7d67e7e18f4f7d033f7f5a5a09bef|11|MEDIUM|326|939|Preparing for Xtreme 12.0
6|cd05154d910e28e73ca3930e9a5103f5|11|HARDEST|90|656|King Capture
7|e21a405d32da71227e2d5fb313fd19d4|11|HARD|186|649|Odd Cycle Check
8|d12a7784af1a3d3f6d88601c81a4bb81|11|MEDIUM|205|1000|Game of Life
9|9ca8fafd184f553a903734761546a224|11|EASY|1311|2126|Rumour
10|09f92a575cc006d4a6a7f525f370ec30|11|EASY|1693|3179|Fibonacci
11|7df0da0b0477307be410f4772c739528|11|HARD|276|2140|Math Challenge
12|59d4aae501fe4ced9ffbf3737acd18a2|11|MEDIUM|334|781|Octopuses with Watches
13|e610aba28810ebcf2d3998692269b5a0|11|MEDIUM|444|1495|Gotta Catch 'Em All
14|15443fc9f89feb90bc30096f43b308af|11|HARD|85|573|Lion Territory
15|96c8b1313edd72abf600facb0a14dbab|11|EASY|1539|2739|Running Up Stairs
16|3dd761f749054a509a0012c5beee0e35|11|HARD|129|531|Mister Counter
17|bd45c86a844acd8ffc58b6a965cb0197|11|MEDIUM|317|527|Fill The Pixels
18|a8030fdc5d7b32664ec5b9addc418f83|11|HARDEST|44|445|Knin
19|0186cd4b3a330dc501606737e090e0da|11|MEDIUM|311|853|Shuffle
20|e1e444f71a2a7a69baf4c61ed756aa55|11|MEDIUM|218|980|The Fast and the Curious
21|d48ada9a7213299f1b24b22b2fb9443f|11|EASY|1031|1545|Aeneas' cryptographic disc (4th c. B.C.)
22|ca9bc49133da9c3c90df045f4ea8fdd3|11|MEDIUM|347|1258|Let’s Cheer Up Bob
23|f8d68dbb0c844910797ce64354c66143|11|MEDIUM|583|1172|RecXor
24|5802db6cc4107baa3e135d06a31494b5|11|HARD|235|1910|Quipu Function
25|46e8a03f242b875f1ae5fb84a3b4321f|11|HARD|143|865|Sub Array Sum Problem
26|979a09a0cd8c4e98dd0a690f39a55bd2|11|EASY|1924|2921|Vangelis the Batbear and the Bubbles challenge
27|8761fb7efefcf1d890df1d8d91cae241|11|EASY|2655|3308|Blackgate Penitentiary
28|95352fd33b0e855d337b5b3ed85da3b6|11|MEDIUM|266|515|Orienteering
29|c787255968c972c653677a52599ecc2f|11|HARDEST|71|470|Elementary
30|painters-dilemma|10|-|208|255|Painter's Dilemma
31|memory-management|10|-|119|141|Memory Management
32|weighty-decisions|10|-|2|45|Weighty Decisions
33|safety|10|-|5|45|Safety
34|n-palindromes|10|-|75|126|N-Palindromes
35|ellipse-art|10|-|79|110|Ellipse Art
36|dog-walking|10|-|308|369|Dog Walking
37|binary-quilts|10|-|30|57|Binary Quilts
38|pvnp|10|-|12|32|P = NP?
39|checkers-challenge|10|-|29|52|Checkers Challenge
40|goldbach|10|-|0|125|Goldbach
41|finding-shelter|10|-|0|41|Finding Shelter
42|pirates|10|-|40|76|Pirates
43|telescope-scheduling|12|-|483|1156|Telescope Scheduling
44|pieeexman|12|-|5|232|PIEEEXMan
45|the-gold-diggers|12|HARD|40|456|The Gold-diggers
46|factorial-zeros|12|-|104|678|Factorial Zeros
47|friendly-sequences|12|-|17|397|Friendly Sequences
48|bit-soccer|12|-|499|959|Bit Soccer
49|barrett-reduction|12|-|148|604|Barrett Reduction
50|gotta-catch-em-all|12|-|51|325|Gotta ~ Catch 'Em All
51|product-rectangle|12|-|188|936|Product Rectangle
52|lemons|12|-|868|1881|Lemons
53|magic-spell|12|-|160|833|Magic Spell
54|tree-fun|12|-|96|593|Tree Fun
55|bear-sums|12|-|936|2298|Bear Sums
56|tweedledums-nested-brackets|12|-|16|500|Tweedledum's Nested Brackets
57|xplore|12|-|455|792|Xplore
58|tweedledees-split-brackets|12|-|28|1017|Tweedledee's Split Brackets
59|barter-system|12|-|154|1170|Barter System
60|troll-coder-escape|12|-|33|1041|Troll Coder - Escape
61|make-distinct|12|-|44|1239|Make Distinct
62|organizational-chart|12|-|36|593|Organizational Chart
63|troll-coder|12|-|1575|2307|Troll Coder
64|infinite-snakes-and-ladders|12|-|108|830|Infinite snakes and ladders
65|xtreme-fake-coins|12|-|331|578|Xtreme Fake Coins
66|drawing-rooted-binary-trees|12|-|696|1828|Drawing Rooted Binary Trees
67|monokeros|13|-|131|1548|Monokeros
68|googolplex|13|-|81|412|Googolplex
69|ranged-alfa-pool|13|-|114|387|Ranged Alfa Pool
70|charlie-new-pc|13|-|99|1476|Charlie New PC
71|yin-yang|13|HARDEST|16|1588|Yin Yang
72|xtreme-rappers|13|-|948|3005|Xtreme Rappers
73|batchman-and-gcd|13|-|115|1457|Batchman and GCD
74|alfa-pool|13|-|169|567|Alfa Pool
75|luck-i-flip|13|-|51|697|Luck-i-flip
76|unicornosaurus|13|-|78|740|Unicornosaurus
77|lonely-shepherd|13|-|78|400|The Lonely Shepherd
78|bearcity-renting|13|-|62|507|Bearcity Renting
79|minimum-permutation|13|-|1080|2568|Minimum Permutation
80|xranda-and-tree|13|-|197|991|Xranda and Tree
81|infinite-string|13|-|182|1002|Infinite String
82|impact-factor|13|-|334|796|Impact Factor
83|reshuffle-teams|13|-|129|940|Reshuffle Teams
84|concentration-game|13|-|583|1084|Concentration Game
85|ave-caesar|13|-|200|936|Ave Caesar!
86|pair-swap-teams|13|-|37|685|Pair Swap Teams
87|protecting-the-hive|13|-|145|436|Protecting the Hive
88|sic-semper-tyrannosaurus|13|HARDEST|17|333|Sic Semper Tyrannosaurus!
89|lexical-addition|13|-|277|2565|Lexical Addition
90|puzzle-of-rooks|13|-|25|341|Puzzle of Rooks
91|alfa-universe-weight-sorting|13|HARD|95|534|Alfa Universe Weight Sorting
92|strictly-convex-pairs|13|HARDEST|11|665|Strictly Convex Pairs
93|merchant-association|13|HARDEST|25|674|Merchant Association
94|rescue-mission|14|HARD|100|677|Rescue Mission
95|parkour|14|HARDEST|12|280|Parkour
96|arm|14|HARDEST|7|340|ARM Constant Multiplication
97|coin-collector|14|MEDIUM|74|660|Coin Collector
98|defensive-walls|14|HARDEST|6|348|The Defensive Walls
99|coupon-codes|14|MEDIUM|172|960|Coupon Codes
100|mosaic3|14|EASY|113|608|Mosaic Decoration III
101|crafting-wooden-tables|14|EASY|362|1921|Crafting Wooden Tables
102|mosaic1|14|EASY|2533|2931|Mosaic Decoration I
103|magical-stones-2|14|HARD|29|433|Magical Stones II
104|identifying-infected|14|HARD|63|912|Identifying Infected
105|conway-gameoflife|14|EASY|600|803|Game of Life 2020
106|ieeexplore-indexing|14|MEDIUM|92|767|IEEEXplore Indexing
107|rotational-lights|14|MEDIUM|199|1206|Rotational Lights
108|mosaic2|14|EASY|1025|1645|Mosaic Decoration II
109|nonoverlapping-palindromes|14|MEDIUM|182|1264|Non-Overlapping Palindromes
110|linearly-separable-samples|14|MEDIUM|62|1270|Linearly Separable Samples
111|magical-stones|14|MEDIUM|100|1162|Magical Stones I
112|hotel-wiring|14|EASY|1564|2305|Hotel Wiring
113|the-last-of-us|14|HARDEST|4|95|The Last of Us
114|social-distancing|14|HARDEST|9|526|Social Distancing in Class
115|restaurant-reopening|14|HARDEST|5|176|Restaurant Reopening
116|poker-game|14|HARD|32|809|Poker Game
117|furin-back|14|HARDEST|17|393|Furin Back
118|molecules|14|HARD|52|517|Molecules
119|making-tangram|14|MEDIUM|158|475|Making a Tangram
120|exploitation|15|MEDIUM|180|965|Maximum Exploitation
121|summation|15|HARD|44|2702|Beautiful Summation
122|spies|15|EASY|297|918|Spies of Red and Blue
123|image-convolution|15|EASY|38|499|Image Convolution
124|wordsearch|15|EASY|183|594|Word Search
125|bridge|15|MEDIUM|138|383|Bridge Construction
126|coloring-tiles|15|HARD|16|227|Coloring Tiles
127|training-plan|15|MEDIUM|77|373|Training Plan
128|chameleon|15|MEDIUM|120|416|Chameleon Walk
129|polygon|15|HARD|9|325|Polygon
130|candy-shop|15|HARDEST|22|1331|Candy Shop
131|arrays-count|15|HARD|5|307|Arrays Count
132|xtreme-winners|15|-|31|2416|Xtreme Winners
133|squad-game|15|-|6|352|Squad Game
134|teleportation|15|HARDEST|12|229|Xtreme Teleportation
135|big-matrix-small-determinant|15|HARD|7|1254|Big Matrix Small Determinant
136|the-tortoise-and-the-hare|15|HARDEST|23|999|The Tortoise and The Hare
137|secret-boxes|15|HARD|18|249|Secret Boxes
138|language-learning|15|MEDIUM|151|709|Language Learning
139|rigged-dice|15|EASY|1234|1980|Rigged Dice
140|image-similarity|15|EASY|304|943|Image Similarity
141|expression|15|MEDIUM|151|1698|Expression Evaluation
142|appointment|15|MEDIUM|275|2436|Doctor's Appointments
143|xtreme-teams|15|MEDIUM|117|1468|Xtreme Teams
144|buscompany|15|HARDEST|31|377|Bus Company
145|palindrome-cutting|16|-|33|1578|Palindrome Cutting
146|queries-on-a-tree|16|-|15|173|Queries on a Tree
147|poker-tournament|16|-|13|255|Poker Tournament
148|weird-reward|16|HARD|15|490|Weird Reward
149|pipeline|16|-|53|1134|Pipeline
150|array|16|-|132|1468|Array
151|pizza-cutter|16|-|2528|3563|Pizza Cutter
152|andman|16|HARDEST|205|1177|ANDman
153|dream-team|16|-|303|1960|Dream Team
154|my-treat|16|-|1451|1869|My Treat
155|tourist-taxi-service|16|MEDIUM|116|297|Tourist Taxi Service
156|random-mazes|16|-|98|278|Random Mazes
157|book-cipher|16|-|307|1415|Book Cipher
158|scheduler|16|-|821|2185|Scheduler
159|wireless-network|16|-|156|422|Wireless Network
160|gaius-letters|16|-|3091|3742|Gaius Letters
161|invisible-ghosts|16|MEDIUM|380|610|Invisible Ghosts
162|ascii-dancer|16|-|921|2772|ASCII Dancer
163|robot-versus-fan|16|HARD|58|660|Robot versus Fan
164|queen|16|-|38|602|Queen
165|scheduler-redux|16|-|551|1704|Scheduler Redux
166|travel-service|16|-|713|1624|Travel Service
167|outpost|16|-|79|736|Outpost
168|what-language-am-i-speaking|16|-|464|1109|What Language Am I Speaking?
169|combo-locks|16|HARD|34|1208|Combo Locks
170|BadPasswords|17|-|193|1612|Bad Passwords
171|labradoodle|17|-|515|1987|Labradoodle
172|powerful-strings|17|-|28|1707|Powerful Strings
173|war_games|17|-|1422|2850|War Games
174|resaturant_cipher|17|-|2983|3520|Restaurant Cipher
175|polygon-cutting|17|-|51|826|Polygon Cutting
176|icecubes|17|-|878|1827|Ice Cubes
177|data_structures|17|-|56|569|He Loves Data Structures
178|dalvik|17|-|19|1542|Dalvik
179|caesar_redux|17|-|2438|4446|Caesar Redux
180|long_lines|17|-|1150|3806|Long Lines
181|rectangles|17|-|45|765|Rectangles
182|happy_numbers|17|-|690|4372|Happy Numbers
183|theme_park|17|-|19|296|Theme Park
184|tree-queries-2|17|-|4|343|Tree Queries 2
185|dices|17|-|14|1489|Dice
186|thesaurus|17|-|9|604|Thesaurus
187|ordered-permutations|17|-|285|1418|Ordered Permutations
188|watershed|17|-|795|1461|Watershed
189|combo_locks|17|-|58|522|Combo Lock Redux
190|rumors|17|-|405|1660|Rumors
191|different_xor|17|-|50|524|Different Xor Values
192|national_highways|17|-|161|1110|National Highway System
193|coolsum|17|-|46|2167|Cool Sum
194|Poetry|17|-|1049|2510|Programmer's Poem
195|kings-order|18|-|3162|3547|King's Order
196|balls|18|-|21|3607|Balls
197|this-is-not-an-optimization-problem|18|-|11|1714|This is not an optimization problem
198|digits-swap|18|-|966|3103|Digits swap
199|brick-stacks|18|-|930|2619|Brick stacks
200|rectangles-and-arrays-ieeextreme-18|18|-|145|2572|Rectangles and arrays
201|invertible-pairs|18|-|357|2120|Invertible Pairs
202|sierpinski|18|-|145|1421|Sierpinski
203|corporation|18|-|84|2726|Corporation
204|welcome-ieeextreme-18|18|-|0|4037|Welcome to IEEEXtreme 18.0
205|another-sliding-window-problem|18|-|83|3187|Another Sliding Window Problem
206|disparate-datasets|18|-|343|2645|Disparate Data Sets
207|triumvirates|18|-|4|3316|Triumvirates
208|doubled-sequence|18|MEDIUM|41|2574|Doubled Sequence
209|icarus|18|-|2430|3618|Icarus
210|power-of-three|18|-|684|4462|Power of three
211|cheap-construction|18|-|428|3106|Cheap Construction
212|stick|18|-|2079|4660|Stick
213|increasing-decreasing-permutation|18|-|14|2929|Increasing-decreasing permutations
214|ieee754-emulator|18|-|986|3278|IEEE754 Emulator
215|increasing-table|18|-|1029|4436|Increasing table
216|two-fridges|18|-|2039|5979|Two Fridges
217|bounded-tuples|18|-|11|4059|Bounded tuples
218|queries|18|-|38|3067|Queries
219|star-road|18|-|123|4816|Star Road
220|laser-defense|18|-|1819|4209|Laser Defense
221|halving|18|-|39|2740|Halving
222|stones|18|-|271|2157|Stones
223|visit-egypt|19|-|1874|3273|Visit Egypt
224|diameter-problem-again|19|-|193|2772|Diameter Problem Again
225|white-knights-and-black-warriors|19|-|2438|2871|White knights and Black warriors
226|easy-sum|19|-|6|8|Easy Sum
227|four-piles|19|-|7|8|Four Piles
228|new-casino-game|19|-|8|9|New Casino Game
229|edps|19|-|6|7|EDPS
230|raju-s-matrix-runs|19|-|9|9|Raju's Matrix Runs
231|become-as-one|19|-|9|12|Become as One
232|circular-permutation|19|-|5|7|Circular Permutation
233|welcome-to-ieeextreme-19|19|-|0|4128|Welcome to IEEEXtreme 19.0
234|palindrome-matrix|19|-|3303|4559|Palindrome Matrix
235|squared-gaps|19|-|1307|3403|Squared Gaps
236|magic-wands|19|-|4186|4603|Magic Wands
237|secure-elliptic-curve-point-addition|19|-|4877|5159|Secure Elliptic Curve Point Addition
238|application-abuse|19|-|1893|3227|Application Abuse
239|bitonic-sequences|19|-|574|4441|Bitonic Sequences
240|airline-traveling|19|-|1852|3728|Airline Traveling
241|the-twin-occurrence-quest|19|-|4548|5844|The Twin Occurrence Quest
242|hack-the-coach|19|-|2947|4301|Hack the coach!
243|beatrice-and-the-dream-tree|19|-|1679|3848|Beatrice and the Dream Tree
244|do-you-know-expectation|19|-|1288|3406|Do you know Expectation?
245|domino-path|19|-|637|3377|Domino Path
246|bakers-competition|19|-|1479|3718|Baker's Competition
247|continued-fractions|19|-|932|3215|Continued Fractions
248|shailesh-s-triplet|19|-|2682|5278|Shailesh's Triplet
249|stable-power-network|19|-|2212|4347|Stable Power Network
250|ladder|19|-|377|3556|Ladder
251|sequence-decomposition|19|-|624|3108|Sequence Decomposition"""

# idx|topics (first = primary)|key skills|library headers|source (T = CS Academy tags, S = statement)
CLS = r"""0|str,bs|subsequence queries: next-occurrence table + binary search|strutil.h search.h|T
1|dp|0/1 knapsack|dp.h|T
2|constr,greedy|arrange numbers to maximise sum of neighbour products (sort, place from the middle)|sort.h|T
3|dp,math|DP on a number triangle + closed formulas|dp.h|T
4|graph|Dijkstra shortest paths|paths.h|T
5|dp,bits|bitmask DP over subsets (exponential states)|dp.h bits.h|T
6|inter,graph,dp|adaptive interactive game on a graph, DP over positions|interactive.h graph.h|T
7|ds,graph|online bipartiteness check: DSU with parity|dsu.h|T
8|impl|cellular automaton on a torus (simulation)|grid.h|T
9|tree,bits|distance in an implicit complete binary tree via bit shifts (LCA)|bits.h|T
10|math,dp|linear recurrence by matrix exponentiation|matrix.h|T
11|math|a^C(b,c) mod p: exponent mod p-1 (Euler/Fermat), binomial mod composite (CRT)|numtheory.h combin.h|T
12|search,greedy|backtracking with pruning under a tight memory limit|-|T
13|dp,bs|grid DP for minimal initial value, binary search on the answer|dp.h search.h|T
14|dp|grid DP, 2D prefix sums|dp.h grid.h|T
15|impl,math|Fibonacci-like recurrence with big integers|bignum.h|T
16|ds,math|permutation counting with a stack|linear.h combin.h|T
17|graph|flood fill on a pixel grid|grid.h|T
18|ds,game|segment tree under a very low memory limit|segtree.h|T
19|graph|maximum bipartite matching|flow.h|T
20|dp,graph|DFS + DP on a graph|graph.h dp.h|T
21|geom|distances between points on a circle (trigonometry)|geom.h|T
22|search,game|game-tree search (tic-tac-toe), backtracking|game.h|T
23|bits,math|XOR of 1..n in O(1), XOR over a rectangle|bits.h|T
24|math|sieve, counting prime factors over ranges|numtheory.h|T
25|dp|sum of all subarray / submatrix sums by contribution, prefix sums|grid.h|T
26|graph,ds|cycle detection with DSU / DFS|dsu.h graph.h|T
27|greedy|sorting with ties, ranges of positions|sort.h|T
28|graph,dp|Dijkstra between control points + bitmask TSP|paths.h dp.h|T
29|impl,dp|ad hoc word encoding, DP over the ways to split the word|-|T
30|dp,greedy|two brushes, minimise colour changes: DP over (position, other brush)|dp.h|S
31|impl|simulate FIFO and LRU page replacement|linear.h hashmap.h|S
32|search,math|minimum number of balance weighings (information bound + search)|-|S
33|str,ds|substring equality under edits: rolling hash in a segment tree|strutil.h segtree.h|S
34|comb,str|count strings that become palindromes with exactly n changes (counting over mirrored pairs)|combin.h dp.h|S
35|geom|area of a union of ellipses: numerical integration on a fine grid|geom.h|S
36|greedy|sort, cut at the K-1 largest gaps|sort.h|S
37|graph,bits|BFS over 2^25 board states stored as bitmasks|graph.h bits.h|S
38|math,greedy|bounds of rank sums with missing values (sorting, greedy)|sort.h|S
39|search|DFS over capture sequences (backtracking)|-|S
40|math|primes: sieve / Miller-Rabin, sum of three primes|numtheory.h|S
41|graph,bs|bottleneck assignment: binary search + bipartite matching, then min-cost matching|flow.h search.h|S
42|graph|label islands by flood fill, 0-1 BFS counting island crossings|grid.h paths.h|S
43|dp,bs|weighted interval scheduling: sort by end, DP + binary search|dp.h search.h sort.h|S
44|inter,game|interactive pursuit game on a grid, BFS distances|interactive.h grid.h|S
45|game,graph|two-player minimax over (positions, collected coins), BFS distances|game.h graph.h|S
46|math,bs|Legendre's formula for base B (factorise B) + binary search on n|numtheory.h search.h|S
47|comb,dp|counting non-decreasing sequences under prefix-sum bounds (DP + prefix sums)|dp.h|S
48|bits|OR of all player masks that are submasks of the target|bits.h|S
49|math,bits,rev|exact division by multiply-and-shift, 64/128-bit arithmetic|bits.h|S
50|graph,bs|binary search on time + bipartite matching (holes take two)|flow.h search.h|S
51|math,dp|rectangle sum = (sum of A range)(sum of B range): max/min subarray sums (Kadane)|dp.h|S
52|dp|worst-case optimal search on a line (egg-drop style minimax DP)|dp.h|S
53|rev,str|discover the hidden string function from the examples|-|S
54|tree|path additions: difference on tree + LCA (or HLD), then maximum|tree.h|S
55|greedy,ds|pair with a given sum: hash set or sort + two pointers|hashmap.h sort.h|S
56|str,comb|bracket depth, counting re-insertions with prefix balances|segtree.h|S
57|text|parse JSON records, compute authors' h-index, sort|sort.h hashmap.h|S
58|str,dp|split brackets into two valid sequences (stack, DP)|dp.h|S
59|graph|exchange rates as products along paths (DFS / weighted DSU)|graph.h dsu.h|S
60|inter|guess a binary sequence with few queries (adaptive group testing)|interactive.h|S
61|greedy|minimal +-1 operations to make values distinct (sort, greedy with a heap)|sort.h heap.h|S
62|tree|bounds of subtree sizes with missing reports (tree DP)|tree.h|S
63|inter|recover a binary sequence from "correct bits" answers|interactive.h|S
64|impl|board game simulation (snakes and ladders)|-|S
65|search,impl|brute force over coin pairs, check all weighings|-|S
66|tree,impl|build a binary tree, ASCII drawing by in-order columns|-|S
67|tree,ds|BST insertion depths: predecessor/successor in an ordered set (Fenwick tree)|fenwick.h|S
68|math|huge exponent: cycle of 5^k mod 100|numtheory.h|S
69|comb,dp|count tournament scenarios by point total (doubling streaks)|dp.h|S
70|dp|multiple-choice knapsack: one part per type, maximum cost within budget|dp.h|S
71|constr,str|constructive balanced string|-|T
72|greedy,math|maximum number of 3-word phrases from two word counts (formula)|-|S
73|math|distinct GCDs of subsequences: check every d via its multiples (harmonic sum)|numtheory.h|S
74|comb,dp|point totals with doubling winning streaks (counting DP)|dp.h|S
75|bits,comb|winning draws of bit-string bets (bitmask reasoning, counting)|bits.h|S
76|greedy,ds|cover broken intervals with fewest powers (interval covering, sweep)|sort.h|S
77|tree,constr|tree cut and toggles independent of the colouring (parity, tree DP)|tree.h|S
78|graph|streets that stay two-way in every strong orientation = bridges|graph.h|S
79|greedy|merge a sorted set into an array for the smallest permutation|sort.h|S
80|tree,ds|sum over pairs of the max edge on the path: Kruskal order + DSU sizes|dsu.h|S
81|math|locate an index in the string of all words by length (powers of B)|-|S
82|text|parse JSON records, aggregate citations per year, compute impact factor|hashmap.h sort.h|S
83|greedy,str|group 4 teams around a table: all team orders x rotations with prefix counts|-|S
84|inter|memory card game: remember revealed cards|interactive.h|S
85|str|recursive validity of strings (split points, comparisons), memoisation|strutil.h|S
86|greedy,search|minimum swaps to group teams on a circle (cycle counting over team orders)|combin.h|S
87|ds,geom|DSU on a hexagonal grid maintaining perimeters|dsu.h|S
88|ds|segment tree|segtree.h|T
89|greedy,math|shortest, then lexicographically smallest sum of terms from [A, B]|-|S
90|constr|move rooks to targets without attacks within an operation budget|-|S
91|graph|known order pairs from comparisons: transitive closure / topological order|graph.h|S
92|geom|strictly convex polygon: two pointers (rotating calipers)|geom.h|T
93|dp,tree|tree DP|tree.h|T
94|ds,graph|DSU, segment tree, maximum flow|segtree.h dsu.h flow.h|T
95|ds|range minimum queries (sparse table)|sparse.h|T
96|bits,rev|multiply by a constant with shifts and adds (search over expressions)|bits.h|T
97|search,math|maximise rewards from coin sets: enumerate some set counts + greedy|-|S
98|geom,ds|sweep line with a segment tree|geom.h segtree.h|T
99|ds,str|hashing of codes|hashmap.h|T
100|math|arithmetic on tile counts|-|T
101|bs|binary search on the answer|search.h|T
102|math|ceiling divisions and costs|-|T
103|graph,constr|BFS over stone states, constructive answer|graph.h bits.h|T
104|tree|lowest common ancestor|tree.h|T
105|impl|Game of Life simulation|grid.h|T
106|text,impl|parse records, build an inverted index|hashmap.h sort.h|T
107|str|KMP on cyclic patterns|strutil.h|T
108|math|arithmetic on tile counts|-|T
109|str,dp|Manacher: best palindrome ending before / starting after each position|strutil.h|S
110|geom|separating line test (convex hulls)|geom.h|T
111|graph|BFS over states|graph.h|T
112|greedy|sorting|sort.h|T
113|graph|Dijkstra (output only task)|paths.h|T
114|dp,tree|tree DP|tree.h|T
115|dp,bits|bitmask DP (exponential states)|dp.h bits.h|T
116|search,greedy|backtracking over card hands|-|T
117|impl|ad hoc|-|T
118|math|chemical formulas: counting atoms, linear equations|matrix.h|T
119|constr|constructive partition of a grid|-|T
120|ds,dp|two non-overlapping rectangles: 2D prefix sums + best rectangle on each side|grid.h|S
121|math|sum P^k k^Q mod M (M not prime): matrix power / divide and conquer with binomials|matrix.h combin.h|S
122|tree,impl|simulate information passing in two hierarchies (depths, events)|tree.h|S
123|str,ds|2D pattern matching (row hashing / KMP)|strutil.h|S
124|impl,str|find words in 8 directions (trie for many words)|trie.h|S
125|tree|join two trees: diameters and radii, max(d1, d2, r1 + r2 + 1)|tree.h|S
126|dp,comb|row-by-row DP over colour patterns (counting)|dp.h|S
127|dp|DP with "at most K consecutive" constraint (monotonic queue)|dp.h linear.h|S
128|graph,bs|binary search on C + Dijkstra|paths.h search.h|S
129|geom,math|lattice points of a 3D planar polygon: projection + Pick's theorem|geom.h numtheory.h|S
130|comb,dp|generating functions, FFT/NTT|fft.h combin.h|T
131|math,bits|counting arrays from an OR expression (ad hoc counting)|combin.h|T
132|rev,text|code golf: map a team name to its edition with the shortest program|-|S
133|geom,greedy|form triangles minimising the total area (sorting, matching)|geom.h|S
134|tree,ds|bottleneck path queries: maximum spanning tree + LCA (or offline DSU)|dsu.h tree.h|S
135|math,constr|construct a matrix with a given determinant (recursion)|matrix.h|T
136|graph|Dijkstra, choosing a city to block|paths.h|T
137|inter|adaptive interactive identification of boxes|interactive.h|S
138|dp,comb|distinct subsequences with an index gap > K (DP + prefix sums, last occurrence)|dp.h hashmap.h|S
139|math,impl|likelihood comparison: count the sixes|-|S
140|impl,geom|all rotations/flips and translations, count overlapping pixels|grid.h|S
141|str,text|expression parsing (recursive descent / two stacks), validity checks|linear.h|S
142|greedy,ds|interval scheduling: sweep days, heap by deadline|heap.h sort.h|S
143|bits,comb|count triples whose topic masks OR to all ones (mask counts, SOS DP)|bits.h|S
144|tree,comb|average path lengths per company: contribution counting on a tree|tree.h|S
145|comb,str|arrays splittable into even palindromes: DP over primitive palindromes|combin.h dp.h|S
146|tree,comb|sum over edge subsets of squared component sums, with updates|tree.h|S
147|ds,comb|range updates, counting member selections: segment tree of products|segtree.h|S
148|str,dp|expression grammar, DP over substrings that are valid expressions|linear.h|S
149|impl,constr|design a 3D pipe network (construction / search on a 3D grid)|-|S
150|comb,bits|count arrays with a given OR-expression length, modulo 4|combin.h|S
151|impl,geom|normalise angles modulo 180, count distinct cuts|sort.h|S
152|tree,ds|path products with point updates: HLD + segment tree (mod product)|tree.h segtree.h|S
153|dp,search|one player per position within budget (multiple-choice knapsack)|dp.h|S
154|greedy,math|minimum days to balance dinners (counting)|-|S
155|graph|shortest rides starting with 5 distinct streets: Dijkstra on expanded states|paths.h|S
156|graph|maze rules: connectivity and loops in regions (BFS / DSU)|graph.h dsu.h grid.h|S
157|text,str|strip XML tags, build the character grid, decode (r, c) pairs|-|S
158|greedy,math|jobs of length 2^x on M workers, time mod 1e9+7|numtheory.h heap.h|S
159|graph|minimum spanning tree with upgrade costs (Kruskal)|graph.h dsu.h|S
160|str|Caesar cipher (the statement itself is encrypted)|-|S
161|graph|BFS with the lexicographically smallest path, ghosts as multi-source BFS|graph.h grid.h|S
162|impl|simulate commands, print ASCII art|-|S
163|impl,math|periodic dust path vs robot path: simulate up to the period (lcm)|numtheory.h|S
164|game,math|Wythoff-like queen game with tolerance K: pattern of losing positions|game.h|S
165|greedy,ds|jobs of length 2^x with equal lengths: heap of worker loads|heap.h|S
166|dp,graph|refuelling decisions at stations: DP / Dijkstra over (station, state)|paths.h dp.h|S
167|ds|max-area rectangle with max-min <= t: monotonic deques / sparse tables|linear.h sparse.h|S
168|impl,str|evaluate a decision tree on character presence|-|S
169|search|choose wheel letters to form many words (heuristic search)|trie.h|S
170|str,text|detect iterated passwords: common prefix/suffix, numeric and month sequences|-|S
171|str|blended words: prefix/suffix lookups in hash sets|hashmap.h trie.h|S
172|str,comb|Aho-Corasick automaton + DP over length (sum of 2^occurrences)|trie.h dp.h|S
173|impl|card game with queues, draw detection by repeated states|linear.h hashmap.h|S
174|rev,str|deduce the encoding scheme from the examples|-|S
175|geom,tree,dp|pieces form a tree: max-weight independent set (tree DP), shoelace areas|geom.h tree.h|S
176|dp|grid DP with a limit on consecutive "bad" cells|dp.h|S
177|tree,ds,math|subtree updates with Euler's totient: Euler tour + Fenwick/segment tree, sieve|tree.h fenwick.h numtheory.h|S
178|rev|read Dalvik (smali) bytecode and reimplement it efficiently|-|S
179|str|Caesar cipher: detect plaintext vs ciphertext|-|S
180|ds|count visible pairs with a monotonic stack|linear.h|S
181|math,comb|group sizes whose rectangles have coprime sides (gcd, factorisation)|numtheory.h|S
182|math,dp|happy numbers in a range: precompute small sums, digit DP|dp.h|S
183|graph|change costs without creating a negative cycle: Bellman-Ford / potentials|paths.h|S
184|tree,ds|path scores with updates: HLD + segment tree of linear maps|tree.h segtree.h|S
185|comb,math|dice-sum probability via generating functions mod 998244353 (NTT)|fft.h combin.h|S
186|text|parse documents and a hierarchical thesaurus, map terms to top topics|hashmap.h|S
187|comb,dp|permutations with a given up/down pattern: O(n^2) DP with prefix sums|dp.h|S
188|graph,dp|water flow on a grid: process cells by decreasing elevation (DAG)|grid.h sort.h|S
189|graph,comb|BFS shortest moves + number of shortest paths mod p|graph.h|S
190|graph|possible rumour sources: reachability, SCC condensation|graph.h|S
191|bits,ds|sum over subarrays of a XOR-basis rank (linear basis per right end)|bits.h|S
192|graph|edges in any MST: Kruskal by equal-weight groups + bridges|graph.h dsu.h|S
193|comb,math|binomial sums by residue mod 2^k (polynomial arithmetic mod x^(2^k) - 1)|fft.h combin.h|S
194|str,impl|rhyme scheme labelling (suffix comparison)|hashmap.h|S
195|graph|topological sort with priorities (heap), cycle detection|graph.h heap.h|S
196|math,comb|tiles hit by multiples: inclusion-exclusion over lcm with pruning|numtheory.h|S
197|tree,comb|sum of Steiner tree weights over all k-subsets: edge contributions with binomials + NTT|fft.h combin.h tree.h|S
198|search,greedy|maximise a number with at most K digit swaps (DFS with pruning)|-|S
199|greedy|fewest stacks: sort + greedy with binary search (chains)|sort.h search.h|S
200|ds|largest histogram rectangle with one change (monotonic stack, prefix/suffix)|linear.h|S
201|dp|maximum subarray with optional sign flips of pairs (Kadane with states)|dp.h|S
202|math|Sierpinski / Pascal triangle mod 2: recursion on coordinates|combin.h|S
203|ds|lazy segment tree: range assign + range add + sums|segtree.h|S
204|impl|print a message (warm-up)|-|S
205|ds,greedy|optimal pairing cost of windows (sorting, two pointers, data structures)|sort.h|S
206|text|CSV parsing, joining records, filling missing fields|hashmap.h|S
207|geom,dp|group points into triples minimising stability (sorting + DP)|geom.h|S
208|constr|Skolem/Langford-like sequence construction|-|T
209|tree,constr|build a binary tree that traps a walk (simulation + construction)|-|S
210|math|is N a power of three (big N: logarithm / big integer)|bignum.h|S
211|str,graph|substring rules connect islands: hashing + DSU for every k|strutil.h dsu.h|S
212|geom,math|area of a union of overlapping equal squares (formula)|-|S
213|comb|sum over permutations of minimal adjacent swaps (inversion counting mod M)|combin.h|S
214|rev,bits|emulate IEEE 754 single precision with lookup tables (bit fields)|bits.h|S
215|comb,dp|2 x N increasing tables with row restrictions (ballot-style DP)|dp.h combin.h|S
216|greedy,search|two temperatures stabbing all intervals (sweep, try all values)|-|S
217|comb,search|count integer assignments under sum constraints, detect infinity|dp.h|S
218|tree,comb|sum over edge subsets of squared component sums, with updates|tree.h|S
219|tree,dp|best path in a tree by restaurant stars (tree DP)|tree.h|S
220|geom,ds|regions cut by beams: count intersections (inversions with Fenwick) + Euler formula|fenwick.h geom.h|S
221|comb,dp|count permutations consistent with min/max halving rules|combin.h|S
222|game,dp|optimal winning probability: DP / minimax over states|dp.h|S
223|dp,comb|ordered ways to pay an amount (coin DP, order matters)|dp.h|S
224|tree,ds|diameter of node sets with negative weights: segment tree of diameter endpoints + LCA|tree.h segtree.h|S
225|tree|distance from a path to the nearest white node: multi-source BFS + path minimum|tree.h graph.h|S
226|ds,bits|sum over subarrays by thresholds per bit (two pointers, counting)|bits.h|S
227|game,dp|count Nim positions with XOR != 0 over ranges: digit DP over bits|game.h bits.h|S
228|comb,math|expected value with random non-attacking rooks (linearity of expectation)|combin.h|S
229|constr,str|bracket sequence with given inner lengths (greedy, stack)|linear.h|S
230|dp,graph|longest increasing path in a grid: DP over cells sorted by value|grid.h sort.h|S
231|ds,math|range check: merging equal values like binary carries (hashing / segment tree)|segtree.h|S
232|bs,greedy|minimise the maximum circular move: try rotations and directions|search.h|S
233|impl|print a message (warm-up)|-|S
234|greedy,ds|cells forced equal (DSU over mirrored positions), choose the median per group|dsu.h sort.h|S
235|dp,str|sequence alignment DP with a modified gap cost|dp.h|S
236|greedy|flip K consecutive: greedy left to right with a difference array|-|S
237|math|modular inverse, elliptic curve point addition|numtheory.h|S
238|text|parse logs, aggregate per user, detect rule violations|hashmap.h sort.h|S
239|comb,dp|count bitonic compositions for every N (partition-style DP / generating functions)|dp.h fft.h|S
240|graph,math|exact total miles on a star of flights: parity and gcd reasoning|numtheory.h graph.h|S
241|bs|first/last occurrence: lower and upper bound|search.h|S
242|constr,tree|construct a counter-test for a wrong root-from-LCA check|tree.h|S
243|tree|indistinguishable nodes: rooted tree hashing / automorphisms|tree.h hashmap.h|S
244|comb,bits|E[X^K] for XOR of a random subset: X is uniform over the linear span|bits.h|S
245|graph,bits|domino subsets forming a chain: Euler path (degrees + connectivity) over subsets|bits.h dsu.h|S
246|ds,math|pair counting on segments: offline queries with a Fenwick tree|fenwick.h|S
247|ds,math|global add / invert of fractions mod p as 2x2 matrix (Mobius) maps|matrix.h numtheory.h|S
248|bits,constr|A + B + C = 2N and A ^ B ^ C = N: bitwise construction|bits.h|S
249|graph,bs|minimise max risk, then time: sort/binary search on risk + Dijkstra|paths.h dsu.h|S
250|rev|reproduce the output of a given Python program efficiently|-|S
251|str,greedy|decompose into "112012" subsequences: greedy counters|-|S"""

TOPICS = collections.OrderedDict([
    ("impl", ("Implementation and simulation", "careful reading, simulation, ASCII output, edge cases", "grid.h, io.h")),
    ("str", ("Strings", "ciphers, KMP, hashing, palindromes (Manacher), tries, Aho-Corasick, brackets", "strutil.h, trie.h, hashmap.h")),
    ("text", ("Text and data processing", "IEEE Xplore tasks: parse JSON/CSV/XML-like input, group, sort, aggregate", "hashmap.h, sort.h")),
    ("rev", ("Reverse engineering and emulation", "guess a hidden function from examples, emulate code / number formats", "bits.h")),
    ("math", ("Math and number theory", "modular arithmetic, primes, gcd, fast exponentiation, formulas", "numtheory.h, matrix.h, bignum.h")),
    ("comb", ("Combinatorics and probability", "counting mod p, binomials, inclusion-exclusion, expectation, generating functions", "combin.h, fft.h, dp.h")),
    ("greedy", ("Greedy and sorting", "sort + greedy choice, exchange argument, intervals, heaps", "sort.h, heap.h")),
    ("bs", ("Binary search", "lower/upper bound, binary search on the answer", "search.h")),
    ("dp", ("Dynamic programming", "knapsack, LIS/LCS, grid DP, bitmask DP, tree DP, counting DP", "dp.h")),
    ("graph", ("Graphs", "BFS/DFS, shortest paths, MST, topological sort, SCC, bridges, matching, flow", "graph.h, paths.h, flow.h, grid.h")),
    ("tree", ("Trees", "rooting, subtree sizes, LCA, diameter, tree DP, HLD, Euler tour", "tree.h")),
    ("ds", ("Data structures", "prefix sums, Fenwick, segment tree (lazy), sparse table, DSU, monotonic stack/queue, hashing", "fenwick.h, segtree.h, sparse.h, dsu.h, linear.h")),
    ("geom", ("Geometry", "cross product, polygon area, convex hull, point in polygon, Pick, sweep line", "geom.h")),
    ("game", ("Game theory", "win/lose DP, minimax, Nim, Sprague-Grundy", "game.h")),
    ("inter", ("Interactive", "query protocol, flushing, adaptive strategies", "interactive.h")),
    ("search", ("Brute force and backtracking", "enumeration, pruning, meet in the middle, state search", "util.h")),
    ("bits", ("Bit manipulation", "masks, XOR tricks, subsets, XOR basis", "bits.h")),
    ("constr", ("Constructive", "build any object that satisfies the rules; small cases first", "-")),
])

SHORT = dict(impl="Implementation", str="Strings", text="Text processing", rev="Reverse engineering", math="Math",
             comb="Combinatorics", greedy="Greedy", bs="Binary search", dp="DP", graph="Graphs", tree="Trees",
             ds="Data structures", geom="Geometry", game="Games", inter="Interactive", search="Brute force",
             bits="Bits", constr="Constructive")

TOPICS_UK = dict(
    impl=("Реалізація і моделювання", "уважне читання, моделювання, ASCII-виведення, граничні випадки"),
    str=("Рядки", "шифри, KMP, гешування, паліндроми (Манакер), префіксні дерева, Ахо–Корасік, дужки"),
    text=("Обробка тексту і даних", "задачі IEEE Xplore: розбір введення у форматах JSON/CSV/XML, групування, сортування, агрегування"),
    rev=("Зворотна розробка та емуляція", "відгадати приховану функцію за прикладами, емулювати код / формати чисел"),
    math=("Математика і теорія чисел", "модульна арифметика, прості числа, НСД, швидке піднесення до степеня, формули"),
    comb=("Комбінаторика і ймовірності", "підрахунок за модулем p, біноміальні коефіцієнти, включення-виключення, математичне сподівання, твірні функції"),
    greedy=("Жадібні алгоритми і сортування", "сортування + жадібний вибір, аргумент обміну, відрізки, купи"),
    bs=("Двійковий пошук", "нижня/верхня межа (lower/upper bound), двійковий пошук за відповіддю"),
    dp=("Динамічне програмування", "рюкзак, LIS/LCS, DP на сітці, DP на бітових масках, DP на дереві, DP для підрахунку"),
    graph=("Графи", "BFS/DFS, найкоротші шляхи, MST, топологічне сортування, SCC, мости, паросполучення, потоки"),
    tree=("Дерева", "підвішування за корінь, розміри піддерев, LCA, діаметр, DP на дереві, HLD, ейлерів обхід"),
    ds=("Структури даних", "префіксні суми, дерево Фенвіка, дерево відрізків (з відкладеним оновленням), розріджена таблиця, DSU, монотонний стек/черга, гешування"),
    geom=("Геометрія", "векторний добуток, площа многокутника, опукла оболонка, точка в многокутнику, формула Піка, замітальна пряма"),
    game=("Теорія ігор", "DP виграшних/програшних позицій, мінімакс, Нім, теорема Шпрага–Ґранді"),
    inter=("Інтерактивні задачі", "протокол запитів, скидання буфера, адаптивні стратегії"),
    search=("Повний перебір і перебір із поверненням", "перебір варіантів, відсікання, «зустріч посередині», пошук у просторі станів"),
    bits=("Бітові операції", "маски, трюки з XOR, підмножини, XOR-базис"),
    constr=("Конструктивні задачі", "побудувати будь-який об’єкт, що задовольняє правила; спершу розібрати малі випадки"),
)
SHORT_UK = dict(impl="Реалізація", str="Рядки", text="Обробка тексту", rev="Зворотна розробка", math="Математика",
                comb="Комбінаторика", greedy="Жадібні", bs="Двійковий пошук", dp="DP", graph="Графи", tree="Дерева",
                ds="Структури даних", geom="Геометрія", game="Ігри", inter="Інтерактивні", search="Перебір",
                bits="Біти", constr="Конструктивні")
DIFF_UK = dict(EASY="легка", MEDIUM="середня", HARD="складна", HARDEST="найскладніша")

# Every user-visible string of tasks.md / tasks.csv, per language.
TXT = dict(
    en=dict(
        csv_head=["edition", "title", "difficulty", "solved", "tried", "solve_rate_pct", "primary_topic",
                  "all_topics", "key_skills", "library", "classified_from", "url"],
        src_long=dict(T="CS Academy tags", S="statement"), src_short=dict(T="tags", S="stmt"),
        title="# IEEEXtreme task archive by topic\n",
        intro="All 252 tasks of the [IEEEXtreme practice community](https://csacademy.com/ieeextreme-practice/tasks/) "
              "on CS Academy (IEEEXtreme 10.0 to 19.0), grouped by the algorithmic skill they need.\n",
        how="How the topics were assigned:",
        tags="- **tags**: CS Academy has its own topic tags for {n} of the tasks ({eds}); those are used as they are.",
        stmt="- **stmt**: every other task was classified by reading its statement. Treat these as a strong hint, not a guarantee: "
             "a task can need more than its listed skills.\n",
        cols="Columns: **Ed.** edition, **Diff.** CS Academy difficulty (where given), **Solved** = accepted / tried users "
             "in the practice archive (higher = easier in practice), **Lib** = the headers of [`lib/`](../../lib) that cover the skill. "
             "The same data as a spreadsheet: [tasks.csv](tasks.csv).\n",
        note="Note: some 19.0 tasks show very small numbers (for example 6/8) because only a few people have tried them in the archive.\n",
        summary="## Summary\n", sum_head="| Topic | Primary | Total | What to know | Library |",
        sum_note="\n*Primary* counts each task once (by its main topic); *Total* counts every topic a task touches.\n",
        by_ed="### By edition\n", topic="Topic", tasks_row="**Tasks**",
        first="### Suggested first tasks\n",
        first_note="Per topic, the three tasks most people solved in the practice archive (primary topic, at least 50 attempts):\n",
        library="Library", tab_head="| Ed. | Task | Diff. | Solved | Key skills | Also | Lib | Src |",
        also="\nAlso uses {name}: "),
    uk=dict(
        csv_head=["випуск", "назва", "складність", "розв’язали", "пробували", "відсоток_розв’язків", "основна_тема",
                  "усі_теми", "ключові_навички", "бібліотека", "джерело_класифікації", "посилання"],
        src_long=dict(T="теги CS Academy", S="умова"), src_short=dict(T="теги", S="умова"),
        title="# Архів задач IEEEXtreme за темами\n",
        intro="Усі 252 задачі [практичної спільноти IEEEXtreme](https://csacademy.com/ieeextreme-practice/tasks/) "
              "на CS Academy (IEEEXtreme 10.0–19.0), згруповані за алгоритмічними навичками, які для них потрібні. "
              "Назви задач подано мовою оригіналу.\n",
        how="Як визначено теми:",
        tags="- **теги**: CS Academy має власні тематичні теги для {n} задач ({eds}); їх використано без змін.",
        stmt="- **умова**: решту задач класифіковано за текстом умови. Вважайте це вагомою підказкою, а не гарантією: "
             "задача може вимагати більше, ніж перелічені навички.\n",
        cols="Стовпці: **Вип.** — випуск змагання, **Скл.** — складність за CS Academy (якщо вказана), "
             "**Розв’язали** — скільки учасників розв’язали задачу / пробували її в практичному архіві "
             "(більша частка — отже, на практиці легша), **Бібл.** — заголовні файли [`lib/`](../../lib), що покривають потрібну навичку. "
             "Ті самі дані у вигляді таблиці: [tasks.csv](tasks.csv).\n",
        note="Примітка: деякі задачі 19.0 мають дуже малі числа (наприклад, 6/8), бо в архіві їх пробували лише кілька людей.\n",
        summary="## Зведення\n", sum_head="| Тема | Основна | Усього | Що треба знати | Бібліотека |",
        sum_note="\n*Основна* — кожну задачу враховано один раз (за головною темою); *Усього* — враховано кожну тему, якої задача стосується.\n",
        by_ed="### За випусками\n", topic="Тема", tasks_row="**Задач**",
        first="### З чого почати\n",
        first_note="Для кожної теми — три задачі, які найчастіше розв’язували в практичному архіві (основна тема, щонайменше 50 спроб):\n",
        library="Бібліотека", tab_head="| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |",
        also="\nТема «{name}» потрібна також у задачах: "),
)[LANG]

if LANG == "uk":
    TOPICS = collections.OrderedDict((k, TOPICS_UK[k] + (v[2],)) for k, v in TOPICS.items())
    SHORT = SHORT_UK
    SKILLS_UK = {}
    for line in (pathlib.Path(__file__).parent / "skills_uk.txt").read_text(encoding="utf-8").splitlines():
        i, s = line.split("|", 1)
        SKILLS_UK[int(i)] = s

def diff_text(d):
    if d == "-":
        return ""
    return DIFF_UK[d] if LANG == "uk" else d

def slug(s):
    """GitHub heading anchor: lower case, drop punctuation, spaces -> hyphens."""
    return re.sub(r"[^\w\- ]", "", s.lower()).replace(" ", "-")

stats = {}
for line in RAW.splitlines():
    i, uid, ed, diff, sol, tri, title = line.split("|")
    stats[int(i)] = dict(uid=uid, edition=int(ed), diff=diff, solved=int(sol), tried=int(tri), title=title)
cls = {}
for line in CLS.splitlines():
    i, topics, skills, lib, src = line.split("|")
    topics = topics.split(",")
    for t in topics:
        assert t in TOPICS, (i, t)
    if LANG == "uk":
        skills = SKILLS_UK[int(i)]
    cls[int(i)] = dict(topics=topics, skills=skills, lib=lib, src=src)
assert sorted(stats) == list(range(252)) and sorted(cls) == list(range(252)), "missing rows"

rows = []
for i in range(252):
    s, c = stats[i], cls[i]
    rate = (100.0 * s["solved"] / s["tried"]) if s["tried"] else 0.0
    rows.append(dict(i=i, **s, **c, rate=rate,
                     url=f"https://csacademy.com/ieeextreme-practice/task/{s['uid']}/"))
rows.sort(key=lambda r: (r["edition"], r["i"]))

with open(OUT / "tasks.csv", "w", newline="", encoding="utf-8") as f:
    w = csv.writer(f)
    w.writerow(TXT["csv_head"])
    for r in rows:
        w.writerow([f"{r['edition']}.0", r["title"], diff_text(r["diff"]), r["solved"], r["tried"],
                    f"{r['rate']:.0f}", TOPICS[r["topics"][0]][0], "; ".join(TOPICS[t][0] for t in r["topics"]),
                    r["skills"], r["lib"] if r["lib"] != "-" else "", TXT["src_long"][r["src"]], r["url"]])

def md_escape(s):
    return s.replace("|", "\\|")

def link(r):
    return f"[{md_escape(r['title'])}]({r['url']})"

L = []
L.append(TXT["title"])
L.append(TXT["intro"])
L.append(TXT["how"])
ntag = sum(1 for r in rows if r["src"] == "T")
tag_eds = collections.Counter(r["edition"] for r in rows if r["src"] == "T")
L.append(TXT["tags"].format(n=ntag, eds=", ".join(f"{e}.0: {n}" for e, n in sorted(tag_eds.items()))))
L.append(TXT["stmt"])
L.append(TXT["cols"])
L.append(TXT["note"])

L.append(TXT["summary"])
L.append(TXT["sum_head"])
L.append("|---|---:|---:|---|---|")
prim = collections.Counter(r["topics"][0] for r in rows)
tot = collections.Counter(t for r in rows for t in r["topics"])
for key, (name, what, lib) in TOPICS.items():
    L.append(f"| [{name}](#{slug(name)}) | {prim[key]} | {tot[key]} | {what} | {lib} |")
L.append(TXT["sum_note"])

L.append(TXT["by_ed"])
eds = sorted({r["edition"] for r in rows})
L.append(f"| {TXT['topic']} | " + " | ".join(f"{e}.0" for e in eds) + " |")
L.append("|---|" + "---:|" * len(eds))
for key, (name, _, _) in TOPICS.items():
    cnt = [sum(1 for r in rows if r["edition"] == e and key in r["topics"]) for e in eds]
    L.append(f"| {name} | " + " | ".join(str(c) if c else "" for c in cnt) + " |")
L.append(f"| {TXT['tasks_row']} | " + " | ".join(str(sum(1 for r in rows if r['edition'] == e)) for e in eds) + " |\n")

L.append(TXT["first"])
L.append(TXT["first_note"])
for key, (name, _, _) in TOPICS.items():
    cand = [r for r in rows if r["topics"][0] == key and r["tried"] >= 50 and r["solved"] > 0]
    cand.sort(key=lambda r: -r["rate"])
    if cand:
        L.append(f"- **{name}**: " + ", ".join(f"{link(r)} ({r['rate']:.0f}%)" for r in cand[:3]))
L.append("")

for key, (name, what, lib) in TOPICS.items():
    group = [r for r in rows if r["topics"][0] == key]
    also = [r for r in rows if key in r["topics"][1:]]
    L.append(f"## {name}\n")
    L.append(f"*{what}.* {TXT['library']}: {lib}.\n")
    L.append(TXT["tab_head"])
    L.append("|---|---|---|---|---|---|---|---|")
    for r in sorted(group, key=lambda r: (-r["rate"])):
        other = ", ".join(SHORT[t] for t in r["topics"][1:])
        L.append(f"| {r['edition']} | {link(r)} | {diff_text(r['diff'])} | "
                 f"{r['solved']}/{r['tried']} | {md_escape(r['skills'])} | {other} | {r['lib'] if r['lib'] != '-' else ''} | "
                 f"{TXT['src_short'][r['src']]} |")
    if also:
        aname = name.lower() if LANG == "en" else name
        L.append(TXT["also"].format(name=aname) + ", ".join(f"{link(r)} ({r['edition']})" for r in also) + "\n")
    else:
        L.append("")

(OUT / "tasks.md").write_text("\n".join(L) + "\n", encoding="utf-8")
print("rows", len(rows), "primary", dict(prim))
