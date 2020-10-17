# Copyright 2019, 2020. IBM All Rights Reserved.
# #
# # Licensed under the Apache License, Version 2.0 (the "License");
# # you may not use this file except in compliance with the License.
# # You may obtain a copy of the License at
# #
# # https://www.apache.org/licenses/LICENSE-2.0
# #
# # Unless required by applicable law or agreed to in writing, software
# # distributed under the License is distributed on an "AS IS" BASIS,
# # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# # See the License for the specific language governing permissions and
# # limitations under the License.
# #
/*
 * simplex.h
 *
 *  Created on: 25-Aug-2016
 *      Author: Sayan
 */

#include "LPTypes.h" //Need to put the #ifndef into LPTypes.h

#ifndef SIMPLEX_H_
#define SIMPLEX_H_

//
//  simplex.h
//  SolverMac
//
//  Created by Sayan Acharya Ghosh on 27/8/12.
//
//


#ifndef __SolverMac__simplex__
#define __SolverMac__simplex__



//Class needs to determine if the problem is a Maximization or Minimization - this information is available in the expression from ExType
//Tableau ex[0] is always the z-funtion
//Table for simplex in available in Tableau and operations are carried out in that
//


class CSimplex
{
private:
    ExpressionType ExType;
    double dRHS;
    Cterm *pTermList;
    int iPivotColumn, iPivotRow;
    double dMin1, dMin2;

public:
	CSimplex();
	~CSimplex();
    CSimplex(Ctableau *);
    void fnSimplexInit(Ctableau *);
    int fnMinRatioTest(Ctableau *);
    void fnPivot(Ctableau *);
    void fnPhaseI(Ctableau *);
    bool fnFeasible(Ctableau *);
    bool fnOptimality(Ctableau *);
    bool fnDegeneracy(Ctableau *);
    double fnObjectiveValue(Ctableau *);
    void fnSetBasicVariable(Ctableau *);
};

#endif /* defined(__SolverMac__simplex__) */




#endif /* SIMPLEX_H_ */
