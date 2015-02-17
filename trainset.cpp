/* Gear Combinator
 *
 * Given a pitch and a list of gears, will calculate (A/B)*(C/D) permutations
 * and give threads / feeds.
 *
 * Copyright (c) 2015, Adam Carmichael <carneeki@carneeki.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <iomanip>
#include <fstream>
//#include <string>
#include <set>


#include "train.cpp"
#include "trainset.h"

int main(int argc, char* argv[])
{
  if(argc != 6)
  {
    std::cerr << "Usage: " << argv[0]
              << " <gear library> <output file> <M gear> <N gear> <pitch>"
              << std::endl;
    return 1;
  }

  int m,n,a,b,c,d;  // gear sizes
  int i=0;          // output iterator
  int pitch;        // leadscrew pitch
  char buf[255];    // input buffer
  FILE * pFile;     // output file pointer

  std::fstream in;  // gear library file
  std::fstream out; // gear output table
  std::multiset<int> gears;  // gear library list
  std::multiset<Train> trains = std::multiset<Train>();

  in.open(argv[1], std::fstream::in);
  //out.open(argv[2], std::fstream::out);
  pFile = fopen(argv[2], "w");

  // fill gears list
  for(std::string line; std::getline(in, line);)
    gears.insert(atoi(line.c_str()));
  in.close();

  m = atoi(argv[3]);
  n = atoi(argv[4]);
  pitch = atoi(argv[5]);

  // print out gears
  fprintf(pFile, "Using gear library\n");
  //out << "Using gear library:" << std::endl;
  for(std::multiset<int>::iterator it = gears.begin(); it != gears.end(); ++it )
  {
    fprintf(pFile, "%d\n",*it);
    //out << *it << std::endl;
  }
  //out << "===============================================================================" << std::endl;
  fprintf(pFile,"===============================================================================\n");

  // compute ALL the gears!
  trains = compute(m, n, pitch, gears);

  // print the output
  for(std::set<Train>::iterator it = trains.begin(); it!=trains.end(); ++it)
  {
    //out << std::setw(7) << std::setfill('0') << i << " " << it->print();
    //it->fakeprint();
    fprintf(pFile,
            "%07d %d/%d * %d/%d * %d/%d => %.4fmm | %.4f TPI\n",
            i,
            it->M, it->N,
            it->A, it->B, it->C, it->D,
            it->travel, it->tpi );
    i++;
  }

  return 0;
} /* int main() */

/*
 * compute all trainset permutations
 */
std::multiset<Train> compute(int m, int n, int pitch, std::multiset<int> gears)
{
  std::multiset<Train> result;
  unsigned int ii = 0, ij = 0, ik = 0, il = 0;

  // process all A gears
  for(std::multiset<int>::iterator i = gears.begin(); i != gears.end(); ++i)
  {
    ij = ik = il = 0;
    // process all B gears
    for(std::multiset<int>::iterator j = gears.begin(); j != gears.end(); ++j)
    {
      ik = il = 0;
      if( ij != ii )
      {
        // process all C gears
        for(std::multiset<int>::iterator k = gears.begin(); k != gears.end(); ++k)
        {
          il = 0;
          if( ik != ii && ik != ij )
          {
            // process all D gears
            for(std::multiset<int>::iterator l = gears.begin(); l != gears.end(); ++l)
            {
              if( il != ii && il != ij && il != ik )
              {
                result.insert(Train(*i,*j,*k,*l,m,n,pitch));
              } // if( il != ii && il != ij && il != ik )
              il++;

            } // for() D gears
          } // if( ik != ii && ik != ij )
          ik++;

        } // for() C gears
      } // if( ij != ii)
      ij++;

    } // for() B gears
    ii++;

  } // for() A gears
  return result;
} /* std::multiset<Train> compute(std::multiset<int> gears) */
