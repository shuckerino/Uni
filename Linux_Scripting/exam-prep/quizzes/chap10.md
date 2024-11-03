1) test and [ 

2) 
a) Option -d: Check if first arg is directory 
b) Option -e: Check if first arg is an existing file
c) Option -f: Check if first arg is a regular file 
d) Option -h: Check if first arg is symbolic link
e) Option -s: Check if first arg is existing file and not empty
f) Option -z: Check if first arg is empty string

3) 
a) 
- Check if first arg equals second arg
- No problems

b)
- Check if first arg equals second arg
- Problem is if there are spaces in the variable names, so that arguments for test do not match and we get runtime error

c)
- Check if first arg is less or equal to second arg
- Problem if one of the args is not convertable to integer

d)
- Check if first arg is different to second arg
- Problem if both args are not convertable to integer
- Also problem if second argument has space

e)
- Runtime error because -n only checks one argument, but two are given

f) 
- Runtime error, because no spaces

