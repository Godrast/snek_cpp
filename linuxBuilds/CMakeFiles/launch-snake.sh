#!/bin/sh
bindir=$(pwd)
cd /home/bartosz/cpp_personal/snek_cpp/snake/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/bartosz/cpp_personal/snek_cpp/linuxBuilds/snake 
	else
		"/home/bartosz/cpp_personal/snek_cpp/linuxBuilds/snake"  
	fi
else
	"/home/bartosz/cpp_personal/snek_cpp/linuxBuilds/snake"  
fi
