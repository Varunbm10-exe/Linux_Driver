# Insert the kernel module
sudo insmod read_write.ko

# Verify the device file has been created
ls /dev/dummydriver

# Set read/write permissions for the device file
sudo chmod 666 /dev/dummydriver

# Write data to the device file
echo "This is varun" > /dev/dummydriver

# Read the first line of data from the device file
head -n 1 /dev/dummydriver

# Display the last 15 kernel log messages
dmesg | tail -n 15

# Move up one directory
cd ..

# Stage changes in the 03_read_write folder
git add 03_read_write/*

# Commit changes with a message
git commit -m "Add 03_next_folder with initial files"

# Push changes to the master branch of the remote repository
git push -u origin master

