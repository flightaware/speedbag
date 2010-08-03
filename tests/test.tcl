#
#
# $Id$
#

package require Cplan

proc testit {} {
    set fp [open metars.txt]
    while {[gets $fp line] >= 0} {
	puts $line
	puts [::cplan::decode_metar $line]
	puts ""
    }
}

proc doit {} {
    testit
}

if !$tcl_interactive {
    doit
}
