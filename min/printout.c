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


void zshortdisplay(integer p) {
    shortdisplay_regmem integer n;
    while (p > memmin) {

        if ((p >= himemmin)) {
            if (p <= memend) {
                if (mem[p].hh.b0 != fontinshortdisplay) {
                    if ((mem[p].hh.b0 > fontmax))
                        printchar(/* str '' */ 42);
                    else
                        printfontidentifier(mem[p].hh.b0);
                    printchar(/* str ' ' */ 32);
                    fontinshortdisplay = mem[p].hh.b0;
                }
                print(mem[p].hh.b1);
            }
        } else /* comment:Print a short indication of the contents of node | */
            switch (mem[p].hh.b0) {
            case HLISTNODE:
            case VLISTNODE:
            case INSNODE:
            case WHATSITNODE:
            case MARKNODE:
            case ADJUSTNODE:
            case UNSETNODE:
                print(/* str '[]' */ 313);
                break;
            case RULENODE:
                printchar(/* str '|' */ 124);
                break;
            case GLUENODE:
                if (mem[p + 1].hh.v.LH != membot)
                    printchar(/* str ' ' */ 32);
                break;
            case MATHNODE:
                if (mem[p].hh.b1 >= LCODE)
                    print(/* str '[]' */ 313);
                else
                    printchar(/* str '$' */ 36);
                break;
            case LIGATURENODE:
                shortdisplay(mem[p + 1].hh.v.RH);
                break;
            case DISCNODE: {
                shortdisplay(mem[p + 1].hh.v.LH);
                shortdisplay(mem[p + 1].hh.v.RH);
                n = mem[p].hh.b1;
                while (n > 0) {

                    if (mem[p].hh.v.RH != TEXNULL)
                        p = mem[p].hh.v.RH;
                    decr(n);
                }
            } break;
            default:;
                break;
            }
        p = mem[p].hh.v.RH;
    }
}
void zprintfontandchar(integer p) {
    printfontandchar_regmem if (p > memend)
        printesc(/* str 'CLOBBERED.' */ 314);
    else {

        if ((mem[p].hh.b0 > fontmax))
            printchar(/* str '' */ 42);
        else
            printfontidentifier(mem[p].hh.b0);
        printchar(/* str ' ' */ 32);
        print(mem[p].hh.b1);
    }
}
void zprintmark(integer p) {
    printmark_regmem printchar(/* str '{' */ 123);
    if ((p < himemmin) || (p > memend))
        printesc(/* str 'CLOBBERED.' */ 314);
    else
        showtokenlist(mem[p].hh.v.RH, TEXNULL, maxprintline - 10);
    printchar(/* str '}' */ 125);
}
void zprintruledimen(scaled d) {
    printruledimen_regmem if ((d == -1073741824L)) printchar(/* str '' */ 42);
    else printscaled(d);
}
void zprintglue(scaled d, integer order, strnumber s) {
    printglue_regmem printscaled(d);
    if ((order < NORMAL) || (order > FILLL))
        print(/* str 'foul' */ 315);
    else if (order > NORMAL) {
        print(/* str 'fil' */ 316);
        while (order > FIL) {

            printchar(/* str 'l' */ 108);
            decr(order);
        }
    } else if (s != 0)
        print(s);
}
void zprintspec(integer p, strnumber s) {
    printspec_regmem if ((p < memmin) || (p >= lomemmax))
        printchar(/* str '' */ 42);
    else {

        printscaled(mem[p + WIDTHOFFSET].cint);
        if (s != 0)
            print(s);
        if (mem[p + 2].cint != 0) {
            print(/* str ' plus ' */ 317);
            printglue(mem[p + 2].cint, mem[p].hh.b0, s);
        }
        if (mem[p + 3].cint != 0) {
            print(/* str ' minus ' */ 318);
            printglue(mem[p + 3].cint, mem[p].hh.b1, s);
        }
    }
}
/* comment:Declare procedures needed for displaying the eleme */ void
zprintfamandchar(halfword p) {
    printfamandchar_regmem printesc(/* str 'fam' */ 484);
    printint(mem[p].hh.b0);
    printchar(/* str ' ' */ 32);
    print(mem[p].hh.b1);
}
void zprintdelimiter(halfword p) {
    printdelimiter_regmem integer a;
    a = mem[p].qqqq.b0 * 256 + mem[p].qqqq.b1;
    a = a * 4096 + mem[p].qqqq.b2 * 256 + mem[p].qqqq.b3;
    if (a < 0)
        printint(a);
    else
        printhex(a);
}
void zprintsubsidiarydata(halfword p, ASCIIcode c) {
    printsubsidiarydata_regmem if ((poolptr - strstart[strptr]) >=
                                   depththreshold) {
        if (mem[p].hh.v.RH != EMPTY)
            print(/* str ' []' */ 319);
    }
    else {

        {
            strpool[poolptr] = c;
            incr(poolptr);
        }
        tempptr = p;
        switch (mem[p].hh.v.RH) {
        case MATHCHAR: {
            println();
            printcurrentstring();
            printfamandchar(p);
        } break;
        case SUBBOX:
            showinfo();
            break;
        case SUBMLIST:
            if (mem[p].hh.v.LH == TEXNULL) {
                println();
                printcurrentstring();
                print(/* str '{}' */ 1269);
            } else
                showinfo();
            break;
        default:;
            break;
        }
        decr(poolptr);
    }
}
void zprintstyle(integer c) {
    printstyle_regmem switch (c / 2) {
    case 0:
        printesc(/* str 'displaystyle' */ 1270);
        break;
    case 1:
        printesc(/* str 'textstyle' */ 1271);
        break;
    case 2:
        printesc(/* str 'scriptstyle' */ 1272);
        break;
    case 3:
        printesc(/* str 'scriptscriptstyle' */ 1273);
        break;
    default:
        print(/* str 'Unknown style!' */ 1274);
        break;
    }
}
/* comment:Declare the procedure called |print_skip_param| */ void
zprintskipparam(integer n) {
    printskipparam_regmem switch (n) {
    case LINESKIPCODE:
        printesc(/* str 'lineskip' */ 393);
        break;
    case BASELINESKIPCODE:
        printesc(/* str 'baselineskip' */ 394);
        break;
    case PARSKIPCODE:
        printesc(/* str 'parskip' */ 395);
        break;
    case ABOVEDISPLAYSKIPCODE:
        printesc(/* str 'abovedisplayskip' */ 396);
        break;
    case BELOWDISPLAYSKIPCODE:
        printesc(/* str 'belowdisplayskip' */ 397);
        break;
    case ABOVEDISPLAYSHORTSKIPCODE:
        printesc(/* str 'abovedisplayshortskip' */ 398);
        break;
    case BELOWDISPLAYSHORTSKIPCODE:
        printesc(/* str 'belowdisplayshortskip' */ 399);
        break;
    case LEFTSKIPCODE:
        printesc(/* str 'leftskip' */ 400);
        break;
    case RIGHTSKIPCODE:
        printesc(/* str 'rightskip' */ 401);
        break;
    case TOPSKIPCODE:
        printesc(/* str 'topskip' */ 402);
        break;
    case SPLITTOPSKIPCODE:
        printesc(/* str 'splittopskip' */ 403);
        break;
    case TABSKIPCODE:
        printesc(/* str 'tabskip' */ 404);
        break;
    case SPACESKIPCODE:
        printesc(/* str 'spaceskip' */ 405);
        break;
    case XSPACESKIPCODE:
        printesc(/* str 'xspaceskip' */ 406);
        break;
    case PARFILLSKIPCODE:
        printesc(/* str 'parfillskip' */ 407);
        break;
    case THINMUSKIPCODE:
        printesc(/* str 'thinmuskip' */ 408);
        break;
    case MEDMUSKIPCODE:
        printesc(/* str 'medmuskip' */ 409);
        break;
    case THICKMUSKIPCODE:
        printesc(/* str 'thickmuskip' */ 410);
        break;
    default:
        print(/* str '[unknown glue parameter!]' */ 411);
        break;
    }
}


void zprintmode(integer m) {
    printmode_regmem if (m > 0) switch (m / (/* @d2321@ */ 103)) {
    case 0:
        print(/* str 'vertical mode' */ 364);
        break;
    case 1:
        print(/* str 'horizontal mode' */ 365);
        break;
    case 2:
        print(/* str 'display math mode' */ 366);
        break;
    }
    else if (m == 0) print(/* str 'no mode' */ 367);
    else switch ((-(integer)m) / (/* @d2326@ */ 103)) {
    case 0:
        print(/* str 'internal vertical mode' */ 368);
        break;
    case 1:
        print(/* str 'restricted horizontal mode' */ 369);
        break;
    case 2:
        print(/* str 'math mode' */ 370);
        break;
    }
}
void zprintinmode(integer m) {
    printinmode_regmem if (m > 0) switch (m / (/* @d2330@ */ 103)) {
    case 0:
        print(/* str '' in vertical mode' */ 371);
        break;
    case 1:
        print(/* str '' in horizontal mode' */ 372);
        break;
    case 2:
        print(/* str '' in display math mode' */ 373);
        break;
    }
    else if (m == 0) print(/* str '' in no mode' */ 374);
    else switch ((-(integer)m) / (/* @d2335@ */ 103)) {
    case 0:
        print(/* str '' in internal vertical mode' */ 375);
        break;
    case 1:
        print(/* str '' in restricted horizontal mode' */ 376);
        break;
    case 2:
        print(/* str '' in math mode' */ 377);
        break;
    }
}


