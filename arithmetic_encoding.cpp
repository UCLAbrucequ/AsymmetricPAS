//
//  arithmetic_encoding.cpp
//  EncoderInC
//
//  Created by Eugene Min on 7/5/22.
//
#include "arithmetic_encoding.h"
#include "utility.h"
#include <assert.h>
#include <iostream>
#include <math.h>
using namespace std;

CCDM::CCDM(float cwd_length, float p)
{
    /*  INPUTS:
     cwd_length: the length of a output code word
     p: the probability of 1's in the output/desired distribution*/
    m_cwd_length = cwd_length;
    m_p = p;
    m_num_1 = cwd_length * p;
    m_num_0 = cwd_length - m_num_1;
    m_input_length = floor(nchoosek_log2(m_cwd_length, m_num_1));
    if(floorf(m_num_1) != m_num_1 || floorf(m_num_0) != m_num_0)
        cout << ("Number or zeros/ones not integer!") << endl;
}

float CCDM::getP()
{
    return m_p;
}

int CCDM::getInputSize()
{
    return m_input_length;
}

bool CCDM::encode(std::vector<int> input_raw, std::vector<int>& encoded)
{
    encoded.clear();
    float num0 = m_num_0;
    float num1 = m_num_1;
    std::vector <int> input;
    if(!m_input_length)
        input.push_back(input_raw[input_raw.size() - 1]);
    for(int i = input_raw.size() - m_input_length; i < input_raw.size(); i++)
        input.push_back(input_raw[i]);
    bool valid = check_input(input);
    
    // First calculate the input bounds
    float input_lo = 0;
    float input_hi = 1;
    
    for(int i = 0; i < input.size(); i++)
    {
        float interval = input_hi - input_lo;
        float mid = input_lo + interval / 2;
        if(input[i] == 0)
            input_hi = mid;
        else
            input_lo = mid;
    }
    cout << input_lo << ", " << input_hi << endl;
    
    // Now, encode the inputs
    float encode_lo = 0;
    float encode_hi = 1;
    while(encoded.size() != m_cwd_length)
    {
        // Case 0: if we want to map to extreme distributions
        if(num0 == 0)
        {
            while(num1 > 0)
            {
                encoded.push_back(1);
                num1--;
            }
            break;
        }
        else if(num1 == 0)
        {
            while(num0 > 0)
            {
                encoded.push_back(0);
                num0--;
            }
            break;
        }
        float encode_interval = encode_hi - encode_lo;
        float threshold = encode_lo + (num0 / (num0 + num1)) * encode_interval;
        
        // Case 1: input_hi is smaller or equal to thres
        if(input_hi <= threshold)
        {
            encoded.push_back(0); //  Successfully encoded a 0
            encode_hi = threshold; //  Change bounds
            num0--; //  Update pocket
        }
        // Case 2: input_lo is greater of equal to thres
        else if(input_lo >= threshold)
        {
            encoded.push_back(1); // Successfully encoded a 1
            encode_lo = threshold; // Change bounds
            num1 --; // Update pocket
        }
        //Case 3: left interval is within the right bounds
        else
        {
            if(input_hi == encode_hi && input_lo <= threshold)
            {
                encoded.push_back(1); // Update encoded list
                encode_lo = threshold; // Change bounds
                num1--; // Update pocket
            }
            else if(input_lo == encode_lo && input_hi >= threshold)
            {
                encoded.push_back(0); // Update encoded list
                encode_hi = threshold; // Change bounds
                num0--; // Update pocket
            }
            else{ // "straddle case"
                encoded.push_back(1); // Update encoded list
                encode_lo = threshold; //Change bounds
                num1--; //Update Pocket
            }
        }
    }
    return valid;
}

bool CCDM::decode(std::vector<int> encoded, std::vector<int>& decoded, int MCDM_input_length)
{
    /*
     INPUT:
     msg: message need to decode in string
     
     OUTPUT:
     Decoded: a string of decoded input.
     */
    decoded.clear();
    float num0 = 0;
    float num1 = 0;
    for(int i = 0; i < encoded.size(); i++)
    {
        if(encoded[i] == 0)
            num0++;
        else if(encoded[i] == 1)
            num1++;
    }
    check_msg(encoded, num0);
    float decode_lo = 0;
    float decode_hi = 1;
    
    for(int i = 0; i < encoded.size(); i++)
    {
        float decode_interval = decode_hi - decode_lo;
        float threshold = decode_lo + (num0 / (num0 + num1)) * decode_interval;
        
        if(encoded[i] == 0)
        {
            decode_hi = threshold; //Update bounds
            num0--; //Update pocket
        }
        else
        {
            decode_lo = threshold; //Update bounds
            num1--; //Update pocket
        }
    }
    
    float encode_lo = 0;
    float encode_hi = 1;
    while(decoded.size() != m_input_length)
    {
        float encode_interval = encode_hi - encode_lo;
        float mid = encode_lo + encode_interval /2;
        if(decode_lo < mid)
        {
            decoded.push_back(0);
            encode_hi = mid;
        }
        else
        {
            decoded.push_back(1);
            encode_lo = mid;
        }
    }
    vector<int> padded_decoded;
    for(int i = MCDM_input_length; i > decoded.size(); i--)
        padded_decoded.push_back(0);
    for(int i = 0; i < decoded.size(); i++)
        padded_decoded.push_back(decoded[i]);
    std::vector<int> encode_2;
    encode(padded_decoded, encode_2);
    if(encoded == encode_2)
        return true;
    else
        return false;
}
