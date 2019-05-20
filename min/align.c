#define EXTERN extern
#include "pdftexd.h"

void initalign(void) {
    initalign_regmem 
    halfword savecsptr;
    halfword p;
    savecsptr = curcs;
    pushalignment();
    alignstate = -1000000L;
    /* comment:Check for improper alignment in displayed math */
    if ((curlist.modefield == MMODE) && ((curlist.tailfield != curlist.headfield) || (curlist.auxfield.cint != TEXNULL))) 
    {
        
        if (interaction == ERRORSTOPMODE)
        {

        }
        if (filelineerrorstylep)
            printfileline();
        else
            printnl(/* str '! ' */ 264);

        print(/* str 'Improper ' */ 781);
        
        printesc(/* str 'halign' */ 599);
        print(/* str ' inside $$'s' */ 1304);
        {
            helpptr = 3;
            helpline[2] =
                /* str 'Displays can use special alignments (like \eqalig' */
                1305;
            helpline[1] =
                /* str 'only if nothing but the alignment itself is betwe' */
                1306;
            helpline[0] =
                /* str 'So I've deleted the formulas that preceded this a' */
                1307;
        }
        error();
        flushmath();
    }


    pushnest();
    /* comment:Change current mode to |-vmode| for \.{\\halign},  */
    if (curlist.modefield == MMODE) {
        curlist.modefield = /* @d9482@ */ -1;
        curlist.auxfield.cint = nest[nestptr - 2].auxfield.cint;
    } else if (curlist.modefield > 0)
        curlist.modefield = -(integer)curlist.modefield;
    scanspec(ALIGNGROUP, false);
    /* comment:Scan the preamble and record it in the |preamble|  */ mem
        [memtop - 8]
            .hh.v.RH = TEXNULL;
    curalign = memtop - 8;
    curloop = TEXNULL;
    scannerstatus = ALIGNING;
    warningindex = savecsptr;
    alignstate = -1000000L;
    while (true) {

        /* comment:Append the current tabskip glue to the preamble li */ mem
            [curalign]
                .hh.v.RH = newparamglue(TABSKIPCODE);
        curalign = mem[curalign].hh.v.RH;
        if (curcmd == CARRET)
            goto labinitalign30done;
        /* comment:Scan preamble text until |cur_cmd| is |tab_mark| o */
        /* comment:Scan the template \<u_j>, putting the resulting to */ p =
            memtop - 4;
        mem[p].hh.v.RH = TEXNULL;
        while (true) {

            getpreambletoken();
            if (curcmd == MACPARAM)
                goto labinitalign31done1;
            if ((curcmd <= CARRET) && (curcmd >= TABMARK) &&
                (alignstate == -1000000L)) {
                if ((p == memtop - 4) && (curloop == TEXNULL) &&
                    (curcmd == /* @d9496@ */
                     4))
                    curloop = curalign;
                else {

                    {
                        if (interaction == ERRORSTOPMODE)
                            ;
                        if (filelineerrorstylep)
                            printfileline();
                        else
                            printnl(/* str '! ' */ 264);
                        print(
                            /* str 'Missing # inserted in alignment preamble' */
                            1313);
                    }
                    {
                        helpptr = 3;
                        helpline[2] = /* str 'There should be exactly one #
                                         between &'s, when a' */
                            1314;
                        helpline[1] = /* str '\halign or \valign is being set
                                         up. In this case ' */
                            1315;
                        helpline[0] = /* str 'none, so I've put one in; maybe
                                         that will work.' */
                            1316;
                    }
                    backerror();
                    goto labinitalign31done1;
                }
            } else if ((curcmd != SPACER) || (p != memtop - 4)) {
                mem[p].hh.v.RH = getavail();
                p = mem[p].hh.v.RH;
                mem[p].hh.v.LH = curtok;
            }
        }
    labinitalign31done1:;
        mem[curalign].hh.v.RH = newnullbox();
        curalign = mem[curalign].hh.v.RH;
        mem[curalign].hh.v.LH = memtop - 9;
        mem[curalign + WIDTHOFFSET].cint = -1073741824L;
        mem[curalign + HEIGHTOFFSET].cint = mem[memtop - 4].hh.v.RH;
        /* comment:Scan the template \<v_j>, putting the resulting to */ p =
            memtop - 4;
        mem[p].hh.v.RH = TEXNULL;
        while (true) {

        labinitalign22continue:
            getpreambletoken();
            if ((curcmd <= CARRET) && (curcmd >= TABMARK) &&
                (alignstate == -1000000L))
                goto labinitalign32done2;
            if (curcmd == MACPARAM) {
                {
                    if (interaction == ERRORSTOPMODE)
                        ;
                    if (filelineerrorstylep)
                        printfileline();
                    else
                        printnl(/* str '! ' */ 264);
                    print(/* str 'Only one # is allowed per tab' */ 1317);
                }
                {
                    helpptr = 3;
                    helpline[2] = /* str 'There should be exactly one # between
                                     &'s, when a' */
                        1314;
                    helpline[1] = /* str '\halign or \valign is being set up. In
                                     this case ' */
                        1315;
                    helpline[0] = /* str 'more than one, so I'm ignoring all but
                                     the first.' */
                        1318;
                }
                error();
                goto labinitalign22continue;
            }
            mem[p].hh.v.RH = getavail();
            p = mem[p].hh.v.RH;
            mem[p].hh.v.LH = curtok;
        }
    labinitalign32done2:
        mem[p].hh.v.RH = getavail();
        p = mem[p].hh.v.RH;
        mem[p].hh.v.LH = /* @d9522@ */ 19614;
        mem[curalign + DEPTHOFFSET].cint = mem[memtop - 4].hh.v.RH;
    }
labinitalign30done:
    scannerstatus = NORMAL;
    newsavelevel(ALIGNGROUP);
    if (eqtb[EVERYCRLOC].hh.v.RH != TEXNULL)
        begintokenlist(eqtb[EVERYCRLOC].hh.v.RH, EVERYCRTEXT);
    alignpeek();
}

