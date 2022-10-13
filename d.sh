#!/bin/bash 
if [ "$1" == "-h" ]; then
  echo "Usage: basename $0"
  echo -e '1.The Script will ask for three things:\n\tthe operation MODE encrypt or decrypt\n\t 2.the hex file that you want to do operation on\n\t 3.the key to encrypt or decrypt\n\t  For Example: 1. operation-> encrypt   \n\t      2. Hex File -> test.hex       \n\t     3. Key -> t.hex or Plain Text like : 0xAABB09182736CCDD \n\t'
  exit 0
fi
read -p 'Enter your Operation (encrypt/decrypt): ' operation
read -p 'Enter your hex filepath: ' hexf
read -p 'Enter Key: ' key
 
g++ des.cpp -o DES;./DES $operation $hexf $key
