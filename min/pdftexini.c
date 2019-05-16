#define EXTERN extern
#include "pdftexd.h"

void initialize(void) {
    initialize_regmem
        /* comment:Local variables for initialization */ integer i;
    integer k;
    hyphpointer z;
    /* comment:Initialize whatever \TeX\ might access */
    /* comment:Set initial values of key variables */ xchr[32] = ' ';
    xchr[33] = '!';
    xchr[34] = '"';
    xchr[35] = '#';
    xchr[36] = '$';
    xchr[37] = '%';
    xchr[38] = '&';
    xchr[39] = '\'';
    xchr[40] = '(';
    xchr[41] = ')';
    xchr[42] = '*';
    xchr[43] = '+';
    xchr[44] = ',';
    xchr[45] = '-';
    xchr[46] = '.';
    xchr[47] = '/';
    xchr[48] = '0';
    xchr[49] = '1';
    xchr[50] = '2';
    xchr[51] = '3';
    xchr[52] = '4';
    xchr[53] = '5';
    xchr[54] = '6';
    xchr[55] = '7';
    xchr[56] = '8';
    xchr[57] = '9';
    xchr[58] = ':';
    xchr[59] = ';';
    xchr[60] = '<';
    xchr[61] = '=';
    xchr[62] = '>';
    xchr[63] = '?';
    xchr[64] = '@';
    xchr[65] = 'A';
    xchr[66] = 'B';
    xchr[67] = 'C';
    xchr[68] = 'D';
    xchr[69] = 'E';
    xchr[70] = 'F';
    xchr[71] = 'G';
    xchr[72] = 'H';
    xchr[73] = 'I';
    xchr[74] = 'J';
    xchr[75] = 'K';
    xchr[76] = 'L';
    xchr[77] = 'M';
    xchr[78] = 'N';
    xchr[79] = 'O';
    xchr[80] = 'P';
    xchr[81] = 'Q';
    xchr[82] = 'R';
    xchr[83] = 'S';
    xchr[84] = 'T';
    xchr[85] = 'U';
    xchr[86] = 'V';
    xchr[87] = 'W';
    xchr[88] = 'X';
    xchr[89] = 'Y';
    xchr[90] = 'Z';
    xchr[91] = '[';
    xchr[92] = '\\';
    xchr[93] = ']';
    xchr[94] = '^';
    xchr[95] = '_';
    xchr[96] = '`';
    xchr[97] = 'a';
    xchr[98] = 'b';
    xchr[99] = 'c';
    xchr[100] = 'd';
    xchr[101] = 'e';
    xchr[102] = 'f';
    xchr[103] = 'g';
    xchr[104] = 'h';
    xchr[105] = 'i';
    xchr[106] = 'j';
    xchr[107] = 'k';
    xchr[108] = 'l';
    xchr[109] = 'm';
    xchr[110] = 'n';
    xchr[111] = 'o';
    xchr[112] = 'p';
    xchr[113] = 'q';
    xchr[114] = 'r';
    xchr[115] = 's';
    xchr[116] = 't';
    xchr[117] = 'u';
    xchr[118] = 'v';
    xchr[119] = 'w';
    xchr[120] = 'x';
    xchr[121] = 'y';
    xchr[122] = 'z';
    xchr[123] = '{';
    xchr[124] = '|';
    xchr[125] = '}';
    xchr[126] = '~';
    {
        register integer for_end;
        i = 0;
        for_end = 31;
        if (i <= for_end)
            do
                xchr[i] = i;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 127;
        for_end = 255;
        if (i <= for_end)
            do
                xchr[i] = i;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 0;
        for_end = 255;
        if (i <= for_end)
            do
                mubyteread[i] = TEXNULL;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 0;
        for_end = 255;
        if (i <= for_end)
            do
                mubytewrite[i] = 0;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 0;
        for_end = 127;
        if (i <= for_end)
            do
                mubytecswrite[i] = TEXNULL;
            while (i++ < for_end);
    }
    mubytekeep = 0;
    mubytestart = false;
    writenoexpanding = false;
    csconverting = false;
    specialprinting = false;
    messageprinting = false;
    noconvert = false;
    activenoconvert = false;
    {
        register integer for_end;
        i = FIRSTTEXTCHAR;
        for_end = LASTTEXTCHAR;
        if (i <= for_end)
            do
                xord[chr(i)] = INVALIDCODE;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 128;
        for_end = 255;
        if (i <= for_end)
            do
                xord[xchr[i]] = i;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 0;
        for_end = 126;
        if (i <= for_end)
            do
                xord[xchr[i]] = i;
            while (i++ < for_end);
    }
    {
        register integer for_end;
        i = 0;
        for_end = 255;
        if (i <= for_end)
            do
                xprn[i] = (eightbitp || ((i >= /* str ' ' */ 32) &&
                                         (i <= /* str '~' */ 126)));
            while (i++ < for_end);
    }
    if (translatefilename)
        readtcxfile();
    if (interactionoption == UNSPECIFIEDMODE)
        interaction = ERRORSTOPMODE;
    else
        interaction = interactionoption;
    deletionsallowed = true;
    setboxallowed = true;
    errorcount = 0;
    helpptr = 0;
    useerrhelp = false;
    interrupt = 0;
    OKtointerrupt = true;
    twotothe[0] = 1;
    {
        register integer for_end;
        k = 1;
        for_end = 30;
        if (k <= for_end)
            do
                twotothe[k] = 2 * twotothe[k - 1];
            while (k++ < for_end);
    }
    speclog[1] = 93032640L;
    speclog[2] = 38612034L;
    speclog[3] = 17922280L;
    speclog[4] = 8662214L;
    speclog[5] = 4261238L;
    speclog[6] = 2113709L;
    speclog[7] = 1052693L;
    speclog[8] = 525315L;
    speclog[9] = 262400L;
    speclog[10] = 131136L;
    speclog[11] = 65552L;
    speclog[12] = 32772L;
    speclog[13] = 16385;
    {
        register integer for_end;
        k = 14;
        for_end = 27;
        if (k <= for_end)
            do
                speclog[k] = twotothe[27 - k];
            while (k++ < for_end);
    }
    speclog[28] = 1;
    ;
#ifdef TEXMF_DEBUG
    wasmemend = memmin;
    waslomax = memmin;
    washimin = memmax;
    panicking = false;
#endif /* TEXMF_DEBUG */
    nestptr = 0;
    maxneststack = 0;
    curlist.modefield = VMODE;
    curlist.headfield = memtop - 1;
    curlist.tailfield = memtop - 1;
    curlist.eTeXauxfield = TEXNULL;
    curlist.auxfield.cint = -65536000L;
    curlist.mlfield = 0;
    curlist.pgfield = 0;
    shownmode = 0;
    pagecontents = EMPTY;
    pagetail = memtop - 2;
    lastglue = 2147483647L;
    lastpenalty = 0;
    lastkern = 0;
    lastnodetype = -1;
    pagesofar[7] = 0;
    pagemaxdepth = 0;
    {
        register integer for_end;
        k = INTBASE;
        for_end = EQTBSIZE;
        if (k <= for_end)
            do
                xeqlevel[k] = LEVELONE;
            while (k++ < for_end);
    }
    nonewcontrolsequence = true;
    prim[0].v.LH = 0;
    prim[0].v.RH = 0;
    {
        register integer for_end;
        k = 1;
        for_end = PRIMSIZE;
        if (k <= for_end)
            do
                prim[k] = prim[0];
            while (k++ < for_end);
    }
    saveptr = 0;
    curlevel = LEVELONE;
    curgroup = BOTTOMLEVEL;
    curboundary = 0;
    maxsavestack = 0;
    magset = 0;
    expanddepthcount = 0;
    isincsname = false;
    curmark[TOPMARKCODE] = TEXNULL;
    curmark[FIRSTMARKCODE] = TEXNULL;
    curmark[BOTMARKCODE] = TEXNULL;
    curmark[SPLITFIRSTMARKCODE] = TEXNULL;
    curmark[SPLITBOTMARKCODE] = TEXNULL;
    curval = 0;
    curvallevel = INTVAL;
    radix = 0;
    curorder = NORMAL;
    {
        register integer for_end;
        k = 0;
        for_end = 16;
        if (k <= for_end)
            do
                readopen[k] = CLOSED;
            while (k++ < for_end);
    }
    condptr = TEXNULL;
    iflimit = NORMAL;
    curif = 0;
    ifline = 0;
    nullcharacter.b0 = MINQUARTERWORD;
    nullcharacter.b1 = MINQUARTERWORD;
    nullcharacter.b2 = MINQUARTERWORD;
    nullcharacter.b3 = MINQUARTERWORD;
    totalpages = 0;
    maxv = 0;
    maxh = 0;
    maxpush = 0;
    lastbop = -1;
    doingleaders = false;
    deadcycles = 0;
    curs = -1;
    halfbuf = dvibufsize / 2;
    dvilimit = dvibufsize;
    dviptr = 0;
    dvioffset = 0;
    dvigone = 0;
    downptr = TEXNULL;
    rightptr = TEXNULL;
    pdfmemptr = 1;
    pdfmemsize = infpdfmemsize;
    pdfgone = 0;
    pdfosmode = false;
    pdfptr = 0;
    pdfopptr = 0;
    pdfosptr = 0;
    pdfoscurobjnum = 0;
    pdfoscntr = 0;
    pdfbufsize = pdfopbufsize;
    pdfosbufsize = infpdfosbufsize;
    pdfbuf = pdfopbuf;
    pdfseekwritelength = false;
    zipwritestate = 0;
    pdfminorversionwritten = false;
    fixedpdfoutputset = false;
    fixedpdfdraftmodeset = false;
    onebp = 65782L;
    onehundredbp = 6578176L;
    onehundredinch = 473628672L;
    tenpow[0] = 1;
    {
        register integer for_end;
        i = 1;
        for_end = 9;
        if (i <= for_end)
            do
                tenpow[i] = 10 * tenpow[i - 1];
            while (i++ < for_end);
    }
    initpdfoutput = false;
    objptr = 0;
    sysobjptr = 0;
    objtabsize = infobjtabsize;
    destnamessize = infdestnamessize;
    {
        register integer for_end;
        k = 1;
        for_end = 9;
        if (k <= for_end)
            do
                headtab[k] = 0;
            while (k++ < for_end);
    }
    pdfboxspecmedia = 1;
    pdfboxspeccrop = 2;
    pdfboxspecbleed = 3;
    pdfboxspectrim = 4;
    pdfboxspecart = 5;
    pdfdummyfont = FONTBASE;
    pdfresnameprefix = 0;
    lasttokensstring = 0;
    vfnf = 0;
    vfcurs = 0;
    vfstackptr = 0;
    adjusttail = TEXNULL;
    lastbadness = 0;
    preadjusttail = TEXNULL;
    packbeginline = 0;
    emptyfield.v.RH = EMPTY;
    emptyfield.v.LH = TEXNULL;
    nulldelimiter.b0 = 0;
    nulldelimiter.b1 = MINQUARTERWORD;
    nulldelimiter.b2 = 0;
    nulldelimiter.b3 = MINQUARTERWORD;
    alignptr = TEXNULL;
    curalign = TEXNULL;
    curspan = TEXNULL;
    curloop = TEXNULL;
    curhead = TEXNULL;
    curtail = TEXNULL;
    curprehead = TEXNULL;
    curpretail = TEXNULL;
    {
        register integer for_end;
        z = 0;
        for_end = hyphsize;
        if (z <= for_end)
            do {
                hyphword[z] = 0;
                hyphlist[z] = TEXNULL;
                hyphlink[z] = 0;
            } while (z++ < for_end);
    }
    hyphcount = 0;
    hyphnext = /* @d793@ */ 608;
    if (hyphnext > hyphsize)
        hyphnext = HYPHPRIME;
    outputactive = false;
    insertpenalties = 0;
    ligaturepresent = false;
    cancelboundary = false;
    lfthit = false;
    rthit = false;
    insdisc = false;
    aftertoken = 0;
    longhelpseen = false;
    formatident = 0;
    {
        register integer for_end;
        k = 0;
        for_end = 17;
        if (k <= for_end)
            do
                writeopen[k] = false;
            while (k++ < for_end);
    }
    altrule = TEXNULL;
    warnpdfpagebox = true;
    countdosnapy = 0;
    secondsandmicros(epochseconds, microseconds);
    initstarttime();
    pdffirstoutline = 0;
    pdflastoutline = 0;
    pdfparentoutline = 0;
    pdfobjcount = 0;
    pdfxformcount = 0;
    pdfximagecount = 0;
    pdfdestnamesptr = 0;
    pdfinfotoks = TEXNULL;
    pdfcatalogtoks = TEXNULL;
    pdfnamestoks = TEXNULL;
    pdfcatalogopenaction = 0;
    pdftrailertoks = TEXNULL;
    pdftraileridtoks = TEXNULL;
    genfakedinterwordspace = false;
    pdflinkstackptr = 0;
    LRptr = TEXNULL;
    LRproblems = 0;
    curdir = LEFTTORIGHT;
    pseudofiles = TEXNULL;
    saroot[MARKVAL] = TEXNULL;
    sanull.hh.v.LH = TEXNULL;
    sanull.hh.v.RH = TEXNULL;
    sachain = TEXNULL;
    salevel = LEVELZERO;
    discptr[LASTBOXCODE] = TEXNULL;
    discptr[VSPLITCODE] = TEXNULL;
    editnamestart = 0;
    stopatspace = true;
    mltexenabledp = false;
    enctexenabledp = false;
    ;
#ifdef INITEX
    if (iniversion) {
        /* comment:Initialize table entries (done by \.{INITEX} only) */ {
            register integer for_end;
            k = membot + 1;
            for_end = /* @d801@ */ /* @d802@ */ /* @d803@ */ /* @d804@ */
                      /* @d805@ */ membot + 19;
            if (k <= for_end)
                do
                    mem[k].cint = 0;
                while (k++ < for_end);
        }
        k = membot;
        while (k <= /* @d806@ */ /* @d807@ */ /* @d808@ */ /* @d809@ */
                        /* @d810@ */ membot + 19) {

            mem[k].hh.v.RH = -2147483646L;
            mem[k].hh.b0 = NORMAL;
            mem[k].hh.b1 = NORMAL;
            k = k + GLUESPECSIZE;
        }
        mem[/* @d814@ */ membot + 6].cint = 65536L;
        mem[membot + GLUESPECSIZE].hh.b0 = FIL;
        mem[/* @d817@ */ /* @d818@ */ membot + 10].cint = 65536L;
        mem[/* @d819@ */ /* @d820@ */ membot + 8].hh.b0 = FILL;
        mem[/* @d822@ */ /* @d823@ */ /* @d824@ */ membot + 14].cint = 65536L;
        mem[/* @d825@ */ /* @d826@ */ /* @d827@ */ membot + 12].hh.b0 = FIL;
        mem[/* @d829@ */ /* @d830@ */ /* @d831@ */ membot + 15].cint = 65536L;
        mem[/* @d832@ */ /* @d833@ */ /* @d834@ */ membot + 12].hh.b1 = FIL;
        mem[/* @d836@ */ /* @d837@ */ /* @d838@ */ /* @d839@ */ membot + 18]
            .cint = -65536L;
        mem[/* @d840@ */ /* @d841@ */ /* @d842@ */ /* @d843@ */ membot + 16]
            .hh.b0 = FIL;
        rover = /* @d845@ */ /* @d846@ */ /* @d847@ */ /* @d848@ */ /* @d849@ */
                membot + 20;
        mem[rover].hh.v.RH = 2147483647L;
        mem[rover].hh.v.LH = 1000;
        mem[rover + 1].hh.v.LH = rover;
        mem[rover + 1].hh.v.RH = rover;
        lomemmax = rover + 1000;
        mem[lomemmax].hh.v.RH = TEXNULL;
        mem[lomemmax].hh.v.LH = TEXNULL;
        {
            register integer for_end;
            k = memtop - 14;
            for_end = memtop;
            if (k <= for_end)
                do
                    mem[k] = mem[lomemmax];
                while (k++ < for_end);
        }
        /* comment:Initialize the special list heads and constant nod */ mem
            [memtop - 10]
                .hh.v.LH = /* @d851@ */ 19614;
        mem[memtop - 9].hh.v.RH = /* @d852@ */ 256;
        mem[memtop - 9].hh.v.LH = TEXNULL;
        mem[memtop - 7].hh.b0 = HYPHENATED;
        mem[memtop - 6].hh.v.LH = 2147483647L;
        mem[memtop - 7].hh.b1 = 0;
        mem[memtop].hh.b1 = 255;
        mem[memtop].hh.b0 = SPLITUP;
        mem[memtop].hh.v.RH = memtop;
        mem[memtop - 2].hh.b0 = GLUENODE;
        mem[memtop - 2].hh.b1 = NORMAL;
        avail = TEXNULL;
        memend = memtop;
        himemmin = memtop - 14;
        varused = /* @d857@ */ /* @d858@ */ /* @d859@ */ /* @d860@ */
                  /* @d861@ */ membot + 20 - membot;
        dynused = HIMEMSTATUSAGE;
        eqtb[UNDEFINEDCONTROLSEQUENCE].hh.b0 = UNDEFINEDCS;
        eqtb[UNDEFINEDCONTROLSEQUENCE].hh.v.RH = TEXNULL;
        eqtb[UNDEFINEDCONTROLSEQUENCE].hh.b1 = LEVELZERO;
        {
            register integer for_end;
            k = ACTIVEBASE;
            for_end = eqtbtop;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[UNDEFINEDCONTROLSEQUENCE];
                while (k++ < for_end);
        }
        eqtb[GLUEBASE].hh.v.RH = membot;
        eqtb[GLUEBASE].hh.b1 = LEVELONE;
        eqtb[GLUEBASE].hh.b0 = GLUEREF;
        {
            register integer for_end;
            k = /* @d875@ */ 26629;
            for_end = /* @d876@ */ 27157;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[GLUEBASE];
                while (k++ < for_end);
        }
        mem[membot].hh.v.RH =
            mem[membot].hh.v.RH /* @d878@ */ /* @d879@ */ + 530;
        eqtb[PARSHAPELOC].hh.v.RH = TEXNULL;
        eqtb[PARSHAPELOC].hh.b0 = SHAPEREF;
        eqtb[PARSHAPELOC].hh.b1 = LEVELONE;
        {
            register integer for_end;
            k = ETEXPENBASE;
            for_end = /* @d886@ */ 27432;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[PARSHAPELOC];
                while (k++ < for_end);
        }
        {
            register integer for_end;
            k = OUTPUTROUTINELOC;
            for_end = /* @d889@ */ 27428;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[UNDEFINEDCONTROLSEQUENCE];
                while (k++ < for_end);
        }
        eqtb[BOXBASE].hh.v.RH = TEXNULL;
        eqtb[BOXBASE].hh.b0 = BOXREF;
        eqtb[BOXBASE].hh.b1 = LEVELONE;
        {
            register integer for_end;
            k = /* @d896@ */ 27434;
            for_end = /* @d897@ */ 27688;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[BOXBASE];
                while (k++ < for_end);
        }
        eqtb[CURFONTLOC].hh.v.RH = FONTBASE;
        eqtb[CURFONTLOC].hh.b0 = DATA;
        eqtb[CURFONTLOC].hh.b1 = LEVELONE;
        {
            register integer for_end;
            k = MATHFONTBASE;
            for_end = /* @d906@ */ 27740;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[CURFONTLOC];
                while (k++ < for_end);
        }
        eqtb[CATCODEBASE].hh.v.RH = 0;
        eqtb[CATCODEBASE].hh.b0 = DATA;
        eqtb[CATCODEBASE].hh.b1 = LEVELONE;
        {
            register integer for_end;
            k = /* @d913@ */ 27742;
            for_end = /* @d914@ */ 29276;
            if (k <= for_end)
                do
                    eqtb[k] = eqtb[CATCODEBASE];
                while (k++ < for_end);
        }
        {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do {
                    eqtb[CATCODEBASE + k].hh.v.RH = OTHERCHAR;
                    eqtb[MATHCODEBASE + k].hh.v.RH = k;
                    eqtb[SFCODEBASE + k].hh.v.RH = 1000;
                } while (k++ < for_end);
        }
        eqtb[CATCODEBASE + CARRIAGERETURN].hh.v.RH = CARRET;
        eqtb[/* @d923@ */ /* str ' ' */ 27773].hh.v.RH = SPACER;
        eqtb[/* @d926@ */ /* str '\' */ 27833].hh.v.RH = ESCAPE;
        eqtb[/* @d929@ */ /* str '%' */ 27778].hh.v.RH = COMMENT;
        eqtb[CATCODEBASE + INVALIDCODE].hh.v.RH = INVALIDCHAR;
        eqtb[CATCODEBASE + NULLCODE].hh.v.RH = IGNORE;
        {
            register integer for_end;
            k = /* str '0' */ 48;
            for_end = /* str '9' */ 57;
            if (k <= for_end)
                do
                    eqtb[MATHCODEBASE + k].hh.v.RH = k + 28672;
                while (k++ < for_end);
        }
        {
            register integer for_end;
            k = /* str 'A' */ 65;
            for_end = /* str 'Z' */ 90;
            if (k <= for_end)
                do {
                    eqtb[CATCODEBASE + k].hh.v.RH = LETTER;
                    eqtb[CATCODEBASE + /* str 'a' */ /* str 'A' */ k + 32]
                        .hh.v.RH = LETTER;
                    eqtb[MATHCODEBASE + k].hh.v.RH = k + 28928;
                    eqtb[MATHCODEBASE + /* str 'a' */ /* str 'A' */ k + 32]
                        .hh.v.RH = /* str 'a' */ /* str 'A' */ k + 28960;
                    eqtb[LCCODEBASE + k].hh.v.RH =
                        /* str 'a' */ /* str 'A' */ k + 32;
                    eqtb[LCCODEBASE + /* str 'a' */ /* str 'A' */ k + 32]
                        .hh.v.RH = /* str 'a' */ /* str 'A' */ k + 32;
                    eqtb[UCCODEBASE + k].hh.v.RH = k;
                    eqtb[UCCODEBASE + /* str 'a' */ /* str 'A' */ k + 32]
                        .hh.v.RH = k;
                    eqtb[SFCODEBASE + k].hh.v.RH = 999;
                } while (k++ < for_end);
        }
        {
            register integer for_end;
            k = INTBASE;
            for_end = /* @d969@ */ 29637;
            if (k <= for_end)
                do
                    eqtb[k].cint = 0;
                while (k++ < for_end);
        }
        eqtb[INTBASE + CHARSUBDEFMINCODE].cint = 256;
        eqtb[INTBASE + CHARSUBDEFMAXCODE].cint = -1;
        eqtb[INTBASE + MAGCODE].cint = 1000;
        eqtb[INTBASE + TOLERANCECODE].cint = 10000;
        eqtb[INTBASE + HANGAFTERCODE].cint = 1;
        eqtb[INTBASE + MAXDEADCYCLESCODE].cint = 25;
        eqtb[INTBASE + ESCAPECHARCODE].cint = /* str '\' */ 92;
        eqtb[INTBASE + ENDLINECHARCODE].cint = CARRIAGERETURN;
        {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do
                    eqtb[DELCODEBASE + k].cint = -1;
                while (k++ < for_end);
        }
        eqtb[/* @d989@ */ /* str '.' */ 29684].cint = 0;
        {
            register integer for_end;
            k = DIMENBASE;
            for_end = EQTBSIZE;
            if (k <= for_end)
                do
                    eqtb[k].cint = 0;
                while (k++ < for_end);
        }
        primused = PRIMSIZE;
        hashused = FROZENCONTROLSEQUENCE;
        hashhigh = 0;
        cscount = 0;
        eqtb[FROZENDONTEXPAND].hh.b0 = DONTEXPAND;
        hash[FROZENDONTEXPAND].v.RH = /* str 'notexpanded' */ 576;
        eqtb[FROZENPRIMITIVE].hh.b0 = IGNORESPACES;
        eqtb[FROZENPRIMITIVE].hh.v.RH = 1;
        eqtb[FROZENPRIMITIVE].hh.b1 = LEVELONE;
        hash[FROZENPRIMITIVE].v.RH = /* str 'pdfprimitive' */ 577;
        eqtb[DIMENBASE + PDFHORIGINCODE].cint = (onehundredinch + 50) / 100;
        eqtb[DIMENBASE + PDFVORIGINCODE].cint = (onehundredinch + 50) / 100;
        eqtb[INTBASE + PDFCOMPRESSLEVELCODE].cint = 9;
        eqtb[INTBASE + PDFOBJCOMPRESSLEVELCODE].cint = 0;
        eqtb[INTBASE + PDFDECIMALDIGITSCODE].cint = 3;
        eqtb[INTBASE + PDFIMAGERESOLUTIONCODE].cint = 72;
        eqtb[INTBASE + PDFMINORVERSIONCODE].cint = 4;
        eqtb[INTBASE + PDFGAMMACODE].cint = 1000;
        eqtb[INTBASE + PDFIMAGEGAMMACODE].cint = 2200;
        eqtb[INTBASE + PDFIMAGEHICOLORCODE].cint = 1;
        eqtb[INTBASE + PDFIMAGEAPPLYGAMMACODE].cint = 0;
        eqtb[DIMENBASE + PDFPXDIMENCODE].cint = onebp;
        eqtb[INTBASE + PDFDRAFTMODECODE].cint = 0;
        eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint = -65536000L;
        eqtb[DIMENBASE + PDFEACHLINEHEIGHTCODE].cint =
            eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint;
        eqtb[DIMENBASE + PDFEACHLINEDEPTHCODE].cint =
            eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint;
        eqtb[DIMENBASE + PDFFIRSTLINEHEIGHTCODE].cint =
            eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint;
        eqtb[DIMENBASE + PDFLASTLINEDEPTHCODE].cint =
            eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint;
        {
            register integer for_end;
            k = -(integer)trieopsize;
            for_end = trieopsize;
            if (k <= for_end)
                do
                    trieophash[k] = 0;
                while (k++ < for_end);
        }
        {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do
                    trieused[k] = mintrieop;
                while (k++ < for_end);
        }
        maxopused = mintrieop;
        trieopptr = 0;
        trienotready = true;
        hash[FROZENPROTECTION].v.RH = /* str 'inaccessible' */ 1611;
        if (iniversion)
            formatident = /* str ' (INITEX)' */ 1698;
        hash[ENDWRITE].v.RH = /* str 'endwrite' */ 1910;
        eqtb[ENDWRITE].hh.b1 = LEVELONE;
        eqtb[ENDWRITE].hh.b0 = OUTERCALL;
        eqtb[ENDWRITE].hh.v.RH = TEXNULL;
        eTeXmode = 0;
        /* comment:Initialize variables for \eTeX\ compatibility mode */
        maxregnum = 255;
        maxreghelpline =
            /* str 'A register number must be between 0 and 255.' */ 789;
        {
            register integer for_end;
            i = INTVAL;
            for_end = TOKVAL;
            if (i <= for_end)
                do
                    saroot[i] = TEXNULL;
                while (i++ < for_end);
        }
    }
#endif /* INITEX */
}
#ifdef INITEX
boolean getstringsstarted(void) {
    register boolean Result;
    getstringsstarted_regmem unsigned char k, l;
    strnumber g;
    poolptr = 0;
    strptr = 0;
    strstart[0] = 0;
    /* comment:Make the first 256 strings */ {
        register integer for_end;
        k = 0;
        for_end = 255;
        if (k <= for_end)
            do {
                if ((/* comment:Character |k| cannot be printed */ (
                         k < /* str ' ' */ 32) ||
                     (k > /* str '~' */ 126))) {
                    {
                        strpool[poolptr] = /* str '^' */ 94;
                        incr(poolptr);
                    }
                    {
                        strpool[poolptr] = /* str '^' */ 94;
                        incr(poolptr);
                    }
                    if (k < 64) {
                        strpool[poolptr] = k + 64;
                        incr(poolptr);
                    } else if (k < 128) {
                        strpool[poolptr] = k - 64;
                        incr(poolptr);
                    } else {

                        l = k / 16;
                        if (l < 10) {
                            strpool[poolptr] = /* str '0' */ l + 48;
                            incr(poolptr);
                        } else {

                            strpool[poolptr] = /* str 'a' */ l + 87;
                            incr(poolptr);
                        }
                        l = k % 16;
                        if (l < 10) {
                            strpool[poolptr] = /* str '0' */ l + 48;
                            incr(poolptr);
                        } else {

                            strpool[poolptr] = /* str 'a' */ l + 87;
                            incr(poolptr);
                        }
                    }
                } else {

                    strpool[poolptr] = k;
                    incr(poolptr);
                }
                g = makestring();
            } while (k++ < for_end);
    }
    /* comment:Read the other strings from the \.{TEX.POOL} file  */ g =
        loadpoolstrings((poolsize - stringvacancies));
    if (g == 0) {
        ;
        fprintf(stdout, "%s\n", "! You have to increase POOLSIZE.");
        Result = false;
        return Result;
    }
    Result = true;
    return Result;
}
#endif /* INITEX */
#ifdef INITEX
void sortavail(void) {
    sortavail_regmem halfword p, q, r;
    halfword oldrover;
    p = getnode(1073741824L);
    p = mem[rover + 1].hh.v.RH;
    mem[rover + 1].hh.v.RH = 2147483647L;
    oldrover = rover;
    while (p != oldrover) /* comment:Sort \(p)|p| into the list starting at
                             |rover| and */
        if (p < rover) {
            q = p;
            p = mem[q + 1].hh.v.RH;
            mem[q + 1].hh.v.RH = rover;
            rover = q;
        } else {

            q = rover;
            while (mem[q + 1].hh.v.RH < p)
                q = mem[q + 1].hh.v.RH;
            r = mem[p + 1].hh.v.RH;
            mem[p + 1].hh.v.RH = mem[q + 1].hh.v.RH;
            mem[q + 1].hh.v.RH = p;
            p = r;
        }
    p = rover;
    while (mem[p + 1].hh.v.RH != 2147483647L) {

        mem[mem[p + 1].hh.v.RH + 1].hh.v.LH = p;
        p = mem[p + 1].hh.v.RH;
    }
    mem[p + 1].hh.v.RH = rover;
    mem[rover + 1].hh.v.LH = p;
}
#endif /* INITEX */
#ifdef INITEX
void zprimitive(strnumber s, quarterword c, halfword o) {
    primitive_regmem poolpointer k;
    integer j;
    smallnumber l;
    integer primval;
    if (s < 256) {
        curval = s + SINGLEBASE;
        primval = primlookup(s);
    } else {

        k = strstart[s];
        l = strstart[s + 1] - k;
        if (first + l > bufsize + 1)
            overflow(/* str 'buffer size' */ 258, bufsize);
        {
            register integer for_end;
            j = 0;
            for_end = l - 1;
            if (j <= for_end)
                do
                    buffer[first + j] = strpool[k + j];
                while (j++ < for_end);
        }
        curval = idlookup(first, l);
        {
            decr(strptr);
            poolptr = strstart[strptr];
        }
        hash[curval].v.RH = s;
        primval = primlookup(s);
    }
    eqtb[curval].hh.b1 = LEVELONE;
    eqtb[curval].hh.b0 = c;
    eqtb[curval].hh.v.RH = o;
    eqtb[PRIMEQTBBASE + primval].hh.b1 = LEVELONE;
    eqtb[PRIMEQTBBASE + primval].hh.b0 = c;
    eqtb[PRIMEQTBBASE + primval].hh.v.RH = o;
}
#endif /* INITEX */
void hyphenate(void) {
    /* @d10272@ */ /* @d10273@ */ /* @d10274@ */ /* @d10275@ */ /* @d10276@ */
    hyphenate_regmem
        /* comment:Local variables for hyphenation */ unsigned char i,
        j, l;
    halfword q, r, s;
    halfword bchar;
    halfword majortail, minortail;
    ASCIIcode c;
    unsigned char cloc;
    integer rcount;
    halfword hyfnode;
    triepointer z;
    integer v;
    hyphpointer h;
    strnumber k;
    poolpointer u;
    /* comment:Find hyphen locations for the word in |hc|, or |re */ {
        register integer for_end;
        j = 0;
        for_end = hn;
        if (j <= for_end)
            do
                hyf[j] = 0;
            while (j++ < for_end);
    }
    /* comment:Look for the word |hc[1..hn]| in the exception tab */ h = hc[1];
    incr(hn);
    hc[hn] = curlang;
    {
        register integer for_end;
        j = 2;
        for_end = hn;
        if (j <= for_end)
            do
                h = (h + h + hc[j]) % /* @d10282@ */ 607;
            while (j++ < for_end);
    }
    while (true) {

        /* comment:If the string |hyph_word[h]| is less than \(hc)|hc */ k =
            hyphword[h];
        if (k == 0)
            goto labhyphenate45not_found;
        if ((strstart[k + 1] - strstart[k]) == hn) {
            j = 1;
            u = strstart[k];
            do {
                if (strpool[u] != hc[j])
                    goto labhyphenate30done;
                incr(j);
                incr(u);
            } while (!(j > hn));
            /* comment:Insert hyphens as specified in |hyph_list[h]| */ s =
                hyphlist[h];
            while (s != TEXNULL) {

                hyf[mem[s].hh.v.LH] = 1;
                s = mem[s].hh.v.RH;
            }
            decr(hn);
            goto labhyphenate40found;
        }
    labhyphenate30done:;
        h = hyphlink[h];
        if (h == 0)
            goto labhyphenate45not_found;
        decr(h);
    }
labhyphenate45not_found:
    decr(hn);
    if (trietrc[curlang + 1] != curlang)
        return;
    hc[0] = 0;
    hc[hn + 1] = 0;
    hc[hn + 2] = 256;
    {
        register integer for_end;
        j = 0;
        for_end = hn - rhyf + 1;
        if (j <= for_end)
            do {
                z = trietrl[curlang + 1] + hc[j];
                l = j;
                while (hc[l] == trietrc[z]) {

                    if (trietro[z] != mintrieop) /* comment:Store \(m)maximum
                                                    values in the |hyf| table */
                    {
                        v = trietro[z];
                        do {
                            v = v + opstart[curlang];
                            i = l - hyfdistance[v];
                            if (hyfnum[v] > hyf[i])
                                hyf[i] = hyfnum[v];
                            v = hyfnext[v];
                        } while (!(v == mintrieop));
                    }
                    incr(l);
                    z = trietrl[z] + hc[l];
                }
            } while (j++ < for_end);
    }
labhyphenate40found : {
    register integer for_end;
    j = 0;
    for_end = lhyf - 1;
    if (j <= for_end)
        do
            hyf[j] = 0;
        while (j++ < for_end);
}
    {
        register integer for_end;
        j = 0;
        for_end = rhyf - 1;
        if (j <= for_end)
            do
                hyf[hn - j] = 0;
            while (j++ < for_end);
    }
    /* comment:If no hyphens were found, |return| */ {
        register integer for_end;
        j = lhyf;
        for_end = hn - rhyf;
        if (j <= for_end)
            do
                if (odd(hyf[j]))
                    goto labhyphenate41found1;
            while (j++ < for_end);
    }
    return;
labhyphenate41found1:;
    /* comment:Replace nodes |ha..hb| by a sequence of nodes that */ q =
        mem[hb].hh.v.RH;
    mem[hb].hh.v.RH = TEXNULL;
    r = mem[ha].hh.v.RH;
    mem[ha].hh.v.RH = TEXNULL;
    bchar = hyfbchar;
    if ((ha >= himemmin)) {

        if (mem[ha].hh.b0 != hf)
            goto labhyphenate42found2;
        else {

            initlist = ha;
            initlig = false;
            hu[0] = mem[ha].hh.b1;
        }
    } else if (mem[ha].hh.b0 == LIGATURENODE) {

        if (mem[ha + 1].hh.b0 != hf)
            goto labhyphenate42found2;
        else {

            initlist = mem[ha + 1].hh.v.RH;
            initlig = true;
            initlft = (mem[ha].hh.b1 > 1);
            hu[0] = mem[ha + 1].hh.b1;
            if (initlist == TEXNULL) {

                if (initlft) {
                    hu[0] = 256;
                    initlig = false;
                }
            }
            freenode(ha, SMALLNODESIZE);
        }
    } else {

        if (!(r >= himemmin)) {

            if (mem[r].hh.b0 == LIGATURENODE) {

                if (mem[r].hh.b1 > 1)
                    goto labhyphenate42found2;
            }
        }
        j = 1;
        s = ha;
        initlist = TEXNULL;
        goto labhyphenate50common_ending;
    }
    s = curp;
    while (mem[s].hh.v.RH != ha)
        s = mem[s].hh.v.RH;
    j = 0;
    goto labhyphenate50common_ending;
labhyphenate42found2:
    s = ha;
    j = 0;
    hu[0] = 256;
    initlig = false;
    initlist = TEXNULL;
labhyphenate50common_ending:
    flushnodelist(r);
    /* comment:Reconstitute nodes for the hyphenated word, insert */ do {
        l = j;
        j = reconstitute(j, hn, bchar, hyfchar) + 1;
        if (hyphenpassed == 0) {
            mem[s].hh.v.RH = mem[memtop - 4].hh.v.RH;
            while (mem[s].hh.v.RH > TEXNULL)
                s = mem[s].hh.v.RH;
            if (odd(hyf[j - 1])) {
                l = j;
                hyphenpassed = j - 1;
                mem[memtop - 4].hh.v.RH = TEXNULL;
            }
        }
        if (hyphenpassed >
            0) /* comment:Create and append a discretionary node as an alter */
            do {
                r = getnode(SMALLNODESIZE);
                mem[r].hh.v.RH = mem[memtop - 4].hh.v.RH;
                mem[r].hh.b0 = DISCNODE;
                majortail = r;
                rcount = 0;
                while (mem[majortail].hh.v.RH > TEXNULL) {

                    majortail = mem[majortail].hh.v.RH;
                    incr(rcount);
                }
                i = hyphenpassed;
                hyf[i] = 0;
                /* comment:Put the \(c)characters |hu[l..i]| and a hyphen int */
                minortail = TEXNULL;
                mem[r + 1].hh.v.LH = TEXNULL;
                hyfnode = newcharacter(hf, hyfchar);
                if (hyfnode != TEXNULL) {
                    incr(i);
                    c = hu[i];
                    hu[i] = hyfchar;
                    {
                        mem[hyfnode].hh.v.RH = avail;
                        avail = hyfnode;
                        mem[hyfnode].hh.me = 0;
                        ;
#ifdef STAT
                        decr(dynused);
#endif /* STAT */
                    }
                }
                while (l <= i) {

                    l = reconstitute(l, i, fontbchar[hf], 256) + 1;
                    if (mem[memtop - 4].hh.v.RH > TEXNULL) {
                        if (minortail == TEXNULL)
                            mem[r + 1].hh.v.LH = mem[memtop - 4].hh.v.RH;
                        else
                            mem[minortail].hh.v.RH = mem[memtop - 4].hh.v.RH;
                        minortail = mem[memtop - 4].hh.v.RH;
                        while (mem[minortail].hh.v.RH > TEXNULL)
                            minortail = mem[minortail].hh.v.RH;
                    }
                }
                if (hyfnode != TEXNULL) {
                    hu[i] = c;
                    l = i;
                    decr(i);
                }
                /* comment:Put the \(c)characters |hu[i+1..@,]| into |post_br */
                minortail = TEXNULL;
                mem[r + 1].hh.v.RH = TEXNULL;
                cloc = 0;
                if (bcharlabel[hf] != NONADDRESS) {
                    decr(l);
                    c = hu[l];
                    cloc = l;
                    hu[l] = 256;
                }
                while (l < j) {

                    do {
                        l = reconstitute(l, hn, bchar, 256) + 1;
                        if (cloc > 0) {
                            hu[cloc] = c;
                            cloc = 0;
                        }
                        if (mem[memtop - 4].hh.v.RH > TEXNULL) {
                            if (minortail == TEXNULL)
                                mem[r + 1].hh.v.RH = mem[memtop - 4].hh.v.RH;
                            else
                                mem[minortail].hh.v.RH =
                                    mem[memtop - 4].hh.v.RH;
                            minortail = mem[memtop - 4].hh.v.RH;
                            while (mem[minortail].hh.v.RH > TEXNULL)
                                minortail = mem[minortail].hh.v.RH;
                        }
                    } while (!(l >= j));
                    while (l > j) /* comment:Append characters of |hu[j..@,]| to
                                     |major_tail|,  */
                    {

                        j = reconstitute(j, hn, bchar, 256) + 1;
                        mem[majortail].hh.v.RH = mem[memtop - 4].hh.v.RH;
                        while (mem[majortail].hh.v.RH > TEXNULL) {

                            majortail = mem[majortail].hh.v.RH;
                            incr(rcount);
                        }
                    }
                }
                /* comment:Move pointer |s| to the end of the current list, a */
                if (rcount > 127) {
                    mem[s].hh.v.RH = mem[r].hh.v.RH;
                    mem[r].hh.v.RH = TEXNULL;
                    flushnodelist(r);
                } else {

                    mem[s].hh.v.RH = r;
                    mem[r].hh.b1 = rcount;
                }
                s = majortail;
                hyphenpassed = j - 1;
                mem[memtop - 4].hh.v.RH = TEXNULL;
            } while (!(!odd(hyf[j - 1])));
    } while (!(j > hn));
    mem[s].hh.v.RH = q;
    flushlist(initlist);
/* @d10318@ */}
#ifdef INITEX
/* comment:Declare procedures for preprocessing hyphenation p */ trieopcode
znewtrieop(smallnumber d, smallnumber n, trieopcode v) {
    register trieopcode Result;
    newtrieop_regmem integer h;
    trieopcode u;
    integer l;
    h = abs(n + 313 * d + 361 * v + 1009 * curlang) %
            (trieopsize - negtrieopsize) +
        negtrieopsize;
    while (true) {

        l = trieophash[h];
        if (l == 0) {
            if (trieopptr == trieopsize)
                overflow(/* str 'pattern memory ops' */ 1363, trieopsize);
            u = trieused[curlang];
            if (u == maxtrieop)
                overflow(/* str 'pattern memory ops per language' */ 1364,
                         maxtrieop - mintrieop);
            incr(trieopptr);
            incr(u);
            trieused[curlang] = u;
            if (u > maxopused)
                maxopused = u;
            hyfdistance[trieopptr] = d;
            hyfnum[trieopptr] = n;
            hyfnext[trieopptr] = v;
            trieoplang[trieopptr] = curlang;
            trieophash[h] = trieopptr;
            trieopval[trieopptr] = u;
            Result = u;
            return Result;
        }
        if ((hyfdistance[l] == d) && (hyfnum[l] == n) && (hyfnext[l] == v) &&
            (trieoplang[l] == curlang)) {
            Result = trieopval[l];
            return Result;
        }
        if (h > -(integer)trieopsize)
            decr(h);
        else
            h = trieopsize;
    }
    return Result;
}
triepointer ztrienode(triepointer p) {
    register triepointer Result;
    trienode_regmem triepointer h;
    triepointer q;
    h = abs(triec[p] + 1009 * trieo[p] + 2718 * triel[p] + 3142 * trier[p]) %
        triesize;
    while (true) {

        q = triehash[h];
        if (q == 0) {
            triehash[h] = p;
            Result = p;
            return Result;
        }
        if ((triec[q] == triec[p]) && (trieo[q] == trieo[p]) &&
            (triel[q] == triel[p]) && (trier[q] == trier[p])) {
            Result = q;
            return Result;
        }
        if (h > 0)
            decr(h);
        else
            h = triesize;
    }
    return Result;
}
triepointer zcompresstrie(triepointer p) {
    register triepointer Result;
    compresstrie_regmem if (p == 0) Result = 0;
    else {

        triel[p] = compresstrie(triel[p]);
        trier[p] = compresstrie(trier[p]);
        Result = trienode(p);
    }
    return Result;
}
void zfirstfit(triepointer p) {
    firstfit_regmem triepointer h;
    triepointer z;
    triepointer q;
    ASCIIcode c;
    triepointer l, r;
    short ll;
    c = triec[p];
    z = triemin[c];
    while (true) {

        h = z - c;
        /* comment:Ensure that |trie_max>=h+256| */ if (triemax < h + 256) {
            if (triesize <= h + 256)
                overflow(/* str 'pattern memory' */ 1365, triesize);
            do {
                incr(triemax);
                trietaken[triemax] = false;
                trietrl[triemax] = triemax + 1;
                trietro[triemax] = triemax - 1;
            } while (!(triemax == h + 256));
        }
        if (trietaken[h])
            goto labfirstfit45not_found;
        /* comment:If all characters of the family fit relative to |h */ q =
            trier[p];
        while (q > 0) {

            if (trietrl[h + triec[q]] == 0)
                goto labfirstfit45not_found;
            q = trier[q];
        }
        goto labfirstfit40found;
    labfirstfit45not_found:
        z = trietrl[z];
    }
labfirstfit40found: /* comment:Pack the family into |trie| relative to |h| */
    trietaken[h] = true;
    triehash[p] = h;
    q = p;
    do {
        z = h + triec[q];
        l = trietro[z];
        r = trietrl[z];
        trietro[r] = l;
        trietrl[l] = r;
        trietrl[z] = 0;
        if (l < 256) {
            if (z < 256)
                ll = z;
            else
                ll = 256;
            do {
                triemin[l] = r;
                incr(l);
            } while (!(l == ll));
        }
        q = trier[q];
    } while (!(q == 0));
}
void ztriepack(triepointer p) {
    triepack_regmem triepointer q;
    do {
        q = triel[p];
        if ((q > 0) && (triehash[q] == 0)) {
            firstfit(q);
            triepack(q);
        }
        p = trier[p];
    } while (!(p == 0));
}
void ztriefix(triepointer p) {
    triefix_regmem triepointer q;
    ASCIIcode c;
    triepointer z;
    z = triehash[p];
    do {
        q = triel[p];
        c = triec[p];
        trietrl[z + c] = triehash[q];
        trietrc[z + c] = c;
        trietro[z + c] = trieo[p];
        if (q > 0)
            triefix(q);
        p = trier[p];
    } while (!(p == 0));
}
void newpatterns(void) {
    newpatterns_regmem unsigned char k, l;
    boolean digitsensed;
    trieopcode v;
    triepointer p, q;
    boolean firstchild;
    ASCIIcode c;
    if (trienotready) {
        if (eqtb[INTBASE + LANGUAGECODE].cint <= 0)
            curlang = 0;
        else if (eqtb[INTBASE + LANGUAGECODE].cint > 255)
            curlang = 0;
        else
            curlang = eqtb[INTBASE + LANGUAGECODE].cint;
        scanleftbrace();
        /* comment:Enter all of the patterns into a linked trie, unti */ k = 0;
        hyf[0] = 0;
        digitsensed = false;
        while (true) {

            getxtoken();
            switch (curcmd) {
            case LETTER:
            case OTHERCHAR:
                /* comment:Append a new letter or a hyphen level */
                if (digitsensed || (curchr < /* str '0' */ 48) ||
                    (curchr > /* str '9' */ 57)) {
                    if (curchr == /* str '.' */ 46)
                        curchr = 0;
                    else {

                        curchr = eqtb[LCCODEBASE + curchr].hh.v.RH;
                        if (curchr == 0) {
                            {
                                if (interaction == ERRORSTOPMODE)
                                    ;
                                if (filelineerrorstylep)
                                    printfileline();
                                else
                                    printnl(/* str '! ' */ 264);
                                print(/* str 'Nonletter' */ 1371);
                            }
                            {
                                helpptr = 1;
                                helpline[0] =
                                    /* str '(See Appendix H.)' */ 1370;
                            }
                            error();
                        }
                    }
                    if (k < 63) {
                        incr(k);
                        hc[k] = curchr;
                        hyf[k] = 0;
                        digitsensed = false;
                    }
                } else if (k < 63) {
                    hyf[k] = /* str '0' */ curchr - 48;
                    digitsensed = true;
                }
                break;
            case SPACER:
            case RIGHTBRACE: {
                if (k >
                    0) /* comment:Insert a new pattern into the linked trie */
                {
                    /* comment:Compute the trie op code, |v|, and set |l */
                    if (hc[1] == 0)
                        hyf[0] = 0;
                    if (hc[k] == 0)
                        hyf[k] = 0;
                    l = k;
                    v = mintrieop;
                    while (true) {

                        if (hyf[l] != 0)
                            v = newtrieop(k - l, hyf[l], v);
                        if (l > 0)
                            decr(l);
                        else
                            goto labnewpatterns31done1;
                    }
                labnewpatterns31done1:;
                    q = 0;
                    hc[0] = curlang;
                    while (l <= k) {

                        c = hc[l];
                        incr(l);
                        p = triel[q];
                        firstchild = true;
                        while ((p > 0) && (c > triec[p])) {

                            q = p;
                            p = trier[q];
                            firstchild = false;
                        }
                        if ((p == 0) ||
                            (c < triec[p])) /* comment:Insert a new trie node
                                               between |q| and |p|, and ma */
                        {
                            if (trieptr == triesize)
                                overflow(/* str 'pattern memory' */ 1365,
                                         triesize);
                            incr(trieptr);
                            trier[trieptr] = p;
                            p = trieptr;
                            triel[p] = 0;
                            if (firstchild)
                                triel[q] = p;
                            else
                                trier[q] = p;
                            triec[p] = c;
                            trieo[p] = mintrieop;
                        }
                        q = p;
                    }
                    if (trieo[q] != mintrieop) {
                        {
                            if (interaction == ERRORSTOPMODE)
                                ;
                            if (filelineerrorstylep)
                                printfileline();
                            else
                                printnl(/* str '! ' */ 264);
                            print(/* str 'Duplicate pattern' */ 1372);
                        }
                        {
                            helpptr = 1;
                            helpline[0] = /* str '(See Appendix H.)' */ 1370;
                        }
                        error();
                    }
                    trieo[q] = v;
                }
                if (curcmd == RIGHTBRACE)
                    goto labnewpatterns30done;
                k = 0;
                hyf[0] = 0;
                digitsensed = false;
            } break;
            default: {
                {
                    if (interaction == ERRORSTOPMODE)
                        ;
                    if (filelineerrorstylep)
                        printfileline();
                    else
                        printnl(/* str '! ' */ 264);
                    print(/* str 'Bad ' */ 1369);
                }
                printesc(/* str 'patterns' */ 1367);
                {
                    helpptr = 1;
                    helpline[0] = /* str '(See Appendix H.)' */ 1370;
                }
                error();
            } break;
            }
        }
    labnewpatterns30done:;
        if (eqtb[INTBASE + SAVINGHYPHCODESCODE].cint >
            0) /* comment:Store hyphenation codes for current language */
        {
            c = curlang;
            firstchild = false;
            p = 0;
            do {
                q = p;
                p = trier[q];
            } while (!((p == 0) || (c <= triec[p])));
            if ((p == 0) || (c < triec[p])) /* comment:Insert a new trie node
                                               between |q| and |p|, and ma */
            {
                if (trieptr == triesize)
                    overflow(/* str 'pattern memory' */ 1365, triesize);
                incr(trieptr);
                trier[trieptr] = p;
                p = trieptr;
                triel[p] = 0;
                if (firstchild)
                    triel[q] = p;
                else
                    trier[q] = p;
                triec[p] = c;
                trieo[p] = mintrieop;
            }
            q = p;
            /* comment:Store all current |lc_code| values */ p = triel[q];
            firstchild = true;
            {
                register integer for_end;
                c = 0;
                for_end = 255;
                if (c <= for_end)
                    do
                        if ((eqtb[LCCODEBASE + c].hh.v.RH > 0) ||
                            ((c == 255) && firstchild)) {
                            if (p == 0) /* comment:Insert a new trie node
                                           between |q| and |p|, and ma */
                            {
                                if (trieptr == triesize)
                                    overflow(/* str 'pattern memory' */ 1365,
                                             triesize);
                                incr(trieptr);
                                trier[trieptr] = p;
                                p = trieptr;
                                triel[p] = 0;
                                if (firstchild)
                                    triel[q] = p;
                                else
                                    trier[q] = p;
                                triec[p] = c;
                                trieo[p] = mintrieop;
                            } else
                                triec[p] = c;
                            trieo[p] = eqtb[LCCODEBASE + c].hh.v.RH;
                            q = p;
                            p = trier[q];
                            firstchild = false;
                        }
                    while (c++ < for_end);
            }
            if (firstchild)
                triel[q] = 0;
            else
                trier[q] = 0;
        }
    } else {

        {
            if (interaction == ERRORSTOPMODE)
                ;
            if (filelineerrorstylep)
                printfileline();
            else
                printnl(/* str '! ' */ 264);
            print(/* str 'Too late for ' */ 1366);
        }
        printesc(/* str 'patterns' */ 1367);
        {
            helpptr = 1;
            helpline[0] =
                /* str 'All patterns must be given before typesetting beg' */
                1368;
        }
        error();
        mem[memtop - 12].hh.v.RH = scantoks(false, false);
        flushlist(defref);
    }
}
void inittrie(void) {
    inittrie_regmem triepointer p;
    integer j, k, t;
    triepointer r, s;
    /* comment:Get ready to compress the trie */
    /* comment:Sort \(t)the hyphenation op tables into proper ord */ opstart
        [0] = -(integer)mintrieop;
    {
        register integer for_end;
        j = 1;
        for_end = 255;
        if (j <= for_end)
            do
                opstart[j] = opstart[j - 1] + trieused[j - 1];
            while (j++ < for_end);
    }
    {
        register integer for_end;
        j = 1;
        for_end = trieopptr;
        if (j <= for_end)
            do
                trieophash[j] = opstart[trieoplang[j]] + trieopval[j];
            while (j++ < for_end);
    }
    {
        register integer for_end;
        j = 1;
        for_end = trieopptr;
        if (j <= for_end)
            do
                while (trieophash[j] > j) {

                    k = trieophash[j];
                    t = hyfdistance[k];
                    hyfdistance[k] = hyfdistance[j];
                    hyfdistance[j] = t;
                    t = hyfnum[k];
                    hyfnum[k] = hyfnum[j];
                    hyfnum[j] = t;
                    t = hyfnext[k];
                    hyfnext[k] = hyfnext[j];
                    hyfnext[j] = t;
                    trieophash[j] = trieophash[k];
                    trieophash[k] = k;
                }
            while (j++ < for_end);
    }
    {
        register integer for_end;
        p = 0;
        for_end = triesize;
        if (p <= for_end)
            do
                triehash[p] = 0;
            while (p++ < for_end);
    }
    trier[0] = compresstrie(trier[0]);
    triel[0] = compresstrie(triel[0]);
    {
        register integer for_end;
        p = 0;
        for_end = trieptr;
        if (p <= for_end)
            do
                triehash[p] = 0;
            while (p++ < for_end);
    }
    {
        register integer for_end;
        p = 0;
        for_end = 255;
        if (p <= for_end)
            do
                triemin[p] = p + 1;
            while (p++ < for_end);
    }
    trietrl[0] = 1;
    triemax = 0;
    if (triel[0] != 0) {
        firstfit(triel[0]);
        triepack(triel[0]);
    }
    if (trier[0] != 0) /* comment:Pack all stored |hyph_codes| */
    {
        if (triel[0] == 0) {
            register integer for_end;
            p = 0;
            for_end = 255;
            if (p <= for_end)
                do
                    triemin[p] = p + 2;
                while (p++ < for_end);
        }
        firstfit(trier[0]);
        triepack(trier[0]);
        hyphstart = triehash[trier[0]];
    }
    /* comment:Move the data into |trie| */ if (triemax == 0) {
        {
            register integer for_end;
            r = 0;
            for_end = 256;
            if (r <= for_end)
                do {
                    trietrl[r] = 0;
                    trietro[r] = mintrieop;
                    trietrc[r] = MINQUARTERWORD;
                } while (r++ < for_end);
        }
        triemax = 256;
    } else {

        if (trier[0] > 0)
            triefix(trier[0]);
        if (triel[0] > 0)
            triefix(triel[0]);
        r = 0;
        do {
            s = trietrl[r];
            {
                trietrl[r] = 0;
                trietro[r] = mintrieop;
                trietrc[r] = MINQUARTERWORD;
            }
            r = s;
        } while (!(r > triemax));
    }
    trietrc[0] = /* str '?' */ 63;
    trienotready = false;
}
#endif /* INITEX */
void zlinebreak(boolean d) {
    /* @d10404@ */ /* @d10405@ */ /* @d10406@ */ /* @d10407@ */ /* @d10408@ */
    linebreak_regmem
        /* comment:Local variables for line breaking */ halfword q,
        r, s, prevs;
    internalfontnumber f;
    smallnumber j;
    unsigned char c;
    packbeginline = curlist.mlfield;
    /* comment:Get ready to start line breaking */ mem[memtop - 3].hh.v.RH =
        mem[curlist.headfield].hh.v.RH;
    if ((curlist.tailfield >= himemmin)) {
        mem[curlist.tailfield].hh.v.RH = newpenalty(INFPENALTY);
        curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
    } else if (mem[curlist.tailfield].hh.b0 != GLUENODE) {
        mem[curlist.tailfield].hh.v.RH = newpenalty(INFPENALTY);
        curlist.tailfield = mem[curlist.tailfield].hh.v.RH;
    } else {

        mem[curlist.tailfield].hh.b0 = PENALTYNODE;
        deleteglueref(mem[curlist.tailfield + 1].hh.v.LH);
        flushnodelist(mem[curlist.tailfield + 1].hh.v.RH);
        mem[curlist.tailfield + 1].cint = INFPENALTY;
    }
    mem[curlist.tailfield].hh.v.RH = newparamglue(PARFILLSKIPCODE);
    lastlinefill = mem[curlist.tailfield].hh.v.RH;
    initcurlang = curlist.pgfield % 65536L;
    initlhyf = curlist.pgfield / 4194304L;
    initrhyf = (curlist.pgfield / 65536L) % 64;
    popnest();
    noshrinkerroryet = true;
    if ((mem[eqtb[GLUEBASE + LEFTSKIPCODE].hh.v.RH].hh.b1 != NORMAL) &&
        (mem[eqtb[/* @d10422@ */ /* @d10423@ */
                  26635]
                 .hh.v.RH +
             3]
             .cint != 0)) {
        eqtb[GLUEBASE + LEFTSKIPCODE].hh.v.RH =
            finiteshrink(eqtb[GLUEBASE + LEFTSKIPCODE].hh.v.RH);
    }
    if ((mem[eqtb[GLUEBASE + RIGHTSKIPCODE].hh.v.RH].hh.b1 != NORMAL) &&
        (mem[eqtb[/* @d10431@ */ /* @d10432@ */
                  26636]
                 .hh.v.RH +
             3]
             .cint != 0)) {
        eqtb[GLUEBASE + RIGHTSKIPCODE].hh.v.RH =
            finiteshrink(eqtb[GLUEBASE + RIGHTSKIPCODE].hh.v.RH);
    }
    q = eqtb[GLUEBASE + LEFTSKIPCODE].hh.v.RH;
    r = eqtb[GLUEBASE + RIGHTSKIPCODE].hh.v.RH;
    background[1] = mem[q + WIDTHOFFSET].cint + mem[r + WIDTHOFFSET].cint;
    background[2] = 0;
    background[3] = 0;
    background[4] = 0;
    background[5] = 0;
    background[2 + mem[q].hh.b0] = mem[q + 2].cint;
    background[2 + mem[r].hh.b0] =
        background[2 + mem[r].hh.b0] + mem[r + 2].cint;
    background[6] = mem[q + 3].cint + mem[r + 3].cint;
    if (eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) {
        background[7] = 0;
        background[8] = 0;
        maxstretchratio = -1;
        maxshrinkratio = -1;
        curfontstep = -1;
        prevcharp = TEXNULL;
    }
    /* comment:Check for special treatment of last line of paragr */
    dolastlinefit = false;
    activenodesize = ACTIVENODESIZENORMAL;
    if (eqtb[INTBASE + LASTLINEFITCODE].cint > 0) {
        q = mem[lastlinefill + 1].hh.v.LH;
        if ((mem[q + 2].cint > 0) && (mem[q].hh.b0 > NORMAL)) {

            if ((background[3] == 0) && (background[4] == 0) &&
                (background[5] == 0)) {
                dolastlinefit = true;
                activenodesize = ACTIVENODESIZEEXTENDED;
                fillwidth[0] = 0;
                fillwidth[1] = 0;
                fillwidth[2] = 0;
                fillwidth[mem[q].hh.b0 - 1] = mem[q + 2].cint;
            }
        }
    }
    minimumdemerits = 1073741823L;
    minimaldemerits[TIGHTFIT] = 1073741823L;
    minimaldemerits[DECENTFIT] = 1073741823L;
    minimaldemerits[LOOSEFIT] = 1073741823L;
    minimaldemerits[VERYLOOSEFIT] = 1073741823L;
    if (eqtb[PARSHAPELOC].hh.v.RH == TEXNULL) {

        if (eqtb[DIMENBASE + HANGINDENTCODE].cint == 0) {
            lastspecialline = 0;
            secondwidth = eqtb[DIMENBASE + HSIZECODE].cint;
            secondindent = 0;
        } else /* comment:Set line length parameters in preparation for hang */
        {

            lastspecialline = abs(eqtb[INTBASE + HANGAFTERCODE].cint);
            if (eqtb[INTBASE + HANGAFTERCODE].cint < 0) {
                firstwidth = eqtb[DIMENBASE + HSIZECODE].cint -
                             abs(eqtb[DIMENBASE + HANGINDENTCODE].cint);
                if (eqtb[DIMENBASE + HANGINDENTCODE].cint >= 0)
                    firstindent = eqtb[DIMENBASE + HANGINDENTCODE].cint;
                else
                    firstindent = 0;
                secondwidth = eqtb[DIMENBASE + HSIZECODE].cint;
                secondindent = 0;
            } else {

                firstwidth = eqtb[DIMENBASE + HSIZECODE].cint;
                firstindent = 0;
                secondwidth = eqtb[DIMENBASE + HSIZECODE].cint -
                              abs(eqtb[DIMENBASE + HANGINDENTCODE].cint);
                if (eqtb[DIMENBASE + HANGINDENTCODE].cint >= 0)
                    secondindent = eqtb[DIMENBASE + HANGINDENTCODE].cint;
                else
                    secondindent = 0;
            }
        }
    } else {

        lastspecialline = mem[eqtb[PARSHAPELOC].hh.v.RH].hh.v.LH - 1;
        secondwidth =
            mem[eqtb[PARSHAPELOC].hh.v.RH + 2 * (lastspecialline + 1)].cint;
        secondindent =
            mem[eqtb[PARSHAPELOC].hh.v.RH + 2 * lastspecialline + 1].cint;
    }
    if (eqtb[INTBASE + LOOSENESSCODE].cint == 0)
        easyline = lastspecialline;
    else
        easyline = 2147483647L;
    /* comment:Find optimal breakpoints */ threshold =
        eqtb[INTBASE + PRETOLERANCECODE].cint;
    if (threshold >= 0) {
        ;
#ifdef STAT
        if (eqtb[INTBASE + TRACINGPARAGRAPHSCODE].cint > 0) {
            begindiagnostic();
            printnl(/* str '@@firstpass' */ 1347);
        }
#endif /* STAT */
        secondpass = false;
        finalpass = false;
    } else {

        threshold = eqtb[INTBASE + TOLERANCECODE].cint;
        secondpass = true;
        finalpass = (eqtb[DIMENBASE + EMERGENCYSTRETCHCODE].cint <= 0);
        ;
#ifdef STAT
        if (eqtb[INTBASE + TRACINGPARAGRAPHSCODE].cint > 0)
            begindiagnostic();
#endif /* STAT */
    }
    while (true) {

        if (threshold > INFBAD)
            threshold = INFBAD;
        if (secondpass) /* comment:Initialize for hyphenating a paragraph */
        {
            ;
#ifdef INITEX
            if (trienotready)
                inittrie();
#endif /* INITEX */
            curlang = initcurlang;
            lhyf = initlhyf;
            rhyf = initrhyf;
            if (trietrc[hyphstart + curlang] != curlang)
                hyphindex = 0;
            else
                hyphindex = trietrl[hyphstart + curlang];
        }
        /* comment:Create an active breakpoint representing the begin */ q =
            getnode(activenodesize);
        mem[q].hh.b0 = UNHYPHENATED;
        mem[q].hh.b1 = DECENTFIT;
        mem[q].hh.v.RH = memtop - 7;
        mem[q + 1].hh.v.RH = TEXNULL;
        mem[q + 1].hh.v.LH = curlist.pgfield + 1;
        mem[q + 2].cint = 0;
        mem[memtop - 7].hh.v.RH = q;
        if (dolastlinefit) /* comment:Initialize additional fields of the first
                              active n */
        {
            mem[q + 3].cint = 0;
            mem[q + 4].cint = 0;
        }
        activewidth[1] = background[1];
        activewidth[2] = background[2];
        activewidth[3] = background[3];
        activewidth[4] = background[4];
        activewidth[5] = background[5];
        activewidth[6] = background[6];
        if (eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) {
            activewidth[7] = background[7];
            activewidth[8] = background[8];
        }
        passive = TEXNULL;
        printednode = memtop - 3;
        passnumber = 0;
        fontinshortdisplay = FONTBASE;
        curp = mem[memtop - 3].hh.v.RH;
        autobreaking = true;
        prevp = curp;
        prevcharp = TEXNULL;
        prevlegal = TEXNULL;
        rejectedcurp = TEXNULL;
        tryprevbreak = false;
        beforerejectedcurp = false;
        firstp = curp;
        while ((curp != TEXNULL) &&
               (mem[memtop - 7].hh.v.RH !=
                memtop - 7)) /* comment:Call |try_break| if |cur_p| is a legal
                                breakpoint; */
        {

            if ((curp >= himemmin)) /* comment:Advance \(c)|cur_p| to the node
                                       following the pres */
            {
                prevp = curp;
                do {
                    f = mem[curp].hh.b0;
                    activewidth[1] =
                        activewidth[1] +
                        fontinfo[widthbase[f] +
                                 fontinfo[charbase[f] +
                                          effectivechar(true, f,
                                                        mem[curp].hh.b1)]
                                     .qqqq.b0]
                            .cint;
                    if ((eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) &&
                        checkexpandpars(f)) {
                        prevcharp = curp;
                        activewidth[7] =
                            activewidth[7] + charstretch(f, mem[curp].hh.b1);
                        activewidth[8] =
                            activewidth[8] + charshrink(f, mem[curp].hh.b1);
                    }
                    curp = mem[curp].hh.v.RH;
                } while (!(!(curp >= himemmin)));
            }
            switch (mem[curp].hh.b0) {
            case HLISTNODE:
            case VLISTNODE:
            case RULENODE:
                activewidth[1] = activewidth[1] + mem[curp + WIDTHOFFSET].cint;
                break;
            case WHATSITNODE:
                /* comment:Advance \(p)past a whatsit node in the \(l)|line_b */
                {

                    if (mem[curp].hh.b1 == LANGUAGENODE) {
                        curlang = mem[curp + 1].hh.v.RH;
                        lhyf = mem[curp + 1].hh.b0;
                        rhyf = mem[curp + 1].hh.b1;
                    }
                    if ((mem[curp].hh.b1 == /* @d10523@ */ 10) ||
                        (mem[curp].hh.b1 == /* @d10524@ */ 12))
                        activewidth[1] = activewidth[1] + mem[curp + 1].cint;
                }
                break;
            case GLUENODE: {
                /* comment:If node |cur_p| is a legal breakpoint, call |try_b */
                if (autobreaking) {
                    if ((prevp >= himemmin))
                        trybreak(0, UNHYPHENATED);
                    else if ((mem[prevp].hh.b0 < MATHNODE))
                        trybreak(0, UNHYPHENATED);
                    else if ((mem[prevp].hh.b0 == KERNNODE) &&
                             (mem[prevp].hh.b1 != EXPLICIT))
                        trybreak(0, UNHYPHENATED);
                }
                if ((mem[mem[curp + 1].hh.v.LH].hh.b1 != NORMAL) &&
                    (mem[mem[curp + 1].hh.v.LH + 3].cint != 0)) {
                    mem[curp + 1].hh.v.LH = finiteshrink(mem[curp + 1].hh.v.LH);
                }
                q = mem[curp + 1].hh.v.LH;
                activewidth[1] = activewidth[1] + mem[q + WIDTHOFFSET].cint;
                activewidth[2 + mem[q].hh.b0] =
                    activewidth[2 + mem[q].hh.b0] + mem[q + 2].cint;
                activewidth[6] = activewidth[6] + mem[q + 3].cint;
                if (secondpass && autobreaking) /* comment:Try to hyphenate the
                                                   following word */
                {
                    prevs = curp;
                    s = mem[prevs].hh.v.RH;
                    if (s != TEXNULL) {
                        /* comment:Skip to node |ha|, or |goto done1| if no
                         * hyphenati */
                        while (true) {

                            if ((s >= himemmin)) {
                                c = mem[s].hh.b1;
                                hf = mem[s].hh.b0;
                            } else if (mem[s].hh.b0 == LIGATURENODE) {

                                if (mem[s + 1].hh.v.RH == TEXNULL)
                                    goto lablinebreak22continue;
                                else {

                                    q = mem[s + 1].hh.v.RH;
                                    c = mem[q].hh.b1;
                                    hf = mem[q].hh.b0;
                                }
                            } else if ((mem[s].hh.b0 == KERNNODE) &&
                                       (mem[s].hh.b1 == /* @d10540@ */
                                        0))
                                goto lablinebreak22continue;
                            else if ((mem[s].hh.b0 == MATHNODE) &&
                                     (mem[s].hh.b1 >= LCODE))
                                goto lablinebreak22continue;
                            else if (mem[s].hh.b0 == WHATSITNODE) {
                                /* comment:Advance \(p)past a whatsit node in
                                 * the \(p)pre-hyp */
                                if (mem[s].hh.b1 == LANGUAGENODE) {
                                    curlang = mem[s + 1].hh.v.RH;
                                    lhyf = mem[s + 1].hh.b0;
                                    rhyf = mem[s + 1].hh.b1;
                                    if (trietrc[hyphstart + curlang] != curlang)
                                        hyphindex = 0;
                                    else
                                        hyphindex =
                                            trietrl[hyphstart + curlang];
                                }
                                goto lablinebreak22continue;
                            } else
                                goto lablinebreak31done1;
                            if (hyphindex == 0)
                                hc[0] = eqtb[LCCODEBASE + c].hh.v.RH;
                            else if (trietrc[hyphindex + c] != c)
                                hc[0] = 0;
                            else
                                hc[0] = trietro[hyphindex + c];
                            if (hc[0] != 0) {

                                if ((hc[0] == c) ||
                                    (eqtb[INTBASE + UCHYPHCODE].cint > 0))
                                    goto lablinebreak32done2;
                                else
                                    goto lablinebreak31done1;
                            }
                        lablinebreak22continue:
                            prevs = s;
                            s = mem[prevs].hh.v.RH;
                        }
                    lablinebreak32done2:
                        hyfchar = hyphenchar[hf];
                        if (hyfchar < 0)
                            goto lablinebreak31done1;
                        if (hyfchar > 255)
                            goto lablinebreak31done1;
                        ha = prevs;
                        if (lhyf + rhyf > 63)
                            goto lablinebreak31done1;
                        /* comment:Skip to node |hb|, putting letters into |hu|
                         * and | */
                        hn = 0;
                        while (true) {

                            if ((s >= himemmin)) {
                                if (mem[s].hh.b0 != hf)
                                    goto lablinebreak33done3;
                                hyfbchar = mem[s].hh.b1;
                                c = hyfbchar;
                                if (hyphindex == 0)
                                    hc[0] = eqtb[LCCODEBASE + c].hh.v.RH;
                                else if (trietrc[hyphindex + c] != c)
                                    hc[0] = 0;
                                else
                                    hc[0] = trietro[hyphindex + c];
                                if (hc[0] == 0)
                                    goto lablinebreak33done3;
                                if (hn == 63)
                                    goto lablinebreak33done3;
                                hb = s;
                                incr(hn);
                                hu[hn] = c;
                                hc[hn] = hc[0];
                                hyfbchar = 256;
                                hm[hn] = mem[s].hh.me;
                            } else if (mem[s].hh.b0 ==
                                       LIGATURENODE) /* comment:Move the
                                                        characters of a ligature
                                                        node to |hu| and */
                            {
                                if (mem[s + 1].hh.b0 != hf)
                                    goto lablinebreak33done3;
                                j = hn;
                                q = mem[s + 1].hh.v.RH;
                                if (q > TEXNULL)
                                    hyfbchar = mem[q].hh.b1;
                                while (q > TEXNULL) {

                                    c = mem[q].hh.b1;
                                    if (hyphindex == 0)
                                        hc[0] = eqtb[LCCODEBASE + c].hh.v.RH;
                                    else if (trietrc[hyphindex + c] != c)
                                        hc[0] = 0;
                                    else
                                        hc[0] = trietro[hyphindex + c];
                                    if (hc[0] == 0)
                                        goto lablinebreak33done3;
                                    if (j == 63)
                                        goto lablinebreak33done3;
                                    incr(j);
                                    hu[j] = c;
                                    hc[j] = hc[0];
                                    hm[j] = mem[q].hh.me;
                                    q = mem[q].hh.v.RH;
                                }
                                hb = s;
                                hn = j;
                                if (odd(mem[s].hh.b1))
                                    hyfbchar = fontbchar[hf];
                                else
                                    hyfbchar = 256;
                            } else if ((mem[s].hh.b0 == KERNNODE) &&
                                       (mem[s].hh.b1 == /* @d10572@ */
                                        0)) {
                                hb = s;
                                hyfbchar = fontbchar[hf];
                            } else
                                goto lablinebreak33done3;
                            s = mem[s].hh.v.RH;
                        }
                    lablinebreak33done3:;
                        /* comment:Check that the nodes following |hb| permit
                         * hyphena */
                        if (hn < lhyf + rhyf)
                            goto lablinebreak31done1;
                        while (true) {

                            if (!((s >= himemmin)))
                                switch (mem[s].hh.b0) {
                                case LIGATURENODE:;
                                    break;
                                case KERNNODE:
                                    if (mem[s].hh.b1 != NORMAL)
                                        goto lablinebreak34done4;
                                    break;
                                case WHATSITNODE:
                                case GLUENODE:
                                case PENALTYNODE:
                                case INSNODE:
                                case ADJUSTNODE:
                                case MARKNODE:
                                    goto lablinebreak34done4;
                                    break;
                                case MATHNODE:
                                    if (mem[s].hh.b1 >= LCODE)
                                        goto lablinebreak34done4;
                                    else
                                        goto lablinebreak31done1;
                                    break;
                                default:
                                    goto lablinebreak31done1;
                                    break;
                                }
                            s = mem[s].hh.v.RH;
                        }
                    lablinebreak34done4:;
                        hyphenate();
                    }
                lablinebreak31done1:;
                }
            } break;
            case KERNNODE:
                if (mem[curp].hh.b1 == EXPLICIT) {
                    if (!(mem[curp].hh.v.RH >= himemmin) && autobreaking) {

                        if (mem[mem[curp].hh.v.RH].hh.b0 == GLUENODE)
                            trybreak(0, UNHYPHENATED);
                    }
                    activewidth[1] =
                        activewidth[1] + mem[curp + WIDTHOFFSET].cint;
                } else {

                    activewidth[1] =
                        activewidth[1] + mem[curp + WIDTHOFFSET].cint;
                    if ((eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) &&
                        (mem[curp].hh.b1 == NORMAL)) {
                        activewidth[7] = activewidth[7] + kernstretch(curp);
                        activewidth[8] = activewidth[8] + kernshrink(curp);
                    }
                }
                break;
            case LIGATURENODE: {
                f = mem[curp + 1].hh.b0;
                activewidth[1] =
                    activewidth[1] +
                    fontinfo[widthbase[f] +
                             fontinfo[charbase[f] +
                                      effectivechar(true, f,
                                                    mem[curp + 1].hh.b1)]
                                 .qqqq.b0]
                        .cint;
                if ((eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) &&
                    checkexpandpars(f)) {
                    prevcharp = curp;
                    activewidth[7] =
                        activewidth[7] + charstretch(f, mem[curp + 1].hh.b1);
                    activewidth[8] =
                        activewidth[8] + charshrink(f, mem[curp + 1].hh.b1);
                }
            } break;
            case DISCNODE:
                /* comment:Try to break after a discretionary fragment, then  */
                {

                    s = mem[curp + 1].hh.v.LH;
                    discwidth[1] = 0;
                    if (eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) {
                        discwidth[7] = 0;
                        discwidth[8] = 0;
                    }
                    if (s == TEXNULL)
                        trybreak(eqtb[INTBASE + EXHYPHENPENALTYCODE].cint,
                                 HYPHENATED);
                    else {

                        do {
                            /* comment:Add the width of node |s| to |disc_width|
                             */
                            if ((s >= himemmin)) {
                                f = mem[s].hh.b0;
                                discwidth[1] =
                                    discwidth[1] +
                                    fontinfo[widthbase[f] +
                                             fontinfo[charbase[f] +
                                                      effectivechar(
                                                          true, f,
                                                          mem[s].hh.b1)]
                                                 .qqqq.b0]
                                        .cint;
                                if ((eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint >
                                     1) &&
                                    checkexpandpars(f)) {
                                    prevcharp = s;
                                    discwidth[7] = discwidth[7] +
                                                   charstretch(f, mem[s].hh.b1);
                                    discwidth[8] = discwidth[8] +
                                                   charshrink(f, mem[s].hh.b1);
                                }
                            } else
                                switch (mem[s].hh.b0) {
                                case LIGATURENODE: {
                                    f = mem[s + 1].hh.b0;
                                    discwidth[1] =
                                        discwidth[1] +
                                        fontinfo[widthbase[f] +
                                                 fontinfo[charbase[f] +
                                                          effectivechar(
                                                              true, f,
                                                              mem[s + 1].hh.b1)]
                                                     .qqqq.b0]
                                            .cint;
                                    if ((eqtb[/* @d10618@ */ /* @d10619@ */
                                              29356]
                                             .cint > 1) &&
                                        checkexpandpars(f)) {
                                        prevcharp = s;
                                        discwidth[7] =
                                            discwidth[7] +
                                            charstretch(f, mem[s + 1].hh.b1);
                                        discwidth[8] =
                                            discwidth[8] +
                                            charshrink(f, mem[s + 1].hh.b1);
                                    }
                                } break;
                                case HLISTNODE:
                                case VLISTNODE:
                                case RULENODE:
                                case KERNNODE: {
                                    discwidth[1] = discwidth[1] +
                                                   mem[s + WIDTHOFFSET].cint;
                                    if ((mem[s].hh.b0 == KERNNODE) &&
                                        (eqtb[/* @d10626@ */ /* @d10627@ */
                                              29356]
                                             .cint > 1) &&
                                        (mem[s].hh.b1 == NORMAL)) {
                                        discwidth[7] =
                                            discwidth[7] + kernstretch(s);
                                        discwidth[8] =
                                            discwidth[8] + kernshrink(s);
                                    }
                                } break;
                                default:
                                    confusion(/* str 'disc3' */ 1351);
                                    break;
                                }
                            s = mem[s].hh.v.RH;
                        } while (!(s == TEXNULL));
                        activewidth[1] = activewidth[1] + discwidth[1];
                        if (eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) {
                            activewidth[7] = activewidth[7] + discwidth[7];
                            activewidth[8] = activewidth[8] + discwidth[8];
                        }
                        trybreak(eqtb[INTBASE + HYPHENPENALTYCODE].cint,
                                 HYPHENATED);
                        activewidth[1] = activewidth[1] - discwidth[1];
                        if (eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint > 1) {
                            activewidth[7] = activewidth[7] - discwidth[7];
                            activewidth[8] = activewidth[8] - discwidth[8];
                        }
                    }
                    r = mem[curp].hh.b1;
                    s = mem[curp].hh.v.RH;
                    while (r > 0) {

                        /* comment:Add the width of node |s| to |act_width| */
                        if ((s >= himemmin)) {
                            f = mem[s].hh.b0;
                            activewidth[1] =
                                activewidth[1] +
                                fontinfo[widthbase[f] +
                                         fontinfo[charbase[f] +
                                                  effectivechar(true, f,
                                                                mem[s].hh.b1)]
                                             .qqqq.b0]
                                    .cint;
                            if ((eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint >
                                 1) &&
                                checkexpandpars(f)) {
                                prevcharp = s;
                                activewidth[7] = activewidth[7] +
                                                 charstretch(f, mem[s].hh.b1);
                                activewidth[8] = activewidth[8] +
                                                 charshrink(f, mem[s].hh.b1);
                            }
                        } else
                            switch (mem[s].hh.b0) {
                            case LIGATURENODE: {
                                f = mem[s + 1].hh.b0;
                                activewidth[1] =
                                    activewidth[1] +
                                    fontinfo[widthbase[f] +
                                             fontinfo[charbase[f] +
                                                      effectivechar(
                                                          true, f,
                                                          mem[s + 1].hh.b1)]
                                                 .qqqq.b0]
                                        .cint;
                                if ((eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint >
                                     1) &&
                                    checkexpandpars(f)) {
                                    prevcharp = s;
                                    activewidth[7] =
                                        activewidth[7] +
                                        charstretch(f, mem[s + 1].hh.b1);
                                    activewidth[8] =
                                        activewidth[8] +
                                        charshrink(f, mem[s + 1].hh.b1);
                                }
                            } break;
                            case HLISTNODE:
                            case VLISTNODE:
                            case RULENODE:
                            case KERNNODE: {
                                activewidth[1] =
                                    activewidth[1] + mem[s + WIDTHOFFSET].cint;
                                if ((mem[s].hh.b0 == KERNNODE) &&
                                    (eqtb[INTBASE + PDFADJUSTSPACINGCODE].cint >
                                     1) &&
                                    (mem[s].hh.b1 == NORMAL)) {
                                    activewidth[7] =
                                        activewidth[7] + kernstretch(s);
                                    activewidth[8] =
                                        activewidth[8] + kernshrink(s);
                                }
                            } break;
                            default:
                                confusion(/* str 'disc4' */ 1352);
                                break;
                            }
                        decr(r);
                        s = mem[s].hh.v.RH;
                    }
                    prevp = curp;
                    curp = s;
                    goto lablinebreak35done5;
                }
                break;
            case MATHNODE: {
                if (mem[curp].hh.b1 < LCODE)
                    autobreaking = odd(mem[curp].hh.b1);
                {
                    if (!(mem[curp].hh.v.RH >= himemmin) && autobreaking) {

                        if (mem[mem[curp].hh.v.RH].hh.b0 == GLUENODE)
                            trybreak(0, UNHYPHENATED);
                    }
                    activewidth[1] =
                        activewidth[1] + mem[curp + WIDTHOFFSET].cint;
                }
            } break;
            case PENALTYNODE:
                trybreak(mem[curp + 1].cint, UNHYPHENATED);
                break;
            case MARKNODE:
            case INSNODE:
            case ADJUSTNODE:;
                break;
            default:
                confusion(/* str 'paragraph' */ 1350);
                break;
            }
            prevp = curp;
            curp = mem[curp].hh.v.RH;
        lablinebreak35done5:;
        }
        if (curp == TEXNULL) /* comment:Try the final line break at the end
                                     of the paragra */
        {
            trybreak(/* @d10667@ */ -10000, HYPHENATED);
            if (mem[memtop - 7].hh.v.RH != memtop - 7) {
                /* comment:Find an active node with fewest demerits */ r =
                    mem[memtop - 7].hh.v.RH;
                fewestdemerits = 1073741823L;
                do {
                    if (mem[r].hh.b0 != DELTANODE) {
                        if (mem[r + 2].cint < fewestdemerits) {
                            fewestdemerits = mem[r + 2].cint;
                            bestbet = r;
                        }
                    }
                    r = mem[r].hh.v.RH;
                } while (!(r == memtop - 7));
                bestline = mem[bestbet + 1].hh.v.LH;
                if (eqtb[INTBASE + LOOSENESSCODE].cint == 0)
                    goto lablinebreak30done;
                /* comment:Find the best active node for the desired loosenes */
                {

                    r = mem[memtop - 7].hh.v.RH;
                    actuallooseness = 0;
                    do {
                        if (mem[r].hh.b0 != DELTANODE) {
                            linediff = mem[r + 1].hh.v.LH - bestline;
                            if (((linediff < actuallooseness) &&
                                 (eqtb[INTBASE + LOOSENESSCODE].cint <=
                                  linediff)) ||
                                ((linediff > actuallooseness) &&
                                 (eqtb[/* @d10678@ */ /* @d10679@ */
                                       29296]
                                      .cint >= linediff))) {
                                bestbet = r;
                                actuallooseness = linediff;
                                fewestdemerits = mem[r + 2].cint;
                            } else if ((linediff == actuallooseness) &&
                                       (mem[r + 2].cint < fewestdemerits)) {
                                bestbet = r;
                                fewestdemerits = mem[r + 2].cint;
                            }
                        }
                        r = mem[r].hh.v.RH;
                    } while (!(r == memtop - 7));
                    bestline = mem[bestbet + 1].hh.v.LH;
                }
                if ((actuallooseness == eqtb[INTBASE + LOOSENESSCODE].cint) ||
                    finalpass)
                    goto lablinebreak30done;
            }
        }
        /* comment:Clean up the memory by removing the break nodes */ q =
            mem[memtop - 7].hh.v.RH;
        while (q != memtop - 7) {

            curp = mem[q].hh.v.RH;
            if (mem[q].hh.b0 == DELTANODE)
                freenode(q, DELTANODESIZE);
            else
                freenode(q, activenodesize);
            q = curp;
        }
        q = passive;
        while (q != TEXNULL) {

            curp = mem[q].hh.v.RH;
            freenode(q, PASSIVENODESIZE);
            q = curp;
        }
        if (!secondpass) {
            ;
#ifdef STAT
            if (eqtb[INTBASE + TRACINGPARAGRAPHSCODE].cint > 0)
                printnl(/* str '@@secondpass' */ 1348);
#endif /* STAT */
            threshold = eqtb[INTBASE + TOLERANCECODE].cint;
            secondpass = true;
            finalpass = (eqtb[DIMENBASE + EMERGENCYSTRETCHCODE].cint <= 0);
        } else {

            ;
#ifdef STAT
            if (eqtb[INTBASE + TRACINGPARAGRAPHSCODE].cint > 0)
                printnl(/* str '@@emergencypass' */ 1349);
#endif /* STAT */
            background[2] =
                background[2] + eqtb[DIMENBASE + EMERGENCYSTRETCHCODE].cint;
            finalpass = true;
        }
    }
lablinebreak30done:;
#ifdef STAT
    if (eqtb[INTBASE + TRACINGPARAGRAPHSCODE].cint > 0) {
        enddiagnostic(true);
        normalizeselector();
    }
#endif                 /* STAT */
    if (dolastlinefit) /* comment:Adjust \(t)the final line of the paragraph */
    {

        if (mem[bestbet + 3].cint == 0)
            dolastlinefit = false;
        else {

            q = newspec(mem[lastlinefill + 1].hh.v.LH);
            deleteglueref(mem[lastlinefill + 1].hh.v.LH);
            mem[q + WIDTHOFFSET].cint = mem[q + WIDTHOFFSET].cint +
                                        mem[bestbet + 3].cint -
                                        mem[bestbet + 4].cint;
            mem[q + 2].cint = 0;
            mem[lastlinefill + 1].hh.v.LH = q;
        }
    }
    /* comment:Break the paragraph at the chosen breakpoints, jus */
    postlinebreak(d);
    /* comment:Clean up the memory by removing the break nodes */ q =
        mem[memtop - 7].hh.v.RH;
    while (q != memtop - 7) {

        curp = mem[q].hh.v.RH;
        if (mem[q].hh.b0 == DELTANODE)
            freenode(q, DELTANODESIZE);
        else
            freenode(q, activenodesize);
        q = curp;
    }
    q = passive;
    while (q != TEXNULL) {

        curp = mem[q].hh.v.RH;
        freenode(q, PASSIVENODESIZE);
        q = curp;
    }
    packbeginline = 0;
}
void newhyphexceptions(void) {
    /* @d10805@ */ /* @d10806@ */ /* @d10807@ */ /* @d10808@ */ /* @d10809@ */
    newhyphexceptions_regmem unsigned char n;
    unsigned char j;
    hyphpointer h;
    strnumber k;
    halfword p;
    halfword q;
    strnumber s;
    poolpointer u, v;
    scanleftbrace();
    if (eqtb[INTBASE + LANGUAGECODE].cint <= 0)
        curlang = 0;
    else if (eqtb[INTBASE + LANGUAGECODE].cint > 255)
        curlang = 0;
    else
        curlang = eqtb[INTBASE + LANGUAGECODE].cint;
    ;
#ifdef INITEX
    if (trienotready) {
        hyphindex = 0;
        goto labnewhyphexceptions46not_found1;
    }
#endif /* INITEX */
    if (trietrc[hyphstart + curlang] != curlang)
        hyphindex = 0;
    else
        hyphindex = trietrl[hyphstart + curlang];
labnewhyphexceptions46not_found1
    : /* comment:Enter as many hyphenation exceptions as are listed */
    n = 0;
    p = TEXNULL;
    while (true) {

        getxtoken();
    labnewhyphexceptions21reswitch:
        switch (curcmd) {
        case LETTER:
        case OTHERCHAR:
        case CHARGIVEN:
            /* comment:Append a new letter or hyphen */
            if (curchr ==
                /* str '-' */ 45) /* comment:Append the value |n| to list |p| */
            {
                if (n < 63) {
                    q = getavail();
                    mem[q].hh.v.RH = p;
                    mem[q].hh.v.LH = n;
                    p = q;
                }
            } else {

                if (hyphindex == 0)
                    hc[0] = eqtb[LCCODEBASE + curchr].hh.v.RH;
                else if (trietrc[hyphindex + curchr] != curchr)
                    hc[0] = 0;
                else
                    hc[0] = trietro[hyphindex + curchr];
                if (hc[0] == 0) {
                    {
                        if (interaction == ERRORSTOPMODE)
                            ;
                        if (filelineerrorstylep)
                            printfileline();
                        else
                            printnl(/* str '! ' */ 264);
                        print(/* str 'Not a letter' */ 1359);
                    }
                    {
                        helpptr = 2;
                        helpline[1] = /* str 'Letters in \hyphenation words must
                                         have \lccode>0' */
                            1360;
                        helpline[0] = /* str 'Proceed; I'll ignore the character
                                         I just read.' */
                            1361;
                    }
                    error();
                } else if (n < 63) {
                    incr(n);
                    hc[n] = hc[0];
                }
            }
            break;
        case CHARNUM: {
            scancharnum();
            curchr = curval;
            curcmd = CHARGIVEN;
            goto labnewhyphexceptions21reswitch;
        } break;
        case SPACER:
        case RIGHTBRACE: {
            if (n > 1) /* comment:Enter a hyphenation exception */
            {
                incr(n);
                hc[n] = curlang;
                {
                    if (poolptr + n > poolsize)
                        overflow(/* str 'pool size' */ 259,
                                 poolsize - initpoolptr);
                }
                h = 0;
                {
                    register integer for_end;
                    j = 1;
                    for_end = n;
                    if (j <= for_end)
                        do {
                            h = (h + h + hc[j]) % /* @d10839@ */ 607;
                            {
                                strpool[poolptr] = hc[j];
                                incr(poolptr);
                            }
                        } while (j++ < for_end);
                }
                s = makestring();
                /* comment:Insert the \(p)pair |(s,p)| into the exception tab */
                if (hyphnext <= HYPHPRIME)
                    while ((hyphnext > 0) && (hyphword[hyphnext - 1] > 0))
                        decr(hyphnext);
                if ((hyphcount == hyphsize) || (hyphnext == 0))
                    overflow(/* str 'exception dictionary' */ 1362, hyphsize);
                incr(hyphcount);
                while (hyphword[h] != 0) {

                    /* comment:If the string |hyph_word[h]| is less than \(or)or
                     */
                    k = hyphword[h];
                    if ((strstart[k + 1] - strstart[k]) !=
                        (strstart[s + 1] - strstart[s]))
                        goto labnewhyphexceptions45not_found;
                    u = strstart[k];
                    v = strstart[s];
                    do {
                        if (strpool[u] != strpool[v])
                            goto labnewhyphexceptions45not_found;
                        incr(u);
                        incr(v);
                    } while (!(u == strstart[k + 1]));
                    {
                        decr(strptr);
                        poolptr = strstart[strptr];
                    }
                    s = hyphword[h];
                    decr(hyphcount);
                    goto labnewhyphexceptions40found;
                labnewhyphexceptions45not_found:;
                    if (hyphlink[h] == 0) {
                        hyphlink[h] = hyphnext;
                        if (hyphnext >= hyphsize)
                            hyphnext = HYPHPRIME;
                        if (hyphnext > HYPHPRIME)
                            incr(hyphnext);
                    }
                    h = hyphlink[h] - 1;
                }
            labnewhyphexceptions40found:
                hyphword[h] = s;
                hyphlist[h] = p;
            }
            if (curcmd == RIGHTBRACE)
                return;
            n = 0;
            p = TEXNULL;
        } break;
        default:
            /* comment:Give improper \.{\\hyphenation} error */ {

                {
                    if (interaction == ERRORSTOPMODE)
                        ;
                    if (filelineerrorstylep)
                        printfileline();
                    else
                        printnl(/* str '! ' */ 264);
                    print(/* str 'Improper ' */ 781);
                }
                printesc(/* str 'hyphenation' */ 1355);
                print(/* str ' will be flushed' */ 1356);
                {
                    helpptr = 2;
                    helpline[1] = /* str 'Hyphenation exceptions must contain
                                     only letters' */
                        1357;
                    helpline[0] = /* str 'and hyphens. But continue; I'll
                                     forgive and forge' */
                        1358;
                }
                error();
            }
            break;
        }
    }
/* @d10861@ */}
halfword zprunepagetop(halfword p, boolean s) {
    register halfword Result;
    prunepagetop_regmem halfword prevp;
    halfword q, r;
    prevp = memtop - 3;
    mem[memtop - 3].hh.v.RH = p;
    while (p != TEXNULL)
        switch (mem[p].hh.b0) {
        case HLISTNODE:
        case VLISTNODE:
        case RULENODE:
            /* comment:Insert glue for |split_top_skip| and set~|p */ {

                q = newskipparam(SPLITTOPSKIPCODE);
                mem[prevp].hh.v.RH = q;
                mem[q].hh.v.RH = p;
                if (mem[tempptr + WIDTHOFFSET].cint >
                    mem[p + HEIGHTOFFSET].cint)
                    mem[tempptr + WIDTHOFFSET].cint =
                        mem[tempptr + WIDTHOFFSET].cint -
                        mem[p + HEIGHTOFFSET].cint;
                else
                    mem[tempptr + WIDTHOFFSET].cint = 0;
                p = TEXNULL;
            }
            break;
        case WHATSITNODE:
        case MARKNODE:
        case INSNODE: {
            if ((mem[p].hh.b0 == WHATSITNODE) &&
                ((mem[p].hh.b1 == /* @d10878@ */ 35) ||
                 (mem[p].hh.b1 == /* @d10879@ */ 36))) {
                print(/* str 'snap node being discarded' */ 1373);
                goto labprunepagetop60discard_or_move;
            }
            prevp = p;
            p = mem[prevp].hh.v.RH;
        } break;
        case GLUENODE:
        case KERNNODE:
        case PENALTYNODE: {
        labprunepagetop60discard_or_move:
            q = p;
            p = mem[q].hh.v.RH;
            mem[q].hh.v.RH = TEXNULL;
            mem[prevp].hh.v.RH = p;
            if (s) {
                if (discptr[VSPLITCODE] == TEXNULL)
                    discptr[VSPLITCODE] = q;
                else
                    mem[r].hh.v.RH = q;
                r = q;
            } else
                flushnodelist(q);
        } break;
        default:
            confusion(/* str 'pruning' */ 1375);
            break;
        }
    Result = mem[memtop - 3].hh.v.RH;
    return Result;
}
/* comment:Declare the function called |do_marks| */ boolean
zdomarks(smallnumber a, smallnumber l, halfword q) {
    register boolean Result;
    domarks_regmem smallnumber i;
    if (l < 4) {
        {
            register integer for_end;
            i = 0;
            for_end = 15;
            if (i <= for_end)
                do {
                    if (odd(i))
                        curptr = mem[q + (i / 2) + 1].hh.v.RH;
                    else
                        curptr = mem[q + (i / 2) + 1].hh.v.LH;
                    if (curptr != TEXNULL) {

                        if (domarks(a, l + 1, curptr)) {
                            if (odd(i))
                                mem[q + (i / 2) + 1].hh.v.RH = TEXNULL;
                            else
                                mem[q + (i / 2) + 1].hh.v.LH = TEXNULL;
                            decr(mem[q].hh.b1);
                        }
                    }
                } while (i++ < for_end);
        }
        if (mem[q].hh.b1 == 0) {
            freenode(q, INDEXNODESIZE);
            q = TEXNULL;
        }
    } else {

        switch (a) { /* comment:Cases for |do_marks| */
        case 0:
            if (mem[q + 2].hh.v.RH != TEXNULL) {
                deletetokenref(mem[q + 2].hh.v.RH);
                mem[q + 2].hh.v.RH = TEXNULL;
                deletetokenref(mem[q + 3].hh.v.LH);
                mem[q + 3].hh.v.LH = TEXNULL;
            }
            break;
        case 1:
            if (mem[q + 2].hh.v.LH != TEXNULL) {
                if (mem[q + 1].hh.v.LH != TEXNULL)
                    deletetokenref(mem[q + 1].hh.v.LH);
                deletetokenref(mem[q + 1].hh.v.RH);
                mem[q + 1].hh.v.RH = TEXNULL;
                if (mem[mem[q + 2].hh.v.LH].hh.v.RH == TEXNULL) {
                    deletetokenref(mem[q + 2].hh.v.LH);
                    mem[q + 2].hh.v.LH = TEXNULL;
                } else
                    incr(mem[mem[q + 2].hh.v.LH].hh.v.LH);
                mem[q + 1].hh.v.LH = mem[q + 2].hh.v.LH;
            }
            break;
        case 2:
            if ((mem[q + 1].hh.v.LH != TEXNULL) &&
                (mem[q + 1].hh.v.RH == TEXNULL)) {
                mem[q + 1].hh.v.RH = mem[q + 1].hh.v.LH;
                incr(mem[mem[q + 1].hh.v.LH].hh.v.LH);
            }
            break;
            ;
#ifdef INITEX
        case 3: {
            register integer for_end;
            i = TOPMARKCODE;
            for_end = SPLITBOTMARKCODE;
            if (i <= for_end)
                do {
                    if (odd(i))
                        curptr = mem[q + (i / 2) + 1].hh.v.RH;
                    else
                        curptr = mem[q + (i / 2) + 1].hh.v.LH;
                    if (curptr != TEXNULL) {
                        deletetokenref(curptr);
                        if (odd(i))
                            mem[q + (i / 2) + 1].hh.v.RH = TEXNULL;
                        else
                            mem[q + (i / 2) + 1].hh.v.LH = TEXNULL;
                    }
                } while (i++ < for_end);
        } break;
#endif /* INITEX */
        }
        if (mem[q + 2].hh.v.LH == TEXNULL) {

            if (mem[q + 3].hh.v.LH == TEXNULL) {
                freenode(q, MARKCLASSNODESIZE);
                q = TEXNULL;
            }
        }
    }
    Result = (q == TEXNULL);
    return Result;
}
void prefixedcommand(void) {
    prefixedcommand_regmem smallnumber a;
    internalfontnumber f;
    halfword j;
    fontindex k;
    halfword p, q, r;
    integer n;
    boolean e;
    a = 0;
    while (curcmd == PREFIX) {

        if (!odd(a / curchr))
            a = a + curchr;
        /* comment:Get the next non-blank non-relax non-call token */ do {
            getxtoken();
        } while (!((curcmd != SPACER) && (curcmd != RELAX)));
        if (curcmd <= MAXNONPREFIXEDCOMMAND) /* comment:Discard erroneous
                                                prefixes and |return| */
        {
            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(/* str 'You can't use a prefix with `' */ 1597);
            }
            printcmdchr(curcmd, curchr);
            printchar(/* str ''' */ 39);
            {
                helpptr = 1;
                helpline[0] = /* str 'I'll pretend you didn't say \long or
                                 \outer or \g' */
                    1598;
            }
            if ((eTeXmode == 1))
                helpline[0] = /* str 'I'll pretend you didn't say \long or
                                 \outer or \g' */
                    1599;
            backerror();
            return;
        }
        if (eqtb[INTBASE + TRACINGCOMMANDSCODE].cint > 2) {

            if ((eTeXmode == 1))
                showcurcmdchr();
        }
    }
    /* comment:Discard the prefixes \.{\\long} and \.{\\outer} if */ if (a >=
                                                                         8) {
        j = PROTECTEDTOKEN;
        a = a - 8;
    } else
        j = 0;
    if ((curcmd != DEF) && ((a % 4 != 0) || (j != 0))) {
        {
            if (interaction == ERRORSTOPMODE)
                ;
            if (filelineerrorstylep)
                printfileline();
            else
                printnl(/* str '! ' */ 264);
            print(/* str 'You can't use `' */ 786);
        }
        printesc(/* str 'long' */ 1589);
        print(/* str '' or `' */ 1600);
        printesc(/* str 'outer' */ 1590);
        {
            helpptr = 1;
            helpline[0] =
                /* str 'I'll pretend you didn't say \long or \outer here.' */
                1601;
        }
        if ((eTeXmode == 1)) {
            helpline[0] =
                /* str 'I'll pretend you didn't say \long or \outer or \p' */
                1602;
            print(/* str '' or `' */ 1600);
            printesc(/* str 'protected' */ 1603);
        }
        print(/* str '' with `' */ 1604);
        printcmdchr(curcmd, curchr);
        printchar(/* str ''' */ 39);
        error();
    }
    /* comment:Adjust \(f)for the setting of \.{\\globaldefs} */
    if (eqtb[INTBASE + GLOBALDEFSCODE].cint != 0) {

        if (eqtb[INTBASE + GLOBALDEFSCODE].cint < 0) {
            if ((a >= 4))
                a = a - 4;
        } else {

            if (!(a >= 4))
                a = a + 4;
        }
    }
    switch (curcmd) { /* comment:Assignments */
    case SETFONT:
        if ((a >= 4))
            geqdefine(CURFONTLOC, DATA, curchr);
        else
            eqdefine(CURFONTLOC, DATA, curchr);
        break;
    case DEF: {
        if (odd(curchr) && !(a >= 4) &&
            (eqtb[INTBASE + GLOBALDEFSCODE].cint >= 0))
            a = a + 4;
        e = (curchr >= 2);
        getrtoken();
        p = curcs;
        q = scantoks(true, e);
        if (j != 0) {
            q = getavail();
            mem[q].hh.v.LH = j;
            mem[q].hh.v.RH = mem[defref].hh.v.RH;
            mem[defref].hh.v.RH = q;
        }
        if ((a >= 4))
            geqdefine(p, CALL + (a % 4), defref);
        else
            eqdefine(p, CALL + (a % 4), defref);
    } break;
    case LET:
        if (curchr == /* @d12559@ */ 11)
            ;
        else if (curchr == /* @d12560@ */ 10) {
            selector = TERMANDLOG;
            gettoken();
            mubytestoken = curtok;
            if (curtok <= 4095)
                mubytestoken = curtok % 256;
            mubyteprefix = 60;
            mubyterelax = false;
            mubytetablein = true;
            mubytetableout = true;
            getxtoken();
            if (curcmd == SPACER)
                getxtoken();
            if (curcmd == SUBMARK) {
                mubytetableout = false;
                getxtoken();
                if (curcmd == SUBMARK) {
                    mubytetableout = true;
                    mubytetablein = false;
                    getxtoken();
                }
            } else if ((mubytestoken > 4095) && (curcmd == MACPARAM)) {
                mubytetableout = false;
                scanint();
                mubyteprefix = curval;
                getxtoken();
                if (mubyteprefix > 50)
                    mubyteprefix = 52;
                if (mubyteprefix <= 0)
                    mubyteprefix = 51;
            } else if ((mubytestoken > 4095) && (curcmd == RELAX)) {
                mubytetableout = true;
                mubytetablein = false;
                mubyterelax = true;
                getxtoken();
            }
            r = getavail();
            p = r;
            while (curcs == 0) {

                {
                    q = getavail();
                    mem[p].hh.v.RH = q;
                    mem[q].hh.v.LH = curtok;
                    p = q;
                }
                getxtoken();
            }
            if ((curcmd != ENDCSNAME) || (curchr != 10)) {
                {
                    if (interaction == ERRORSTOPMODE)
                        ;
                    if (filelineerrorstylep)
                        printfileline();
                    else
                        printnl(/* str '! ' */ 264);
                    print(/* str 'Missing ' */ 712);
                }
                printesc(/* str 'endmubyte' */ 592);
                print(/* str ' inserted' */ 713);
                {
                    helpptr = 2;
                    helpline[1] = /* str 'The control sequence marked <to be
                                     read again> sh' */
                        714;
                    helpline[0] = /* str 'not appear in <byte sequence> between
                                     \mubyte and' */
                        1616;
                }
                backerror();
            }
            p = mem[r].hh.v.RH;
            if ((p == TEXNULL) && mubytetablein) {
                {
                    if (interaction == ERRORSTOPMODE)
                        ;
                    if (filelineerrorstylep)
                        printfileline();
                    else
                        printnl(/* str '! ' */ 264);
                    print(/* str 'The empty <byte sequence>, ' */ 1617);
                }
                printesc(/* str 'mubyte' */ 1614);
                print(/* str ' ignored' */ 1618);
                {
                    helpptr = 2;
                    helpline[1] = /* str 'The <byte sequence> in' */ 1619;
                    helpline[0] = /* str '\mubyte <token> <byte
                                     sequence>\endmubyte should ' */
                        1620;
                }
                error();
            } else {

                while (p != TEXNULL) {

                    {
                        strpool[poolptr] = mem[p].hh.v.LH % 256;
                        incr(poolptr);
                    }
                    p = mem[p].hh.v.RH;
                }
                flushlist(r);
                if ((strstart[strptr] + 1 == poolptr) &&
                    (strpool[poolptr - 1] == mubytestoken)) {
                    if (mubyteread[mubytestoken] != TEXNULL && mubytetablein)
                        disposemunode(mubyteread[mubytestoken]);
                    if (mubytetablein)
                        mubyteread[mubytestoken] = TEXNULL;
                    if (mubytetableout)
                        mubytewrite[mubytestoken] = 0;
                    poolptr = strstart[strptr];
                } else {

                    if (mubytetablein)
                        mubyteupdate();
                    if (mubytetableout) {
                        if (mubytestoken > 4095) {
                            disposemutableout(mubytestoken - 4095);
                            if ((strstart[strptr] < poolptr) || mubyterelax) {
                                r = mubytecswrite[(mubytestoken - 4095) % 128];
                                p = getavail();
                                mubytecswrite[(mubytestoken - 4095) % 128] = p;
                                mem[p].hh.v.LH = mubytestoken - 4095;
                                mem[p].hh.v.RH = getavail();
                                p = mem[p].hh.v.RH;
                                if (mubyterelax) {
                                    mem[p].hh.v.LH = 0;
                                    poolptr = strstart[strptr];
                                } else
                                    mem[p].hh.v.LH = slowmakestring();
                                mem[p].hh.v.RH = r;
                            }
                        } else {

                            if (strstart[strptr] == poolptr)
                                mubytewrite[mubytestoken] = 0;
                            else
                                mubytewrite[mubytestoken] = slowmakestring();
                        }
                    } else
                        poolptr = strstart[strptr];
                }
            }
        } else {

            n = curchr;
            getrtoken();
            p = curcs;
            if (n == NORMAL) {
                do {
                    gettoken();
                } while (!(curcmd != SPACER));
                if (curtok == /* @d12584@ */ /* str '=' */ 3133) {
                    gettoken();
                    if (curcmd == SPACER)
                        gettoken();
                }
            } else {

                gettoken();
                q = curtok;
                gettoken();
                backinput();
                curtok = q;
                backinput();
            }
            if (curcmd >= CALL)
                incr(mem[curchr].hh.v.LH);
            else if ((curcmd == REGISTER) || (curcmd == TOKSREGISTER)) {

                if ((curchr < membot) ||
                    (curchr > /* @d12590@ */ /* @d12591@ */ /* @d12592@ */
                                  /* @d12593@ */ /* @d12594@ */ membot + 19))
                    incr(mem[curchr + 1].hh.v.LH);
            }
            if ((a >= 4))
                geqdefine(p, curcmd, curchr);
            else
                eqdefine(p, curcmd, curchr);
        }
        break;
    case SHORTHANDDEF:
        if (curchr == CHARSUBDEFCODE) {
            scancharnum();
            p = CHARSUBCODEBASE + curval;
            scanoptionalequals();
            scancharnum();
            n = curval;
            scancharnum();
            if ((eqtb[INTBASE + TRACINGCHARSUBDEFCODE].cint > 0)) {
                begindiagnostic();
                printnl(/* str 'New character substitution' */ 1629);
                print(p - CHARSUBCODEBASE);
                print(/* str ' = ' */ 1630);
                print(n);
                printchar(/* str ' ' */ 32);
                print(curval);
                enddiagnostic(false);
            }
            n = n * 256 + curval;
            if ((a >= 4))
                geqdefine(p, DATA, n);
            else
                eqdefine(p, DATA, n);
            if ((p - CHARSUBCODEBASE) <
                eqtb[INTBASE + CHARSUBDEFMINCODE].cint) {

                if ((a >= 4))
                    geqworddefine(INTBASE+CHARSUBDEFMINCODE,
                                  p - CHARSUBCODEBASE);
                else
                    eqworddefine(INTBASE+CHARSUBDEFMINCODE,
                                 p - CHARSUBCODEBASE);
            }
            if ((p - CHARSUBCODEBASE) >
                eqtb[INTBASE + CHARSUBDEFMAXCODE].cint) {

                if ((a >= 4))
                    geqworddefine(INTBASE+CHARSUBDEFMAXCODE,
                                  p - CHARSUBCODEBASE);
                else
                    eqworddefine(INTBASE+CHARSUBDEFMAXCODE,
                                 p - CHARSUBCODEBASE);
            }
        } else {

            n = curchr;
            getrtoken();
            p = curcs;
            if ((a >= 4))
                geqdefine(p, RELAX, 256);
            else
                eqdefine(p, RELAX, 256);
            scanoptionalequals();
            switch (n) {
            case CHARDEFCODE: {
                scancharnum();
                if ((a >= 4))
                    geqdefine(p, CHARGIVEN, curval);
                else
                    eqdefine(p, CHARGIVEN, curval);
            } break;
            case MATHCHARDEFCODE: {
                scanfifteenbitint();
                if ((a >= 4))
                    geqdefine(p, MATHGIVEN, curval);
                else
                    eqdefine(p, MATHGIVEN, curval);
            } break;
            default: {
                scanregisternum();
                if (curval > 255) {
                    j = n - COUNTDEFCODE;
                    if (j > MUVAL)
                        j = TOKVAL;
                    findsaelement(j, curval, true);
                    incr(mem[curptr + 1].hh.v.LH);
                    if (j == TOKVAL)
                        j = TOKSREGISTER;
                    else
                        j = REGISTER;
                    if ((a >= 4))
                        geqdefine(p, j, curptr);
                    else
                        eqdefine(p, j, curptr);
                } else
                    switch (n) {
                    case COUNTDEFCODE:
                        if ((a >= 4))
                            geqdefine(p, ASSIGNINT, COUNTBASE + curval);
                        else
                            eqdefine(p, ASSIGNINT, COUNTBASE + curval);
                        break;
                    case DIMENDEFCODE:
                        if ((a >= 4))
                            geqdefine(p, ASSIGNDIMEN, SCALEDBASE + curval);
                        else
                            eqdefine(p, ASSIGNDIMEN, SCALEDBASE + curval);
                        break;
                    case SKIPDEFCODE:
                        if ((a >= 4))
                            geqdefine(p, ASSIGNGLUE, SKIPBASE + curval);
                        else
                            eqdefine(p, ASSIGNGLUE, SKIPBASE + curval);
                        break;
                    case MUSKIPDEFCODE:
                        if ((a >= 4))
                            geqdefine(p, ASSIGNMUGLUE, MUSKIPBASE + curval);
                        else
                            eqdefine(p, ASSIGNMUGLUE, MUSKIPBASE + curval);
                        break;
                    case TOKSDEFCODE:
                        if ((a >= 4))
                            geqdefine(p, ASSIGNTOKS, TOKSBASE + curval);
                        else
                            eqdefine(p, ASSIGNTOKS, TOKSBASE + curval);
                        break;
                    }
            } break;
            }
        }
        break;
    case READTOCS: {
        j = curchr;
        scanint();
        n = curval;
        if (!scankeyword(/* str 'to' */ 1245)) {
            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(/* str 'Missing `to' inserted' */ 1487);
            }
            {
                helpptr = 2;
                helpline[1] =
                    /* str 'You should have said `\read<number> to \cs'.' */
                    1631;
                helpline[0] =
                    /* str 'I'm going to look for the \cs now.' */ 1632;
            }
            error();
        }
        getrtoken();
        p = curcs;
        readtoks(n, p, j);
        if ((a >= 4))
            geqdefine(p, CALL, curval);
        else
            eqdefine(p, CALL, curval);
    } break;
    case TOKSREGISTER:
    case ASSIGNTOKS: {
        q = curcs;
        e = false;
        if (curcmd == TOKSREGISTER) {

            if (curchr == membot) {
                scanregisternum();
                if (curval > 255) {
                    findsaelement(TOKVAL, curval, true);
                    curchr = curptr;
                    e = true;
                } else
                    curchr = TOKSBASE + curval;
            } else
                e = true;
        }
        p = curchr;
        scanoptionalequals();
        /* comment:Get the next non-blank non-relax non-call token */ do {
            getxtoken();
        } while (!((curcmd != SPACER) && (curcmd != RELAX)));
        if (curcmd != LEFTBRACE) /* comment:If the right-hand side is a token
                                    parameter or tok */
        {

            if ((curcmd == TOKSREGISTER) || (curcmd == ASSIGNTOKS)) {
                if (curcmd == TOKSREGISTER) {

                    if (curchr == membot) {
                        scanregisternum();
                        if (curval < 256)
                            q = eqtb[TOKSBASE + curval].hh.v.RH;
                        else {

                            findsaelement(TOKVAL, curval, false);
                            if (curptr == TEXNULL)
                                q = TEXNULL;
                            else
                                q = mem[curptr + 1].hh.v.RH;
                        }
                    } else
                        q = mem[curchr + 1].hh.v.RH;
                } else
                    q = eqtb[curchr].hh.v.RH;
                if (q == TEXNULL) {

                    if (e) {

                        if ((a >= 4))
                            gsadef(p, TEXNULL);
                        else
                            sadef(p, TEXNULL);
                    } else if ((a >= 4))
                        geqdefine(p, UNDEFINEDCS, TEXNULL);
                    else
                        eqdefine(p, UNDEFINEDCS, TEXNULL);
                } else {

                    incr(mem[q].hh.v.LH);
                    if (e) {

                        if ((a >= 4))
                            gsadef(p, q);
                        else
                            sadef(p, q);
                    } else if ((a >= 4))
                        geqdefine(p, CALL, q);
                    else
                        eqdefine(p, CALL, q);
                }
                goto labprefixedcommand30done;
            }
        }
        backinput();
        curcs = q;
        q = scantoks(false, false);
        if (mem[defref].hh.v.RH == TEXNULL) {
            if (e) {

                if ((a >= 4))
                    gsadef(p, TEXNULL);
                else
                    sadef(p, TEXNULL);
            } else if ((a >= 4))
                geqdefine(p, UNDEFINEDCS, TEXNULL);
            else
                eqdefine(p, UNDEFINEDCS, TEXNULL);
            {
                mem[defref].hh.v.RH = avail;
                avail = defref;
                mem[defref].hh.me = 0;
                ;
#ifdef STAT
                decr(dynused);
#endif /* STAT */
            }
        } else {

            if ((p == OUTPUTROUTINELOC) && !e) {
                mem[q].hh.v.RH = getavail();
                q = mem[q].hh.v.RH;
                mem[q].hh.v.LH = /* @d12695@ */ /* str '}' */ 637;
                q = getavail();
                mem[q].hh.v.LH = /* @d12697@ */ /* str '{' */ 379;
                mem[q].hh.v.RH = mem[defref].hh.v.RH;
                mem[defref].hh.v.RH = q;
            }
            if (e) {

                if ((a >= 4))
                    gsadef(p, defref);
                else
                    sadef(p, defref);
            } else if ((a >= 4))
                geqdefine(p, CALL, defref);
            else
                eqdefine(p, CALL, defref);
        }
    } break;
    case ASSIGNINT: {
        p = curchr;
        scanoptionalequals();
        scanint();
        if ((a >= 4))
            geqworddefine(p, curval);
        else
            eqworddefine(p, curval);
    } break;
    case ASSIGNDIMEN: {
        p = curchr;
        scanoptionalequals();
        scandimen(false, false, false);
        if ((a >= 4))
            geqworddefine(p, curval);
        else
            eqworddefine(p, curval);
    } break;
    case ASSIGNGLUE:
    case ASSIGNMUGLUE: {
        p = curchr;
        n = curcmd;
        scanoptionalequals();
        if (n == ASSIGNMUGLUE)
            scanglue(MUVAL);
        else
            scanglue(GLUEVAL);
        trapzeroglue();
        if ((a >= 4))
            geqdefine(p, GLUEREF, curval);
        else
            eqdefine(p, GLUEREF, curval);
    } break;
    case DEFCODE: {
        /* comment:Let |n| be the largest legal code value, based on  */
        if (curchr == CATCODEBASE)
            n = MAXCHARCODE;
        else if (curchr == MATHCODEBASE)
            n = 32768L;
        else if (curchr == SFCODEBASE)
            n = 32767;
        else if (curchr == DELCODEBASE)
            n = 16777215L;
        else
            n = 255;
        p = curchr;
        scancharnum();
        if (p == XORDCODEBASE)
            p = curval;
        else if (p == XCHRCODEBASE)
            p = curval + 256;
        else if (p == XPRNCODEBASE)
            p = curval + 512;
        else
            p = p + curval;
        scanoptionalequals();
        scanint();
        if (((curval < 0) && (p < DELCODEBASE)) || (curval > n)) {
            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(/* str 'Invalid code (' */ 1636);
            }
            printint(curval);
            if (p < DELCODEBASE)
                print(/* str '), should be in the range 0..' */ 1637);
            else
                print(/* str '), should be at most ' */ 1638);
            printint(n);
            {
                helpptr = 1;
                helpline[0] = /* str 'I'm going to use 0 instead of that illegal
                                 code v' */
                    1639;
            }
            error();
            curval = 0;
        }
        if (p < 256)
            xord[p] = curval;
        else if (p < 512)
            xchr[p - 256] = curval;
        else if (p < 768)
            xprn[p - 512] = curval;
        else if (p < MATHCODEBASE) {

            if ((a >= 4))
                geqdefine(p, DATA, curval);
            else
                eqdefine(p, DATA, curval);
        } else if (p < DELCODEBASE) {

            if ((a >= 4))
                geqdefine(p, DATA, curval);
            else
                eqdefine(p, DATA, curval);
        } else if ((a >= 4))
            geqworddefine(p, curval);
        else
            eqworddefine(p, curval);
    } break;
    case DEFFAMILY: {
        p = curchr;
        scanfourbitint();
        p = p + curval;
        scanoptionalequals();
        scanfontident();
        if ((a >= 4))
            geqdefine(p, DATA, curval);
        else
            eqdefine(p, DATA, curval);
    } break;
    case REGISTER:
    case ADVANCE:
    case MULTIPLY:
    case DIVIDE:
        doregistercommand(a);
        break;
    case SETBOX: {
        scanregisternum();
        if ((a >= 4))
            n = 1073774592L + curval;
        else
            n = 1073741824L + curval;
        scanoptionalequals();
        if (setboxallowed)
            scanbox(n);
        else {

            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(/* str 'Improper ' */ 781);
            }
            printesc(/* str 'setbox' */ 616);
            {
                helpptr = 2;
                helpline[1] = /* str 'Sorry, \setbox is not allowed after
                                 \halign in a ' */
                    1645;
                helpline[0] =
                    /* str 'or between \accent and an accented character.' */
                    1646;
            }
            error();
        }
    } break;
    case SETAUX:
        alteraux();
        break;
    case SETPREVGRAF:
        alterprevgraf();
        break;
    case SETPAGEDIMEN:
        alterpagesofar();
        break;
    case SETPAGEINT:
        alterinteger();
        break;
    case SETBOXDIMEN:
        alterboxdimen();
        break;
    case SETSHAPE: {
        q = curchr;
        scanoptionalequals();
        scanint();
        n = curval;
        if (n <= 0)
            p = TEXNULL;
        else if (q > PARSHAPELOC) {
            n = (curval / 2) + 1;
            p = getnode(2 * n + 1);
            mem[p].hh.v.LH = n;
            n = curval;
            mem[p + 1].cint = n;
            {
                register integer for_end;
                j = p + 2;
                for_end = p + n + 1;
                if (j <= for_end)
                    do {
                        scanint();
                        mem[j].cint = curval;
                    } while (j++ < for_end);
            }
            if (!odd(n))
                mem[p + n + 2].cint = 0;
        } else {

            p = getnode(2 * n + 1);
            mem[p].hh.v.LH = n;
            {
                register integer for_end;
                j = 1;
                for_end = n;
                if (j <= for_end)
                    do {
                        scandimen(false, false, false);
                        mem[p + 2 * j - 1].cint = curval;
                        scandimen(false, false, false);
                        mem[p + 2 * j].cint = curval;
                    } while (j++ < for_end);
            }
        }
        if ((a >= 4))
            geqdefine(q, SHAPEREF, p);
        else
            eqdefine(q, SHAPEREF, p);
    } break;
    case HYPHDATA:
        if (curchr == 1) {
            ;
#ifdef INITEX
            if (iniversion) {
                newpatterns();
                goto labprefixedcommand30done;
            }
#endif /* INITEX */
            {
                if (interaction == ERRORSTOPMODE)
                    ;
                if (filelineerrorstylep)
                    printfileline();
                else
                    printnl(/* str '! ' */ 264);
                print(/* str 'Patterns can be loaded only by INITEX' */ 1650);
            }
            helpptr = 0;
            error();
            do {
                gettoken();
            } while (!(curcmd == RIGHTBRACE));
            return;
        } else {

            newhyphexceptions();
            goto labprefixedcommand30done;
        }
        break;
    case ASSIGNFONTDIMEN: {
        findfontdimen(true);
        k = curval;
        scanoptionalequals();
        scandimen(false, false, false);
        fontinfo[k].cint = curval;
    } break;
    case ASSIGNFONTINT: {
        n = curchr;
        scanfontident();
        f = curval;
        if (n == 6)
            setnoligatures(f);
        else if (n < 2) {
            scanoptionalequals();
            scanint();
            if (n == 0)
                hyphenchar[f] = curval;
            else
                skewchar[f] = curval;
        } else {

            scancharnum();
            p = curval;
            scanoptionalequals();
            scanint();
            switch (n) {
            case 2:
                setlpcode(f, p, curval);
                break;
            case 3:
                setrpcode(f, p, curval);
                break;
            case 4:
                setefcode(f, p, curval);
                break;
            case 5:
                settagcode(f, p, curval);
                break;
            case 7:
                setknbscode(f, p, curval);
                break;
            case 8:
                setstbscode(f, p, curval);
                break;
            case 9:
                setshbscode(f, p, curval);
                break;
            case 10:
                setknbccode(f, p, curval);
                break;
            case 11:
                setknaccode(f, p, curval);
                break;
            }
        }
    } break;
    case DEFFONT:
        newfont(a);
        break;
    case LETTERSPACEFONT:
        newletterspacedfont(a);
        break;
    case PDFCOPYFONT:
        makefontcopy(a);
        break;
    case SETINTERACTION:
        newinteraction();
        break;
    default:
        confusion(/* str 'prefix' */ 1596);
        break;
    }
