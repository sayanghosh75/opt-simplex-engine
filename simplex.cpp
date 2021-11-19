/*
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
*/
/*
 * simplex.cpp
 *
 *  Created on: 25-Aug-2016
 *      Author: Sayan
 */

//
//  simplex.cpp
//  SolverMac
//
//  Created by Sayan Acharya Ghosh on 27/8/12.
//
//

#include "simplex.h"


CSimplex::CSimplex()
{

}

CSimplex::~CSimplex()
{

}

CSimplex::CSimplex(Ctableau *tableau)
{
    tableau->ex[0](pTermList, ExType, dRHS); //Get Z-function details
    switch (ExType)
	{
        case LT:
        case EQ:
        case GT:
        case LQ:
        case GQ:
            //No relevance in z-function
            //Raise exception if encountered
            break;
        case MN:
            //Minimize
            //Check z-Column for +ve coefficients; exception if none
            printf("Minimize Z-function\n\r");//remove from production
            break;
        case MX:
            //Maximize
            //Check z-Column for -ve coefficients; exception if none
            printf("Maximize Z-function\n\r");//remove from production
            break;
        default:
            //No default case to process
            break;
	}
    printf("%s%.3G\n\r", "Simplex Init RHS:", dRHS);
    tableau->fntableauset();
}

void CSimplex::fnSimplexInit(Ctableau *tableau)
{
    tableau->ex[0](pTermList, ExType, dRHS); //Get Z-function details

	switch (ExType)
	{
        case LT:
        case EQ:
        case GT:
        case LQ:
        case GQ:
            //No relevant for z-column
            //Exception if set
            break;
        case MN:
            //Minimize
            //Check z-column for +ve coefficients; exception if none
            printf("Simplex Init - Minimize\n\r");//remove from production
            break;
        case MX:
            //Maximize
            //check z-column for -ve coefficients; exception if none
            printf("Simplex Init - Maximize\n\r");//remove from production
            break;
        default:
            //No default case to process
            //Exception if set
            break;
	}
}


int CSimplex::fnMinRatioTest(Ctableau *tableau)
{
    int iMRT, iRow, iColumn;

    iMRT = 1;
    iColumn = iPivotColumn;

    dMin1 = 0;
    for (iRow = 1; iRow<=tableau->icConstraints; iRow++) //Find the max number in the answer column so that ratio is compared against this
    {
        dMin2 = tableau->dTable[iRow][tableau->icVariables+tableau->icConstraints];
        dMin1 =  dMin2 > dMin1 ? dMin2 : dMin1;
    }
    dMin2 = dMin1;
    for (iRow = 1; iRow<=tableau->icConstraints; iRow++) //iRow is from 1 as the MRT calculation excludes the z-row
    {
        //Calculate the MRT
        //This is RHS divided by PivotColumn values
        if (tableau->dTable[iRow][iPivotColumn] > 0)
        {
            dMin1 = tableau->dTable[iRow][tableau->icVariables+tableau->icConstraints] / tableau->dTable[iRow][iPivotColumn];
            if (dMin1 > 0)
            {
                iMRT = dMin1 < dMin2 ? iRow : iMRT;
                dMin2 = dMin1 < dMin2? dMin1 : dMin2;
            }
        }
    }
    return iMRT;
}


