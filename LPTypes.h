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
 * LPTypes.h
 *
 *  Created on: 25-Aug-2016
 *      Author: Sayan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>


#ifndef LPTYPES_H_
#define LPTYPES_H_


#ifndef __SolverMac__LPTypes__
#define __SolverMac__LPTypes__


#define MAX_LABEL_SIZE 40

enum VariableType {NORMAL, SLACK, SURPLUS};
enum VariableBound {LQZ, GQZ, UNB};
enum ExpressionType {LT, EQ, GT, LQ, GQ, MN, MX};
enum VariablePrec {INTEGER, REAL};

//NORMAL - Normal variable
//SLACK - SLACK variable
//SURPLUS - SURPLUS variable
//LQZ - Less Than Equal Zero variable bound
//GQZ - Greater Than Equal Zero variable bound
//UNB - Unbounded variable
//INTEGER - Takes whole / integer numbers
//REAL - Takes real numbers
//LT - Less Than
//EQ - Equal
//GT - Greater Than
//LQ - Less Than Equal
//GQ - Greater Than Equal
//MN - Minimize
//MX - Maximise

class CVariable
{
protected:
	double dVar;
	char *szlabel;
	VariableType VarType;
	VariableBound VarBound;
    VariablePrec VarPrec;

public:
	CVariable();
	CVariable(VariableType VType);
	CVariable(double dVal);
	~CVariable();
	/*
	//These two operator overloads may not be required
	CVariable operator = (CVariable &OVariable);
	CVariable operator = (CVariable *OVariable);
	 */
	void operator = (double dVal);
	CVariable &operator () (double &dVal);
	CVariable operator + (CVariable &OVariable);
	CVariable operator + (double dVal);
	CVariable operator + (CVariable* pVariable);
	CVariable operator - (CVariable &OVariable);
	CVariable operator - (double dVal);
	CVariable operator - (int iVal);
	CVariable operator * (CVariable &OVariable);
	CVariable operator * (double dVal);
	CVariable operator * (int iVal);
	CVariable operator / (CVariable &OVariable);
	CVariable operator / (double dVal);
	CVariable operator / (int iVal);
    bool operator == (VariableType VType); //Define the == operator for testing variable type
    bool operator == (double dVal); //Define the == operator for testing variable type

	//Operator to define LP variable type
	CVariable &operator () (VariableType VType, VariableBound VBound, VariablePrec VPrec);
	CVariable &operator () (const char *dszlabel);
	//Also define a function to return the variable label to use in a window
	char *fnVarLabel();

};


class Cterm
{
protected:
	double dCoef;
	CVariable *OVar;

public:
	Cterm();
	~Cterm();
	void operator = (double &dVal);
	void operator = (double dVal);
	void operator = (CVariable *pVariable);
	void operator = (Cterm *pTerm);
	//Operator to export the coefficient value
	Cterm &operator () (double &dCoefficient);
	Cterm &operator () (double dCoefficient, CVariable *pVariable);
	//fnEvalTerm returns the value of the term
	double fnEvalTerm(void);
};

class Cexpression
{
private:
		ExpressionType ExType;

protected:
		Cterm *pTermList;
		double dRHS;
		int iNumTerms;

public:
	Cexpression();
	~Cexpression();
	Cexpression &operator () (int iCountTerms, Cterm *pTerms, ExpressionType ET, double dRight);
    Cexpression &operator () (Cterm *pTerms, ExpressionType &ET, double &dRight);
    Cexpression &operator () (double &dRight);
	double fnExpEval();
};


class Cerror
{

public:
    Cerror();
    ~Cerror();
};

class Ctableau
{
private:
	double **dTable; //dtable will not match up with LP Variables and their types and bounds, need to review implementation of this
    int icVariables, icConstraints;

public:
	Ctableau();
	~Ctableau();
    Ctableau(int iVariables, int iConstraints);
    Cterm **terms;
	CVariable *var;
	Cexpression *ex;
	Ctableau operator () (int iVariables, int iConstraints);
    void fntableauset();
    void fnPrintTable();
    friend class CSimplex;

};


class CGraphtableau
{
private:
    double **dTable;

public:
    CGraphtableau();
    ~CGraphtableau();

};

#endif



#endif /* LPTYPES_H_ */
