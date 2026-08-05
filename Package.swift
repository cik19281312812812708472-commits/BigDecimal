// swift-tools-version: 6.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "BigDecimal",
    products: [
        .library(name: "BigDecimal", targets: ["BigDecimal"]),
        .library(name: "CxxSide", targets: ["CxxSide"])
      //  .library(name: "d", targets: ["hello"])
    ],
    targets: [
        .target(name: "CxxSide"),
        .target(name: "BigDecimal", dependencies: ["CxxSide"]),
        
            
        
    ],
    
    swiftLanguageModes: [.v6],
    cLanguageStandard: .c17,
    cxxLanguageStandard: .cxx17,
)

//28C239B1-904B-4252-B360-D6E33841B3A6 public headers ("include") directory path for 'C++ Side' is invalid or not contained in the target
