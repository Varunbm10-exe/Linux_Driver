# Clean up previous build files
make clean

# Compile the module
make

# Start a new tmux session
tmux

# In another tmux pane or window, continuously monitor kernel messages
sudo dmesg -W

# Insert the hello.ko module (output will display in dmesg window)
sudo insmod mymodule.ko

# Remove the hello.ko module (output will display in dmesg window)
sudo rmmod mymodule.ko

