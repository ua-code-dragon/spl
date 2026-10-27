/* io.h - fast input. Reading 10^6 numbers with scanf is slow; this is ~10x faster.
 *
 *   int n = read_int();  ll x = read_ll();  char w[100]; read_word(w);
 *
 * Do NOT mix with scanf/getchar on the same input (the buffer is private).
 * Do NOT use for interactive problems (fread waits for a full buffer): there
 * use scanf and fflush(stdout), see interactive.h.
 */
#ifndef XT_IO_H
#define XT_IO_H
#include "common.h"

static char io_buf[1 << 16];
static size_t io_pos, io_len;

/* next byte of stdin or EOF */
static inline int io_getc(void) {
    if (io_pos == io_len) {
        io_len = fread(io_buf, 1, sizeof io_buf, stdin);
        io_pos = 0;
        if (io_len == 0) return EOF;
    }
    return (unsigned char)io_buf[io_pos++];
}

/* next (possibly negative) integer; 0 at end of input */
static inline ll read_ll(void) {
    int c = io_getc(), neg = 0;
    ll x = 0;
    while (c != EOF && c != '-' && (c < '0' || c > '9')) c = io_getc();
    if (c == '-') { neg = 1; c = io_getc(); }
    for (; c >= '0' && c <= '9'; c = io_getc()) x = x * 10 + (c - '0');
    if (c != EOF) io_pos--;                      /* leave the delimiter unread */
    return neg ? -x : x;
}

static inline int read_int(void) { return (int)read_ll(); }

/* next whitespace-delimited word into s; returns its length, 0 at end of input */
static inline int read_word(char *s) {
    int c = io_getc(), len = 0;
    while (c != EOF && c <= ' ') c = io_getc();
    for (; c != EOF && c > ' '; c = io_getc()) s[len++] = (char)c;
    if (c != EOF) io_pos--;
    s[len] = 0;
    return len;
}

/* rest of the current line without '\n' / '\r'; returns its length, -1 at end of input.
 * Right after read_int() it returns the (empty) remainder of that line. */
static inline int read_line(char *s) {
    int c = io_getc(), len = 0;
    if (c == EOF) return -1;
    for (; c != EOF && c != '\n'; c = io_getc())
        if (c != '\r') s[len++] = (char)c;
    s[len] = 0;
    return len;
}

#endif
