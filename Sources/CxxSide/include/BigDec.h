//
//  BigDec.h
//  BigDecimal
//
//  Created by Desire on 2026-08-04.
//

#pragma once

#include <stdint.h>


#ifdef __cplusplus
extern "C"  {
#endif

typedef struct BigDecimal BigDec;


BigDec* createBigDecimal(int64_t integer);

void getBinaryDigitsInABigDecimal(BigDec* bD, uint32_t* numOfDigits);

void getBinaryValue(BigDec* bD, uint32_t* binaryValues);

BigDec* addTwoBigDecimals(BigDec* decimal, BigDec* decimal_2);


#ifdef __cplusplus
}
#endif
