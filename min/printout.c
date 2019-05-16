#define EXTERN extern
#include "pdftexd.h"

/* comment:Basic printing procedures */  
void println(void) {
    println_regmem switch (selector) {
    case TERMANDLOG: {
        putc('\n', stdout);
        putc('\n', logfile);
        termoffset = 0;
        fileoffset = 0;
    } break;
    case LOGONLY: {
        putc('\n', logfile);
        fileoffset = 0;
    } break;
    case TERMONLY: {
        putc('\n', stdout);
        termoffset = 0;
    } break;
    case NOPRINT:
    case PSEUDO:
    case NEWSTRING:;
        break;
    default:
        putc('\n', writefile[selector]);
        break;
    }
}


void zprintchar(ASCIIcode s) {
    printchar_regmem if (
        /* comment:Character |s| is the current new-line character */ s ==
        eqtb[INTBASE + NEWLINECHARCODE].cint) {

        if (selector < PSEUDO) {
            println();
            return;
        }
    }
    switch (selector) {
    case TERMANDLOG: {
        putc(Xchr(s), stdout);
        putc(Xchr(s), logfile);
        incr(termoffset);
        incr(fileoffset);
        if (termoffset == maxprintline) {
            putc('\n', stdout);
            termoffset = 0;
        }
        if (fileoffset == maxprintline) {
            putc('\n', logfile);
            fileoffset = 0;
        }
    } break;
    case LOGONLY: {
        putc(Xchr(s), logfile);
        incr(fileoffset);
        if (fileoffset == maxprintline)
            println();
    } break;
    case TERMONLY: {
        putc(Xchr(s), stdout);
        incr(termoffset);
        if (termoffset == maxprintline)
            println();
    } break;
    case NOPRINT:;
        break;
    case PSEUDO:
        if (tally < trickcount)
            trickbuf[tally % errorline] = s;
        break;
    case NEWSTRING: {
        if (poolptr < poolsize) {
            strpool[poolptr] = s;
            incr(poolptr);
        }
    } break;
    default:
        putc(Xchr(s), writefile[selector]);
        break;
    }
    incr(tally);
}


void zprint(integer s) {
    print_regmem poolpointer j;
    integer nl;
    if (s >= strptr)
        s = /* str '???' */ 261;
    else if (s < 256) {

        if (s < 0)
            s = /* str '???' */ 261;
        else {

            if ((selector > PSEUDO) && (!specialprinting) &&
                (!messageprinting)) {
                printchar(s);
                return;
            }
            if ((/* comment:Character |s| is the current new-line character */
                 s == eqtb[INTBASE + NEWLINECHARCODE].cint)) {

                if (selector < PSEUDO) {
                    println();
                    noconvert = false;
                    return;
                } else if (messageprinting) {
                    printchar(s);
                    noconvert = false;
                    return;
                }
            }
            if ((eqtb[INTBASE + MUBYTELOGCODE].cint > 0) && (!noconvert) &&
                (mubytewrite[s] > 0))
                s = mubytewrite[s];
            else if (xprn[s] || specialprinting) {
                printchar(s);
                noconvert = false;
                return;
            }
            noconvert = false;
            nl = eqtb[INTBASE + NEWLINECHARCODE].cint;
            eqtb[INTBASE + NEWLINECHARCODE].cint = -1;
            j = strstart[s];
            while (j < strstart[s + 1]) {

                printchar(strpool[j]);
                incr(j);
            }
            eqtb[INTBASE + NEWLINECHARCODE].cint = nl;
            return;
        }
    }
    j = strstart[s];
    while (j < strstart[s + 1]) {

        printchar(strpool[j]);
        incr(j);
    }
}


void zslowprint(integer s) {
    slowprint_regmem poolpointer j;
    if ((s >= strptr) || (s < 256))
        print(s);
    else {

        j = strstart[s];
        while (j < strstart[s + 1]) {

            print(strpool[j]);
            incr(j);
        }
    }
}


