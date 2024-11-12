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

# Stage changes in the 03_read_write folder
git add 03_read_write/*

# Commit changes with a message
git commit -m "Add 03_next_folder with initial files"

# Push changes to the master branch of the remote repository
git push -u origin master

