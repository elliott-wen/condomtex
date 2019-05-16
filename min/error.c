#define EXTERN extern
#include "pdftexd.h"
/* comment:Error handling procedures */ 
void jumpout(void) {
    jumpout_regmem closefilesandterminate();
    {
        fflush(stdout);
        readyalready = 0;
        if ((history != SPOTLESS) && (history != WARNINGISSUED))
            uexit(1);
        else
            uexit(0);
    }
}
void error(void) {
    error_regmem ASCIIcode c;
    integer s1, s2, s3, s4;
    if (history < ERRORMESSAGEISSUED)
        history = ERRORMESSAGEISSUED;
    printchar(/* str '.' */ 46);
    showcontext();
    if ((haltonerrorp)) {
        history = FATALERRORSTOP;
        jumpout();
    }
    if (interaction ==
        ERRORSTOPMODE) /* comment:Get user's advice and |return| */
        while (true) {

        laberror22continue:
            clearforerrorprompt();
            {
                ;
                print(/* str '? ' */ 266);
                terminput();
            }
            if (last == first)
                return;
            c = buffer[first];
            if (c >= /* str 'a' */ 97)
                c = /* str 'A' */ /* str 'a' */ c - 32;
            /* comment:Interpret code |c| and |return| if done */ switch (
                c) { /* str '0' */
            case 48:
            /* str '1' */ case 49:
            /* str '2' */ case 50:
            /* str '3' */ case 51:
            /* str '4' */ case 52:
            /* str '5' */ case 53:
            /* str '6' */ case 54:
            /* str '7' */ case 55:
            /* str '8' */ case 56:
            /* str '9' */ case 57:
                if (deletionsallowed) /* comment:Delete \(c)|c-"0"| tokens and
                                         |goto continue| */
                {
                    s1 = curtok;
                    s2 = curcmd;
                    s3 = curchr;
                    s4 = alignstate;
                    alignstate = 1000000L;
                    OKtointerrupt = false;
                    if ((last > first + 1) &&
                        (buffer[first + 1] >= /* str '0' */ 48) &&
                        (buffer[first + 1] <= /* str '9' */ 57))
                        c = c * 10 + buffer[first + 1] /* str '0' */ - 48 * 11;
                    else
                        c = /* str '0' */ c - 48;
                    while (c > 0) {

                        gettoken();
                        decr(c);
                    }
                    curtok = s1;
                    curcmd = s2;
                    curchr = s3;
                    alignstate = s4;
                    OKtointerrupt = true;
                    {
                        helpptr = 2;
                        helpline[1] = /* str 'I have just deleted some text, as
                                         you asked.' */
                            279;
                        helpline[0] = /* str 'You can now delete more, or
                                         insert, or whatever.' */
                            280;
                    }
                    showcontext();
                    goto laberror22continue;
                }
                break;
                ;
#ifdef TEXMF_DEBUG
            /* str 'D' */ case 68 : {
                debughelp();
                goto laberror22continue;
            } break;
#endif /* TEXMF_DEBUG */
            /* str 'E' */ case 69:
                if (baseptr > 0) {
                    editnamestart = strstart[inputstack[baseptr].namefield];
                    editnamelength =
                        strstart[inputstack[baseptr].namefield + 1] -
                        strstart[inputstack[baseptr].namefield];
                    editline = line;
                    jumpout();
                }
                break;
            /* str 'H' */ case 72:
                /* comment:Print the help information and |goto continue| */ {

                    if (useerrhelp) {
                        giveerrhelp();
                        useerrhelp = false;
                    } else {

                        if (helpptr == 0) {
                            helpptr = 2;
                            helpline[1] = /* str 'Sorry, I don't know how to
                                             help in this situation' */
                                281;
                            helpline[0] =
                                /* str 'Maybe you should try asking a human?' */
                                282;
                        }
                        do {
                            decr(helpptr);
                            print(helpline[helpptr]);
                            println();
                        } while (!(helpptr == 0));
                    }
                    {
                        helpptr = 4;
                        helpline[3] = /* str 'Sorry, I already gave what help I
                                         could...' */
                            283;
                        helpline[2] =
                            /* str 'Maybe you should try asking a human?' */
                            282;
                        helpline[1] = /* str 'An error might have occurred
                                         before I noticed any' */
                            284;
                        helpline[0] = /* str '``If all else fails, read the
                                         instructions.''' */
                            285;
                    }
                    goto laberror22continue;
                }
                break;
            /* str 'I' */ case 73:
                /* comment:Introduce new material from the terminal and |retu */
                {

                    beginfilereading();
                    if (last > first + 1) {
                        curinput.locfield = first + 1;
                        buffer[first] = /* str ' ' */ 32;
                    } else {

                        {
                            ;
                            print(/* str 'insert>' */ 278);
                            terminput();
                        }
                        curinput.locfield = first;
                    }
                    first = last;
                    curinput.limitfield = last - 1;
                    return;
                }
                break;
            /* str 'Q' */ case 81:
            /* str 'R' */ case 82:
            /* str 'S' */ case 83:
                /* comment:Change the interaction level and |return| */ {

                    errorcount = 0;
                    interaction = BATCHMODE + /* str 'Q' */ c - 81;
                    print(/* str 'OK, entering ' */ 273);
                    switch (c) { /* str 'Q' */
                    case 81: {
                        printesc(/* str 'batchmode' */ 274);
                        decr(selector);
                    } break;
                    /* str 'R' */ case 82:
                        printesc(/* str 'nonstopmode' */ 275);
                        break;
                    /* str 'S' */ case 83:
                        printesc(/* str 'scrollmode' */ 276);
                        break;
                    }
                    print(/* str '...' */ 277);
                    println();
                    fflush(stdout);
                    return;
                }
                break;
            /* str 'X' */ case 88 : {
                interaction = SCROLLMODE;
                jumpout();
            } break;
            default:;
                break;
            }
            /* comment:Print the menu of available options */ {

                print(/* str 'Type <return> to proceed, S to scroll future erro'
                       */
                      267);
                printnl(/* str 'R to run without stopping, Q to run quietly,' */
                        268);
                printnl(/* str 'I to insert something, ' */ 269);
                if (baseptr > 0)
                    print(/* str 'E to edit your file,' */ 270);
                if (deletionsallowed)
                    printnl(/* str '1 or ... or 9 to ignore the next 1 to 9
                               tokens of' */
                            271);
                printnl(/* str 'H for help, X to quit.' */ 272);
            }
        }
    incr(errorcount);
    if (errorcount == 100) {
        printnl(/* str '(That makes 100 errors; please try again.)' */ 265);
        history = FATALERRORSTOP;
        jumpout();
    }
    /* comment:Put help message on the transcript file */ if (interaction >
                                                              BATCHMODE)
        decr(selector);
    if (useerrhelp) {
        println();
        giveerrhelp();
    } else
        while (helpptr > 0) {

            decr(helpptr);
            printnl(helpline[helpptr]);
        }
    println();
    if (interaction > BATCHMODE)
        incr(selector);
    println();
}
void zfatalerror(strnumber s) {
    fatalerror_regmem normalizeselector();
    {
        if (interaction == ERRORSTOPMODE)
            ;
        if (filelineerrorstylep)
            printfileline();
        else
            printnl(/* str '! ' */ 264);
        print(/* str 'Emergency stop' */ 287);
    }
    {
        helpptr = 1;
        helpline[0] = s;
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
void zoverflow(strnumber s, integer n) {
    overflow_regmem normalizeselector();
    {
        if (interaction == ERRORSTOPMODE)
            ;
        if (filelineerrorstylep)
            printfileline();
        else
            printnl(/* str '! ' */ 264);
        print(/* str 'TeX capacity exceeded, sorry [' */ 288);
    }
    print(s);
    printchar(/* str '=' */ 61);
    printint(n);
    printchar(/* str ']' */ 93);
    {
        helpptr = 2;
        helpline[1] =
            /* str 'If you really absolutely need more capacity,' */ 289;
        helpline[0] = /* str 'you can ask a wizard to enlarge me.' */ 290;
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
void zconfusion(strnumber s) {
    confusion_regmem normalizeselector();
    if (history < ERRORMESSAGEISSUED) {
        {
            if (interaction == ERRORSTOPMODE)
                ;
            if (filelineerrorstylep)
                printfileline();
            else
                printnl(/* str '! ' */ 264);
            print(/* str 'This can't happen (' */ 291);
        }
        print(s);
        printchar(/* str ')' */ 41);
        {
            helpptr = 1;
            helpline[0] =
                /* str 'I'm broken. Please show this to someone who can f' */
                292;
        }
    } else {

        {
            if (interaction == ERRORSTOPMODE)
                ;
            if (filelineerrorstylep)
                printfileline();
            else
                printnl(/* str '! ' */ 264);
            print(/* str 'I can't go on meeting you like this' */ 293);
        }
        {
            helpptr = 2;
            helpline[1] =
                /* str 'One of your faux pas seems to have wounded me dee' */
                294;
            helpline[0] =
                /* str 'in fact, I'm barely conscious. Please fix it and ' */
                295;
        }
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