#!/bin/bash
# Check if the user is root
if [ $(id -u) != "0" ]; then
    echo "You must be root to install projup."
    exit 1
fi

cmake --install .

# Create a folder in /etc/projup/
mkdir /etc/projup/

# Move the templates folder to /etc/projup/
mv templates /etc/projup/