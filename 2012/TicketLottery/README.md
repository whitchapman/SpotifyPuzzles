TicketLottery
==============

The puzzle:
* find the probability of getting tickets for your group
* input 4 integers separated by " ":
    + m - total number of people who entered the lottery
    + n - total number of winners
    + t - number of tickets each winner is allowed to buy
    + p - number of people in your group
* output probablity with 10 digit precision

First, determine the min and max number of people from your group that need to win the lottery in order to get enough tickets for your group.  Then, sum the probabilities of winning each x between min and max, inclusive.  Each probability is calculated using combinatorics:

```
       C(p, x) * C(m-p, n-x)  
P(x) = ---------------------  
            C(m, n)
```

C++
---

The C++ solution uses a decimal implentation based on a long with an exponent field.  The class was coded to be only robust enough to address the problem's requirements.

Spotify Status: Wrong Answer -- the decimal implementation gives the same answers to the sample inputs as the Java program; however, there must be an edge case that is still incorrect.

Compile:
g++ ticket_lottery.cpp -o ticket_lottery.exe

Run:
./ticket_lottery.exe

Run using sample inputs from the Spotify puzzle page:
./ticket_lottery.exe < ../sample-input1.txt
./ticket_lottery.exe < ../sample-input2.txt

Java
----

Spotify Status: Accepted -- by switching from double to BigDecimal with DECIMAL64 precision, the program was accepted.

Compile:  
javac TicketLottery.java

Run:  
java TicketLottery

Run using sample inputs from the Spotify puzzle page:  
java TicketLottery < ../sample-input1.txt  
java TicketLottery < ../sample-input2.txt  
java TicketLottery < ../sample-input3.txt  