void zprintnl(strnumber s) {
    printnl_regmem if (((termoffset > 0) && (odd(selector))) ||
                       ((fileoffset > 0) && (selector >= LOGONLY))) println();
    print(s);
}


void zprintesc(strnumber s) {
    printesc_regmem integer c;
    /* comment:Set variable |c| to the current escape character */ c =
        eqtb[INTBASE + ESCAPECHARCODE].cint;
    if (c >= 0) {

        if (c < 256)
            print(c);
    }
    slowprint(s);
}


void zprintthedigs(eightbits k) {
    printthedigs_regmem while (k > 0) {

        decr(k);
        if (dig[k] < 10)
            printchar(/* str '0' */ 48 + dig[k]);
        else
            printchar(/* str 'A' */ 55 + dig[k]);
    }
}

void zprintint(longinteger n) {
    printint_regmem unsigned char k;
    longinteger m;
    k = 0;
    if (n < 0) {
        printchar(/* str '-' */ 45);
        if (n > -100000000L)
            n = -(integer)n;
        else {

            m = -1 - n;
            n = m / 10;
            m = (m % 10) + 1;
            k = 1;
            if (m < 10)
                dig[0] = m;
            else {

                dig[0] = 0;
                incr(n);
            }
        }
    }
    do {
        dig[k] = n % 10;
        n = n / 10;
        incr(k);
    } while (!(n == 0));
    printthedigs(k);
}

void zprintcs(integer p) {
    printcs_regmem halfword q;
    strnumber s;
    if (activenoconvert && (!noconvert) && (eqtb[p].hh.b0 == LET) &&
        (eqtb[p].hh.v.RH == /* @d1114@ */ 11)) {
        noconvert = true;
        return;
    }
    s = 0;
    if (csconverting && (!noconvert)) {
        q = mubytecswrite[p % 128];
        while (q != TEXNULL)
            if (mem[q].hh.v.LH == p) {
                s = mem[mem[q].hh.v.RH].hh.v.LH;
                q = TEXNULL;
            } else
                q = mem[mem[q].hh.v.RH].hh.v.RH;
    }
    noconvert = false;
    if (s > 0)
        print(s);
    else if (p < HASHBASE) {

        if (p >= SINGLEBASE) {

            if (p == NULLCS) {
                printesc(/* str 'csname' */ 580);
                printesc(/* str 'endcsname' */ 581);
                printchar(/* str ' ' */ 32);
            } else {

                printesc(p - SINGLEBASE);
                if (eqtb[CATCODEBASE + p - SINGLEBASE].hh.v.RH == LETTER)
                    printchar(/* str ' ' */ 32);
            }
        } else if (p < ACTIVEBASE)
            printesc(/* str 'IMPOSSIBLE.' */ 582);
        else
            print(p - ACTIVEBASE);
    } else if (((p >= UNDEFINEDCONTROLSEQUENCE) && (p <= EQTBSIZE)) ||
               (p > eqtbtop))
        printesc(/* str 'IMPOSSIBLE.' */ 582);
    else if ((hash[p].v.RH >= strptr))
        printesc(/* str 'NONEXISTENT.' */ 583);
    else {

        if ((p >= PRIMEQTBBASE) && (p < FROZENNULLFONT))
            printesc(prim[p - PRIMEQTBBASE].v.RH - 1);
        else
            printesc(hash[p].v.RH);
        printchar(/* str ' ' */ 32);
    }
}

void zsprintcs(halfword p) {
    sprintcs_regmem if (p < HASHBASE) {

        if (p < SINGLEBASE)
            print(p - ACTIVEBASE);
        else if (p < NULLCS)
            printesc(p - SINGLEBASE);
        else {

            printesc(/* str 'csname' */ 580);
            printesc(/* str 'endcsname' */ 581);
        }
    }
    else if ((p >= PRIMEQTBBASE) && (p < FROZENNULLFONT))
        printesc(prim[p - PRIMEQTBBASE].v.RH - 1);
    else printesc(hash[p].v.RH);
}

