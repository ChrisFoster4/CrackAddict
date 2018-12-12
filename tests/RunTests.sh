set -Ee

if [ -z $1 ]
then echo "Give test file name or \"all\" for all test files" && exit 1
fi

echo "Building tests"
if [ $1 == "all" ]
<<<<<<< HEAD
then
    allCheckFiles=$(find . -name "*.check" -type f -printf "%p ")
    echo "Running following check files $allCheckFiles"
    checkmk $allCheckFiles  > tests.c || (echo "Failed to build tests" && rm allCheck.check && exit 1)
=======
then 
    checkmk <(cat $(find * -name "*.check")) > tests.c || (echo "Failed to build tests" && exit 1)
>>>>>>> 1ec9ba67ab657a16dd544317a728118c083ba281
else
    checkmk $1 > tests.c || (echo "Failed to build tests" && exit 1)
fi

echo "Compiling tests"
<<<<<<< HEAD
gcc -Wall -o tests  tests.c ../src/StringGeneration/stringGen.c ../src/md5/md5.c -lcheck -lrt -lpthread -lm -lsubunit ||exit 1
=======
gcc -Wall -o tests  tests.c ../src/stringGen.c ../src/md5.c -lcheck -lrt -lpthread -lm -lsubunit ||exit 1
>>>>>>> 1ec9ba67ab657a16dd544317a728118c083ba281

echo "Running tests"
#echo the message if cowsay isn't avaliable otherwise use cowsay
hash cowsay 1>& /dev/null && ((./tests && cowsay -f turtle "Tests passed") || (cowsay -f stegosaurus "Tests failed")) || ((./tests && echo "Tests passed") || (echo "Tests failed"))
rm ./tests
rm ./tests.c
<<<<<<< HEAD
=======


>>>>>>> 1ec9ba67ab657a16dd544317a728118c083ba281
