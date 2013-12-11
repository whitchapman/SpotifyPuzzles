#include <iostream>
 
using namespace std;

//////////////////////////////////////////////

int main() {
  unsigned int input;
  cin >> input;

  //find the first power of 2 equal to or greater than the input.
  //this will work for 32 bit integers as long as the input is less than 2^30 per requirements.
  unsigned int n = 1;
  while (input >= n) {
    n <<= 1;
  }

  //at the initial test, n is the leftmost bit and i is the rightmost bit.
  //at each iteration, n is right shifted and i is left shifted.
  unsigned int result = 0;
  unsigned int i = 1;
  do {

    n >>= 1;

    //test if n exists in input, if so, then or i to the result
    if ((n & input) > 0) {
      result |= i;
    }

    i <<= 1;

    //the last test is when n has become the leftmost bit.
  } while (n > 1);

  cout << result << endl;
}
