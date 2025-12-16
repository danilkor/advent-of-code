# My solutions to advent of code

Some of solutions use different language, but to run c++ you need to compile a day you want with ```-std=c++23``` and ```-I cpp/libs```


## Examples  
(From *advent-of-code/builds*)
- **Perfomance**
```
g++ -O3 -std=c++23 -I ../cpp/libs -o a.out ../cpp/year/day.cpp
```  
- **Debug**
```
g++ -O0 -g -Wall -Wextra -D_GLIBCXX_DEBUG -std=c++23 -I ../cpp/libs -o a.out ../cpp/year/day.cpp
```

Then stdin the input you want into the level 


