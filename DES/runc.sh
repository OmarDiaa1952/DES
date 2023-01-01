#!/bin/bash

echo 'Process C Code of Group '$1

echo ''
echo 'Rmove temp files if exist ..........'
rm des 2>&1 >/dev/null
rm plain_text.txt 2>&1 >/dev/null
rm cipher_text.dat 2>&1 >/dev/null
rm large_cipher_text.dat 2>&1 >/dev/null

echo ''
echo 'Compile.............................'
gcc des_g$1.c -o des -std=c99 -pthread
ls des -l

echo ''
echo 'Start ..............................'
date +"%T.%3N"

echo ''
echo 'Encrypt .............................'
./des encrypt plain_text_org.txt key.txt cipher_text.dat 2>&1 >/dev/null
ls cipher_text.dat -l
diff cipher_text.dat cipher_text_org.dat
date +"%T.%3N"

echo ''
echo 'Decrypt .............................'
./des decrypt cipher_text.dat key.txt plain_text.txt 2>&1 >/dev/null
ls plain_text.txt -l
diff plain_text.txt plain_text_org.txt
date +"%T.%3N"

echo ''
echo 'Encrypt/Decrypt Large File ..........'
./des encrypt large_plain_text_org.txt key.txt large_cipher_text.dat 2>&1 >/dev/null
./des decrypt large_cipher_text.dat key.txt large_plain_text.txt 2>&1 >/dev/null
ls large_cipher_text.dat -l
ls large_plain_text.txt -l
diff large_plain_text.txt large_plain_text_org.txt
date +"%T.%3N"

echo ''
echo 'End'
