#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

// ----------------------------------------------- //
// ------------------ Constants ------------------ //
// ----------------------------------------------- //

// Data types
typedef unsigned long long u64;
typedef unsigned long u32;
typedef enum
{
    ENC,
    DEC
} Mode;
struct Setup
{
    Mode mode = ENC;
    string inputFilename;
    string outputFilename;
    u64 key;
};
// KEY
extern const unsigned char SHIFT[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

extern const unsigned char PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

extern const unsigned char PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

// MESSAGE

extern const unsigned char IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

extern const unsigned char EXP[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

extern const unsigned char P[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

extern const unsigned char IIP[64]{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

extern const unsigned char SBOX[8][64]{
    {// S1
     14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
     0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
     4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
     15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

    {// S2
     15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
     3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
     0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
     13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

    {// S3
     10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
     13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
     1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},

    {// S4
     7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
     13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
     10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
     3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},

    {// S5
     2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
     14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
     11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},

    {// S6
     12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
     10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
     9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
     4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},

    {// S7
     4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
     13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
     1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
     6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},

    {// S8
     13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
     1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
     7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
     2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

// ------------------------------------------------ //
// --------------- Helper functions --------------- //
// ------------------------------------------------ //

u64 permute(u64 in, const unsigned char *p, unsigned char inSize, unsigned char outSize)
{
    u64 out = 0;
    for (unsigned char i = 0; i < outSize; i++)
        out |= (in >> (inSize - p[i]) & 1) << (outSize - i - 1);
    return out;
}

inline u32 getR(u64 data)
{
    return (u32)(data);
}

inline u32 getL(u64 data)
{
    return (u32)(data >> 32);
}

inline u32 getC0(u64 data)
{
    return (u32)(data >> 28);
}

inline u32 getD0(u64 data)
{
    return (u32)(data & 0xFFFFFFF);
}

inline void swap(u32 &l, u32 &r)
{
    u32 temp = l;
    l = r;
    r = temp;
}

inline u32 shift(u32 in, unsigned char round)
{
    return (in >> (28 - SHIFT[round])) | (in << SHIFT[round]);
}

inline u64 mergeKey(u32 c, u32 d)
{
    return (((u64)c) << 28) | (d & 0x0FFFFFFF);
}

inline u64 mergeMsg(u32 l, u32 r)
{
    return ((u64)l) << 32 | r;
}

inline unsigned int minimum(unsigned int length)
{
    return length < 524288000 ? length : 524288000;
}

inline u64 ASCII2u64(string b)
{
    return ((uint64_t)(uint8_t)b[0] << 56) | ((uint64_t)(uint8_t)b[1] << 48) | ((uint64_t)(uint8_t)b[2] << 40) | ((uint64_t)(uint8_t)b[3] << 32) | ((uint64_t)(uint8_t)b[4] << 24) | ((uint64_t)(uint8_t)b[5] << 16) | ((uint64_t)(uint8_t)b[6] << 8) | ((uint64_t)(uint8_t)b[7]);
}
inline string u64ToASCII(u64 a)
{
    string result = "";
    for (unsigned int i = 0; i < 8; ++i)
    {
        result += (unsigned char)((a >> (56 - (i << 3))) & 0xFF);
    }
    return result;
}

string read(string fileName)
{
    string line, output = "";
    ifstream file(fileName, ios::binary);
    while (getline(file, line))
        output += line + "\n";
    return output;
}
// ------------------------------------------------- //
// ----------------- DES algorithm ----------------- //
// ------------------------------------------------- //

void generateKeys(u64 key, u64 *keys)
{
    u64 keyPC1 = permute(key, PC1, 64, 56);

    u32 c = getC0(keyPC1);
    u32 d = getD0(keyPC1);

    keys[15] = permute(mergeKey(c, d), PC2, 56, 48);

    for (int i = 0; i < 16; i++)
    {
        c = shift(c, i);
        d = shift(d, i);

        keys[i] = permute(mergeKey(c, d), PC2, 56, 48);
    }
}

u32 feistelFunction(u32 in, u64 k)
{
    u32 result = 0;
    u64 expanded = k ^ permute((u64)in, EXP, 32, 48); // Expansion -> XOR with subkey
    for (int i = 0; i < 8; i++)
    { // S-BOX
        unsigned char idx = expanded >> (7 - i) * 6 & 0x3F;
        idx = idx >> 1 & 15 | (idx & 1) << 4 | idx & 0x20;
        result |= SBOX[i][idx] << (7 - i) * 4;
    }
    return permute((u64)result, P, 32, 32); // Permutation P
}

void processRound(u32 &l, u32 &r, u64 *keys, unsigned char round)
{
    u32 temp = l;
    l = r;
    r = temp ^ feistelFunction(r, keys[round]);
}

u64 process(u64 MSG, u64 keys[16], Mode mode)
{
    // MSG
    u64 msg = permute(MSG, IP, 64, 64); // Initial permutation

    u32 l = getL(msg);
    u32 r = getR(msg);

    if (mode == ENC)
        for (unsigned char i = 0; i < 16; i++)
            processRound(l, r, keys, i);
    else
        for (unsigned char i = 0; i < 16; i++)
            processRound(l, r, keys, 15 - i);

    swap(l, r); // 32-bit swap

    u64 result = mergeMsg(l, r);

    return permute(result, IIP, 64, 64);
}

// ----------------------------------------------- //
// ------------------ Main code ------------------ //
// ----------------------------------------------- //
int main(int argc, char *argv[])
{
    string key, data, KeyFile, action, inputFile, outputFile;

    // Read arguments
    action = argv[1];
    inputFile = argv[2];
    KeyFile = argv[3];
    outputFile = argv[4];

    // Set mode
    Mode mode = action == "encrypt" ? ENC : DEC;

    // Generate keys
    key = read(KeyFile);
    u64 u64key = stoull(key, nullptr, 16);
    u64 keys[16];
    generateKeys(u64key, keys);

    // Read file
    data = read(inputFile);

    // Process data
    ofstream ofs(outputFile, ios::binary);
    for (int i = 0; i < data.size() - 1; i += 8)
    {
        u64 plainText = ASCII2u64(data.substr(i, 8));
        u64 cipher = process(plainText, keys, mode);
        ofs << u64ToASCII(cipher);
    }
    ofs.close();

    return 0;
}