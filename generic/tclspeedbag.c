/*
 * tclspeedbag.c --
 *
 */

#include <tcl.h>
#include "speedbag.h"

#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLEXPORT


/*
 *----------------------------------------------------------------------
 *
 * Speedbag_Init --
 *
 *	Initialize the speedbag extension.  The string "speedbag" 
 *      in the function name must match the PACKAGE declaration at the top of
 *	configure.in.
 *
 * Results:
 *	A standard Tcl result
 *
 * Side effects:
 *
 *----------------------------------------------------------------------
 */

EXTERN int
Speedbag_Init(Tcl_Interp *interp)
{
    Tcl_Namespace *namespace;

    /*
     * This may work with 8.0, but we are using strictly stubs here,
     * which requires 8.1.
     */
    if (Tcl_InitStubs(interp, "8.1", 0) == NULL) {
	return TCL_ERROR;
    }

    if (Tcl_PkgRequire(interp, "Tcl", "8.1", 0) == NULL) {
	return TCL_ERROR;
    }

    if (Tcl_PkgProvide(interp, "Speedbag", PACKAGE_VERSION) != TCL_OK) {
	return TCL_ERROR;
    }

    namespace = Tcl_CreateNamespace (interp, "speedbag", (ClientData)NULL, (Tcl_NamespaceDeleteProc *)NULL);

    Tcl_CreateObjCommand (interp,
			  "speedbag::tsv_to_array",
			  speedbag_TsvToArrayObjCmd,
                          (ClientData) NULL,
                          (Tcl_CmdDeleteProc*) NULL);

    if (Tcl_Export (interp, namespace, "*", 0) == TCL_ERROR) {
	return TCL_ERROR;
    }

    return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * Speedbag_SafeInit --
 *
 *	Initialize the speedbag extension in a safe interpreter.
 *
 * Results:
 *	A standard Tcl result
 *
 * Side effects:
 *	Very little
 *
 *----------------------------------------------------------------------
 */

EXTERN int
Speedbag_SafeInit(Tcl_Interp *interp)
{
    return Speedbag_Init (interp);
}

// vim: set ts=8 sw=4 sts=4 noet :
