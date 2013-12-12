ZipfsSong
==============

The puzzle:
* read two integers, the number of input songs and the number of output titles to display
* for each song, read the number of plays and the title
* calculate the quality for each song
* sort the songs from greatest to least quality, using track number as a tie breaker
* display song titles with the highest quality, in decreasing order of quality


C++
---

The C++ solution is a linked list implementation that runs in n^2 time for insertions.  Spotify Status: TBD

Compile:  
g++ zipfs_song.cpp -o zipfs_song.exe

Run (expects an integer as input):  
./zipfs_song.exe

Run using sample inputs from the Spotify puzzle page:  
./zipfs_song.exe < ../sample-input1.txt  
./zipfs_song.exe < ../sample-input2.txt


Java
----

The Java solution makes use of the Comparable interface and the TreeSet implementation of a SortedSet.  Spotify Status: Time limit exceeded -- this could be due to the JVM startup time.

Compile:  
javac ZipfsSong.java

Run (expects an integer as input):  
java ZipfsSong

Run using sample inputs from the Spotify puzzle page:  
java ZipfsSong < ../sample-input1.txt  
java ZipfsSong < ../sample-input2.txt

