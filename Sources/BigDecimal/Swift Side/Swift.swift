//
//  Untitled.swift
//  BigDecimal
//
//  Created by Desire on 2026-08-04.
//

import CxxSide

public enum BigDecimalSign {
    case negative
    case positive
}

public struct BigDecimal: CustomStringConvertible {
    
    var decimal: OpaquePointer
    
    public init(_ value: Int, sign: BigDecimalSign = .positive) {
        
        self.decimal = CxxSide.createBigDecimal(Int64(value))
        
    }
    
    public init(decimalPointer: OpaquePointer) {
        self.decimal = decimalPointer
    }
    
    public var description: String {
        
        var count: UInt32 = 0;
        
        CxxSide.getBinaryDigitsInABigDecimal(decimal, &count)
        
        var array = [UInt32](repeating: 0, count: Int(count))

        array.withUnsafeMutableBufferPointer { ptr in
            CxxSide.getBinaryValue(decimal, ptr.baseAddress!)
        }
        
        return array.description
    }
    
    
    public static func + (lhs: BigDecimal, rhs: BigDecimal) -> BigDecimal {
        
        var Decimal = CxxSide.createBigDecimal(0)
        Decimal = CxxSide.addTwoBigDecimals(lhs.decimal, rhs.decimal)
        
        return BigDecimal(decimalPointer: Decimal!)
    }
    

    
}