labprefixedcommand30done
    : /* comment:Insert a token saved by \.{\\afterassignment}, if  */
    if (aftertoken != 0) {
        curtok = aftertoken;
        backinput();
        aftertoken = 0;
    }
/* @d12774@ */}
void doassignments(void) {
    doassignments_regmem while (true) {

        /* comment:Get the next non-blank non-relax non-call token */ do {
            getxtoken();
        } while (!((curcmd != SPACER) && (curcmd != RELAX)));
        if (curcmd <= MAXNONPREFIXEDCOMMAND)
            return;
        setboxallowed = false;
        prefixedcommand();
        setboxallowed = true;
    }
/* @d12781@ */}
void openorclosein(void) {
    openorclosein_regmem unsigned char c;
    unsigned char n;
    c = curchr;
    scanfourbitint();
    n = curval;
    if (readopen[n] != CLOSED) {
        aclose(readfile[n]);
        readopen[n] = CLOSED;
    }
    if (c != 0) {
        scanoptionalequals();
        scanfilename();
        packfilename(curname, curarea, curext);
        texinputtype = 0;
        if (kpseinnameok(stringcast(nameoffile + 1)) &&
            aopenin(readfile[n], kpsetexformat))
            readopen[n] = JUSTOPEN;
    }
}
#ifdef INITEX
void storefmtfile(void) {
    /* @d12858@ */ /* @d12859@ */ /* @d12860@ */ /* @d12861@ */
    storefmtfile_regmem integer j, k, l;
    halfword p, q;
    integer x;
    ASCIIcode *formatengine;
    /* comment:If dumping is not allowed, abort */ if (saveptr != 0) {
        {
            if (interaction == ERRORSTOPMODE)
                ;
            if (filelineerrorstylep)
                printfileline();
            else
                printnl(/* str '! ' */ 264);
            print(/* str 'You can't dump inside a group' */ 1699);
        }
        {
            helpptr = 1;
            helpline[0] = /* str '`{...\dump}' is a no-no.' */ 1700;
        }
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
    /* comment:Create the |format_ident|, open the format file, a */ selector =
        NEWSTRING;
    print(/* str ' (preloaded format=' */ 1718);
    print(jobname);
    printchar(/* str ' ' */ 32);
    printint(eqtb[INTBASE + YEARCODE].cint);
    printchar(/* str '.' */ 46);
    printint(eqtb[INTBASE + MONTHCODE].cint);
    printchar(/* str '.' */ 46);
    printint(eqtb[INTBASE + DAYCODE].cint);
    printchar(/* str ')' */ 41);
    if (interaction == BATCHMODE)
        selector = LOGONLY;
    else
        selector = TERMANDLOG;
    {
        if (poolptr + 1 > poolsize)
            overflow(/* str 'pool size' */ 259, poolsize - initpoolptr);
    }
    formatident = makestring();
    packjobname(FORMATEXTENSION);
    while (!wopenout(fmtfile))
        promptfilename(/* str 'format file name' */ 1719, FORMATEXTENSION);
    printnl(/* str 'Beginning to dump on file ' */ 1720);
    slowprint(wmakenamestring(fmtfile));
    {
        decr(strptr);
        poolptr = strstart[strptr];
    }
    printnl(/* str '' */ 345);
    slowprint(formatident);
    /* comment:Dump constants for consistency check */ dumpint(1462916184L);
    x = strlen(enginename);
    formatengine = xmallocarray(ASCIIcode, x + 4);
    strcpy(stringcast(formatengine), enginename);
    {
        register integer for_end;
        k = x;
        for_end = x + 3;
        if (k <= for_end)
            do
                formatengine[k] = 0;
            while (k++ < for_end);
    }
    x = x + 4 - (x % 4);
    dumpint(x);
    dumpthings(formatengine[0], x);
    libcfree(formatengine);
    dumpint(383633139L);
    /* comment:Dump |xord|, |xchr|, and |xprn| */ dumpthings(xord[0], 256);
    dumpthings(xchr[0], 256);
    dumpthings(xprn[0], 256);
    dumpint(2147483647L);
    dumpint(hashhigh);
    /* comment:Dump the \eTeX\ state */ dumpint(eTeXmode);
    {
        register integer for_end;
        j = 0;
        for_end = /* @d12896@ */ -0;
        if (j <= for_end)
            do
                eqtb[ETEXSTATEBASE + j].cint = 0;
            while (j++ < for_end);
    }
    while (pseudofiles != TEXNULL)
        pseudoclose();
    dumpint(membot);
    dumpint(memtop);
    dumpint(EQTBSIZE);
    dumpint(HASHPRIME);
    dumpint(HYPHPRIME);
    /* comment:Dump ML\TeX-specific data */ dumpint(1296847960L);
    if (mltexp)
        dumpint(1);
    else
        dumpint(0);
    /* comment:Dump enc\TeX-specific data */ dumpint(1162040408L);
    if (!enctexp)
        dumpint(0);
    else {

        dumpint(1);
        dumpthings(mubyteread[0], 256);
        dumpthings(mubytewrite[0], 256);
        dumpthings(mubytecswrite[0], 128);
    }
    /* comment:Dump the string pool */ dumpint(poolptr);
    dumpint(strptr);
    dumpthings(strstart[0], strptr + 1);
    dumpthings(strpool[0], poolptr);
    println();
    printint(strptr);
    print(/* str ' strings of total length ' */ 1701);
    printint(poolptr);
    /* comment:Dump the dynamic memory */ sortavail();
    varused = 0;
    dumpint(lomemmax);
    dumpint(rover);
    if ((eTeXmode == 1)) {
        register integer for_end;
        k = INTVAL;
        for_end = TOKVAL;
        if (k <= for_end)
            do
                dumpint(saroot[k]);
            while (k++ < for_end);
    }
    p = membot;
    q = rover;
    x = 0;
    do {
        dumpthings(mem[p], q + 2 - p);
        x = x + q + 2 - p;
        varused = varused + q - p;
        p = q + mem[q].hh.v.LH;
        q = mem[q + 1].hh.v.RH;
    } while (!(q == rover));
    varused = varused + lomemmax - p;
    dynused = memend + 1 - himemmin;
    dumpthings(mem[p], lomemmax + 1 - p);
    x = x + lomemmax + 1 - p;
    dumpint(himemmin);
    dumpint(avail);
    dumpthings(mem[himemmin], memend + 1 - himemmin);
    x = x + memend + 1 - himemmin;
    p = avail;
    while (p != TEXNULL) {

        decr(dynused);
        p = mem[p].hh.v.RH;
    }
    dumpint(varused);
    dumpint(dynused);
    println();
    printint(x);
    print(/* str ' memory locations dumped; current usage is ' */ 1702);
    printint(varused);
    printchar(/* str '&' */ 38);
    printint(dynused);
    /* comment:Dump the table of equivalents */
    /* comment:Dump regions 1 to 4 of |eqtb| */ k = ACTIVEBASE;
    do {
        j = k;
        while (j < /* @d12913@ */ 29276) {

            if ((eqtb[j].hh.v.RH == eqtb[j + 1].hh.v.RH) &&
                (eqtb[j].hh.b0 == eqtb[j + 1].hh.b0) &&
                (eqtb[j].hh.b1 == eqtb[j + 1].hh.b1))
                goto labstorefmtfile41found1;
            incr(j);
        }
        l = INTBASE;
        goto labstorefmtfile31done1;
    labstorefmtfile41found1:
        incr(j);
        l = j;
        while (j < /* @d12918@ */ 29276) {

            if ((eqtb[j].hh.v.RH != eqtb[j + 1].hh.v.RH) ||
                (eqtb[j].hh.b0 != eqtb[j + 1].hh.b0) ||
                (eqtb[j].hh.b1 != eqtb[j + 1].hh.b1))
                goto labstorefmtfile31done1;
            incr(j);
        }
    labstorefmtfile31done1:
        dumpint(l - k);
        dumpthings(eqtb[k], l - k);
        k = j + 1;
        dumpint(k - l);
    } while (!(k == INTBASE));
    /* comment:Dump regions 5 and 6 of |eqtb| */ do {
        j = k;
        while (j < EQTBSIZE) {

            if (eqtb[j].cint == eqtb[j + 1].cint)
                goto labstorefmtfile42found2;
            incr(j);
        }
        l = /* @d12925@ */ 30184;
        goto labstorefmtfile32done2;
    labstorefmtfile42found2:
        incr(j);
        l = j;
        while (j < EQTBSIZE) {

            if (eqtb[j].cint != eqtb[j + 1].cint)
                goto labstorefmtfile32done2;
            incr(j);
        }
    labstorefmtfile32done2:
        dumpint(l - k);
        dumpthings(eqtb[k], l - k);
        k = j + 1;
        dumpint(k - l);
    } while (!(k > EQTBSIZE));
    if (hashhigh > 0)
        dumpthings(eqtb[/* @d12932@ */ 30184], hashhigh);
    dumpint(parloc);
    dumpint(writeloc);
    /* comment:Dump the hash table */ {
        register integer for_end;
        p = 0;
        for_end = PRIMSIZE;
        if (p <= for_end)
            do
                dumphh(prim[p]);
            while (p++ < for_end);
    }
    dumpint(hashused);
    cscount = /* @d12935@ */ 15513 - hashused + hashhigh;
    {
        register integer for_end;
        p = HASHBASE;
        for_end = hashused;
        if (p <= for_end)
            do
                if (hash[p].v.RH != 0) {
                    dumpint(p);
                    dumphh(hash[p]);
                    incr(cscount);
                }
            while (p++ < for_end);
    }
    dumpthings(hash[hashused + 1], /* @d12937@ */ 26626 - hashused);
    if (hashhigh > 0)
        dumpthings(hash[/* @d12938@ */ 30184], hashhigh);
    dumpint(cscount);
    println();
    printint(cscount);
    print(/* str ' multiletter control sequences' */ 1703);
    /* comment:Dump the font information */ dumpint(fmemptr);
    dumpthings(fontinfo[0], fmemptr);
    dumpint(fontptr);
    /* comment:Dump the array info for internal font number |k| */ {

        dumpthings(fontcheck[FONTBASE], /* @d12943@ */ fontptr + 1);
        dumpthings(fontsize[FONTBASE], /* @d12945@ */ fontptr + 1);
        dumpthings(fontdsize[FONTBASE], /* @d12947@ */ fontptr + 1);
        dumpthings(fontparams[FONTBASE], /* @d12949@ */ fontptr + 1);
        dumpthings(hyphenchar[FONTBASE], /* @d12951@ */ fontptr + 1);
        dumpthings(skewchar[FONTBASE], /* @d12953@ */ fontptr + 1);
        dumpthings(fontname[FONTBASE], /* @d12955@ */ fontptr + 1);
        dumpthings(fontarea[FONTBASE], /* @d12957@ */ fontptr + 1);
        dumpthings(fontbc[FONTBASE], /* @d12959@ */ fontptr + 1);
        dumpthings(fontec[FONTBASE], /* @d12961@ */ fontptr + 1);
        dumpthings(charbase[FONTBASE], /* @d12963@ */ fontptr + 1);
        dumpthings(widthbase[FONTBASE], /* @d12965@ */ fontptr + 1);
        dumpthings(heightbase[FONTBASE], /* @d12967@ */ fontptr + 1);
        dumpthings(depthbase[FONTBASE], /* @d12969@ */ fontptr + 1);
        dumpthings(italicbase[FONTBASE], /* @d12971@ */ fontptr + 1);
        dumpthings(ligkernbase[FONTBASE], /* @d12973@ */ fontptr + 1);
        dumpthings(kernbase[FONTBASE], /* @d12975@ */ fontptr + 1);
        dumpthings(extenbase[FONTBASE], /* @d12977@ */ fontptr + 1);
        dumpthings(parambase[FONTBASE], /* @d12979@ */ fontptr + 1);
        dumpthings(fontglue[FONTBASE], /* @d12981@ */ fontptr + 1);
        dumpthings(bcharlabel[FONTBASE], /* @d12983@ */ fontptr + 1);
        dumpthings(fontbchar[FONTBASE], /* @d12985@ */ fontptr + 1);
        dumpthings(fontfalsebchar[FONTBASE], /* @d12987@ */ fontptr + 1);
        {
            register integer for_end;
            k = FONTBASE;
            for_end = fontptr;
            if (k <= for_end)
                do {
                    printnl(/* str '\font' */ 1707);
                    printesc(hash[FONTIDBASE + k].v.RH);
                    printchar(/* str '=' */ 61);
                    printfilename(fontname[k], fontarea[k], /* str '' */ 345);
                    if (fontsize[k] != fontdsize[k]) {
                        print(/* str ' at ' */ 895);
                        printscaled(fontsize[k]);
                        print(/* str 'pt' */ 312);
                    }
                } while (k++ < for_end);
        }
    }
    println();
    printint(fmemptr - 7);
    print(/* str ' words of font info for ' */ 1704);
    printint(fontptr - FONTBASE);
    if (fontptr != /* @d12997@ */ 1)
        print(/* str ' preloaded fonts' */ 1705);
    else
        print(/* str ' preloaded font' */ 1706);
    /* comment:Dump the hyphenation tables */ dumpint(hyphcount);
    if (hyphnext <= HYPHPRIME)
        hyphnext = hyphsize;
    dumpint(hyphnext);
    {
        register integer for_end;
        k = 0;
        for_end = hyphsize;
        if (k <= for_end)
            do
                if (hyphword[k] != 0) {
                    dumpint(k + 65536L * hyphlink[k]);
                    dumpint(hyphword[k]);
                    dumpint(hyphlist[k]);
                }
            while (k++ < for_end);
    }
    println();
    printint(hyphcount);
    if (hyphcount != 1)
        print(/* str ' hyphenation exceptions' */ 1708);
    else
        print(/* str ' hyphenation exception' */ 1709);
    if (trienotready)
        inittrie();
    dumpint(triemax);
    dumpint(hyphstart);
    dumpthings(trietrl[0], triemax + 1);
    dumpthings(trietro[0], triemax + 1);
    dumpthings(trietrc[0], triemax + 1);
    dumpint(trieopptr);
    dumpthings(hyfdistance[1], trieopptr);
    dumpthings(hyfnum[1], trieopptr);
    dumpthings(hyfnext[1], trieopptr);
    printnl(/* str 'Hyphenation trie of length ' */ 1710);
    printint(triemax);
    print(/* str ' has ' */ 1711);
    printint(trieopptr);
    if (trieopptr != 1)
        print(/* str ' ops' */ 1712);
    else
        print(/* str ' op' */ 1713);
    print(/* str ' out of ' */ 1714);
    printint(trieopsize);
    {
        register integer for_end;
        k = 255;
        for_end = 0;
        if (k >= for_end)
            do
                if (trieused[k] > MINQUARTERWORD) {
                    printnl(/* str '  ' */ 955);
                    printint(trieused[k]);
                    print(/* str ' for language ' */ 1715);
                    printint(k);
                    dumpint(k);
                    dumpint(trieused[k]);
                }
            while (k-- > for_end);
    }
    /* comment:Dump pdftex data */ {

        dumpimagemeta();
        dumpint(pdfmemsize);
        dumpint(pdfmemptr);
        {
            register integer for_end;
            k = 1;
            for_end = pdfmemptr - 1;
            if (k <= for_end)
                do {
                    dumpint(pdfmem[k]);
                } while (k++ < for_end);
        }
        println();
        printint(pdfmemptr - 1);
        print(/* str ' words of pdfTeX memory' */ 1716);
        dumpint(objtabsize);
        dumpint(objptr);
        dumpint(sysobjptr);
        {
            register integer for_end;
            k = 1;
            for_end = sysobjptr;
            if (k <= for_end)
                do {
                    dumpint(objtab[k].int0);
                    dumpint(objtab[k].int1);
                    dumpint(objtab[k].int3);
                    dumpint(objtab[k].int4);
                } while (k++ < for_end);
        }
        println();
        printint(sysobjptr);
        print(/* str ' indirect objects' */ 1717);
        dumpint(pdfobjcount);
        dumpint(pdfxformcount);
        dumpint(pdfximagecount);
        dumpint(headtab[6]);
        dumpint(headtab[7]);
        dumpint(headtab[8]);
        dumpint(pdflastobj);
        dumpint(pdflastxform);
        dumpint(pdflastximage);
    }
    /* comment:Dump a couple more things and the closing check wo */ dumpint(
        interaction);
    dumpint(formatident);
    dumpint(69069L);
    eqtb[INTBASE + TRACINGSTATSCODE].cint = 0;
    /* comment:Close the format file */ wclose(fmtfile);
}
#endif /* INITEX */
boolean loadfmtfile(void) {
    register boolean Result;
    loadfmtfile_regmem integer j, k;
    halfword p, q;
    integer x;
    ASCIIcode *formatengine;
    ASCIIcode dummyxord;
    ASCIIcode dummyxchr;
    ASCIIcode dummyxprn;
    /* comment:Undump constants for consistency check */;
#ifdef INITEX
    if (iniversion) {
        libcfree(fontinfo);
        libcfree(strpool);
        libcfree(strstart);
        libcfree(yhash);
        libcfree(zeqtb);
        libcfree(yzmem);
    }
#endif /* INITEX */
    undumpint(x);
    if (debugformatfile) {
        fprintf(stderr, "%s%s", "fmtdebug:", "format magic number");
        fprintf(stderr, "%s%ld\n", " = ", (long)x);
    }
    if (x != 1462916184L)
        goto labloadfmtfile6666bad_fmt;
    undumpint(x);
    if (debugformatfile) {
        fprintf(stderr, "%s%s", "fmtdebug:", "engine name size");
        fprintf(stderr, "%s%ld\n", " = ", (long)x);
    }
    if ((x < 0) || (x > 256))
        goto labloadfmtfile6666bad_fmt;
    formatengine = xmallocarray(ASCIIcode, x);
    undumpthings(formatengine[0], x);
    formatengine[x - 1] = 0;
    if (strcmp(enginename, stringcast(formatengine))) {
        ;
        fprintf(stdout, "%s%s%s%s\n", "---! ", stringcast(nameoffile + 1),
                " was written by ", formatengine);
        libcfree(formatengine);
        goto labloadfmtfile6666bad_fmt;
    }
    libcfree(formatengine);
    undumpint(x);
    if (debugformatfile) {
        fprintf(stderr, "%s%s", "fmtdebug:", "string pool checksum");
        fprintf(stderr, "%s%ld\n", " = ", (long)x);
    }
    if (x != 383633139L) {
        ;
        fprintf(stdout, "%s%s%s\n", "---! ", stringcast(nameoffile + 1),
                " made by different executable version");
        goto labloadfmtfile6666bad_fmt;
    }
    /* comment:Undump |xord|, |xchr|, and |xprn| */ if (translatefilename) {
        {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do
                    undumpthings(dummyxord, 1);
                while (k++ < for_end);
        }
        {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do
                    undumpthings(dummyxchr, 1);
                while (k++ < for_end);
        }
        {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do
                    undumpthings(dummyxprn, 1);
                while (k++ < for_end);
        }
    } else {

        undumpthings(xord[0], 256);
        undumpthings(xchr[0], 256);
        undumpthings(xprn[0], 256);
        if (eightbitp) {
            register integer for_end;
            k = 0;
            for_end = 255;
            if (k <= for_end)
                do
                    xprn[k] = 1;
                while (k++ < for_end);
        }
    }
    undumpint(x);
    if (x != 2147483647L)
        goto labloadfmtfile6666bad_fmt;
    undumpint(hashhigh);
    if ((hashhigh < 0) || (hashhigh > suphashextra))
        goto labloadfmtfile6666bad_fmt;
    if (hashextra < hashhigh)
        hashextra = hashhigh;
    eqtbtop = EQTBSIZE + hashextra;
    if (hashextra == 0)
        hashtop = UNDEFINEDCONTROLSEQUENCE;
    else
        hashtop = eqtbtop;
    yhash = xmallocarray(twohalves, 1 + hashtop - hashoffset);
    hash = yhash - hashoffset;
    hash[HASHBASE].v.LH = 0;
    hash[HASHBASE].v.RH = 0;
    {
        register integer for_end;
        x = /* @d14416@ */ 515;
        for_end = hashtop;
        if (x <= for_end)
            do
                hash[x] = hash[HASHBASE];
            while (x++ < for_end);
    }
    zeqtb = xmallocarray(memoryword, eqtbtop + 1);
    eqtb = zeqtb;
    eqtb[UNDEFINEDCONTROLSEQUENCE].hh.b0 = UNDEFINEDCS;
    eqtb[UNDEFINEDCONTROLSEQUENCE].hh.v.RH = TEXNULL;
    eqtb[UNDEFINEDCONTROLSEQUENCE].hh.b1 = LEVELZERO;
    {
        register integer for_end;
        x = /* @d14423@ */ 30184;
        for_end = eqtbtop;
        if (x <= for_end)
            do
                eqtb[x] = eqtb[UNDEFINEDCONTROLSEQUENCE];
            while (x++ < for_end);
    }
    /* comment:Undump the \eTeX\ state */ {

        undumpint(x);
        if ((x < 0) || (x > 1))
            goto labloadfmtfile6666bad_fmt;
        else
            eTeXmode = x;
    }
    if ((eTeXmode == 1)) {
        /* comment:Initialize variables for \eTeX\ extended mode */ maxregnum =
            32767;
        maxreghelpline =
            /* str 'A register number must be between 0 and 32767.' */ 2066;
    } else {

        /* comment:Initialize variables for \eTeX\ compatibility mode */
        maxregnum = 255;
        maxreghelpline =
            /* str 'A register number must be between 0 and 255.' */ 789;
    }
    undumpint(x);
    if (debugformatfile) {
        fprintf(stderr, "%s%s", "fmtdebug:", "mem_bot");
        fprintf(stderr, "%s%ld\n", " = ", (long)x);
    }
    if (x != membot)
        goto labloadfmtfile6666bad_fmt;
    undumpint(memtop);
    if (debugformatfile) {
        fprintf(stderr, "%s%s", "fmtdebug:", "mem_top");
        fprintf(stderr, "%s%ld\n", " = ", (long)memtop);
    }
    if (membot + 1100 > memtop)
        goto labloadfmtfile6666bad_fmt;
    curlist.headfield = memtop - 1;
    curlist.tailfield = memtop - 1;
    pagetail = memtop - 2;
    memmin = membot - extramembot;
    memmax = memtop + extramemtop;
    yzmem = xmallocarray(memoryword, memmax - memmin + 1);
    zmem = yzmem - memmin;
    mem = zmem;
    undumpint(x);
    if (x != EQTBSIZE)
        goto labloadfmtfile6666bad_fmt;
    undumpint(x);
    if (x != HASHPRIME)
        goto labloadfmtfile6666bad_fmt;
    undumpint(x);
    if (x != HYPHPRIME)
        goto labloadfmtfile6666bad_fmt;
    /* comment:Undump ML\TeX-specific data */ undumpint(x);
    if (x != 1296847960L)
        goto labloadfmtfile6666bad_fmt;
    undumpint(x);
    if (x == 1)
        mltexenabledp = true;
    else if (x != 0)
        goto labloadfmtfile6666bad_fmt;
    /* comment:Undump enc\TeX-specific data */ undumpint(x);
    if (x != 1162040408L)
        goto labloadfmtfile6666bad_fmt;
    undumpint(x);
    if (x == 0)
        enctexenabledp = false;
    else if (x != 1)
        goto labloadfmtfile6666bad_fmt;
    else {

        enctexenabledp = true;
        undumpthings(mubyteread[0], 256);
        undumpthings(mubytewrite[0], 256);
        undumpthings(mubytecswrite[0], 128);
    }
    /* comment:Undump the string pool */ {

        undumpint(x);
        if (x < 0)
            goto labloadfmtfile6666bad_fmt;
        if (x > suppoolsize - poolfree) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ",
                    "string pool size");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "string pool size");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        poolptr = x;
    }
    if (poolsize < poolptr + poolfree)
        poolsize = poolptr + poolfree;
    {
        undumpint(x);
        if (x < 0)
            goto labloadfmtfile6666bad_fmt;
        if (x > supmaxstrings - stringsfree) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ", "sup strings");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "sup strings");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        strptr = x;
    }
    if (maxstrings < strptr + stringsfree)
        maxstrings = strptr + stringsfree;
    strstart = xmallocarray(poolpointer, maxstrings);
    undumpcheckedthings(0, poolptr, strstart[0], strptr + 1);
    strpool = xmallocarray(packedASCIIcode, poolsize);
    undumpthings(strpool[0], poolptr);
    initstrptr = strptr;
    initpoolptr = poolptr;
    /* comment:Undump the dynamic memory */ {

        undumpint(x);
        if ((x < /* @d14451@ */ /* @d14452@ */ /* @d14453@ */ /* @d14454@ */
                     /* @d14455@ */ membot + 1019) ||
            (x > memtop - 15))
            goto labloadfmtfile6666bad_fmt;
        else
            lomemmax = x;
    }
    {
        undumpint(x);
        if ((x < /* @d14457@ */ /* @d14458@ */ /* @d14459@ */ /* @d14460@ */
                     /* @d14461@ */ membot + 20) ||
            (x > lomemmax))
            goto labloadfmtfile6666bad_fmt;
        else
            rover = x;
    }
    if ((eTeXmode == 1)) {
        register integer for_end;
        k = INTVAL;
        for_end = TOKVAL;
        if (k <= for_end)
            do {
                undumpint(x);
                if ((x < TEXNULL) || (x > lomemmax))
                    goto labloadfmtfile6666bad_fmt;
                else
                    saroot[k] = x;
            } while (k++ < for_end);
    }
    p = membot;
    q = rover;
    do {
        undumpthings(mem[p], q + 2 - p);
        p = q + mem[q].hh.v.LH;
        if ((p > lomemmax) ||
            ((q >= mem[q + 1].hh.v.RH) && (mem[q + 1].hh.v.RH != rover)))
            goto labloadfmtfile6666bad_fmt;
        q = mem[q + 1].hh.v.RH;
    } while (!(q == rover));
    undumpthings(mem[p], lomemmax + 1 - p);
    if (memmin < membot - 2) {
        p = mem[rover + 1].hh.v.LH;
        q = memmin + 1;
        mem[memmin].hh.v.RH = TEXNULL;
        mem[memmin].hh.v.LH = TEXNULL;
        mem[p + 1].hh.v.RH = q;
        mem[rover + 1].hh.v.LH = q;
        mem[q + 1].hh.v.RH = rover;
        mem[q + 1].hh.v.LH = p;
        mem[q].hh.v.RH = 2147483647L;
        mem[q].hh.v.LH = membot - q;
    }
    {
        undumpint(x);
        if ((x < lomemmax + 1) || (x > memtop - 14))
            goto labloadfmtfile6666bad_fmt;
        else
            himemmin = x;
    }
    {
        undumpint(x);
        if ((x < TEXNULL) || (x > memtop))
            goto labloadfmtfile6666bad_fmt;
        else
            avail = x;
    }
    memend = memtop;
    undumpthings(mem[himemmin], memend + 1 - himemmin);
    undumpint(varused);
    undumpint(dynused);
    /* comment:Undump the table of equivalents */
    /* comment:Undump regions 1 to 6 of |eqtb| */ k = ACTIVEBASE;
    do {
        undumpint(x);
        if ((x < 1) || (k + x > /* @d14472@ */ 30184))
            goto labloadfmtfile6666bad_fmt;
        undumpthings(eqtb[k], x);
        k = k + x;
        undumpint(x);
        if ((x < 0) || (k + x > /* @d14474@ */ 30184))
            goto labloadfmtfile6666bad_fmt;
        {
            register integer for_end;
            j = k;
            for_end = k + x - 1;
            if (j <= for_end)
                do
                    eqtb[j] = eqtb[k - 1];
                while (j++ < for_end);
        }
        k = k + x;
    } while (!(k > EQTBSIZE));
    if (hashhigh > 0)
        undumpthings(eqtb[/* @d14477@ */ 30184], hashhigh);
    {
        undumpint(x);
        if ((x < HASHBASE) || (x > hashtop))
            goto labloadfmtfile6666bad_fmt;
        else
            parloc = x;
    }
    partoken = 4095 + parloc;
    {
        undumpint(x);
        if ((x < HASHBASE) || (x > hashtop))
            goto labloadfmtfile6666bad_fmt;
        else
            writeloc = x;
    }
    /* comment:Undump the hash table */ {
        register integer for_end;
        p = 0;
        for_end = PRIMSIZE;
        if (p <= for_end)
            do
                undumphh(prim[p]);
            while (p++ < for_end);
    }
    {
        undumpint(x);
        if ((x < HASHBASE) || (x > FROZENCONTROLSEQUENCE))
            goto labloadfmtfile6666bad_fmt;
        else
            hashused = x;
    }
    p = /* @d14487@ */ 513;
    do {
        {
            undumpint(x);
            if ((x < p + 1) || (x > hashused))
                goto labloadfmtfile6666bad_fmt;
            else
                p = x;
        }
        undumphh(hash[p]);
    } while (!(p == hashused));
    undumpthings(hash[hashused + 1], /* @d14489@ */ 26626 - hashused);
    if (debugformatfile) {
        printcsnames(HASHBASE, /* @d14491@ */ 26626);
    }
    if (hashhigh > 0) {
        undumpthings(hash[/* @d14492@ */ 30184], hashhigh);
        if (debugformatfile) {
            printcsnames(/* @d14493@ */ 30184,
                         hashhigh - (/* @d14494@ */ 30184));
        }
    }
    undumpint(cscount);
    /* comment:Undump the font information */ {

        undumpint(x);
        if (x < 7)
            goto labloadfmtfile6666bad_fmt;
        if (x > supfontmemsize) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ",
                    "font mem size");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "font mem size");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        fmemptr = x;
    }
    if (fmemptr > fontmemsize)
        fontmemsize = fmemptr;
    fontinfo = xmallocarray(fmemoryword, fontmemsize);
    undumpthings(fontinfo[0], fmemptr);
    {
        undumpint(x);
        if (x < FONTBASE)
            goto labloadfmtfile6666bad_fmt;
        if (x > /* @d14500@ */ MAXFONTMAX) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ", "font max");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "font max");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        fontptr = x;
    }
    /* comment:Undump the array info for internal font number |k| */ {

        fontcheck = xmallocarray(fourquarters, fontmax);
        fontsize = xmallocarray(scaled, fontmax);
        fontdsize = xmallocarray(scaled, fontmax);
        fontparams = xmallocarray(fontindex, fontmax);
        fontname = xmallocarray(strnumber, fontmax);
        fontarea = xmallocarray(strnumber, fontmax);
        fontbc = xmallocarray(eightbits, fontmax);
        fontec = xmallocarray(eightbits, fontmax);
        fontglue = xmallocarray(halfword, fontmax);
        hyphenchar = xmallocarray(integer, fontmax);
        skewchar = xmallocarray(integer, fontmax);
        bcharlabel = xmallocarray(fontindex, fontmax);
        fontbchar = xmallocarray(ninebits, fontmax);
        fontfalsebchar = xmallocarray(ninebits, fontmax);
        charbase = xmallocarray(integer, fontmax);
        widthbase = xmallocarray(integer, fontmax);
        heightbase = xmallocarray(integer, fontmax);
        depthbase = xmallocarray(integer, fontmax);
        italicbase = xmallocarray(integer, fontmax);
        ligkernbase = xmallocarray(integer, fontmax);
        kernbase = xmallocarray(integer, fontmax);
        extenbase = xmallocarray(integer, fontmax);
        parambase = xmallocarray(integer, fontmax);
        pdfcharused = xmallocarray(charusedarray, fontmax);
        pdffontsize = xmallocarray(scaled, fontmax);
        pdffontnum = xmallocarray(integer, fontmax);
        pdffontmap = xmallocarray(fmentryptr, fontmax);
        pdffonttype = xmallocarray(eightbits, fontmax);
        pdffontattr = xmallocarray(strnumber, fontmax);
        pdffontblink = xmallocarray(internalfontnumber, fontmax);
        pdffontelink = xmallocarray(internalfontnumber, fontmax);
        pdffontstretch = xmallocarray(integer, fontmax);
        pdffontshrink = xmallocarray(integer, fontmax);
        pdffontstep = xmallocarray(integer, fontmax);
        pdffontexpandratio = xmallocarray(integer, fontmax);
        pdffontautoexpand = xmallocarray(boolean, fontmax);
        pdffontlpbase = xmallocarray(integer, fontmax);
        pdffontrpbase = xmallocarray(integer, fontmax);
        pdffontefbase = xmallocarray(integer, fontmax);
        pdffontknbsbase = xmallocarray(integer, fontmax);
        pdffontstbsbase = xmallocarray(integer, fontmax);
        pdffontshbsbase = xmallocarray(integer, fontmax);
        pdffontknbcbase = xmallocarray(integer, fontmax);
        pdffontknacbase = xmallocarray(integer, fontmax);
        vfpacketbase = xmallocarray(integer, fontmax);
        vfdefaultfont = xmallocarray(internalfontnumber, fontmax);
        vflocalfontnum = xmallocarray(internalfontnumber, fontmax);
        vfefnts = xmallocarray(integer, fontmax);
        vfifnts = xmallocarray(internalfontnumber, fontmax);
        pdffontnobuiltintounicode = xmallocarray(boolean, fontmax);
        {
            register integer for_end;
            fontk = FONTBASE;
            for_end = fontmax;
            if (fontk <= for_end)
                do {
                    {
                        register integer for_end;
                        k = 0;
                        for_end = 31;
                        if (k <= for_end)
                            do
                                pdfcharused[fontk][k] = 0;
                            while (k++ < for_end);
                    }
                    pdffontsize[fontk] = 0;
                    pdffontnum[fontk] = 0;
                    pdffontmap[fontk] = 0;
                    pdffonttype[fontk] = NEWFONTTYPE;
                    pdffontattr[fontk] = /* str '' */ 345;
                    pdffontblink[fontk] = FONTBASE;
                    pdffontelink[fontk] = FONTBASE;
                    pdffontstretch[fontk] = FONTBASE;
                    pdffontshrink[fontk] = FONTBASE;
                    pdffontstep[fontk] = 0;
                    pdffontexpandratio[fontk] = 0;
                    pdffontautoexpand[fontk] = false;
                    pdffontlpbase[fontk] = 0;
                    pdffontrpbase[fontk] = 0;
                    pdffontefbase[fontk] = 0;
                    pdffontknbsbase[fontk] = 0;
                    pdffontstbsbase[fontk] = 0;
                    pdffontshbsbase[fontk] = 0;
                    pdffontknbcbase[fontk] = 0;
                    pdffontknacbase[fontk] = 0;
                    pdffontnobuiltintounicode[fontk] = false;
                } while (fontk++ < for_end);
        }
        makepdftexbanner();
        undumpthings(fontcheck[FONTBASE], /* @d14512@ */ fontptr + 1);
        undumpthings(fontsize[FONTBASE], /* @d14514@ */ fontptr + 1);
        undumpthings(fontdsize[FONTBASE], /* @d14516@ */ fontptr + 1);
        undumpcheckedthings(TEXNULL, 2147483647L,
                            fontparams[FONTBASE], /* @d14518@ */
                            fontptr + 1);
        undumpthings(hyphenchar[FONTBASE], /* @d14520@ */ fontptr + 1);
        undumpthings(skewchar[FONTBASE], /* @d14522@ */ fontptr + 1);
        undumpuppercheckthings(strptr, fontname[FONTBASE],
                               /* @d14524@ */ fontptr + 1);
        undumpuppercheckthings(strptr, fontarea[FONTBASE],
                               /* @d14526@ */ fontptr + 1);
        undumpthings(fontbc[FONTBASE], /* @d14528@ */ fontptr + 1);
        undumpthings(fontec[FONTBASE], /* @d14530@ */ fontptr + 1);
        undumpthings(charbase[FONTBASE], /* @d14532@ */ fontptr + 1);
        undumpthings(widthbase[FONTBASE], /* @d14534@ */ fontptr + 1);
        undumpthings(heightbase[FONTBASE], /* @d14536@ */ fontptr + 1);
        undumpthings(depthbase[FONTBASE], /* @d14538@ */ fontptr + 1);
        undumpthings(italicbase[FONTBASE], /* @d14540@ */ fontptr + 1);
        undumpthings(ligkernbase[FONTBASE], /* @d14542@ */ fontptr + 1);
        undumpthings(kernbase[FONTBASE], /* @d14544@ */ fontptr + 1);
        undumpthings(extenbase[FONTBASE], /* @d14546@ */ fontptr + 1);
        undumpthings(parambase[FONTBASE], /* @d14548@ */ fontptr + 1);
        undumpcheckedthings(TEXNULL, lomemmax, fontglue[FONTBASE],
                            /* @d14550@ */ fontptr + 1);
        undumpcheckedthings(0, fmemptr - 1, bcharlabel[FONTBASE],
                            /* @d14552@ */ fontptr + 1);
        undumpcheckedthings(MINQUARTERWORD, 256, fontbchar[FONTBASE],
                            /* @d14555@ */ fontptr + 1);
        undumpcheckedthings(MINQUARTERWORD, 256, fontfalsebchar[FONTBASE],
                            /* @d14558@ */ fontptr + 1);
    }
    /* comment:Undump the hyphenation tables */ {

        undumpint(x);
        if (x < 0)
            goto labloadfmtfile6666bad_fmt;
        if (x > hyphsize) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ", "hyph_size");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "hyph_size");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        hyphcount = x;
    }
    {
        undumpint(x);
        if (x < HYPHPRIME)
            goto labloadfmtfile6666bad_fmt;
        if (x > hyphsize) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ", "hyph_size");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "hyph_size");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        hyphnext = x;
    }
    j = 0;
    {
        register integer for_end;
        k = 1;
        for_end = hyphcount;
        if (k <= for_end)
            do {
                undumpint(j);
                if (j < 0)
                    goto labloadfmtfile6666bad_fmt;
                if (j > 65535L) {
                    hyphnext = j / 65536L;
                    j = j - hyphnext * 65536L;
                } else
                    hyphnext = 0;
                if ((j >= hyphsize) || (hyphnext > hyphsize))
                    goto labloadfmtfile6666bad_fmt;
                hyphlink[j] = hyphnext;
                {
                    undumpint(x);
                    if ((x < 0) || (x > strptr))
                        goto labloadfmtfile6666bad_fmt;
                    else
                        hyphword[j] = x;
                }
                {
                    undumpint(x);
                    if ((x < TEXNULL) || (x > 2147483647L))
                        goto labloadfmtfile6666bad_fmt;
                    else
                        hyphlist[j] = x;
                }
            } while (k++ < for_end);
    }
    incr(j);
    if (j < HYPHPRIME)
        j = HYPHPRIME;
    hyphnext = j;
    if (hyphnext >= hyphsize)
        hyphnext = HYPHPRIME;
    else if (hyphnext >= HYPHPRIME)
        incr(hyphnext);
    {
        undumpint(x);
        if (x < 0)
            goto labloadfmtfile6666bad_fmt;
        if (x > triesize) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ", "trie size");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "trie size");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        j = x;
    };
