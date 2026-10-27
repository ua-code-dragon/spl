# Архів задач IEEEXtreme за темами

Усі 252 задачі [практичної спільноти IEEEXtreme](https://csacademy.com/ieeextreme-practice/tasks/) на CS Academy (IEEEXtreme 10.0–19.0), згруповані за алгоритмічними навичками, які для них потрібні. Назви задач подано мовою оригіналу.

Як визначено теми:
- **теги**: CS Academy має власні тематичні теги для 63 задач (11.0: 30, 13.0: 4, 14.0: 24, 15.0: 4, 18.0: 1); їх використано без змін.
- **умова**: решту задач класифіковано за текстом умови. Вважайте це вагомою підказкою, а не гарантією: задача може вимагати більше, ніж перелічені навички.

Стовпці: **Вип.** — випуск змагання, **Скл.** — складність за CS Academy (якщо вказана), **Розв’язали** — скільки учасників розв’язали задачу / пробували її в практичному архіві (більша частка — отже, на практиці легша), **Бібл.** — заголовні файли [`lib/`](../../lib), що покривають потрібну навичку. Ті самі дані у вигляді таблиці: [tasks.csv](tasks.csv).

Примітка: деякі задачі 19.0 мають дуже малі числа (наприклад, 6/8), бо в архіві їх пробували лише кілька людей.

## Зведення

| Тема | Основна | Усього | Що треба знати | Бібліотека |
|---|---:|---:|---|---|
| [Реалізація і моделювання](#реалізація-і-моделювання) | 17 | 23 | уважне читання, моделювання, ASCII-виведення, граничні випадки | grid.h, io.h |
| [Рядки](#рядки) | 18 | 30 | шифри, KMP, гешування, паліндроми (Манакер), префіксні дерева, Ахо–Корасік, дужки | strutil.h, trie.h, hashmap.h |
| [Обробка тексту і даних](#обробка-тексту-і-даних) | 7 | 10 | задачі IEEE Xplore: розбір введення у форматах JSON/CSV/XML, групування, сортування, агрегування | hashmap.h, sort.h |
| [Зворотна розробка та емуляція](#зворотна-розробка-та-емуляція) | 6 | 8 | відгадати приховану функцію за прикладами, емулювати код / формати чисел | bits.h |
| [Математика і теорія чисел](#математика-і-теорія-чисел) | 25 | 47 | модульна арифметика, прості числа, НСД, швидке піднесення до степеня, формули | numtheory.h, matrix.h, bignum.h |
| [Комбінаторика і ймовірності](#комбінаторика-і-ймовірності) | 17 | 32 | підрахунок за модулем p, біноміальні коефіцієнти, включення-виключення, математичне сподівання, твірні функції | combin.h, fft.h, dp.h |
| [Жадібні алгоритми і сортування](#жадібні-алгоритми-і-сортування) | 19 | 29 | сортування + жадібний вибір, аргумент обміну, відрізки, купи | sort.h, heap.h |
| [Двійковий пошук](#двійковий-пошук) | 3 | 11 | нижня/верхня межа (lower/upper bound), двійковий пошук за відповіддю | search.h |
| [Динамічне програмування](#динамічне-програмування) | 24 | 48 | рюкзак, LIS/LCS, DP на сітці, DP на бітових масках, DP на дереві, DP для підрахунку | dp.h |
| [Графи](#графи) | 30 | 38 | BFS/DFS, найкоротші шляхи, MST, топологічне сортування, SCC, мости, паросполучення, потоки | graph.h, paths.h, flow.h, grid.h |
| [Дерева](#дерева) | 23 | 27 | підвішування за корінь, розміри піддерев, LCA, діаметр, DP на дереві, HLD, ейлерів обхід | tree.h |
| [Структури даних](#структури-даних) | 19 | 37 | префіксні суми, дерево Фенвіка, дерево відрізків (з відкладеним оновленням), розріджена таблиця, DSU, монотонний стек/черга, гешування | fenwick.h, segtree.h, sparse.h, dsu.h, linear.h |
| [Геометрія](#геометрія) | 11 | 14 | векторний добуток, площа многокутника, опукла оболонка, точка в многокутнику, формула Піка, замітальна пряма | geom.h |
| [Теорія ігор](#теорія-ігор) | 4 | 7 | DP виграшних/програшних позицій, мінімакс, Нім, теорема Шпрага–Ґранді | game.h |
| [Інтерактивні задачі](#інтерактивні-задачі) | 6 | 6 | протокол запитів, скидання буфера, адаптивні стратегії | interactive.h |
| [Повний перебір і перебір із поверненням](#повний-перебір-і-перебір-із-поверненням) | 9 | 13 | перебір варіантів, відсікання, «зустріч посередині», пошук у просторі станів | util.h |
| [Бітові операції](#бітові-операції) | 7 | 18 | маски, трюки з XOR, підмножини, XOR-базис | bits.h |
| [Конструктивні задачі](#конструктивні-задачі) | 7 | 13 | побудувати будь-який об’єкт, що задовольняє правила; спершу розібрати малі випадки | - |

*Основна* — кожну задачу враховано один раз (за головною темою); *Усього* — враховано кожну тему, якої задача стосується.

### За випусками

| Тема | 10.0 | 11.0 | 12.0 | 13.0 | 14.0 | 15.0 | 16.0 | 17.0 | 18.0 | 19.0 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Реалізація і моделювання | 1 | 3 | 3 |  | 3 | 4 | 5 | 2 | 1 | 1 |
| Рядки | 2 | 1 | 3 | 3 | 3 | 3 | 5 | 6 | 1 | 3 |
| Обробка тексту і даних |  |  | 1 | 1 | 1 | 2 | 1 | 2 | 1 | 1 |
| Зворотна розробка та емуляція |  |  | 2 |  | 1 | 1 |  | 2 | 1 | 1 |
| Математика і теорія чисел | 3 | 7 | 3 | 5 | 5 | 5 | 4 | 5 | 4 | 6 |
| Комбінаторика і ймовірності | 1 |  | 2 | 3 |  | 5 | 4 | 6 | 7 | 4 |
| Жадібні алгоритми і сортування | 3 | 3 | 2 | 6 | 2 | 2 | 3 |  | 4 | 4 |
| Двійковий пошук | 1 | 2 | 3 |  | 1 | 1 |  |  |  | 3 |
| Динамічне програмування | 1 | 11 | 5 | 4 | 3 | 5 | 3 | 5 | 6 | 5 |
| Графи | 3 | 8 | 3 | 2 | 4 | 2 | 5 | 5 | 2 | 4 |
| Дерева |  | 1 | 3 | 4 | 2 | 4 | 2 | 3 | 4 | 4 |
| Структури даних | 1 | 4 | 1 | 5 | 4 | 4 | 4 | 4 | 4 | 6 |
| Геометрія | 1 | 1 |  | 2 | 2 | 3 | 1 | 1 | 3 |  |
| Теорія ігор |  | 2 | 2 |  |  |  | 1 |  | 1 | 1 |
| Інтерактивні задачі |  | 1 | 3 | 1 |  | 1 |  |  |  |  |
| Повний перебір і перебір із поверненням | 2 | 2 | 1 | 1 | 2 |  | 2 |  | 3 |  |
| Бітові операції | 1 | 3 | 2 | 1 | 2 | 2 | 1 | 1 | 1 | 4 |
| Конструктивні задачі |  | 1 |  | 3 | 2 | 1 | 1 |  | 2 | 3 |
| **Задач** | 13 | 30 | 24 | 27 | 26 | 25 | 25 | 25 | 28 | 29 |

### З чого почати

Для кожної теми — три задачі, які найчастіше розв’язували в практичному архіві (основна тема, щонайменше 50 спроб):

- **Реалізація і моделювання**: [Memory Management](https://csacademy.com/ieeextreme-practice/task/memory-management/) (84%), [Game of Life 2020](https://csacademy.com/ieeextreme-practice/task/conway-gameoflife/) (75%), [Pizza Cutter](https://csacademy.com/ieeextreme-practice/task/pizza-cutter/) (71%)
- **Рядки**: [Gaius Letters](https://csacademy.com/ieeextreme-practice/task/gaius-letters/) (83%), [Caesar Redux](https://csacademy.com/ieeextreme-practice/task/caesar_redux/) (55%), [Programmer's Poem](https://csacademy.com/ieeextreme-practice/task/Poetry/) (42%)
- **Обробка тексту і даних**: [Application Abuse](https://csacademy.com/ieeextreme-practice/task/application-abuse/) (59%), [Xplore](https://csacademy.com/ieeextreme-practice/task/xplore/) (57%), [Impact Factor](https://csacademy.com/ieeextreme-practice/task/impact-factor/) (42%)
- **Зворотна розробка та емуляція**: [Restaurant Cipher](https://csacademy.com/ieeextreme-practice/task/resaturant_cipher/) (85%), [IEEE754 Emulator](https://csacademy.com/ieeextreme-practice/task/ieee754-emulator/) (30%), [Magic Spell](https://csacademy.com/ieeextreme-practice/task/magic-spell/) (19%)
- **Математика і теорія чисел**: [Secure Elliptic Curve Point Addition](https://csacademy.com/ieeextreme-practice/task/secure-elliptic-curve-point-addition/) (95%), [Mosaic Decoration I](https://csacademy.com/ieeextreme-practice/task/mosaic1/) (86%), [Rigged Dice](https://csacademy.com/ieeextreme-practice/task/rigged-dice/) (62%)
- **Комбінаторика і ймовірності**: [N-Palindromes](https://csacademy.com/ieeextreme-practice/task/n-palindromes/) (60%), [Do you know Expectation?](https://csacademy.com/ieeextreme-practice/task/do-you-know-expectation/) (38%), [Alfa Pool](https://csacademy.com/ieeextreme-practice/task/alfa-pool/) (30%)
- **Жадібні алгоритми і сортування**: [Magic Wands](https://csacademy.com/ieeextreme-practice/task/magic-wands/) (91%), [Dog Walking](https://csacademy.com/ieeextreme-practice/task/dog-walking/) (83%), [Blackgate Penitentiary](https://csacademy.com/ieeextreme-practice/task/8761fb7efefcf1d890df1d8d91cae241/) (80%)
- **Двійковий пошук**: [The Twin Occurrence Quest](https://csacademy.com/ieeextreme-practice/task/the-twin-occurrence-quest/) (78%), [Crafting Wooden Tables](https://csacademy.com/ieeextreme-practice/task/crafting-wooden-tables/) (19%)
- **Динамічне програмування**: [Painter's Dilemma](https://csacademy.com/ieeextreme-practice/task/painters-dilemma/) (82%), [BeetleBag](https://csacademy.com/ieeextreme-practice/task/ed8629419f140a5a2c923b049aba1224/) (64%), [Visit Egypt](https://csacademy.com/ieeextreme-practice/task/visit-egypt/) (57%)
- **Графи**: [King's Order](https://csacademy.com/ieeextreme-practice/task/kings-order/) (89%), [Vangelis the Batbear and the Bubbles challenge](https://csacademy.com/ieeextreme-practice/task/979a09a0cd8c4e98dd0a690f39a55bd2/) (66%), [Invisible Ghosts](https://csacademy.com/ieeextreme-practice/task/invisible-ghosts/) (62%)
- **Дерева**: [White knights and Black warriors](https://csacademy.com/ieeextreme-practice/task/white-knights-and-black-warriors/) (85%), [Icarus](https://csacademy.com/ieeextreme-practice/task/icarus/) (67%), [Rumour](https://csacademy.com/ieeextreme-practice/task/9ca8fafd184f553a903734761546a224/) (62%)
- **Структури даних**: [Baker's Competition](https://csacademy.com/ieeextreme-practice/task/bakers-competition/) (40%), [Protecting the Hive](https://csacademy.com/ieeextreme-practice/task/protecting-the-hive/) (33%), [Long Lines](https://csacademy.com/ieeextreme-practice/task/long_lines/) (30%)
- **Геометрія**: [Ellipse Art](https://csacademy.com/ieeextreme-practice/task/ellipse-art/) (72%), [Aeneas' cryptographic disc (4th c. B.C.)](https://csacademy.com/ieeextreme-practice/task/d48ada9a7213299f1b24b22b2fb9443f/) (67%), [Stick](https://csacademy.com/ieeextreme-practice/task/stick/) (45%)
- **Теорія ігор**: [Stones](https://csacademy.com/ieeextreme-practice/task/stones/) (13%), [The Gold-diggers](https://csacademy.com/ieeextreme-practice/task/the-gold-diggers/) (9%), [Queen](https://csacademy.com/ieeextreme-practice/task/queen/) (6%)
- **Інтерактивні задачі**: [Troll Coder](https://csacademy.com/ieeextreme-practice/task/troll-coder/) (68%), [Concentration Game](https://csacademy.com/ieeextreme-practice/task/concentration-game/) (54%), [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) (14%)
- **Повний перебір і перебір із поверненням**: [Xtreme Fake Coins](https://csacademy.com/ieeextreme-practice/task/xtreme-fake-coins/) (57%), [Checkers Challenge](https://csacademy.com/ieeextreme-practice/task/checkers-challenge/) (56%), [Octopuses with Watches](https://csacademy.com/ieeextreme-practice/task/59d4aae501fe4ced9ffbf3737acd18a2/) (43%)
- **Бітові операції**: [Bit Soccer](https://csacademy.com/ieeextreme-practice/task/bit-soccer/) (52%), [Shailesh's Triplet](https://csacademy.com/ieeextreme-practice/task/shailesh-s-triplet/) (51%), [RecXor](https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/) (50%)
- **Конструктивні задачі**: [Hack the coach!](https://csacademy.com/ieeextreme-practice/task/hack-the-coach/) (69%), [Making a Tangram](https://csacademy.com/ieeextreme-practice/task/making-tangram/) (33%), [Maximum Sum](https://csacademy.com/ieeextreme-practice/task/04dfa70efd936271ae191cb1a97eb876/) (17%)

## Реалізація і моделювання

*уважне читання, моделювання, ASCII-виведення, граничні випадки.* Бібліотека: grid.h, io.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 10 | [Memory Management](https://csacademy.com/ieeextreme-practice/task/memory-management/) |  | 119/141 | моделювання заміщення сторінок FIFO і LRU |  | linear.h hashmap.h | умова |
| 14 | [Game of Life 2020](https://csacademy.com/ieeextreme-practice/task/conway-gameoflife/) | легка | 600/803 | моделювання гри «Життя» |  | grid.h | теги |
| 16 | [Pizza Cutter](https://csacademy.com/ieeextreme-practice/task/pizza-cutter/) |  | 2528/3563 | нормалізувати кути за модулем 180, порахувати різні розрізи | Геометрія | sort.h | умова |
| 11 | [Running Up Stairs](https://csacademy.com/ieeextreme-practice/task/96c8b1313edd72abf600facb0a14dbab/) | легка | 1539/2739 | рекурента типу Фібоначчі з довгою арифметикою | Математика | bignum.h | теги |
| 17 | [War Games](https://csacademy.com/ieeextreme-practice/task/war_games/) |  | 1422/2850 | карткова гра з чергами, виявлення нічиєї за повторенням станів |  | linear.h hashmap.h | умова |
| 16 | [What Language Am I Speaking?](https://csacademy.com/ieeextreme-practice/task/what-language-am-i-speaking/) |  | 464/1109 | обчислити дерево рішень за наявністю символів | Рядки |  | умова |
| 16 | [ASCII Dancer](https://csacademy.com/ieeextreme-practice/task/ascii-dancer/) |  | 921/2772 | моделювання команд, виведення ASCII-графіки |  |  | умова |
| 15 | [Image Similarity](https://csacademy.com/ieeextreme-practice/task/image-similarity/) | легка | 304/943 | усі повороти/віддзеркалення і зсуви, підрахунок пікселів, що перекриваються | Геометрія | grid.h | умова |
| 15 | [Word Search](https://csacademy.com/ieeextreme-practice/task/wordsearch/) | легка | 183/594 | пошук слів у 8 напрямках (префіксне дерево для багатьох слів) | Рядки | trie.h | умова |
| 11 | [Game of Life](https://csacademy.com/ieeextreme-practice/task/d12a7784af1a3d3f6d88601c81a4bb81/) | середня | 205/1000 | клітинний автомат на торі (моделювання) |  | grid.h | теги |
| 11 | [Elementary](https://csacademy.com/ieeextreme-practice/task/c787255968c972c653677a52599ecc2f/) | найскладніша | 71/470 | нестандартне кодування слів, DP за способами розбити слово | DP |  | теги |
| 12 | [Infinite snakes and ladders](https://csacademy.com/ieeextreme-practice/task/infinite-snakes-and-ladders/) |  | 108/830 | моделювання настільної гри («Змії та драбини») |  |  | умова |
| 16 | [Robot versus Fan](https://csacademy.com/ieeextreme-practice/task/robot-versus-fan/) | складна | 58/660 | періодичний шлях пилу проти шляху робота: моделювати до періоду (НСК) | Математика | numtheory.h | умова |
| 16 | [Pipeline](https://csacademy.com/ieeextreme-practice/task/pipeline/) |  | 53/1134 | спроєктувати тривимірну мережу труб (побудова / пошук на тривимірній сітці) | Конструктивні |  | умова |
| 14 | [Furin Back](https://csacademy.com/ieeextreme-practice/task/furin-back/) | найскладніша | 17/393 | нестандартна задача |  |  | теги |
| 18 | [Welcome to IEEEXtreme 18.0](https://csacademy.com/ieeextreme-practice/task/welcome-ieeextreme-18/) |  | 0/4037 | вивести повідомлення (розминка) |  |  | умова |
| 19 | [Welcome to IEEEXtreme 19.0](https://csacademy.com/ieeextreme-practice/task/welcome-to-ieeextreme-19/) |  | 0/4128 | вивести повідомлення (розминка) |  |  | умова |

Тема «Реалізація і моделювання» потрібна також у задачах: [Xtreme Fake Coins](https://csacademy.com/ieeextreme-practice/task/xtreme-fake-coins/) (12), [Drawing Rooted Binary Trees](https://csacademy.com/ieeextreme-practice/task/drawing-rooted-binary-trees/) (12), [IEEEXplore Indexing](https://csacademy.com/ieeextreme-practice/task/ieeexplore-indexing/) (14), [Spies of Red and Blue](https://csacademy.com/ieeextreme-practice/task/spies/) (15), [Rigged Dice](https://csacademy.com/ieeextreme-practice/task/rigged-dice/) (15), [Programmer's Poem](https://csacademy.com/ieeextreme-practice/task/Poetry/) (17)

## Рядки

*шифри, KMP, гешування, паліндроми (Манакер), префіксні дерева, Ахо–Корасік, дужки.* Бібліотека: strutil.h, trie.h, hashmap.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 16 | [Gaius Letters](https://csacademy.com/ieeextreme-practice/task/gaius-letters/) |  | 3091/3742 | шифр Цезаря (сама умова зашифрована) |  |  | умова |
| 17 | [Caesar Redux](https://csacademy.com/ieeextreme-practice/task/caesar_redux/) |  | 2438/4446 | шифр Цезаря: відрізнити відкритий текст від шифротексту |  |  | умова |
| 17 | [Programmer's Poem](https://csacademy.com/ieeextreme-practice/task/Poetry/) |  | 1049/2510 | розмітка схеми рими (порівняння суфіксів) | Реалізація | hashmap.h | умова |
| 11 | [Jarawi and The Interview](https://csacademy.com/ieeextreme-practice/task/6f960361da7beb7f3a083f4776c2cf79/) | середня | 428/1504 | запити про підпослідовності: таблиця наступних входжень + двійковий пошук | Двійковий пошук | strutil.h search.h | теги |
| 17 | [Labradoodle](https://csacademy.com/ieeextreme-practice/task/labradoodle/) |  | 515/1987 | злиті слова: пошук префіксів/суфіксів у геш-множинах |  | hashmap.h trie.h | умова |
| 13 | [Ave Caesar!](https://csacademy.com/ieeextreme-practice/task/ave-caesar/) |  | 200/936 | рекурсивна перевірка правильності рядків (точки розбиття, порівняння), мемоїзація |  | strutil.h | умова |
| 19 | [Sequence Decomposition](https://csacademy.com/ieeextreme-practice/task/sequence-decomposition/) |  | 624/3108 | розкласти на підпослідовності «112012»: жадібні лічильники | Жадібні |  | умова |
| 14 | [Rotational Lights](https://csacademy.com/ieeextreme-practice/task/rotational-lights/) | середня | 199/1206 | KMP для циклічних шаблонів |  | strutil.h | теги |
| 14 | [Non-Overlapping Palindromes](https://csacademy.com/ieeextreme-practice/task/nonoverlapping-palindromes/) | середня | 182/1264 | Манакер: найкращий паліндром, що закінчується перед / починається після кожної позиції | DP | strutil.h | умова |
| 18 | [Cheap Construction](https://csacademy.com/ieeextreme-practice/task/cheap-construction/) |  | 428/3106 | правила для підрядків з’єднують острови: гешування + DSU для кожного k | Графи | strutil.h dsu.h | умова |
| 17 | [Bad Passwords](https://csacademy.com/ieeextreme-practice/task/BadPasswords/) |  | 193/1612 | виявити похідні паролі: спільний префікс/суфікс, числові послідовності та послідовності місяців | Обробка тексту |  | умова |
| 10 | [Safety](https://csacademy.com/ieeextreme-practice/task/safety/) |  | 5/45 | рівність підрядків під час змін: поліноміальний геш у дереві відрізків | Структури даних | strutil.h segtree.h | умова |
| 15 | [Expression Evaluation](https://csacademy.com/ieeextreme-practice/task/expression/) | середня | 151/1698 | розбір виразів (рекурсивний спуск / два стеки), перевірки правильності | Обробка тексту | linear.h | умова |
| 15 | [Image Convolution](https://csacademy.com/ieeextreme-practice/task/image-convolution/) | легка | 38/499 | двовимірний пошук шаблону (гешування рядків / KMP) | Структури даних | strutil.h | умова |
| 12 | [Tweedledum's Nested Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledums-nested-brackets/) |  | 16/500 | глибина дужок, підрахунок повторних вставок через префіксні баланси | Комбінаторика | segtree.h | умова |
| 16 | [Weird Reward](https://csacademy.com/ieeextreme-practice/task/weird-reward/) | складна | 15/490 | граматика виразів, DP за підрядками, які є правильними виразами | DP | linear.h | умова |
| 12 | [Tweedledee's Split Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledees-split-brackets/) |  | 28/1017 | розбити дужки на дві правильні послідовності (стек, DP) | DP | dp.h | умова |
| 17 | [Powerful Strings](https://csacademy.com/ieeextreme-practice/task/powerful-strings/) |  | 28/1707 | автомат Ахо–Корасік + DP за довжиною (сума 2^кількість входжень) | Комбінаторика | trie.h dp.h | умова |

Тема «Рядки» потрібна також у задачах: [N-Palindromes](https://csacademy.com/ieeextreme-practice/task/n-palindromes/) (10), [Magic Spell](https://csacademy.com/ieeextreme-practice/task/magic-spell/) (12), [Yin Yang](https://csacademy.com/ieeextreme-practice/task/yin-yang/) (13), [Reshuffle Teams](https://csacademy.com/ieeextreme-practice/task/reshuffle-teams/) (13), [Coupon Codes](https://csacademy.com/ieeextreme-practice/task/coupon-codes/) (14), [Word Search](https://csacademy.com/ieeextreme-practice/task/wordsearch/) (15), [Palindrome Cutting](https://csacademy.com/ieeextreme-practice/task/palindrome-cutting/) (16), [Book Cipher](https://csacademy.com/ieeextreme-practice/task/book-cipher/) (16), [What Language Am I Speaking?](https://csacademy.com/ieeextreme-practice/task/what-language-am-i-speaking/) (16), [Restaurant Cipher](https://csacademy.com/ieeextreme-practice/task/resaturant_cipher/) (17), [EDPS](https://csacademy.com/ieeextreme-practice/task/edps/) (19), [Squared Gaps](https://csacademy.com/ieeextreme-practice/task/squared-gaps/) (19)

## Обробка тексту і даних

*задачі IEEE Xplore: розбір введення у форматах JSON/CSV/XML, групування, сортування, агрегування.* Бібліотека: hashmap.h, sort.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [Application Abuse](https://csacademy.com/ieeextreme-practice/task/application-abuse/) |  | 1893/3227 | розбір журналів, агрегування за користувачами, виявлення порушень правил |  | hashmap.h sort.h | умова |
| 12 | [Xplore](https://csacademy.com/ieeextreme-practice/task/xplore/) |  | 455/792 | розбір записів JSON, обчислення h-індексу авторів, сортування |  | sort.h hashmap.h | умова |
| 13 | [Impact Factor](https://csacademy.com/ieeextreme-practice/task/impact-factor/) |  | 334/796 | розбір записів JSON, агрегування цитувань за роками, обчислення імпакт-фактора |  | hashmap.h sort.h | умова |
| 16 | [Book Cipher](https://csacademy.com/ieeextreme-practice/task/book-cipher/) |  | 307/1415 | прибрати XML-теги, побудувати сітку символів, декодувати пари (r, c) | Рядки |  | умова |
| 18 | [Disparate Data Sets](https://csacademy.com/ieeextreme-practice/task/disparate-datasets/) |  | 343/2645 | розбір CSV, з’єднання записів, заповнення пропущених полів |  | hashmap.h | умова |
| 14 | [IEEEXplore Indexing](https://csacademy.com/ieeextreme-practice/task/ieeexplore-indexing/) | середня | 92/767 | розбір записів, побудова інвертованого індексу | Реалізація | hashmap.h sort.h | теги |
| 17 | [Thesaurus](https://csacademy.com/ieeextreme-practice/task/thesaurus/) |  | 9/604 | розбір документів та ієрархічного тезауруса, зіставлення термінів з темами верхнього рівня |  | hashmap.h | умова |

Тема «Обробка тексту і даних» потрібна також у задачах: [Xtreme Winners](https://csacademy.com/ieeextreme-practice/task/xtreme-winners/) (15), [Expression Evaluation](https://csacademy.com/ieeextreme-practice/task/expression/) (15), [Bad Passwords](https://csacademy.com/ieeextreme-practice/task/BadPasswords/) (17)

## Зворотна розробка та емуляція

*відгадати приховану функцію за прикладами, емулювати код / формати чисел.* Бібліотека: bits.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 17 | [Restaurant Cipher](https://csacademy.com/ieeextreme-practice/task/resaturant_cipher/) |  | 2983/3520 | вивести схему кодування з прикладів | Рядки |  | умова |
| 18 | [IEEE754 Emulator](https://csacademy.com/ieeextreme-practice/task/ieee754-emulator/) |  | 986/3278 | емуляція IEEE 754 одинарної точності з таблицями підстановки (бітові поля) | Біти | bits.h | умова |
| 12 | [Magic Spell](https://csacademy.com/ieeextreme-practice/task/magic-spell/) |  | 160/833 | відгадати приховану функцію над рядками за прикладами | Рядки |  | умова |
| 19 | [Ladder](https://csacademy.com/ieeextreme-practice/task/ladder/) |  | 377/3556 | ефективно відтворити виведення заданої програми на Python |  |  | умова |
| 15 | [Xtreme Winners](https://csacademy.com/ieeextreme-practice/task/xtreme-winners/) |  | 31/2416 | code golf: зіставити назву команди з її змаганням найкоротшою програмою | Обробка тексту |  | умова |
| 17 | [Dalvik](https://csacademy.com/ieeextreme-practice/task/dalvik/) |  | 19/1542 | прочитати байт-код Dalvik (smali) і ефективно реалізувати його заново |  |  | умова |

Тема «Зворотна розробка та емуляція» потрібна також у задачах: [Barrett Reduction](https://csacademy.com/ieeextreme-practice/task/barrett-reduction/) (12), [ARM Constant Multiplication](https://csacademy.com/ieeextreme-practice/task/arm/) (14)

## Математика і теорія чисел

*модульна арифметика, прості числа, НСД, швидке піднесення до степеня, формули.* Бібліотека: numtheory.h, matrix.h, bignum.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [Secure Elliptic Curve Point Addition](https://csacademy.com/ieeextreme-practice/task/secure-elliptic-curve-point-addition/) |  | 4877/5159 | обернений елемент за модулем, додавання точок еліптичної кривої |  | numtheory.h | умова |
| 14 | [Mosaic Decoration I](https://csacademy.com/ieeextreme-practice/task/mosaic1/) | легка | 2533/2931 | ділення з округленням угору і вартості |  |  | теги |
| 15 | [Rigged Dice](https://csacademy.com/ieeextreme-practice/task/rigged-dice/) | легка | 1234/1980 | порівняння правдоподібності: порахувати шістки | Реалізація |  | умова |
| 14 | [Mosaic Decoration II](https://csacademy.com/ieeextreme-practice/task/mosaic2/) | легка | 1025/1645 | арифметика з кількостями плиток |  |  | теги |
| 11 | [Fibonacci](https://csacademy.com/ieeextreme-practice/task/09f92a575cc006d4a6a7f525f370ec30/) | легка | 1693/3179 | лінійна рекурента через піднесення матриці до степеня | DP | matrix.h | теги |
| 10 | [P = NP?](https://csacademy.com/ieeextreme-practice/task/pvnp/) |  | 12/32 | межі сум рангів із пропущеними значеннями (сортування, жадібний алгоритм) | Жадібні | sort.h | умова |
| 12 | [Barrett Reduction](https://csacademy.com/ieeextreme-practice/task/barrett-reduction/) |  | 148/604 | точне ділення через множення і зсув, 64/128-бітна арифметика | Біти, Зворотна розробка | bits.h | умова |
| 12 | [Product Rectangle](https://csacademy.com/ieeextreme-practice/task/product-rectangle/) |  | 188/936 | сума прямокутника = (сума відрізка A)(сума відрізка B): максимальна/мінімальна сума підмасиву (Кадане) | DP | dp.h | умова |
| 13 | [Googolplex](https://csacademy.com/ieeextreme-practice/task/googolplex/) |  | 81/412 | величезний показник: цикл 5^k mod 100 |  | numtheory.h | умова |
| 14 | [Mosaic Decoration III](https://csacademy.com/ieeextreme-practice/task/mosaic3/) | легка | 113/608 | арифметика з кількостями плиток |  |  | теги |
| 13 | [Infinite String](https://csacademy.com/ieeextreme-practice/task/infinite-string/) |  | 182/1002 | знайти позицію в рядку з усіх слів, упорядкованих за довжиною (степені B) |  |  | умова |
| 17 | [Happy Numbers](https://csacademy.com/ieeextreme-practice/task/happy_numbers/) |  | 690/4372 | щасливі числа на відрізку: попередньо обчислити малі суми, DP за цифрами | DP | dp.h | умова |
| 12 | [Factorial Zeros](https://csacademy.com/ieeextreme-practice/task/factorial-zeros/) |  | 104/678 | формула Лежандра для основи B (розклад B на множники) + двійковий пошук за n | Двійковий пошук | numtheory.h search.h | умова |
| 18 | [Power of three](https://csacademy.com/ieeextreme-practice/task/power-of-three/) |  | 684/4462 | чи є N степенем трійки (велике N: логарифм / довга арифметика) |  | bignum.h | умова |
| 11 | [Math Challenge](https://csacademy.com/ieeextreme-practice/task/7df0da0b0477307be410f4772c739528/) | складна | 276/2140 | a^C(b,c) mod p: показник за модулем p-1 (Ейлер/Ферма), біноміальний коефіцієнт за складеним модулем (КТО) |  | numtheory.h combin.h | теги |
| 11 | [Quipu Function](https://csacademy.com/ieeextreme-practice/task/5802db6cc4107baa3e135d06a31494b5/) | складна | 235/1910 | решето, підрахунок простих дільників на відрізках |  | numtheory.h | теги |
| 18 | [Sierpinski](https://csacademy.com/ieeextreme-practice/task/sierpinski/) |  | 145/1421 | трикутник Серпінського / Паскаля за модулем 2: рекурсія за координатами |  | combin.h | умова |
| 14 | [Molecules](https://csacademy.com/ieeextreme-practice/task/molecules/) | складна | 52/517 | хімічні формули: підрахунок атомів, лінійні рівняння |  | matrix.h | теги |
| 13 | [Batchman and GCD](https://csacademy.com/ieeextreme-practice/task/batchman-and-gcd/) |  | 115/1457 | різні НСД підпослідовностей: перевірити кожне d через його кратні (гармонічна сума) |  | numtheory.h | умова |
| 17 | [Rectangles](https://csacademy.com/ieeextreme-practice/task/rectangles/) |  | 45/765 | розміри груп, у яких прямокутники мають взаємно прості сторони (НСД, розклад на множники) | Комбінаторика | numtheory.h | умова |
| 15 | [Arrays Count](https://csacademy.com/ieeextreme-practice/task/arrays-count/) | складна | 5/307 | підрахунок масивів за виразом з OR (нестандартний підрахунок) | Біти | combin.h | теги |
| 15 | [Beautiful Summation](https://csacademy.com/ieeextreme-practice/task/summation/) | складна | 44/2702 | сума P^k k^Q mod M (M не просте): степінь матриці / «розділяй і володарюй» з біноміальними коефіцієнтами |  | matrix.h combin.h | умова |
| 18 | [Balls](https://csacademy.com/ieeextreme-practice/task/balls/) |  | 21/3607 | плитки, у які влучають кратні: включення-виключення за НСК з відсіканням | Комбінаторика | numtheory.h | умова |
| 15 | [Big Matrix Small Determinant](https://csacademy.com/ieeextreme-practice/task/big-matrix-small-determinant/) | складна | 7/1254 | побудувати матрицю із заданим визначником (рекурсія) | Конструктивні | matrix.h | теги |
| 10 | [Goldbach](https://csacademy.com/ieeextreme-practice/task/goldbach/) |  | 0/125 | прості числа: решето / Міллер–Рабін, сума трьох простих |  | numtheory.h | умова |

Тема «Математика і теорія чисел» потрібна також у задачах: [Weighty Decisions](https://csacademy.com/ieeextreme-practice/task/weighty-decisions/) (10), [Pyramid](https://csacademy.com/ieeextreme-practice/task/5e98e4b17b3477e671568a437388fb7a/) (11), [Running Up Stairs](https://csacademy.com/ieeextreme-practice/task/96c8b1313edd72abf600facb0a14dbab/) (11), [Mister Counter](https://csacademy.com/ieeextreme-practice/task/3dd761f749054a509a0012c5beee0e35/) (11), [RecXor](https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/) (11), [Xtreme Rappers](https://csacademy.com/ieeextreme-practice/task/xtreme-rappers/) (13), [Lexical Addition](https://csacademy.com/ieeextreme-practice/task/lexical-addition/) (13), [Coin Collector](https://csacademy.com/ieeextreme-practice/task/coin-collector/) (14), [Polygon](https://csacademy.com/ieeextreme-practice/task/polygon/) (15), [My Treat](https://csacademy.com/ieeextreme-practice/task/my-treat/) (16), [Scheduler](https://csacademy.com/ieeextreme-practice/task/scheduler/) (16), [Robot versus Fan](https://csacademy.com/ieeextreme-practice/task/robot-versus-fan/) (16), [Queen](https://csacademy.com/ieeextreme-practice/task/queen/) (16), [He Loves Data Structures](https://csacademy.com/ieeextreme-practice/task/data_structures/) (17), [Dice](https://csacademy.com/ieeextreme-practice/task/dices/) (17), [Cool Sum](https://csacademy.com/ieeextreme-practice/task/coolsum/) (17), [Stick](https://csacademy.com/ieeextreme-practice/task/stick/) (18), [New Casino Game](https://csacademy.com/ieeextreme-practice/task/new-casino-game/) (19), [Become as One](https://csacademy.com/ieeextreme-practice/task/become-as-one/) (19), [Airline Traveling](https://csacademy.com/ieeextreme-practice/task/airline-traveling/) (19), [Baker's Competition](https://csacademy.com/ieeextreme-practice/task/bakers-competition/) (19), [Continued Fractions](https://csacademy.com/ieeextreme-practice/task/continued-fractions/) (19)

## Комбінаторика і ймовірності

*підрахунок за модулем p, біноміальні коефіцієнти, включення-виключення, математичне сподівання, твірні функції.* Бібліотека: combin.h, fft.h, dp.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [New Casino Game](https://csacademy.com/ieeextreme-practice/task/new-casino-game/) |  | 8/9 | математичне сподівання з випадковими турами, що не б’ють одна одну (лінійність сподівання) | Математика | combin.h | умова |
| 10 | [N-Palindromes](https://csacademy.com/ieeextreme-practice/task/n-palindromes/) |  | 75/126 | кількість рядків, що стають паліндромами рівно після n змін (підрахунок за дзеркальними парами) | Рядки | combin.h dp.h | умова |
| 19 | [Do you know Expectation?](https://csacademy.com/ieeextreme-practice/task/do-you-know-expectation/) |  | 1288/3406 | E[X^K] для XOR випадкової підмножини: X рівномірно розподілений на лінійній оболонці | Біти | bits.h | умова |
| 13 | [Alfa Pool](https://csacademy.com/ieeextreme-practice/task/alfa-pool/) |  | 169/567 | суми очок із серіями перемог, що подвоюються (DP для підрахунку) | DP | dp.h | умова |
| 13 | [Ranged Alfa Pool](https://csacademy.com/ieeextreme-practice/task/ranged-alfa-pool/) |  | 114/387 | підрахунок сценаріїв турніру за сумою очок (серії з подвоєнням) | DP | dp.h | умова |
| 18 | [Increasing table](https://csacademy.com/ieeextreme-practice/task/increasing-table/) |  | 1029/4436 | зростаючі таблиці 2 x N з обмеженнями на рядки (DP на зразок задачі про голосування) | DP | dp.h combin.h | умова |
| 17 | [Ordered Permutations](https://csacademy.com/ieeextreme-practice/task/ordered-permutations/) |  | 285/1418 | перестановки із заданим шаблоном зростань/спадань: DP за O(n^2) з префіксними сумами | DP | dp.h | умова |
| 19 | [Bitonic Sequences](https://csacademy.com/ieeextreme-practice/task/bitonic-sequences/) |  | 574/4441 | підрахунок бітонічних композицій для кожного N (DP на зразок розбиттів / твірні функції) | DP | dp.h fft.h | умова |
| 16 | [Array](https://csacademy.com/ieeextreme-practice/task/array/) |  | 132/1468 | кількість масивів із заданою довжиною виразу з OR, за модулем 4 | Біти | combin.h | умова |
| 12 | [Friendly Sequences](https://csacademy.com/ieeextreme-practice/task/friendly-sequences/) |  | 17/397 | підрахунок неспадних послідовностей з обмеженнями на префіксні суми (DP + префіксні суми) | DP | dp.h | умова |
| 17 | [Cool Sum](https://csacademy.com/ieeextreme-practice/task/coolsum/) |  | 46/2167 | біноміальні суми за лишками за модулем 2^k (арифметика многочленів за модулем x^(2^k) - 1) | Математика | fft.h combin.h | умова |
| 16 | [Palindrome Cutting](https://csacademy.com/ieeextreme-practice/task/palindrome-cutting/) |  | 33/1578 | масиви, що розбиваються на паліндроми парної довжини: DP за примітивними паліндромами | Рядки | combin.h dp.h | умова |
| 15 | [Candy Shop](https://csacademy.com/ieeextreme-practice/task/candy-shop/) | найскладніша | 22/1331 | твірні функції, FFT/NTT | DP | fft.h combin.h | теги |
| 18 | [Halving](https://csacademy.com/ieeextreme-practice/task/halving/) |  | 39/2740 | підрахунок перестановок, сумісних з правилами поділу навпіл за min/max | DP | combin.h | умова |
| 17 | [Dice](https://csacademy.com/ieeextreme-practice/task/dices/) |  | 14/1489 | ймовірність суми на кубиках через твірні функції за модулем 998244353 (NTT) | Математика | fft.h combin.h | умова |
| 18 | [Increasing-decreasing permutations](https://csacademy.com/ieeextreme-practice/task/increasing-decreasing-permutation/) |  | 14/2929 | сума за перестановками мінімальної кількості обмінів сусідів (підрахунок інверсій за модулем M) |  | combin.h | умова |
| 18 | [Bounded tuples](https://csacademy.com/ieeextreme-practice/task/bounded-tuples/) |  | 11/4059 | підрахунок цілочисельних присвоєнь з обмеженнями на суми, виявлення нескінченності | Перебір | dp.h | умова |

Тема «Комбінаторика і ймовірності» потрібна також у задачах: [Tweedledum's Nested Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledums-nested-brackets/) (12), [Luck-i-flip](https://csacademy.com/ieeextreme-practice/task/luck-i-flip/) (13), [Coloring Tiles](https://csacademy.com/ieeextreme-practice/task/coloring-tiles/) (15), [Language Learning](https://csacademy.com/ieeextreme-practice/task/language-learning/) (15), [Xtreme Teams](https://csacademy.com/ieeextreme-practice/task/xtreme-teams/) (15), [Bus Company](https://csacademy.com/ieeextreme-practice/task/buscompany/) (15), [Queries on a Tree](https://csacademy.com/ieeextreme-practice/task/queries-on-a-tree/) (16), [Poker Tournament](https://csacademy.com/ieeextreme-practice/task/poker-tournament/) (16), [Powerful Strings](https://csacademy.com/ieeextreme-practice/task/powerful-strings/) (17), [Rectangles](https://csacademy.com/ieeextreme-practice/task/rectangles/) (17), [Combo Lock Redux](https://csacademy.com/ieeextreme-practice/task/combo_locks/) (17), [Balls](https://csacademy.com/ieeextreme-practice/task/balls/) (18), [This is not an optimization problem](https://csacademy.com/ieeextreme-practice/task/this-is-not-an-optimization-problem/) (18), [Queries](https://csacademy.com/ieeextreme-practice/task/queries/) (18), [Visit Egypt](https://csacademy.com/ieeextreme-practice/task/visit-egypt/) (19)

## Жадібні алгоритми і сортування

*сортування + жадібний вибір, аргумент обміну, відрізки, купи.* Бібліотека: sort.h, heap.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [Magic Wands](https://csacademy.com/ieeextreme-practice/task/magic-wands/) |  | 4186/4603 | перевертання K елементів поспіль: жадібно зліва направо з різницевим масивом |  |  | умова |
| 10 | [Dog Walking](https://csacademy.com/ieeextreme-practice/task/dog-walking/) |  | 308/369 | сортування, розрізати по K-1 найбільших проміжках |  | sort.h | умова |
| 11 | [Blackgate Penitentiary](https://csacademy.com/ieeextreme-practice/task/8761fb7efefcf1d890df1d8d91cae241/) | легка | 2655/3308 | сортування з однаковими значеннями, діапазони позицій |  | sort.h | теги |
| 16 | [My Treat](https://csacademy.com/ieeextreme-practice/task/my-treat/) |  | 1451/1869 | мінімум днів, щоб збалансувати вечері (підрахунок) | Математика |  | умова |
| 19 | [Palindrome Matrix](https://csacademy.com/ieeextreme-practice/task/palindrome-matrix/) |  | 3303/4559 | клітинки, що мусять бути рівними (DSU над дзеркальними позиціями), вибрати медіану в кожній групі | Структури даних | dsu.h sort.h | умова |
| 14 | [Hotel Wiring](https://csacademy.com/ieeextreme-practice/task/hotel-wiring/) | легка | 1564/2305 | сортування |  | sort.h | теги |
| 13 | [Minimum Permutation](https://csacademy.com/ieeextreme-practice/task/minimum-permutation/) |  | 1080/2568 | влити відсортовану множину в масив, щоб отримати найменшу перестановку |  | sort.h | умова |
| 12 | [Bear Sums](https://csacademy.com/ieeextreme-practice/task/bear-sums/) |  | 936/2298 | пара із заданою сумою: геш-множина або сортування + два вказівники | Структури даних | hashmap.h sort.h | умова |
| 16 | [Scheduler](https://csacademy.com/ieeextreme-practice/task/scheduler/) |  | 821/2185 | завдання тривалістю 2^x на M виконавцях, час за модулем 1e9+7 | Математика | numtheory.h heap.h | умова |
| 18 | [Brick stacks](https://csacademy.com/ieeextreme-practice/task/brick-stacks/) |  | 930/2619 | найменша кількість стосів: сортування + жадібний алгоритм з двійковим пошуком (ланцюжки) |  | sort.h search.h | умова |
| 18 | [Two Fridges](https://csacademy.com/ieeextreme-practice/task/two-fridges/) |  | 2039/5979 | дві температури, що протикають усі відрізки (замітання, перебір усіх значень) | Перебір |  | умова |
| 16 | [Scheduler Redux](https://csacademy.com/ieeextreme-practice/task/scheduler-redux/) |  | 551/1704 | завдання тривалістю 2^x однакової довжини: купа навантажень виконавців | Структури даних | heap.h | умова |
| 13 | [Xtreme Rappers](https://csacademy.com/ieeextreme-practice/task/xtreme-rappers/) |  | 948/3005 | максимальна кількість фраз із 3 слів за двома лічильниками слів (формула) | Математика |  | умова |
| 13 | [Reshuffle Teams](https://csacademy.com/ieeextreme-practice/task/reshuffle-teams/) |  | 129/940 | розсадити 4 команди за столом: усі порядки команд × повороти з префіксними лічильниками | Рядки |  | умова |
| 15 | [Doctor's Appointments](https://csacademy.com/ieeextreme-practice/task/appointment/) | середня | 275/2436 | планування інтервалів: замітання за днями, купа за кінцевим терміном | Структури даних | heap.h sort.h | умова |
| 13 | [Lexical Addition](https://csacademy.com/ieeextreme-practice/task/lexical-addition/) |  | 277/2565 | найкоротша, а потім лексикографічно найменша сума доданків з [A, B] | Математика |  | умова |
| 13 | [Unicornosaurus](https://csacademy.com/ieeextreme-practice/task/unicornosaurus/) |  | 78/740 | покрити зламані відрізки найменшою кількістю джерел живлення (покриття відрізками, замітання) | Структури даних | sort.h | умова |
| 13 | [Pair Swap Teams](https://csacademy.com/ieeextreme-practice/task/pair-swap-teams/) |  | 37/685 | мінімум обмінів, щоб згрупувати команди на колі (підрахунок циклів за порядками команд) | Перебір | combin.h | умова |
| 12 | [Make Distinct](https://csacademy.com/ieeextreme-practice/task/make-distinct/) |  | 44/1239 | мінімум операцій ±1, щоб зробити значення різними (сортування, жадібний алгоритм із купою) |  | sort.h heap.h | умова |

Тема «Жадібні алгоритми і сортування» потрібна також у задачах: [Painter's Dilemma](https://csacademy.com/ieeextreme-practice/task/painters-dilemma/) (10), [P = NP?](https://csacademy.com/ieeextreme-practice/task/pvnp/) (10), [Maximum Sum](https://csacademy.com/ieeextreme-practice/task/04dfa70efd936271ae191cb1a97eb876/) (11), [Octopuses with Watches](https://csacademy.com/ieeextreme-practice/task/59d4aae501fe4ced9ffbf3737acd18a2/) (11), [Poker Game](https://csacademy.com/ieeextreme-practice/task/poker-game/) (14), [Squad Game](https://csacademy.com/ieeextreme-practice/task/squad-game/) (15), [Digits swap](https://csacademy.com/ieeextreme-practice/task/digits-swap/) (18), [Another Sliding Window Problem](https://csacademy.com/ieeextreme-practice/task/another-sliding-window-problem/) (18), [Circular Permutation](https://csacademy.com/ieeextreme-practice/task/circular-permutation/) (19), [Sequence Decomposition](https://csacademy.com/ieeextreme-practice/task/sequence-decomposition/) (19)

## Двійковий пошук

*нижня/верхня межа (lower/upper bound), двійковий пошук за відповіддю.* Бібліотека: search.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [The Twin Occurrence Quest](https://csacademy.com/ieeextreme-practice/task/the-twin-occurrence-quest/) |  | 4548/5844 | перше/останнє входження: нижня і верхня межа (lower/upper bound) |  | search.h | умова |
| 19 | [Circular Permutation](https://csacademy.com/ieeextreme-practice/task/circular-permutation/) |  | 5/7 | мінімізувати максимальне переміщення по колу: перебрати повороти й напрямки | Жадібні | search.h | умова |
| 14 | [Crafting Wooden Tables](https://csacademy.com/ieeextreme-practice/task/crafting-wooden-tables/) | легка | 362/1921 | двійковий пошук за відповіддю |  | search.h | теги |

Тема «Двійковий пошук» потрібна також у задачах: [Finding Shelter](https://csacademy.com/ieeextreme-practice/task/finding-shelter/) (10), [Jarawi and The Interview](https://csacademy.com/ieeextreme-practice/task/6f960361da7beb7f3a083f4776c2cf79/) (11), [Gotta Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/e610aba28810ebcf2d3998692269b5a0/) (11), [Telescope Scheduling](https://csacademy.com/ieeextreme-practice/task/telescope-scheduling/) (12), [Factorial Zeros](https://csacademy.com/ieeextreme-practice/task/factorial-zeros/) (12), [Gotta ~ Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/gotta-catch-em-all/) (12), [Chameleon Walk](https://csacademy.com/ieeextreme-practice/task/chameleon/) (15), [Stable Power Network](https://csacademy.com/ieeextreme-practice/task/stable-power-network/) (19)

## Динамічне програмування

*рюкзак, LIS/LCS, DP на сітці, DP на бітових масках, DP на дереві, DP для підрахунку.* Бібліотека: dp.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [Raju's Matrix Runs](https://csacademy.com/ieeextreme-practice/task/raju-s-matrix-runs/) |  | 9/9 | найдовший зростаючий шлях на сітці: DP за клітинками, відсортованими за значенням | Графи | grid.h sort.h | умова |
| 10 | [Painter's Dilemma](https://csacademy.com/ieeextreme-practice/task/painters-dilemma/) |  | 208/255 | два пензлі, мінімізувати кількість змін кольору: DP за (позиція, інший пензель) | Жадібні | dp.h | умова |
| 11 | [BeetleBag](https://csacademy.com/ieeextreme-practice/task/ed8629419f140a5a2c923b049aba1224/) | легка | 1533/2387 | рюкзак 0/1 |  | dp.h | теги |
| 19 | [Visit Egypt](https://csacademy.com/ieeextreme-practice/task/visit-egypt/) |  | 1874/3273 | упорядковані способи сплатити суму (DP для монет, порядок важливий) | Комбінаторика | dp.h | умова |
| 17 | [Ice Cubes](https://csacademy.com/ieeextreme-practice/task/icecubes/) |  | 878/1827 | DP на сітці з обмеженням на кількість «поганих» клітинок поспіль |  | dp.h | умова |
| 12 | [Lemons](https://csacademy.com/ieeextreme-practice/task/lemons/) |  | 868/1881 | оптимальний у найгіршому випадку пошук на прямій (мінімаксне DP на зразок задачі про яйця) |  | dp.h | умова |
| 16 | [Travel Service](https://csacademy.com/ieeextreme-practice/task/travel-service/) |  | 713/1624 | рішення про заправку на станціях: DP / Дейкстра за (станція, стан) | Графи | paths.h dp.h | умова |
| 12 | [Telescope Scheduling](https://csacademy.com/ieeextreme-practice/task/telescope-scheduling/) |  | 483/1156 | зважене планування інтервалів: сортування за кінцем, DP + двійковий пошук | Двійковий пошук | dp.h search.h sort.h | умова |
| 19 | [Squared Gaps](https://csacademy.com/ieeextreme-practice/task/squared-gaps/) |  | 1307/3403 | DP вирівнювання послідовностей зі зміненою вартістю пропуску | Рядки | dp.h | умова |
| 11 | [Preparing for Xtreme 12.0](https://csacademy.com/ieeextreme-practice/task/72a7d67e7e18f4f7d033f7f5a5a09bef/) | середня | 326/939 | DP на бітових масках підмножин (експоненційна кількість станів) | Біти | dp.h bits.h | теги |
| 11 | [Gotta Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/e610aba28810ebcf2d3998692269b5a0/) | середня | 444/1495 | DP на сітці для мінімального початкового значення, двійковий пошук за відповіддю | Двійковий пошук | dp.h search.h | теги |
| 11 | [The Fast and the Curious](https://csacademy.com/ieeextreme-practice/task/e1e444f71a2a7a69baf4c61ed756aa55/) | середня | 218/980 | DFS + DP на графі | Графи | graph.h dp.h | теги |
| 15 | [Language Learning](https://csacademy.com/ieeextreme-practice/task/language-learning/) | середня | 151/709 | різні підпослідовності з проміжком індексів > K (DP + префіксні суми, останнє входження) | Комбінаторика | dp.h hashmap.h | умова |
| 15 | [Training Plan](https://csacademy.com/ieeextreme-practice/task/training-plan/) | середня | 77/373 | DP з обмеженням «не більше K поспіль» (монотонна черга) |  | dp.h linear.h | умова |
| 11 | [Pyramid](https://csacademy.com/ieeextreme-practice/task/5e98e4b17b3477e671568a437388fb7a/) | складна | 121/714 | DP на числовому трикутнику + формули в замкненому вигляді | Математика | dp.h | теги |
| 18 | [Invertible Pairs](https://csacademy.com/ieeextreme-practice/task/invertible-pairs/) |  | 357/2120 | максимальний підмасив з необов’язковою зміною знака пар (Кадане зі станами) |  | dp.h | умова |
| 11 | [Sub Array Sum Problem](https://csacademy.com/ieeextreme-practice/task/46e8a03f242b875f1ae5fb84a3b4321f/) | складна | 143/865 | сума сум усіх підмасивів / підматриць через внески, префіксні суми |  | grid.h | теги |
| 16 | [Dream Team](https://csacademy.com/ieeextreme-practice/task/dream-team/) |  | 303/1960 | один гравець на кожну позицію в межах бюджету (рюкзак із групами) | Перебір | dp.h | умова |
| 11 | [Lion Territory](https://csacademy.com/ieeextreme-practice/task/15443fc9f89feb90bc30096f43b308af/) | складна | 85/573 | DP на сітці, двовимірні префіксні суми |  | dp.h grid.h | теги |
| 15 | [Coloring Tiles](https://csacademy.com/ieeextreme-practice/task/coloring-tiles/) | складна | 16/227 | DP рядок за рядком по шаблонах кольорів (підрахунок) | Комбінаторика | dp.h | умова |
| 13 | [Charlie New PC](https://csacademy.com/ieeextreme-practice/task/charlie-new-pc/) |  | 99/1476 | рюкзак із групами: одна деталь кожного типу, максимальна вартість у межах бюджету |  | dp.h | умова |
| 13 | [Merchant Association](https://csacademy.com/ieeextreme-practice/task/merchant-association/) | найскладніша | 25/674 | DP на дереві | Дерева | tree.h | теги |
| 14 | [Restaurant Reopening](https://csacademy.com/ieeextreme-practice/task/restaurant-reopening/) | найскладніша | 5/176 | DP на бітових масках (експоненційна кількість станів) | Біти | dp.h bits.h | теги |
| 14 | [Social Distancing in Class](https://csacademy.com/ieeextreme-practice/task/social-distancing/) | найскладніша | 9/526 | DP на дереві | Дерева | tree.h | теги |

Тема «Динамічне програмування» потрібна також у задачах: [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) (11), [Fibonacci](https://csacademy.com/ieeextreme-practice/task/09f92a575cc006d4a6a7f525f370ec30/) (11), [Orienteering](https://csacademy.com/ieeextreme-practice/task/95352fd33b0e855d337b5b3ed85da3b6/) (11), [Elementary](https://csacademy.com/ieeextreme-practice/task/c787255968c972c653677a52599ecc2f/) (11), [Friendly Sequences](https://csacademy.com/ieeextreme-practice/task/friendly-sequences/) (12), [Product Rectangle](https://csacademy.com/ieeextreme-practice/task/product-rectangle/) (12), [Tweedledee's Split Brackets](https://csacademy.com/ieeextreme-practice/task/tweedledees-split-brackets/) (12), [Ranged Alfa Pool](https://csacademy.com/ieeextreme-practice/task/ranged-alfa-pool/) (13), [Alfa Pool](https://csacademy.com/ieeextreme-practice/task/alfa-pool/) (13), [Non-Overlapping Palindromes](https://csacademy.com/ieeextreme-practice/task/nonoverlapping-palindromes/) (14), [Maximum Exploitation](https://csacademy.com/ieeextreme-practice/task/exploitation/) (15), [Candy Shop](https://csacademy.com/ieeextreme-practice/task/candy-shop/) (15), [Weird Reward](https://csacademy.com/ieeextreme-practice/task/weird-reward/) (16), [Polygon Cutting](https://csacademy.com/ieeextreme-practice/task/polygon-cutting/) (17), [Happy Numbers](https://csacademy.com/ieeextreme-practice/task/happy_numbers/) (17), [Ordered Permutations](https://csacademy.com/ieeextreme-practice/task/ordered-permutations/) (17), [Watershed](https://csacademy.com/ieeextreme-practice/task/watershed/) (17), [Triumvirates](https://csacademy.com/ieeextreme-practice/task/triumvirates/) (18), [Increasing table](https://csacademy.com/ieeextreme-practice/task/increasing-table/) (18), [Star Road](https://csacademy.com/ieeextreme-practice/task/star-road/) (18), [Halving](https://csacademy.com/ieeextreme-practice/task/halving/) (18), [Stones](https://csacademy.com/ieeextreme-practice/task/stones/) (18), [Four Piles](https://csacademy.com/ieeextreme-practice/task/four-piles/) (19), [Bitonic Sequences](https://csacademy.com/ieeextreme-practice/task/bitonic-sequences/) (19)

## Графи

*BFS/DFS, найкоротші шляхи, MST, топологічне сортування, SCC, мости, паросполучення, потоки.* Бібліотека: graph.h, paths.h, flow.h, grid.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 18 | [King's Order](https://csacademy.com/ieeextreme-practice/task/kings-order/) |  | 3162/3547 | топологічне сортування з пріоритетами (купа), виявлення циклу |  | graph.h heap.h | умова |
| 11 | [Vangelis the Batbear and the Bubbles challenge](https://csacademy.com/ieeextreme-practice/task/979a09a0cd8c4e98dd0a690f39a55bd2/) | легка | 1924/2921 | пошук циклів за допомогою DSU / DFS | Структури даних | dsu.h graph.h | теги |
| 16 | [Invisible Ghosts](https://csacademy.com/ieeextreme-practice/task/invisible-ghosts/) | середня | 380/610 | BFS з лексикографічно найменшим шляхом, привиди як BFS з кількох джерел |  | graph.h grid.h | умова |
| 11 | [Fill The Pixels](https://csacademy.com/ieeextreme-practice/task/bd45c86a844acd8ffc58b6a965cb0197/) | середня | 317/527 | заливка області на піксельній сітці |  | grid.h | теги |
| 17 | [Watershed](https://csacademy.com/ieeextreme-practice/task/watershed/) |  | 795/1461 | стікання води на сітці: обробка клітинок у порядку спадання висоти (DAG) | DP | grid.h sort.h | умова |
| 10 | [Binary Quilts](https://csacademy.com/ieeextreme-practice/task/binary-quilts/) |  | 30/57 | BFS по 2^25 станах дошки, збережених як бітові маски | Біти | graph.h bits.h | умова |
| 10 | [Pirates](https://csacademy.com/ieeextreme-practice/task/pirates/) |  | 40/76 | позначити острови заливкою, 0-1 BFS для підрахунку перетинів островів |  | grid.h paths.h | умова |
| 11 | [Orienteering](https://csacademy.com/ieeextreme-practice/task/95352fd33b0e855d337b5b3ed85da3b6/) | середня | 266/515 | Дейкстра між контрольними точками + TSP на бітових масках | DP | paths.h dp.h | теги |
| 19 | [Stable Power Network](https://csacademy.com/ieeextreme-practice/task/stable-power-network/) |  | 2212/4347 | мінімізувати максимальний ризик, потім час: сортування/двійковий пошук за ризиком + Дейкстра | Двійковий пошук | paths.h dsu.h | умова |
| 19 | [Airline Traveling](https://csacademy.com/ieeextreme-practice/task/airline-traveling/) |  | 1852/3728 | точна сумарна кількість миль на зірці рейсів: міркування про парність і НСД | Математика | numtheory.h graph.h | умова |
| 16 | [Tourist Taxi Service](https://csacademy.com/ieeextreme-practice/task/tourist-taxi-service/) | середня | 116/297 | найкоротші поїздки, що починаються з 5 різних вулиць: Дейкстра на розширених станах |  | paths.h | умова |
| 16 | [Wireless Network](https://csacademy.com/ieeextreme-practice/task/wireless-network/) |  | 156/422 | мінімальне кістякове дерево з вартостями покращення (Крускал) |  | graph.h dsu.h | умова |
| 11 | [Shuffle](https://csacademy.com/ieeextreme-practice/task/0186cd4b3a330dc501606737e090e0da/) | середня | 311/853 | максимальне паросполучення в дводольному графі |  | flow.h | теги |
| 11 | [Collecting Gold](https://csacademy.com/ieeextreme-practice/task/333043935273ab966569971859d1835b/) | середня | 320/906 | найкоротші шляхи (алгоритм Дейкстри) |  | paths.h | теги |
| 16 | [Random Mazes](https://csacademy.com/ieeextreme-practice/task/random-mazes/) |  | 98/278 | правила лабіринту: зв’язність і цикли в областях (BFS / DSU) |  | graph.h dsu.h grid.h | умова |
| 15 | [Chameleon Walk](https://csacademy.com/ieeextreme-practice/task/chameleon/) | середня | 120/416 | двійковий пошук за C + Дейкстра | Двійковий пошук | paths.h search.h | умова |
| 17 | [Rumors](https://csacademy.com/ieeextreme-practice/task/rumors/) |  | 405/1660 | можливі джерела чуток: досяжність, конденсація SCC |  | graph.h | умова |
| 19 | [Domino Path](https://csacademy.com/ieeextreme-practice/task/domino-path/) |  | 637/3377 | підмножини доміно, що утворюють ланцюжок: ейлерів шлях (степені + зв’язність) по підмножинах | Біти | bits.h dsu.h | умова |
| 13 | [Alfa Universe Weight Sorting](https://csacademy.com/ieeextreme-practice/task/alfa-universe-weight-sorting/) | складна | 95/534 | відомі пари порядку з порівнянь: транзитивне замикання / топологічний порядок |  | graph.h | умова |
| 12 | [Gotta ~ Catch 'Em All](https://csacademy.com/ieeextreme-practice/task/gotta-catch-em-all/) |  | 51/325 | двійковий пошук за часом + паросполучення в дводольному графі (кожна лунка вміщує двох) | Двійковий пошук | flow.h search.h | умова |
| 17 | [National Highway System](https://csacademy.com/ieeextreme-practice/task/national_highways/) |  | 161/1110 | ребра, що входять хоча б в одне MST: Крускал групами рівної ваги + мости |  | graph.h dsu.h | умова |
| 12 | [Barter System](https://csacademy.com/ieeextreme-practice/task/barter-system/) |  | 154/1170 | курси обміну як добутки вздовж шляхів (DFS / зважена DSU) |  | graph.h dsu.h | умова |
| 13 | [Bearcity Renting](https://csacademy.com/ieeextreme-practice/task/bearcity-renting/) |  | 62/507 | вулиці, що лишаються двосторонніми за будь-якої сильно зв’язної орієнтації = мости |  | graph.h | умова |
| 17 | [Combo Lock Redux](https://csacademy.com/ieeextreme-practice/task/combo_locks/) |  | 58/522 | найкоротші ходи через BFS + кількість найкоротших шляхів за модулем p | Комбінаторика | graph.h | умова |
| 14 | [Magical Stones I](https://csacademy.com/ieeextreme-practice/task/magical-stones/) | середня | 100/1162 | BFS по станах |  | graph.h | теги |
| 14 | [Magical Stones II](https://csacademy.com/ieeextreme-practice/task/magical-stones-2/) | складна | 29/433 | BFS по станах каменів, конструктивна відповідь | Конструктивні | graph.h bits.h | теги |
| 17 | [Theme Park](https://csacademy.com/ieeextreme-practice/task/theme_park/) |  | 19/296 | змінити вартості, не створивши від’ємного циклу: Беллман–Форд / потенціали |  | paths.h | умова |
| 14 | [The Last of Us](https://csacademy.com/ieeextreme-practice/task/the-last-of-us/) | найскладніша | 4/95 | Дейкстра (задача лише з відповіддю у виведенні) |  | paths.h | теги |
| 15 | [The Tortoise and The Hare](https://csacademy.com/ieeextreme-practice/task/the-tortoise-and-the-hare/) | найскладніша | 23/999 | Дейкстра, вибір міста для блокування |  | paths.h | теги |
| 10 | [Finding Shelter](https://csacademy.com/ieeextreme-practice/task/finding-shelter/) |  | 0/41 | вузьке призначення: двійковий пошук + паросполучення в дводольному графі, потім паросполучення мінімальної вартості | Двійковий пошук | flow.h search.h | умова |

Тема «Графи» потрібна також у задачах: [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) (11), [Odd Cycle Check](https://csacademy.com/ieeextreme-practice/task/e21a405d32da71227e2d5fb313fd19d4/) (11), [The Fast and the Curious](https://csacademy.com/ieeextreme-practice/task/e1e444f71a2a7a69baf4c61ed756aa55/) (11), [The Gold-diggers](https://csacademy.com/ieeextreme-practice/task/the-gold-diggers/) (12), [Rescue Mission](https://csacademy.com/ieeextreme-practice/task/rescue-mission/) (14), [Travel Service](https://csacademy.com/ieeextreme-practice/task/travel-service/) (16), [Cheap Construction](https://csacademy.com/ieeextreme-practice/task/cheap-construction/) (18), [Raju's Matrix Runs](https://csacademy.com/ieeextreme-practice/task/raju-s-matrix-runs/) (19)

## Дерева

*підвішування за корінь, розміри піддерев, LCA, діаметр, DP на дереві, HLD, ейлерів обхід.* Бібліотека: tree.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [White knights and Black warriors](https://csacademy.com/ieeextreme-practice/task/white-knights-and-black-warriors/) |  | 2438/2871 | відстань від шляху до найближчої білої вершини: BFS з кількох джерел + мінімум на шляху |  | tree.h graph.h | умова |
| 18 | [Icarus](https://csacademy.com/ieeextreme-practice/task/icarus/) |  | 2430/3618 | побудувати бінарне дерево, у якому обхід потрапляє в пастку (моделювання + побудова) | Конструктивні |  | умова |
| 11 | [Rumour](https://csacademy.com/ieeextreme-practice/task/9ca8fafd184f553a903734761546a224/) | легка | 1311/2126 | відстань у неявному повному бінарному дереві через бітові зсуви (LCA) | Біти | bits.h | теги |
| 19 | [Beatrice and the Dream Tree](https://csacademy.com/ieeextreme-practice/task/beatrice-and-the-dream-tree/) |  | 1679/3848 | нерозрізненні вершини: гешування кореневих дерев / автоморфізми |  | tree.h hashmap.h | умова |
| 12 | [Drawing Rooted Binary Trees](https://csacademy.com/ieeextreme-practice/task/drawing-rooted-binary-trees/) |  | 696/1828 | побудувати бінарне дерево, ASCII-малюнок за стовпцями симетричного обходу | Реалізація |  | умова |
| 15 | [Bridge Construction](https://csacademy.com/ieeextreme-practice/task/bridge/) | середня | 138/383 | з’єднати два дерева: діаметри й радіуси, max(d1, d2, r1 + r2 + 1) |  | tree.h | умова |
| 15 | [Spies of Red and Blue](https://csacademy.com/ieeextreme-practice/task/spies/) | легка | 297/918 | моделювання передавання інформації у двох ієрархіях (глибини, події) | Реалізація | tree.h | умова |
| 13 | [Xranda and Tree](https://csacademy.com/ieeextreme-practice/task/xranda-and-tree/) |  | 197/991 | сума за парами вершин максимального ребра на шляху: порядок Крускала + розміри множин DSU | Структури даних | dsu.h | умова |
| 13 | [The Lonely Shepherd](https://csacademy.com/ieeextreme-practice/task/lonely-shepherd/) |  | 78/400 | розріз дерева і перемикання, незалежні від розфарбування (парність, DP на дереві) | Конструктивні | tree.h | умова |
| 16 | [ANDman](https://csacademy.com/ieeextreme-practice/task/andman/) | найскладніша | 205/1177 | добутки на шляхах з точковими оновленнями: HLD + дерево відрізків (добуток за модулем) | Структури даних | tree.h segtree.h | умова |
| 12 | [Tree Fun](https://csacademy.com/ieeextreme-practice/task/tree-fun/) |  | 96/593 | додавання на шляхах: різницевий масив на дереві + LCA (або HLD), потім максимум |  | tree.h | умова |
| 17 | [He Loves Data Structures](https://csacademy.com/ieeextreme-practice/task/data_structures/) |  | 56/569 | оновлення піддерев з функцією Ейлера: ейлерів обхід + дерево Фенвіка / відрізків, решето | Структури даних, Математика | tree.h fenwick.h numtheory.h | умова |
| 16 | [Queries on a Tree](https://csacademy.com/ieeextreme-practice/task/queries-on-a-tree/) |  | 15/173 | сума за підмножинами ребер квадратів сум компонент, з оновленнями | Комбінаторика | tree.h | умова |
| 13 | [Monokeros](https://csacademy.com/ieeextreme-practice/task/monokeros/) |  | 131/1548 | глибини вставок у BST: попередник/наступник у впорядкованій множині (дерево Фенвіка) | Структури даних | fenwick.h | умова |
| 15 | [Bus Company](https://csacademy.com/ieeextreme-practice/task/buscompany/) | найскладніша | 31/377 | середні довжини шляхів у кожній компанії: підрахунок внесків на дереві | Комбінаторика | tree.h | умова |
| 19 | [Diameter Problem Again](https://csacademy.com/ieeextreme-practice/task/diameter-problem-again/) |  | 193/2772 | діаметр множин вершин з від’ємними вагами: дерево відрізків кінців діаметра + LCA | Структури даних | tree.h segtree.h | умова |
| 14 | [Identifying Infected](https://csacademy.com/ieeextreme-practice/task/identifying-infected/) | складна | 63/912 | найнижчий спільний предок |  | tree.h | теги |
| 12 | [Organizational Chart](https://csacademy.com/ieeextreme-practice/task/organizational-chart/) |  | 36/593 | межі розмірів піддерев за пропущених звітів (DP на дереві) |  | tree.h | умова |
| 15 | [Xtreme Teleportation](https://csacademy.com/ieeextreme-practice/task/teleportation/) | найскладніша | 12/229 | запити вузького місця на шляху: максимальне кістякове дерево + LCA (або офлайн DSU) | Структури даних | dsu.h tree.h | умова |
| 18 | [Star Road](https://csacademy.com/ieeextreme-practice/task/star-road/) |  | 123/4816 | найкращий шлях у дереві за зірками ресторанів (DP на дереві) | DP | tree.h | умова |
| 18 | [Queries](https://csacademy.com/ieeextreme-practice/task/queries/) |  | 38/3067 | сума за підмножинами ребер квадратів сум компонент, з оновленнями | Комбінаторика | tree.h | умова |
| 17 | [Tree Queries 2](https://csacademy.com/ieeextreme-practice/task/tree-queries-2/) |  | 4/343 | оцінки шляхів з оновленнями: HLD + дерево відрізків лінійних відображень | Структури даних | tree.h segtree.h | умова |
| 18 | [This is not an optimization problem](https://csacademy.com/ieeextreme-practice/task/this-is-not-an-optimization-problem/) |  | 11/1714 | сума ваг дерев Штейнера за всіма k-підмножинами: внески ребер з біноміальними коефіцієнтами + NTT | Комбінаторика | fft.h combin.h tree.h | умова |

Тема «Дерева» потрібна також у задачах: [Merchant Association](https://csacademy.com/ieeextreme-practice/task/merchant-association/) (13), [Social Distancing in Class](https://csacademy.com/ieeextreme-practice/task/social-distancing/) (14), [Polygon Cutting](https://csacademy.com/ieeextreme-practice/task/polygon-cutting/) (17), [Hack the coach!](https://csacademy.com/ieeextreme-practice/task/hack-the-coach/) (19)

## Структури даних

*префіксні суми, дерево Фенвіка, дерево відрізків (з відкладеним оновленням), розріджена таблиця, DSU, монотонний стек/черга, гешування.* Бібліотека: fenwick.h, segtree.h, sparse.h, dsu.h, linear.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [Easy Sum](https://csacademy.com/ieeextreme-practice/task/easy-sum/) |  | 6/8 | сума за підмасивами через пороги для кожного біта (два вказівники, підрахунок) | Біти | bits.h | умова |
| 19 | [Become as One](https://csacademy.com/ieeextreme-practice/task/become-as-one/) |  | 9/12 | перевірка відрізка: злиття рівних значень як двійкові переноси (гешування / дерево відрізків) | Математика | segtree.h | умова |
| 19 | [Baker's Competition](https://csacademy.com/ieeextreme-practice/task/bakers-competition/) |  | 1479/3718 | підрахунок пар на відрізках: офлайн-запити з деревом Фенвіка | Математика | fenwick.h | умова |
| 13 | [Protecting the Hive](https://csacademy.com/ieeextreme-practice/task/protecting-the-hive/) |  | 145/436 | DSU на шестикутній сітці з підтримкою периметрів | Геометрія | dsu.h | умова |
| 17 | [Long Lines](https://csacademy.com/ieeextreme-practice/task/long_lines/) |  | 1150/3806 | підрахунок пар, що бачать одне одного, монотонним стеком |  | linear.h | умова |
| 19 | [Continued Fractions](https://csacademy.com/ieeextreme-practice/task/continued-fractions/) |  | 932/3215 | глобальне додавання / обернення дробів за модулем p як відображення матрицями 2x2 (Мебіуса) | Математика | matrix.h numtheory.h | умова |
| 11 | [Odd Cycle Check](https://csacademy.com/ieeextreme-practice/task/e21a405d32da71227e2d5fb313fd19d4/) | складна | 186/649 | онлайн-перевірка дводольності: DSU з парністю | Графи | dsu.h | теги |
| 11 | [Mister Counter](https://csacademy.com/ieeextreme-practice/task/3dd761f749054a509a0012c5beee0e35/) | складна | 129/531 | підрахунок перестановок за допомогою стека | Математика | linear.h combin.h | теги |
| 15 | [Maximum Exploitation](https://csacademy.com/ieeextreme-practice/task/exploitation/) | середня | 180/965 | два прямокутники, що не перетинаються: двовимірні префіксні суми + найкращий прямокутник з кожного боку | DP | grid.h | умова |
| 14 | [Coupon Codes](https://csacademy.com/ieeextreme-practice/task/coupon-codes/) | середня | 172/960 | гешування кодів | Рядки | hashmap.h | теги |
| 14 | [Rescue Mission](https://csacademy.com/ieeextreme-practice/task/rescue-mission/) | складна | 100/677 | DSU, дерево відрізків, максимальний потік | Графи | segtree.h dsu.h flow.h | теги |
| 16 | [Outpost](https://csacademy.com/ieeextreme-practice/task/outpost/) |  | 79/736 | прямокутник максимальної площі з max-min <= t: монотонні деки / розріджені таблиці |  | linear.h sparse.h | умова |
| 11 | [Knin](https://csacademy.com/ieeextreme-practice/task/a8030fdc5d7b32664ec5b9addc418f83/) | найскладніша | 44/445 | дерево відрізків за дуже малого обмеження пам’яті | Ігри | segtree.h | теги |
| 18 | [Rectangles and arrays](https://csacademy.com/ieeextreme-practice/task/rectangles-and-arrays-ieeextreme-18/) |  | 145/2572 | найбільший прямокутник у гістограмі з однією зміною (монотонний стек, префікси/суфікси) |  | linear.h | умова |
| 13 | [Sic Semper Tyrannosaurus!](https://csacademy.com/ieeextreme-practice/task/sic-semper-tyrannosaurus/) | найскладніша | 17/333 | дерево відрізків |  | segtree.h | теги |
| 16 | [Poker Tournament](https://csacademy.com/ieeextreme-practice/task/poker-tournament/) |  | 13/255 | оновлення на відрізках, підрахунок виборів учасників: дерево відрізків добутків | Комбінаторика | segtree.h | умова |
| 14 | [Parkour](https://csacademy.com/ieeextreme-practice/task/parkour/) | найскладніша | 12/280 | запити мінімуму на відрізку (розріджена таблиця) |  | sparse.h | теги |
| 18 | [Corporation](https://csacademy.com/ieeextreme-practice/task/corporation/) |  | 84/2726 | дерево відрізків з відкладеним оновленням: присвоєння на відрізку + додавання на відрізку + суми |  | segtree.h | умова |
| 18 | [Another Sliding Window Problem](https://csacademy.com/ieeextreme-practice/task/another-sliding-window-problem/) |  | 83/3187 | оптимальна вартість розбиття вікон на пари (сортування, два вказівники, структури даних) | Жадібні | sort.h | умова |

Тема «Структури даних» потрібна також у задачах: [Safety](https://csacademy.com/ieeextreme-practice/task/safety/) (10), [Vangelis the Batbear and the Bubbles challenge](https://csacademy.com/ieeextreme-practice/task/979a09a0cd8c4e98dd0a690f39a55bd2/) (11), [Bear Sums](https://csacademy.com/ieeextreme-practice/task/bear-sums/) (12), [Monokeros](https://csacademy.com/ieeextreme-practice/task/monokeros/) (13), [Unicornosaurus](https://csacademy.com/ieeextreme-practice/task/unicornosaurus/) (13), [Xranda and Tree](https://csacademy.com/ieeextreme-practice/task/xranda-and-tree/) (13), [The Defensive Walls](https://csacademy.com/ieeextreme-practice/task/defensive-walls/) (14), [Image Convolution](https://csacademy.com/ieeextreme-practice/task/image-convolution/) (15), [Xtreme Teleportation](https://csacademy.com/ieeextreme-practice/task/teleportation/) (15), [Doctor's Appointments](https://csacademy.com/ieeextreme-practice/task/appointment/) (15), [ANDman](https://csacademy.com/ieeextreme-practice/task/andman/) (16), [Scheduler Redux](https://csacademy.com/ieeextreme-practice/task/scheduler-redux/) (16), [He Loves Data Structures](https://csacademy.com/ieeextreme-practice/task/data_structures/) (17), [Tree Queries 2](https://csacademy.com/ieeextreme-practice/task/tree-queries-2/) (17), [Different Xor Values](https://csacademy.com/ieeextreme-practice/task/different_xor/) (17), [Laser Defense](https://csacademy.com/ieeextreme-practice/task/laser-defense/) (18), [Diameter Problem Again](https://csacademy.com/ieeextreme-practice/task/diameter-problem-again/) (19), [Palindrome Matrix](https://csacademy.com/ieeextreme-practice/task/palindrome-matrix/) (19)

## Геометрія

*векторний добуток, площа многокутника, опукла оболонка, точка в многокутнику, формула Піка, замітальна пряма.* Бібліотека: geom.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 10 | [Ellipse Art](https://csacademy.com/ieeextreme-practice/task/ellipse-art/) |  | 79/110 | площа об’єднання еліпсів: чисельне інтегрування на дрібній сітці |  | geom.h | умова |
| 11 | [Aeneas' cryptographic disc (4th c. B.C.)](https://csacademy.com/ieeextreme-practice/task/d48ada9a7213299f1b24b22b2fb9443f/) | легка | 1031/1545 | відстані між точками на колі (тригонометрія) |  | geom.h | теги |
| 18 | [Stick](https://csacademy.com/ieeextreme-practice/task/stick/) |  | 2079/4660 | площа об’єднання рівних квадратів, що перекриваються (формула) | Математика |  | умова |
| 18 | [Laser Defense](https://csacademy.com/ieeextreme-practice/task/laser-defense/) |  | 1819/4209 | області, на які ділять промені: підрахунок перетинів (інверсії деревом Фенвіка) + формула Ейлера | Структури даних | fenwick.h geom.h | умова |
| 17 | [Polygon Cutting](https://csacademy.com/ieeextreme-practice/task/polygon-cutting/) |  | 51/826 | частини утворюють дерево: незалежна множина максимальної ваги (DP на дереві), площі за формулою Гаусса («шнурівки») | Дерева, DP | geom.h tree.h | умова |
| 14 | [Linearly Separable Samples](https://csacademy.com/ieeextreme-practice/task/linearly-separable-samples/) | середня | 62/1270 | перевірка існування роздільної прямої (опуклі оболонки) |  | geom.h | теги |
| 15 | [Polygon](https://csacademy.com/ieeextreme-practice/task/polygon/) | складна | 9/325 | точки цілочисельної ґратки плоского многокутника у просторі: проєкція + формула Піка | Математика | geom.h numtheory.h | умова |
| 14 | [The Defensive Walls](https://csacademy.com/ieeextreme-practice/task/defensive-walls/) | найскладніша | 6/348 | замітальна пряма з деревом відрізків | Структури даних | geom.h segtree.h | теги |
| 15 | [Squad Game](https://csacademy.com/ieeextreme-practice/task/squad-game/) |  | 6/352 | утворити трикутники з мінімальною сумарною площею (сортування, паросполучення) | Жадібні | geom.h | умова |
| 13 | [Strictly Convex Pairs](https://csacademy.com/ieeextreme-practice/task/strictly-convex-pairs/) | найскладніша | 11/665 | строго опуклий многокутник: два вказівники (rotating calipers) |  | geom.h | теги |
| 18 | [Triumvirates](https://csacademy.com/ieeextreme-practice/task/triumvirates/) |  | 4/3316 | згрупувати точки в трійки з мінімальною стійкістю (сортування + DP) | DP | geom.h | умова |

Тема «Геометрія» потрібна також у задачах: [Protecting the Hive](https://csacademy.com/ieeextreme-practice/task/protecting-the-hive/) (13), [Image Similarity](https://csacademy.com/ieeextreme-practice/task/image-similarity/) (15), [Pizza Cutter](https://csacademy.com/ieeextreme-practice/task/pizza-cutter/) (16)

## Теорія ігор

*DP виграшних/програшних позицій, мінімакс, Нім, теорема Шпрага–Ґранді.* Бібліотека: game.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [Four Piles](https://csacademy.com/ieeextreme-practice/task/four-piles/) |  | 7/8 | кількість позицій Нім з XOR != 0 на діапазонах: DP за цифрами над бітами | DP | game.h bits.h | умова |
| 18 | [Stones](https://csacademy.com/ieeextreme-practice/task/stones/) |  | 271/2157 | оптимальна ймовірність виграшу: DP / мінімакс за станами | DP | dp.h | умова |
| 12 | [The Gold-diggers](https://csacademy.com/ieeextreme-practice/task/the-gold-diggers/) | складна | 40/456 | мінімакс для двох гравців за (позиції, зібрані монети), відстані BFS | Графи | game.h graph.h | умова |
| 16 | [Queen](https://csacademy.com/ieeextreme-practice/task/queen/) |  | 38/602 | гра з ферзем типу Вітгоффа з допуском K: закономірність програшних позицій | Математика | game.h | умова |

Тема «Теорія ігор» потрібна також у задачах: [Knin](https://csacademy.com/ieeextreme-practice/task/a8030fdc5d7b32664ec5b9addc418f83/) (11), [Let’s Cheer Up Bob](https://csacademy.com/ieeextreme-practice/task/ca9bc49133da9c3c90df045f4ea8fdd3/) (11), [PIEEEXMan](https://csacademy.com/ieeextreme-practice/task/pieeexman/) (12)

## Інтерактивні задачі

*протокол запитів, скидання буфера, адаптивні стратегії.* Бібліотека: interactive.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 12 | [Troll Coder](https://csacademy.com/ieeextreme-practice/task/troll-coder/) |  | 1575/2307 | відновити бінарну послідовність з відповідей «скільки бітів правильні» |  | interactive.h | умова |
| 13 | [Concentration Game](https://csacademy.com/ieeextreme-practice/task/concentration-game/) |  | 583/1084 | гра «Пам’ять» з картками: запам’ятовувати відкриті картки |  | interactive.h | умова |
| 11 | [King Capture](https://csacademy.com/ieeextreme-practice/task/cd05154d910e28e73ca3930e9a5103f5/) | найскладніша | 90/656 | адаптивна інтерактивна гра на графі, DP за позиціями | Графи, DP | interactive.h graph.h | теги |
| 15 | [Secret Boxes](https://csacademy.com/ieeextreme-practice/task/secret-boxes/) | складна | 18/249 | адаптивне інтерактивне розпізнавання скриньок |  | interactive.h | умова |
| 12 | [Troll Coder - Escape](https://csacademy.com/ieeextreme-practice/task/troll-coder-escape/) |  | 33/1041 | відгадати бінарну послідовність за малу кількість запитів (адаптивне групове тестування) |  | interactive.h | умова |
| 12 | [PIEEEXMan](https://csacademy.com/ieeextreme-practice/task/pieeexman/) |  | 5/232 | інтерактивна гра-переслідування на сітці, відстані BFS | Ігри | interactive.h grid.h | умова |

## Повний перебір і перебір із поверненням

*перебір варіантів, відсікання, «зустріч посередині», пошук у просторі станів.* Бібліотека: util.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 12 | [Xtreme Fake Coins](https://csacademy.com/ieeextreme-practice/task/xtreme-fake-coins/) |  | 331/578 | повний перебір пар монет, перевірка всіх зважувань | Реалізація |  | умова |
| 10 | [Checkers Challenge](https://csacademy.com/ieeextreme-practice/task/checkers-challenge/) |  | 29/52 | DFS по послідовностях взяттів (перебір із поверненням) |  |  | умова |
| 11 | [Octopuses with Watches](https://csacademy.com/ieeextreme-practice/task/59d4aae501fe4ced9ffbf3737acd18a2/) | середня | 334/781 | перебір із поверненням і відсіканням за жорсткого обмеження пам’яті | Жадібні |  | теги |
| 18 | [Digits swap](https://csacademy.com/ieeextreme-practice/task/digits-swap/) |  | 966/3103 | максимізувати число, зробивши не більше K обмінів цифр (DFS з відсіканням) | Жадібні |  | умова |
| 11 | [Let’s Cheer Up Bob](https://csacademy.com/ieeextreme-practice/task/ca9bc49133da9c3c90df045f4ea8fdd3/) | середня | 347/1258 | пошук у дереві гри (хрестики-нулики), перебір із поверненням | Ігри | game.h | теги |
| 14 | [Coin Collector](https://csacademy.com/ieeextreme-practice/task/coin-collector/) | середня | 74/660 | максимізувати винагороди з наборів монет: перебрати кількості деяких наборів + жадібний алгоритм | Математика |  | умова |
| 10 | [Weighty Decisions](https://csacademy.com/ieeextreme-practice/task/weighty-decisions/) |  | 2/45 | мінімальна кількість зважувань на шальках терезів (інформаційна оцінка + пошук) | Математика |  | умова |
| 14 | [Poker Game](https://csacademy.com/ieeextreme-practice/task/poker-game/) | складна | 32/809 | перебір із поверненням по наборах карт | Жадібні |  | теги |
| 16 | [Combo Locks](https://csacademy.com/ieeextreme-practice/task/combo-locks/) | складна | 34/1208 | вибрати літери колеса, щоб скласти багато слів (евристичний пошук) |  | trie.h | умова |

Тема «Повний перебір і перебір із поверненням» потрібна також у задачах: [Pair Swap Teams](https://csacademy.com/ieeextreme-practice/task/pair-swap-teams/) (13), [Dream Team](https://csacademy.com/ieeextreme-practice/task/dream-team/) (16), [Two Fridges](https://csacademy.com/ieeextreme-practice/task/two-fridges/) (18), [Bounded tuples](https://csacademy.com/ieeextreme-practice/task/bounded-tuples/) (18)

## Бітові операції

*маски, трюки з XOR, підмножини, XOR-базис.* Бібліотека: bits.h.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 12 | [Bit Soccer](https://csacademy.com/ieeextreme-practice/task/bit-soccer/) |  | 499/959 | OR масок усіх гравців, які є підмасками цільової маски |  | bits.h | умова |
| 19 | [Shailesh's Triplet](https://csacademy.com/ieeextreme-practice/task/shailesh-s-triplet/) |  | 2682/5278 | A + B + C = 2N і A ^ B ^ C = N: побітова побудова | Конструктивні | bits.h | умова |
| 11 | [RecXor](https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/) | середня | 583/1172 | XOR чисел 1..n за O(1), XOR по прямокутнику | Математика | bits.h | теги |
| 17 | [Different Xor Values](https://csacademy.com/ieeextreme-practice/task/different_xor/) |  | 50/524 | сума рангів XOR-базису по підмасивах (лінійний базис для кожного правого кінця) | Структури даних | bits.h | умова |
| 15 | [Xtreme Teams](https://csacademy.com/ieeextreme-practice/task/xtreme-teams/) | середня | 117/1468 | кількість трійок, у яких OR масок тем дає всі одиниці (лічильники масок, SOS DP) | Комбінаторика | bits.h | умова |
| 13 | [Luck-i-flip](https://csacademy.com/ieeextreme-practice/task/luck-i-flip/) |  | 51/697 | виграшні розіграші ставок у вигляді бітових рядків (міркування з бітовими масками, підрахунок) | Комбінаторика | bits.h | умова |
| 14 | [ARM Constant Multiplication](https://csacademy.com/ieeextreme-practice/task/arm/) | найскладніша | 7/340 | множення на константу зсувами й додаваннями (пошук серед виразів) | Зворотна розробка | bits.h | теги |

Тема «Бітові операції» потрібна також у задачах: [Binary Quilts](https://csacademy.com/ieeextreme-practice/task/binary-quilts/) (10), [Preparing for Xtreme 12.0](https://csacademy.com/ieeextreme-practice/task/72a7d67e7e18f4f7d033f7f5a5a09bef/) (11), [Rumour](https://csacademy.com/ieeextreme-practice/task/9ca8fafd184f553a903734761546a224/) (11), [Barrett Reduction](https://csacademy.com/ieeextreme-practice/task/barrett-reduction/) (12), [Restaurant Reopening](https://csacademy.com/ieeextreme-practice/task/restaurant-reopening/) (14), [Arrays Count](https://csacademy.com/ieeextreme-practice/task/arrays-count/) (15), [Array](https://csacademy.com/ieeextreme-practice/task/array/) (16), [IEEE754 Emulator](https://csacademy.com/ieeextreme-practice/task/ieee754-emulator/) (18), [Easy Sum](https://csacademy.com/ieeextreme-practice/task/easy-sum/) (19), [Do you know Expectation?](https://csacademy.com/ieeextreme-practice/task/do-you-know-expectation/) (19), [Domino Path](https://csacademy.com/ieeextreme-practice/task/domino-path/) (19)

## Конструктивні задачі

*побудувати будь-який об’єкт, що задовольняє правила; спершу розібрати малі випадки.* Бібліотека: -.

| Вип. | Задача | Скл. | Розв’язали | Ключові навички | Також | Бібл. | Джер. |
|---|---|---|---|---|---|---|---|
| 19 | [EDPS](https://csacademy.com/ieeextreme-practice/task/edps/) |  | 6/7 | дужкова послідовність із заданими внутрішніми довжинами (жадібний алгоритм, стек) | Рядки | linear.h | умова |
| 19 | [Hack the coach!](https://csacademy.com/ieeextreme-practice/task/hack-the-coach/) |  | 2947/4301 | побудувати контртест для хибної перевірки кореня через LCA | Дерева | tree.h | умова |
| 14 | [Making a Tangram](https://csacademy.com/ieeextreme-practice/task/making-tangram/) | середня | 158/475 | конструктивне розбиття сітки |  |  | теги |
| 11 | [Maximum Sum](https://csacademy.com/ieeextreme-practice/task/04dfa70efd936271ae191cb1a97eb876/) | складна | 136/809 | розставити числа так, щоб максимізувати суму добутків сусідів (сортування, розміщення від середини) | Жадібні | sort.h | теги |
| 13 | [Puzzle of Rooks](https://csacademy.com/ieeextreme-practice/task/puzzle-of-rooks/) |  | 25/341 | перемістити тури до цілей без взаємних атак у межах бюджету операцій |  |  | умова |
| 18 | [Doubled Sequence](https://csacademy.com/ieeextreme-practice/task/doubled-sequence/) | середня | 41/2574 | побудова послідовності типу Сколема/Ленгфорда |  |  | теги |
| 13 | [Yin Yang](https://csacademy.com/ieeextreme-practice/task/yin-yang/) | найскладніша | 16/1588 | побудова збалансованого рядка | Рядки |  | теги |

Тема «Конструктивні задачі» потрібна також у задачах: [The Lonely Shepherd](https://csacademy.com/ieeextreme-practice/task/lonely-shepherd/) (13), [Magical Stones II](https://csacademy.com/ieeextreme-practice/task/magical-stones-2/) (14), [Big Matrix Small Determinant](https://csacademy.com/ieeextreme-practice/task/big-matrix-small-determinant/) (15), [Pipeline](https://csacademy.com/ieeextreme-practice/task/pipeline/) (16), [Icarus](https://csacademy.com/ieeextreme-practice/task/icarus/) (18), [Shailesh's Triplet](https://csacademy.com/ieeextreme-practice/task/shailesh-s-triplet/) (19)

