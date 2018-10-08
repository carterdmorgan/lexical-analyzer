//
//  ConversionTools.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/7/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "ConversionTools.h"
#include "Id.h"
#include "Expression.h"
#include "DLString.h"

using namespace std;

class ConversionTools {
public:
    string parameterToString(Id id);
    string parameterToString(Expression expression);
    string parameterToString(DLString dlString);
};
