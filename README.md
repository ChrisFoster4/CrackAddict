MD5Cracker:
A multi-threaded MD5 hash cracker

**Compiling**  
Currently the program must be build on-top of Linux or FreeBSD with a C11 compiler,cmake and make installed  
On Ubuntu 18.04 to satisfy these dependencies run
```
sudo apt-get update && sudo apt install -y cmake make gcc
```
To build the program run the following commands from the root of the repository(The same directory as this file)  
```
cmake .
make 
```

**Running**  
To run the program call it with an MD5 hash.  
For instance
```
./MD5Cracker 5d41402abc4b2a76b9719d911017c592
```  
Note currently only hashes of 5 letter words are crackable.  
To get a hash to crack run the following(replacing "hello" with any 5 letter word)  
```
echo -n "hello" | md5sum
```
There are additional command line options. To see these run
```
./MD5Cracker --help 
```

**Unit tests**  
  
Tests are written with the check library:  
https://libcheck.github.io/check/

To install check on Ubuntu 18.04 run:
```
sudo apt-get update && sudo apt install -y check
```

Run a single test with ./RunTests.sh then the .check file for instance:
```
cd tests
./RunTests.sh stringGen/stringGen.check
```

Run all tests with:
```
cd tests
./RunTests.sh all
```
