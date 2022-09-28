//
//  arithmetic_encoding1.hpp
//  EncoderInC
//
//  Created by Eugene Min on 7/5/22.
//

#ifndef arithmetic_encoding_hpp
#define arithmetic_encoding_hpp
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class CCDM{
public:
    CCDM(float cwd_length, float p);
    bool encode(std::vector<int> input_raw, std::vector<int>& encoded);
    bool decode(std::vector<int> encoded, std::vector<int>& decoded, int MCDM_input_length);
    float getP();
    int getInputSize();
private:
    float m_p;
    float m_num_0;
    float m_num_1;
    float m_input_length;
    float m_cwd_length;
    
    bool check_input(std::vector<int> input)
    {
        //Cannot exceed or drop below self.input_length
        if(input.size() != m_input_length)
        {
            if (input.size() == 0)
                cout << "Empty Input!";
            cout << "Incongruent Input Size! It should be: " << m_input_length << endl;
            return false;
        }
        
        // Cannot contain bits other than 0 or 1
        for(int i = 0; i < input.size(); i++)
            if (input[i] != 0 && input[i] != 1)
            {
                cout << "Inputs bits contain elements other than 0 or 1" << endl;
                return false;
            }
        return true;
    }
    
    
    bool check_msg(std::vector<int> encoded, float num0)
    {
        if(encoded.size() != m_cwd_length)
        {
            if(encoded.size() == 0)
                cout << "Empty Message!" << endl;
            cout << "Incongruent Message Size! It should be" << m_cwd_length << endl;
            return false;
        }
            
        
        for(int i = 0; i < encoded.size(); i++)
            if (encoded[i] != 0 && encoded[i] != 1)
            {
                cout << "Inputs bits contain elements other than 0 or 1" << endl;
                return false;
            }
    
        // Message not following desired distribution
        if(num0 != m_num_0)
        {
            cout << "Message not following desired distribution!" << endl;
            return false;
        }
        
        return true; 
    }
};
#endif /* arithmetic_encoding1_hpp */
