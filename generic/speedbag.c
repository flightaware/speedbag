/* 
 * speedbag.c --
 *
 * $Id$
 */

#include <tcl.h>
#include <string.h>
#include "speedbag.h"


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
    char    *stringPtr;
    int      stringLen;
    int      count = 0;
    char    *p;
    char    *end;
    Tcl_Obj *arrayNameObj;
    Tcl_Obj *elementNameObj;
    Tcl_Obj *valueObj;

    if (objc != 3) {
	Tcl_WrongNumArgs (interp, 1, objv, "string array");
	return TCL_ERROR;
    }

    stringPtr = Tcl_GetStringFromObj (objv[1], &stringLen);
    end = stringPtr + stringLen;

    arrayNameObj = objv[2];

    while (*stringPtr && (p = strchr (stringPtr, (int)'\t')) != NULL) {
        elementNameObj = Tcl_NewStringObj (stringPtr, p - stringPtr);
	// printf("element '%s'\n", Tcl_GetString (elementNameObj));
	stringPtr = p + 1;

	if (*stringPtr == '\0') {
		valueObj = Tcl_NewObj();
        Tcl_IncrRefCount (elementNameObj);
        if (Tcl_ObjSetVar2 (interp, arrayNameObj, elementNameObj, valueObj, TCL_LEAVE_ERR_MSG) == NULL) {
            return TCL_ERROR;
        }
        Tcl_DecrRefCount (elementNameObj);
        count++;
        break;
	}

	p = strchr (stringPtr, (int)'\t');
	if (p == NULL) {
	    valueObj = Tcl_NewStringObj (stringPtr, end - stringPtr);
	    // printf("p null value '%s'\n", Tcl_GetString (valueObj));
	    stringPtr = end;
	} else {
	    valueObj = Tcl_NewStringObj (stringPtr, p - stringPtr);
	    // printf("value '%s'\n", Tcl_GetString (valueObj));
	    stringPtr = p + 1;
	}

	Tcl_IncrRefCount (elementNameObj);
	if (Tcl_ObjSetVar2 (interp, arrayNameObj, elementNameObj, valueObj, TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
	}
	Tcl_DecrRefCount (elementNameObj);
	count++;

	if (p == NULL) {
	    // printf("p null\n");
	    break;
	}
    }

    if (*stringPtr != '\0') {
	Tcl_AppendResult (interp, "list has uneven number of elements", NULL);
	return TCL_ERROR;
    }

    Tcl_SetObjResult (interp, Tcl_NewIntObj (count));
    return TCL_OK;
}

// vim: set ts=8 sw=4 sts=4 noet :