void pushalignment(void) {
    pushalignment_regmem halfword p;
    p = getnode(ALIGNSTACKNODESIZE);
    mem[p].hh.v.RH = alignptr;
    mem[p].hh.v.LH = curalign;
    mem[p + 1].hh.v.LH = mem[memtop - 8].hh.v.RH;
    mem[p + 1].hh.v.RH = curspan;
    mem[p + 2].cint = curloop;
    mem[p + 3].cint = alignstate;
    mem[p + 4].hh.v.LH = curhead;
    mem[p + 4].hh.v.RH = curtail;
    mem[p + 5].hh.v.LH = curprehead;
    mem[p + 5].hh.v.RH = curpretail;
    alignptr = p;
    curhead = getavail();
    curprehead = getavail();
}
void popalignment(void) {
    popalignment_regmem halfword p;
    {
        mem[curhead].hh.v.RH = avail;
        avail = curhead;
        mem[curhead].hh.me = 0;
        ;
#ifdef STAT
        decr(dynused);
#endif /* STAT */
    }
    {
        mem[curprehead].hh.v.RH = avail;
        avail = curprehead;
        mem[curprehead].hh.me = 0;
        ;
#ifdef STAT
        decr(dynused);
#endif /* STAT */
    }
    p = alignptr;
    curtail = mem[p + 4].hh.v.RH;
    curhead = mem[p + 4].hh.v.LH;
    curpretail = mem[p + 5].hh.v.RH;
    curprehead = mem[p + 5].hh.v.LH;
    alignstate = mem[p + 3].cint;
    curloop = mem[p + 2].cint;
    curspan = mem[p + 1].hh.v.RH;
    mem[memtop - 8].hh.v.RH = mem[p + 1].hh.v.LH;
    curalign = mem[p].hh.v.LH;
    alignptr = mem[p].hh.v.RH;
    freenode(p, ALIGNSTACKNODESIZE);
}
/* comment:Declare the procedure called |get_preamble_token| */ 
void
getpreambletoken(void) {
    getpreambletoken_regmem labgetpreambletoken20restart : gettoken();
    while ((curchr == SPANCODE) && (curcmd == TABMARK)) {

        gettoken();
        if (curcmd > MAXCOMMAND) {
            expand();
            gettoken();
        }
    }
    if (curcmd == ENDV)
        fatalerror(
            /* str '(interwoven alignment preambles are not allowed)' */ 679);
    if ((curcmd == ASSIGNGLUE) &&
        (curchr == /* @d9454@ */ /* @d9455@ */ 26639)) {
        scanoptionalequals();
        scanglue(GLUEVAL);
        if (eqtb[INTBASE + GLOBALDEFSCODE].cint > 0)
            geqdefine(/* @d9459@ */ /* @d9460@ */ 26639, GLUEREF, curval);
        else
            eqdefine(/* @d9462@ */ /* @d9463@ */ 26639, GLUEREF, curval);
        goto labgetpreambletoken20restart;
    }
}

