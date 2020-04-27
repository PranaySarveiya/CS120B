# Test file for "Lab4_State_Machines"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "Check init => chck & chck loop"
set state = init
setPINA ~0x00
continue 10
expectPORTC 0x07
expect state chck
checkResult


test "Check chck -> inc (right edge)"
set state = init
setPINA ~0x01
continue 10

setPINA ~0x00
continue 10

setPINA ~0x01
continue 10

setPINA ~0x00
continue 10

setPINA ~0x01
continue 10

expectPORTC 0x09
expect state chck
checkResult

test "Check chck -> inc from left edge and dec to 0"
set state = init
setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x01
continue 10

expectPORTC 0x01
expect state wait
checkResult

test "Check chck -> dec"
set state = init
setPINA ~0x02
continue 10

expectPORTC 0x06
expect state wait
checkResult

test "Check chck -> dec (left edge)"
set state = init
setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

setPINA ~0x00
continue 10

setPINA ~0x02
continue 10

expectPORTC 0x00
expect state chck
checkResult
#test "Check chck -> dec (right edge)"

#test "chck -> dec"
#test "reset ->reset"
#test "reset ->chck"
#test "wait -> reset"
#test "wait -> chck"
#test "wait -> wait"












































# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
