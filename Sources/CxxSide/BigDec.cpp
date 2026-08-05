//
//  BigDec.cpp
//  BigDecimal
//
//  Created by Desire on 2026-08-04.
//

#include "BigDec.h"
#include <string>
#include <vector>
#include <cstdint>

typedef unsigned char binary;

std::vector<binary> convertInt64ToBinary(int64_t integer) {
    //max num = 1 * 2^(2^64) and that is less than 2^64 which can be divided by 2, 64 times.
    int64_t tInt = integer;
    
    // if the integer is 0 nothing happens
    std::vector<binary> finalBinary(1, 0);
    
    int counter = 0;
    bool finishedBinaryDigits = false;
    
    while (finishedBinaryDigits == false) {
        
        int64_t remainder = tInt % 2;
        
        tInt /= 2;
        
        int binaryDigitToModify = counter % 8;
        int charToModify = counter / 8;
        
        //- if it is to small
        if (charToModify > finalBinary.size()) {
            finalBinary.push_back(0);
        }
        
        
        if (remainder == 1) {
            finalBinary[charToModify] = finalBinary[charToModify] | (1 << (8 - binaryDigitToModify));
        }
        
        counter++;
    }
    
    return finalBinary;
}





struct BigDecimalRaw {
    std::vector<binary> data;
};

struct BigDecimal {
    
    //This is so that we can print it easliy
    BigDecimalRaw aboveDecimal;
    ///This value goes from the decimal in item 0 to the end
    BigDecimalRaw belowDecimal;
    
    
    //to divide and multiply wi will just combined it into 1 value do hte operation then remeber the places
    
    
};



BigDecimal* createBigDecimal(int64_t integer) {
    
    BigDecimal* bD = new BigDecimal();
    
    (*bD).aboveDecimal.data = convertInt64ToBinary(integer);
    (*bD).belowDecimal.data = convertInt64ToBinary(0);
    
    return bD;
}

void destroyBigDecimal(BigDecimal* bD) {
    delete bD;
}

///Please Destroy the two decimals that you give.
BigDecimal addTwoBigDecimals(BigDecimal decimal1, BigDecimal decimal2) {
    
    //this represents the binary that will also be added to above the decimal
    BigDecimal* P_carryDec = createBigDecimal(0);
    
    std::vector<binary> tDecimal1 = decimal1.belowDecimal.data;
    std::vector<binary> tDecimal2 = decimal2.belowDecimal.data;
    //add below decimal so carrys can ve added t oabove decimal.
    //making the decimals the same length.
    int tempCounter = 0;
    while(true) {
        int charToModify = tempCounter / 8;
        
        if (charToModify < 0) { // for 0th element
            break;
        }
        
        if (charToModify > tDecimal1.size() && charToModify > tDecimal2.size()) {
            break;
        } else if (charToModify > tDecimal1.size()) {
            tDecimal1.push_back(0);
        } else if (charToModify > tDecimal2.size()) {
            tDecimal1.push_back(0);
        }
        
        tempCounter -= 1;
    }
    
    
    bool finishedAdding = false;
    unsigned int counter = 0;
    while (finishedAdding == false ) {
        
        //set the bit to
        
        int binaryDigitToModify = 8 - (counter % 8);
        int charToModify = counter / 8;
        
        int dec1Bit = (tDecimal1[charToModify] >> binaryDigitToModify) & 1;
        int dec2Bit = (tDecimal2[charToModify] >> binaryDigitToModify) & 1;
        
        int newVal = dec1Bit + dec2Bit;
        
        if (newVal == 2) {
            
            bool foundNearestZero = false;
            unsigned int nCounter = 0;
            
            while (foundNearestZero == false) {
                
                int binaryDigitToModify = 8 - (nCounter % 8);
                int charToModify = nCounter / 8;
                
                if (charToModify < 0) { // for 0th element
                    
                    
                    foundNearestZero = true;
                }
                
                if (charToModify > tDecimal1.size() && charToModify > tDecimal2.size()) {
                    
                    
                    break;
                } else if (charToModify > tDecimal1.size()) {
                    
                    tDecimal1.push_back(0);
                    
                } else if (charToModify > tDecimal2.size()) {
                    
                }
                
                int bit = (tDecimal1[charToModify] >> binaryDigitToModify) & 1;
                
                
                
                if (bit == 0) {
                    tDecimal1[charToModify] = tDecimal1[charToModify]  | (1 << binaryDigitToModify);
                    foundNearestZero = true;
                }
                
                nCounter -= 1;
            }
            
            
        } else if (newVal == 1) {
            //finalBinary[charToModify] = finalBinary[charToModify] | (1 << (8 - binaryDigitToModify))
            tDecimal1[charToModify] = tDecimal1[charToModify]  | (1 << binaryDigitToModify);
            
        } // we do nothing if they are both 0.
        
        counter++;
        
        
        //checking for the next iteration
        if ((counter / 8) > tDecimal1.size()) {
            finishedAdding = true;
        }
        
        if ((counter / 8) > tDecimal2.size()) {
            finishedAdding = true;
        }
    }
    
    //it wil lreturn decimal1
    decimal1.belowDecimal.data = tDecimal1;
    
    tDecimal1 = decimal1.aboveDecimal.data;
    
    tDecimal2 = decimal2.aboveDecimal.data;
    
    //add above dec
    
    counter = 0;
    
    finishedAdding = false;
    
    while (finishedAdding == false) {
        
        int binaryDigitToModify = 8 - (counter % 8);
        int charToModify = counter / 8;
        
        int dec1Bit = (tDecimal1[charToModify] >> binaryDigitToModify) & 1;
        int dec2Bit = (tDecimal2[charToModify] >> binaryDigitToModify) & 1;
        
        int newVal = dec1Bit + dec2Bit;
        
        if (newVal == 2) {
            
            bool foundNearestZero = false;
            unsigned int nCounter = 0;
            
            while (foundNearestZero == false) {
                
                int binaryDigitToModify = 8 - (nCounter % 8);
                int charToModify = nCounter / 8;
                
                uint64_t tDecimal1Size = tDecimal1.size();
                uint64_t tDecimal2Size = tDecimal2.size();
                
                if (charToModify > tDecimal1Size && charToModify > tDecimal2Size) {
                    foundNearestZero = true;
                    break;
                } else if (charToModify > tDecimal1Size) {
                    tDecimal1.push_back(0);
                } else if (charToModify > tDecimal2Size) {
                    tDecimal2.push_back(0);
                }
                
                int bit = (tDecimal1[charToModify] >> binaryDigitToModify) & 1;
                
                
                
                if (bit == 0) {
                    tDecimal1[charToModify] = tDecimal1[charToModify]  | (1 << binaryDigitToModify);
                    foundNearestZero = true;
                }
                
                nCounter++;
            }
            
        } else if (newVal == 1) {
            tDecimal1[charToModify] = tDecimal1[charToModify]  | (1 << binaryDigitToModify);
        }
        
    }
    
    
    //adding hte carry
    
    BigDecimal* temp = createBigDecimal(0);
    temp->aboveDecimal.data = tDecimal1;
    addTwoBigDecimals(*temp, *P_carryDec);
    
    destroyBigDecimal(temp);
    destroyBigDecimal(P_carryDec);
}

const char* getStringValue(BigDecimal* bD) {
    
}