void zprintfilename(integer n, integer a, integer e) {
    printfilename_regmem boolean mustquote;
    poolpointer j;
    mustquote = false;
    if (a != 0) {
        j = strstart[a];
        while ((!mustquote) && (j < strstart[a + 1])) {

            mustquote = strpool[j] == /* str ' ' */ 32;
            incr(j);
        }
    }
    if (n != 0) {
        j = strstart[n];
        while ((!mustquote) && (j < strstart[n + 1])) {

            mustquote = strpool[j] == /* str ' ' */ 32;
            incr(j);
        }
    }
    if (e != 0) {
        j = strstart[e];
        while ((!mustquote) && (j < strstart[e + 1])) {

            mustquote = strpool[j] == /* str ' ' */ 32;
            incr(j);
        }
    }
    if (mustquote)
        printchar(/* str '""' */ 34);
    if (a != 0) {
        register integer for_end;
        j = strstart[a];
        for_end = strstart[a + 1] - 1;
        if (j <= for_end)
            do
                if (strpool[j] != /* str '""' */ 34)
                    print(strpool[j]);
            while (j++ < for_end);
    }
    if (n != 0) {
        register integer for_end;
        j = strstart[n];
        for_end = strstart[n + 1] - 1;
        if (j <= for_end)
            do
                if (strpool[j] != /* str '""' */ 34)
                    print(strpool[j]);
            while (j++ < for_end);
    }
    if (e != 0) {
        register integer for_end;
        j = strstart[e];
        for_end = strstart[e + 1] - 1;
        if (j <= for_end)
            do
                if (strpool[j] != /* str '""' */ 34)
                    print(strpool[j]);
            while (j++ < for_end);
    }
    if (mustquote)
        printchar(/* str '""' */ 34);
}

void zprintsize(integer s) {
    printsize_regmem if (s == TEXTSIZE) printesc(/* str 'textfont' */ 432);
    else if (s == SCRIPTSIZE) printesc(/* str 'scriptfont' */ 433);
    else printesc(/* str 'scriptscriptfont' */ 434);
}

void zprintwritewhatsit(strnumber s, halfword p) {
    printwritewhatsit_regmem printesc(s);
    if (mem[p + 1].hh.b0 < 16)
        printint(mem[p + 1].hh.b0);
    else if (mem[p + 1].hh.b0 == 16)
        printchar(/* str '' */ 42);
    else
        printchar(/* str '-' */ 45);
    if ((s == /* str 'write' */ 678) && (mem[p + 1].hh.b1 != 64)) {
        printchar(/* str '<' */ 60);
        printint(mem[p + 1].hh.b1 - 64);
        printchar(/* str '>' */ 62);
    }
}

void zprintsanum(halfword q) {
    printsanum_regmem halfword n;
    if (mem[q].hh.b0 < DIMENVALLIMIT)
        n = mem[q + 1].hh.v.RH;
    else {

        n = mem[q].hh.b0 % 16;
        q = mem[q].hh.v.RH;
        n = n + 16 * mem[q].hh.b0;
        q = mem[q].hh.v.RH;
        n = n + 256 * (mem[q].hh.b0 + 16 * mem[mem[q].hh.v.RH].hh.b0);
    }
    printint(n);
}

void zprintcsnames(integer hstart, integer hfinish) {
    printcsnames_regmem integer c, h;
    fprintf(stderr, "%s%ld%s%ld%c\n", "fmtdebug:csnames from ", (long)hstart,
            " to ", (long)hfinish, ':');
    {
        register integer for_end;
        h = hstart;
        for_end = hfinish;
        if (h <= for_end)
            do {
                if (hash[h].v.RH > 0) {
                    {
                        register integer for_end;
                        c = strstart[hash[h].v.RH];
                        for_end = strstart[hash[h].v.RH + 1] - 1;
                        if (c <= for_end)
                            do {
                                putbyte(strpool[c], stderr);
                            } while (c++ < for_end);
                    }
                    {
                        putc('|', stderr);
                        putc('\n', stderr);
                    }
                }
            } while (h++ < for_end);
    }
}

