# **COMP 310 & ECSE 427 Assignment 1: Building an OS Shell**  

## Development Environment  
All codes are developed on `mimi.cs.mcgill.ca`.  

## RUN101: How to get started  
A `makefile` is provided together with this project. You may use the instructions provided below:  
```bash
# To compile the project
make mysh

# To test the shell
make test

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