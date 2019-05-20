#define EXTERN extern
#include "pdftexd.h"


// void *xmalloc(size_t newsize)
// {
// 	void *ptr = malloc(newsize);
// 	if(!ptr)
// 	{
// 		fprintf(stderr, "Malloc Failed");
// 		abort();
// 	}
// 	memset(ptr, 0, newsize);
// 	return ptr;
// }

// void* xrealloc(void* oriptr, size_t newsize)
// {
// 	void *ptr = realloc(oriptr, newsize);
// 	if(!ptr)
// 	{
// 		fprintf(stderr, "Realloc Failed");
// 		abort();
// 	}
// 	return ptr;
// }

/* comment:Declare the procedure called |show_token_list| */ void
zshowtokenlist(integer p, integer q, integer l) {
    showtokenlist_regmem integer m, c;
    ASCIIcode matchchr;
    ASCIIcode n;
    matchchr = /* str '#' */ 35;
    n = /* str '0' */ 48;
    tally = 0;
    while ((p != TEXNULL) && (tally < l)) {

        if (p == q) /* comment:Do magic computation */
        {
            firstcount = tally;
            trickcount = tally + 1 + errorline - halferrorline;
            if (trickcount < errorline)
                trickcount = errorline;
        }
        /* comment:Display token |p|, and |return| if there are probl */
        if ((p < himemmin) || (p > memend)) {
            printesc(/* str 'CLOBBERED.' */ 314);
            return;
        }
        if (mem[p].hh.v.LH >= 4095)
            printcs(mem[p].hh.v.LH - 4095);
        else {

            m = mem[p].hh.v.LH / 256;
            c = mem[p].hh.v.LH % 256;
            if (mem[p].hh.v.LH < 0)
                printesc(/* str 'BAD.' */ 638);
            else /* comment:Display the token $(|m|,|c|)$ */
                switch (m) {
                case LEFTBRACE:
                case RIGHTBRACE:
                case MATHSHIFT:
                case TABMARK:
                case SUPMARK:
                case SUBMARK:
                case SPACER:
                case LETTER:
                case OTHERCHAR:
                    print(c);
                    break;
                case MACPARAM: {
                    print(c);
                    print(c);
                } break;
                case OUTPARAM: {
                    print(matchchr);
                    if (c <= 9)
                        printchar(/* str '0' */ c + 48);
                    else {

                        printchar(/* str '!' */ 33);
                        return;
                    }
                } break;
                case MATCH: {
                    matchchr = c;
                    print(c);
                    incr(n);
                    printchar(n);
                    if (n > /* str '9' */ 57)
                        return;
                } break;
                case ENDMATCH:
                    if (c == 0)
                        print(/* str '->' */ 639);
                    break;
                default:
                    printesc(/* str 'BAD.' */ 638);
                    break;
                }
        }
        p = mem[p].hh.v.RH;
    }
    if (p != TEXNULL)
        printesc(/* str 'ETC.' */ 428);
}
/* comment:Declare the procedure called |runaway| */ void runaway(void) {
    runaway_regmem halfword p;
    if (scannerstatus > SKIPPING) {
        switch (scannerstatus) {
        case DEFINING: {
            printnl(/* str 'Runaway definition' */ 653);
            p = defref;
        } break;
        case MATCHING: {
            printnl(/* str 'Runaway argument' */ 654);
            p = memtop - 3;
        } break;
        case ALIGNING: {
            printnl(/* str 'Runaway preamble' */ 655);
            p = memtop - 4;
        } break;
        case ABSORBING: {
            printnl(/* str 'Runaway text' */ 656);
            p = defref;
        } break;
        }
        printchar(/* str '?' */ 63);
        println();
        showtokenlist(mem[p].hh.v.RH, TEXNULL, errorline - 10);
    }
}
halfword getavail(void) {
    register halfword Result;
    getavail_regmem halfword p;
    p = avail;
    if (p != TEXNULL)
        avail = mem[avail].hh.v.RH;
    else if (memend < memmax) {
        incr(memend);
        p = memend;
    } else {

        decr(himemmin);
        p = himemmin;
        if (himemmin <= lomemmax) {
            runaway();
            overflow(/* str 'main memory size' */ 304, memmax + 1 - memmin);
        }
    }
    mem[p].hh.v.RH = TEXNULL;
    mem[p].hh.me = curchrsig;
    ;
#ifdef STAT
    incr(dynused);
#endif /* STAT */
    Result = p;
    return Result;
}
void zflushlist(halfword p) {
    flushlist_regmem halfword q, r;
    if (p != TEXNULL) {
        r = p;
        do {
            q = r;
            mem[r].hh.me = 0;
            r = mem[r].hh.v.RH;
            ;
#ifdef STAT
            decr(dynused);
#endif /* STAT */
        } while (!(r == TEXNULL));
        mem[q].hh.v.RH = avail;
        avail = p;
    }
}
halfword zgetnode(integer s) {
     halfword Result;
    getnode_regmem halfword p;
    halfword q;
    integer r;
    integer t;
labgetnode20restart:
    p = rover;
    do {
        /* comment:Try to allocate within node |p| and its physical s */ q =
            p + mem[p].hh.v.LH;
        while ((mem[q].hh.v.RH == 2147483647L)) {

            t = mem[q + 1].hh.v.RH;
            if (q == rover)
                rover = t;
            mem[t + 1].hh.v.LH = mem[q + 1].hh.v.LH;
            mem[mem[q + 1].hh.v.LH + 1].hh.v.RH = t;
            q = q + mem[q].hh.v.LH;
        }
        r = q - s;
        if (r > p + 1) /* comment:Allocate from the top of node |p| and |goto
                          found| */
        {
            mem[p].hh.v.LH = r - p;
            rover = p;
            goto labgetnode40found;
        }
        if (r == p) {

            if (mem[p + 1].hh.v.RH !=
                p) /* comment:Allocate entire node |p| and |goto found| */
            {
                rover = mem[p + 1].hh.v.RH;
                t = mem[p + 1].hh.v.LH;
                mem[rover + 1].hh.v.LH = t;
                mem[t + 1].hh.v.RH = rover;
                goto labgetnode40found;
            }
        }
        mem[p].hh.v.LH = q - p;
        p = mem[p + 1].hh.v.RH;
    } while (!(p == rover));
    if (s == 1073741824L) {
        Result = 2147483647L;
        return Result;
    }
    if (lomemmax + 2 < himemmin) {

        if (lomemmax + 2 <=
            membot + 2147483647L) /* comment:Grow more variable-size memory and
                                     |goto restart| */
        {
            if (himemmin - lomemmax >= 1998)
                t = lomemmax + 1000;
            else
                t = lomemmax + 1 + (himemmin - lomemmax) / 2;
            p = mem[rover + 1].hh.v.LH;
            q = lomemmax;
            mem[p + 1].hh.v.RH = q;
            mem[rover + 1].hh.v.LH = q;
            if (t > membot + 2147483647L)
                t = membot + 2147483647L;
            mem[q + 1].hh.v.RH = rover;
            mem[q + 1].hh.v.LH = p;
            mem[q].hh.v.RH = 2147483647L;
            mem[q].hh.v.LH = t - lomemmax;
            lomemmax = t;
            mem[lomemmax].hh.v.RH = TEXNULL;
            mem[lomemmax].hh.v.LH = TEXNULL;
            rover = q;
            goto labgetnode20restart;
        }
    }
    overflow(/* str 'main memory size' */ 304, memmax + 1 - memmin);
labgetnode40found:
    mem[r].hh.v.RH = TEXNULL;
    ;
#ifdef STAT
    varused = varused + s;
#endif /* STAT */
    Result = r;
    return Result;
}
void zfreenode(halfword p, halfword s) {
    freenode_regmem halfword q;
    mem[p].hh.v.LH = s;
    mem[p].hh.v.RH = 2147483647L;
    q = mem[rover + 1].hh.v.LH;
    mem[p + 1].hh.v.LH = q;
    mem[p + 1].hh.v.RH = rover;
    mem[rover + 1].hh.v.LH = p;
    mem[q + 1].hh.v.RH = p;
    ;
#ifdef STAT
    varused = varused - s;
#endif /* STAT */
}
halfword newnullbox(void) {
    register halfword Result;
    newnullbox_regmem halfword p;
    p = getnode(BOXNODESIZE);
    mem[p].hh.b0 = HLISTNODE;
    mem[p].hh.b1 = MINQUARTERWORD;
    mem[p + WIDTHOFFSET].cint = 0;
    mem[p + DEPTHOFFSET].cint = 0;
    mem[p + HEIGHTOFFSET].cint = 0;
    mem[p + 4].cint = 0;
    mem[p + LISTOFFSET].hh.v.RH = TEXNULL;
    mem[p + LISTOFFSET].hh.b0 = NORMAL;
    mem[p + LISTOFFSET].hh.b1 = NORMAL;
    mem[p + GLUEOFFSET].gr = 0.0;
    Result = p;
    return Result;
}
halfword newrule(void) {
    register halfword Result;
    newrule_regmem halfword p;
    p = getnode(RULENODESIZE);
    mem[p].hh.b0 = RULENODE;
    mem[p].hh.b1 = 0;
    mem[p + WIDTHOFFSET].cint = -1073741824L;
    mem[p + DEPTHOFFSET].cint = -1073741824L;
    mem[p + HEIGHTOFFSET].cint = -1073741824L;
    Result = p;
    return Result;
}
halfword znewligature(internalfontnumber f, quarterword c, halfword q) {
    register halfword Result;
    newligature_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = LIGATURENODE;
    mem[p + 1].hh.b0 = f;
    mem[p + 1].hh.b1 = c;
    mem[p + 1].hh.v.RH = q;
    mem[p].hh.b1 = 0;
    Result = p;
    return Result;
}
halfword znewligitem(quarterword c) {
    register halfword Result;
    newligitem_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b1 = c;
    mem[p + 1].hh.v.RH = TEXNULL;
    Result = p;
    return Result;
}
halfword newdisc(void) {
    register halfword Result;
    newdisc_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = DISCNODE;
    mem[p].hh.b1 = 0;
    mem[p + 1].hh.v.LH = TEXNULL;
    mem[p + 1].hh.v.RH = TEXNULL;
    Result = p;
    return Result;
}
halfword znewmath(scaled w, smallnumber s) {
    register halfword Result;
    newmath_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = MATHNODE;
    mem[p].hh.b1 = s;
    mem[p + WIDTHOFFSET].cint = w;
    Result = p;
    return Result;
}
halfword znewspec(halfword p) {
    register halfword Result;
    newspec_regmem halfword q;
    q = getnode(GLUESPECSIZE);
    mem[q] = mem[p];
    mem[q].hh.v.RH = TEXNULL;
    mem[q + WIDTHOFFSET].cint = mem[p + WIDTHOFFSET].cint;
    mem[q + 2].cint = mem[p + 2].cint;
    mem[q + 3].cint = mem[p + 3].cint;
    Result = q;
    return Result;
}
halfword znewparamglue(smallnumber n) {
    register halfword Result;
    newparamglue_regmem halfword p;
    halfword q;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = GLUENODE;
    mem[p].hh.b1 = n + 1;
    mem[p + 1].hh.v.RH = TEXNULL;
    q = /* comment:Current |mem| equivalent of glue parameter number  */ eqtb
            [GLUEBASE + n]
                .hh.v.RH;
    mem[p + 1].hh.v.LH = q;
    incr(mem[q].hh.v.RH);
    Result = p;
    return Result;
}
halfword znewglue(halfword q) {
    register halfword Result;
    newglue_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = GLUENODE;
    mem[p].hh.b1 = NORMAL;
    mem[p + 1].hh.v.RH = TEXNULL;
    mem[p + 1].hh.v.LH = q;
    incr(mem[q].hh.v.RH);
    Result = p;
    return Result;
}
halfword znewskipparam(smallnumber n) {
    register halfword Result;
    newskipparam_regmem halfword p;
    tempptr = newspec(
        /* comment:Current |mem| equivalent of glue parameter number  */ eqtb
            [GLUEBASE + n]
                .hh.v.RH);
    p = newglue(tempptr);
    mem[tempptr].hh.v.RH = TEXNULL;
    mem[p].hh.b1 = n + 1;
    Result = p;
    return Result;
}
halfword znewkern(scaled w) {
    register halfword Result;
    newkern_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = KERNNODE;
    mem[p].hh.b1 = NORMAL;
    mem[p + WIDTHOFFSET].cint = w;
    Result = p;
    return Result;
}
halfword znewpenalty(integer m) {
    register halfword Result;
    newpenalty_regmem halfword p;
    p = getnode(SMALLNODESIZE);
    mem[p].hh.b0 = PENALTYNODE;
    mem[p].hh.b1 = 0;
    mem[p + 1].cint = m;
    Result = p;
    return Result;
}
#ifdef TEXMF_DEBUG
void zcheckmem(boolean printlocs) {
    checkmem_regmem halfword p, q;
    boolean clobbered;
    {
        register integer for_end;
        p = memmin;
        for_end = lomemmax;
        if (p <= for_end)
            do
                freearr[p] = false;
            while (p++ < for_end);
    }
    {
        register integer for_end;
        p = himemmin;
        for_end = memend;
        if (p <= for_end)
            do
                freearr[p] = false;
            while (p++ < for_end);
    }
    /* comment:Check single-word |avail| list */ p = avail;
    q = TEXNULL;
    clobbered = false;
    while (p != TEXNULL) {

        if ((p > memend) || (p < himemmin))
            clobbered = true;
        else if (freearr[p])
            clobbered = true;
        if (clobbered) {
            printnl(/* str 'AVAIL list clobbered at ' */ 305);
            printint(q);
            goto labcheckmem31done1;
        }
        freearr[p] = true;
        q = p;
        p = mem[q].hh.v.RH;
    }
labcheckmem31done1:;
    /* comment:Check variable-size |avail| list */ p = rover;
    q = TEXNULL;
    clobbered = false;
    do {
        if ((p >= lomemmax) || (p < memmin))
            clobbered = true;
        else if ((mem[p + 1].hh.v.RH >= lomemmax) ||
                 (mem[p + 1].hh.v.RH < memmin))
            clobbered = true;
        else if (!((mem[p].hh.v.RH == 2147483647L)) || (mem[p].hh.v.LH < 2) ||
                 (p + mem[p].hh.v.LH > lomemmax) ||
                 (mem[mem[p + 1].hh.v.RH + 1].hh.v.LH != p))
            clobbered = true;
        if (clobbered) {
            printnl(/* str 'Double-AVAIL list clobbered at ' */ 306);
            printint(q);
            goto labcheckmem32done2;
        }
        {
            register integer for_end;
            q = p;
            for_end = p + mem[p].hh.v.LH - 1;
            if (q <= for_end)
                do {
                    if (freearr[q]) {
                        printnl(/* str 'Doubly free location at ' */ 307);
                        printint(q);
                        goto labcheckmem32done2;
                    }
                    freearr[q] = true;
                } while (q++ < for_end);
        }
        q = p;
        p = mem[p + 1].hh.v.RH;
    } while (!(p == rover));
labcheckmem32done2:;
    /* comment:Check flags of unavailable nodes */ p = memmin;
    while (p <= lomemmax) {

        if ((mem[p].hh.v.RH == 2147483647L)) {
            printnl(/* str 'Bad flag at ' */ 308);
            printint(p);
        }
        while ((p <= lomemmax) && !freearr[p])
            incr(p);
        while ((p <= lomemmax) && freearr[p])
            incr(p);
    }
    if (printlocs) /* comment:Print newly busy locations */
    {
        printnl(/* str 'New busy locs' */ 309);
        {
            register integer for_end;
            p = memmin;
            for_end = lomemmax;
            if (p <= for_end)
                do
                    if (!freearr[p] && ((p > waslomax) || wasfree[p])) {
                        printchar(/* str ' ' */ 32);
                        printint(p);
                    }
                while (p++ < for_end);
        }
        {
            register integer for_end;
            p = himemmin;
            for_end = memend;
            if (p <= for_end)
                do
                    if (!freearr[p] &&
                        ((p < washimin) || (p > wasmemend) || wasfree[p])) {
                        printchar(/* str ' ' */ 32);
                        printint(p);
                    }
                while (p++ < for_end);
        }
    }
    {
        register integer for_end;
        p = memmin;
        for_end = lomemmax;
        if (p <= for_end)
            do
                wasfree[p] = freearr[p];
            while (p++ < for_end);
    }
    {
        register integer for_end;
        p = himemmin;
        for_end = memend;
        if (p <= for_end)
            do
                wasfree[p] = freearr[p];
            while (p++ < for_end);
    }
    wasmemend = memend;
    waslomax = lomemmax;
    washimin = himemmin;
}
#endif /* TEXMF_DEBUG */
#ifdef TEXMF_DEBUG
void zsearchmem(halfword p) {
    searchmem_regmem integer q;
    {
        register integer for_end;
        q = memmin;
        for_end = lomemmax;
        if (q <= for_end)
            do {
                if (mem[q].hh.v.RH == p) {
                    printnl(/* str 'LINK(' */ 310);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
                if (mem[q].hh.v.LH == p) {
                    printnl(/* str 'INFO(' */ 311);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
            } while (q++ < for_end);
    }
    {
        register integer for_end;
        q = himemmin;
        for_end = memend;
        if (q <= for_end)
            do {
                if (mem[q].hh.v.RH == p) {
                    printnl(/* str 'LINK(' */ 310);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
                if (mem[q].hh.v.LH == p) {
                    printnl(/* str 'INFO(' */ 311);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
            } while (q++ < for_end);
    }
    /* comment:Search |eqtb| for equivalents equal to |p| */ {
        register integer for_end;
        q = ACTIVEBASE;
        for_end = /* @d1555@ */ 27688;
        if (q <= for_end)
            do {
                if (eqtb[q].hh.v.RH == p) {
                    printnl(/* str 'EQUIV(' */ 575);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
            } while (q++ < for_end);
    }
    /* comment:Search |save_stack| for equivalents that point to  */
    if (saveptr > 0) {
        register integer for_end;
        q = 0;
        for_end = saveptr - 1;
        if (q <= for_end)
            do {
                if (savestack[q].hh.v.RH == p) {
                    printnl(/* str 'SAVE(' */ 630);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
            } while (q++ < for_end);
    }
    /* comment:Search |hyph_list| for pointers to |p| */ {
        register integer for_end;
        q = 0;
        for_end = hyphsize;
        if (q <= for_end)
            do {
                if (hyphlist[q] == p) {
                    printnl(/* str 'HYPH(' */ 1354);
                    printint(q);
                    printchar(/* str ')' */ 41);
                }
            } while (q++ < for_end);
    }
}
#endif /* TEXMF_DEBUG */



void zshownodelist(integer p) {
    shownodelist_regmem integer n;
    real g;
    if ((poolptr - strstart[strptr]) > depththreshold) {
        if (p > TEXNULL)
            print(/* str ' []' */ 319);
        return;
    }
    n = 0;
    while (p > memmin) {

        println();
        printcurrentstring();
        if (p > memend) {
            print(/* str 'Bad link, display aborted.' */ 320);
            return;
        }
        incr(n);
        if (n > breadthmax) {
            print(/* str 'etc.' */ 321);
            return;
        }
        /* comment:Display node |p| */ if ((p >= himemmin))
            printfontandchar(p);
        else
            switch (mem[p].hh.b0) {
            case HLISTNODE:
            case VLISTNODE:
            case UNSETNODE:
                /* comment:Display box |p| */ {

                    if (mem[p].hh.b0 == HLISTNODE)
                        printesc(/* str 'h' */ 104);
                    else if (mem[p].hh.b0 == VLISTNODE)
                        printesc(/* str 'v' */ 118);
                    else
                        printesc(/* str 'unset' */ 326);
                    print(/* str 'box(' */ 327);
                    printscaled(mem[p + HEIGHTOFFSET].cint);
                    printchar(/* str '+' */ 43);
                    printscaled(mem[p + DEPTHOFFSET].cint);
                    print(/* str ')x' */ 328);
                    printscaled(mem[p + WIDTHOFFSET].cint);
                    if (mem[p].hh.b0 ==
                        UNSETNODE) /* comment:Display special fields of
                                             the unset node |p| */
                    {
                        if (mem[p].hh.b1 != MINQUARTERWORD) {
                            print(/* str ' (' */ 286);
                            printint(mem[p].hh.b1 + 1);
                            print(/* str ' columns)' */ 330);
                        }
                        if (mem[p + GLUEOFFSET].cint != 0) {
                            print(/* str ', stretch ' */ 331);
                            printglue(mem[p + GLUEOFFSET].cint,
                                      mem[p + LISTOFFSET].hh.b1, 0);
                        }
                        if (mem[p + 4].cint != 0) {
                            print(/* str ', shrink ' */ 332);
                            printglue(mem[p + 4].cint,
                                      mem[p + LISTOFFSET].hh.b0, 0);
                        }
                    } else {

                        /* comment:Display the value of |glue_set(p)| */ g =
                            mem[p + GLUEOFFSET].gr;
                        if ((g != 0.0) &&
                            (mem[p + LISTOFFSET].hh.b0 != NORMAL)) {
                            print(/* str ', glue set ' */ 333);
                            if (mem[p + LISTOFFSET].hh.b0 == SHRINKING)
                                print(/* str '- ' */ 334);
                            if (fabs(g) > 20000.0) {
                                if (g > 0.0)
                                    printchar(/* str '>' */ 62);
                                else
                                    print(/* str '< -' */ 335);
                                printglue(20000 * 65536L,
                                          mem[p + LISTOFFSET].hh.b1, 0);
                            } else
                                printglue(round(65536L * g),
                                          mem[p + LISTOFFSET].hh.b1, 0);
                        }
                        if (mem[p + 4].cint != 0) {
                            print(/* str ', shifted ' */ 329);
                            printscaled(mem[p + 4].cint);
                        }
                        if ((eTeXmode == 1)) /* comment:Display if this box is
                                                never to be reversed */
                        {

                            if ((mem[p].hh.b0 == HLISTNODE) &&
                                ((mem[p].hh.b1) == DLIST))
                                print(/* str ', display' */ 2025);
                        }
                    }
                    {
                        {
                            strpool[poolptr] = /* str '.' */ 46;
                            incr(poolptr);
                        }
                        shownodelist(mem[p + LISTOFFSET].hh.v.RH);
                        decr(poolptr);
                    }
                }
                break;
            case RULENODE:
                /* comment:Display rule |p| */ {

                    printesc(/* str 'rule(' */ 336);
                    printruledimen(mem[p + HEIGHTOFFSET].cint);
                    printchar(/* str '+' */ 43);
                    printruledimen(mem[p + DEPTHOFFSET].cint);
                    print(/* str ')x' */ 328);
                    printruledimen(mem[p + WIDTHOFFSET].cint);
                }
                break;
            case INSNODE:
                /* comment:Display insertion |p| */ {

                    printesc(/* str 'insert' */ 337);
                    printint(mem[p].hh.b1);
                    print(/* str ', natural size ' */ 338);
                    printscaled(mem[p + HEIGHTOFFSET].cint);
                    print(/* str '; split(' */ 339);
                    printspec(mem[p + 4].hh.v.RH, 0);
                    printchar(/* str ',' */ 44);
                    printscaled(mem[p + DEPTHOFFSET].cint);
                    print(/* str '); float cost ' */ 340);
                    printint(mem[p + 1].cint);
                    {
                        {
                            strpool[poolptr] = /* str '.' */ 46;
                            incr(poolptr);
                        }
                        shownodelist(mem[p + 4].hh.v.LH);
                        decr(poolptr);
                    }
                }
                break;
            case WHATSITNODE:
                /* comment:Display the whatsit node |p| */ switch (
                    mem[p].hh.b1) {
                case OPENNODE: {
                    printwritewhatsit(/* str 'openout' */ 1732, p);
                    printchar(/* str '=' */ 61);
                    printfilename(mem[p + 1].hh.v.RH, mem[p + 2].hh.v.LH,
                                  mem[p + 2].hh.v.RH);
                } break;
                case WRITENODE: {
                    printwritewhatsit(/* str 'write' */ 678, p);
                    printmark(mem[p + 1].hh.v.RH);
                } break;
                case CLOSENODE:
                    printwritewhatsit(/* str 'closeout' */ 1733, p);
                    break;
                case SPECIALNODE: {
                    printesc(/* str 'special' */ 1734);
                    if (mem[p + 1].hh.b0 != 64) {
                        printchar(/* str '<' */ 60);
                        printint(mem[p + 1].hh.b0 - 64);
                        if ((mem[p + 1].hh.b0 - 64 == 2) ||
                            (mem[p + 1].hh.b0 - 64 == 3)) {
                            printchar(/* str '' */ 58);
                            printint(mem[p + 1].hh.b1 - 64);
                        }
                        printchar(/* str '>' */ 62);
                    }
                    printmark(mem[p + 1].hh.v.RH);
                } break;
                case LANGUAGENODE: {
                    printesc(/* str 'setlanguage' */ 1736);
                    printint(mem[p + 1].hh.v.RH);
                    print(/* str ' (hyphenmin ' */ 1884);
                    printint(mem[p + 1].hh.b0);
                    printchar(/* str ',' */ 44);
                    printint(mem[p + 1].hh.b1);
                    printchar(/* str ')' */ 41);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE: {
                    printesc(/* str 'pdfliteral' */ 1737);
                    switch (mem[p + 1].hh.v.LH) {
                    case 0:;
                        break;
                    case 1:
                        print(/* str ' page' */ 999);
                        break;
                    case 2:
                        print(/* str ' direct' */ 1885);
                        break;
                    default:
                        confusion(/* str 'literal2' */ 1886);
                        break;
                    }
                    printmark(mem[p + 1].hh.v.RH);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 32: {
                    printesc(/* str 'pdfcolorstack ' */ 1887);
                    printint(mem[p + 1].hh.v.RH);
                    switch (mem[p + 1].hh.v.LH) {
                    case 0:
                        print(/* str ' set ' */ 1888);
                        break;
                    case 1:
                        print(/* str ' push ' */ 1889);
                        break;
                    case 2:
                        print(/* str ' pop' */ 1890);
                        break;
                    case 3:
                        print(/* str ' current' */ 1891);
                        break;
                    default:
                        confusion(/* str 'pdfcolorstack' */ 1136);
                        break;
                    }
                    if (mem[p + 1].hh.v.LH <= 1)
                        printmark(mem[p + 2].hh.v.RH);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 33: {
                    printesc(/* str 'pdfsetmatrix' */ 1738);
                    printmark(mem[p + 1].hh.v.RH);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 34: {
                    printesc(/* str 'pdfsave' */ 1739);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 35: {
                    printesc(/* str 'pdfrestore' */ 1740);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 2: {
                    printesc(/* str 'pdfrefobj' */ 1742);
                    if (pdfmem[objtab[mem[p + 1].hh.v.LH].int4 + 1] > 0) {
                        if (pdfmem[objtab[mem[p + 1].hh.v.LH].int4 + 2] !=
                            TEXNULL) {
                            print(/* str ' attr' */ 1892);
                            printmark(
                                pdfmem[objtab[mem[p + 1].hh.v.LH].int4 + 2]);
                        }
                        print(/* str ' stream' */ 1893);
                    }
                    if (pdfmem[objtab[mem[p + 1].hh.v.LH].int4 + 3] > 0)
                        print(/* str ' file' */ 1894);
                    printmark(pdfmem[objtab[mem[p + 1].hh.v.LH].int4 + 0]);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 4: {
                    printesc(/* str 'pdfrefxform' */ 1744);
                    print(/* str '(' */ 40);
                    printscaled(pdfmem[objtab[mem[p + 4].hh.v.LH].int4 + 1]);
                    printchar(/* str '+' */ 43);
                    printscaled(pdfmem[objtab[mem[p + 4].hh.v.LH].int4 + 2]);
                    print(/* str ')x' */ 328);
                    printscaled(pdfmem[objtab[mem[p + 4].hh.v.LH].int4 + 0]);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 6: {
                    printesc(/* str 'pdfrefximage' */ 1746);
                    print(/* str '(' */ 40);
                    printscaled(pdfmem[objtab[mem[p + 4].hh.v.LH].int4 + 1]);
                    printchar(/* str '+' */ 43);
                    printscaled(pdfmem[objtab[mem[p + 4].hh.v.LH].int4 + 2]);
                    print(/* str ')x' */ 328);
                    printscaled(pdfmem[objtab[mem[p + 4].hh.v.LH].int4 + 0]);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 7: {
                    printesc(/* str 'pdfannot' */ 1747);
                    /* comment:Display <rule spec> for whatsit node created by
                     * \p */
                    print(/* str '(' */ 40);
                    printruledimen(mem[p + 2].cint);
                    printchar(/* str '+' */ 43);
                    printruledimen(mem[p + 3].cint);
                    print(/* str ')x' */ 328);
                    printruledimen(mem[p + 1].cint);
                    printmark(mem[p + 5].hh.v.LH);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 8: {
                    printesc(/* str 'pdfstartlink' */ 1748);
                    /* comment:Display <rule spec> for whatsit node created by
                     * \p */
                    print(/* str '(' */ 40);
                    printruledimen(mem[p + 2].cint);
                    printchar(/* str '+' */ 43);
                    printruledimen(mem[p + 3].cint);
                    print(/* str ')x' */ 328);
                    printruledimen(mem[p + 1].cint);
                    if (mem[p + 5].hh.v.LH != TEXNULL) {
                        print(/* str ' attr' */ 1892);
                        printmark(mem[p + 5].hh.v.LH);
                    }
                    print(/* str ' action' */ 1895);
                    if (mem[mem[p + 5].hh.v.RH].hh.b0 == 3) {
                        print(/* str ' user' */ 1896);
                        printmark(mem[mem[p + 5].hh.v.RH + 2].hh.v.LH);
                    } else {

                        if (mem[mem[p + 5].hh.v.RH + 1].hh.v.LH != TEXNULL) {
                            print(/* str ' file' */ 1894);
                            printmark(mem[mem[p + 5].hh.v.RH + 1].hh.v.LH);
                        }
                        switch (mem[mem[p + 5].hh.v.RH].hh.b0) {
                        case 1: {
                            if (mem[mem[p + 5].hh.v.RH].hh.b1 > 0) {
                                print(/* str ' goto name' */ 1897);
                                printmark(mem[mem[p + 5].hh.v.RH].hh.v.RH);
                            } else {

                                print(/* str ' goto num' */ 1898);
                                printint(mem[mem[p + 5].hh.v.RH].hh.v.RH);
                            }
                        } break;
                        case 0: {
                            print(/* str ' page' */ 999);
                            printint(mem[mem[p + 5].hh.v.RH].hh.v.RH);
                            printmark(mem[mem[p + 5].hh.v.RH + 2].hh.v.LH);
                        } break;
                        case 2: {
                            if (mem[mem[p + 5].hh.v.RH].hh.b1 > 0) {
                                print(/* str ' thread name' */ 1899);
                                printmark(mem[mem[p + 5].hh.v.RH].hh.v.RH);
                            } else {

                                print(/* str ' thread num' */ 1900);
                                printint(mem[mem[p + 5].hh.v.RH].hh.v.RH);
                            }
                        } break;
                        default:
                            pdferror(/* str 'displaying' */ 1901,
                                     /* str 'unknown action type' */ 1902);
                            break;
                        }
                    }
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 9:
                    printesc(/* str 'pdfendlink' */ 1749);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 11: {
                    printesc(/* str 'pdfdest' */ 1751);
                    if (mem[p + 5].hh.b1 > 0) {
                        print(/* str ' name' */ 1903);
                        printmark(mem[p + 5].hh.v.RH);
                    } else {

                        print(/* str ' num' */ 1904);
                        printint(mem[p + 5].hh.v.RH);
                    }
                    print(/* str ' ' */ 32);
                    switch (mem[p + 5].hh.b0) {
                    case 0: {
                        print(/* str 'xyz' */ 1847);
                        if (mem[p + 6].hh.v.LH != TEXNULL) {
                            print(/* str ' zoom' */ 1905);
                            printint(mem[p + 6].hh.v.LH);
                        }
                    } break;
                    case 5:
                        print(/* str 'fitbh' */ 1849);
                        break;
                    case 6:
                        print(/* str 'fitbv' */ 1850);
                        break;
                    case 4:
                        print(/* str 'fitb' */ 1851);
                        break;
                    case 2:
                        print(/* str 'fith' */ 1852);
                        break;
                    case 3:
                        print(/* str 'fitv' */ 1853);
                        break;
                    case 7: {
                        print(/* str 'fitr' */ 1854);
                        /* comment:Display <rule spec> for whatsit node created
                         * by \p */
                        print(/* str '(' */ 40);
                        printruledimen(mem[p + 2].cint);
                        printchar(/* str '+' */ 43);
                        printruledimen(mem[p + 3].cint);
                        print(/* str ')x' */ 328);
                        printruledimen(mem[p + 1].cint);
                    } break;
                    case 1:
                        print(/* str 'fit' */ 1855);
                        break;
                    default:
                        print(/* str 'unknown!' */ 1906);
                        break;
                    }
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 12:
                case PDFTEXFIRSTEXTENSIONCODE + 13: {
                    if (mem[p].hh.b1 == /* @d1936@ */ 18)
                        printesc(/* str 'pdfthread' */ 1752);
                    else
                        printesc(/* str 'pdfstartthread' */ 1753);
                    print(/* str '(' */ 40);
                    printruledimen(mem[p + 2].cint);
                    printchar(/* str '+' */ 43);
                    printruledimen(mem[p + 3].cint);
                    print(/* str ')x' */ 328);
                    printruledimen(mem[p + 1].cint);
                    if (mem[p + 6].hh.v.LH != TEXNULL) {
                        print(/* str ' attr' */ 1892);
                        printmark(mem[p + 6].hh.v.LH);
                    }
                    if (mem[p + 5].hh.b1 > 0) {
                        print(/* str ' name' */ 1903);
                        printmark(mem[p + 5].hh.v.RH);
                    } else {

                        print(/* str ' num' */ 1904);
                        printint(mem[p + 5].hh.v.RH);
                    }
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 14:
                    printesc(/* str 'pdfendthread' */ 1754);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 15:
                    printesc(/* str 'pdfsavepos' */ 1755);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 28:
                    printesc(/* str 'pdfsnaprefpoint' */ 1756);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 29: {
                    printesc(/* str 'pdfsnapy' */ 1757);
                    printchar(/* str ' ' */ 32);
                    printspec(mem[p + 1].hh.v.LH, 0);
                    printchar(/* str ' ' */ 32);
                    printspec(mem[p + 2].cint, 0);
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 30: {
                    printesc(/* str 'pdfsnapycomp' */ 1758);
                    printchar(/* str ' ' */ 32);
                    printint(mem[p + 1].cint);
                } break;
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
                    print(/* str 'whatsit?' */ 1907);
                    break;
                }
                break;
            case GLUENODE:
                /* comment:Display glue |p| */
                if (mem[p].hh.b1 >= ALEADERS) /* comment:Display
                                                          leaders
                                                          |p| */
                {
                    printesc(/* str '' */ 345);
                    if (mem[p].hh.b1 == CLEADERS)
                        printchar(/* str 'c' */ 99);
                    else if (mem[p].hh.b1 == XLEADERS)
                        printchar(/* str 'x' */ 120);
                    print(/* str 'leaders ' */ 346);
                    printspec(mem[p + 1].hh.v.LH, 0);
                    {
                        {
                            strpool[poolptr] = /* str '.' */ 46;
                            incr(poolptr);
                        }
                        shownodelist(mem[p + 1].hh.v.RH);
                        decr(poolptr);
                    }
                } else {

                    printesc(/* str 'glue' */ 341);
                    if (mem[p].hh.b1 != NORMAL) {
                        printchar(/* str '(' */ 40);
                        if (mem[p].hh.b1 < CONDMATHGLUE)
                            printskipparam(mem[p].hh.b1 - 1);
                        else if (mem[p].hh.b1 == CONDMATHGLUE)
                            printesc(/* str 'nonscript' */ 342);
                        else
                            printesc(/* str 'mskip' */ 343);
                        printchar(/* str ')' */ 41);
                    }
                    if (mem[p].hh.b1 != CONDMATHGLUE) {
                        printchar(/* str ' ' */ 32);
                        if (mem[p].hh.b1 < CONDMATHGLUE)
                            printspec(mem[p + 1].hh.v.LH, 0);
                        else
                            printspec(mem[p + 1].hh.v.LH, /* str 'mu' */ 344);
                    }
                }
                break;
            case MARGINKERNNODE: {
                printesc(/* str 'kern' */ 322);
                printscaled(mem[p + WIDTHOFFSET].cint);
                if (mem[p].hh.b1 == 0)
                    print(/* str ' (left margin)' */ 323);
                else
                    print(/* str ' (right margin)' */ 324);
            } break;
            case KERNNODE:
                /* comment:Display kern |p| */ if (mem[p].hh.b1 != MUGLUE) {
                    printesc(/* str 'kern' */ 322);
                    if (mem[p].hh.b1 != NORMAL)
                        printchar(/* str ' ' */ 32);
                    printscaled(mem[p + WIDTHOFFSET].cint);
                    if (mem[p].hh.b1 == ACCKERN)
                        print(/* str ' (for accent)' */ 347);
                } else {

                    printesc(/* str 'mkern' */ 348);
                    printscaled(mem[p + WIDTHOFFSET].cint);
                    print(/* str 'mu' */ 344);
                }
                break;
            case MATHNODE:
                /* comment:Display math node |p| */ if (mem[p].hh.b1 > AFTER) {
                    if (odd(mem[p].hh.b1))
                        printesc(/* str 'end' */ 349);
                    else
                        printesc(/* str 'begin' */ 350);
                    if (mem[p].hh.b1 > RCODE)
                        printchar(/* str 'R' */ 82);
                    else if (mem[p].hh.b1 > LCODE)
                        printchar(/* str 'L' */ 76);
                    else
                        printchar(/* str 'M' */ 77);
                } else {

                    printesc(/* str 'math' */ 351);
                    if (mem[p].hh.b1 == BEFORE)
                        print(/* str 'on' */ 352);
                    else
                        print(/* str 'off' */ 353);
                    if (mem[p + WIDTHOFFSET].cint != 0) {
                        print(/* str ', surrounded ' */ 354);
                        printscaled(mem[p + WIDTHOFFSET].cint);
                    }
                }
                break;
            case LIGATURENODE:
                /* comment:Display ligature |p| */ {

                    printfontandchar(p + 1);
                    print(/* str ' (ligature ' */ 355);
                    if (mem[p].hh.b1 > 1)
                        printchar(/* str '|' */ 124);
                    fontinshortdisplay = mem[p + 1].hh.b0;
                    shortdisplay(mem[p + 1].hh.v.RH);
                    if (odd(mem[p].hh.b1))
                        printchar(/* str '|' */ 124);
                    printchar(/* str ')' */ 41);
                }
                break;
            case PENALTYNODE:
                /* comment:Display penalty |p| */ {

                    printesc(/* str 'penalty ' */ 356);
                    printint(mem[p + 1].cint);
                }
                break;
            case DISCNODE:
                /* comment:Display discretionary |p| */ {

                    printesc(/* str 'discretionary' */ 357);
                    if (mem[p].hh.b1 > 0) {
                        print(/* str ' replacing ' */ 358);
                        printint(mem[p].hh.b1);
                    }
                    {
                        {
                            strpool[poolptr] = /* str '.' */ 46;
                            incr(poolptr);
                        }
                        shownodelist(mem[p + 1].hh.v.LH);
                        decr(poolptr);
                    }
                    {
                        strpool[poolptr] = /* str '|' */ 124;
                        incr(poolptr);
                    }
                    shownodelist(mem[p + 1].hh.v.RH);
                    decr(poolptr);
                }
                break;
            case MARKNODE:
                /* comment:Display mark |p| */ {

                    printesc(/* str 'mark' */ 359);
                    if (mem[p + 1].hh.v.LH != 0) {
                        printchar(/* str 's' */ 115);
                        printint(mem[p + 1].hh.v.LH);
                    }
                    printmark(mem[p + 1].hh.v.RH);
                }
                break;
            case ADJUSTNODE:
                /* comment:Display adjustment |p| */ {

                    printesc(/* str 'vadjust' */ 360);
                    if (mem[p].hh.b1 != 0)
                        print(/* str ' pre ' */ 361);
                    {
                        {
                            strpool[poolptr] = /* str '.' */ 46;
                            incr(poolptr);
                        }
                        shownodelist(mem[p + 1].cint);
                        decr(poolptr);
                    }
                }
                break;
            /* comment:Cases of |show_node_list| that arise in mlists onl */
            case STYLENODE:
                printstyle(mem[p].hh.b1);
                break;
            case CHOICENODE:
                /* comment:Display choice node |p| */ {

                    printesc(/* str 'mathchoice' */ 604);
                    {
                        strpool[poolptr] = /* str 'D' */ 68;
                        incr(poolptr);
                    }
                    shownodelist(mem[p + 1].hh.v.LH);
                    decr(poolptr);
                    {
                        strpool[poolptr] = /* str 'T' */ 84;
                        incr(poolptr);
                    }
                    shownodelist(mem[p + 1].hh.v.RH);
                    decr(poolptr);
                    {
                        strpool[poolptr] = /* str 'S' */ 83;
                        incr(poolptr);
                    }
                    shownodelist(mem[p + 2].hh.v.LH);
                    decr(poolptr);
                    {
                        strpool[poolptr] = /* str 's' */ 115;
                        incr(poolptr);
                    }
                    shownodelist(mem[p + 2].hh.v.RH);
                    decr(poolptr);
                }
                break;
            case ORDNOAD:
            case OPNOAD:
            case BINNOAD:
            case RELNOAD:
            case OPENNOAD:
            case CLOSENOAD:
            case PUNCTNOAD:
            case INNERNOAD:
            case RADICALNOAD:
            case OVERNOAD:
            case UNDERNOAD:
            case VCENTERNOAD:
            case ACCENTNOAD:
            case LEFTNOAD:
            case RIGHTNOAD:
                /* comment:Display normal noad |p| */ {

                    switch (mem[p].hh.b0) {
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
                    case OVERNOAD:
                        printesc(/* str 'overline' */ 1283);
                        break;
                    case UNDERNOAD:
                        printesc(/* str 'underline' */ 1284);
                        break;
                    case VCENTERNOAD:
                        printesc(/* str 'vcenter' */ 619);
                        break;
                    case RADICALNOAD: {
                        printesc(/* str 'radical' */ 613);
                        printdelimiter(p + 4);
                    } break;
                    case ACCENTNOAD: {
                        printesc(/* str 'accent' */ 584);
                        printfamandchar(p + 4);
                    } break;
                    case LEFTNOAD: {
                        printesc(/* str 'left' */ 1285);
                        printdelimiter(p + 1);
                    } break;
                    case RIGHTNOAD: {
                        if (mem[p].hh.b1 == NORMAL)
                            printesc(/* str 'right' */ 1286);
                        else
                            printesc(/* str 'middle' */ 1287);
                        printdelimiter(p + 1);
                    } break;
                    }
                    if (mem[p].hh.b0 < LEFTNOAD) {
                        if (mem[p].hh.b1 != NORMAL) {

                            if (mem[p].hh.b1 == LIMITS)
                                printesc(/* str 'limits' */ 1288);
                            else
                                printesc(/* str 'nolimits' */ 1289);
                        }
                        printsubsidiarydata(p + 1, /* str '.' */ 46);
                    }
                    printsubsidiarydata(p + 2, /* str '^' */ 94);
                    printsubsidiarydata(p + 3, /* str '_' */ 95);
                }
                break;
            case FRACTIONNOAD:
                /* comment:Display fraction noad |p| */ {

                    printesc(/* str 'fraction, thickness ' */ 1290);
                    if (mem[p + WIDTHOFFSET].cint == 1073741824L)
                        print(/* str '= default' */ 1291);
                    else
                        printscaled(mem[p + WIDTHOFFSET].cint);
                    if ((mem[p + 4].qqqq.b0 != 0) ||
                        (mem[p + 4].qqqq.b1 != /* @d2117@ */
                         0) ||
                        (mem[p + 4].qqqq.b2 != 0) ||
                        (mem[p + 4].qqqq.b3 != MINQUARTERWORD)) {
                        print(/* str ', left-delimiter ' */ 1292);
                        printdelimiter(p + 4);
                    }
                    if ((mem[p + 5].qqqq.b0 != 0) ||
                        (mem[p + 5].qqqq.b1 != /* @d2120@ */
                         0) ||
                        (mem[p + 5].qqqq.b2 != 0) ||
                        (mem[p + 5].qqqq.b3 != MINQUARTERWORD)) {
                        print(/* str ', right-delimiter ' */ 1293);
                        printdelimiter(p + 5);
                    }
                    printsubsidiarydata(p + 2, /* str '\' */ 92);
                    printsubsidiarydata(p + 3, /* str '' */ 47);
                }
                break;
            default:
                print(/* str 'Unknown node type!' */ 325);
                break;
            }
        p = mem[p].hh.v.RH;
    }
}
void zshowbox(halfword p) {
    showbox_regmem
        /* comment:Assign the values |depth_threshold */ depththreshold =
            eqtb[INTBASE + SHOWBOXDEPTHCODE].cint;
    breadthmax = eqtb[INTBASE + SHOWBOXBREADTHCODE].cint;
    if (breadthmax <= 0)
        breadthmax = 5;
    if (poolptr + depththreshold >= poolsize)
        depththreshold = poolsize - poolptr - 1;
    shownodelist(p);
    println();
}
void zdeletetokenref(halfword p) {
    deletetokenref_regmem if (mem[p].hh.v.LH == TEXNULL) flushlist(p);
    else decr(mem[p].hh.v.LH);
}
void zdeleteglueref(halfword p) {
    deleteglueref_regmem if (mem[p].hh.v.RH == TEXNULL)
        freenode(p, GLUESPECSIZE);
    else decr(mem[p].hh.v.RH);
}
void zflushnodelist(halfword p) {
    flushnodelist_regmem halfword q;
    while (p != TEXNULL) {

        q = mem[p].hh.v.RH;
        if ((p >= himemmin)) {
            mem[p].hh.v.RH = avail;
            avail = p;
            mem[p].hh.me = 0;
            ;
#ifdef STAT
            decr(dynused);
#endif /* STAT */
        } else {

            switch (mem[p].hh.b0) {
            case HLISTNODE:
            case VLISTNODE:
            case UNSETNODE: {
                flushnodelist(mem[p + LISTOFFSET].hh.v.RH);
                freenode(p, BOXNODESIZE);
                goto labflushnodelist30done;
            } break;
            case RULENODE: {
                freenode(p, RULENODESIZE);
                goto labflushnodelist30done;
            } break;
            case INSNODE: {
                flushnodelist(mem[p + 4].hh.v.LH);
                deleteglueref(mem[p + 4].hh.v.RH);
                freenode(p, INSNODESIZE);
                goto labflushnodelist30done;
            } break;
            case WHATSITNODE:
                /* comment:Wipe out the whatsit node |p| and |goto done| */ {

                    switch (mem[p].hh.b1) {
                    case OPENNODE:
                        freenode(p, OPENNODESIZE);
                        break;
                    case WRITENODE:
                    case SPECIALNODE: {
                        deletetokenref(mem[p + 1].hh.v.RH);
                        freenode(p, WRITENODESIZE);
                        goto labflushnodelist30done;
                    } break;
                    case CLOSENODE:
                    case LANGUAGENODE:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE: {
                        deletetokenref(mem[p + 1].hh.v.RH);
                        freenode(p, WRITENODESIZE);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 32: {
                        if (mem[p + 1].hh.v.LH <= 1) {
                            deletetokenref(mem[p + 2].hh.v.RH);
                            freenode(p, 3);
                        } else
                            freenode(p, 2);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 33: {
                        deletetokenref(mem[p + 1].hh.v.RH);
                        freenode(p, 2);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 34: {
                        freenode(p, 2);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 35: {
                        freenode(p, 2);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 2:
                        freenode(p, 2);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 4:
                        freenode(p, 5);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 6:
                        freenode(p, 5);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 7: {
                        deletetokenref(mem[p + 5].hh.v.LH);
                        freenode(p, 7);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 8: {
                        if (mem[p + 5].hh.v.LH != TEXNULL)
                            deletetokenref(mem[p + 5].hh.v.LH);
                        {
                            if (mem[mem[p + 5].hh.v.RH + 2].hh.v.RH ==
                                TEXNULL) {
                                if (mem[mem[p + 5].hh.v.RH].hh.b0 == 3)
                                    deletetokenref(
                                        mem[mem[p + 5].hh.v.RH + 2].hh.v.LH);
                                else {

                                    if (mem[mem[p + 5].hh.v.RH + 1].hh.v.LH !=
                                        TEXNULL)
                                        deletetokenref(
                                            mem[mem[p + 5].hh.v.RH + 1]
                                                .hh.v.LH);
                                    if (mem[mem[p + 5].hh.v.RH].hh.b0 == 0)
                                        deletetokenref(
                                            mem[mem[p + 5].hh.v.RH + 2]
                                                .hh.v.LH);
                                    else if (mem[mem[p + 5].hh.v.RH].hh.b1 > 0)
                                        deletetokenref(
                                            mem[mem[p + 5].hh.v.RH].hh.v.RH);
                                }
                                freenode(mem[p + 5].hh.v.RH, 3);
                            } else
                                decr(mem[mem[p + 5].hh.v.RH + 2].hh.v.RH);
                        }
                        freenode(p, 7);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 9:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 11: {
                        if (mem[p + 5].hh.b1 > 0)
                            deletetokenref(mem[p + 5].hh.v.RH);
                        freenode(p, 7);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 12:
                    case PDFTEXFIRSTEXTENSIONCODE + 13: {
                        if (mem[p + 5].hh.b1 > 0)
                            deletetokenref(mem[p + 5].hh.v.RH);
                        if (mem[p + 6].hh.v.LH != TEXNULL)
                            deletetokenref(mem[p + 6].hh.v.LH);
                        freenode(p, 7);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 14:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 15:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 28:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 29: {
                        deleteglueref(mem[p + 1].hh.v.LH);
                        freenode(p, 3);
                    } break;
                    case PDFTEXFIRSTEXTENSIONCODE + 30:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 37:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 38:
                        freenode(p, SMALLNODESIZE);
                        break;
                    case PDFTEXFIRSTEXTENSIONCODE + 39:
                        freenode(p, SMALLNODESIZE);
                        break;
                    default:
                        confusion(/* str 'ext3' */ 1909);
                        break;
                    }
                    goto labflushnodelist30done;
                }
                break;
            case GLUENODE: {
                {
                    if (mem[mem[p + 1].hh.v.LH].hh.v.RH == TEXNULL)
                        freenode(mem[p + 1].hh.v.LH, GLUESPECSIZE);
                    else
                        decr(mem[mem[p + 1].hh.v.LH].hh.v.RH);
                }
                if (mem[p + 1].hh.v.RH != TEXNULL)
                    flushnodelist(mem[p + 1].hh.v.RH);
            } break;
            case KERNNODE:
            case MATHNODE:
            case PENALTYNODE:;
                break;
            case MARGINKERNNODE: {
                {
                    mem[mem[p + 2].hh.v.LH].hh.v.RH = avail;
                    avail = mem[p + 2].hh.v.LH;
                    mem[mem[p + 2].hh.v.LH].hh.me = 0;
                    ;
#ifdef STAT
                    decr(dynused);
#endif /* STAT */
                }
                freenode(p, MARGINKERNNODESIZE);
                goto labflushnodelist30done;
            } break;
            case LIGATURENODE:
                flushnodelist(mem[p + 1].hh.v.RH);
                break;
            case MARKNODE:
                deletetokenref(mem[p + 1].hh.v.RH);
                break;
            case DISCNODE: {
                flushnodelist(mem[p + 1].hh.v.LH);
                flushnodelist(mem[p + 1].hh.v.RH);
            } break;
            case ADJUSTNODE:
                flushnodelist(mem[p + 1].cint);
                break;
            /* comment:Cases of |flush_node_list| that arise in mlists on */
            case STYLENODE: {
                freenode(p, STYLENODESIZE);
                goto labflushnodelist30done;
            } break;
            case CHOICENODE: {
                flushnodelist(mem[p + 1].hh.v.LH);
                flushnodelist(mem[p + 1].hh.v.RH);
                flushnodelist(mem[p + 2].hh.v.LH);
                flushnodelist(mem[p + 2].hh.v.RH);
                freenode(p, STYLENODESIZE);
                goto labflushnodelist30done;
            } break;
            case ORDNOAD:
            case OPNOAD:
            case BINNOAD:
            case RELNOAD:
            case OPENNOAD:
            case CLOSENOAD:
            case PUNCTNOAD:
            case INNERNOAD:
            case RADICALNOAD:
            case OVERNOAD:
            case UNDERNOAD:
            case VCENTERNOAD:
            case ACCENTNOAD: {
                if (mem[p + 1].hh.v.RH >= SUBBOX)
                    flushnodelist(mem[p + 1].hh.v.LH);
                if (mem[p + 2].hh.v.RH >= SUBBOX)
                    flushnodelist(mem[p + 2].hh.v.LH);
                if (mem[p + 3].hh.v.RH >= SUBBOX)
                    flushnodelist(mem[p + 3].hh.v.LH);
                if (mem[p].hh.b0 == RADICALNOAD)
                    freenode(p, RADICALNOADSIZE);
                else if (mem[p].hh.b0 == ACCENTNOAD)
                    freenode(p, ACCENTNOADSIZE);
                else
                    freenode(p, NOADSIZE);
                goto labflushnodelist30done;
            } break;
            case LEFTNOAD:
            case RIGHTNOAD: {
                freenode(p, NOADSIZE);
                goto labflushnodelist30done;
            } break;
            case FRACTIONNOAD: {
                flushnodelist(mem[p + 2].hh.v.LH);
                flushnodelist(mem[p + 3].hh.v.LH);
                freenode(p, FRACTIONNOADSIZE);
                goto labflushnodelist30done;
            } break;
            default:
                confusion(/* str 'flushing' */ 362);
                break;
            }
            freenode(p, SMALLNODESIZE);
        labflushnodelist30done:;
        }
        p = q;
    }
}
halfword zcopynodelist(halfword p) {
    register halfword Result;
    copynodelist_regmem halfword h;
    halfword q;
    halfword r;
    unsigned char words;
    h = getavail();
    q = h;
    while (p != TEXNULL) {

        /* comment:Make a copy of node |p| in node |r| */ words = 1;
        if ((p >= himemmin))
            r = getavail();
        else /* comment:Case statement to copy different types and set |wo */
            switch (mem[p].hh.b0) {
            case HLISTNODE:
            case VLISTNODE:
            case UNSETNODE: {
                r = getnode(BOXNODESIZE);
                mem[r + 6] = mem[p + 6];
                mem[r + 5] = mem[p + 5];
                mem[r + LISTOFFSET].hh.v.RH =
                    copynodelist(mem[p + LISTOFFSET].hh.v.RH);
                words = 5;
            } break;
            case RULENODE: {
                r = getnode(RULENODESIZE);
                words = RULENODESIZE;
            } break;
            case INSNODE: {
                r = getnode(INSNODESIZE);
                mem[r + 4] = mem[p + 4];
                incr(mem[mem[p + 4].hh.v.RH].hh.v.RH);
                mem[r + 4].hh.v.LH = copynodelist(mem[p + 4].hh.v.LH);
                words = /* @d2254@ */ 4;
            } break;
            case WHATSITNODE:
                /* comment:Make a partial copy of the whatsit node |p| and ma */
                switch (mem[p].hh.b1) {
                case OPENNODE: {
                    r = getnode(OPENNODESIZE);
                    words = OPENNODESIZE;
                } break;
                case WRITENODE:
                case SPECIALNODE: {
                    r = getnode(WRITENODESIZE);
                    incr(mem[mem[p + 1].hh.v.RH].hh.v.LH);
                    words = WRITENODESIZE;
                } break;
                case CLOSENODE:
                case LANGUAGENODE: {
                    r = getnode(SMALLNODESIZE);
                    words = SMALLNODESIZE;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE: {
                    r = getnode(WRITENODESIZE);
                    incr(mem[mem[p + 1].hh.v.RH].hh.v.LH);
                    words = WRITENODESIZE;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 32: {
                    if (mem[p + 1].hh.v.LH <= 1) {
                        r = getnode(3);
                        incr(mem[mem[p + 2].hh.v.RH].hh.v.LH);
                        words = 3;
                    } else {

                        r = getnode(2);
                        words = 2;
                    }
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 33: {
                    r = getnode(2);
                    incr(mem[mem[p + 1].hh.v.RH].hh.v.LH);
                    words = 2;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 34: {
                    r = getnode(2);
                    words = 2;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 35: {
                    r = getnode(2);
                    words = 2;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 2: {
                    r = getnode(2);
                    words = 2;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 4: {
                    r = getnode(5);
                    words = 5;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 6: {
                    r = getnode(5);
                    words = 5;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 7: {
                    r = getnode(7);
                    incr(mem[mem[p + 5].hh.v.LH].hh.v.LH);
                    words = 7;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 8: {
                    r = getnode(7);
                    mem[r + 2].cint = mem[p + 2].cint;
                    mem[r + 3].cint = mem[p + 3].cint;
                    mem[r + 1].cint = mem[p + 1].cint;
                    mem[r + 5].hh.v.LH = mem[p + 5].hh.v.LH;
                    if (mem[r + 5].hh.v.LH != TEXNULL)
                        incr(mem[mem[r + 5].hh.v.LH].hh.v.LH);
                    mem[r + 5].hh.v.RH = mem[p + 5].hh.v.RH;
                    incr(mem[mem[r + 5].hh.v.RH + 2].hh.v.RH);
                    mem[r + 6].cint = mem[p + 6].cint;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 9:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 11: {
                    r = getnode(7);
                    if (mem[p + 5].hh.b1 > 0)
                        incr(mem[mem[p + 5].hh.v.RH].hh.v.LH);
                    words = 7;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 12:
                case PDFTEXFIRSTEXTENSIONCODE + 13: {
                    r = getnode(7);
                    if (mem[p + 5].hh.b1 > 0)
                        incr(mem[mem[p + 5].hh.v.RH].hh.v.LH);
                    if (mem[p + 6].hh.v.LH != TEXNULL)
                        incr(mem[mem[p + 6].hh.v.LH].hh.v.LH);
                    words = 7;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 14:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 15:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 28:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 29: {
                    incr(mem[mem[p + 1].hh.v.LH].hh.v.RH);
                    r = getnode(3);
                    words = 3;
                } break;
                case PDFTEXFIRSTEXTENSIONCODE + 30:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 37:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 38:
                    r = getnode(SMALLNODESIZE);
                    break;
                case PDFTEXFIRSTEXTENSIONCODE + 39:
                    r = getnode(SMALLNODESIZE);
                    break;
                default:
                    confusion(/* str 'ext2' */ 1908);
                    break;
                }
                break;
            case GLUENODE: {
                r = getnode(SMALLNODESIZE);
                incr(mem[mem[p + 1].hh.v.LH].hh.v.RH);
                mem[r + 1].hh.v.LH = mem[p + 1].hh.v.LH;
                mem[r + 1].hh.v.RH = copynodelist(mem[p + 1].hh.v.RH);
            } break;
            case KERNNODE:
            case MATHNODE:
            case PENALTYNODE: {
                r = getnode(SMALLNODESIZE);
                words = SMALLNODESIZE;
            } break;
            case MARGINKERNNODE: {
                r = getnode(MARGINKERNNODESIZE);
                {
                    mem[r + 2].hh.v.LH = avail;
                    if (mem[r + 2].hh.v.LH == TEXNULL)
                        mem[r + 2].hh.v.LH = getavail();
                    else {

                        avail = mem[mem[r + 2].hh.v.LH].hh.v.RH;
                        mem[mem[r + 2].hh.v.LH].hh.v.RH = TEXNULL;
                        mem[mem[r + 2].hh.v.LH].hh.me = curchrsig;
                        ;
#ifdef STAT
                        incr(dynused);
#endif /* STAT */
                    }
                }
                mem[mem[r + 2].hh.v.LH].hh.b0 = mem[mem[p + 2].hh.v.LH].hh.b0;
                mem[mem[r + 2].hh.v.LH].hh.b1 = mem[mem[p + 2].hh.v.LH].hh.b1;
                words = SMALLNODESIZE;
            } break;
            case LIGATURENODE: {
                r = getnode(SMALLNODESIZE);
                mem[r + 1] = mem[p + 1];
                mem[r + 1].hh.v.RH = copynodelist(mem[p + 1].hh.v.RH);
            } break;
            case DISCNODE: {
                r = getnode(SMALLNODESIZE);
                mem[r + 1].hh.v.LH = copynodelist(mem[p + 1].hh.v.LH);
                mem[r + 1].hh.v.RH = copynodelist(mem[p + 1].hh.v.RH);
            } break;
            case MARKNODE: {
                r = getnode(SMALLNODESIZE);
                incr(mem[mem[p + 1].hh.v.RH].hh.v.LH);
                words = SMALLNODESIZE;
            } break;
            case ADJUSTNODE: {
                r = getnode(SMALLNODESIZE);
                mem[r + 1].cint = copynodelist(mem[p + 1].cint);
            } break;
            default:
                confusion(/* str 'copying' */ 363);
                break;
            }
        while (words > 0) {

            decr(words);
            mem[r + words] = mem[p + words];
        }
        mem[q].hh.v.RH = r;
        q = r;
        p = mem[p].hh.v.RH;
    }
    mem[q].hh.v.RH = TEXNULL;
    q = mem[h].hh.v.RH;
    {
        mem[h].hh.v.RH = avail;
        avail = h;
        mem[h].hh.me = 0;
        ;
#ifdef STAT
        decr(dynused);
#endif /* STAT */
    }
    Result = q;
    return Result;
}


void zbegintokenlist(halfword p, quarterword t) {
    begintokenlist_regmem {
        if (inputptr > maxinstack) {
            maxinstack = inputptr;
            if (inputptr == stacksize)
                overflow(/* str 'input stack size' */ 677, stacksize);
        }
        inputstack[inputptr] = curinput;
        incr(inputptr);
    }
    curinput.statefield = TOKENLIST;
    curinput.startfield = p;
    curinput.indexfield = t;
    if (t >= MACRO) {
        incr(mem[p].hh.v.LH);
        if (t == MACRO)
            curinput.limitfield = paramptr;
        else {

            curinput.locfield = mem[p].hh.v.RH;
            if (eqtb[INTBASE + TRACINGMACROSCODE].cint > 1) {
                begindiagnostic();
                printnl(/* str '' */ 345);
                switch (t) {
                case MARKTEXT:
                    printesc(/* str 'mark' */ 359);
                    break;
                case WRITETEXT:
                    printesc(/* str 'write' */ 678);
                    break;
                default:
                    printcmdchr(ASSIGNTOKS,
                                /* @d4054@ */ /* @d4055@ */ t + 27153);
                    break;
                }
                print(/* str '->' */ 639);
                tokenshow(p);
                enddiagnostic(false);
            }
        }
    } else
        curinput.locfield = p;
}
void endtokenlist(void) {
    endtokenlist_regmem if (curinput.indexfield >= BACKEDUP) {
        if (curinput.indexfield <= INSERTED)
            flushlist(curinput.startfield);
        else {

            deletetokenref(curinput.startfield);
            if (curinput.indexfield == MACRO)
                while (paramptr > curinput.limitfield) {

                    decr(paramptr);
                    flushlist(paramstack[paramptr]);
                }
        }
    }
    else if (curinput.indexfield == UTEMPLATE) {

        if (alignstate > 500000L)
            alignstate = 0;
        else
            fatalerror(
                /* str '(interwoven alignment preambles are not allowed)' */
                679);
    }
    {
        decr(inputptr);
        curinput = inputstack[inputptr];
    }
    {
        if (interrupt != 0)
            pauseforinstructions();
    }
}