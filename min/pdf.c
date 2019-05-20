#define EXTERN extern
#include "pdftexd.h"

/* comment:Declare procedures that need to be declared forwar */ void
zpdferror(strnumber t, strnumber p) {
    pdferror_regmem normalizeselector();
    {
        if (interaction == ERRORSTOPMODE)
            ;
        if (filelineerrorstylep)
            printfileline();
        else
            printnl(/* str '! ' */ 264);
        print(/* str 'pdfTeX error' */ 1021);
    }
    if (t != 0) {
        print(/* str ' (' */ 286);
        print(t);
        print(/* str ')' */ 41);
    }
    print(/* str '' */ 651);
    print(p);
    {
        if (interaction == ERRORSTOPMODE)
            interaction = SCROLLMODE;
        if (logopened)
            error();
        ;
#ifdef TEXMF_DEBUG
        if (interaction > BATCHMODE)
            debughelp();
#endif /* TEXMF_DEBUG */
        history = FATALERRORSTOP;
        jumpout();
    }
}
void zpdfwarning(strnumber t, strnumber p, boolean prependnl,
                 boolean appendnl) {
    pdfwarning_regmem if (interaction == ERRORSTOPMODE);
    if (prependnl)
        println();
    print(/* str 'pdfTeX warning' */ 1022);
    if (t != 0) {
        print(/* str ' (' */ 286);
        print(t);
        print(/* str ')' */ 41);
    }
    print(/* str '' */ 651);
    print(p);
    if (appendnl)
        println();
    if (history == SPOTLESS)
        history = WARNINGISSUED;
}
void zpdfosgetosbuf(integer s) {
    pdfosgetosbuf_regmem integer a;
    if (s > suppdfosbufsize - pdfptr)
        overflow(/* str 'PDF object stream buffer' */ 1023, pdfosbufsize);
    if (pdfptr + s > pdfosbufsize) {
        a = 0.2 * pdfosbufsize;
        if (pdfptr + s > pdfosbufsize + a)
            pdfosbufsize = pdfptr + s;
        else if (pdfosbufsize < suppdfosbufsize - a)
            pdfosbufsize = pdfosbufsize + a;
        else
            pdfosbufsize = suppdfosbufsize;
        pdfosbuf = xreallocarray(pdfosbuf, eightbits, pdfosbufsize);
        pdfbuf = pdfosbuf;
        pdfbufsize = pdfosbufsize;
    }
}
void removelastspace(void) {
    removelastspace_regmem if ((pdfptr > 0) && (pdfbuf[pdfptr - 1] == 32))
        decr(pdfptr);
}
void zpdfprintoctal(integer n) {
    pdfprintoctal_regmem unsigned char k;
    k = 0;
    do {
        dig[k] = n % 8;
        n = n / 8;
        incr(k);
    } while (!(n == 0));
    if (k == 1) {
        {{if (pdfosmode && (1 + pdfptr > pdfbufsize)) pdfosgetosbuf(1);
        else if (!pdfosmode && (1 > pdfbufsize))
            overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
        else if (!pdfosmode && (1 + pdfptr > pdfbufsize)) pdfflush();
    }
    {
        pdfbuf[pdfptr] = /* str '0' */ 48;
        incr(pdfptr);
    }
}
{
    {
        if (pdfosmode && (1 + pdfptr > pdfbufsize))
            pdfosgetosbuf(1);
        else if (!pdfosmode && (1 > pdfbufsize))
            overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
        else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
            pdfflush();
    }
    {
        pdfbuf[pdfptr] = /* str '0' */ 48;
        incr(pdfptr);
    }
}
}
if (k == 2) {
    {
        if (pdfosmode && (1 + pdfptr > pdfbufsize))
            pdfosgetosbuf(1);
        else if (!pdfosmode && (1 > pdfbufsize))
            overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
        else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
            pdfflush();
    }
    {
        pdfbuf[pdfptr] = /* str '0' */ 48;
        incr(pdfptr);
    }
}
while (k > 0) {

    decr(k);
    {
        {
            if (pdfosmode && (1 + pdfptr > pdfbufsize))
                pdfosgetosbuf(1);
            else if (!pdfosmode && (1 > pdfbufsize))
                overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
            else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                pdfflush();
        }
        {
            pdfbuf[pdfptr] = /* str '0' */ 48 + dig[k];
            incr(pdfptr);
        }
    }
}
}
void zpdfprintchar(internalfontnumber f, integer c) {
    pdfprintchar_regmem pdfmarkchar(f, c);
    if ((c <= 32) || (c == 92) || (c == 40) || (c == 41) || (c > 127)) {
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = 92;
                incr(pdfptr);
            }
        }
        pdfprintoctal(c);
    } else {

        {
            if (pdfosmode && (1 + pdfptr > pdfbufsize))
                pdfosgetosbuf(1);
            else if (!pdfosmode && (1 > pdfbufsize))
                overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
            else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                pdfflush();
        }
        {
            pdfbuf[pdfptr] = c;
            incr(pdfptr);
        }
    }
}
void zpdfprint(strnumber s) {
    pdfprint_regmem poolpointer j;
    integer c;
    j = strstart[s];
    while (j < strstart[s + 1]) {

        c = strpool[j];
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = c;
                incr(pdfptr);
            }
        }
        incr(j);
    }
}
boolean zstrinstr(strnumber s, strnumber r, integer i) {
    register boolean Result;
    strinstr_regmem poolpointer j, k;
    Result = false;
    if ((strstart[s + 1] - strstart[s]) < i + (strstart[r + 1] - strstart[r]))
        return Result;
    j = i + strstart[s];
    k = strstart[r];
    while ((j < strstart[s + 1]) && (k < strstart[r + 1])) {

        if (strpool[j] != strpool[k])
            return Result;
        incr(j);
        incr(k);
    }
    Result = true;
    return Result;
}
void zpdfprintint(longinteger n) {
    pdfprintint_regmem integer k;
    longinteger m;
    k = 0;
    if (n < 0) {
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = /* str '-' */ 45;
                incr(pdfptr);
            }
        }
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
    {
        if (pdfosmode && (k + pdfptr > pdfbufsize))
            pdfosgetosbuf(k);
        else if (!pdfosmode && (k > pdfbufsize))
            overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
        else if (!pdfosmode && (k + pdfptr > pdfbufsize))
            pdfflush();
    }
    while (k > 0) {

        decr(k);
        {
            pdfbuf[pdfptr] = /* str '0' */ 48 + dig[k];
            incr(pdfptr);
        }
    }
}
void zpdfprinttwo(integer n) {
    pdfprinttwo_regmem n = abs(n) % 100;
    {{if (pdfosmode && (1 + pdfptr > pdfbufsize)) pdfosgetosbuf(1);
    else if (!pdfosmode && (1 > pdfbufsize))
        overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
    else if (!pdfosmode && (1 + pdfptr > pdfbufsize)) pdfflush();
}
{
    pdfbuf[pdfptr] = /* str '0' */ 48 + (n / 10);
    incr(pdfptr);
}
}
{
    {
        if (pdfosmode && (1 + pdfptr > pdfbufsize))
            pdfosgetosbuf(1);
        else if (!pdfosmode && (1 > pdfbufsize))
            overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
        else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
            pdfflush();
    }
    {
        pdfbuf[pdfptr] = /* str '0' */ 48 + (n % 10);
        incr(pdfptr);
    }
}
}
strnumber ztokenstostring(halfword p) {
    register strnumber Result;
    tokenstostring_regmem if (selector == NEWSTRING) pdferror(
        /* str 'tokens' */ 1024,
        /* str 'tokens_to_string() called while selector = new_st' */ 1025);
    oldsetting = selector;
    selector = NEWSTRING;
    showtokenlist(mem[p].hh.v.RH, TEXNULL, poolsize - poolptr);
    selector = oldsetting;
    lasttokensstring = makestring();
    Result = lasttokensstring;
    return Result;
}
scaled zdividescaled(scaled s, scaled m, integer dd) {
    register scaled Result;
    dividescaled_regmem scaled q, r;
    integer sign, i;
    sign = 1;
    if (s < 0) {
        sign = -(integer)sign;
        s = -(integer)s;
    }
    if (m < 0) {
        sign = -(integer)sign;
        m = -(integer)m;
    }
    if (m == 0)
        pdferror(/* str 'arithmetic' */ 1026, /* str 'divided by zero' */ 1027);
    else if (m >= (2147483647L / 10))
        pdferror(/* str 'arithmetic' */ 1026, /* str 'number too big' */ 1028);
    q = s / m;
    r = s % m;
    {
        register integer for_end;
        i = 1;
        for_end = dd;
        if (i <= for_end)
            do {
                q = 10 * q + (10 * r) / m;
                r = (10 * r) % m;
            } while (i++ < for_end);
    }
    if (2 * r >= m) {
        incr(q);
        r = r - m;
    }
    scaledout = sign * (s - (r / tenpow[dd]));
    Result = sign * q;
    return Result;
}
scaled zroundxnoverd(scaled x, integer n, integer d) {
    register scaled Result;
    roundxnoverd_regmem boolean positive;
    nonnegativeinteger t, u, v;
    if (x >= 0)
        positive = true;
    else {

        x = -(integer)x;
        positive = false;
    }
    t = (x % 32768L) * n;
    u = (x / 32768L) * n + (t / 32768L);
    v = (u % d) * 32768L + (t % 32768L);
    if (u / d >= 32768L)
        aritherror = true;
    else
        u = 32768L * (u / d) + (v / d);
    v = v % d;
    if (2 * v >= d)
        incr(u);
    if (positive)
        Result = u;
    else
        Result = -(integer)u;
    return Result;
}
void zappenddestname(strnumber s, integer n) {
    appenddestname_regmem integer a;
    if (pdfdestnamesptr == supdestnamessize)
        overflow(/* str 'number of destination names (dest_names_size)' */ 1071,
                 destnamessize);
    if (pdfdestnamesptr == destnamessize) {
        a = 0.2 * destnamessize;
        if (destnamessize < supdestnamessize - a)
            destnamessize = destnamessize + a;
        else
            destnamessize = supdestnamessize;
        destnames = xreallocarray(destnames, destnameentry, destnamessize);
    }
    destnames[pdfdestnamesptr].objname = s;
    destnames[pdfdestnamesptr].objnum = n;
    incr(pdfdestnamesptr);
}
void zpdfcreateobj(integer t, integer i) {
    pdfcreateobj_regmem integer a, p, q;
    if (sysobjptr == supobjtabsize)
        overflow(/* str 'indirect objects table size' */ 1072, objtabsize);
    if (sysobjptr == objtabsize) {
        a = 0.2 * objtabsize;
        if (objtabsize < supobjtabsize - a)
            objtabsize = objtabsize + a;
        else
            objtabsize = supobjtabsize;
        objtab = xreallocarray(objtab, objentry, objtabsize);
    }
    incr(sysobjptr);
    objptr = sysobjptr;
    objtab[objptr].int0 = i;
    objtab[objptr].int2 = -2;
    objtab[objptr].int4 = 0;
    avlputobj(objptr, t);
    if (t == 1) {
        p = headtab[t];
        if ((p == 0) || (objtab[p].int0 < i)) {
            objtab[objptr].int1 = p;
            headtab[t] = objptr;
        } else {

            while (p != 0) {

                if (objtab[p].int0 < i)
                    goto labpdfcreateobj30done;
                q = p;
                p = objtab[p].int1;
            }
        labpdfcreateobj30done:
            objtab[q].int1 = objptr;
            objtab[objptr].int1 = p;
        }
    } else if (t != 0) {
        objtab[objptr].int1 = headtab[t];
        headtab[t] = objptr;
        if ((t == 5) && (i < 0))
            appenddestname(-(integer)objtab[objptr].int0, objptr);
    }
}
integer pdfnewobjnum(void) {
    register integer Result;
    pdfnewobjnum_regmem pdfcreateobj(0, 0);
    Result = objptr;
    return Result;
}
void zpdfosswitch(boolean pdfos) {
    pdfosswitch_regmem if (pdfos && pdfosenable) {
        if (!pdfosmode) {
            pdfopptr = pdfptr;
            pdfptr = pdfosptr;
            pdfbuf = pdfosbuf;
            pdfbufsize = pdfosbufsize;
            pdfosmode = true;
        }
    }
    else {

        if (pdfosmode) {
            pdfosptr = pdfptr;
            pdfptr = pdfopptr;
            pdfbuf = pdfopbuf;
            pdfbufsize = pdfopbufsize;
            pdfosmode = false;
        }
    }
}
void zpdfosprepareobj(integer i, integer pdfoslevel) {
    pdfosprepareobj_regmem pdfosswitch(
        (pdfoslevel > 0) && (fixedpdfobjcompresslevel >= pdfoslevel));
    if (pdfosmode) {
        if (pdfoscurobjnum == 0) {
            pdfoscurobjnum = pdfnewobjnum();
            decr(objptr);
            incr(pdfoscntr);
            pdfosobjidx = 0;
            pdfptr = 0;
        } else
            incr(pdfosobjidx);
        objtab[i].int3 = pdfosobjidx;
        objtab[i].int2 = pdfoscurobjnum;
        pdfosobjnum[pdfosobjidx] = i;
        pdfosobjoff[pdfosobjidx] = pdfptr;
    } else {

        objtab[i].int2 = (pdfgone + pdfptr);
        objtab[i].int3 = -1;
    }
}
void zpdfbeginobj(integer i, integer pdfoslevel) {
    pdfbeginobj_regmem checkpdfminorversion();
    pdfosprepareobj(i, pdfoslevel);
    eqtb[INTBASE + PDFCOMPRESSLEVELCODE].cint = 0;
    if (!pdfosmode) {
        pdfprintint(i);
        {
            pdfprint(/* str ' 0 obj' */ 1073);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
    } else if (eqtb[INTBASE + PDFCOMPRESSLEVELCODE].cint == 0) {
        pdfprint(/* str '% ' */ 1074);
        pdfprintint(i);
        {
            pdfprint(/* str ' 0 obj' */ 1073);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
    }
}
void zpdfnewobj(integer t, integer i, integer pdfos) {
    pdfnewobj_regmem pdfcreateobj(t, i);
    pdfbeginobj(objptr, pdfos);
}
void pdfendobj(void) {
    pdfendobj_regmem if (pdfosmode) {
        if (pdfosobjidx == pdfosmaxobjs - 1)
            pdfoswriteobjstream();
    }
    else {

        pdfprint(/* str 'endobj' */ 1075);
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = 10;
                incr(pdfptr);
            }
        }
    }
}
void zpdfbegindict(integer i, integer pdfoslevel) {
    pdfbegindict_regmem checkpdfminorversion();
    pdfosprepareobj(i, pdfoslevel);
    eqtb[INTBASE + PDFCOMPRESSLEVELCODE].cint = 0;
    if (!pdfosmode) {
        pdfprintint(i);
        {
            pdfprint(/* str ' 0 obj' */ 1073);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
    } else if (eqtb[INTBASE + PDFCOMPRESSLEVELCODE].cint == 0) {
        pdfprint(/* str '% ' */ 1074);
        pdfprintint(i);
        {
            pdfprint(/* str ' 0 obj' */ 1073);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
    }
    {
        pdfprint(/* str '<<' */ 1076);
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = 10;
                incr(pdfptr);
            }
        }
    }
}
void zpdfnewdict(integer t, integer i, integer pdfos) {
    pdfnewdict_regmem pdfcreateobj(t, i);
    pdfbegindict(objptr, pdfos);
}
void pdfenddict(void) {
    pdfenddict_regmem if (pdfosmode) {
        {
            pdfprint(/* str '>>' */ 1018);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
        if (pdfosobjidx == pdfosmaxobjs - 1)
            pdfoswriteobjstream();
    }
    else {

        {
            pdfprint(/* str '>>' */ 1018);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
        {
            pdfprint(/* str 'endobj' */ 1075);
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
        }
    }
}
void pdfoswriteobjstream(void) {
    pdfoswriteobjstream_regmem halfword i, j, p, q;
    if (pdfoscurobjnum == 0)
        return;
    p = pdfptr;
    i = 0;
    j = 0;
    while (i <= pdfosobjidx) {

        pdfprintint(pdfosobjnum[i]);
        pdfprint(/* str ' ' */ 32);
        pdfprintint(pdfosobjoff[i]);
        if (j == 9) {
            {
                {
                    if (pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfosgetosbuf(1);
                    else if (!pdfosmode && (1 > pdfbufsize))
                        overflow(/* str 'PDF output buffer' */ 1004,
                                 pdfopbufsize);
                    else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                        pdfflush();
                }
                {
                    pdfbuf[pdfptr] = 10;
                    incr(pdfptr);
                }
            }
            j = 0;
        } else {

            pdfprint(/* str ' ' */ 32);
            incr(j);
        }
        incr(i);
    }
    pdfbuf[pdfptr - 1] = 10;
    q = pdfptr;
    pdfbegindict(pdfoscurobjnum, 0);
    {
        pdfprint(/* str 'Type ObjStm' */ 1077);
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = 10;
                incr(pdfptr);
            }
        }
    }
    pdfprint(/* str 'N ' */ 1078);
    {
        pdfprintint(pdfosobjidx + 1);
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = 10;
                incr(pdfptr);
            }
        }
    }
    pdfprint(/* str 'First ' */ 1079);
    {
        pdfprintint(q - p);
        {
            {
                if (pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfosgetosbuf(1);
                else if (!pdfosmode && (1 > pdfbufsize))
                    overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
                else if (!pdfosmode && (1 + pdfptr > pdfbufsize))
                    pdfflush();
            }
            {
                pdfbuf[pdfptr] = 10;
                incr(pdfptr);
            }
        }
    }
    pdfbeginstream();
    {
        if (pdfosmode && (q - p + pdfptr > pdfbufsize))
            pdfosgetosbuf(q - p);
        else if (!pdfosmode && (q - p > pdfbufsize))
            overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
        else if (!pdfosmode && (q - p + pdfptr > pdfbufsize))
            pdfflush();
    }
    i = p;
    while (i < q) {

        {
            pdfbuf[pdfptr] = pdfosbuf[i];
            incr(pdfptr);
        }
        incr(i);
    }
    i = 0;
    while (i < p) {

        q = i + pdfbufsize;
        if (q > p)
            q = p;
        {
            if (pdfosmode && (q - i + pdfptr > pdfbufsize))
                pdfosgetosbuf(q - i);
            else if (!pdfosmode && (q - i > pdfbufsize))
                overflow(/* str 'PDF output buffer' */ 1004, pdfopbufsize);
            else if (!pdfosmode && (q - i + pdfptr > pdfbufsize))
                pdfflush();
        }
        while (i < q) {

            {
                pdfbuf[pdfptr] = pdfosbuf[i];
                incr(pdfptr);
            }
            incr(i);
        }
    }
    pdfendstream();
    pdfoscurobjnum = 0;
}
halfword zappendptr(halfword p, integer i) {
    register halfword Result;
    appendptr_regmem halfword q;
    Result = p;
    {
        q = avail;
        if (q == TEXNULL)
            q = getavail();
        else {

            avail = mem[q].hh.v.RH;
            mem[q].hh.v.RH = TEXNULL;
            mem[q].hh.me = curchrsig;
            ;
#ifdef STAT
            incr(dynused);
#endif /* STAT */
        }
    }
    mem[q].hh.v.LH = i;
    mem[q].hh.v.RH = TEXNULL;
    if (p == TEXNULL) {
        Result = q;
        return Result;
    }
    while (mem[p].hh.v.RH != TEXNULL)
        p = mem[p].hh.v.RH;
    mem[p].hh.v.RH = q;
    return Result;
}
halfword zpdflookuplist(halfword p, integer i) {
    register halfword Result;
    pdflookuplist_regmem Result = TEXNULL;
    while (p != TEXNULL) {

        if (mem[p].hh.v.LH == i) {
            Result = p;
            return Result;
        }
        p = mem[p].hh.v.RH;
    }
    return Result;
}
halfword zprevrightmost(halfword s, halfword e) {
    register halfword Result;
    prevrightmost_regmem halfword p;
    Result = TEXNULL;
    p = s;
    if (p == TEXNULL)
        return Result;
    while (mem[p].hh.v.RH != e) {

        p = mem[p].hh.v.RH;
        if (p == TEXNULL)
            return Result;
    }
    Result = p;
    return Result;
}
void zpdfcheckobj(integer t, integer n) {
    pdfcheckobj_regmem integer k;
    k = headtab[t];
    while ((k != 0) && (k != n))
        k = objtab[k].int1;
    if (k == 0)
        pdferror(/* str 'ext1' */ 1777,
                 /* str 'cannot find referenced object' */ 1803);
}
integer zfindobj(integer t, integer i, boolean byname) {
    register integer Result;
    findobj_regmem Result = avlfindobj(t, i, byname);
    return Result;
}
void zflushstr(strnumber s) {
    flushstr_regmem if ((s == strptr - 1)) {
        decr(strptr);
        poolptr = strstart[strptr];
    }
}
integer zgetobj(integer t, integer i, boolean byname) {
    register integer Result;
    getobj_regmem integer r;
    strnumber s;
    if (byname > 0) {
        s = tokenstostring(i);
        r = findobj(t, s, true);
    } else {

        s = 0;
        r = findobj(t, i, false);
    }
    if (r == 0) {
        if (byname > 0) {
            pdfcreateobj(t, -(integer)s);
            s = 0;
        } else
            pdfcreateobj(t, i);
        r = objptr;
        if (t == 5)
            objtab[r].int4 = TEXNULL;
    }
    if (s != 0)
        flushstr(s);
    Result = r;
    return Result;
}
integer getmicrointerval(void) {
    register integer Result;
    getmicrointerval_regmem integer s, m;
    secondsandmicros(s, m);
    if ((s - epochseconds) > 32767)
        Result = 2147483647L;
    else if ((microseconds > m))
        Result = ((s - 1 - epochseconds) * 65536L) +
                 (((m + 1000000L - microseconds) / ((double)100)) * 65536L) /
                     ((double)10000);
    else
        Result =
            ((s - epochseconds) * 65536L) +
            (((m - microseconds) / ((double)100)) * 65536L) / ((double)10000);
    return Result;
}
void zprintfontidentifier(internalfontnumber f) {
    printfontidentifier_regmem if (pdffontblink[f] == FONTBASE)
        printesc(hash[FONTIDBASE + f].v.RH);
    else printesc(hash[FONTIDBASE + pdffontblink[f]].v.RH);
    if (eqtb[INTBASE + PDFTRACINGFONTSCODE].cint > 0) {
        print(/* str ' (' */ 286);
        print(fontname[f]);
        if (fontsize[f] != fontdsize[f]) {
            print(/* str '@@' */ 64);
            printscaled(fontsize[f]);
            print(/* str 'pt' */ 312);
        }
        print(/* str ')' */ 41);
    } else if (pdffontexpandratio[f] != 0) {
        print(/* str ' (' */ 286);
        if (pdffontexpandratio[f] > 0)
            print(/* str '+' */ 43);
        printint(pdffontexpandratio[f]);
        print(/* str ')' */ 41);
    }
}