/* comment:Declare the procedure called |init_span| */ 
void
zinitspan(halfword p) {
    initspan_regmem pushnest();
    if (curlist.modefield == /* @d9531@ */ -104)
        curlist.auxfield.hh.v.LH = 1000;
    else {

        curlist.auxfield.cint = eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint;
        normalparagraph();
    }
    curspan = p;
}


void initrow(void) {
    initrow_regmem pushnest();
    curlist.modefield = (/* @d9534@ */ /* @d9535@ */ -105) - curlist.modefield;
    if (curlist.modefield == /* @d9536@ */ -104)
        curlist.auxfield.hh.v.LH = 0;
    else
        curlist.auxfield.cint = 0;
    {
        mem[curlist.tailfield].hh.v.RH =
            newglue(mem[mem[memtop - 8].hh.v.RH + 1].hh.v.LH);
        curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
    }
    mem[curlist.tailfield].hh.b1 = /* @d9537@ */ 12;
    curalign = mem[mem[memtop - 8].hh.v.RH].hh.v.RH;
    curtail = curhead;
    curpretail = curprehead;
    initspan(curalign);
}

void initcol(void) {
    initcol_regmem mem[curalign + LISTOFFSET].hh.v.LH = curcmd;
    if (curcmd == OMIT)
        alignstate = 0;
    else {

        backinput();
        begintokenlist(mem[curalign + HEIGHTOFFSET].cint, UTEMPLATE);
    }
}