#ifdef INITEX
    triemax = j;
#endif /* INITEX */
    {
        undumpint(x);
        if ((x < 0) || (x > j))
            goto labloadfmtfile6666bad_fmt;
        else
            hyphstart = x;
    }
    if (!trietrl)
        trietrl = xmallocarray(triepointer, j + 1);
    undumpthings(trietrl[0], j + 1);
    if (!trietro)
        trietro = xmallocarray(triepointer, j + 1);
    undumpthings(trietro[0], j + 1);
    if (!trietrc)
        trietrc = xmallocarray(quarterword, j + 1);
    undumpthings(trietrc[0], j + 1);
    {
        undumpint(x);
        if (x < 0)
            goto labloadfmtfile6666bad_fmt;
        if (x > trieopsize) {
            ;
            fprintf(stdout, "%s%s\n", "---! Must increase the ",
                    "trie op size");
            goto labloadfmtfile6666bad_fmt;
        } else if (debugformatfile) {
            fprintf(stderr, "%s%s", "fmtdebug:", "trie op size");
            fprintf(stderr, "%s%ld\n", " = ", (long)x);
        }
        j = x;
    };
#ifdef INITEX
    trieopptr = j;
#endif /* INITEX */
    undumpthings(hyfdistance[1], j);
    undumpthings(hyfnum[1], j);
    undumpuppercheckthings(maxtrieop, hyfnext[1], j);
    ;
