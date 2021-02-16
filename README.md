# RPN_Calculator
Console program for counting mathematical expressions. Operations handled by program: add,  subtract, divide, multiply, calculate the power.
Program can count complex epressions, for example: ((10-5)/5^2)*-3+2.
On the begin, program reads expression from the keyboard, then converts it to the Reverse Polish Notation.
Conversion is done using 2 stacks, one for signs, and one for numbers.

Operation: +, -, *, /, ^
During conversion, everytime when program encounters an operation, if priority of the operation on the top of signs stack is lower or equal to currently considered, or the stack is empty, program puts operation on the top of the signs stack. In the other case, program removes operations from the sings stack, and adds it to the number stack, until any of these 2 conditions are met.
Every attemption of putting operation on top of numbers stack(pushAndCheck function) ends with calculating expression based on that operation, and 2 last numbers on top of the stack.
