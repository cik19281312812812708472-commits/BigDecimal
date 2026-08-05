//
//  Untitled.swift
//  BigDecimal
//
//  Created by Desire on 2026-08-04.
//

import CxxSide

enum BigDecimalSign {
    case negative
    case positive
}

struct BigDecimal {
    
    var decimal: OpaquePointer
    
    public init(_ value: Int, sign: BigDecimalSign = .positive) {
        
        self.decimal = CxxSide.createBigDecimal(Int64(value))
        
    }
    
    
    
}

