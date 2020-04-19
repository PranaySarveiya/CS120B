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

test "Check init -> lock"
set state = init
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check lock -> lock"
set state = lock
setPINA 0x03
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check lock -> lock (2)"
set state = lock
setPINA 0x01
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check lock -> pressHash"
set state = lock
setPINA 0x04
continue 2
expectPORTB 0x00
expect state pressHash
checkResult

test "Check pressHash -> pressHash"
set state = pressHash
setPINA 0x04
continue 2
expectPORTB 0x00
expect state pressHash
checkResult

test "Check pressHash -> releaseHash"
set state = pressHash
setPINA 0x00
continue 2
expectPORTB 0x00
expect state releaseHash
checkResult

test "Check pressHash -> lock"
set state = pressHash
setPINA 0x01
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check pressHash -> lock (2)"
set state = pressHash
setPINA 0x03
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check releaseHash -> releaseHash"
set state = releaseHash
setPINA 0x00
continue 2
expectPORTB 0x00
expect state releaseHash
checkResult

test "Check releaseHash -> unlock"
set state = releaseHash
setPINA 0x02
continue 2
expectPORTB 0x01
expect state unlock
checkResult

test "Check releaseHash -> lock"
set state = releaseHash
setPINA 0x04
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check releaseHash -> lock (2)"
set state = releaseHash
setPINA 0x03
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check unlock -> unlock"
set state = unlock
setPINA 0x7F
continue 2
expectPORTB 0x01
expect state unlock
checkResult

test "Check unlock -> lock (2)"
set state = unlock
setPINA 0x80
continue 2
expectPORTB 0x00
expect state lock
checkResult

test "Check locking with combination while unlocked"
set state = unlock
setPINA 0x04
continue
expectPORTB 0x01
expect state pressHash
checkResult


test "Check locking with combination while unlocked (full test)"
set state = unlock
setPINA 0x04
continue 2

setPINA 0x00
continue 2

setPINA 0x02
continue 2
expectPORTB 0x00
expect state lock



checkResult




















# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
