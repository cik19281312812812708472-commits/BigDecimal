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

struct BigDecimal: CustomStringConvertible {
    
    var decimal: OpaquePointer
    
    public init(_ value: Int, sign: BigDecimalSign = .positive) {
        
        self.decimal = CxxSide.createBigDecimal(Int64(value))
        
    }
    
    public init(decimalPointer: OpaquePointer) {
        self.decimal = decimalPointer
    }
    
    public var description: String {
        
        var count: UInt32 = 0
        
        let pointer = CxxSide.getBinaryValue(decimal, &count)
        
        let array: [UInt32] = Array(
            UnsafeBufferPointer(
                start: pointer,
                count: Int(count)
            )
        )
        
        return array.description
    }
    
    
    public static func + (lhs: BigDecimal, rhs: BigDecimal) -> BigDecimal {
        
        var Decimal = CxxSide.createBigDecimal(0)
        Decimal = CxxSide.addTwoBigDecimals(lhs.decimal, rhs.decimal)
        
        return BigDecimal(decimalPointer: Decimal!)
    }
    

    
}

