/**************************************************************************/
/* FILE   **************          check.c          ************************/
/**************************************************************************/
/* Author: Dave Can                                                       */
/* Update: Patrick Miller -- Ansi support (Dec 2000)                      */
/* Copyright (C) University of California Regents                         */
/**************************************************************************/
/*
 * $Log:
 *
 * Revision 12.7  1992/11/04  22:04:55  miller
 * Initial revision
 *
 * Revision 12.7  1992/10/21  18:07:25  miller
 * Initial RCS Version by Cann
 *
 */
/**************************************************************************/

#include "world.h"


FILE *input   = 0;                 /* IF1 INPUT  FILE POINTER         */
FILE *output  = 0;                /* IF1 OUTPUT FILE POINTER         */

char *program = "if1check";            /* PROGRAM NAME                    */

int info      = FALSE;  /* NOT ALL USED */
int noassoc   = FALSE;
int sgnok     = FALSE;
int native    = TRUE;
int tgcse     = FALSE;
int normidx   = FALSE;
int cRay      = FALSE;
int alliantfx = FALSE;
int glue      = FALSE;
/* int iter      = FALSE; */


/**************************************************************************/
/* LOCAL  **************      ParseCommandLine     ************************/
/**************************************************************************/
/* PURPOSE: PARSE THE COMMAND LINE argv CONTAINING argc ENTRIES. THE 1ST  */
/*          ENTRY (argv[0]) IS IGNORED.   IF AN ARGUMENT DOES NOT BEGIN   */
/*          WITH A DASH, IT IS CONSIDERED THE NAME OF A FILE.  THE FIRST  */
/*          ENCOUNTERED FILE IS FOR IF1 INPUT.  THE SECOND ENCOUNTERED    */
/*          FILE IS FOR IF1 OUTPUT.  ANY OTHER FILES ON THE COMMAND LINE  */
/*          CAUSE AN ERROR MESSAGE TO BE PRINTED.                         */
/*                                                                        */
/*          FILES:                                                        */
/*              0:      -> input IF1                                      */
/*              1:      -> output report                                  */
/*                                                                        */
/*          OPTIONS:                                                      */
/*              -       -> Skip a standard file (in, out, etc..)          */
/**************************************************************************/

static void ParseCommandLine( argc, argv )
int    argc;
char **argv;
{
    register char *c;
    register int   fmode = 0;
    register int   idx;
    register FILE *fd;

    for ( idx = 1; idx < argc; ++idx ) {
        if ( *(c = argv[ idx ]) != '-' ) {
            switch ( fmode ) {
                case 0: 
                    if ( (fd = fopen( c, "r" )) == NULL )
                        Error2( "CAN'T OPEN", c );

                    input = fd;

                    AssignSourceFileName( c );

                    fmode++;
                    break;

                case 1:
                    if ( (fd = fopen( c, "w" )) == NULL )
                        Error2( "CAN'T OPEN", c );

                    output = fd;

                    fmode++;
                    break;

                default:
                    Error2( "ILLEGAL ARGUMENT", c );
                }

            continue;
            }

        switch ( *( ++c ) ) {
            case '\0':
                fmode++;
                break;

            default:
                Error2( "ILLEGAL ARGUMENT", --c );
            }
        }
}


/**************************************************************************/
/* GLOBAL **************            main           ************************/
/**************************************************************************/
/* PURPOSE: CHECK THE STURCTURE AND SEMANTICS OF ALL FUNCTION GRAPHS.     */
/*          DIAGNOSTICS ARE PRINTED TO stderr.                            */
/**************************************************************************/

int main( argc, argv )
int    argc;
char **argv;
{
   input = stdin;
   output = stdout;
   
    ParseCommandLine( argc, argv );

    If1Read();

    If1Check();

    return OK;
}
