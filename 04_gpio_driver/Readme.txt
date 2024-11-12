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

