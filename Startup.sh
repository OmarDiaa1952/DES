#!/bin/bash 

read -p 'Enter your Operation (encrypt/decrypt): ' operation
read -p 'Enter your hex filepath: ' hexf
read -p 'Enter Key: ' key
 
g++ des.cpp -o DES;./DES $operation $hexf $key