#ifdef INITEX
    {
        register integer for_end;
        k = 0;
        for_end = 255;
        if (k <= for_end)
            do
                trieused[k] = MINQUARTERWORD;
            while (k++ < for_end);
    }
#endif /* INITEX */
    k = 256;
    while (j > 0) {

        {
            undumpint(x);
            if ((x < 0) || (x > k - 1))
                goto labloadfmtfile6666bad_fmt;
            else
                k = x;
        }
        {
            undumpint(x);
            if ((x < 1) || (x > j))
                goto labloadfmtfile6666bad_fmt;
            else
                x = x;
        };
#ifdef INITEX
        trieused[k] = x;
#endif /* INITEX */
        j = j - x;
        opstart[k] = j;
    };
#ifdef INITEX
    trienotready = false
#endif /* INITEX */
        ;
    /* comment:Undump pdftex data */ {

        undumpimagemeta(eqtb[INTBASE + PDFMINORVERSIONCODE].cint,
                        eqtb[INTBASE + PDFINCLUSIONERRORLEVELCODE].cint);
        undumpint(pdfmemsize);
        pdfmem = xreallocarray(pdfmem, integer, pdfmemsize);
        undumpint(pdfmemptr);
        {
            register integer for_end;
            k = 1;
            for_end = pdfmemptr - 1;
            if (k <= for_end)
                do {
                    undumpint(pdfmem[k]);
                } while (k++ < for_end);
        }
        undumpint(objtabsize);
        undumpint(objptr);
        undumpint(sysobjptr);
        {
            register integer for_end;
            k = 1;
            for_end = sysobjptr;
            if (k <= for_end)
                do {
                    undumpint(objtab[k].int0);
                    undumpint(objtab[k].int1);
                    objtab[k].int2 = -1;
                    undumpint(objtab[k].int3);
                    undumpint(objtab[k].int4);
                } while (k++ < for_end);
        }
        undumpint(pdfobjcount);
        undumpint(pdfxformcount);
        undumpint(pdfximagecount);
        undumpint(headtab[6]);
        undumpint(headtab[7]);
        undumpint(headtab[8]);
        undumpint(pdflastobj);
        undumpint(pdflastxform);
        undumpint(pdflastximage);
    }
    /* comment:Undump a couple more things and the closing check  */ {

        undumpint(x);
        if ((x < BATCHMODE) || (x > ERRORSTOPMODE))
            goto labloadfmtfile6666bad_fmt;
        else
            interaction = x;
    }
    if (interactionoption != UNSPECIFIEDMODE)
        interaction = interactionoption;
    {
        undumpint(x);
        if ((x < 0) || (x > strptr))
            goto labloadfmtfile6666bad_fmt;
        else
            formatident = x;
    }
    undumpint(x);
    if (x != 69069L)
        goto labloadfmtfile6666bad_fmt;
    curlist.auxfield.cint = eqtb[DIMENBASE + PDFIGNOREDDIMENCODE].cint;
    Result = true;
    return Result;