void CSimplex::fnPivot(Ctableau *tableau)
{
    int iColumn, iRow;
    double dPivotElement;

    //Determine the Pivot Column and Row and set it in
    //iPivotColumn and iPivotRow - class Private variables
    //Do the pivoting and then test for feasibility, degeneracy and optimality as part of the simplex
    dMin1=tableau->dTable[0][0];
    dMin2=dMin1;
    iPivotColumn = 0;

    fnSetBasicVariable(tableau); //Set the basic variables and update with values
    //Most -ve z-column coefficient for Maximization
    //Most +ve z-column coefficient for Minimization
    //Break ties by choosing left-most column; use a reducing for loop to accomplish this
    for (iColumn = (tableau->icVariables+tableau->icConstraints); iColumn >= 0; iColumn--)
    {
        switch(ExType)
        {
            case MN:
                dMin1 = ((tableau->dTable[0][iColumn] > dMin2) && (tableau->dTable[0][iColumn] > 0)) ? tableau->dTable[0][iColumn] : dMin2;
                iPivotColumn = dMin1 > dMin2 ? iColumn : iPivotColumn;
                break;
            case MX:
                dMin1 = ((tableau->dTable[0][iColumn] < dMin2 ) && (tableau->dTable[0][iColumn] < 0)) ? tableau->dTable[0][iColumn] : dMin2;
                iPivotColumn = dMin1 < dMin2 ? iColumn : iPivotColumn;
                break;
            default:
                //printf("PivotColumn - Default\n\r");//remove from production
                break;
        }
    }

    iPivotRow = fnMinRatioTest(tableau);
    //Pivot Row and Column determined
    dPivotElement = tableau->dTable[iPivotRow][iPivotColumn];
    printf("%s:%d,%s:%d,%s:%0.2f\n\r", "Pivot Row", iPivotRow, "Pivot Column",iPivotColumn, "Pivot Element",dPivotElement);//Remove from production


    //Insert row operations here
    //Pivot to be set to 1 by dividing Pivot row by Pivot element
    //printf("Into Pivot Row Operations\n\r");//Remove from production
    for (iColumn = 0; iColumn <= (tableau->icVariables+tableau->icConstraints); iColumn++)
    {
        tableau->dTable[iPivotRow][iColumn] = tableau->dTable[iPivotRow][iColumn] / dPivotElement;
    }


    //Change the rest of the pivot's columns to '0' by adding to each row a suitable multiple of the pivot row
    //(New row = (Current row) - (its pivot column coeeficient) X (New pivot row), including z row
    //printf("Into Table Pivot Operations\n\r");//remove from production

    for (iRow = 0; iRow <= tableau->icConstraints; iRow++)
    {
            for (iColumn = 0; iColumn <= (tableau->icVariables+tableau->icConstraints); iColumn++)
            {
                //Skip the pivot row
                if (iRow != iPivotRow)
                {
                    dPivotElement = tableau->dTable[iRow][iPivotColumn];
                    if (iColumn != iPivotColumn) //Don't do the PivotColumn till the end
                    {
                        tableau->dTable[iRow][iColumn] = tableau->dTable[iRow][iColumn]-(dPivotElement*tableau->dTable[iPivotRow][iColumn]);
                    }
                }
            }
        //Do the Pivot Column if it is not the Pivot Row
        if (iRow != iPivotRow)
        {
            dPivotElement = tableau->dTable[iRow][iPivotColumn];
            tableau->dTable[iRow][iPivotColumn] = tableau->dTable[iRow][iPivotColumn]-(dPivotElement*tableau->dTable[iPivotRow][iPivotColumn]);
        }
    }
    fnSetBasicVariable(tableau); //Set the basic variables and update with values
}

void CSimplex::fnPhaseI(Ctableau *tableau)
{
    //To be implemented
}


bool CSimplex::fnFeasible(Ctableau *tableau)
{
    int iColumn, iRow;
    bool bFeasible;

    //1. If all the variables in row[0] assume non-negative values the basic solution is feasible


    bFeasible = false;
    //for (iRow = 0; iRow <= tableau->icConstraints; iRow++)
    {
        iRow = 0;
        for (iColumn = 0; iColumn <= (tableau->icVariables+tableau->icConstraints); iColumn++)
        {
                    bFeasible = tableau->dTable[iRow][iColumn] < 0? (bFeasible && false) : true;
        }
    }

    return bFeasible;
}


