# **COMP 310 & ECSE 427 Course Project: Shell**  

## Development Environment  
All codes are developed on `mimi.cs.mcgill.ca`.  

## RUN101: How to get started  
A `makefile` is provided together with this project. You may use the instructions provided below:  
```bash
# To compile the project
make mysh

# To test the shell
make test

# To test the shell with crazy tester
make crazy_test

# To pack up for submission
make pack

# Clean
make clean
```

## Commands
Here are available commands listed below:
> `help` - List all avaliable commands.  
> `quit` - Exit the current process.  
> `set VAR STRING` - Set variable VAR with string STRING. Now supporting sentence as value (i.e. hello world).  
> `print VAR` - Print the value of variable VAR.  
> `run SCRIPT.txt` - Run the script SCRIPT.  

## Examples
```bash
./mysh # Start the shell
Welcome to the Pengnan Fan Shell
Version 1.0 Created January 2o2o
& set singleword hello # Store single-word value
& print singleword
hello
& set multiword hello\ world # Use backslash to escape blank
& print multiword
hello world
& set multiword hello world
& print multiword
hello
```