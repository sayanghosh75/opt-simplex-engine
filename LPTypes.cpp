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
 * LPTypes.cpp
 *
 *  Created on: 25-Aug-2016
 *      Author: Sayan
 */

#include "LPTypes.h"

CVariable::CVariable()
{
    VarType = NORMAL;
    szlabel = new char [MAX_LABEL_SIZE];
}


CVariable::CVariable(VariableType VType)
{
    VarType = VType;
    szlabel = new char [MAX_LABEL_SIZE];
    szlabel[0] = NULL;
}

CVariable::CVariable(double dVal)
{
	dVar = dVal;
	szlabel = new char [MAX_LABEL_SIZE];
}

CVariable::~CVariable()
{
	delete szlabel;
}

/*
//See note for the below two operator overloads
CVariable CVariable::operator = (CVariable &OVariable)
{
dVar = OVariable.dVar;
VarType = OVariable.VarType;
if (strlen(OVariable.szlabel) <= 0)
	strcpy(szlabel, OVariable.szlabel);
	return OVariable;
}

CVariable CVariable::operator = (CVariable *OVariable)
{
	dVar = OVariable->dVar;
	VarType = OVariable->VarType;
	if (strlen(OVariable->szlabel) <= 0)
		strcpy(szlabel, OVariable->szlabel);
	return *OVariable;
}
*/

void CVariable::operator = (double dVal)
{
    switch (VarPrec)
    {
        case INTEGER:
            dVar = (int)dVal; //convert to int
            break;
        case REAL:
            dVar = dVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
}

CVariable &CVariable::operator () (double &dVal)
{
	dVal = dVar;
	return *this;
}

CVariable CVariable::operator + (CVariable &OVariable)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar+OVariable.dVar); //convert to int
            break;
        case REAL:
            dTemp = dVar+OVariable.dVar;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
    //return CVariable(dVar+OVariable.dVar);
	return CVariable(dTemp);
}


CVariable CVariable::operator + (CVariable* pVariable)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar+pVariable->dVar); //convert to int
            break;
        case REAL:
            dTemp = dVar+pVariable->dVar;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar+pVariable->dVar);
    return CVariable(dTemp);
}

CVariable CVariable::operator + (double dVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar+dVal); //convert to int
            break;
        case REAL:
            dTemp = dVar+dVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar+dVal);
    return CVariable(dTemp);
}


CVariable CVariable::operator - (CVariable &OVariable)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar-OVariable.dVar); //convert to int
            break;
        case REAL:
            dTemp = dVar-OVariable.dVar;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar-OVariable.dVar);
    return CVariable(dTemp);
}


CVariable CVariable::operator - (double dVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar-dVal); //convert to int
            break;
        case REAL:
            dTemp = dVar-dVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar-dVal);
    return CVariable(dTemp);
}

CVariable CVariable::operator - (int iVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar)-iVal; //convert to int
            break;
        case REAL:
            dTemp = dVar-iVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar-iVal);
    return CVariable(dTemp);
}

CVariable CVariable::operator * (CVariable &OVariable)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar*OVariable.dVar); //convert to int
            break;
        case REAL:
            dTemp = dVar*OVariable.dVar;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar*OVariable.dVar);
    return CVariable(dTemp);
}

CVariable CVariable::operator * (double dVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar*dVal); //convert to int
            break;
        case REAL:
            dTemp = dVar*dVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar*dVal);
    return CVariable(dTemp);
}

CVariable CVariable::operator * (int iVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar)*iVal; //convert to int
            break;
        case REAL:
            dTemp = dVar*iVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar*(double)iVal);
    return CVariable(dTemp);
}

CVariable CVariable::operator / (CVariable &OVariable)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar/OVariable.dVar); //convert to int
            break;
        case REAL:
            dTemp = dVar/OVariable.dVar;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar/OVariable.dVar);
    return CVariable(dTemp);
}

CVariable CVariable::operator / (double dVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar/dVal); //convert to int
            break;
        case REAL:
            dTemp = dVar/dVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar/dVal);
    return CVariable(dTemp);
}

CVariable CVariable::operator / (int iVal)
{
    double dTemp;
    switch (VarPrec)
    {
        case INTEGER:
            dTemp = (int)(dVar)/iVal; //convert to int
            break;
        case REAL:
            dTemp = dVar/(double)iVal;
            break;
    }
    switch (VarBound)
    {
        case LQZ:
            //Insert error processing code here
            break;
        case GQZ:
            //Insert error processing code here
            break;
        case UNB:
            //Insert error processing code here
            break;
    }
	//return CVariable(dVar/(double)iVal);
    return CVariable(dTemp);
}