void printfileline(void) {
    printfileline_regmem integer level;
    level = inopen;
    while ((level > 0) && (fullsourcefilenamestack[level] == 0))
        decr(level);
    if (level == 0)
        printnl(/* str '! ' */ 264);
    else {

        printnl(/* str '' */ 345);
        print(fullsourcefilenamestack[level]);
        print(/* str '' */ 58);
        if (level == inopen)
            printint(line);
        else
            printint(linestack[level + 1]);
        print(/* str '' */ 651);
    }
}


ASCIIcode zzreadbuffer(integer *i) {
    register ASCIIcode Result;
    readbuffer_regmem halfword p;
    integer lastfound;
    integer lasttype;
    mubyteskip = 0;
    mubytetoken = 0;
    Result = buffer[*i];
    if (eqtb[INTBASE + MUBYTEINCODE].cint == 0) {
        if (mubytekeep > 0)
            mubytekeep = 0;
        return Result;
    }
    lastfound = -2;
    if ((*i == curinput.startfield) && (!mubytestart)) {
        mubytekeep = 0;
        if ((eqtb[INTBASE + ENDLINECHARCODE].cint >= 0) &&
            (eqtb[INTBASE + ENDLINECHARCODE].cint < 256)) {

            if (mubyteread[eqtb[INTBASE + ENDLINECHARCODE].cint] != TEXNULL) {
                mubytestart = true;
                mubyteskip = -1;
                p = mubyteread[eqtb[INTBASE + ENDLINECHARCODE].cint];
                goto labreadbuffer22continue;
            }
        }
    }
labreadbuffer20restart:
    mubytestart = false;
    if ((mubyteread[buffer[*i]] == TEXNULL) || (mubytekeep > 0)) {
        if (mubytekeep > 0)
            decr(mubytekeep);
        return Result;
    }
    p = mubyteread[buffer[*i]];
labreadbuffer22continue:
    if (mem[p].hh.b0 >= 64) {
        lasttype = mem[p].hh.b0 - 64;
        p = mem[p].hh.v.RH;
        mubytetoken = mem[p].hh.v.LH;
        lastfound = mubyteskip;
    } else if (mem[p].hh.b0 > 0) {
        lasttype = mem[p].hh.b0;
        mubytetoken = mem[p].hh.v.RH;
        goto labreadbuffer40found;
    }
    incr(mubyteskip);
    if (*i + mubyteskip > curinput.limitfield) {
        mubyteskip = 0;
        if (mubytestart)
            goto labreadbuffer20restart;
        return Result;
    }
    do {
        p = mem[p].hh.v.RH;
        if (mem[mem[p].hh.v.LH].hh.b1 == buffer[*i + mubyteskip]) {
            p = mem[p].hh.v.LH;
            goto labreadbuffer22continue;
        }
    } while (!(mem[p].hh.v.RH == TEXNULL));
    mubyteskip = 0;
    if (mubytestart)
        goto labreadbuffer20restart;
    if (lastfound == -2)
        return Result;
    mubyteskip = lastfound;
labreadbuffer40found:
    if (mubytetoken < 256) {
        Result = mubytetoken;
        mubytetoken = 0;
        *i = *i + mubyteskip;
        if (mubytestart && (*i >= curinput.startfield))
            mubytestart = false;
        return Result;
    } else {

        Result = 0;
        if (lasttype == 60)
            *i = *i + mubyteskip;
        else {

            decr(*i);
            mubytekeep = lasttype;
            if (*i < curinput.startfield)
                mubytestart = true;
            if (lasttype == 52)
                mubytekeep = 10000;
            if (lasttype == 51)
                mubytekeep = mubyteskip + 1;
            mubyteskip = -1;
        }
        if (mubytestart && (*i >= curinput.startfield))
            mubytestart = false;
        return Result;
    }
    return Result;
}
void zzprintbuffer(integer *i) {
    printbuffer_regmem ASCIIcode c;
    if (eqtb[INTBASE + MUBYTEINCODE].cint == 0)
        print(buffer[*i]);
    else if (eqtb[INTBASE + MUBYTELOGCODE].cint > 0)
        printchar(buffer[*i]);
    else {

        c = readbuffer(*i);
        if (mubytetoken > 0)
            printcs(mubytetoken - 4095);
        else
            print(c);
    }
    incr(*i);
}



