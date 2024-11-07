# Clean up previous build files
make clean

# Compile the module
make

# Check the device number in /proc/device with grep for my_dev_nr
cat /proc/device | grep my_dev_nr

# Insert the dev_nr.ko module (note the device number output)
sudo insmod dev_nr.ko

# Create a device node with the noted device number (replace 90 with your device number)
sudo mknod /dev/mydevice c 90 0

# Check the last two dmesg messages to confirm device registration
dmesg | tail -n 2

# Open a new test program file in gedit
gedit test.c

# Compile the test program
gcc test.c -o test

# Set read/write permissions for the device
sudo chmod 666 /dev/mydevice

# Check the last five dmesg messages
dmesg | tail -n 5

# Remove the dev_nr.ko module
sudo rmmod dev_nr.ko

