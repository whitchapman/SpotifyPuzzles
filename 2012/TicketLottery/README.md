TicketLottery
==============

The puzzle:
* find the probability of getting tickets for your group
* input 4 integers separated by " ":
*   m - total number of people who entered the lottery
*   n - total number of winners
*   t - number of tickets each winner is allowed to buy
*   p - number of people in your group
* output probablity with 10 digit precision

The solution uses combinatorics.  First, determine the min and max number of people from your group that need to win the lottery in order to get enough tickets for your group.  Then, sum the probabilities of winning each x between min and max, inclusive.

       C(p, x) * C(m-p, n-x)  
P(x) = ---------------------  
            C(m, n)

C++
---


Java
----

Spotify Status: Wrong Answer -- there must be an unhandled edge case or a lack of precision in the solution

Compile:  
javac TicketLottery.java

Run:  
java TicketLottery

Run using sample inputs from the Spotify puzzle page:  
java TicketLottery < ../sample-input1.txt  
java TicketLottery < ../sample-input2.txt  
java TicketLottery < ../sample-input3.txt  

