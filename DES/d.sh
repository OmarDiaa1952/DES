#!/bin/bash 
if [ "$1" == "-h" ]; then
  echo "Usage: basename $0"
  echo -e '1.The Script will ask for three things:\n\tthe operation MODE encrypt or decrypt\n\t 2.the hex file that you want to do operation on\n\t 3.the key to encrypt or decrypt\n\t  For Example: 1. operation-> encrypt   \n\t      2. Hex File -> test.hex       \n\t     3. Key -> t.hex or Plain Text like : 0xAABB09182736CCDD \n\t'
  exit 0
fi
read -p 'Enter your Operation (encrypt/decrypt): ' operation
echo  -n 'Enter your filepath: ' 
FILE=`zenity --file-selection --title="Select a File"`
echo "$FILE" 
echo -n 'Enter Key: '
Key_FILE=`zenity --file-selection --title="Select a Key_File"`
echo "$Key_FILE"  
g++ des_g10.cpp -o DES;./DES $operation $FILE $Key_FILE