boolean fincol(void) {
    register boolean Result;
    fincol_regmem halfword p;
    halfword q, r;
    halfword s;
    halfword u;
    scaled w;
    glueord o;
    halfword n;
    if (curalign == TEXNULL)
        confusion(/* str 'endv' */ 1319);
    q = mem[curalign].hh.v.RH;
    if (q == TEXNULL)
        confusion(/* str 'endv' */ 1319);
    if (alignstate < 500000L)
        fatalerror(
            /* str '(interwoven alignment preambles are not allowed)' */ 679);
    p = mem[q].hh.v.RH;
    /* comment:If the preamble list has been traversed, check tha */
    if ((p == TEXNULL) && (mem[curalign + LISTOFFSET].hh.v.LH < CRCODE)) {

        if (curloop != TEXNULL) /* comment:Lengthen the preamble periodically */
        {
            mem[q].hh.v.RH = newnullbox();
            p = mem[q].hh.v.RH;
            mem[p].hh.v.LH = memtop - 9;
            mem[p + WIDTHOFFSET].cint = -1073741824L;
            curloop = mem[curloop].hh.v.RH;
            /* comment:Copy the templates from node |cur_loop| into node  */ q =
                memtop - 4;
            r = mem[curloop + HEIGHTOFFSET].cint;
            while (r != TEXNULL) {

                mem[q].hh.v.RH = getavail();
                q = mem[q].hh.v.RH;
                mem[q].hh.v.LH = mem[r].hh.v.LH;
                r = mem[r].hh.v.RH;
            }
            mem[q].hh.v.RH = TEXNULL;
            mem[p + HEIGHTOFFSET].cint = mem[memtop - 4].hh.v.RH;
            q = memtop - 4;
            r = mem[curloop + DEPTHOFFSET].cint;
            while (r != TEXNULL) {

                mem[q].hh.v.RH = getavail();
                q = mem[q].hh.v.RH;
                mem[q].hh.v.LH = mem[r].hh.v.LH;
                r = mem[r].hh.v.RH;
            }
            mem[q].hh.v.RH = TEXNULL;
            mem[p + DEPTHOFFSET].cint = mem[memtop - 4].hh.v.RH;
            curloop = mem[curloop].hh.v.RH;
            mem[p].hh.v.RH = newglue(mem[curloop + 1].hh.v.LH);
        } else {

            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(
                    /* str 'Extra alignment tab has been changed to ' */ 1320);
            }
            printesc(/* str 'cr' */ 1309);
            {
                helpptr = 3;
                helpline[2] = /* str 'You have given more \span or & marks than
                                 there w' */
                    1321;
                helpline[1] = /* str 'in the preamble to the \halign or \valign
                                 now in ' */
                    1322;
                helpline[0] = /* str 'So I'll assume that you meant to type \cr
                                 instead' */
                    1323;
            }
            mem[curalign + LISTOFFSET].hh.v.LH = CRCODE;
            error();
        }
    }
    if (mem[curalign + LISTOFFSET].hh.v.LH != SPANCODE) {
        unsave();
        newsavelevel(ALIGNGROUP);
        /* comment:Package an unset box for the current column and re */ {

            if (curlist.modefield == /* @d9569@ */ -104) {
                adjusttail = curtail;
                preadjusttail = curpretail;
                u = hpack(mem[curlist.headfield].hh.v.RH, 0, ADDITIONAL);
                w = mem[u + WIDTHOFFSET].cint;
                curtail = adjusttail;
                adjusttail = TEXNULL;
                curpretail = preadjusttail;
                preadjusttail = TEXNULL;
            } else {

                u = vpackage(mem[curlist.headfield].hh.v.RH, 0, ADDITIONAL, 0);
                w = mem[u + HEIGHTOFFSET].cint;
            }
            n = MINQUARTERWORD;
            if (curspan !=
                curalign) /* comment:Update width entry for spanned columns */
            {
                q = curspan;
                do {
                    incr(n);
                    q = mem[mem[q].hh.v.RH].hh.v.RH;
                } while (!(q == curalign));
                if (n > MAXQUARTERWORD)
                    confusion(/* str '256 spans' */ 1324);
                q = curspan;
                while (mem[mem[q].hh.v.LH].hh.v.RH < n)
                    q = mem[q].hh.v.LH;
                if (mem[mem[q].hh.v.LH].hh.v.RH > n) {
                    s = getnode(SPANNODESIZE);
                    mem[s].hh.v.LH = mem[q].hh.v.LH;
                    mem[s].hh.v.RH = n;
                    mem[q].hh.v.LH = s;
                    mem[s + WIDTHOFFSET].cint = w;
                } else if (mem[mem[q].hh.v.LH /* @d9580@ */ + 1].cint < w)
                    mem[mem[q].hh.v.LH /* @d9581@ */ + 1].cint = w;
            } else if (w > mem[curalign + WIDTHOFFSET].cint)
                mem[curalign + WIDTHOFFSET].cint = w;
            mem[u].hh.b0 = UNSETNODE;
            mem[u].hh.b1 = n;
            /* comment:Determine the stretch order */
            if (totalstretch[FILLL] != 0)
                o = FILLL;
            else if (totalstretch[FILL] != 0)
                o = FILL;
            else if (totalstretch[FIL] != 0)
                o = FIL;
            else
                o = NORMAL;
            mem[u + LISTOFFSET].hh.b1 = o;
            mem[u + GLUEOFFSET].cint = totalstretch[o];
            /* comment:Determine the shrink order */
            if (totalshrink[FILLL] != 0)
                o = FILLL;
            else if (totalshrink[FILL] != 0)
                o = FILL;
            else if (totalshrink[FIL] != 0)
                o = FIL;
            else
                o = NORMAL;
            mem[u + LISTOFFSET].hh.b0 = o;
            mem[u + 4].cint = totalshrink[o];
            popnest();
            mem[curlist.tailfield].hh.v.RH = u;
            curlist.tailfield = u;
        }
        /* comment:Copy the tabskip glue between columns */ {

            mem[curlist.tailfield].hh.v.RH =
                newglue(mem[mem[curalign].hh.v.RH + 1].hh.v.LH);
            curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
        }
        mem[curlist.tailfield].hh.b1 = /* @d9605@ */ 12;
        if (mem[curalign + LISTOFFSET].hh.v.LH >= CRCODE) {
            Result = true;
            return Result;
        }
        initspan(p);
    }
    alignstate = 1000000L;
    do {
        getxorprotected();
    } while (!(curcmd != SPACER));
    curalign = p;
    initcol();
    Result = false;
    return Result;
}

void finrow(void) {
    finrow_regmem halfword p;
    if (curlist.modefield == /* @d9611@ */ -104) {
        p = hpack(mem[curlist.headfield].hh.v.RH, 0, ADDITIONAL);
        popnest();
        if (curprehead != curpretail) {
            mem[curlist.tailfield].hh.v.RH = mem[curprehead].hh.v.RH;
            curlist.tailfield = curpretail;
        }
        appendtovlist(p);
        if (curhead != curtail) {
            mem[curlist.tailfield].hh.v.RH = mem[curhead].hh.v.RH;
            curlist.tailfield = curtail;
        }
    } else {

        p = vpackage(mem[curlist.headfield].hh.v.RH, 0, ADDITIONAL,
                     1073741823L);
        popnest();
        mem[curlist.tailfield].hh.v.RH = p;
        curlist.tailfield = p;
        curlist.auxfield.hh.v.LH = 1000;
    }
    mem[p].hh.b0 = UNSETNODE;
    mem[p + GLUEOFFSET].cint = 0;
    if (eqtb[EVERYCRLOC].hh.v.RH != TEXNULL)
        begintokenlist(eqtb[EVERYCRLOC].hh.v.RH, EVERYCRTEXT);
    alignpeek();
}

