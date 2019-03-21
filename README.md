# InfLong-Arithmetic
A class written in c++ to support arithmetic operations for long integers having LLONG_MAX number of digits
Right now, this library supports addition, subtraction(unsigned), division, and square root computation up to a certain error
Utility functions of this library use intermediate numbers of type long long, whereas the numbers of type "InfLong" are stored as vectors (digit-by-digit), and all Arithmetic operations are being performed accordingly.