CVariable &CVariable::operator () (VariableType VType, VariableBound VBound, VariablePrec VPrec)
{
    VarType = VType;
    VarBound = VBound;
    VarPrec = VPrec;
    return *this;

}

CVariable &CVariable::operator () (const char *dszlabel)
{

    strcpy(szlabel, dszlabel);
    return *this;
}

bool CVariable::operator == (VariableType VType)
{
    return VType == VarType ? true : false;
}

bool CVariable::operator == (double dVal)
{
    return dVal == dVar ? true : false;
}


char *CVariable::fnVarLabel()
{
	return szlabel;
}

//Cterm method implementations

Cterm::Cterm()
{
    OVar = NULL;
}

Cterm::~Cterm()
{
}

void Cterm::operator = (double &dVal)
{
	*OVar = dVal;
}

void Cterm::operator = (double dVal)
{
	*OVar = dVal;
}

void Cterm::operator = (CVariable *pVariable)
{
	OVar = pVariable;
}

void Cterm::operator = (Cterm *pTerm)
{
	OVar = pTerm->OVar;
	dCoef = pTerm->dCoef;
}

Cterm &Cterm::operator () (double &dCoefficient)
{
	dCoefficient = dCoef;
	return *this;
}

Cterm &Cterm::operator () (double dCoefficient, CVariable *pVariable)
{
	dCoef = dCoefficient;
	OVar = pVariable;
	return *this;
}

double Cterm::fnEvalTerm(void)
{
	double dVar;
	(*OVar)(dVar);
    if (((*OVar) == SLACK) || ((*OVar) == SURPLUS))
    {
        dVar *= 0;
    }
    else
        dVar *= dCoef;
    return dVar;
}

Cexpression::Cexpression()
{
pTermList = NULL;
}

Cexpression::~Cexpression()
{
}

Cexpression &Cexpression::operator () (int iCountTerms, Cterm *pTerms, ExpressionType ET, double dRight)
{
	ExType = ET;
	dRHS = dRight;
	pTermList = pTerms;
	iNumTerms = iCountTerms;
	return *this;
}

Cexpression &Cexpression::operator () (Cterm *pTerms, ExpressionType &ET, double &dRight)
{
    pTerms = pTermList;
    dRight = dRHS;
    ET = ExType;
    return *this;
}

Cexpression &Cexpression::operator () (double &dRight)
{
    dRight = dRHS;
    return *this;
}


double Cexpression::fnExpEval()
{
	int iCount;
	double dRetVal = 0.00;

	for (iCount = 0; iCount < iNumTerms; iCount++)
		dRetVal += (pTermList[iCount]).fnEvalTerm();

	return dRetVal;
}


Cerror::Cerror()
{

}

Cerror::~Cerror()
{

}


Ctableau::Ctableau()
{
}

Ctableau::~Ctableau()
{
	delete [] dTable;
    delete [] ex;
	delete [] terms;
	delete [] var;
}

Ctableau::Ctableau(int iVariables, int iConstraints)
{
	int iGeneral;

	dTable = new double *[iConstraints+1];
    var = new CVariable[iVariables+iConstraints];
	terms = new Cterm *[iConstraints+1]; // Allocate new pointers of type Cterm
	ex = new Cexpression [iConstraints+1];

	for (iGeneral = 0; iGeneral <= iConstraints; iGeneral++)
    {
		dTable[iGeneral] = new double [iVariables+iConstraints]; //Tableau has all variables and the answer column
        terms[iGeneral] = new Cterm [iVariables + iConstraints]; //All the terms in the LP including slack/surplus variables
    }
    icVariables = iVariables;
    icConstraints = iConstraints;
}


Ctableau Ctableau::operator () (int iVariables, int iConstraints)
{
    //This method needs to be redefined from earlier purposes
	return *this;
}



void Ctableau::fntableauset()
{
    int iColumn, iRow;

    for (iRow = 0; iRow <= icConstraints; iRow++)
    {
        for (iColumn = 0; iColumn <= (icVariables+icConstraints); iColumn++)
        {
            //The following should come from expressions
            terms[iRow][iColumn](dTable[iRow][iColumn]);
        }
        ex[iRow](dTable[iRow][iColumn-1]); //Set the answer column from expressions
    }
}

void Ctableau::fnPrintTable()
{
    int iColumn, iRow;

    for (iRow = 0; iRow <= icConstraints; iRow++)
    {
        printf("Row %d: ", iRow);
        for (iColumn = 0; iColumn <= (icVariables+icConstraints); iColumn++)
        {
            printf("%4.3G,", dTable[iRow][iColumn]);
        }
        printf("\n\r");
    }

}


CGraphtableau::CGraphtableau()
{

}

CGraphtableau::~CGraphtableau()
{
    delete [] dTable;
}



