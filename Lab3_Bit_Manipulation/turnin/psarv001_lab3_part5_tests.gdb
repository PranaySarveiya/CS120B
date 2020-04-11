# Test file for "Lab3_Bit_Manipulation"


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

test "D and B0: 0000 0000 0	-> [B2:B1] = 00"
setPIND 0x00
setPINB 0x00
continue 5
expectPORTB 0x00
checkResult

test "D and B0: 0010 0011 0 (70)     -> [B2:B1] = 01"
setPIND 0x23
setPINB 0x00
continue 5
expectPORTB 0x02
checkResult

test "D and B0: 0010 0011 1 (71)     -> [B2:B1] = 01"
setPIND 0x23
setPINB 0x01
continue 5
expectPORTB 0x02
checkResult

test "D and B0: 1111 1111 1 (mx)     -> [B2:B1] = 01"
setPIND 0xFF
setPINB 0x01
continue 5
expectPORTB 0x02
checkResult

test "D and B0: 0010 0010 1  (69)   -> [B2:B1] = 10"
setPIND 0x22
setPINB 0x01
continue 5
expectPORTB 0x04
checkResult

test "D and B0: 0000 0011 0 (6)     -> [B2:B1] = 10"
setPIND 0x03
setPINB 0x00
continue 5
expectPORTB 0x04
checkResult

test "D and B0: 0000 0010 1 (5)     -> [B2:B1] = 00"
setPIND 0x02
setPINB 0x01
continue 5
expectPORTB 0x00
checkResult

test "D and B0: 0000 0000 0     -> [B2:B1] = 00"
setPIND 0x00
setPINB 0x00
continue 5
expectPORTB 0x00
checkResult


# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
