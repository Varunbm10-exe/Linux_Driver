# Clean previous builds and compile the module
make clean
make

# Insert the compiled kernel module (requires sudo permissions)
sudo insmod gpio_driver.ko

# Check the last 10 lines of the kernel log to verify the module loaded correctly
dmesg | tail -n 10

# Confirm that the device file was created in /dev (should be /dev/my_gpio_driver)
ls /dev/my_gpio_driver

# List details of the device file to note down major and minor numbers
ls -al /dev/my_gpio_driver

# Grant read and write permissions to all users on the device file
sudo chmod 666 /dev/my_gpio_driver

# Test turning the LED on by writing '1' to the device file
echo 1 > /dev/my_gpio_driver  # LED should turn on if the write function works correctly

# Test turning the LED off by writing '0' to the device file
echo 0 > /dev/my_gpio_driver  # LED should turn off if the write function works correctly

# Move up one directory
cd ..

# Clean previous builds, compile the module, and load it
make clean
make
sudo insmod gpio_driver.ko

# Check kernel log to confirm module load status
dmesg | tail -n 10

# Verify the device file creation
ls /dev/my_gpio_driver

# Note down device number details (major and minor numbers)
ls -al /dev/my_gpio_driver

# Set read and write permissions for all users on the device file
sudo chmod 666 /dev/my_gpio_driver

# Test the LED by writing '1' to turn it on
echo 1 > /dev/my_gpio_driver

# Test the LED by writing '0' to turn it off
echo 0 > /dev/my_gpio_driver

# Navigate up one directory to commit changes
cd ..

# Stage the new driver files for commit
git add 04_gpio_driver/*

# Commit the changes with a descriptive message
git commit -m "Adding 04_gpio_driver with initial files"

# Push the commit to the 'master' branch on the remote repository
git push -u origin master

