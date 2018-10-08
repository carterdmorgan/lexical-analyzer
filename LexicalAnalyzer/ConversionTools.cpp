//
//  ConversionTools.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/7/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "ConversionTools.h"

string ConversionTools::parameterToString(Id id) {
    return id.constant;
}

string ConversionTools::parameterToString(Expression expression) {
    return "(" + expression.leftParameter->toString() + expression.exOperator.constant + expression.rightParameter->toString() + ")";
}

string ConversionTools::parameterToString(DLString dlString) {
    return dlString.constant;
}
