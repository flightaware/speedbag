/* 
 * speedbag.h -- flightaware tcl speedup stuff
 *
 */

extern int
speedbag_TsvToArrayObjCmd (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);

#ifndef TCL_SIZE_MAX
#ifndef Tcl_Size
/* Tcl 8.x without the Tcl_Size backport: all the affected APIs use "int" */
typedef int Tcl_Size;
#endif
#endif
