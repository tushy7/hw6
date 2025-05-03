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
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        std::string lower;
        for(unsigned int i = 0; i < k.size(); ++i){
            if(k[i] >= 'A' && k[i] <= 'Z'){
                lower += k[i] + 32;
            }
            else{
                lower += k[i];
            }
        }

        int inFours = 4;
        int i = lower.size() - 1;
        while(i >= 0 && inFours >= 0){
            unsigned long long curr = 0;
            unsigned long long base = 1;
            int count = 0;
            while(count < 6 && i >= 0){
                int val = 0;
                if(lower[i] >= 'a' && lower[i] <= 'z'){
                    val = lower[i] - 'a';
                }
                else if(lower[i] >= '0' && lower[i] <= '9'){
                    val = lower[i] - '0' + 26;
                }
                curr += val * base;
                base *= 36;
                --i;
                ++count;
            }
            w[inFours] = curr;
            --inFours;
        }

        HASH_INDEX_T final = 0;
        for(int i = 0; i < 5; ++i)
        {
            final += rValues[i] * w[i];
        }
        return final;    
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