void zprinttwo(integer n) {
    printtwo_regmem n = abs(n) % 100;
    printchar(/* str '0' */ 48 + (n / 10));
    printchar(/* str '0' */ 48 + (n % 10));
}
void zprinthex(integer n) {
    printhex_regmem unsigned char k;
    k = 0;
    printchar(/* str '""' */ 34);
    do {
        dig[k] = n % 16;
        n = n / 16;
        incr(k);
    } while (!(n == 0));
    printthedigs(k);
}
void zprintromanint(integer n) {
    printromanint_regmem poolpointer j, k;
    nonnegativeinteger u, v;
    j = strstart[/* str 'm2d5c2l5x2v5i' */ 262];
    v = 1000;
    while (true) {

        while (n >= v) {

            printchar(strpool[j]);
            n = n - v;
        }
        if (n <= 0)
            return;
        k = j + 2;
        u = v / (strpool[k - 1] /* str '0' */ - 48);
        if (strpool[k - 1] == /* str '2' */ 50) {
            k = k + 2;
            u = u / (strpool[k - 1] /* str '0' */ - 48);
        }
        if (n + u >= v) {
            printchar(strpool[k]);
            n = n + u;
        } else {

            j = j + 2;
            v = v / (strpool[j - 1] /* str '0' */ - 48);
        }
    }
}
void printcurrentstring(void) {
    printcurrentstring_regmem poolpointer j;
    j = strstart[strptr];
    while (j < poolptr) {

        printchar(strpool[j]);
        incr(j);
    }
}

void zprintscaled(scaled s) {
    printscaled_regmem scaled delta;
    if (s < 0) {
        printchar(/* str '-' */ 45);
        s = -(integer)s;
    }
    printint(s / 65536L);
    printchar(/* str '.' */ 46);
    s = 10 * (s % 65536L) + 5;
    delta = 10;
    do {
        if (delta > 65536L)
            s = s - 17232;
        printchar(/* str '0' */ 48 + (s / 65536L));
        s = 10 * (s % 65536L);
        delta = delta * 10;
    } while (!(s <= delta));
}


#ifdef TEXMF_DEBUG
void zprintword(memoryword w) {
    printword_regmem printint(w.cint);
    printchar(/* str ' ' */ 32);
    printscaled(w.cint);
    printchar(/* str ' ' */ 32);
    printscaled(round(65536L * w.gr));
    println();
    printint(w.hh.v.LH);
    printchar(/* str '=' */ 61);
    printint(w.hh.b0);
    printchar(/* str '' */ 58);
    printint(w.hh.b1);
    printchar(/* str ';' */ 59);
    printint(w.hh.v.RH);
    printchar(/* str ' ' */ 32);
    printint(w.qqqq.b0);
    printchar(/* str '' */ 58);
    printint(w.qqqq.b1);
    printchar(/* str '' */ 58);
    printint(w.qqqq.b2);
    printchar(/* str '' */ 58);
    printint(w.qqqq.b3);
}
#endif /* TEXMF_DEBUG */