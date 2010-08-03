/* 
 * speedbag.c --
 *
 * $Id$
 */

#include <tcl.h>
#include "speedbag.h"
#include <sys/limits.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


/*-----------------------------------------------------------------------------
 * speedbag_TsvToArrayObjCmd --
 *  
 * Implements the `tsv_to_array' command:
 *
 *    tsv_to_array $line arrayName
 *  
 * Results:
 *      An array is updated with zero or more key-value pairs.
 *
 * Side effects:
 *      None.
 *-----------------------------------------------------------------------------
 */     
int
speedbag_TsvToArrayObjCmd (clientData, interp, objc, objv)
    ClientData    clientData;
    Tcl_Interp   *interp;
    int           objc;
    Tcl_Obj      *CONST objv[];
{
    if (objc != 3) {
	Tcl_WrongNumArgs (interp, 1, objv, "string array");
	return TCL_ERROR;
    }

    return TCL_OK;
}

