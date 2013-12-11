ReversedBinary
==============

The puzzle:
* input an integer N, 1 ≤ N ≤ 1000000000
* convert N to a binary string
* reverse the binary string
* convert the result back to an integer


C++
---

The C++ solution consists of two iterations:  the first to find the highest order bit, and the second to sum the result.  It runs in 2 * log (input).

Compile:  
g++ binary_reverse.cpp -o binary_reverse.exe

Run (expects an integer as input):  
./binary_reverse.exe

Run using sample inputs from the Spotify puzzle page:  
./binary_reverse.exe < sample-input1.txt  
./binary_reverse.exe < sample-input2.txt


Java
----

The Java solution is aided by the Integer.toBinaryString function.

Compile:  
javac BinaryReverse.java

Run (expects an integer as input):  
java BinaryReverse

Run using sample inputs from the Spotify puzzle page:  
java BinaryReverse < sample-input1.txt  
java BinaryReverse < sample-input2.txt

