#define EXTERN extern
#include "pdftexd.h"


integer zhalf(integer x) {
    register integer Result;
    half_regmem if (odd(x)) Result = (x + 1) / 2;
    else Result = x / 2;
    return Result;
}
scaled zrounddecimals(smallnumber k) {
    register scaled Result;
    rounddecimals_regmem integer a;
    a = 0;
    while (k > 0) {

        decr(k);
        a = (a + dig[k] * 131072L) / 10;
    }
    Result = (a + 1) / 2;
    return Result;
}

scaled zmultandadd(integer n, scaled x, scaled y, scaled maxanswer) {
    register scaled Result;
    multandadd_regmem if (n < 0) {
        x = -(integer)x;
        n = -(integer)n;
    }
    if (n == 0)
        Result = y;
    else if (((x <= (maxanswer - y) / n) &&
              (-(integer)x <= (maxanswer + y) / n)))
        Result = n * x + y;
    else {

        aritherror = true;
        Result = 0;
    }
    return Result;
}
scaled zxovern(scaled x, integer n) {
    register scaled Result;
    xovern_regmem boolean negative;
    negative = false;
    if (n == 0) {
        aritherror = true;
        Result = 0;
        texremainder = x;
    } else {

        if (n < 0) {
            x = -(integer)x;
            n = -(integer)n;
            negative = true;
        }
        if (x >= 0) {
            Result = x / n;
            texremainder = x % n;
        } else {

            Result = -(integer)((-(integer)x) / n);
            texremainder = -(integer)((-(integer)x) % n);
        }
    }
    if (negative)
        texremainder = -(integer)texremainder;
    return Result;
}
scaled zxnoverd(scaled x, integer n, integer d) {
    register scaled Result;
    xnoverd_regmem boolean positive;
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
    if (positive) {
        Result = u;
        texremainder = v % d;
    } else {

        Result = -(integer)u;
        texremainder = -(integer)(v % d);
    }
    return Result;
}
halfword zbadness(scaled t, scaled s) {
    register halfword Result;
    badness_regmem integer r;
    if (t == 0)
        Result = 0;
    else if (s <= 0)
        Result = INFBAD;
    else {

        if (t <= 7230584L)
            r = (t * 297) / s;
        else if (s >= 1663497L)
            r = t / (s / 297);
        else
            r = t;
        if (r > 1290)
            Result = INFBAD;
        else
            Result = (r * r * r + 131072L) / 262144L;
    }
    return Result;
}
integer zmakefrac(integer p, integer q) {
    register integer Result;
    makefrac_regmem integer f;
    integer n;
    boolean negative;
    integer becareful;
    if (p >= 0)
        negative = false;
    else {

        p = -(integer)p;
        negative = true;
    }
    if (q <= 0) {
        ;
#ifdef TEXMF_DEBUG
        if (q == 0)
            confusion(/* str '' */ 47);
#endif /* TEXMF_DEBUG */
        q = -(integer)q;
        negative = !negative;
    }
    n = p / q;
    p = p % q;
    if (n >= 8) {
        aritherror = true;
        if (negative)
            Result = TEXNULL;
        else
            Result = 2147483647L;
    } else {

        n = (n - 1) * 268435456L;
        /* comment:Compute $f=\lfloor 2^{28}(1+pq)+{1\over2}\rfloor$ */ f = 1;
        do {
            becareful = p - q;
            p = becareful + p;
            if (p >= 0)
                f = f + f + 1;
            else {

                f = f + f;
                p = p + q;
            }
        } while (!(f >= 268435456L));
        becareful = p - q;
        if (becareful + p >= 0)
            incr(f);
        if (negative)
            Result = -(integer)(f + n);
        else
            Result = f + n;
    }
    return Result;
}
integer ztakefrac(integer q, integer f) {
    register integer Result;
    takefrac_regmem integer p;
    boolean negative;
    integer n;
    integer becareful;
    /* comment:Reduce to the case that |f>=0| and |q>0| */ if (f >= 0)
        negative = false;
    else {

        f = -(integer)f;
        negative = true;
    }
    if (q < 0) {
        q = -(integer)q;
        negative = !negative;
    }
    if (f < 268435456L)
        n = 0;
    else {

        n = f / 268435456L;
        f = f % 268435456L;
        if (q <= 2147483647L / n)
            n = n * q;
        else {

            aritherror = true;
            n = 2147483647L;
        }
    }
    f = f + 268435456L;
    /* comment:Compute $p=\lfloor qf2^{28}+{1\over2}\rfloor-q$ */ p =
        134217728L;
    if (q < 1073741824L)
        do {
            if (odd(f))
                p = (p + q) / 2;
            else
                p = (p) / 2;
            f = (f) / 2;
        } while (!(f == 1));
    else
        do {
            if (odd(f))
                p = p + (q - p) / 2;
            else
                p = (p) / 2;
            f = (f) / 2;
        } while (!(f == 1));
    becareful = n - 2147483647L;
    if (becareful + p > 0) {
        aritherror = true;
        n = 2147483647L - p;
    }
    if (negative)
        Result = -(integer)(n + p);
    else
        Result = n + p;
    return Result;
}
integer zmlog(integer x) {
    register integer Result;
    mlog_regmem integer y, z;
    integer k;
    if (x <= 0) /* comment:Handle non-positive logarithm */
    {
        {
            if (interaction == ERRORSTOPMODE)
                ;
            if (filelineerrorstylep)
                printfileline();
            else
                printnl(/* str '! ' */ 264);
            print(/* str 'Logarithm of ' */ 300);
        }
        printscaled(x);
        print(/* str ' has been replaced by 0' */ 301);
        {
            helpptr = 2;
            helpline[1] =
                /* str 'Since I don't take logs of non-positive numbers,' */
                302;
            helpline[0] =
                /* str 'I'm zeroing this one. Proceed, with fingers cross' */
                303;
        }
        error();
        Result = 0;
    } else {

        y = 1302456860L;
        z = 6581195L;
        while (x < 1073741824L) {

            x = x + x;
            y = y - 93032639L;
            z = z - 48782L;
        }
        y = y + (z / 65536L);
        k = 2;
        while (x > 1073741828L) /* comment:Increase |k| until |x| can be
                                   multiplied by a fact */
        {

            z = ((x - 1) / twotothe[k]) + 1;
            while (x < 1073741824L + z) {

                z = (z + 1) / 2;
                k = k + 1;
            }
            y = y + speclog[k];
            x = x - z;
        }
        Result = y / 8;
    }
    return Result;
}
integer zabvscd(integer a, integer b, integer c, integer d) {
    register integer Result;
    abvscd_regmem integer q, r;
    /* comment:Reduce to the case that |a,c>=0|, |b,d>0| */ if (a < 0) {
        a = -(integer)a;
        b = -(integer)b;
    }
    if (c < 0) {
        c = -(integer)c;
        d = -(integer)d;
    }
    if (d <= 0) {
        if (b >= 0) {

            if (((a == 0) || (b == 0)) && ((c == 0) || (d == 0))) {
                Result = 0;
                return Result;
            } else {

                Result = 1;
                return Result;
            }
        }
        if (d == 0) {

            if (a == 0) {
                Result = 0;
                return Result;
            } else {

                Result = -1;
                return Result;
            }
        }
        q = a;
        a = c;
        c = q;
        q = -(integer)b;
        b = -(integer)d;
        d = q;
    } else if (b <= 0) {
        if (b < 0) {

            if (a > 0) {
                Result = -1;
                return Result;
            }
        }
        if (c == 0) {
            Result = 0;
            return Result;
        } else {

            Result = -1;
            return Result;
        }
    }
    while (true) {

        q = a / d;
        r = c / b;
        if (q != r) {

            if (q > r) {
                Result = 1;
                return Result;
            } else {

                Result = -1;
                return Result;
            }
        }
        q = a % d;
        r = c % b;
        if (r == 0) {

            if (q == 0) {
                Result = 0;
                return Result;
            } else {

                Result = 1;
                return Result;
            }
        }
        if (q == 0) {
            Result = -1;
            return Result;
        }
        a = b;
        b = q;
        c = d;
        d = r;
    }
    return Result;
}
void newrandoms(void) {
    newrandoms_regmem unsigned char k;
    integer x;
    {
        register integer for_end;
        k = 0;
        for_end = 23;
        if (k <= for_end)
            do {
                x = randoms[k] - randoms[k + 31];
                if (x < 0)
                    x = x + 268435456L;
                randoms[k] = x;
            } while (k++ < for_end);
    }
    {
        register integer for_end;
        k = 24;
        for_end = 54;
        if (k <= for_end)
            do {
                x = randoms[k] - randoms[k - 24];
                if (x < 0)
                    x = x + 268435456L;
                randoms[k] = x;
            } while (k++ < for_end);
    }
    jrandom = 54;
}
void zinitrandoms(integer seed) {
    initrandoms_regmem integer j, jj, k;
    unsigned char i;
    j = abs(seed);
    while (j >= 268435456L)
        j = (j) / 2;
    k = 1;
    {
        register integer for_end;
        i = 0;
        for_end = 54;
        if (i <= for_end)
            do {
                jj = k;
                k = j - k;
                j = jj;
                if (k < 0)
                    k = k + 268435456L;
                randoms[(i * 21) % 55] = j;
            } while (i++ < for_end);
    }
    newrandoms();
    newrandoms();
    newrandoms();
}
integer zunifrand(integer x) {
    register integer Result;
    unifrand_regmem integer y;
    if (jrandom == 0)
        newrandoms();
    else
        decr(jrandom);
    y = takefrac(abs(x), randoms[jrandom]);
    if (y == abs(x))
        Result = 0;
    else if (x > 0)
        Result = y;
    else
        Result = -(integer)y;
    return Result;
}
integer normrand(void) {
    register integer Result;
    normrand_regmem integer x, u, l;
    do {
        do {
            if (jrandom == 0)
                newrandoms();
            else
                decr(jrandom);
            x = takefrac(112429L, randoms[jrandom] - 134217728L);
            if (jrandom == 0)
                newrandoms();
            else
                decr(jrandom);
            u = randoms[jrandom];
        } while (!(abs(x) < u));
        x = makefrac(x, u);
        l = 139548960L - mlog(u);
    } while (!(abvscd(1024, l, x, x) >= 0));
    Result = x;
    return Result;
}