labloadfmtfile6666bad_fmt:;
    fprintf(stdout, "%s\n", "(Fatal format file error; I'm stymied)");
    Result = false;
    return Result;
}
void finalcleanup(void) {
    finalcleanup_regmem smallnumber c;
    c = curchr;
    if (jobname == 0)
        openlogfile();
    while (inputptr > 0)
        if (curinput.statefield == TOKENLIST)
            endtokenlist();
        else
            endfilereading();
    while (openparens > 0) {

        print(/* str ' )' */ 1723);
        decr(openparens);
    }
    if (curlevel > LEVELONE) {
        printnl(/* str '(' */ 40);
        printesc(/* str 'end occurred ' */ 1724);
        print(/* str 'inside a group at level ' */ 1725);
        printint(curlevel - LEVELONE);
        printchar(/* str ')' */ 41);
        if ((eTeXmode == 1))
            showsavegroups();
    }
    while (condptr != TEXNULL) {

        printnl(/* str '(' */ 40);
        printesc(/* str 'end occurred ' */ 1724);
        print(/* str 'when ' */ 1726);
        printcmdchr(IFTEST, curif);
        if (ifline != 0) {
            print(/* str ' on line ' */ 1727);
            printint(ifline);
        }
        print(/* str ' was incomplete)' */ 1728);
        ifline = mem[condptr + 1].cint;
        curif = mem[condptr].hh.b1;
        tempptr = condptr;
        condptr = mem[condptr].hh.v.RH;
        freenode(tempptr, IFNODESIZE);
    }
    if (history != SPOTLESS) {

        if (((history == WARNINGISSUED) || (interaction < ERRORSTOPMODE))) {

            if (selector == TERMANDLOG) {
                selector = TERMONLY;
                printnl(/* str '(see the transcript file for additional
                           informati' */
                        1729);
                selector = TERMANDLOG;
            }
        }
    }
    if (c == 1) {
        ;
#ifdef INITEX
        if (iniversion) {
            {
                register integer for_end;
                c = TOPMARKCODE;
                for_end = SPLITBOTMARKCODE;
                if (c <= for_end)
                    do
                        if (curmark[c] != TEXNULL)
                            deletetokenref(curmark[c]);
                    while (c++ < for_end);
            }
            if (saroot[MARKVAL] != TEXNULL) {

                if (domarks(3, 0, saroot[MARKVAL]))
                    saroot[MARKVAL] = TEXNULL;
            }
            {
                register integer for_end;
                c = LASTBOXCODE;
                for_end = VSPLITCODE;
                if (c <= for_end)
                    do
                        flushnodelist(discptr[c]);
                    while (c++ < for_end);
            }
            if (lastglue != 2147483647L)
                deleteglueref(lastglue);
            storefmtfile();
            return;
        }
#endif /* INITEX */
        printnl(/* str '(\dump is performed only by INITEX)' */ 1730);
        return;
    }
/* @d14803@ */}
#ifdef INITEX
void initprim(void) {
    initprim_regmem nonewcontrolsequence = false;
    first = 0;
    /* comment:Put each of \TeX's primitives into the hash table */ primitive(
        /* str 'lineskip' */ 393, ASSIGNGLUE,
        GLUEBASE+LINESKIPCODE);
    primitive(/* str 'baselineskip' */ 394, ASSIGNGLUE,
              GLUEBASE+BASELINESKIPCODE);
    primitive(/* str 'parskip' */ 395, ASSIGNGLUE,
              GLUEBASE+PARSKIPCODE);
    primitive(/* str 'abovedisplayskip' */ 396, ASSIGNGLUE,
              GLUEBASE+ABOVEDISPLAYSKIPCODE);
    primitive(/* str 'belowdisplayskip' */ 397, ASSIGNGLUE,
              GLUEBASE+BELOWDISPLAYSKIPCODE);
    primitive(/* str 'abovedisplayshortskip' */ 398, ASSIGNGLUE,
              GLUEBASE+ABOVEDISPLAYSHORTSKIPCODE);
    primitive(/* str 'belowdisplayshortskip' */ 399, ASSIGNGLUE,
              GLUEBASE+BELOWDISPLAYSHORTSKIPCODE);
    primitive(/* str 'leftskip' */ 400, ASSIGNGLUE,
              GLUEBASE+LEFTSKIPCODE);
    primitive(/* str 'rightskip' */ 401, ASSIGNGLUE,
              GLUEBASE+RIGHTSKIPCODE);
    primitive(/* str 'topskip' */ 402, ASSIGNGLUE,
              GLUEBASE+TOPSKIPCODE);
    primitive(/* str 'splittopskip' */ 403, ASSIGNGLUE,
              GLUEBASE+SPLITTOPSKIPCODE);
    primitive(/* str 'tabskip' */ 404, ASSIGNGLUE,
              GLUEBASE+TABSKIPCODE);
    primitive(/* str 'spaceskip' */ 405, ASSIGNGLUE,
              GLUEBASE+SPACESKIPCODE);
    primitive(/* str 'xspaceskip' */ 406, ASSIGNGLUE,
              GLUEBASE+XSPACESKIPCODE);
    primitive(/* str 'parfillskip' */ 407, ASSIGNGLUE,
              GLUEBASE+PARFILLSKIPCODE);
    primitive(/* str 'thinmuskip' */ 408, ASSIGNMUGLUE,
              GLUEBASE+THINMUSKIPCODE);
    primitive(/* str 'medmuskip' */ 409, ASSIGNMUGLUE,
              GLUEBASE+MEDMUSKIPCODE);
    primitive(/* str 'thickmuskip' */ 410, ASSIGNMUGLUE,
              GLUEBASE+THICKMUSKIPCODE);
    primitive(/* str 'output' */ 414, ASSIGNTOKS, OUTPUTROUTINELOC);
    primitive(/* str 'everypar' */ 415, ASSIGNTOKS, EVERYPARLOC);
    primitive(/* str 'everymath' */ 416, ASSIGNTOKS, EVERYMATHLOC);
    primitive(/* str 'everydisplay' */ 417, ASSIGNTOKS, EVERYDISPLAYLOC);
    primitive(/* str 'everyhbox' */ 418, ASSIGNTOKS, EVERYHBOXLOC);
    primitive(/* str 'everyvbox' */ 419, ASSIGNTOKS, EVERYVBOXLOC);
    primitive(/* str 'everyjob' */ 420, ASSIGNTOKS, EVERYJOBLOC);
    primitive(/* str 'everycr' */ 421, ASSIGNTOKS, EVERYCRLOC);
    primitive(/* str 'errhelp' */ 422, ASSIGNTOKS, ERRHELPLOC);
    primitive(/* str 'pdfpagesattr' */ 423, ASSIGNTOKS, PDFPAGESATTRLOC);
    primitive(/* str 'pdfpageattr' */ 424, ASSIGNTOKS, PDFPAGEATTRLOC);
    primitive(/* str 'pdfpageresources' */ 425, ASSIGNTOKS,
              PDFPAGERESOURCESLOC);
    primitive(/* str 'pdfpkmode' */ 426, ASSIGNTOKS, PDFPKMODELOC);
    primitive(/* str 'pretolerance' */ 440, ASSIGNINT,
              INTBASE+PRETOLERANCECODE);
    primitive(/* str 'tolerance' */ 441, ASSIGNINT,
              INTBASE+TOLERANCECODE);
    primitive(/* str 'linepenalty' */ 442, ASSIGNINT,
              INTBASE+LINEPENALTYCODE);
    primitive(/* str 'hyphenpenalty' */ 443, ASSIGNINT,
              INTBASE+HYPHENPENALTYCODE);
    primitive(/* str 'exhyphenpenalty' */ 444, ASSIGNINT,
              INTBASE+EXHYPHENPENALTYCODE);
    primitive(/* str 'clubpenalty' */ 445, ASSIGNINT,
              INTBASE+CLUBPENALTYCODE);
    primitive(/* str 'widowpenalty' */ 446, ASSIGNINT,
              INTBASE+WIDOWPENALTYCODE);
    primitive(/* str 'displaywidowpenalty' */ 447, ASSIGNINT,
              INTBASE+DISPLAYWIDOWPENALTYCODE);
    primitive(/* str 'brokenpenalty' */ 448, ASSIGNINT,
              INTBASE+BROKENPENALTYCODE);
    primitive(/* str 'binoppenalty' */ 449, ASSIGNINT,
              INTBASE+BINOPPENALTYCODE);
    primitive(/* str 'relpenalty' */ 450, ASSIGNINT,
              INTBASE+RELPENALTYCODE);
    primitive(/* str 'predisplaypenalty' */ 451, ASSIGNINT,
              INTBASE+PREDISPLAYPENALTYCODE);
    primitive(/* str 'postdisplaypenalty' */ 452, ASSIGNINT,
              INTBASE+POSTDISPLAYPENALTYCODE);
    primitive(/* str 'interlinepenalty' */ 453, ASSIGNINT,
              INTBASE+INTERLINEPENALTYCODE);
    primitive(/* str 'doublehyphendemerits' */ 454, ASSIGNINT,
              INTBASE+DOUBLEHYPHENDEMERITSCODE);
    primitive(/* str 'finalhyphendemerits' */ 455, ASSIGNINT,
              INTBASE+FINALHYPHENDEMERITSCODE);
    primitive(/* str 'adjdemerits' */ 456, ASSIGNINT,
              INTBASE+ADJDEMERITSCODE);
    primitive(/* str 'mag' */ 457, ASSIGNINT,
              INTBASE+MAGCODE);
    primitive(/* str 'delimiterfactor' */ 458, ASSIGNINT,
              INTBASE+DELIMITERFACTORCODE);
    primitive(/* str 'looseness' */ 459, ASSIGNINT,
              INTBASE+LOOSENESSCODE);
    primitive(/* str 'time' */ 460, ASSIGNINT,
              INTBASE+TIMECODE);
    primitive(/* str 'day' */ 461, ASSIGNINT,
              INTBASE+DAYCODE);
    primitive(/* str 'month' */ 462, ASSIGNINT,
              INTBASE+MONTHCODE);
    primitive(/* str 'year' */ 463, ASSIGNINT,
              INTBASE+YEARCODE);
    primitive(/* str 'showboxbreadth' */ 464, ASSIGNINT,
              INTBASE+SHOWBOXBREADTHCODE);
    primitive(/* str 'showboxdepth' */ 465, ASSIGNINT,
              INTBASE+SHOWBOXDEPTHCODE);
    primitive(/* str 'hbadness' */ 466, ASSIGNINT,
              INTBASE+HBADNESSCODE);
    primitive(/* str 'vbadness' */ 467, ASSIGNINT,
              INTBASE+VBADNESSCODE);
    primitive(/* str 'pausing' */ 468, ASSIGNINT,
              INTBASE+PAUSINGCODE);
    primitive(/* str 'tracingonline' */ 469, ASSIGNINT,
              INTBASE+TRACINGONLINECODE);
    primitive(/* str 'tracingmacros' */ 470, ASSIGNINT,
              INTBASE+TRACINGMACROSCODE);
    primitive(/* str 'tracingstats' */ 471, ASSIGNINT,
              INTBASE+TRACINGSTATSCODE);
    primitive(/* str 'tracingparagraphs' */ 472, ASSIGNINT,
              INTBASE+TRACINGPARAGRAPHSCODE);
    primitive(/* str 'tracingpages' */ 473, ASSIGNINT,
              INTBASE+TRACINGPAGESCODE);
    primitive(/* str 'tracingoutput' */ 474, ASSIGNINT,
              INTBASE+TRACINGOUTPUTCODE);
    primitive(/* str 'tracinglostchars' */ 475, ASSIGNINT,
              INTBASE+TRACINGLOSTCHARSCODE);
    primitive(/* str 'tracingcommands' */ 476, ASSIGNINT,
              INTBASE+TRACINGCOMMANDSCODE);
    primitive(/* str 'tracingrestores' */ 477, ASSIGNINT,
              INTBASE+TRACINGRESTORESCODE);
    primitive(/* str 'uchyph' */ 478, ASSIGNINT,
              INTBASE+UCHYPHCODE);
    primitive(/* str 'outputpenalty' */ 479, ASSIGNINT,
              INTBASE+OUTPUTPENALTYCODE);
    primitive(/* str 'maxdeadcycles' */ 480, ASSIGNINT,
              INTBASE+MAXDEADCYCLESCODE);
    primitive(/* str 'hangafter' */ 481, ASSIGNINT,
              INTBASE+HANGAFTERCODE);
    primitive(/* str 'floatingpenalty' */ 482, ASSIGNINT,
              INTBASE+FLOATINGPENALTYCODE);
    primitive(/* str 'globaldefs' */ 483, ASSIGNINT,
              INTBASE+GLOBALDEFSCODE);
    primitive(/* str 'fam' */ 484, ASSIGNINT,
              INTBASE+CURFAMCODE);
    primitive(/* str 'escapechar' */ 485, ASSIGNINT,
              INTBASE+ESCAPECHARCODE);
    primitive(/* str 'defaulthyphenchar' */ 486, ASSIGNINT,
              INTBASE+DEFAULTHYPHENCHARCODE);
    primitive(/* str 'defaultskewchar' */ 487, ASSIGNINT,
              INTBASE+DEFAULTSKEWCHARCODE);
    primitive(/* str 'endlinechar' */ 488, ASSIGNINT,
              INTBASE+ENDLINECHARCODE);
    primitive(/* str 'newlinechar' */ 489, ASSIGNINT,
              INTBASE+NEWLINECHARCODE);
    primitive(/* str 'language' */ 490, ASSIGNINT,
              INTBASE+LANGUAGECODE);
    primitive(/* str 'lefthyphenmin' */ 491, ASSIGNINT,
              INTBASE+LEFTHYPHENMINCODE);
    primitive(/* str 'righthyphenmin' */ 492, ASSIGNINT,
              INTBASE+RIGHTHYPHENMINCODE);
    primitive(/* str 'holdinginserts' */ 493, ASSIGNINT,
              INTBASE+HOLDINGINSERTSCODE);
    primitive(/* str 'errorcontextlines' */ 494, ASSIGNINT,
              INTBASE+ERRORCONTEXTLINESCODE);
    if (mltexp) {
        mltexenabledp = true;
        if (false)
            primitive(/* str 'charsubdefmin' */ 495, ASSIGNINT,
                      INTBASE+CHARSUBDEFMINCODE);
        primitive(/* str 'charsubdefmax' */ 496, ASSIGNINT,
                  INTBASE+CHARSUBDEFMAXCODE);
        primitive(/* str 'tracingcharsubdef' */ 497, ASSIGNINT,
                  INTBASE+TRACINGCHARSUBDEFCODE);
    }
    if (enctexp) {
        enctexenabledp = true;
        primitive(/* str 'mubytein' */ 498, ASSIGNINT,
                  INTBASE+MUBYTEINCODE);
        primitive(/* str 'mubyteout' */ 499, ASSIGNINT,
                  INTBASE+MUBYTEOUTCODE);
        primitive(/* str 'mubytelog' */ 500, ASSIGNINT,
                  INTBASE+MUBYTELOGCODE);
        primitive(/* str 'specialout' */ 501, ASSIGNINT,
                  INTBASE+SPECOUTCODE);
    }
    primitive(/* str 'pdfoutput' */ 502, ASSIGNINT,
              INTBASE+PDFOUTPUTCODE);
    primitive(/* str 'pdfcompresslevel' */ 503, ASSIGNINT,
              INTBASE+PDFCOMPRESSLEVELCODE);
    primitive(/* str 'pdfobjcompresslevel' */ 504, ASSIGNINT,
              INTBASE+PDFOBJCOMPRESSLEVELCODE);
    primitive(/* str 'pdfdecimaldigits' */ 505, ASSIGNINT,
              INTBASE+PDFDECIMALDIGITSCODE);
    primitive(/* str 'pdfmovechars' */ 506, ASSIGNINT,
              INTBASE+PDFMOVECHARSCODE);
    primitive(/* str 'pdfimageresolution' */ 507, ASSIGNINT,
              INTBASE+PDFIMAGERESOLUTIONCODE);
    primitive(/* str 'pdfpkresolution' */ 508, ASSIGNINT,
              INTBASE+PDFPKRESOLUTIONCODE);
    primitive(/* str 'pdfuniqueresname' */ 509, ASSIGNINT,
              INTBASE+PDFUNIQUERESNAMECODE);
    primitive(/* str 'pdfoptionpdfminorversion' */ 536, ASSIGNINT,
              INTBASE+PDFMINORVERSIONCODE);
    primitive(/* str 'pdfoptionalwaysusepdfpagebox' */ 510, ASSIGNINT,
              INTBASE+PDFOPTIONALWAYSUSEPDFPAGEBOXCODE);
    primitive(/* str 'pdfoptionpdfinclusionerrorlevel' */ 511, ASSIGNINT,
              INTBASE+PDFOPTIONPDFINCLUSIONERRORLEVELCODE);
    primitive(/* str 'pdfminorversion' */ 512, ASSIGNINT,
              INTBASE+PDFMINORVERSIONCODE);
    primitive(/* str 'pdfforcepagebox' */ 513, ASSIGNINT,
              INTBASE+PDFFORCEPAGEBOXCODE);
    primitive(/* str 'pdfpagebox' */ 514, ASSIGNINT,
              INTBASE+PDFPAGEBOXCODE);
    primitive(/* str 'pdfinclusionerrorlevel' */ 515, ASSIGNINT,
              INTBASE+PDFINCLUSIONERRORLEVELCODE);
    primitive(/* str 'pdfgamma' */ 516, ASSIGNINT,
              INTBASE+PDFGAMMACODE);
    primitive(/* str 'pdfimagegamma' */ 517, ASSIGNINT,
              INTBASE+PDFIMAGEGAMMACODE);
    primitive(/* str 'pdfimagehicolor' */ 518, ASSIGNINT,
              INTBASE+PDFIMAGEHICOLORCODE);
    primitive(/* str 'pdfimageapplygamma' */ 519, ASSIGNINT,
              INTBASE+PDFIMAGEAPPLYGAMMACODE);
    primitive(/* str 'pdfadjustspacing' */ 520, ASSIGNINT,
              INTBASE+PDFADJUSTSPACINGCODE);
    primitive(/* str 'pdfprotrudechars' */ 521, ASSIGNINT,
              INTBASE+PDFPROTRUDECHARSCODE);
    primitive(/* str 'pdftracingfonts' */ 522, ASSIGNINT,
              INTBASE+PDFTRACINGFONTSCODE);
    primitive(/* str 'pdfadjustinterwordglue' */ 523, ASSIGNINT,
              INTBASE+PDFADJUSTINTERWORDGLUECODE);
    primitive(/* str 'pdfprependkern' */ 524, ASSIGNINT,
              INTBASE+PDFPREPENDKERNCODE);
    primitive(/* str 'pdfappendkern' */ 525, ASSIGNINT,
              INTBASE+PDFAPPENDKERNCODE);
    primitive(/* str 'pdfgentounicode' */ 526, ASSIGNINT,
              INTBASE+PDFGENTOUNICODECODE);
    primitive(/* str 'pdfdraftmode' */ 527, ASSIGNINT,
              INTBASE+PDFDRAFTMODECODE);
    primitive(/* str 'pdfinclusioncopyfonts' */ 528, ASSIGNINT,
              INTBASE+PDFINCLUSIONCOPYFONTCODE);
    primitive(/* str 'pdfsuppresswarningdupdest' */ 529, ASSIGNINT,
              INTBASE+PDFSUPPRESSWARNINGDUPDESTCODE);
    primitive(/* str 'pdfsuppresswarningdupmap' */ 530, ASSIGNINT,
              INTBASE+PDFSUPPRESSWARNINGDUPMAPCODE);
    primitive(/* str 'pdfsuppresswarningpagegroup' */ 531, ASSIGNINT,
              INTBASE+PDFSUPPRESSWARNINGPAGEGROUPCODE);
    primitive(/* str 'pdfinfoomitdate' */ 532, ASSIGNINT,
              INTBASE+PDFINFOOMITDATECODE);
    primitive(/* str 'pdfsuppressptexinfo' */ 533, ASSIGNINT,
              INTBASE+PDFSUPPRESSPTEXINFOCODE);
    primitive(/* str 'pdfomitcharset' */ 534, ASSIGNINT,
              INTBASE+PDFOMITCHARSETCODE);
    primitive(/* str 'parindent' */ 539, ASSIGNDIMEN,
              DIMENBASE+PARINDENTCODE);
    primitive(/* str 'mathsurround' */ 540, ASSIGNDIMEN,
              DIMENBASE+MATHSURROUNDCODE);
    primitive(/* str 'lineskiplimit' */ 541, ASSIGNDIMEN,
              DIMENBASE+LINESKIPLIMITCODE);
    primitive(/* str 'hsize' */ 542, ASSIGNDIMEN,
              DIMENBASE+HSIZECODE);
    primitive(/* str 'vsize' */ 543, ASSIGNDIMEN,
              DIMENBASE+VSIZECODE);
    primitive(/* str 'maxdepth' */ 544, ASSIGNDIMEN,
              DIMENBASE+MAXDEPTHCODE);
    primitive(/* str 'splitmaxdepth' */ 545, ASSIGNDIMEN,
              DIMENBASE+SPLITMAXDEPTHCODE);
    primitive(/* str 'boxmaxdepth' */ 546, ASSIGNDIMEN,
              DIMENBASE+BOXMAXDEPTHCODE);
    primitive(/* str 'hfuzz' */ 547, ASSIGNDIMEN,
              DIMENBASE+HFUZZCODE);
    primitive(/* str 'vfuzz' */ 548, ASSIGNDIMEN,
              DIMENBASE+VFUZZCODE);
    primitive(/* str 'delimitershortfall' */ 549, ASSIGNDIMEN,
              DIMENBASE+DELIMITERSHORTFALLCODE);
    primitive(/* str 'nulldelimiterspace' */ 550, ASSIGNDIMEN,
              DIMENBASE+NULLDELIMITERSPACECODE);
    primitive(/* str 'scriptspace' */ 551, ASSIGNDIMEN,
              DIMENBASE+SCRIPTSPACECODE);
    primitive(/* str 'predisplaysize' */ 552, ASSIGNDIMEN,
              DIMENBASE+PREDISPLAYSIZECODE);
    primitive(/* str 'displaywidth' */ 553, ASSIGNDIMEN,
              DIMENBASE+DISPLAYWIDTHCODE);
    primitive(/* str 'displayindent' */ 554, ASSIGNDIMEN,
              DIMENBASE+DISPLAYINDENTCODE);
    primitive(/* str 'overfullrule' */ 555, ASSIGNDIMEN,
              DIMENBASE+OVERFULLRULECODE);
    primitive(/* str 'hangindent' */ 556, ASSIGNDIMEN,
              DIMENBASE+HANGINDENTCODE);
    primitive(/* str 'hoffset' */ 557, ASSIGNDIMEN,
              DIMENBASE+HOFFSETCODE);
    primitive(/* str 'voffset' */ 558, ASSIGNDIMEN,
              DIMENBASE+VOFFSETCODE);
    primitive(/* str 'emergencystretch' */ 559, ASSIGNDIMEN,
              DIMENBASE+EMERGENCYSTRETCHCODE);
    primitive(/* str 'pdfhorigin' */ 560, ASSIGNDIMEN,
              DIMENBASE+PDFHORIGINCODE);
    primitive(/* str 'pdfvorigin' */ 561, ASSIGNDIMEN,
              DIMENBASE+PDFVORIGINCODE);
    primitive(/* str 'pdfpagewidth' */ 562, ASSIGNDIMEN,
              DIMENBASE+PDFPAGEWIDTHCODE);
    primitive(/* str 'pdfpageheight' */ 563, ASSIGNDIMEN,
              DIMENBASE+PDFPAGEHEIGHTCODE);
    primitive(/* str 'pdflinkmargin' */ 564, ASSIGNDIMEN,
              DIMENBASE+PDFLINKMARGINCODE);
    primitive(/* str 'pdfdestmargin' */ 565, ASSIGNDIMEN,
              DIMENBASE+PDFDESTMARGINCODE);
    primitive(/* str 'pdfthreadmargin' */ 566, ASSIGNDIMEN,
              DIMENBASE+PDFTHREADMARGINCODE);
    primitive(/* str 'pdffirstlineheight' */ 567, ASSIGNDIMEN,
              DIMENBASE+PDFFIRSTLINEHEIGHTCODE);
    primitive(/* str 'pdflastlinedepth' */ 568, ASSIGNDIMEN,
              DIMENBASE+PDFLASTLINEDEPTHCODE);
    primitive(/* str 'pdfeachlineheight' */ 569, ASSIGNDIMEN,
              DIMENBASE+PDFEACHLINEHEIGHTCODE);
    primitive(/* str 'pdfeachlinedepth' */ 570, ASSIGNDIMEN,
              DIMENBASE+PDFEACHLINEDEPTHCODE);
    primitive(/* str 'pdfignoreddimen' */ 571, ASSIGNDIMEN,
              DIMENBASE+PDFIGNOREDDIMENCODE);
    primitive(/* str 'pdfpxdimen' */ 572, ASSIGNDIMEN,
              DIMENBASE+PDFPXDIMENCODE);
    primitive(/* str ' ' */ 32, EXSPACE, 0);
    primitive(/* str '' */ 47, ITALCORR, 0);
    primitive(/* str 'accent' */ 584, ACCENT, 0);
    primitive(/* str 'advance' */ 585, ADVANCE, 0);
    primitive(/* str 'afterassignment' */ 586, AFTERASSIGNMENT, 0);
    primitive(/* str 'aftergroup' */ 587, AFTERGROUP, 0);
    primitive(/* str 'begingroup' */ 588, BEGINGROUP, 0);
    primitive(/* str 'char' */ 589, CHARNUM, 0);
    primitive(/* str 'csname' */ 580, CSNAME, 0);
    primitive(/* str 'delimiter' */ 590, DELIMNUM, 0);
    primitive(/* str 'divide' */ 591, DIVIDE, 0);
    primitive(/* str 'endcsname' */ 581, ENDCSNAME, 0);
    if (enctexp) {
        primitive(/* str 'endmubyte' */ 592, ENDCSNAME, 10);
    }
    primitive(/* str 'endgroup' */ 593, ENDGROUP, 0);
    hash[FROZENENDGROUP].v.RH = /* str 'endgroup' */ 593;
    eqtb[FROZENENDGROUP] = eqtb[curval];
    primitive(/* str 'expandafter' */ 594, EXPANDAFTER, 0);
    primitive(/* str 'font' */ 595, DEFFONT, 0);
    primitive(/* str 'letterspacefont' */ 596, LETTERSPACEFONT, 0);
    primitive(/* str 'pdfcopyfont' */ 597, PDFCOPYFONT, 0);
    primitive(/* str 'fontdimen' */ 598, ASSIGNFONTDIMEN, 0);
    primitive(/* str 'halign' */ 599, HALIGN, 0);
    primitive(/* str 'hrule' */ 600, HRULE, 0);
    primitive(/* str 'ignorespaces' */ 601, IGNORESPACES, 0);
    primitive(/* str 'insert' */ 337, INSERT, 0);
    primitive(/* str 'mark' */ 359, MARK, 0);
    primitive(/* str 'mathaccent' */ 602, MATHACCENT, 0);
    primitive(/* str 'mathchar' */ 603, MATHCHARNUM, 0);
    primitive(/* str 'mathchoice' */ 604, MATHCHOICE, 0);
    primitive(/* str 'multiply' */ 605, MULTIPLY, 0);
    primitive(/* str 'noalign' */ 606, NOALIGN, 0);
    primitive(/* str 'noboundary' */ 607, NOBOUNDARY, 0);
    primitive(/* str 'noexpand' */ 608, NOEXPAND, 0);
    primitive(/* str 'pdfprimitive' */ 577, NOEXPAND, 1);
    primitive(/* str 'nonscript' */ 342, NONSCRIPT, 0);
    primitive(/* str 'omit' */ 609, OMIT, 0);
    primitive(/* str 'parshape' */ 610, SETSHAPE, PARSHAPELOC);
    primitive(/* str 'penalty' */ 611, BREAKPENALTY, 0);
    primitive(/* str 'prevgraf' */ 612, SETPREVGRAF, 0);
    primitive(/* str 'radical' */ 613, RADICAL, 0);
    primitive(/* str 'read' */ 614, READTOCS, 0);
    primitive(/* str 'relax' */ 615, RELAX, 256);
    hash[FROZENRELAX].v.RH = /* str 'relax' */ 615;
    eqtb[FROZENRELAX] = eqtb[curval];
    primitive(/* str 'setbox' */ 616, SETBOX, 0);
    primitive(/* str 'the' */ 617, THE, 0);
    primitive(/* str 'toks' */ 427, TOKSREGISTER, membot);
    primitive(/* str 'vadjust' */ 360, VADJUST, 0);
    primitive(/* str 'valign' */ 618, VALIGN, 0);
    primitive(/* str 'vcenter' */ 619, VCENTER, 0);
    primitive(/* str 'vrule' */ 620, VRULE, 0);
    primitive(/* str 'par' */ 681, PAREND, 256);
    parloc = curval;
    partoken = 4095 + parloc;
    primitive(/* str 'input' */ 716, INPUT, 0);
    primitive(/* str 'endinput' */ 717, INPUT, 1);
    primitive(/* str 'topmark' */ 718, TOPBOTMARK, TOPMARKCODE);
    primitive(/* str 'firstmark' */ 719, TOPBOTMARK, FIRSTMARKCODE);
    primitive(/* str 'botmark' */ 720, TOPBOTMARK, BOTMARKCODE);
    primitive(/* str 'splitfirstmark' */ 721, TOPBOTMARK, SPLITFIRSTMARKCODE);
    primitive(/* str 'splitbotmark' */ 722, TOPBOTMARK, SPLITBOTMARKCODE);
    primitive(/* str 'count' */ 537, REGISTER, membot + INTVAL);
    primitive(/* str 'dimen' */ 574, REGISTER, membot + DIMENVAL);
    primitive(/* str 'skip' */ 412, REGISTER, membot + GLUEVAL);
    primitive(/* str 'muskip' */ 413, REGISTER, membot + MUVAL);
    primitive(/* str 'spacefactor' */ 755, SETAUX, HMODE);
    primitive(/* str 'prevdepth' */ 756, SETAUX, VMODE);
    primitive(/* str 'deadcycles' */ 757, SETPAGEINT, 0);
    primitive(/* str 'insertpenalties' */ 758, SETPAGEINT, 1);
    primitive(/* str 'wd' */ 759, SETBOXDIMEN, WIDTHOFFSET);
    primitive(/* str 'ht' */ 760, SETBOXDIMEN, HEIGHTOFFSET);
    primitive(/* str 'dp' */ 761, SETBOXDIMEN, DEPTHOFFSET);
    primitive(/* str 'lastpenalty' */ 762, LASTITEM, INTVAL);
    primitive(/* str 'lastkern' */ 763, LASTITEM, DIMENVAL);
    primitive(/* str 'lastskip' */ 764, LASTITEM, GLUEVAL);
    primitive(/* str 'inputlineno' */ 765, LASTITEM, INPUTLINENOCODE);
    primitive(/* str 'badness' */ 766, LASTITEM, BADNESSCODE);
    primitive(/* str 'pdftexversion' */ 767, LASTITEM, PDFTEXVERSIONCODE);
    primitive(/* str 'pdflastobj' */ 768, LASTITEM, PDFLASTOBJCODE);
    primitive(/* str 'pdflastxform' */ 769, LASTITEM, PDFLASTXFORMCODE);
    primitive(/* str 'pdflastximage' */ 770, LASTITEM, PDFLASTXIMAGECODE);
    primitive(/* str 'pdflastximagepages' */ 771, LASTITEM,
              PDFLASTXIMAGEPAGESCODE);
    primitive(/* str 'pdflastannot' */ 772, LASTITEM, PDFLASTANNOTCODE);
    primitive(/* str 'pdflastxpos' */ 773, LASTITEM, PDFLASTXPOSCODE);
    primitive(/* str 'pdflastypos' */ 774, LASTITEM, PDFLASTYPOSCODE);
    primitive(/* str 'pdfretval' */ 775, LASTITEM, PDFRETVALCODE);
    primitive(/* str 'pdflastximagecolordepth' */ 776, LASTITEM,
              PDFLASTXIMAGECOLORDEPTHCODE);
    primitive(/* str 'pdfelapsedtime' */ 777, LASTITEM, ELAPSEDTIMECODE);
    primitive(/* str 'pdfshellescape' */ 778, LASTITEM, PDFSHELLESCAPECODE);
    primitive(/* str 'pdfrandomseed' */ 779, LASTITEM, RANDOMSEEDCODE);
    primitive(/* str 'pdflastlink' */ 780, LASTITEM, PDFLASTLINKCODE);
    primitive(/* str 'number' */ 839, CONVERT, NUMBERCODE);
    primitive(/* str 'romannumeral' */ 840, CONVERT, ROMANNUMERALCODE);
    primitive(/* str 'string' */ 841, CONVERT, STRINGCODE);
    primitive(/* str 'meaning' */ 842, CONVERT, MEANINGCODE);
    primitive(/* str 'fontname' */ 843, CONVERT, FONTNAMECODE);
    primitive(/* str 'expanded' */ 844, CONVERT, EXPANDEDCODE);
    primitive(/* str 'pdftexrevision' */ 845, CONVERT, PDFTEXREVISIONCODE);
    primitive(/* str 'pdftexbanner' */ 846, CONVERT, PDFTEXBANNERCODE);
    primitive(/* str 'pdffontname' */ 847, CONVERT, PDFFONTNAMECODE);
    primitive(/* str 'pdffontobjnum' */ 848, CONVERT, PDFFONTOBJNUMCODE);
    primitive(/* str 'pdffontsize' */ 849, CONVERT, PDFFONTSIZECODE);
    primitive(/* str 'pdfpageref' */ 850, CONVERT, PDFPAGEREFCODE);
    primitive(/* str 'leftmarginkern' */ 851, CONVERT, LEFTMARGINKERNCODE);
    primitive(/* str 'rightmarginkern' */ 852, CONVERT, RIGHTMARGINKERNCODE);
    primitive(/* str 'pdfxformname' */ 853, CONVERT, PDFXFORMNAMECODE);
    primitive(/* str 'pdfescapestring' */ 854, CONVERT, PDFESCAPESTRINGCODE);
    primitive(/* str 'pdfescapename' */ 855, CONVERT, PDFESCAPENAMECODE);
    primitive(/* str 'pdfescapehex' */ 856, CONVERT, PDFESCAPEHEXCODE);
    primitive(/* str 'pdfunescapehex' */ 857, CONVERT, PDFUNESCAPEHEXCODE);
    primitive(/* str 'pdfcreationdate' */ 858, CONVERT, PDFCREATIONDATECODE);
    primitive(/* str 'pdffilemoddate' */ 859, CONVERT, PDFFILEMODDATECODE);
    primitive(/* str 'pdffilesize' */ 860, CONVERT, PDFFILESIZECODE);
    primitive(/* str 'pdfmdfivesum' */ 861, CONVERT, PDFMDFIVESUMCODE);
    primitive(/* str 'pdffiledump' */ 862, CONVERT, PDFFILEDUMPCODE);
    primitive(/* str 'pdfmatch' */ 863, CONVERT, PDFMATCHCODE);
    primitive(/* str 'pdflastmatch' */ 864, CONVERT, PDFLASTMATCHCODE);
    primitive(/* str 'pdfstrcmp' */ 865, CONVERT, PDFSTRCMPCODE);
    primitive(/* str 'pdfcolorstackinit' */ 866, CONVERT,
              PDFCOLORSTACKINITCODE);
    primitive(/* str 'pdfuniformdeviate' */ 867, CONVERT, UNIFORMDEVIATECODE);
    primitive(/* str 'pdfnormaldeviate' */ 868, CONVERT, NORMALDEVIATECODE);
    primitive(/* str 'jobname' */ 869, CONVERT, JOBNAMECODE);
    primitive(/* str 'pdfinsertht' */ 870, CONVERT, PDFINSERTHTCODE);
    primitive(/* str 'pdfximagebbox' */ 871, CONVERT, PDFXIMAGEBBOXCODE);
    primitive(/* str 'if' */ 910, IFTEST, IFCHARCODE);
    primitive(/* str 'ifcat' */ 911, IFTEST, IFCATCODE);
    primitive(/* str 'ifnum' */ 912, IFTEST, IFINTCODE);
    primitive(/* str 'ifdim' */ 913, IFTEST, IFDIMCODE);
    primitive(/* str 'ifodd' */ 914, IFTEST, IFODDCODE);
    primitive(/* str 'ifvmode' */ 915, IFTEST, IFVMODECODE);
    primitive(/* str 'ifhmode' */ 916, IFTEST, IFHMODECODE);
    primitive(/* str 'ifmmode' */ 917, IFTEST, IFMMODECODE);
    primitive(/* str 'ifinner' */ 918, IFTEST, IFINNERCODE);
    primitive(/* str 'ifvoid' */ 919, IFTEST, IFVOIDCODE);
    primitive(/* str 'ifhbox' */ 920, IFTEST, IFHBOXCODE);
    primitive(/* str 'ifvbox' */ 921, IFTEST, IFVBOXCODE);
    primitive(/* str 'ifx' */ 922, IFTEST, IFXCODE);
    primitive(/* str 'ifeof' */ 923, IFTEST, IFEOFCODE);
    primitive(/* str 'iftrue' */ 924, IFTEST, IFTRUECODE);
    primitive(/* str 'iffalse' */ 925, IFTEST, IFFALSECODE);
    primitive(/* str 'ifcase' */ 926, IFTEST, IFCASECODE);
    primitive(/* str 'ifpdfprimitive' */ 927, IFTEST, IFPDFPRIMITIVECODE);
    primitive(/* str 'fi' */ 929, FIORELSE, FICODE);
    hash[FROZENFI].v.RH = /* str 'fi' */ 929;
    eqtb[FROZENFI] = eqtb[curval];
    primitive(/* str 'or' */ 930, FIORELSE, ORCODE);
    primitive(/* str 'else' */ 931, FIORELSE, ELSECODE);
    primitive(/* str 'nullfont' */ 956, SETFONT, FONTBASE);
    hash[FROZENNULLFONT].v.RH = /* str 'nullfont' */ 956;
    eqtb[FROZENNULLFONT] = eqtb[curval];
    primitive(/* str 'span' */ 1308, TABMARK, SPANCODE);
    primitive(/* str 'cr' */ 1309, CARRET, CRCODE);
    hash[FROZENCR].v.RH = /* str 'cr' */ 1309;
    eqtb[FROZENCR] = eqtb[curval];
    primitive(/* str 'crcr' */ 1310, CARRET, CRCRCODE);
    hash[FROZENENDTEMPLATE].v.RH = /* str 'endtemplate' */ 1311;
    hash[FROZENENDV].v.RH = /* str 'endtemplate' */ 1311;
    eqtb[FROZENENDV].hh.b0 = ENDV;
    eqtb[FROZENENDV].hh.v.RH = memtop - 11;
    eqtb[FROZENENDV].hh.b1 = LEVELONE;
    eqtb[FROZENENDTEMPLATE] = eqtb[FROZENENDV];
    eqtb[FROZENENDTEMPLATE].hh.b0 = ENDTEMPLATE;
    primitive(/* str 'pagegoal' */ 1386, SETPAGEDIMEN, 0);
    primitive(/* str 'pagetotal' */ 1387, SETPAGEDIMEN, 1);
    primitive(/* str 'pagestretch' */ 1388, SETPAGEDIMEN, 2);
    primitive(/* str 'pagefilstretch' */ 1389, SETPAGEDIMEN, 3);
    primitive(/* str 'pagefillstretch' */ 1390, SETPAGEDIMEN, 4);
    primitive(/* str 'pagefilllstretch' */ 1391, SETPAGEDIMEN, 5);
    primitive(/* str 'pageshrink' */ 1392, SETPAGEDIMEN, 6);
    primitive(/* str 'pagedepth' */ 1393, SETPAGEDIMEN, 7);
    primitive(/* str 'end' */ 349, STOP, 0);
    primitive(/* str 'dump' */ 1439, STOP, 1);
    primitive(/* str 'hskip' */ 1440, HSKIP, SKIPCODE);
    primitive(/* str 'hfil' */ 1441, HSKIP, FILCODE);
    primitive(/* str 'hfill' */ 1442, HSKIP, FILLCODE);
    primitive(/* str 'hss' */ 1443, HSKIP, SSCODE);
    primitive(/* str 'hfilneg' */ 1444, HSKIP, FILNEGCODE);
    primitive(/* str 'vskip' */ 1445, VSKIP, SKIPCODE);
    primitive(/* str 'vfil' */ 1446, VSKIP, FILCODE);
    primitive(/* str 'vfill' */ 1447, VSKIP, FILLCODE);
    primitive(/* str 'vss' */ 1448, VSKIP, SSCODE);
    primitive(/* str 'vfilneg' */ 1449, VSKIP, FILNEGCODE);
    primitive(/* str 'mskip' */ 343, MSKIP, MSKIPCODE);
    primitive(/* str 'kern' */ 322, KERN, EXPLICIT);
    primitive(/* str 'mkern' */ 348, MKERN, MUGLUE);
    primitive(/* str 'moveleft' */ 1467, HMOVE, 1);
    primitive(/* str 'moveright' */ 1468, HMOVE, 0);
    primitive(/* str 'raise' */ 1469, VMOVE, 1);
    primitive(/* str 'lower' */ 1470, VMOVE, 0);
    primitive(/* str 'box' */ 429, MAKEBOX, BOXCODE);
    primitive(/* str 'copy' */ 1471, MAKEBOX, COPYCODE);
    primitive(/* str 'lastbox' */ 1472, MAKEBOX, LASTBOXCODE);
    primitive(/* str 'vsplit' */ 1381, MAKEBOX, VSPLITCODE);
    primitive(/* str 'vtop' */ 1473, MAKEBOX, VTOPCODE);
    primitive(/* str 'vbox' */ 1383, MAKEBOX, VTOPCODE+VMODE);
    primitive(/* str 'hbox' */ 1474, MAKEBOX,
              VTOPCODE+HMODE);
    primitive(/* str 'shipout' */ 1475, LEADERSHIP, /* @d15934@ */ 99);
    primitive(/* str 'leaders' */ 1476, LEADERSHIP, ALEADERS);
    primitive(/* str 'cleaders' */ 1477, LEADERSHIP, CLEADERS);
    primitive(/* str 'xleaders' */ 1478, LEADERSHIP, XLEADERS);
    primitive(/* str 'indent' */ 1494, STARTPAR, 1);
    primitive(/* str 'noindent' */ 1495, STARTPAR, 0);
    primitive(/* str 'quitvmode' */ 1496, STARTPAR, 2);
    primitive(/* str 'unpenalty' */ 1506, REMOVEITEM, PENALTYNODE);
    primitive(/* str 'unkern' */ 1507, REMOVEITEM, KERNNODE);
    primitive(/* str 'unskip' */ 1508, REMOVEITEM, GLUENODE);
    primitive(/* str 'unhbox' */ 1509, UNHBOX, BOXCODE);
    primitive(/* str 'unhcopy' */ 1510, UNHBOX, COPYCODE);
    primitive(/* str 'unvbox' */ 1511, UNVBOX, BOXCODE);
    primitive(/* str 'unvcopy' */ 1512, UNVBOX, COPYCODE);
    primitive(/* str '-' */ 45, DISCRETIONARY, 1);
    primitive(/* str 'discretionary' */ 357, DISCRETIONARY, 0);
    primitive(/* str 'eqno' */ 1544, EQNO, 0);
    primitive(/* str 'leqno' */ 1545, EQNO, 1);
    primitive(/* str 'mathord' */ 1275, MATHCOMP, ORDNOAD);
    primitive(/* str 'mathop' */ 1276, MATHCOMP, OPNOAD);
    primitive(/* str 'mathbin' */ 1277, MATHCOMP, BINNOAD);
    primitive(/* str 'mathrel' */ 1278, MATHCOMP, RELNOAD);
    primitive(/* str 'mathopen' */ 1279, MATHCOMP, OPENNOAD);
    primitive(/* str 'mathclose' */ 1280, MATHCOMP, CLOSENOAD);
    primitive(/* str 'mathpunct' */ 1281, MATHCOMP, PUNCTNOAD);
    primitive(/* str 'mathinner' */ 1282, MATHCOMP, INNERNOAD);
    primitive(/* str 'underline' */ 1284, MATHCOMP, UNDERNOAD);
    primitive(/* str 'overline' */ 1283, MATHCOMP, OVERNOAD);
    primitive(/* str 'displaylimits' */ 1546, LIMITSWITCH, NORMAL);
    primitive(/* str 'limits' */ 1288, LIMITSWITCH, LIMITS);
    primitive(/* str 'nolimits' */ 1289, LIMITSWITCH, NOLIMITS);
    primitive(/* str 'displaystyle' */ 1270, MATHSTYLE, DISPLAYSTYLE);
    primitive(/* str 'textstyle' */ 1271, MATHSTYLE, TEXTSTYLE);
    primitive(/* str 'scriptstyle' */ 1272, MATHSTYLE, SCRIPTSTYLE);
    primitive(/* str 'scriptscriptstyle' */ 1273, MATHSTYLE, SCRIPTSCRIPTSTYLE);
    primitive(/* str 'above' */ 1564, ABOVE, ABOVECODE);
    primitive(/* str 'over' */ 1565, ABOVE, OVERCODE);
    primitive(/* str 'atop' */ 1566, ABOVE, ATOPCODE);
    primitive(/* str 'abovewithdelims' */ 1567, ABOVE,
              DELIMITEDCODE+ABOVECODE);
    primitive(/* str 'overwithdelims' */ 1568, ABOVE,
              DELIMITEDCODE+OVERCODE);
    primitive(/* str 'atopwithdelims' */ 1569, ABOVE,
              DELIMITEDCODE+ATOPCODE);
    primitive(/* str 'left' */ 1285, LEFTRIGHT, LEFTNOAD);
    primitive(/* str 'right' */ 1286, LEFTRIGHT, RIGHTNOAD);
    hash[FROZENRIGHT].v.RH = /* str 'right' */ 1286;
    eqtb[FROZENRIGHT] = eqtb[curval];
    primitive(/* str 'long' */ 1589, PREFIX, 1);
    primitive(/* str 'outer' */ 1590, PREFIX, 2);
    primitive(/* str 'global' */ 1591, PREFIX, 4);
    primitive(/* str 'def' */ 1592, DEF, 0);
    primitive(/* str 'gdef' */ 1593, DEF, 1);
    primitive(/* str 'edef' */ 1594, DEF, 2);
    primitive(/* str 'xdef' */ 1595, DEF, 3);
    primitive(/* str 'let' */ 1612, LET, NORMAL);
    primitive(/* str 'futurelet' */ 1613, LET, /* @d16079@ */ 1);
    if (enctexp) {
        primitive(/* str 'mubyte' */ 1614, LET, /* @d16082@ */ 10);
        primitive(/* str 'noconvert' */ 1615, LET, /* @d16085@ */ 11);
    }
    primitive(/* str 'chardef' */ 1621, SHORTHANDDEF, CHARDEFCODE);
    primitive(/* str 'mathchardef' */ 1622, SHORTHANDDEF, MATHCHARDEFCODE);
    primitive(/* str 'countdef' */ 1623, SHORTHANDDEF, COUNTDEFCODE);
    primitive(/* str 'dimendef' */ 1624, SHORTHANDDEF, DIMENDEFCODE);
    primitive(/* str 'skipdef' */ 1625, SHORTHANDDEF, SKIPDEFCODE);
    primitive(/* str 'muskipdef' */ 1626, SHORTHANDDEF, MUSKIPDEFCODE);
    primitive(/* str 'toksdef' */ 1627, SHORTHANDDEF, TOKSDEFCODE);
    if (mltexp) {
        primitive(/* str 'charsubdef' */ 1628, SHORTHANDDEF, CHARSUBDEFCODE);
    }
    primitive(/* str 'catcode' */ 435, DEFCODE, CATCODEBASE);
    if (enctexp) {
        primitive(/* str 'xordcode' */ 1633, DEFCODE, XORDCODEBASE);
        primitive(/* str 'xchrcode' */ 1634, DEFCODE, XCHRCODEBASE);
        primitive(/* str 'xprncode' */ 1635, DEFCODE, XPRNCODEBASE);
    }
    primitive(/* str 'mathcode' */ 439, DEFCODE, MATHCODEBASE);
    primitive(/* str 'lccode' */ 436, DEFCODE, LCCODEBASE);
    primitive(/* str 'uccode' */ 437, DEFCODE, UCCODEBASE);
    primitive(/* str 'sfcode' */ 438, DEFCODE, SFCODEBASE);
    primitive(/* str 'delcode' */ 538, DEFCODE, DELCODEBASE);
    primitive(/* str 'textfont' */ 432, DEFFAMILY, MATHFONTBASE);
    primitive(/* str 'scriptfont' */ 433, DEFFAMILY,
              MATHFONTBASE+SCRIPTSIZE);
    primitive(/* str 'scriptscriptfont' */ 434, DEFFAMILY,
              MATHFONTBASE+SCRIPTSCRIPTSIZE);
    primitive(/* str 'hyphenation' */ 1355, HYPHDATA, 0);
    primitive(/* str 'patterns' */ 1367, HYPHDATA, 1);
    primitive(/* str 'hyphenchar' */ 1651, ASSIGNFONTINT, 0);
    primitive(/* str 'skewchar' */ 1652, ASSIGNFONTINT, 1);
    primitive(/* str 'lpcode' */ 1653, ASSIGNFONTINT, 2);
    primitive(/* str 'rpcode' */ 1654, ASSIGNFONTINT, 3);
    primitive(/* str 'efcode' */ 1655, ASSIGNFONTINT, 4);
    primitive(/* str 'tagcode' */ 1656, ASSIGNFONTINT, 5);
    primitive(/* str 'knbscode' */ 1657, ASSIGNFONTINT, 7);
    primitive(/* str 'stbscode' */ 1658, ASSIGNFONTINT, 8);
    primitive(/* str 'shbscode' */ 1659, ASSIGNFONTINT, 9);
    primitive(/* str 'knbccode' */ 1660, ASSIGNFONTINT, 10);
    primitive(/* str 'knaccode' */ 1661, ASSIGNFONTINT, 11);
    primitive(/* str 'pdfnoligatures' */ 1662, ASSIGNFONTINT, 6);
    primitive(/* str 'batchmode' */ 274, SETINTERACTION, BATCHMODE);
    primitive(/* str 'nonstopmode' */ 275, SETINTERACTION, NONSTOPMODE);
    primitive(/* str 'scrollmode' */ 276, SETINTERACTION, SCROLLMODE);
    primitive(/* str 'errorstopmode' */ 1670, SETINTERACTION, ERRORSTOPMODE);
    primitive(/* str 'openin' */ 1671, INSTREAM, 1);
    primitive(/* str 'closein' */ 1672, INSTREAM, 0);
    primitive(/* str 'message' */ 1673, MESSAGE, 0);
    primitive(/* str 'errmessage' */ 1674, MESSAGE, 1);
    primitive(/* str 'lowercase' */ 1680, CASESHIFT, LCCODEBASE);
    primitive(/* str 'uppercase' */ 1681, CASESHIFT, UCCODEBASE);
    primitive(/* str 'show' */ 1682, XRAY, SHOWCODE);
    primitive(/* str 'showbox' */ 1683, XRAY, SHOWBOXCODE);
    primitive(/* str 'showthe' */ 1684, XRAY, SHOWTHECODE);
    primitive(/* str 'showlists' */ 1685, XRAY, SHOWLISTS);
    primitive(/* str 'openout' */ 1732, EXTENSION, OPENNODE);
    primitive(/* str 'write' */ 678, EXTENSION, WRITENODE);
    writeloc = curval;
    primitive(/* str 'closeout' */ 1733, EXTENSION, CLOSENODE);
    primitive(/* str 'special' */ 1734, EXTENSION, SPECIALNODE);
    hash[FROZENSPECIAL].v.RH = /* str 'special' */ 1734;
    eqtb[FROZENSPECIAL] = eqtb[curval];
    primitive(/* str 'immediate' */ 1735, EXTENSION, IMMEDIATECODE);
    primitive(/* str 'setlanguage' */ 1736, EXTENSION, SETLANGUAGECODE);
    primitive(/* str 'pdfliteral' */ 1737, EXTENSION, PDFTEXFIRSTEXTENSIONCODE);
    primitive(/* str 'pdfcolorstack' */ 1136, EXTENSION, /* @d16240@ */ 38);
    primitive(/* str 'pdfsetmatrix' */ 1738, EXTENSION, /* @d16243@ */ 39);
    primitive(/* str 'pdfsave' */ 1739, EXTENSION, /* @d16246@ */ 40);
    primitive(/* str 'pdfrestore' */ 1740, EXTENSION, /* @d16249@ */ 41);
    primitive(/* str 'pdfobj' */ 1741, EXTENSION, /* @d16252@ */ 7);
    primitive(/* str 'pdfrefobj' */ 1742, EXTENSION, /* @d16255@ */ 8);
    primitive(/* str 'pdfxform' */ 1743, EXTENSION, /* @d16258@ */ 9);
    primitive(/* str 'pdfrefxform' */ 1744, EXTENSION, /* @d16261@ */ 10);
    primitive(/* str 'pdfximage' */ 1745, EXTENSION, /* @d16264@ */ 11);
    primitive(/* str 'pdfrefximage' */ 1746, EXTENSION, /* @d16267@ */ 12);
    primitive(/* str 'pdfannot' */ 1747, EXTENSION, /* @d16270@ */ 13);
    primitive(/* str 'pdfstartlink' */ 1748, EXTENSION, /* @d16273@ */ 14);
    primitive(/* str 'pdfendlink' */ 1749, EXTENSION, /* @d16276@ */ 15);
    primitive(/* str 'pdfoutline' */ 1750, EXTENSION, /* @d16279@ */ 16);
    primitive(/* str 'pdfdest' */ 1751, EXTENSION, /* @d16282@ */ 17);
    primitive(/* str 'pdfthread' */ 1752, EXTENSION, /* @d16285@ */ 18);
    primitive(/* str 'pdfstartthread' */ 1753, EXTENSION, /* @d16288@ */ 19);
    primitive(/* str 'pdfendthread' */ 1754, EXTENSION, /* @d16291@ */ 20);
    primitive(/* str 'pdfsavepos' */ 1755, EXTENSION, /* @d16294@ */ 21);
    primitive(/* str 'pdfsnaprefpoint' */ 1756, EXTENSION, /* @d16297@ */ 34);
    primitive(/* str 'pdfsnapy' */ 1757, EXTENSION, /* @d16300@ */ 35);
    primitive(/* str 'pdfsnapycomp' */ 1758, EXTENSION, /* @d16303@ */ 36);
    primitive(/* str 'pdfinfo' */ 1759, EXTENSION, /* @d16306@ */ 22);
    primitive(/* str 'pdfcatalog' */ 1760, EXTENSION, /* @d16309@ */ 23);
    primitive(/* str 'pdfnames' */ 1761, EXTENSION, /* @d16312@ */ 24);
    primitive(/* str 'pdfincludechars' */ 1762, EXTENSION, /* @d16315@ */ 26);
    primitive(/* str 'pdffontattr' */ 1763, EXTENSION, /* @d16318@ */ 25);
    primitive(/* str 'pdfmapfile' */ 1764, EXTENSION, /* @d16321@ */ 27);
    primitive(/* str 'pdfmapline' */ 1765, EXTENSION, /* @d16324@ */ 28);
    primitive(/* str 'pdftrailer' */ 1766, EXTENSION, /* @d16327@ */ 29);
    primitive(/* str 'pdftrailerid' */ 1767, EXTENSION, /* @d16330@ */ 30);
    primitive(/* str 'pdfresettimer' */ 1768, EXTENSION, /* @d16333@ */ 31);
    primitive(/* str 'pdfsetrandomseed' */ 1769, EXTENSION, /* @d16336@ */ 33);
    primitive(/* str 'pdffontexpand' */ 1770, EXTENSION, /* @d16339@ */ 32);
    primitive(/* str 'pdfglyphtounicode' */ 1771, EXTENSION, /* @d16342@ */ 37);
    primitive(/* str 'pdfnobuiltintounicode' */ 1772, EXTENSION,
              /* @d16345@ */ 42);
    primitive(/* str 'pdfinterwordspaceon' */ 1773, EXTENSION,
              /* @d16348@ */ 43);
    primitive(/* str 'pdfinterwordspaceoff' */ 1774, EXTENSION,
              /* @d16351@ */ 44);
    primitive(/* str 'pdffakespace' */ 1775, EXTENSION, /* @d16354@ */ 45);
    nonewcontrolsequence = true;
}
#endif /* INITEX */
#ifdef TEXMF_DEBUG
void debughelp(void) {
    debughelp_regmem integer k, l, m, n;
    while (true) {

        ;
        printnl(/* str 'debug # (-1 to exit)' */ 1731);
        fflush(stdout);
        read(stdin, m);
        if (m < 0)
            return;
        else if (m == 0)
            dumpcore();
        else {

            read(stdin, n);
            switch (m) { /* comment:Numbered cases for |debug_help| */
            case 1:
                printword(mem[n]);
                break;
            case 2:
                printint(mem[n].hh.v.LH);
                break;
            case 3:
                printint(mem[n].hh.v.RH);
                break;
            case 4:
                printword(eqtb[n]);
                break;
            case 5: {
                printscaled(fontinfo[n].cint);
                printchar(/* str ' ' */ 32);
                printint(fontinfo[n].qqqq.b0);
                printchar(/* str '' */ 58);
                printint(fontinfo[n].qqqq.b1);
                printchar(/* str '' */ 58);
                printint(fontinfo[n].qqqq.b2);
                printchar(/* str '' */ 58);
                printint(fontinfo[n].qqqq.b3);
            } break;
            case 6:
                printword(savestack[n]);
                break;
            case 7:
                showbox(n);
                break;
            case 8: {
                breadthmax = 10000;
                depththreshold = poolsize - poolptr - 10;
                shownodelist(n);
            } break;
            case 9:
                showtokenlist(n, TEXNULL, 1000);
                break;
            case 10:
                slowprint(n);
                break;
            case 11:
                checkmem(n > 0);
                break;
            case 12:
                searchmem(n);
                break;
            case 13: {
                read(stdin, l);
                printcmdchr(n, l);
            } break;
            case 14: {
                register integer for_end;
                k = 0;
                for_end = n;
                if (k <= for_end)
                    do
                        print(buffer[k]);
                    while (k++ < for_end);
            } break;
            case 15: {
                fontinshortdisplay = FONTBASE;
                shortdisplay(n);
            } break;
            case 16:
                panicking = !panicking;
                break;
            default:
                print(/* str '?' */ 63);
                break;
            }
        }
    }
/* @d16366@ */}
#endif /* TEXMF_DEBUG */
void mainbody(void) {
    mainbody_regmem bounddefault = 0;
    boundname = "mem_bot";
    setupboundvariable(addressof(membot), boundname, bounddefault);
    bounddefault = 250000L;
    boundname = "main_memory";
    setupboundvariable(addressof(mainmemory), boundname, bounddefault);
    bounddefault = 0;
    boundname = "extra_mem_top";
    setupboundvariable(addressof(extramemtop), boundname, bounddefault);
    bounddefault = 0;
    boundname = "extra_mem_bot";
    setupboundvariable(addressof(extramembot), boundname, bounddefault);
    bounddefault = 200000L;
    boundname = "pool_size";
    setupboundvariable(addressof(poolsize), boundname, bounddefault);
    bounddefault = 75000L;
    boundname = "string_vacancies";
    setupboundvariable(addressof(stringvacancies), boundname, bounddefault);
    bounddefault = 5000;
    boundname = "pool_free";
    setupboundvariable(addressof(poolfree), boundname, bounddefault);
    bounddefault = 15000;
    boundname = "max_strings";
    setupboundvariable(addressof(maxstrings), boundname, bounddefault);
    bounddefault = 100;
    boundname = "strings_free";
    setupboundvariable(addressof(stringsfree), boundname, bounddefault);
    bounddefault = 100000L;
    boundname = "font_mem_size";
    setupboundvariable(addressof(fontmemsize), boundname, bounddefault);
    bounddefault = 500;
    boundname = "font_max";
    setupboundvariable(addressof(fontmax), boundname, bounddefault);
    bounddefault = 20000;
    boundname = "trie_size";
    setupboundvariable(addressof(triesize), boundname, bounddefault);
    bounddefault = 659;
    boundname = "hyph_size";
    setupboundvariable(addressof(hyphsize), boundname, bounddefault);
    bounddefault = 3000;
    boundname = "buf_size";
    setupboundvariable(addressof(bufsize), boundname, bounddefault);
    bounddefault = 50;
    boundname = "nest_size";
    setupboundvariable(addressof(nestsize), boundname, bounddefault);
    bounddefault = 15;
    boundname = "max_in_open";
    setupboundvariable(addressof(maxinopen), boundname, bounddefault);
    bounddefault = 60;
    boundname = "param_size";
    setupboundvariable(addressof(paramsize), boundname, bounddefault);
    bounddefault = 4000;
    boundname = "save_size";
    setupboundvariable(addressof(savesize), boundname, bounddefault);
    bounddefault = 300;
    boundname = "stack_size";
    setupboundvariable(addressof(stacksize), boundname, bounddefault);
    bounddefault = 16384;
    boundname = "dvi_buf_size";
    setupboundvariable(addressof(dvibufsize), boundname, bounddefault);
    bounddefault = 79;
    boundname = "error_line";
    setupboundvariable(addressof(errorline), boundname, bounddefault);
    bounddefault = 50;
    boundname = "half_error_line";
    setupboundvariable(addressof(halferrorline), boundname, bounddefault);
    bounddefault = 79;
    boundname = "max_print_line";
    setupboundvariable(addressof(maxprintline), boundname, bounddefault);
    bounddefault = 0;
    boundname = "hash_extra";
    setupboundvariable(addressof(hashextra), boundname, bounddefault);
    bounddefault = 10000;
    boundname = "expand_depth";
    setupboundvariable(addressof(expanddepth), boundname, bounddefault);
    bounddefault = 72;
    boundname = "pk_dpi";
    setupboundvariable(addressof(pkdpi), boundname, bounddefault);
    {
        if (membot < infmembot)
            membot = infmembot;
        else if (membot > supmembot)
            membot = supmembot;
    }
    {
        if (mainmemory < infmainmemory)
            mainmemory = infmainmemory;
        else if (mainmemory > supmainmemory)
            mainmemory = supmainmemory;
    };
#ifdef INITEX
    if (iniversion) {
        extramemtop = 0;
        extramembot = 0;
    }
#endif /* INITEX */
    if (extramembot > supmainmemory)
        extramembot = supmainmemory;
    if (extramemtop > supmainmemory)
        extramemtop = supmainmemory;
    memtop = membot + mainmemory - 1;
    memmin = membot;
    memmax = memtop;
    {
        if (triesize < inftriesize)
            triesize = inftriesize;
        else if (triesize > suptriesize)
            triesize = suptriesize;
    }
    {
        if (hyphsize < infhyphsize)
            hyphsize = infhyphsize;
        else if (hyphsize > suphyphsize)
            hyphsize = suphyphsize;
    }
    {
        if (bufsize < infbufsize)
            bufsize = infbufsize;
        else if (bufsize > supbufsize)
            bufsize = supbufsize;
    }
    {
        if (nestsize < infnestsize)
            nestsize = infnestsize;
        else if (nestsize > supnestsize)
            nestsize = supnestsize;
    }
    {
        if (maxinopen < infmaxinopen)
            maxinopen = infmaxinopen;
        else if (maxinopen > supmaxinopen)
            maxinopen = supmaxinopen;
    }
    {
        if (paramsize < infparamsize)
            paramsize = infparamsize;
        else if (paramsize > supparamsize)
            paramsize = supparamsize;
    }
    {
        if (savesize < infsavesize)
            savesize = infsavesize;
        else if (savesize > supsavesize)
            savesize = supsavesize;
    }
    {
        if (stacksize < infstacksize)
            stacksize = infstacksize;
        else if (stacksize > supstacksize)
            stacksize = supstacksize;
    }
    {
        if (dvibufsize < infdvibufsize)
            dvibufsize = infdvibufsize;
        else if (dvibufsize > supdvibufsize)
            dvibufsize = supdvibufsize;
    }
    {
        if (poolsize < infpoolsize)
            poolsize = infpoolsize;
        else if (poolsize > suppoolsize)
            poolsize = suppoolsize;
    }
    {
        if (stringvacancies < infstringvacancies)
            stringvacancies = infstringvacancies;
        else if (stringvacancies > supstringvacancies)
            stringvacancies = supstringvacancies;
    }
    {
        if (poolfree < infpoolfree)
            poolfree = infpoolfree;
        else if (poolfree > suppoolfree)
            poolfree = suppoolfree;
    }
    {
        if (maxstrings < infmaxstrings)
            maxstrings = infmaxstrings;
        else if (maxstrings > supmaxstrings)
            maxstrings = supmaxstrings;
    }
    {
        if (stringsfree < infstringsfree)
            stringsfree = infstringsfree;
        else if (stringsfree > supstringsfree)
            stringsfree = supstringsfree;
    }
    {
        if (fontmemsize < inffontmemsize)
            fontmemsize = inffontmemsize;
        else if (fontmemsize > supfontmemsize)
            fontmemsize = supfontmemsize;
    }
    {
        if (fontmax < inffontmax)
            fontmax = inffontmax;
        else if (fontmax > supfontmax)
            fontmax = supfontmax;
    }
    {
        if (hashextra < infhashextra)
            hashextra = infhashextra;
        else if (hashextra > suphashextra)
            hashextra = suphashextra;
    }
    {
        if (objtabsize < infobjtabsize)
            objtabsize = infobjtabsize;
        else if (objtabsize > supobjtabsize)
            objtabsize = supobjtabsize;
    }
    {
        if (pdfmemsize < infpdfmemsize)
            pdfmemsize = infpdfmemsize;
        else if (pdfmemsize > suppdfmemsize)
            pdfmemsize = suppdfmemsize;
    }
    {
        if (destnamessize < infdestnamessize)
            destnamessize = infdestnamessize;
        else if (destnamessize > supdestnamessize)
            destnamessize = supdestnamessize;
    }
    {
        if (pkdpi < infpkdpi)
            pkdpi = infpkdpi;
        else if (pkdpi > suppkdpi)
            pkdpi = suppkdpi;
    }
    if (errorline > SSUPERRORLINE)
        errorline = SSUPERRORLINE;
    buffer = xmallocarray(ASCIIcode, bufsize);
    nest = xmallocarray(liststaterecord, nestsize);
    savestack = xmallocarray(memoryword, savesize);
    inputstack = xmallocarray(instaterecord, stacksize);
    inputfile = xmallocarray(alphafile, maxinopen);
    linestack = xmallocarray(integer, maxinopen);
    eofseen = xmallocarray(boolean, maxinopen);
    grpstack = xmallocarray(savepointer, maxinopen);
    ifstack = xmallocarray(halfword, maxinopen);
    sourcefilenamestack = xmallocarray(strnumber, maxinopen);
    fullsourcefilenamestack = xmallocarray(strnumber, maxinopen);
    paramstack = xmallocarray(halfword, paramsize);
    dvibuf = xmallocarray(eightbits, dvibufsize);
    hyphword = xmallocarray(strnumber, hyphsize);
    hyphlist = xmallocarray(halfword, hyphsize);
    hyphlink = xmallocarray(hyphpointer, hyphsize);
    objtab = xmallocarray(objentry, infobjtabsize);
    pdfmem = xmallocarray(integer, infpdfmemsize);
    destnames = xmallocarray(destnameentry, infdestnamessize);
    pdfopbuf = xmallocarray(eightbits, pdfopbufsize);
    pdfosbuf = xmallocarray(eightbits, infpdfosbufsize);
    pdfosobjnum = xmallocarray(integer, pdfosmaxobjs);
    pdfosobjoff = xmallocarray(integer, pdfosmaxobjs);
    ;
#ifdef INITEX
    if (iniversion) {
        yzmem = xmallocarray(memoryword, memtop - membot + 1);
        zmem = yzmem - membot;
        eqtbtop = EQTBSIZE + hashextra;
        if (hashextra == 0)
            hashtop = UNDEFINEDCONTROLSEQUENCE;
        else
            hashtop = eqtbtop;
        yhash = xmallocarray(twohalves, 1 + hashtop - hashoffset);
        hash = yhash - hashoffset;
        hash[HASHBASE].v.LH = 0;
        hash[HASHBASE].v.RH = 0;
        {
            register integer for_end;
            hashused = /* @d16373@ */ 515;
            for_end = hashtop;
            if (hashused <= for_end)
                do
                    hash[hashused] = hash[HASHBASE];
                while (hashused++ < for_end);
        }
        zeqtb = xmallocarray(memoryword, eqtbtop);
        eqtb = zeqtb;
        strstart = xmallocarray(poolpointer, maxstrings);
        strpool = xmallocarray(packedASCIIcode, poolsize);
        fontinfo = xmallocarray(fmemoryword, fontmemsize);
    }
#endif /* INITEX */
    history = FATALERRORSTOP;
    if (readyalready == 314159L)
        goto labmainbody1start_of_TEX;
    /* comment:Check the ``constant'' values for consistency */ bad = 0;
    if ((halferrorline < 30) || (halferrorline > errorline - 15))
        bad = 1;
    if (maxprintline < 60)
        bad = 2;
    if (dvibufsize % 8 != 0)
        bad = 3;
    if (membot + 1100 > memtop)
        bad = 4;
    if (HASHPRIME > HASHSIZE)
        bad = 5;
    if (maxinopen >= 128)
        bad = 6;
    if (memtop < 267)
        bad = 7;
    ;
#ifdef INITEX
    if ((memmin != membot) || (memmax != memtop))
        bad = 10;
#endif /* INITEX */
    if ((memmin > membot) || (memmax < memtop))
        bad = 10;
    if ((MINQUARTERWORD > 0) || (MAXQUARTERWORD < 127))
        bad = 11;
    if ((TEXNULL > 0) || (2147483647L < 32767))
        bad = 12;
    if ((MINQUARTERWORD < TEXNULL) || (MAXQUARTERWORD > 2147483647L))
        bad = 13;
    if ((membot - supmainmemory < TEXNULL) ||
        (memtop + supmainmemory >= 2147483647L))
        bad = 14;
    if ((MAXFONTMAX < TEXNULL) || (MAXFONTMAX > 2147483647L))
        bad = 15;
    if (fontmax > /* @d16386@ */ MAXFONTMAX)
        bad = 16;
    if ((savesize > 2147483647L) || (maxstrings > 2147483647L))
        bad = 17;
    if (bufsize > 2147483647L)
        bad = 18;
    if (MAXQUARTERWORD+MINQUARTERWORD < 255)
        bad = 19;
    if (/* @d16390@ */ 34278L + hashextra > 2147483647L)
        bad = 21;
    if ((hashoffset < 0) || (hashoffset > HASHBASE))
        bad = 42;
    if (formatdefaultlength > maxint)
        bad = 31;
    if (2 * 2147483647L < memtop - memmin)
        bad = 41;
    if (bad > 0) {
        fprintf(stdout, "%s%s%ld\n",
                "Ouch---my internal constants have been clobbered!", "---case ",
                (long)bad);
        goto labmainbody9999final_end;
    }
    initialize();
    ;
#ifdef INITEX
    if (iniversion) {
        if (!getstringsstarted())
            goto labmainbody9999final_end;
        initprim();
        initstrptr = strptr;
        initpoolptr = poolptr;
        dateandtime(eqtb[INTBASE + TIMECODE].cint, eqtb[INTBASE + DAYCODE].cint,
                    eqtb[INTBASE + MONTHCODE].cint,
                    eqtb[INTBASE + YEARCODE].cint);
    }
#endif /* INITEX */
    readyalready = 314159L;
labmainbody1start_of_TEX: /* comment:Initialize the output routines */
    selector = TERMONLY;
    tally = 0;
    termoffset = 0;
    fileoffset = 0;
    if (srcspecialsp || filelineerrorstylep || parsefirstlinep)
        fprintf(stdout, "%s%s%s", "This is pdfTeX, Version 3.14159265", "-2.6",
                "-1.40.20");
    else
        fprintf(stdout, "%s%s%s", "This is pdfTeX, Version 3.14159265", "-2.6",
                "-1.40.20");
    Fputs(stdout, versionstring);
    if (formatident == 0)
        fprintf(stdout, "%s%s%c\n", " (preloaded format=", dumpname, ')');
    else {

        slowprint(formatident);
        println();
    }
    if (shellenabledp) {
        putc(' ', stdout);
        if (restrictedshell) {
            Fputs(stdout, "restricted ");
        }
        fprintf(stdout, "%s\n", "\\write18 enabled.");
    }
    if (srcspecialsp) {
        fprintf(stdout, "%s\n", " Source specials enabled.");
    }
    if (translatefilename) {
        Fputs(stdout, " (");
        fputs(translatefilename, stdout);
        {
            putc(')', stdout);
            putc('\n', stdout);
        }
    }
    fflush(stdout);
    jobname = 0;
    nameinprogress = false;
    logopened = false;
    outputfilename = 0;
    /* comment:Get the first line of input and prepare to start */ {

        /* comment:Initialize the input routines */ {

            inputptr = 0;
            maxinstack = 0;
            sourcefilenamestack[0] = 0;
            fullsourcefilenamestack[0] = 0;
            inopen = 0;
            openparens = 0;
            maxbufstack = 0;
            grpstack[0] = 0;
            ifstack[0] = TEXNULL;
            paramptr = 0;
            maxparamstack = 0;
            first = bufsize;
            do {
                buffer[first] = 0;
                decr(first);
            } while (!(first == 0));
            scannerstatus = NORMAL;
            warningindex = TEXNULL;
            first = 1;
            curinput.statefield = NEWLINE;
            curinput.startfield = 1;
            curinput.indexfield = 0;
            line = 0;
            curinput.namefield = 0;
            forceeof = false;
            alignstate = 1000000L;
            if (!initterminal())
                goto labmainbody9999final_end;
            curinput.limitfield = last;
            first = last + 1;
        }
        /* comment:Enable \eTeX, if requested */;
#ifdef INITEX
        if ((etexp || (buffer[curinput.locfield] == /* str '' */ 42)) &&
            (formatident == /* str ' (INITEX)' */ 1698)) {
            nonewcontrolsequence = false;
            /* comment:Generate all \eTeX\ primitives */ primitive(
                /* str 'lastnodetype' */ 1968, LASTITEM, LASTNODETYPECODE);
            primitive(/* str 'eTeXversion' */ 1969, LASTITEM, ETEXVERSIONCODE);
            primitive(/* str 'eTeXrevision' */ 872, CONVERT, ETEXREVISIONCODE);
            primitive(/* str 'everyeof' */ 1971, ASSIGNTOKS, EVERYEOFLOC);
            primitive(/* str 'tracingassigns' */ 1972, ASSIGNINT,
                      INTBASE+TRACINGASSIGNSCODE);
            primitive(/* str 'tracinggroups' */ 1973, ASSIGNINT,
                      INTBASE+TRACINGGROUPSCODE);
            primitive(/* str 'tracingifs' */ 1974, ASSIGNINT,
                      INTBASE+TRACINGIFSCODE);
            primitive(/* str 'tracingscantokens' */ 1975, ASSIGNINT,
                      INTBASE+TRACINGSCANTOKENSCODE);
            primitive(/* str 'tracingnesting' */ 1976, ASSIGNINT,
                      INTBASE+TRACINGNESTINGCODE);
            primitive(/* str 'predisplaydirection' */ 1977, ASSIGNINT,
                      INTBASE+PREDISPLAYDIRECTIONCODE);
            primitive(/* str 'lastlinefit' */ 1978, ASSIGNINT,
                      INTBASE+LASTLINEFITCODE);
            primitive(/* str 'savingvdiscards' */ 1979, ASSIGNINT,
                      INTBASE+SAVINGVDISCARDSCODE);
            primitive(/* str 'savinghyphcodes' */ 1980, ASSIGNINT,
                      INTBASE+SAVINGHYPHCODESCODE);
            primitive(/* str 'currentgrouplevel' */ 1995, LASTITEM,
                      CURRENTGROUPLEVELCODE);
            primitive(/* str 'currentgrouptype' */ 1996, LASTITEM,
                      CURRENTGROUPTYPECODE);
            primitive(/* str 'currentiflevel' */ 1997, LASTITEM,
                      CURRENTIFLEVELCODE);
            primitive(/* str 'currentiftype' */ 1998, LASTITEM,
                      CURRENTIFTYPECODE);
            primitive(/* str 'currentifbranch' */ 1999, LASTITEM,
                      CURRENTIFBRANCHCODE);
            primitive(/* str 'fontcharwd' */ 2000, LASTITEM, FONTCHARWDCODE);
            primitive(/* str 'fontcharht' */ 2001, LASTITEM, FONTCHARHTCODE);
            primitive(/* str 'fontchardp' */ 2002, LASTITEM, FONTCHARDPCODE);
            primitive(/* str 'fontcharic' */ 2003, LASTITEM, FONTCHARICCODE);
            primitive(/* str 'parshapelength' */ 2004, LASTITEM,
                      PARSHAPELENGTHCODE);
            primitive(/* str 'parshapeindent' */ 2005, LASTITEM,
                      PARSHAPEINDENTCODE);
            primitive(/* str 'parshapedimen' */ 2006, LASTITEM,
                      PARSHAPEDIMENCODE);
            primitive(/* str 'showgroups' */ 2007, XRAY, SHOWGROUPS);
            primitive(/* str 'showtokens' */ 2009, XRAY, SHOWTOKENS);
            primitive(/* str 'unexpanded' */ 2010, THE, 1);
            primitive(/* str 'detokenize' */ 2011, THE, SHOWTOKENS);
            primitive(/* str 'showifs' */ 2012, XRAY, SHOWIFS);
            primitive(/* str 'interactionmode' */ 2016, SETPAGEINT, 2);
            primitive(/* str 'middle' */ 1287, LEFTRIGHT, 1);
            primitive(/* str 'TeXXeTstate' */ 2020, ASSIGNINT,
                      ETEXSTATEBASE+TEXXETCODE);
            primitive(/* str 'beginL' */ 2021, VALIGN, BEGINLCODE);
            primitive(/* str 'endL' */ 2022, VALIGN, ENDLCODE);
            primitive(/* str 'beginR' */ 2023, VALIGN, BEGINRCODE);
            primitive(/* str 'endR' */ 2024, VALIGN, ENDRCODE);
            primitive(/* str 'scantokens' */ 2033, INPUT, 2);
            primitive(/* str 'readline' */ 2035, READTOCS, 1);
            primitive(/* str 'unless' */ 928, EXPANDAFTER, 1);
            primitive(/* str 'ifdefined' */ 2036, IFTEST, IFDEFCODE);
            primitive(/* str 'ifcsname' */ 2037, IFTEST, IFCSCODE);
            primitive(/* str 'iffontchar' */ 2038, IFTEST, IFFONTCHARCODE);
            primitive(/* str 'ifincsname' */ 2039, IFTEST, IFINCSNAMECODE);
            primitive(/* str 'ifpdfabsnum' */ 2040, IFTEST, IFPDFABSNUMCODE);
            primitive(/* str 'ifpdfabsdim' */ 2041, IFTEST, IFPDFABSDIMCODE);
            primitive(/* str 'protected' */ 1603, PREFIX, 8);
            primitive(/* str 'numexpr' */ 2047, LASTITEM,
                      /* @d16560@ */ /* @d16561@ */ /* @d16562@ */ 39);
            primitive(/* str 'dimexpr' */ 2048, LASTITEM,
                      /* @d16565@ */ /* @d16566@ */ /* @d16567@ */ 40);
            primitive(/* str 'glueexpr' */ 2049, LASTITEM,
                      /* @d16570@ */ /* @d16571@ */ /* @d16572@ */ 41);
            primitive(/* str 'muexpr' */ 2050, LASTITEM,
                      /* @d16575@ */ /* @d16576@ */ /* @d16577@ */ 42);
            primitive(/* str 'gluestretchorder' */ 2054, LASTITEM,
                      GLUESTRETCHORDERCODE);
            primitive(/* str 'glueshrinkorder' */ 2055, LASTITEM,
                      GLUESHRINKORDERCODE);
            primitive(/* str 'gluestretch' */ 2056, LASTITEM, GLUESTRETCHCODE);
            primitive(/* str 'glueshrink' */ 2057, LASTITEM, GLUESHRINKCODE);
            primitive(/* str 'mutoglue' */ 2058, LASTITEM, MUTOGLUECODE);
            primitive(/* str 'gluetomu' */ 2059, LASTITEM, GLUETOMUCODE);
            primitive(/* str 'marks' */ 2060, MARK, 5);
            primitive(/* str 'topmarks' */ 2061, TOPBOTMARK, /* @d16600@ */ 5);
            primitive(/* str 'firstmarks' */ 2062, TOPBOTMARK,
                      /* @d16603@ */ 6);
            primitive(/* str 'botmarks' */ 2063, TOPBOTMARK, /* @d16606@ */ 7);
            primitive(/* str 'splitfirstmarks' */ 2064, TOPBOTMARK,
                      /* @d16609@ */ 8);
            primitive(/* str 'splitbotmarks' */ 2065, TOPBOTMARK,
                      /* @d16612@ */ 9);
            primitive(/* str 'pagediscards' */ 2069, UNVBOX, LASTBOXCODE);
            primitive(/* str 'splitdiscards' */ 2070, UNVBOX, VSPLITCODE);
            primitive(/* str 'interlinepenalties' */ 2071, SETSHAPE,
                      INTERLINEPENALTIESLOC);
            primitive(/* str 'clubpenalties' */ 2072, SETSHAPE,
                      CLUBPENALTIESLOC);
            primitive(/* str 'widowpenalties' */ 2073, SETSHAPE,
                      WIDOWPENALTIESLOC);
            primitive(/* str 'displaywidowpenalties' */ 2074, SETSHAPE,
                      DISPLAYWIDOWPENALTIESLOC);
            if ((buffer[curinput.locfield] == /* str '' */ 42))
                incr(curinput.locfield);
            eTeXmode = 1;
            /* comment:Initialize variables for \eTeX\ extended mode */
            maxregnum = 32767;
            maxreghelpline =
                /* str 'A register number must be between 0 and 32767.' */ 2066;
        }
#endif /* INITEX */
        if (!nonewcontrolsequence)
            nonewcontrolsequence = true;
        else if ((formatident == 0) ||
                 (buffer[curinput.locfield] == /* str '&' */ 38) || dumpline) {
            if (formatident != 0)
                initialize();
            if (!openfmtfile())
                goto labmainbody9999final_end;
            if (!loadfmtfile()) {
                wclose(fmtfile);
                goto labmainbody9999final_end;
            }
            wclose(fmtfile);
            eqtb = zeqtb;
            while ((curinput.locfield < curinput.limitfield) &&
                   (buffer[curinput.locfield] == /* str ' ' */ 32))
                incr(curinput.locfield);
        }
        if ((pdfoutputoption != 0))
            eqtb[INTBASE + PDFOUTPUTCODE].cint = pdfoutputvalue;
        if ((pdfdraftmodeoption != 0))
            eqtb[INTBASE + PDFDRAFTMODECODE].cint = pdfdraftmodevalue;
        pdfinitmapfile("pdftex.map");
        if ((eTeXmode == 1))
            fprintf(stdout, "%s\n", "entering extended mode");
        if ((eqtb[INTBASE + ENDLINECHARCODE].cint < 0) ||
            (eqtb[INTBASE + ENDLINECHARCODE].cint > 255))
            decr(curinput.limitfield);
        else
            buffer[curinput.limitfield] = eqtb[INTBASE + ENDLINECHARCODE].cint;
        if (mltexenabledp) {
            fprintf(stdout, "%s\n", "MLTeX v2.2 enabled");
        }
        if (enctexenabledp) {
            Fputs(stdout, " encTeX v. Jun. 2004");
            fprintf(stdout, "%s\n", ", reencoding enabled.");
            if (translatefilename) {
                fprintf(
                    stdout, "%s\n",
                    " (\\xordcode, \\xchrcode, \\xprncode overridden by TCX)");
            }
        }
        dateandtime(eqtb[INTBASE + TIMECODE].cint, eqtb[INTBASE + DAYCODE].cint,
                    eqtb[INTBASE + MONTHCODE].cint,
                    eqtb[INTBASE + YEARCODE].cint);
        ;
#ifdef INITEX
        if (trienotready) {
            trietrl = xmallocarray(triepointer, triesize);
            trietro = xmallocarray(triepointer, triesize);
            trietrc = xmallocarray(quarterword, triesize);
            triec = xmallocarray(packedASCIIcode, triesize);
            trieo = xmallocarray(trieopcode, triesize);
            triel = xmallocarray(triepointer, triesize);
            trier = xmallocarray(triepointer, triesize);
            triehash = xmallocarray(triepointer, triesize);
            trietaken = xmallocarray(boolean, triesize);
            triel[0] = 0;
            triec[0] = 0;
            trieptr = 0;
            trier[0] = 0;
            hyphstart = 0;
            fontcheck = xmallocarray(fourquarters, fontmax);
            fontsize = xmallocarray(scaled, fontmax);
            fontdsize = xmallocarray(scaled, fontmax);
            fontparams = xmallocarray(fontindex, fontmax);
            fontname = xmallocarray(strnumber, fontmax);
            fontarea = xmallocarray(strnumber, fontmax);
            fontbc = xmallocarray(eightbits, fontmax);
            fontec = xmallocarray(eightbits, fontmax);
            fontglue = xmallocarray(halfword, fontmax);
            hyphenchar = xmallocarray(integer, fontmax);
            skewchar = xmallocarray(integer, fontmax);
            bcharlabel = xmallocarray(fontindex, fontmax);
            fontbchar = xmallocarray(ninebits, fontmax);
            fontfalsebchar = xmallocarray(ninebits, fontmax);
            charbase = xmallocarray(integer, fontmax);
            widthbase = xmallocarray(integer, fontmax);
            heightbase = xmallocarray(integer, fontmax);
            depthbase = xmallocarray(integer, fontmax);
            italicbase = xmallocarray(integer, fontmax);
            ligkernbase = xmallocarray(integer, fontmax);
            kernbase = xmallocarray(integer, fontmax);
            extenbase = xmallocarray(integer, fontmax);
            parambase = xmallocarray(integer, fontmax);
            pdfcharused = xmallocarray(charusedarray, fontmax);
            pdffontsize = xmallocarray(scaled, fontmax);
            pdffontnum = xmallocarray(integer, fontmax);
            pdffontmap = xmallocarray(fmentryptr, fontmax);
            pdffonttype = xmallocarray(eightbits, fontmax);
            pdffontattr = xmallocarray(strnumber, fontmax);
            pdffontblink = xmallocarray(internalfontnumber, fontmax);
            pdffontelink = xmallocarray(internalfontnumber, fontmax);
            pdffontstretch = xmallocarray(integer, fontmax);
            pdffontshrink = xmallocarray(integer, fontmax);
            pdffontstep = xmallocarray(integer, fontmax);
            pdffontexpandratio = xmallocarray(integer, fontmax);
            pdffontautoexpand = xmallocarray(boolean, fontmax);
            pdffontlpbase = xmallocarray(integer, fontmax);
            pdffontrpbase = xmallocarray(integer, fontmax);
            pdffontefbase = xmallocarray(integer, fontmax);
            pdffontknbsbase = xmallocarray(integer, fontmax);
            pdffontstbsbase = xmallocarray(integer, fontmax);
            pdffontshbsbase = xmallocarray(integer, fontmax);
            pdffontknbcbase = xmallocarray(integer, fontmax);
            pdffontknacbase = xmallocarray(integer, fontmax);
            vfpacketbase = xmallocarray(integer, fontmax);
            vfdefaultfont = xmallocarray(internalfontnumber, fontmax);
            vflocalfontnum = xmallocarray(internalfontnumber, fontmax);
            vfefnts = xmallocarray(integer, fontmax);
            vfifnts = xmallocarray(internalfontnumber, fontmax);
            pdffontnobuiltintounicode = xmallocarray(boolean, fontmax);
            {
                register integer for_end;
                fontk = FONTBASE;
                for_end = fontmax;
                if (fontk <= for_end)
                    do {
                        {
                            register integer for_end;
                            k = 0;
                            for_end = 31;
                            if (k <= for_end)
                                do
                                    pdfcharused[fontk][k] = 0;
                                while (k++ < for_end);
                        }
                        pdffontsize[fontk] = 0;
                        pdffontnum[fontk] = 0;
                        pdffontmap[fontk] = 0;
                        pdffonttype[fontk] = NEWFONTTYPE;
                        pdffontattr[fontk] = /* str '' */ 345;
                        pdffontblink[fontk] = FONTBASE;
                        pdffontelink[fontk] = FONTBASE;
                        pdffontstretch[fontk] = FONTBASE;
                        pdffontshrink[fontk] = FONTBASE;
                        pdffontstep[fontk] = 0;
                        pdffontexpandratio[fontk] = 0;
                        pdffontautoexpand[fontk] = false;
                        pdffontlpbase[fontk] = 0;
                        pdffontrpbase[fontk] = 0;
                        pdffontefbase[fontk] = 0;
                        pdffontknbsbase[fontk] = 0;
                        pdffontstbsbase[fontk] = 0;
                        pdffontshbsbase[fontk] = 0;
                        pdffontknbcbase[fontk] = 0;
                        pdffontknacbase[fontk] = 0;
                        pdffontnobuiltintounicode[fontk] = false;
                    } while (fontk++ < for_end);
            }
            fontptr = FONTBASE;
            fmemptr = 7;
            makepdftexbanner();
            fontname[FONTBASE] = /* str 'nullfont' */ 956;
            fontarea[FONTBASE] = /* str '' */ 345;
            hyphenchar[FONTBASE] = /* str '-' */ 45;
            skewchar[FONTBASE] = -1;
            bcharlabel[FONTBASE] = NONADDRESS;
            fontbchar[FONTBASE] = 256;
            fontfalsebchar[FONTBASE] = 256;
            fontbc[FONTBASE] = 1;
            fontec[FONTBASE] = 0;
            fontsize[FONTBASE] = 0;
            fontdsize[FONTBASE] = 0;
            charbase[FONTBASE] = 0;
            widthbase[FONTBASE] = 0;
            heightbase[FONTBASE] = 0;
            depthbase[FONTBASE] = 0;
            italicbase[FONTBASE] = 0;
            ligkernbase[FONTBASE] = 0;
            kernbase[FONTBASE] = 0;
            extenbase[FONTBASE] = 0;
            fontglue[FONTBASE] = TEXNULL;
            fontparams[FONTBASE] = 7;
            parambase[FONTBASE] = -1;
            {
                register integer for_end;
                fontk = 0;
                for_end = 6;
                if (fontk <= for_end)
                    do
                        fontinfo[fontk].cint = 0;
                    while (fontk++ < for_end);
            }
        }
#endif /* INITEX */
        fontused = xmallocarray(boolean, fontmax);
        {
            register integer for_end;
            fontk = FONTBASE;
            for_end = fontmax;
            if (fontk <= for_end)
                do
                    fontused[fontk] = false;
                while (fontk++ < for_end);
        }
        randomseed = (microseconds * 1000) + (epochseconds % 1000000L);
        initrandoms(randomseed);
        /* comment:Compute the magic offset */ magicoffset =
            strstart[MATHSPACING] - 9 * ORDNOAD;
        /* comment:Initialize the print |selector| based on |interact */
        if (interaction == BATCHMODE)
            selector = NOPRINT;
        else
            selector = TERMONLY;
        if ((curinput.locfield < curinput.limitfield) &&
            (eqtb[CATCODEBASE + buffer[curinput.locfield]].hh.v.RH != ESCAPE))
            startinput();
    }
    history = SPOTLESS;
    maincontrol();
    finalcleanup();
    closefilesandterminate();
labmainbody9999final_end : {

    fflush(stdout);
    readyalready = 0;
    if ((history != SPOTLESS) && (history != WARNINGISSUED))
        uexit(1);
    else
        uexit(0);
}
}
