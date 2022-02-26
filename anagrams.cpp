#include <iostream>
#include <stdexcept>
#include <string>

//this code takes in a string (without spaces) and return its anagram(s).

int main() {

  std::cout << "Type here your initial string: ";

  std::string s;
  std::cin >> s;

  std::cout << "Tell me a number to start random reordering from: n = "; 

  int n; // n is basically an upper limit, see notes [1] and [2].
  std::cin >> n;

  if (n > 10000) {
    throw std::runtime_error{"Sorry, but your n is far too great for my patience..."};
  };

  std::cout << "Is n also equal to the times you want this algorithm to be executed? [y/n] ";
  std::string ans;
  std::cin >> ans;

  int m; // m defines the maximum number of anagrams you want to obtain. [1]: if nothing is said, m is chosen equal to n.

  if (ans == "n" || ans == "N") {
    std::cout << "Well, tell me another number, then: m = ";
    std::cin >> m;
  } else {
    m = n;
  };

  int a = s.size();

  if (m == 0) {
    ;
  } else {
    std::cout << "Last question: do you also want to know each result generated during runtime? [y/n] ";
    std::string ans2;
    std::cin >> ans2;

    for (int i{1}; i <= m; ++i) {

      int d = rand() % n; // [2]: d is a number chosen randomly between 0 and n.

      int r; // r indicates the position of the "cut"; it must not overcome the string size.

      if (d <= a) {
        r = d;
      } else {
        while (r > a)
          r = d % a;
      };

      std::string z1 = s; 
      std::string z2 = s;
      std::string b = z1.erase(0, r); // this string corresponds to s without its first r char.
      std::string c = z2.erase(r); // this string corresponds to the first r char of s.

      int e = b.size();
      int z = 0; // an index useful only to see on screen wihch of the following path the code applies.

      if (r <= e) {
        s = b.insert(r, c); //insert string c into string b, after r char.
      } else {
        s = b.append(c); //swap the two parts s is cut into.
        ++z;
      }

      if (ans2 == "y" || ans2 == "Y") {
        std::cout << i << ") " << s << " [" << z << " " << d << "]\n";
      } else {
        ;
      };
    };
  };

  std::cout << "Here's your last recombination: " << s << '\n';
}