#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long rValues[5];
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        std::string cleaned;
        for(unsigned int i = 0; i < k.size(); ++i){
            if(k[i] >= 'A' && k[i] <= 'Z'){
                cleaned += k[i] + 32;
            }
            else{
                cleaned += k[i];
            }
        }

        int currentIndex = 4;
        int position = cleaned.size() - 1;
        while(position >= 0 && currentIndex >= 0){
            unsigned long long value = 0;
            unsigned long long multiplier = 1;
            int count = 0;

            while(count < 6 && position >= 0){
                char ch = cleaned[position];
                int num = 0;
                if(ch >= 'a' && ch <= 'z'){
                    num = ch - 'a';
                }
                else if(ch >= '0' && ch <= '9'){
                    num = ch - '0' + 26;
                }
                value += num * multiplier;
                multiplier *= 36;
                --position;
                ++count;
            }

            w[currentIndex] = value;
            --currentIndex;
        }

        HASH_INDEX_T finalHash = 0;
        for(int i = 0; i < 5; ++i){
            finalHash += rValues[i] * w[i];
        }
        return finalHash;
    }



    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = (char)(tolower(letter));
        if (letter>= 'a' && letter <= 'z') 
        {
            return (HASH_INDEX_T)(letter -'a');
        }
        else
        {
            return (HASH_INDEX_T)(letter - 'a' + 26);
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