void showactivities(void) {
    showactivities_regmem integer p;
    /* @d2340@ */ /* @d2341@ */ short m;
    memoryword a;
    halfword q, r;
    integer t;
    nest[nestptr] = curlist;
    printnl(/* str '' */ 345);
    println();
    {
        register integer for_end;
        p = nestptr;
        for_end = 0;
        if (p >= for_end)
            do {
                m = nest[p].modefield;
                a = nest[p].auxfield;
                printnl(/* str '### ' */ 379);
                printmode(m);
                print(/* str ' entered at line ' */ 380);
                printint(abs(nest[p].mlfield));
                if (m == HMODE) {

                    if (nest[p].pgfield != 8585216L) {
                        print(/* str ' (language' */ 381);
                        printint(nest[p].pgfield % 65536L);
                        print(/* str '' */ 382);
                        printint(nest[p].pgfield / 4194304L);
                        printchar(/* str ',' */ 44);
                        printint((nest[p].pgfield / 65536L) % 64);
                        printchar(/* str ')' */ 41);
                    }
                }
                if (nest[p].mlfield < 0)
                    print(/* str ' (\output routine)' */ 383);
                if (p == 0) {
                    /* comment:Show the status of the current page */
                    if (memtop - 2 != pagetail) {
                        printnl(/* str '### current page' */ 1396);
                        if (outputactive)
                            print(
                                /* str ' (held over for next output)' */ 1397);
                        showbox(mem[memtop - 2].hh.v.RH);
                        if (pagecontents > EMPTY) {
                            printnl(/* str 'total height ' */ 1398);
                            printtotals();
                            printnl(/* str ' goal height ' */ 1399);
                            printscaled(pagesofar[0]);
                            r = mem[memtop].hh.v.RH;
                            while (r != memtop) {

                                println();
                                printesc(/* str 'insert' */ 337);
                                t = mem[r].hh.b1;
                                printint(t);
                                print(/* str ' adds ' */ 1400);
                                if (eqtb[COUNTBASE + t].cint == 1000)
                                    t = mem[r + HEIGHTOFFSET].cint;
                                else
                                    t = xovern(mem[r + HEIGHTOFFSET].cint,
                                               1000) *
                                        eqtb[COUNTBASE + t].cint;
                                printscaled(t);
                                if (mem[r].hh.b0 == SPLITUP) {
                                    q = memtop - 2;
                                    t = 0;
                                    do {
                                        q = mem[q].hh.v.RH;
                                        if ((mem[q].hh.b0 == INSNODE) &&
                                            (mem[q].hh.b1 == mem[r].hh.b1))
                                            incr(t);
                                    } while (!(q == mem[r + 1].hh.v.LH));
                                    print(/* str ', #' */ 1401);
                                    printint(t);
                                    print(/* str ' might split' */ 1402);
                                }
                                r = mem[r].hh.v.RH;
                            }
                        }
                    }
                    if (mem[memtop - 1].hh.v.RH != TEXNULL)
                        printnl(/* str '### recent contributions' */ 384);
                }
                showbox(mem[nest[p].headfield].hh.v.RH);
                /* comment:Show the auxiliary field, |a| */ switch (
                    abs(m) / (/* @d2369@ */ 103)) {
                case 0: {
                    printnl(/* str 'prevdepth ' */ 385);
                    if (a.cint <= eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint)
                        print(/* str 'ignored' */ 386);
                    else
                        printscaled(a.cint);
                    if (nest[p].pgfield != 0) {
                        print(/* str ', prevgraf ' */ 387);
                        printint(nest[p].pgfield);
                        if (nest[p].pgfield != 1)
                            print(/* str ' lines' */ 388);
                        else
                            print(/* str ' line' */ 389);
                    }
                } break;
                case 1: {
                    printnl(/* str 'spacefactor ' */ 390);
                    printint(a.hh.v.LH);
                    if (m > 0) {

                        if (a.hh.v.RH > 0) {
                            print(/* str ', current language ' */ 391);
                            printint(a.hh.v.RH);
                        }
                    }
                } break;
                case 2:
                    if (a.cint != TEXNULL) {
                        print(/* str 'this will be denominator of' */ 392);
                        showbox(a.cint);
                    }
                    break;
                }
            } while (p-- > for_end);
    }
}
void zprintparam(integer n) {
    printparam_regmem switch (n) {
    case PRETOLERANCECODE:
        printesc(/* str 'pretolerance' */ 440);
        break;
    case TOLERANCECODE:
        printesc(/* str 'tolerance' */ 441);
        break;
    case LINEPENALTYCODE:
        printesc(/* str 'linepenalty' */ 442);
        break;
    case HYPHENPENALTYCODE:
        printesc(/* str 'hyphenpenalty' */ 443);
        break;
    case EXHYPHENPENALTYCODE:
        printesc(/* str 'exhyphenpenalty' */ 444);
        break;
    case CLUBPENALTYCODE:
        printesc(/* str 'clubpenalty' */ 445);
        break;
    case WIDOWPENALTYCODE:
        printesc(/* str 'widowpenalty' */ 446);
        break;
    case DISPLAYWIDOWPENALTYCODE:
        printesc(/* str 'displaywidowpenalty' */ 447);
        break;
    case BROKENPENALTYCODE:
        printesc(/* str 'brokenpenalty' */ 448);
        break;
    case BINOPPENALTYCODE:
        printesc(/* str 'binoppenalty' */ 449);
        break;
    case RELPENALTYCODE:
        printesc(/* str 'relpenalty' */ 450);
        break;
    case PREDISPLAYPENALTYCODE:
        printesc(/* str 'predisplaypenalty' */ 451);
        break;
    case POSTDISPLAYPENALTYCODE:
        printesc(/* str 'postdisplaypenalty' */ 452);
        break;
    case INTERLINEPENALTYCODE:
        printesc(/* str 'interlinepenalty' */ 453);
        break;
    case DOUBLEHYPHENDEMERITSCODE:
        printesc(/* str 'doublehyphendemerits' */ 454);
        break;
    case FINALHYPHENDEMERITSCODE:
        printesc(/* str 'finalhyphendemerits' */ 455);
        break;
    case ADJDEMERITSCODE:
        printesc(/* str 'adjdemerits' */ 456);
        break;
    case MAGCODE:
        printesc(/* str 'mag' */ 457);
        break;
    case DELIMITERFACTORCODE:
        printesc(/* str 'delimiterfactor' */ 458);
        break;
    case LOOSENESSCODE:
        printesc(/* str 'looseness' */ 459);
        break;
    case TIMECODE:
        printesc(/* str 'time' */ 460);
        break;
    case DAYCODE:
        printesc(/* str 'day' */ 461);
        break;
    case MONTHCODE:
        printesc(/* str 'month' */ 462);
        break;
    case YEARCODE:
        printesc(/* str 'year' */ 463);
        break;
    case SHOWBOXBREADTHCODE:
        printesc(/* str 'showboxbreadth' */ 464);
        break;
    case SHOWBOXDEPTHCODE:
        printesc(/* str 'showboxdepth' */ 465);
        break;
    case HBADNESSCODE:
        printesc(/* str 'hbadness' */ 466);
        break;
    case VBADNESSCODE:
        printesc(/* str 'vbadness' */ 467);
        break;
    case PAUSINGCODE:
        printesc(/* str 'pausing' */ 468);
        break;
    case TRACINGONLINECODE:
        printesc(/* str 'tracingonline' */ 469);
        break;
    case TRACINGMACROSCODE:
        printesc(/* str 'tracingmacros' */ 470);
        break;
    case TRACINGSTATSCODE:
        printesc(/* str 'tracingstats' */ 471);
        break;
    case TRACINGPARAGRAPHSCODE:
        printesc(/* str 'tracingparagraphs' */ 472);
        break;
    case TRACINGPAGESCODE:
        printesc(/* str 'tracingpages' */ 473);
        break;
    case TRACINGOUTPUTCODE:
        printesc(/* str 'tracingoutput' */ 474);
        break;
    case TRACINGLOSTCHARSCODE:
        printesc(/* str 'tracinglostchars' */ 475);
        break;
    case TRACINGCOMMANDSCODE:
        printesc(/* str 'tracingcommands' */ 476);
        break;
    case TRACINGRESTORESCODE:
        printesc(/* str 'tracingrestores' */ 477);
        break;
    case UCHYPHCODE:
        printesc(/* str 'uchyph' */ 478);
        break;
    case OUTPUTPENALTYCODE:
        printesc(/* str 'outputpenalty' */ 479);
        break;
    case MAXDEADCYCLESCODE:
        printesc(/* str 'maxdeadcycles' */ 480);
        break;
    case HANGAFTERCODE:
        printesc(/* str 'hangafter' */ 481);
        break;
    case FLOATINGPENALTYCODE:
        printesc(/* str 'floatingpenalty' */ 482);
        break;
    case GLOBALDEFSCODE:
        printesc(/* str 'globaldefs' */ 483);
        break;
    case CURFAMCODE:
        printesc(/* str 'fam' */ 484);
        break;
    case ESCAPECHARCODE:
        printesc(/* str 'escapechar' */ 485);
        break;
    case DEFAULTHYPHENCHARCODE:
        printesc(/* str 'defaulthyphenchar' */ 486);
        break;
    case DEFAULTSKEWCHARCODE:
        printesc(/* str 'defaultskewchar' */ 487);
        break;
    case ENDLINECHARCODE:
        printesc(/* str 'endlinechar' */ 488);
        break;
    case NEWLINECHARCODE:
        printesc(/* str 'newlinechar' */ 489);
        break;
    case LANGUAGECODE:
        printesc(/* str 'language' */ 490);
        break;
    case LEFTHYPHENMINCODE:
        printesc(/* str 'lefthyphenmin' */ 491);
        break;
    case RIGHTHYPHENMINCODE:
        printesc(/* str 'righthyphenmin' */ 492);
        break;
    case HOLDINGINSERTSCODE:
        printesc(/* str 'holdinginserts' */ 493);
        break;
    case ERRORCONTEXTLINESCODE:
        printesc(/* str 'errorcontextlines' */ 494);
        break;
    case CHARSUBDEFMINCODE:
        printesc(/* str 'charsubdefmin' */ 495);
        break;
    case CHARSUBDEFMAXCODE:
        printesc(/* str 'charsubdefmax' */ 496);
        break;
    case TRACINGCHARSUBDEFCODE:
        printesc(/* str 'tracingcharsubdef' */ 497);
        break;
    case MUBYTEINCODE:
        printesc(/* str 'mubytein' */ 498);
        break;
    case MUBYTEOUTCODE:
        printesc(/* str 'mubyteout' */ 499);
        break;
    case MUBYTELOGCODE:
        printesc(/* str 'mubytelog' */ 500);
        break;
    case SPECOUTCODE:
        printesc(/* str 'specialout' */ 501);
        break;
    case PDFOUTPUTCODE:
        printesc(/* str 'pdfoutput' */ 502);
        break;
    case PDFCOMPRESSLEVELCODE:
        printesc(/* str 'pdfcompresslevel' */ 503);
        break;
    case PDFOBJCOMPRESSLEVELCODE:
        printesc(/* str 'pdfobjcompresslevel' */ 504);
        break;
    case PDFDECIMALDIGITSCODE:
        printesc(/* str 'pdfdecimaldigits' */ 505);
        break;
    case PDFMOVECHARSCODE:
        printesc(/* str 'pdfmovechars' */ 506);
        break;
    case PDFIMAGERESOLUTIONCODE:
        printesc(/* str 'pdfimageresolution' */ 507);
        break;
    case PDFPKRESOLUTIONCODE:
        printesc(/* str 'pdfpkresolution' */ 508);
        break;
    case PDFUNIQUERESNAMECODE:
        printesc(/* str 'pdfuniqueresname' */ 509);
        break;
    case PDFOPTIONALWAYSUSEPDFPAGEBOXCODE:
        printesc(/* str 'pdfoptionalwaysusepdfpagebox' */ 510);
        break;
    case PDFOPTIONPDFINCLUSIONERRORLEVELCODE:
        printesc(/* str 'pdfoptionpdfinclusionerrorlevel' */ 511);
        break;
    case PDFMINORVERSIONCODE:
        printesc(/* str 'pdfminorversion' */ 512);
        break;
    case PDFFORCEPAGEBOXCODE:
        printesc(/* str 'pdfforcepagebox' */ 513);
        break;
    case PDFPAGEBOXCODE:
        printesc(/* str 'pdfpagebox' */ 514);
        break;
    case PDFINCLUSIONERRORLEVELCODE:
        printesc(/* str 'pdfinclusionerrorlevel' */ 515);
        break;
    case PDFGAMMACODE:
        printesc(/* str 'pdfgamma' */ 516);
        break;
    case PDFIMAGEGAMMACODE:
        printesc(/* str 'pdfimagegamma' */ 517);
        break;
    case PDFIMAGEHICOLORCODE:
        printesc(/* str 'pdfimagehicolor' */ 518);
        break;
    case PDFIMAGEAPPLYGAMMACODE:
        printesc(/* str 'pdfimageapplygamma' */ 519);
        break;
    case PDFADJUSTSPACINGCODE:
        printesc(/* str 'pdfadjustspacing' */ 520);
        break;
    case PDFPROTRUDECHARSCODE:
        printesc(/* str 'pdfprotrudechars' */ 521);
        break;
    case PDFTRACINGFONTSCODE:
        printesc(/* str 'pdftracingfonts' */ 522);
        break;
    case PDFADJUSTINTERWORDGLUECODE:
        printesc(/* str 'pdfadjustinterwordglue' */ 523);
        break;
    case PDFPREPENDKERNCODE:
        printesc(/* str 'pdfprependkern' */ 524);
        break;
    case PDFAPPENDKERNCODE:
        printesc(/* str 'pdfappendkern' */ 525);
        break;
    case PDFGENTOUNICODECODE:
        printesc(/* str 'pdfgentounicode' */ 526);
        break;
    case PDFDRAFTMODECODE:
        printesc(/* str 'pdfdraftmode' */ 527);
        break;
    case PDFINCLUSIONCOPYFONTCODE:
        printesc(/* str 'pdfinclusioncopyfonts' */ 528);
        break;
    case PDFSUPPRESSWARNINGDUPDESTCODE:
        printesc(/* str 'pdfsuppresswarningdupdest' */ 529);
        break;
    case PDFSUPPRESSWARNINGDUPMAPCODE:
        printesc(/* str 'pdfsuppresswarningdupmap' */ 530);
        break;
    case PDFSUPPRESSWARNINGPAGEGROUPCODE:
        printesc(/* str 'pdfsuppresswarningpagegroup' */ 531);
        break;
    case PDFINFOOMITDATECODE:
        printesc(/* str 'pdfinfoomitdate' */ 532);
        break;
    case PDFSUPPRESSPTEXINFOCODE:
        printesc(/* str 'pdfsuppressptexinfo' */ 533);
        break;
    case PDFOMITCHARSETCODE:
        printesc(/* str 'pdfomitcharset' */ 534);
        break;
    /* comment:Cases for |print_param| */ case TRACINGASSIGNSCODE:
        printesc(/* str 'tracingassigns' */ 1972);
        break;
    case TRACINGGROUPSCODE:
        printesc(/* str 'tracinggroups' */ 1973);
        break;
    case TRACINGIFSCODE:
        printesc(/* str 'tracingifs' */ 1974);
        break;
    case TRACINGSCANTOKENSCODE:
        printesc(/* str 'tracingscantokens' */ 1975);
        break;
    case TRACINGNESTINGCODE:
        printesc(/* str 'tracingnesting' */ 1976);
        break;
    case PREDISPLAYDIRECTIONCODE:
        printesc(/* str 'predisplaydirection' */ 1977);
        break;
    case LASTLINEFITCODE:
        printesc(/* str 'lastlinefit' */ 1978);
        break;
    case SAVINGVDISCARDSCODE:
        printesc(/* str 'savingvdiscards' */ 1979);
        break;
    case SAVINGHYPHCODESCODE:
        printesc(/* str 'savinghyphcodes' */ 1980);
        break;
    case ETEXSTATECODE + TEXXETCODE:
        printesc(/* str 'TeXXeTstate' */ 2020);
        break;
    default:
        print(/* str '[unknown integer parameter!]' */ 535);
        break;
    }
}
void begindiagnostic(void) {
    begindiagnostic_regmem oldsetting = selector;
    if ((eqtb[INTBASE + TRACINGONLINECODE].cint <= 0) &&
        (selector == TERMANDLOG)) {
        decr(selector);
        if (history == SPOTLESS)
            history = WARNINGISSUED;
    }
}
void zenddiagnostic(boolean blankline) {
    enddiagnostic_regmem printnl(/* str '' */ 345);
    if (blankline)
        println();
    selector = oldsetting;
}
void zprintlengthparam(integer n) {
    printlengthparam_regmem switch (n) {
    case PARINDENTCODE:
        printesc(/* str 'parindent' */ 539);
        break;
    case MATHSURROUNDCODE:
        printesc(/* str 'mathsurround' */ 540);
        break;
    case LINESKIPLIMITCODE:
        printesc(/* str 'lineskiplimit' */ 541);
        break;
    case HSIZECODE:
        printesc(/* str 'hsize' */ 542);
        break;
    case VSIZECODE:
        printesc(/* str 'vsize' */ 543);
        break;
    case MAXDEPTHCODE:
        printesc(/* str 'maxdepth' */ 544);
        break;
    case SPLITMAXDEPTHCODE:
        printesc(/* str 'splitmaxdepth' */ 545);
        break;
    case BOXMAXDEPTHCODE:
        printesc(/* str 'boxmaxdepth' */ 546);
        break;
    case HFUZZCODE:
        printesc(/* str 'hfuzz' */ 547);
        break;
    case VFUZZCODE:
        printesc(/* str 'vfuzz' */ 548);
        break;
    case DELIMITERSHORTFALLCODE:
        printesc(/* str 'delimitershortfall' */ 549);
        break;
    case NULLDELIMITERSPACECODE:
        printesc(/* str 'nulldelimiterspace' */ 550);
        break;
    case SCRIPTSPACECODE:
        printesc(/* str 'scriptspace' */ 551);
        break;
    case PREDISPLAYSIZECODE:
        printesc(/* str 'predisplaysize' */ 552);
        break;
    case DISPLAYWIDTHCODE:
        printesc(/* str 'displaywidth' */ 553);
        break;
    case DISPLAYINDENTCODE:
        printesc(/* str 'displayindent' */ 554);
        break;
    case OVERFULLRULECODE:
        printesc(/* str 'overfullrule' */ 555);
        break;
    case HANGINDENTCODE:
        printesc(/* str 'hangindent' */ 556);
        break;
    case HOFFSETCODE:
        printesc(/* str 'hoffset' */ 557);
        break;
    case VOFFSETCODE:
        printesc(/* str 'voffset' */ 558);
        break;
    case EMERGENCYSTRETCHCODE:
        printesc(/* str 'emergencystretch' */ 559);
        break;
    case PDFHORIGINCODE:
        printesc(/* str 'pdfhorigin' */ 560);
        break;
    case PDFVORIGINCODE:
        printesc(/* str 'pdfvorigin' */ 561);
        break;
    case PDFPAGEWIDTHCODE:
        printesc(/* str 'pdfpagewidth' */ 562);
        break;
    case PDFPAGEHEIGHTCODE:
        printesc(/* str 'pdfpageheight' */ 563);
        break;
    case PDFLINKMARGINCODE:
        printesc(/* str 'pdflinkmargin' */ 564);
        break;
    case PDFDESTMARGINCODE:
        printesc(/* str 'pdfdestmargin' */ 565);
        break;
    case PDFTHREADMARGINCODE:
        printesc(/* str 'pdfthreadmargin' */ 566);
        break;
    case PDFFIRSTLINEHEIGHTCODE:
        printesc(/* str 'pdffirstlineheight' */ 567);
        break;
    case PDFLASTLINEDEPTHCODE:
        printesc(/* str 'pdflastlinedepth' */ 568);
        break;
    case PDFEACHLINEHEIGHTCODE:
        printesc(/* str 'pdfeachlineheight' */ 569);
        break;
    case PDFEACHLINEDEPTHCODE:
        printesc(/* str 'pdfeachlinedepth' */ 570);
        break;
    case PDFIGNOREDDIMENCODE:
        printesc(/* str 'pdfignoreddimen' */ 571);
        break;
    case PDFPXDIMENCODE:
        printesc(/* str 'pdfpxdimen' */ 572);
        break;
    default:
        print(/* str '[unknown dimen parameter!]' */ 573);
        break;
    }
}
/* comment:Declare the procedure called |print_cmd_chr| */ void
zprintcmdchr(quarterword cmd, halfword chrcode) {
    printcmdchr_regmem integer n;
    switch (cmd) {
    case LEFTBRACE: {
        print(/* str 'begin-group character ' */ 640);
        print(chrcode);
    } break;
    case RIGHTBRACE: {
        print(/* str 'end-group character ' */ 641);
        print(chrcode);
    } break;
    case MATHSHIFT: {
        print(/* str 'math shift character ' */ 642);
        print(chrcode);
    } break;
    case MACPARAM: {
        print(/* str 'macro parameter character ' */ 643);
        print(chrcode);
    } break;
    case SUPMARK: {
        print(/* str 'superscript character ' */ 644);
        print(chrcode);
    } break;
    case SUBMARK: {
        print(/* str 'subscript character ' */ 645);
        print(chrcode);
    } break;
    case ENDV:
        print(/* str 'end of alignment template' */ 646);
        break;
    case SPACER: {
        print(/* str 'blank space ' */ 647);
        print(chrcode);
    } break;
    case LETTER: {
        print(/* str 'the letter ' */ 648);
        print(chrcode);
    } break;
    case OTHERCHAR: {
        print(/* str 'the character ' */ 649);
        print(chrcode);
    } break;
    /* comment:Cases of |print_cmd_chr| for symbolic printing of  */
    case ASSIGNGLUE:
    case ASSIGNMUGLUE:
        if (chrcode < SKIPBASE)
            printskipparam(chrcode - GLUEBASE);
        else if (chrcode < MUSKIPBASE) {
            printesc(/* str 'skip' */ 412);
            printint(chrcode - SKIPBASE);
        } else {

            printesc(/* str 'muskip' */ 413);
            printint(chrcode - MUSKIPBASE);
        }
        break;
    case ASSIGNTOKS:
        if (chrcode >= TOKSBASE) {
            printesc(/* str 'toks' */ 427);
            printint(chrcode - TOKSBASE);
        } else
            switch (chrcode) {
            case OUTPUTROUTINELOC:
                printesc(/* str 'output' */ 414);
                break;
            case EVERYPARLOC:
                printesc(/* str 'everypar' */ 415);
                break;
            case EVERYMATHLOC:
                printesc(/* str 'everymath' */ 416);
                break;
            case EVERYDISPLAYLOC:
                printesc(/* str 'everydisplay' */ 417);
                break;
            case EVERYHBOXLOC:
                printesc(/* str 'everyhbox' */ 418);
                break;
            case EVERYVBOXLOC:
                printesc(/* str 'everyvbox' */ 419);
                break;
            case EVERYJOBLOC:
                printesc(/* str 'everyjob' */ 420);
                break;
            case EVERYCRLOC:
                printesc(/* str 'everycr' */ 421);
                break;
            /* comment:Cases of |assign_toks| for |print_cmd_chr| */
            case EVERYEOFLOC:
                printesc(/* str 'everyeof' */ 1971);
                break;
            case PDFPAGESATTRLOC:
                printesc(/* str 'pdfpagesattr' */ 423);
                break;
            case PDFPAGEATTRLOC:
                printesc(/* str 'pdfpageattr' */ 424);
                break;
            case PDFPAGERESOURCESLOC:
                printesc(/* str 'pdfpageresources' */ 425);
                break;
            case PDFPKMODELOC:
                printesc(/* str 'pdfpkmode' */ 426);
                break;
            default:
                printesc(/* str 'errhelp' */ 422);
                break;
            }
        break;
    case ASSIGNINT:
        if (chrcode < COUNTBASE)
            printparam(chrcode - INTBASE);
        else {

            printesc(/* str 'count' */ 537);
            printint(chrcode - COUNTBASE);
        }
        break;
    case ASSIGNDIMEN:
        if (chrcode < SCALEDBASE)
            printlengthparam(chrcode - DIMENBASE);
        else {

            printesc(/* str 'dimen' */ 574);
            printint(chrcode - SCALEDBASE);
        }
        break;
    case ACCENT:
        printesc(/* str 'accent' */ 584);
        break;
    case ADVANCE:
        printesc(/* str 'advance' */ 585);
        break;
    case AFTERASSIGNMENT:
        printesc(/* str 'afterassignment' */ 586);
        break;
    case AFTERGROUP:
        printesc(/* str 'aftergroup' */ 587);
        break;
    case ASSIGNFONTDIMEN:
        printesc(/* str 'fontdimen' */ 598);
        break;
    case BEGINGROUP:
        printesc(/* str 'begingroup' */ 588);
        break;
    case BREAKPENALTY:
        printesc(/* str 'penalty' */ 611);
        break;
    case CHARNUM:
        printesc(/* str 'char' */ 589);
        break;
    case CSNAME:
        printesc(/* str 'csname' */ 580);
        break;
    case DEFFONT:
        printesc(/* str 'font' */ 595);
        break;
    case LETTERSPACEFONT:
        printesc(/* str 'letterspacefont' */ 596);
        break;
    case PDFCOPYFONT:
        printesc(/* str 'pdfcopyfont' */ 597);
        break;
    case DELIMNUM:
        printesc(/* str 'delimiter' */ 590);
        break;
    case DIVIDE:
        printesc(/* str 'divide' */ 591);
        break;
    case ENDCSNAME:
        if (chrcode == 10)
            printesc(/* str 'endmubyte' */ 592);
        else
            printesc(/* str 'endcsname' */ 581);
        break;
    case ENDGROUP:
        printesc(/* str 'endgroup' */ 593);
        break;
    case EXSPACE:
        printesc(/* str ' ' */ 32);
        break;
    case EXPANDAFTER:
        if (chrcode == 0)
            printesc(/* str 'expandafter' */ 594);
        /* comment:Cases of |expandafter| for |print_cmd_chr| */ else
            printesc(/* str 'unless' */ 928);
        break;
    case HALIGN:
        printesc(/* str 'halign' */ 599);
        break;
    case HRULE:
        printesc(/* str 'hrule' */ 600);
        break;
    case IGNORESPACES:
        if (chrcode == 0)
            printesc(/* str 'ignorespaces' */ 601);
        else
            printesc(/* str 'pdfprimitive' */ 577);
        break;
    case INSERT:
        printesc(/* str 'insert' */ 337);
        break;
    case ITALCORR:
        printesc(/* str '' */ 47);
        break;
    case MARK: {
        printesc(/* str 'mark' */ 359);
        if (chrcode > 0)
            printchar(/* str 's' */ 115);
    } break;
    case MATHACCENT:
        printesc(/* str 'mathaccent' */ 602);
        break;
    case MATHCHARNUM:
        printesc(/* str 'mathchar' */ 603);
        break;
    case MATHCHOICE:
        printesc(/* str 'mathchoice' */ 604);
        break;
    case MULTIPLY:
        printesc(/* str 'multiply' */ 605);
        break;
    case NOALIGN:
        printesc(/* str 'noalign' */ 606);
        break;
    case NOBOUNDARY:
        printesc(/* str 'noboundary' */ 607);
        break;
    case NOEXPAND:
        if (chrcode == 0)
            printesc(/* str 'noexpand' */ 608);
        else
            printesc(/* str 'pdfprimitive' */ 577);
        break;
    case NONSCRIPT:
        printesc(/* str 'nonscript' */ 342);
        break;
    case OMIT:
        printesc(/* str 'omit' */ 609);
        break;
    case RADICAL:
        printesc(/* str 'radical' */ 613);
        break;
    case READTOCS:
        if (chrcode == 0)
            printesc(/* str 'read' */ 614);
        /* comment:Cases of |read| for |print_cmd_chr| */ else
            printesc(/* str 'readline' */ 2035);
        break;
    case RELAX:
        printesc(/* str 'relax' */ 615);
        break;
    case SETBOX:
        printesc(/* str 'setbox' */ 616);
        break;
    case SETPREVGRAF:
        printesc(/* str 'prevgraf' */ 612);
        break;
    case SETSHAPE:
        switch (chrcode) {
        case PARSHAPELOC:
            printesc(/* str 'parshape' */ 610);
            break;
        /* comment:Cases of |set_shape| for |print_cmd_chr| */
        case INTERLINEPENALTIESLOC:
            printesc(/* str 'interlinepenalties' */ 2071);
            break;
        case CLUBPENALTIESLOC:
            printesc(/* str 'clubpenalties' */ 2072);
            break;
        case WIDOWPENALTIESLOC:
            printesc(/* str 'widowpenalties' */ 2073);
            break;
        case DISPLAYWIDOWPENALTIESLOC:
            printesc(/* str 'displaywidowpenalties' */ 2074);
            break;
        }
        break;
    case THE:
        if (chrcode == 0)
            printesc(/* str 'the' */ 617);
        /* comment:Cases of |the| for |print_cmd_chr| */ else if (chrcode == 1)
            printesc(/* str 'unexpanded' */ 2010);
        else
            printesc(/* str 'detokenize' */ 2011);
        break;
    case TOKSREGISTER:
        /* comment:Cases of |toks_register| for |print_cmd_chr| */ {

            printesc(/* str 'toks' */ 427);
            if (chrcode != membot)
                printsanum(chrcode);
        }
        break;
    case VADJUST:
        printesc(/* str 'vadjust' */ 360);
        break;
    case VALIGN:
        if (chrcode == 0)
            printesc(/* str 'valign' */ 618);
        /* comment:Cases of |valign| for |print_cmd_chr| */ else
            switch (chrcode) {
            case BEGINLCODE:
                printesc(/* str 'beginL' */ 2021);
                break;
            case ENDLCODE:
                printesc(/* str 'endL' */ 2022);
                break;
            case BEGINRCODE:
                printesc(/* str 'beginR' */ 2023);
                break;
            default:
                printesc(/* str 'endR' */ 2024);
                break;
            }
        break;
    case VCENTER:
        printesc(/* str 'vcenter' */ 619);
        break;
    case VRULE:
        printesc(/* str 'vrule' */ 620);
        break;
    case PAREND:
        printesc(/* str 'par' */ 681);
        break;
    case INPUT:
        if (chrcode == 0)
            printesc(/* str 'input' */ 716);
        /* comment:Cases of |input| for |print_cmd_chr| */ else if (chrcode ==
                                                                    2)
            printesc(/* str 'scantokens' */ 2033);
        else
            printesc(/* str 'endinput' */ 717);
        break;
    case TOPBOTMARK: {
        switch ((chrcode % 5)) {
        case FIRSTMARKCODE:
            printesc(/* str 'firstmark' */ 719);
            break;
        case BOTMARKCODE:
            printesc(/* str 'botmark' */ 720);
            break;
        case SPLITFIRSTMARKCODE:
            printesc(/* str 'splitfirstmark' */ 721);
            break;
        case SPLITBOTMARKCODE:
            printesc(/* str 'splitbotmark' */ 722);
            break;
        default:
            printesc(/* str 'topmark' */ 718);
            break;
        }
        if (chrcode >= 5)
            printchar(/* str 's' */ 115);
    } break;
    case REGISTER:
        /* comment:Cases of |register| for |print_cmd_chr| */ {

            if ((chrcode < membot) ||
                (chrcode > /* @d2881@ */ /* @d2882@ */ /* @d2883@ */
                               /* @d2884@ */ /* @d2885@ */ membot + 19))
                cmd = (mem[chrcode].hh.b0 / 16);
            else {

                cmd = chrcode - membot;
                chrcode = TEXNULL;
            }
            if (cmd == INTVAL)
                printesc(/* str 'count' */ 537);
            else if (cmd == DIMENVAL)
                printesc(/* str 'dimen' */ 574);
            else if (cmd == GLUEVAL)
                printesc(/* str 'skip' */ 412);
            else
                printesc(/* str 'muskip' */ 413);
            if (chrcode != TEXNULL)
                printsanum(chrcode);
        }
        break;
    case SETAUX:
        if (chrcode == VMODE)
            printesc(/* str 'prevdepth' */ 756);
        else
            printesc(/* str 'spacefactor' */ 755);
        break;
    case SETPAGEINT:
        if (chrcode == 0)
            printesc(/* str 'deadcycles' */ 757);
        /* comment:Cases of |set_page_int| for |print_cmd_chr| */
        else if (chrcode == 2)
            printesc(/* str 'interactionmode' */ 2016);
        else
            printesc(/* str 'insertpenalties' */ 758);
        break;
    case SETBOXDIMEN:
        if (chrcode == WIDTHOFFSET)
            printesc(/* str 'wd' */ 759);
        else if (chrcode == HEIGHTOFFSET)
            printesc(/* str 'ht' */ 760);
        else
            printesc(/* str 'dp' */ 761);
        break;
    case LASTITEM:
        switch (chrcode) {
        case INTVAL:
            printesc(/* str 'lastpenalty' */ 762);
            break;
        case DIMENVAL:
            printesc(/* str 'lastkern' */ 763);
            break;
        case GLUEVAL:
            printesc(/* str 'lastskip' */ 764);
            break;
        case INPUTLINENOCODE:
            printesc(/* str 'inputlineno' */ 765);
            break;
        /* comment:Cases of |last_item| for |print_cmd_chr| */
        case LASTNODETYPECODE:
            printesc(/* str 'lastnodetype' */ 1968);
            break;
        case ETEXVERSIONCODE:
            printesc(/* str 'eTeXversion' */ 1969);
            break;
        case CURRENTGROUPLEVELCODE:
            printesc(/* str 'currentgrouplevel' */ 1995);
            break;
        case CURRENTGROUPTYPECODE:
            printesc(/* str 'currentgrouptype' */ 1996);
            break;
        case CURRENTIFLEVELCODE:
            printesc(/* str 'currentiflevel' */ 1997);
            break;
        case CURRENTIFTYPECODE:
            printesc(/* str 'currentiftype' */ 1998);
            break;
        case CURRENTIFBRANCHCODE:
            printesc(/* str 'currentifbranch' */ 1999);
            break;
        case FONTCHARWDCODE:
            printesc(/* str 'fontcharwd' */ 2000);
            break;
        case FONTCHARHTCODE:
            printesc(/* str 'fontcharht' */ 2001);
            break;
        case FONTCHARDPCODE:
            printesc(/* str 'fontchardp' */ 2002);
            break;
        case FONTCHARICCODE:
            printesc(/* str 'fontcharic' */ 2003);
            break;
        case PARSHAPELENGTHCODE:
            printesc(/* str 'parshapelength' */ 2004);
            break;
        case PARSHAPEINDENTCODE:
            printesc(/* str 'parshapeindent' */ 2005);
            break;
        case PARSHAPEDIMENCODE:
            printesc(/* str 'parshapedimen' */ 2006);
            break;
        case ETEXEXPR + INTVAL + INTVAL:
            printesc(/* str 'numexpr' */ 2047);
            break;
        case ETEXEXPR + INTVAL + DIMENVAL:
            printesc(/* str 'dimexpr' */ 2048);
            break;
        case ETEXEXPR + INTVAL + GLUEVAL:
            printesc(/* str 'glueexpr' */ 2049);
            break;
        case ETEXEXPR + INTVAL + MUVAL:
            printesc(/* str 'muexpr' */ 2050);
            break;
        case GLUESTRETCHORDERCODE:
            printesc(/* str 'gluestretchorder' */ 2054);
            break;
        case GLUESHRINKORDERCODE:
            printesc(/* str 'glueshrinkorder' */ 2055);
            break;
        case GLUESTRETCHCODE:
            printesc(/* str 'gluestretch' */ 2056);
            break;
        case GLUESHRINKCODE:
            printesc(/* str 'glueshrink' */ 2057);
            break;
        case MUTOGLUECODE:
            printesc(/* str 'mutoglue' */ 2058);
            break;
        case GLUETOMUCODE:
            printesc(/* str 'gluetomu' */ 2059);
            break;
        case PDFTEXVERSIONCODE:
            printesc(/* str 'pdftexversion' */ 767);
            break;
        case PDFLASTOBJCODE:
            printesc(/* str 'pdflastobj' */ 768);
            break;
        case PDFLASTXFORMCODE:
            printesc(/* str 'pdflastxform' */ 769);
            break;
        case PDFLASTXIMAGECODE:
            printesc(/* str 'pdflastximage' */ 770);
            break;
        case PDFLASTXIMAGEPAGESCODE:
            printesc(/* str 'pdflastximagepages' */ 771);
            break;
        case PDFLASTANNOTCODE:
            printesc(/* str 'pdflastannot' */ 772);
            break;
        case PDFLASTXPOSCODE:
            printesc(/* str 'pdflastxpos' */ 773);
            break;
        case PDFLASTYPOSCODE:
            printesc(/* str 'pdflastypos' */ 774);
            break;
        case PDFRETVALCODE:
            printesc(/* str 'pdfretval' */ 775);
            break;
        case PDFLASTXIMAGECOLORDEPTHCODE:
            printesc(/* str 'pdflastximagecolordepth' */ 776);
            break;
        case ELAPSEDTIMECODE:
            printesc(/* str 'pdfelapsedtime' */ 777);
            break;
        case PDFSHELLESCAPECODE:
            printesc(/* str 'pdfshellescape' */ 778);
            break;
        case RANDOMSEEDCODE:
            printesc(/* str 'pdfrandomseed' */ 779);
            break;
        case PDFLASTLINKCODE:
            printesc(/* str 'pdflastlink' */ 780);
            break;
        default:
            printesc(/* str 'badness' */ 766);
            break;
        }
        break;
    case CONVERT:
        switch (chrcode) {
        case NUMBERCODE:
            printesc(/* str 'number' */ 839);
            break;
        case ROMANNUMERALCODE:
            printesc(/* str 'romannumeral' */ 840);
            break;
        case STRINGCODE:
            printesc(/* str 'string' */ 841);
            break;
        case MEANINGCODE:
            printesc(/* str 'meaning' */ 842);
            break;
        case FONTNAMECODE:
            printesc(/* str 'fontname' */ 843);
            break;
        case ETEXREVISIONCODE:
            printesc(/* str 'eTeXrevision' */ 872);
            break;
        case EXPANDEDCODE:
            printesc(/* str 'expanded' */ 844);
            break;
        case PDFTEXREVISIONCODE:
            printesc(/* str 'pdftexrevision' */ 845);
            break;
        case PDFTEXBANNERCODE:
            printesc(/* str 'pdftexbanner' */ 846);
            break;
        case PDFFONTNAMECODE:
            printesc(/* str 'pdffontname' */ 847);
            break;
        case PDFFONTOBJNUMCODE:
            printesc(/* str 'pdffontobjnum' */ 848);
            break;
        case PDFFONTSIZECODE:
            printesc(/* str 'pdffontsize' */ 849);
            break;
        case PDFPAGEREFCODE:
            printesc(/* str 'pdfpageref' */ 850);
            break;
        case LEFTMARGINKERNCODE:
            printesc(/* str 'leftmarginkern' */ 851);
            break;
        case RIGHTMARGINKERNCODE:
            printesc(/* str 'rightmarginkern' */ 852);
            break;
        case PDFXFORMNAMECODE:
            printesc(/* str 'pdfxformname' */ 853);
            break;
        case PDFESCAPESTRINGCODE:
            printesc(/* str 'pdfescapestring' */ 854);
            break;
        case PDFESCAPENAMECODE:
            printesc(/* str 'pdfescapename' */ 855);
            break;
        case PDFESCAPEHEXCODE:
            printesc(/* str 'pdfescapehex' */ 856);
            break;
        case PDFUNESCAPEHEXCODE:
            printesc(/* str 'pdfunescapehex' */ 857);
            break;
        case PDFCREATIONDATECODE:
            printesc(/* str 'pdfcreationdate' */ 858);
            break;
        case PDFFILEMODDATECODE:
            printesc(/* str 'pdffilemoddate' */ 859);
            break;
        case PDFFILESIZECODE:
            printesc(/* str 'pdffilesize' */ 860);
            break;
        case PDFMDFIVESUMCODE:
            printesc(/* str 'pdfmdfivesum' */ 861);
            break;
        case PDFFILEDUMPCODE:
            printesc(/* str 'pdffiledump' */ 862);
            break;
        case PDFMATCHCODE:
            printesc(/* str 'pdfmatch' */ 863);
            break;
        case PDFLASTMATCHCODE:
            printesc(/* str 'pdflastmatch' */ 864);
            break;
        case PDFSTRCMPCODE:
            printesc(/* str 'pdfstrcmp' */ 865);
            break;
        case PDFCOLORSTACKINITCODE:
            printesc(/* str 'pdfcolorstackinit' */ 866);
            break;
        case UNIFORMDEVIATECODE:
            printesc(/* str 'pdfuniformdeviate' */ 867);
            break;
        case NORMALDEVIATECODE:
            printesc(/* str 'pdfnormaldeviate' */ 868);
            break;
        case PDFINSERTHTCODE:
            printesc(/* str 'pdfinsertht' */ 870);
            break;
        case PDFXIMAGEBBOXCODE:
            printesc(/* str 'pdfximagebbox' */ 871);
            break;
        default:
            printesc(/* str 'jobname' */ 869);
            break;
        }
        break;
    case IFTEST: {
        if (chrcode >= UNLESSCODE)
            printesc(/* str 'unless' */ 928);
        switch (chrcode % /* @d3074@ */ 32) {
        case IFCATCODE:
            printesc(/* str 'ifcat' */ 911);
            break;
        case IFINTCODE:
            printesc(/* str 'ifnum' */ 912);
            break;
        case IFDIMCODE:
            printesc(/* str 'ifdim' */ 913);
            break;
        case IFODDCODE:
            printesc(/* str 'ifodd' */ 914);
            break;
        case IFVMODECODE:
            printesc(/* str 'ifvmode' */ 915);
            break;
        case IFHMODECODE:
            printesc(/* str 'ifhmode' */ 916);
            break;
        case IFMMODECODE:
            printesc(/* str 'ifmmode' */ 917);
            break;
        case IFINNERCODE:
            printesc(/* str 'ifinner' */ 918);
            break;
        case IFVOIDCODE:
            printesc(/* str 'ifvoid' */ 919);
            break;
        case IFHBOXCODE:
            printesc(/* str 'ifhbox' */ 920);
            break;
        case IFVBOXCODE:
            printesc(/* str 'ifvbox' */ 921);
            break;
        case IFXCODE:
            printesc(/* str 'ifx' */ 922);
            break;
        case IFEOFCODE:
            printesc(/* str 'ifeof' */ 923);
            break;
        case IFTRUECODE:
            printesc(/* str 'iftrue' */ 924);
            break;
        case IFFALSECODE:
            printesc(/* str 'iffalse' */ 925);
            break;
        case IFCASECODE:
            printesc(/* str 'ifcase' */ 926);
            break;
        case IFPDFPRIMITIVECODE:
            printesc(/* str 'ifpdfprimitive' */ 927);
            break;
        /* comment:Cases of |if_test| for |print_cmd_chr| */ case IFDEFCODE:
            printesc(/* str 'ifdefined' */ 2036);
            break;
        case IFCSCODE:
            printesc(/* str 'ifcsname' */ 2037);
            break;
        case IFFONTCHARCODE:
            printesc(/* str 'iffontchar' */ 2038);
            break;
        case IFINCSNAMECODE:
            printesc(/* str 'ifincsname' */ 2039);
            break;
        case IFPDFABSNUMCODE:
            printesc(/* str 'ifpdfabsnum' */ 2040);
            break;
        case IFPDFABSDIMCODE:
            printesc(/* str 'ifpdfabsdim' */ 2041);
            break;
        default:
            printesc(/* str 'if' */ 910);
            break;
        }
    } break;
    case FIORELSE:
        if (chrcode == FICODE)
            printesc(/* str 'fi' */ 929);
        else if (chrcode == ORCODE)
            printesc(/* str 'or' */ 930);
        else
            printesc(/* str 'else' */ 931);
        break;
    case TABMARK:
        if (chrcode == SPANCODE)
            printesc(/* str 'span' */ 1308);
        else {

            print(/* str 'alignment tab character ' */ 1312);
            print(chrcode);
        }
        break;
    case CARRET:
        if (chrcode == CRCODE)
            printesc(/* str 'cr' */ 1309);
        else
            printesc(/* str 'crcr' */ 1310);
        break;
    case SETPAGEDIMEN:
        switch (chrcode) {
        case 0:
            printesc(/* str 'pagegoal' */ 1386);
            break;
        case 1:
            printesc(/* str 'pagetotal' */ 1387);
            break;
        case 2:
            printesc(/* str 'pagestretch' */ 1388);
            break;
        case 3:
            printesc(/* str 'pagefilstretch' */ 1389);
            break;
        case 4:
            printesc(/* str 'pagefillstretch' */ 1390);
            break;
        case 5:
            printesc(/* str 'pagefilllstretch' */ 1391);
            break;
        case 6:
            printesc(/* str 'pageshrink' */ 1392);
            break;
        default:
            printesc(/* str 'pagedepth' */ 1393);
            break;
        }
        break;
    case STOP:
        if (chrcode == 1)
            printesc(/* str 'dump' */ 1439);
        else
            printesc(/* str 'end' */ 349);
        break;
    case HSKIP:
        switch (chrcode) {
        case SKIPCODE:
            printesc(/* str 'hskip' */ 1440);
            break;
        case FILCODE:
            printesc(/* str 'hfil' */ 1441);
            break;
        case FILLCODE:
            printesc(/* str 'hfill' */ 1442);
            break;
        case SSCODE:
            printesc(/* str 'hss' */ 1443);
            break;
        default:
            printesc(/* str 'hfilneg' */ 1444);
            break;
        }
        break;
    case VSKIP:
        switch (chrcode) {
        case SKIPCODE:
            printesc(/* str 'vskip' */ 1445);
            break;
        case FILCODE:
            printesc(/* str 'vfil' */ 1446);
            break;
        case FILLCODE:
            printesc(/* str 'vfill' */ 1447);
            break;
        case SSCODE:
            printesc(/* str 'vss' */ 1448);
            break;
        default:
            printesc(/* str 'vfilneg' */ 1449);
            break;
        }
        break;
    case MSKIP:
        printesc(/* str 'mskip' */ 343);
        break;
    case KERN:
        printesc(/* str 'kern' */ 322);
        break;
    case MKERN:
        printesc(/* str 'mkern' */ 348);
        break;
    case HMOVE:
        if (chrcode == 1)
            printesc(/* str 'moveleft' */ 1467);
        else
            printesc(/* str 'moveright' */ 1468);
        break;
    case VMOVE:
        if (chrcode == 1)
            printesc(/* str 'raise' */ 1469);
        else
            printesc(/* str 'lower' */ 1470);
        break;
    case MAKEBOX:
        switch (chrcode) {
        case BOXCODE:
            printesc(/* str 'box' */ 429);
            break;
        case COPYCODE:
            printesc(/* str 'copy' */ 1471);
            break;
        case LASTBOXCODE:
            printesc(/* str 'lastbox' */ 1472);
            break;
        case VSPLITCODE:
            printesc(/* str 'vsplit' */ 1381);
            break;
        case VTOPCODE:
            printesc(/* str 'vtop' */ 1473);
            break;
        case VTOPCODE + VMODE:
            printesc(/* str 'vbox' */ 1383);
            break;
        default:
            printesc(/* str 'hbox' */ 1474);
            break;
        }
        break;
    case LEADERSHIP:
        if (chrcode == ALEADERS)
            printesc(/* str 'leaders' */ 1476);
        else if (chrcode == CLEADERS)
            printesc(/* str 'cleaders' */ 1477);
        else if (chrcode == XLEADERS)
            printesc(/* str 'xleaders' */ 1478);
        else
            printesc(/* str 'shipout' */ 1475);
        break;
    case STARTPAR:
        if (chrcode == 0)
            printesc(/* str 'noindent' */ 1495);
        else if (chrcode == 1)
            printesc(/* str 'indent' */ 1494);
        else
            printesc(/* str 'quitvmode' */ 1496);
        break;
    case REMOVEITEM:
        if (chrcode == GLUENODE)
            printesc(/* str 'unskip' */ 1508);
        else if (chrcode == KERNNODE)
            printesc(/* str 'unkern' */ 1507);
        else
            printesc(/* str 'unpenalty' */ 1506);
        break;
    case UNHBOX:
        if (chrcode == COPYCODE)
            printesc(/* str 'unhcopy' */ 1510);
        else
            printesc(/* str 'unhbox' */ 1509);
        break;
    case UNVBOX:
        if (chrcode == COPYCODE)
            printesc(/* str 'unvcopy' */ 1512);
        /* comment:Cases of |un_vbox| for |print_cmd_chr| */
        else if (chrcode == LASTBOXCODE)
            printesc(/* str 'pagediscards' */ 2069);
        else if (chrcode == VSPLITCODE)
            printesc(/* str 'splitdiscards' */ 2070);
        else
            printesc(/* str 'unvbox' */ 1511);
        break;
    case DISCRETIONARY:
        if (chrcode == 1)
            printesc(/* str '-' */ 45);
        else
            printesc(/* str 'discretionary' */ 357);
        break;
    case EQNO:
        if (chrcode == 1)
            printesc(/* str 'leqno' */ 1545);
        else
            printesc(/* str 'eqno' */ 1544);
        break;
    case MATHCOMP:
        switch (chrcode) {
        case ORDNOAD:
            printesc(/* str 'mathord' */ 1275);
            break;
        case OPNOAD:
            printesc(/* str 'mathop' */ 1276);
            break;
        case BINNOAD:
            printesc(/* str 'mathbin' */ 1277);
            break;
        case RELNOAD:
            printesc(/* str 'mathrel' */ 1278);
            break;
        case OPENNOAD:
            printesc(/* str 'mathopen' */ 1279);
            break;
        case CLOSENOAD:
            printesc(/* str 'mathclose' */ 1280);
            break;
        case PUNCTNOAD:
            printesc(/* str 'mathpunct' */ 1281);
            break;
        case INNERNOAD:
            printesc(/* str 'mathinner' */ 1282);
            break;
        case UNDERNOAD:
            printesc(/* str 'underline' */ 1284);
            break;
        default:
            printesc(/* str 'overline' */ 1283);
            break;
        }
        break;
    case LIMITSWITCH:
        if (chrcode == LIMITS)
            printesc(/* str 'limits' */ 1288);
        else if (chrcode == NOLIMITS)
            printesc(/* str 'nolimits' */ 1289);
        else
            printesc(/* str 'displaylimits' */ 1546);
        break;
    case MATHSTYLE:
        printstyle(chrcode);
        break;
    case ABOVE:
        switch (chrcode) {
        case OVERCODE:
            printesc(/* str 'over' */ 1565);
            break;
        case ATOPCODE:
            printesc(/* str 'atop' */ 1566);
            break;
        case DELIMITEDCODE + ABOVECODE:
            printesc(/* str 'abovewithdelims' */ 1567);
            break;
        case DELIMITEDCODE + OVERCODE:
            printesc(/* str 'overwithdelims' */ 1568);
            break;
        case DELIMITEDCODE + ATOPCODE:
            printesc(/* str 'atopwithdelims' */ 1569);
            break;
        default:
            printesc(/* str 'above' */ 1564);
            break;
        }
        break;
    case LEFTRIGHT:
        if (chrcode == LEFTNOAD)
            printesc(/* str 'left' */ 1285);
        /* comment:Cases of |left_right| for |print_cmd_chr| */
        else if (chrcode == 1)
            printesc(/* str 'middle' */ 1287);
        else
            printesc(/* str 'right' */ 1286);
        break;
    case PREFIX:
        if (chrcode == 1)
            printesc(/* str 'long' */ 1589);
        else if (chrcode == 2)
            printesc(/* str 'outer' */ 1590);
        /* comment:Cases of |prefix| for |print_cmd_chr| */ else if (chrcode ==
                                                                     8)
            printesc(/* str 'protected' */ 1603);
        else
            printesc(/* str 'global' */ 1591);
        break;
    case DEF:
        if (chrcode == 0)
            printesc(/* str 'def' */ 1592);
        else if (chrcode == 1)
            printesc(/* str 'gdef' */ 1593);
        else if (chrcode == 2)
            printesc(/* str 'edef' */ 1594);
        else
            printesc(/* str 'xdef' */ 1595);
        break;
    case LET:
        if (chrcode != NORMAL) {

            if (chrcode == /* @d3294@ */ 10)
                printesc(/* str 'mubyte' */ 1614);
            else if (chrcode == /* @d3296@ */ 11)
                printesc(/* str 'noconvert' */ 1615);
            else
                printesc(/* str 'futurelet' */ 1613);
        } else
            printesc(/* str 'let' */ 1612);
        break;
    case SHORTHANDDEF:
        switch (chrcode) {
        case CHARDEFCODE:
            printesc(/* str 'chardef' */ 1621);
            break;
        case MATHCHARDEFCODE:
            printesc(/* str 'mathchardef' */ 1622);
            break;
        case COUNTDEFCODE:
            printesc(/* str 'countdef' */ 1623);
            break;
        case DIMENDEFCODE:
            printesc(/* str 'dimendef' */ 1624);
            break;
        case SKIPDEFCODE:
            printesc(/* str 'skipdef' */ 1625);
            break;
        case MUSKIPDEFCODE:
            printesc(/* str 'muskipdef' */ 1626);
            break;
        case CHARSUBDEFCODE:
            printesc(/* str 'charsubdef' */ 1628);
            break;
        default:
            printesc(/* str 'toksdef' */ 1627);
            break;
        }
        break;
    case CHARGIVEN: {
        printesc(/* str 'char' */ 589);
        printhex(chrcode);
    } break;
    case MATHGIVEN: {
        printesc(/* str 'mathchar' */ 603);
        printhex(chrcode);
    } break;
    case DEFCODE:
        if (chrcode == XORDCODEBASE)
            printesc(/* str 'xordcode' */ 1633);
        else if (chrcode == XCHRCODEBASE)
            printesc(/* str 'xchrcode' */ 1634);
        else if (chrcode == XPRNCODEBASE)
            printesc(/* str 'xprncode' */ 1635);
        else if (chrcode == CATCODEBASE)
            printesc(/* str 'catcode' */ 435);
        else if (chrcode == MATHCODEBASE)
            printesc(/* str 'mathcode' */ 439);
        else if (chrcode == LCCODEBASE)
            printesc(/* str 'lccode' */ 436);
        else if (chrcode == UCCODEBASE)
            printesc(/* str 'uccode' */ 437);
        else if (chrcode == SFCODEBASE)
            printesc(/* str 'sfcode' */ 438);
        else
            printesc(/* str 'delcode' */ 538);
        break;
    case DEFFAMILY:
        printsize(chrcode - MATHFONTBASE);
        break;
    case HYPHDATA:
        if (chrcode == 1)
            printesc(/* str 'patterns' */ 1367);
        else
            printesc(/* str 'hyphenation' */ 1355);
        break;
    case ASSIGNFONTINT:
        switch (chrcode) {
        case 0:
            printesc(/* str 'hyphenchar' */ 1651);
            break;
        case 1:
            printesc(/* str 'skewchar' */ 1652);
            break;
        case 2:
            printesc(/* str 'lpcode' */ 1653);
            break;
        case 3:
            printesc(/* str 'rpcode' */ 1654);
            break;
        case 4:
            printesc(/* str 'efcode' */ 1655);
            break;
        case 5:
            printesc(/* str 'tagcode' */ 1656);
            break;
        case 7:
            printesc(/* str 'knbscode' */ 1657);
            break;
        case 8:
            printesc(/* str 'stbscode' */ 1658);
            break;
        case 9:
            printesc(/* str 'shbscode' */ 1659);
            break;
        case 10:
            printesc(/* str 'knbccode' */ 1660);
            break;
        case 11:
            printesc(/* str 'knaccode' */ 1661);
            break;
        case 6:
            printesc(/* str 'pdfnoligatures' */ 1662);
            break;
        }
        break;
    case SETFONT: {
        print(/* str 'select font ' */ 1669);
        slowprint(fontname[chrcode]);
        if (fontsize[chrcode] != fontdsize[chrcode]) {
            print(/* str ' at ' */ 895);
            printscaled(fontsize[chrcode]);
            print(/* str 'pt' */ 312);
        }
    } break;
    case SETINTERACTION:
        switch (chrcode) {
        case BATCHMODE:
            printesc(/* str 'batchmode' */ 274);
            break;
        case NONSTOPMODE:
            printesc(/* str 'nonstopmode' */ 275);
            break;
        case SCROLLMODE:
            printesc(/* str 'scrollmode' */ 276);
            break;
        default:
            printesc(/* str 'errorstopmode' */ 1670);
            break;
        }
        break;
    case INSTREAM:
        if (chrcode == 0)
            printesc(/* str 'closein' */ 1672);
        else
            printesc(/* str 'openin' */ 1671);
        break;
    case MESSAGE:
        if (chrcode == 0)
            printesc(/* str 'message' */ 1673);
        else
            printesc(/* str 'errmessage' */ 1674);
        break;
    case CASESHIFT:
        if (chrcode == LCCODEBASE)
            printesc(/* str 'lowercase' */ 1680);
        else
            printesc(/* str 'uppercase' */ 1681);
        break;
    case XRAY:
        switch (chrcode) {
        case SHOWBOXCODE:
            printesc(/* str 'showbox' */ 1683);
            break;
        case SHOWTHECODE:
            printesc(/* str 'showthe' */ 1684);
            break;
        case SHOWLISTS:
            printesc(/* str 'showlists' */ 1685);
            break;
        /* comment:Cases of |xray| for |print_cmd_chr| */ case SHOWGROUPS:
            printesc(/* str 'showgroups' */ 2007);
            break;
        case SHOWTOKENS:
            printesc(/* str 'showtokens' */ 2009);
            break;
        case SHOWIFS:
            printesc(/* str 'showifs' */ 2012);
            break;
        default:
            printesc(/* str 'show' */ 1682);
            break;
        }
        break;
    case UNDEFINEDCS:
        print(/* str 'undefined' */ 1692);
        break;
    case CALL:
    case LONGCALL:
    case OUTERCALL:
    case LONGOUTERCALL: {
        n = cmd - CALL;
        if (mem[mem[chrcode].hh.v.RH].hh.v.LH == PROTECTEDTOKEN)
            n = n + 4;
        if (odd(n / 4))
            printesc(/* str 'protected' */ 1603);
        if (odd(n))
            printesc(/* str 'long' */ 1589);
        if (odd(n / 2))
            printesc(/* str 'outer' */ 1590);
        if (n > 0)
            printchar(/* str ' ' */ 32);
        print(/* str 'macro' */ 1693);
    } break;
    case ENDTEMPLATE:
        printesc(/* str 'outer endtemplate' */ 1694);
        break;
    case EXTENSION:
        switch (chrcode) {
        case OPENNODE:
            printesc(/* str 'openout' */ 1732);
            break;
        case WRITENODE:
            printesc(/* str 'write' */ 678);
            break;
        case CLOSENODE:
            printesc(/* str 'closeout' */ 1733);
            break;
        case SPECIALNODE:
            printesc(/* str 'special' */ 1734);
            break;
        case IMMEDIATECODE:
            printesc(/* str 'immediate' */ 1735);
            break;
        case SETLANGUAGECODE:
            printesc(/* str 'setlanguage' */ 1736);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 7:
            printesc(/* str 'pdfannot' */ 1747);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 17:
            printesc(/* str 'pdfcatalog' */ 1760);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 11:
            printesc(/* str 'pdfdest' */ 1751);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 9:
            printesc(/* str 'pdfendlink' */ 1749);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 14:
            printesc(/* str 'pdfendthread' */ 1754);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 19:
            printesc(/* str 'pdffontattr' */ 1763);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 26:
            printesc(/* str 'pdffontexpand' */ 1770);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 20:
            printesc(/* str 'pdfincludechars' */ 1762);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 16:
            printesc(/* str 'pdfinfo' */ 1759);
            break;
        case PDFTEXFIRSTEXTENSIONCODE:
            printesc(/* str 'pdfliteral' */ 1737);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 32:
            printesc(/* str 'pdfcolorstack' */ 1136);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 33:
            printesc(/* str 'pdfsetmatrix' */ 1738);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 34:
            printesc(/* str 'pdfsave' */ 1739);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 35:
            printesc(/* str 'pdfrestore' */ 1740);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 21:
            printesc(/* str 'pdfmapfile' */ 1764);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 22:
            printesc(/* str 'pdfmapline' */ 1765);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 18:
            printesc(/* str 'pdfnames' */ 1761);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 1:
            printesc(/* str 'pdfobj' */ 1741);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 10:
            printesc(/* str 'pdfoutline' */ 1750);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 2:
            printesc(/* str 'pdfrefobj' */ 1742);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 4:
            printesc(/* str 'pdfrefxform' */ 1744);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 6:
            printesc(/* str 'pdfrefximage' */ 1746);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 15:
            printesc(/* str 'pdfsavepos' */ 1755);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 28:
            printesc(/* str 'pdfsnaprefpoint' */ 1756);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 30:
            printesc(/* str 'pdfsnapycomp' */ 1758);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 29:
            printesc(/* str 'pdfsnapy' */ 1757);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 8:
            printesc(/* str 'pdfstartlink' */ 1748);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 13:
            printesc(/* str 'pdfstartthread' */ 1753);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 12:
            printesc(/* str 'pdfthread' */ 1752);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 23:
            printesc(/* str 'pdftrailer' */ 1766);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 24:
            printesc(/* str 'pdftrailerid' */ 1767);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 3:
            printesc(/* str 'pdfxform' */ 1743);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 5:
            printesc(/* str 'pdfximage' */ 1745);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 25:
            printesc(/* str 'pdfresettimer' */ 1768);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 27:
            printesc(/* str 'pdfsetrandomseed' */ 1769);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 36:
            printesc(/* str 'pdfnobuiltintounicode' */ 1772);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 31:
            printesc(/* str 'pdfglyphtounicode' */ 1771);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 37:
            printesc(/* str 'pdfinterwordspaceon' */ 1773);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 38:
            printesc(/* str 'pdfinterwordspaceoff' */ 1774);
            break;
        case PDFTEXFIRSTEXTENSIONCODE + 39:
            printesc(/* str 'pdffakespace' */ 1775);
            break;
        default:
            print(/* str '[unknown extension!]' */ 1776);
            break;
        }
        break;
    default:
        print(/* str '[unknown command code!]' */ 650);
        break;
    }
}
#ifdef STAT
void zshoweqtb(halfword n) {
    showeqtb_regmem if (n < ACTIVEBASE) printchar(/* str '?' */ 63);
    else if ((n < GLUEBASE) ||
             ((n > EQTBSIZE) &&
              (n <=
               eqtbtop))) /* comment:Show equivalent |n|, in region 1 or 2 */
    {
        sprintcs(n);
        printchar(/* str '=' */ 61);
        printcmdchr(eqtb[n].hh.b0, eqtb[n].hh.v.RH);
        if (eqtb[n].hh.b0 >= CALL) {
            printchar(/* str '' */ 58);
            showtokenlist(mem[eqtb[n].hh.v.RH].hh.v.RH, TEXNULL, 32);
        }
    }
    else if (n < /* @d3511@ */
             27158) /* comment:Show equivalent |n|, in region 3 */ {

        if (n < SKIPBASE) {
            printskipparam(n - GLUEBASE);
            printchar(/* str '=' */ 61);
            if (n < /* @d3516@ */ /* @d3517@ */ 26643)
                printspec(eqtb[n].hh.v.RH, /* str 'pt' */ 312);
            else
                printspec(eqtb[n].hh.v.RH, /* str 'mu' */ 344);
        } else if (n < MUSKIPBASE) {
            printesc(/* str 'skip' */ 412);
            printint(n - SKIPBASE);
            printchar(/* str '=' */ 61);
            printspec(eqtb[n].hh.v.RH, /* str 'pt' */ 312);
        } else {

            printesc(/* str 'muskip' */ 413);
            printint(n - MUSKIPBASE);
            printchar(/* str '=' */ 61);
            printspec(eqtb[n].hh.v.RH, /* str 'mu' */ 344);
        }
    }
    else if (n < /* @d3529@ */
             29277) /* comment:Show equivalent |n|, in region 4 */ {

        if ((n == PARSHAPELOC) || ((n >= ETEXPENBASE) && (n < ETEXPENS))) {
            printcmdchr(SETSHAPE, n);
            printchar(/* str '=' */ 61);
            if (eqtb[n].hh.v.RH == TEXNULL)
                printchar(/* str '0' */ 48);
            else if (n > PARSHAPELOC) {
                printint(mem[eqtb[n].hh.v.RH + 1].cint);
                printchar(/* str ' ' */ 32);
                printint(mem[eqtb[n].hh.v.RH + 2].cint);
                if (mem[eqtb[n].hh.v.RH + 1].cint > 1)
                    printesc(/* str 'ETC.' */ 428);
            } else
                printint(mem[eqtb[PARSHAPELOC].hh.v.RH].hh.v.LH);
        } else if (n < TOKSBASE) {
            printcmdchr(ASSIGNTOKS, n);
            printchar(/* str '=' */ 61);
            if (eqtb[n].hh.v.RH != TEXNULL)
                showtokenlist(mem[eqtb[n].hh.v.RH].hh.v.RH, TEXNULL, 32);
        } else if (n < BOXBASE) {
            printesc(/* str 'toks' */ 427);
            printint(n - TOKSBASE);
            printchar(/* str '=' */ 61);
            if (eqtb[n].hh.v.RH != TEXNULL)
                showtokenlist(mem[eqtb[n].hh.v.RH].hh.v.RH, TEXNULL, 32);
        } else if (n < CURFONTLOC) {
            printesc(/* str 'box' */ 429);
            printint(n - BOXBASE);
            printchar(/* str '=' */ 61);
            if (eqtb[n].hh.v.RH == TEXNULL)
                print(/* str 'void' */ 430);
            else {

                depththreshold = 0;
                breadthmax = 1;
                shownodelist(eqtb[n].hh.v.RH);
            }
        } else if (n < CATCODEBASE) /* comment:Show the font identifier
                                               in |eqtb[n]| */
        {
            if (n == CURFONTLOC)
                print(/* str 'current font' */ 431);
            else if (n < /* @d3557@ */ 27709) {
                printesc(/* str 'textfont' */ 432);
                printint(n - MATHFONTBASE);
            } else if (n < /* @d3560@ */ 27725) {
                printesc(/* str 'scriptfont' */ 433);
                printint(/* @d3562@ */ n - 27709);
            } else {

                printesc(/* str 'scriptscriptfont' */ 434);
                printint(/* @d3564@ */ n - 27725);
            }
            printchar(/* str '=' */ 61);
            printesc(hash[FONTIDBASE + eqtb[n].hh.v.RH].v.RH);
        } else /* comment:Show the halfword code in |eqtb[n]| */
            if (n < MATHCODEBASE) {
            if (n < LCCODEBASE) {
                printesc(/* str 'catcode' */ 435);
                printint(n - CATCODEBASE);
            } else if (n < UCCODEBASE) {
                printesc(/* str 'lccode' */ 436);
                printint(n - LCCODEBASE);
            } else if (n < SFCODEBASE) {
                printesc(/* str 'uccode' */ 437);
                printint(n - UCCODEBASE);
            } else {

                printesc(/* str 'sfcode' */ 438);
                printint(n - SFCODEBASE);
            }
            printchar(/* str '=' */ 61);
            printint(eqtb[n].hh.v.RH);
        } else {

            printesc(/* str 'mathcode' */ 439);
            printint(n - MATHCODEBASE);
            printchar(/* str '=' */ 61);
            printint(eqtb[n].hh.v.RH);
        }
    }
    else if (n < DIMENBASE) /* comment:Show equivalent |n|, in region 5 */
    {
        if (n < COUNTBASE)
            printparam(n - INTBASE);
        else if (n < DELCODEBASE) {
            printesc(/* str 'count' */ 537);
            printint(n - COUNTBASE);
        } else {

            printesc(/* str 'delcode' */ 538);
            printint(n - DELCODEBASE);
        }
        printchar(/* str '=' */ 61);
        printint(eqtb[n].cint);
    }
    else if (n <= EQTBSIZE) /* comment:Show equivalent |n|, in region 6 */
    {
        if (n < SCALEDBASE)
            printlengthparam(n - DIMENBASE);
        else {

            printesc(/* str 'dimen' */ 574);
            printint(n - SCALEDBASE);
        }
        printchar(/* str '=' */ 61);
        printscaled(eqtb[n].cint);
        print(/* str 'pt' */ 312);
    }
    else printchar(/* str '?' */ 63);
}
#endif /* STAT */