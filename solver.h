#ifndef SOLVER_H
#define SOLVER_H

#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include <mpi.h>
#include <unistd.h>



/************ Sequential solving function for nqueen*****************

 * *****************************************************************/

void seq_solver(unsigned int n, unsigned int exit_on_first, std::vector<std::vector<unsigned int> >& all_solns);





/************ Master function for parallel nqueen*****************

 * *****************************************************************/
void nqueen_master( unsigned int n,
                    unsigned int k,
                    unsigned int exit_on_first,
                    std::vector<std::vector<unsigned int> >& all_solns);







/************ Worker function for parallel nqueen*****************
 
 * *****************************************************************/
void nqueen_worker( unsigned int n,
                    unsigned int k,
                    unsigned int exit_on_first);



#endif // SOLVER_H
