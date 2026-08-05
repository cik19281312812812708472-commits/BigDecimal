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

const uint32_t* getBinaryValue(BigDecimal* bD, uint32_t* numOfDigits);

BigDec* addTwoBigDecimals(BigDecimal* decimal, BigDecimal* decimal_2);


#ifdef __cplusplus
}
#endif