void finalign(void) {
    finalign_regmem halfword p, q, r, s, u, v;
    scaled t, w;
    scaled o;
    halfword n;
    scaled rulesave;
    memoryword auxsave;
    if (curgroup != ALIGNGROUP)
        confusion(/* str 'align1' */ 1325);
    unsave();
    if (curgroup != ALIGNGROUP)
        confusion(/* str 'align0' */ 1326);
    unsave();
    if (nest[nestptr - 1].modefield == MMODE)
        o = eqtb[DIMENBASE + DISPLAYINDENTCODE].cint;
    else
        o = 0;
    /* comment:Go through the preamble list, determining the colu */ q =
        mem[mem[memtop - 8].hh.v.RH].hh.v.RH;
    do {
        flushlist(mem[q + HEIGHTOFFSET].cint);
        flushlist(mem[q + DEPTHOFFSET].cint);
        p = mem[mem[q].hh.v.RH].hh.v.RH;
        if (mem[q + WIDTHOFFSET].cint ==
            -1073741824L) /* comment:Nullify |width(q)| and the tabskip glue
                             following  */
        {
            mem[q + WIDTHOFFSET].cint = 0;
            r = mem[q].hh.v.RH;
            s = mem[r + 1].hh.v.LH;
            if (s != membot) {
                incr(mem[membot].hh.v.RH);
                deleteglueref(s);
                mem[r + 1].hh.v.LH = membot;
            }
        }
        if (mem[q].hh.v.LH != memtop - 9) /* comment:Merge the widths in the
                                             span nodes of |q| with tho */
        {
            t = mem[q + WIDTHOFFSET].cint +
                mem[mem[mem[q].hh.v.RH + 1].hh.v.LH /* @d9634@ */ + 1].cint;
            r = mem[q].hh.v.LH;
            s = memtop - 9;
            mem[s].hh.v.LH = p;
            n = /* @d9635@ */ 1;
            do {
                mem[r + WIDTHOFFSET].cint = mem[r + WIDTHOFFSET].cint - t;
                u = mem[r].hh.v.LH;
                while (mem[r].hh.v.RH > n) {

                    s = mem[s].hh.v.LH;
                    n = mem[mem[s].hh.v.LH].hh.v.RH + 1;
                }
                if (mem[r].hh.v.RH < n) {
                    mem[r].hh.v.LH = mem[s].hh.v.LH;
                    mem[s].hh.v.LH = r;
                    decr(mem[r].hh.v.RH);
                    s = r;
                } else {

                    if (mem[r + WIDTHOFFSET].cint >
                        mem[mem[s].hh.v.LH /* @d9639@ */ + 1].cint)
                        mem[mem[s].hh.v.LH /* @d9640@ */ + 1].cint =
                            mem[r + WIDTHOFFSET].cint;
                    freenode(r, SPANNODESIZE);
                }
                r = u;
            } while (!(r == memtop - 9));
        }
        mem[q].hh.b0 = UNSETNODE;
        mem[q].hh.b1 = MINQUARTERWORD;
        mem[q + HEIGHTOFFSET].cint = 0;
        mem[q + DEPTHOFFSET].cint = 0;
        mem[q + LISTOFFSET].hh.b1 = NORMAL;
        mem[q + LISTOFFSET].hh.b0 = NORMAL;
        mem[q + GLUEOFFSET].cint = 0;
        mem[q + 4].cint = 0;
        q = p;
    } while (!(q == TEXNULL));
    /* comment:Package the preamble list, to determine the actual */ saveptr =
        saveptr - 2;
    packbeginline = -(integer)curlist.mlfield;
    if (curlist.modefield == /* @d9653@ */ -1) {
        rulesave = eqtb[DIMENBASE + OVERFULLRULECODE].cint;
        eqtb[DIMENBASE + OVERFULLRULECODE].cint = 0;
        p = hpack(mem[memtop - 8].hh.v.RH, savestack[saveptr + 1].cint,
                  savestack[saveptr + 0].cint);
        eqtb[DIMENBASE + OVERFULLRULECODE].cint = rulesave;
    } else {

        q = mem[mem[memtop - 8].hh.v.RH].hh.v.RH;
        do {
            mem[q + HEIGHTOFFSET].cint = mem[q + WIDTHOFFSET].cint;
            mem[q + WIDTHOFFSET].cint = 0;
            q = mem[mem[q].hh.v.RH].hh.v.RH;
        } while (!(q == TEXNULL));
        p = vpackage(mem[memtop - 8].hh.v.RH, savestack[saveptr + 1].cint,
                     savestack[saveptr + 0].cint, 1073741823L);
        q = mem[mem[memtop - 8].hh.v.RH].hh.v.RH;
        do {
            mem[q + WIDTHOFFSET].cint = mem[q + HEIGHTOFFSET].cint;
            mem[q + HEIGHTOFFSET].cint = 0;
            q = mem[mem[q].hh.v.RH].hh.v.RH;
        } while (!(q == TEXNULL));
    }
    packbeginline = 0;
    /* comment:Set the glue in all the unset boxes of the current */ q =
        mem[curlist.headfield].hh.v.RH;
    s = curlist.headfield;
    while (q != TEXNULL) {

        if (!(q >= himemmin)) {

            if (mem[q].hh.b0 == UNSETNODE) /* comment:Set the unset box |q| and
                                              the unset boxes in it */
            {
                if (curlist.modefield == /* @d9669@ */ -1) {
                    mem[q].hh.b0 = HLISTNODE;
                    mem[q + WIDTHOFFSET].cint = mem[p + WIDTHOFFSET].cint;
                    if (nest[nestptr - 1].modefield == MMODE)
                        mem[q].hh.b1 = DLIST;
                } else {

                    mem[q].hh.b0 = VLISTNODE;
                    mem[q + HEIGHTOFFSET].cint = mem[p + HEIGHTOFFSET].cint;
                }
                mem[q + LISTOFFSET].hh.b1 = mem[p + LISTOFFSET].hh.b1;
                mem[q + LISTOFFSET].hh.b0 = mem[p + LISTOFFSET].hh.b0;
                mem[q + GLUEOFFSET].gr = mem[p + GLUEOFFSET].gr;
                mem[q + 4].cint = o;
                r = mem[mem[q + LISTOFFSET].hh.v.RH].hh.v.RH;
                s = mem[mem[p + LISTOFFSET].hh.v.RH].hh.v.RH;
                do {
                    /* comment:Set the glue in node |r| and change it from an
                     * uns */
                    n = mem[r].hh.b1;
                    t = mem[s + WIDTHOFFSET].cint;
                    w = t;
                    u = memtop - 4;
                    mem[r].hh.b1 = 0;
                    while (n > MINQUARTERWORD) {

                        decr(n);
                        /* comment:Append tabskip glue and an empty box to list
                         * |u|,  */
                        s = mem[s].hh.v.RH;
                        v = mem[s + 1].hh.v.LH;
                        mem[u].hh.v.RH = newglue(v);
                        u = mem[u].hh.v.RH;
                        mem[u].hh.b1 = /* @d9690@ */ 12;
                        t = t + mem[v + WIDTHOFFSET].cint;
                        if (mem[p + LISTOFFSET].hh.b0 == STRETCHING) {
                            if (mem[v].hh.b0 == mem[p + LISTOFFSET].hh.b1)
                                t = t + round(mem[p + GLUEOFFSET].gr *
                                              mem[v + 2].cint);
                        } else if (mem[p + LISTOFFSET].hh.b0 == SHRINKING) {
                            if (mem[v].hh.b1 == mem[p + LISTOFFSET].hh.b1)
                                t = t - round(mem[p + GLUEOFFSET].gr *
                                              mem[v + 3].cint);
                        }
                        s = mem[s].hh.v.RH;
                        mem[u].hh.v.RH = newnullbox();
                        u = mem[u].hh.v.RH;
                        t = t + mem[s + WIDTHOFFSET].cint;
                        if (curlist.modefield == /* @d9701@ */ -1)
                            mem[u + WIDTHOFFSET].cint =
                                mem[s + WIDTHOFFSET].cint;
                        else {

                            mem[u].hh.b0 = VLISTNODE;
                            mem[u + HEIGHTOFFSET].cint =
                                mem[s + WIDTHOFFSET].cint;
                        }
                    }
                    if (curlist.modefield ==
                        /* @d9707@ */ -1) /* comment:Make the unset node |r|
                                             into an |hlist_node| of wi */
                    {
                        mem[r + HEIGHTOFFSET].cint = mem[q + HEIGHTOFFSET].cint;
                        mem[r + DEPTHOFFSET].cint = mem[q + DEPTHOFFSET].cint;
                        if (t == mem[r + WIDTHOFFSET].cint) {
                            mem[r + LISTOFFSET].hh.b0 = NORMAL;
                            mem[r + LISTOFFSET].hh.b1 = NORMAL;
                            mem[r + GLUEOFFSET].gr = 0.0;
                        } else if (t > mem[r + WIDTHOFFSET].cint) {
                            mem[r + LISTOFFSET].hh.b0 = STRETCHING;
                            if (mem[r + GLUEOFFSET].cint == 0)
                                mem[r + GLUEOFFSET].gr = 0.0;
                            else
                                mem[r + GLUEOFFSET].gr =
                                    (t - mem[r + WIDTHOFFSET].cint) /
                                    ((double)mem[r + GLUEOFFSET].cint);
                        } else {

                            mem[r + LISTOFFSET].hh.b1 =
                                mem[r + LISTOFFSET].hh.b0;
                            mem[r + LISTOFFSET].hh.b0 = SHRINKING;
                            if (mem[r + 4].cint == 0)
                                mem[r + GLUEOFFSET].gr = 0.0;
                            else if ((mem[r + LISTOFFSET].hh.b1 == NORMAL) &&
                                     (mem[r + WIDTHOFFSET].cint - t >
                                      mem[r + 4].cint))
                                mem[r + GLUEOFFSET].gr = 1.0;
                            else
                                mem[r + GLUEOFFSET].gr =
                                    (mem[r + WIDTHOFFSET].cint - t) /
                                    ((double)mem[r + 4].cint);
                        }
                        mem[r + WIDTHOFFSET].cint = w;
                        mem[r].hh.b0 = HLISTNODE;
                    } else /* comment:Make the unset node |r| into a
                              |vlist_node| of hei */
                    {

                        mem[r + WIDTHOFFSET].cint = mem[q + WIDTHOFFSET].cint;
                        if (t == mem[r + HEIGHTOFFSET].cint) {
                            mem[r + LISTOFFSET].hh.b0 = NORMAL;
                            mem[r + LISTOFFSET].hh.b1 = NORMAL;
                            mem[r + GLUEOFFSET].gr = 0.0;
                        } else if (t > mem[r + HEIGHTOFFSET].cint) {
                            mem[r + LISTOFFSET].hh.b0 = STRETCHING;
                            if (mem[r + GLUEOFFSET].cint == 0)
                                mem[r + GLUEOFFSET].gr = 0.0;
                            else
                                mem[r + GLUEOFFSET].gr =
                                    (t - mem[r + HEIGHTOFFSET].cint) /
                                    ((double)mem[r + GLUEOFFSET].cint);
                        } else {

                            mem[r + LISTOFFSET].hh.b1 =
                                mem[r + LISTOFFSET].hh.b0;
                            mem[r + LISTOFFSET].hh.b0 = SHRINKING;
                            if (mem[r + 4].cint == 0)
                                mem[r + GLUEOFFSET].gr = 0.0;
                            else if ((mem[r + LISTOFFSET].hh.b1 == NORMAL) &&
                                     (mem[r + HEIGHTOFFSET].cint - t >
                                      mem[r + 4].cint))
                                mem[r + GLUEOFFSET].gr = 1.0;
                            else
                                mem[r + GLUEOFFSET].gr =
                                    (mem[r + HEIGHTOFFSET].cint - t) /
                                    ((double)mem[r + 4].cint);
                        }
                        mem[r + HEIGHTOFFSET].cint = w;
                        mem[r].hh.b0 = VLISTNODE;
                    }
                    mem[r + 4].cint = 0;
                    if (u != memtop - 4) {
                        mem[u].hh.v.RH = mem[r].hh.v.RH;
                        mem[r].hh.v.RH = mem[memtop - 4].hh.v.RH;
                        r = u;
                    }
                    r = mem[mem[r].hh.v.RH].hh.v.RH;
                    s = mem[mem[s].hh.v.RH].hh.v.RH;
                } while (!(r == TEXNULL));
            } else if (mem[q].hh.b0 ==
                       RULENODE) /* comment:Make the running dimensions
                                           in rule |q| extend to  */
            {
                if ((mem[q + WIDTHOFFSET].cint == -1073741824L))
                    mem[q + WIDTHOFFSET].cint = mem[p + WIDTHOFFSET].cint;
                if ((mem[q + HEIGHTOFFSET].cint == -1073741824L))
                    mem[q + HEIGHTOFFSET].cint = mem[p + HEIGHTOFFSET].cint;
                if ((mem[q + DEPTHOFFSET].cint == -1073741824L))
                    mem[q + DEPTHOFFSET].cint = mem[p + DEPTHOFFSET].cint;
                if (o != 0) {
                    r = mem[q].hh.v.RH;
                    mem[q].hh.v.RH = TEXNULL;
                    q = hpack(q, 0, ADDITIONAL);
                    mem[q + 4].cint = o;
                    mem[q].hh.v.RH = r;
                    mem[s].hh.v.RH = q;
                }
            }
        }
        s = q;
        q = mem[q].hh.v.RH;
    }
    flushnodelist(p);
    popalignment();
    /* comment:Insert the \(c)current list into its environment */ auxsave =
        curlist.auxfield;
    p = mem[curlist.headfield].hh.v.RH;
    q = curlist.tailfield;
    popnest();
    if (curlist.modefield ==
        MMODE) /* comment:Finish an alignment in a display */
    {
        doassignments();
        if (curcmd != MATHSHIFT) /* comment:Pontificate about improper
                                          alignment in display */
        {
            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(/* str 'Missing $$ inserted' */ 1588);
            }
            {
                helpptr = 2;
                helpline[1] = /* str 'Displays can use special alignments (like
                                 \eqalig' */
                    1305;
                helpline[0] = /* str 'only if nothing but the alignment itself
                                 is betwe' */
                    1306;
            }
            backerror();
        } else /* comment:Check that another \.\$ follows */ {

            getxtoken();
            if (curcmd != MATHSHIFT) {
                {
                    if (interaction == ERRORSTOPMODE)
                        ;
                    if (filelineerrorstylep)
                        printfileline();
                    else
                        printnl(/* str '! ' */ 264);
                    print(/* str 'Display math should end with $$' */ 1584);
                }
                {
                    helpptr = 2;
                    helpline[1] = /* str 'The `$' that I just saw supposedly
                                     matches a prev' */
                        1585;
                    helpline[0] = /* str 'So I shall assume that you typed `$$'
                                     both times.' */
                        1586;
                }
                backerror();
            }
        }
        flushnodelist(curlist.eTeXauxfield);
        popnest();
        {
            mem[curlist.tailfield].hh.v.RH =
                newpenalty(eqtb[INTBASE + PREDISPLAYPENALTYCODE].cint);
            curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
        }
        {
            mem[curlist.tailfield].hh.v.RH = newparamglue(ABOVEDISPLAYSKIPCODE);
            curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
        }
        mem[curlist.tailfield].hh.v.RH = p;
        if (p != TEXNULL)
            curlist.tailfield = q;
        {
            mem[curlist.tailfield].hh.v.RH =
                newpenalty(eqtb[INTBASE + POSTDISPLAYPENALTYCODE].cint);
            curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
        }
        {
            mem[curlist.tailfield].hh.v.RH = newparamglue(BELOWDISPLAYSKIPCODE);
            curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
        }
        curlist.auxfield.cint = auxsave.cint;
        resumeafterdisplay();
    } else {

        curlist.auxfield = auxsave;
        mem[curlist.tailfield].hh.v.RH = p;
        if (p != TEXNULL)
            curlist.tailfield = q;
        if (curlist.modefield == VMODE)
            buildpage();
    }
}

void alignpeek(void) {
    alignpeek_regmem 
    labalignpeek20restart : alignstate = 1000000L;
    do {
        getxorprotected();
    } while (!(curcmd != SPACER));
    if (curcmd == NOALIGN) {
        scanleftbrace();
        newsavelevel(NOALIGNGROUP);
        if (curlist.modefield == /* @d9812@ */ -1)
            normalparagraph();
    } else if (curcmd == RIGHTBRACE)
        finalign();
    else if ((curcmd == CARRET) && (curchr == CRCRCODE))
        goto labalignpeek20restart;
    else {

        initrow();
        initcol();
    }
}