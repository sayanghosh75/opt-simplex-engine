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
 * main.cpp
 *
 *  Created on: 25-Aug-2016
 *      Author: Sayan
 */

// solver.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "LPTypes.h"
#include "simplex.h"

#define MAX_ITERATIONS  10

int main(int argc, char* argv[])
{
	Ctableau *tableau;
    CSimplex *simplex;
	double x1, x2, x3, x4, x5, x6, x7;
	double C1, C2, C3, C4, C5, C6, C7;
	int iVariable, iConstraint, iIterations;

	x1=x2=x3=0;
	C1=C2=C3=C4=C5=C6=0;

	//LP sizing

	iVariable = 3;
	iConstraint = 4;

	tableau = new Ctableau(iVariable, iConstraint);
    //simplex = new CSimplex(tableau);

    //The following should be put into a table builder funtion within Tableau
	//Assiging labels - Use fnVarLabel to retrieve the label

	tableau->var[0]("Tool & Die");
	tableau->var[1]("Drill Press");
	tableau->var[2]("Lathe");
	tableau->var[3]("Slack Surplus");
	tableau->var[4]("Slack Surplus");
	tableau->var[5]("Slack Surplus");
	tableau->var[6]("Slack Surplus");


	//Setting variable types
	tableau->var[0](NORMAL, GQZ, REAL);
	tableau->var[1](NORMAL, GQZ, REAL);
	tableau->var[2](NORMAL, GQZ, REAL);
	tableau->var[3](SURPLUS, GQZ, REAL);
	tableau->var[4](SURPLUS, GQZ, REAL);
	tableau->var[5](SURPLUS, GQZ, REAL);
	tableau->var[6](SURPLUS, GQZ, REAL);


	//Assignment of coefficients and variables

	//Building the expressions
	//Max 30v1+9v2+16v3
    // Subject to:
    //1) 9v1+3v2+0.5v3 <= 477
    //2) 5v1+4v2+0v3 <= 350
    //3) 3v1+0v2+2v3 <= 150
    //4) 0v1+1v2+0v3 <= 20

	tableau->terms[0][0](-30.0, &(tableau->var[0]));
	tableau->terms[0][1](-9.0, &(tableau->var[1]));
	tableau->terms[0][2](-15.0, &(tableau->var[2]));
	tableau->terms[0][3](0.0, &(tableau->var[3]));
	tableau->terms[0][4](0.0, &(tableau->var[4]));
	tableau->terms[0][5](0.0, &(tableau->var[5]));
	tableau->terms[0][6](0.0, &(tableau->var[6]));


    tableau->terms[1][0](9.0, &(tableau->var[0]));
	tableau->terms[1][1](3.0, &(tableau->var[1]));
	tableau->terms[1][2](0.5, &(tableau->var[2]));
	tableau->terms[1][3](1.0, &(tableau->var[3]));
	tableau->terms[1][4](0.0, &(tableau->var[4]));
	tableau->terms[1][5](0.0, &(tableau->var[5]));
	tableau->terms[1][6](0.0, &(tableau->var[6]));


    tableau->terms[2][0](5.0, &(tableau->var[0]));
	tableau->terms[2][1](4.0, &(tableau->var[1]));
	tableau->terms[2][2](0.0, &(tableau->var[2]));
	tableau->terms[2][3](0.0, &(tableau->var[3]));
	tableau->terms[2][4](1.0, &(tableau->var[4]));
	tableau->terms[2][5](0.0, &(tableau->var[5]));
	tableau->terms[2][6](0.0, &(tableau->var[6]));


    tableau->terms[3][0](3.0, &(tableau->var[0]));
	tableau->terms[3][1](0.0, &(tableau->var[1]));
	tableau->terms[3][2](2.0, &(tableau->var[2]));
	tableau->terms[3][3](0.0, &(tableau->var[3]));
	tableau->terms[3][4](0.0, &(tableau->var[4]));
	tableau->terms[3][5](1.0, &(tableau->var[5]));
	tableau->terms[3][6](0.0, &(tableau->var[6]));


    tableau->terms[4][0](0.0, &(tableau->var[0]));
	tableau->terms[4][1](1.0, &(tableau->var[1]));
	tableau->terms[4][2](0.0, &(tableau->var[2]));
	tableau->terms[4][3](0.0, &(tableau->var[3]));
	tableau->terms[4][4](0.0, &(tableau->var[4]));
	tableau->terms[4][5](0.0, &(tableau->var[5]));
	tableau->terms[4][6](1.0, &(tableau->var[6]));

	//Use the generic expression for defining the z-function also
	//For defining the z-function, set ExType as MN or MX and RHS to 0
	tableau->ex[0](iVariable+iConstraint, tableau->terms[0], MX, 0.0); //Includes surplus variable defined in terms above
	tableau->ex[1](iVariable+iConstraint, tableau->terms[1], LT, 477.0);
    tableau->ex[2](iVariable+iConstraint, tableau->terms[2], LT, 350.0);
    tableau->ex[3](iVariable+iConstraint, tableau->terms[3], LT, 150.0);
    tableau->ex[4](iVariable+iConstraint, tableau->terms[4], LT, 20);

    //Till here for Table Builder


	//Assign value to variables for evaluation of each function - this should be used within the Simplex class
	tableau->var[0] = 0.0;
	tableau->var[1] = 0.0;
	tableau->var[2] = 0.0;
	tableau->var[3] = 0.0;
	tableau->var[4] = 0.0;
	tableau->var[5] = 0.0;
    tableau->var[6] = 0.0;


    //tableau->fntableauset();
    //simplex->fnSimplexInit(tableau);

    simplex = new CSimplex(tableau); //Composite constructor

    iIterations = 0;
    tableau->fnPrintTable();
    while (!(simplex->fnOptimality(tableau)) && ((iIterations <= MAX_ITERATIONS) || (simplex->fnDegeneracy(tableau))))
    {
        printf("Iteration:%d\n\r", iIterations); //Remove from Production
        simplex->fnPivot(tableau);
        tableau->fnPrintTable();
        iIterations++;
    }
    //tableau->fnPrintTable();

    if (simplex->fnOptimality(tableau))
        printf("Optimal\n\r");
    else
        printf("Not-optimal\n\r");
    if (simplex->fnDegeneracy( tableau ))
        printf("Degenerate\n\r");
    else
        printf("Non-degenerate\n\r");


	/*Problem with "operator =" overloading*/
	//var[0] = var[1]; //Legal but breaks due to pointer issues;
	//var[0] * var[1]; //Legal, but where does this store the value needs to be checked whether we should not use *= instead, breaks due to pointer issues
	/*tableau->var[0] = tableau->var[0] * tableau->var[1];*/
	//var[1] = var[1] / var[0];
	//var[2] = var[2] / C3;

	//Extracting the coefficient of each term - used in fntableauset

    tableau->terms[0][0](C1);
	tableau->terms[0][1](C2);
	tableau->terms[0][2](C3);
	tableau->terms[0][3](C4);
	tableau->terms[0][4](C5);
	tableau->terms[0][5](C6);
    tableau->terms[0][6](C7);


	//Extracting the value of each variable

	tableau->var[0](x1);
	tableau->var[1](x2);
	tableau->var[2](x3);
	tableau->var[3](x4);
    tableau->var[4](x5);
    tableau->var[5](x6);
    tableau->var[6](x7);


	//Output - Test cases
	printf("%s%.3G,%.3G,%.3G,%.3G,%.3G,%.3G,%.3G\n\r", "Coefficients:", C1, C2, C3, C4, C5, C6, C7);
	printf("%s%.3G,%.3G,%.3G,%.3G,%.3G,%.3G,%.3G\n\r", "Variable Values:", x1, x2, x3, x4, x5, x6, x7);
	printf("%s%.3G\n\r", "Expression Value (C):", tableau->ex[0].fnExpEval());
	printf("%s%.3G\n\r", "Expression Value:", simplex->fnObjectiveValue(tableau));

	//Evaluating the value of each term
	x1 = tableau->terms[0][0].fnEvalTerm();
	x2 = tableau->terms[0][1].fnEvalTerm();
	x3 = tableau->terms[0][2].fnEvalTerm();


	printf("%s%.3G+%.3G+%.3G=%.3G\n\r", "Term Values:", x1, x2, x3, x1+x2+x3);


	getchar();

    delete simplex;
	delete tableau;
	return 0;

}



