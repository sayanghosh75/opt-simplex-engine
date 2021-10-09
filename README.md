# opt-simplex-engine
Linear Programming Simplex Engine for optimization problems

<!-- This should be the location of the title of the repository, normally the short name -->
# OPT-SIMPLEX-ENGINE - A C++ implementation of the Simplex algorithm for Linear Program optimizations

<!-- Build Status, is a great thing to have at the top of your repository, it shows that you take your CI/CD as first class citizens -->
<!-- [![Build Status](https://travis-ci.org/jjasghar/ibm-cloud-cli.svg?branch=master)](https://travis-ci.org/jjasghar/ibm-cloud-cli) -->

<!-- Not always needed, but a scope helps the user understand in a short sentance like below, why this repo exists -->
## Scope

The purpose of this repository is to provide an example implementation of the Simplex algorithm.


<!-- A more detailed Usage or detailed explaination of the repository here -->
## Usage

The key classes are:

CVariable - implements a variable for use in the linear program context
Cterm - combines the variables to create a term in the form of Coeeficient X Variable ie. ax
Cexpression - combines the terms to form an expression as ax1 + bx2 + cx3
Cerror - Placeholder class to report any errors
Ctableau - The Simplex tableau on which the Simplex operation is executed. Consists of set of terms and also the optimization function

## The Simplex Method

1. The expressions need to be set up with surplus or slack variables. Slack is used for less than / equal to (<=) terms (goal programming) and surplus in greater than / equal to (>=) terms
2. The tableau is set up using two types of expressions - Constraint coefficients and the z-function co-efficients
3. Check if any coefficient in any row is negative (determine feasibility); if so, then run phase 1 solution else start simplex
4. The simplex starts by identifying the pivot column on the basis of the lowest -ve number column (for maximize problems) and +ve number column (for minimize problems)
5. Test / Trial ratio is determined for identifying the pivot row by dividing the answer column with the respective pivot column values to determine the minimum value
6. The pivot element is determined as the intersection of the lowest column and lowest test ratio
7. Pivot the Tableau
8. Repeat entire process from [3] to [7] till optimum or degeneracy conditions are reached


# Slack and Surplus variables
1. Slack variables have a Greater Than Equal To (>=) bound
2. Surplus variables have a Less Than Equal To (<-) bound

# Setting up the Tableau

1. The tableau comprises of the coefficients of the expressions in standard form (including slack/surplus variables as an Equality)
2. The Z-function coefficients and the Answer coefficients are maintained separately to identification and use in pivot identification


# Basic variables

1. The Tableau is set up for m linear equations with n unknowns
2. The associate m variables are called Basic Variables (slack or surplus)
3. The n-m zero variables are called non-basic variables


# Pivoting the Tableau - Pivot Operations

1. Select the column with the largest -ve Coefficient in the z-row as the pivot column
2. Calculate the minimum ratio by dividing the Answer column with the pivot column coefficient
3. Minimum ratio row is selected as the pivot row 
4. Change the chosen pivot to '1' by dividing the pivot row by the pivot number (New pivot row = Current pivot row / Pivot element)
5. Change the rest of the pivot's columns to '0' by adding to each row a suitable multiple of the pivot row (New row = (Current row) - (its pivot column coeeficient) X (New pivot row), including z row

# Optimum Condition(s)

1. For a Maximize problem, no -ve coefficients in the Z-function of the non-basic variables
2. For a Minimize problem, no +ve coefficients in the Z-function of the non-basic variables

# Degeneracy

1. As long as there are fewer than m +ve coefficients in the Z-function (maximize) (m linear expressions in n variables), the solution is considered degenerate
2. As long as there are fewer than m -ve coefficients in the Z-function (minimize) (m linear expressions in n variables), the solution is considered degenerate
3. If Z-function value doesn't change

# Degeneracy indicates redundant constraints

Alternatively, if any of the basic variables have a value of 0 in the solution {Note to myself - the test for basic vs. non-basic is 0 after fnSetBasic runs, this will need modification, if the test for degeneracy is based on the alternate understanding}

# Feasibility

1. If all the variables assume non-negative values the basic solution is feasible

Phase 1 Solution (The 2 phase method)


# Notes:

1. 0/(+1) is considered +ve and 0/(-1) is considered -ve even through they are both numerically equivalent



<!-- License and Authors is optional here, but gives you the ability to highlight who is involed in the project -->
## License & Authors

If you would like to see the detailed LICENSE click [here](LICENSE).

- Author: Sayan A Ghosh <sghosh@sg.ibm.com>
- Maintainer: Sayan A Ghosh <sayan.acharya.ghosh@kyndryl.com>

```text
Copyright:: 2020-2020 IBM, Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