bool CSimplex::fnOptimality(Ctableau *tableau)
{
    //For a Maximize problem, no -ve coefficients in the Z-function of the non-basic variables
    //For a Minimize problem, no +ve coefficients in the Z-function of the non-basic variables
    //Basic variables are those which have their columns cleared (except for themselves, which is unitary)
    //LOGIC NEEDS TO BE CHECKED FOR THIS FUNCTION - though in some literature
    //the entire Z row is tested as opposed to only Basic variables
    int iColumn;
    bool bOptimal;

    bOptimal = true;
    iColumn = (tableau->icVariables+tableau->icConstraints-1); //Ignore answer column
    while ( iColumn >= 0 && bOptimal)
    {
        if (tableau->var[iColumn] == 0) //Check if variable is non-basic, will have 0 value set by fnSetBasicVariable
        {
            switch(ExType)
            {
                case MN:
                    bOptimal = tableau->dTable[0][iColumn] < 0 ? (bOptimal && true) : false;
                    break;
                case MX:
                    bOptimal = tableau->dTable[0][iColumn] > 0 ? (bOptimal && true) : false;
                    break;
                default:
                    break;
            }
        }
        iColumn--;
    }
    return bOptimal;
}


bool CSimplex::fnDegeneracy(Ctableau *tableau)
{
    //1. As long as there are fewer than m +ve coefficients in the Z-function (maximize) (m linear expressions in n variables) - degenerate
    //2. As long as there are fewer than m -ve coefficients in the Z-function (minimize) (m linear expressions in n variables) - degenerate
    //3. If Z-function value doesn't change - degenerate - TO BE IMPLEMENTED

    int iColumn, iCountCoeff;
    bool bDegenerate;

    bDegenerate = false;
    iCountCoeff = 0;
    iColumn = (tableau->icVariables+tableau->icConstraints);
    while ( iColumn >= 0 )
    {
        switch(ExType)
        {
            case MN:
                iCountCoeff = tableau->dTable[0][iColumn] <= 0 ? ++iCountCoeff : iCountCoeff;
                break;
            case MX:
                iCountCoeff = tableau->dTable[0][iColumn] >= 0 ? ++iCountCoeff : iCountCoeff;
                break;
            default:
                break;
        }
        iColumn--;
    }

    bDegenerate = iCountCoeff < tableau->icConstraints ? true : false;

    return bDegenerate;
}

double CSimplex::fnObjectiveValue(Ctableau *tableau)
{
    return tableau->dTable[0][tableau->icVariables+tableau->icConstraints];
}


void CSimplex::fnSetBasicVariable(Ctableau *tableau)
{
    int iRow, iColumn, iBasicRow, iBasic, iAnswer;
    bool bIsBasic;

    //Code optimized
    bIsBasic = false;
    iColumn = 0;
    iBasic = 1;
    iAnswer = tableau->icVariables+tableau->icConstraints;
    //printf("%s\n\r", "Finding Basic variables - start"); //Remove from production
    while (iColumn < tableau->icVariables + tableau->icConstraints)
    {
        iBasicRow = iRow = 1; //Row 0 is Z row
        if (tableau->dTable[iRow][iColumn] == 0 || tableau->dTable[iRow][iColumn] == 1)
        {
            bIsBasic = true;
            iBasicRow = tableau->dTable[iRow][iColumn] == 1 ? iRow : iBasicRow;
        }
        else
            bIsBasic = false;
        iRow++; //Check next row onwards
        if (bIsBasic) //Check further if it really is basic
        {
            while (iRow <= tableau->icConstraints)
            {
                if (tableau->dTable[iRow][iColumn] == 0 || tableau->dTable[iRow][iColumn] == 1)
                {
                    bIsBasic = true;
                    iBasicRow = tableau->dTable[iRow][iColumn] == 1 ? iRow : iBasicRow;
                    iRow++;
                }
                else
                {
                    bIsBasic = false;
                    iRow = tableau->icConstraints + 1;
                }
            }
        }
        //If this is a basic variable, take value from answer column else 0
        if (bIsBasic) //Finally check if this really turned out to be a Basic Column
        {
            tableau->var[iColumn] = tableau->dTable[iBasicRow][iAnswer];
            iBasic++;
        }
        else
            tableau->var[iColumn] = 0;
        iColumn++;
    }
}


