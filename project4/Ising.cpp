#include "project4/Ising.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

Ising::Ising(int lattice_side_length, double T, int seed) {
    L_ = lattice_side_length;
    N_ = L_*L_;
    T_ = T;
    //Initalise randomness with Mersenne Twister 19937 random number generator
    generator.seed(seed);
    proposal_pdf_ = normal_distribution(0.0,1.0);
    lattice_uniform_distribution_ = uniform_int_distribution(0, L-1);
    up_or_down_spin_ = uniform_int_distribution(0, 1);

    boltzmann_factors_ = calc_boltzmann_factors(T);

    generate_random_lattice();
    
}

Ising::Ising(std::vector<std::vector<int> > s_current, double T, int seed) {
    L_ = s_current.size();
    N_ = L_*L_;
    T_ = T;
    //Initalise randomness with Mersenne Twister 19937 random number generator
    generator.seed(seed);
    proposal_pdf = normal_distribution(0.0,1.0);
    lattice_uniform_distribution = uniform_int_distribution(0, L-1);
    up_or_down_spin = uniform_int_distribution(0, 1);
    boltzmann_factors = boltzmann_factor(T);
}

void Ising::generate_random_lattice() {
     vector<vector<int>> lattice(L, vector<int>(L, 1));
     for (int i=0; i<L; i++){
        for (int j=0; j<L; j++){
            lattice[i][j] = lattice[i][j] - 2 * up_or_down_spin_(generator); // Generates a 1 or a -1
        }
    }
    s_ = lattice;   
}

std::vector<std::vector<int>>Ising::run_metropolis_MCMC(){
  // running one MC cycle for sampling

  for (int c = 0; c < N; c++){ // one MC cycle; attempt N spin flips
    // flip random spin
    int randRow = rand() % L;
    int randCol = rand() % L;
    s_[randRow][randCol] *= -1;

    // examining surrounding spins to figure out index in boltzmann_factor vector
    // for computing the probability ratio
    int deltaE = s_[randRow][randCol] * 2 * (
                 s_[randRow][(randCol - 1 + L) % L] // Neighbour to the left 
               + s_[randRow][(randCol + 1) % L]; // Neighbour to the right 
               + s_[(randRow + 1) % L][randCol] // Neighbour above
               + s_[(randRow - 1 + L) % L][randCol]) // Neighbour below

    // finding the index to use in Boltzmann
    int index;
    // boltzmann factor depends on flipping a +1 to -1, so the value will have
    // reverse index when a negative spin is flipped to positive.
    if(s_[randRow][randCol] == 1){
      index = 5 - sumofsurroundingspins/2 + 2; // reversing index
    }else{
      index = sumofsurroundingspins/2 + 2;
    }

    // Acceptance ratio
    double probability_ratio = calc_boltzmann_factors[index];
    double r = rand()/RAND_MAX;

    if(r > probability_ratio){ //Rejected spin-flip
      s_[randRow][randCol] *= -1;
    }
    else{
      // Accept spin configuration candidate
      double totalenergy_ = totalenergy_ + deltaE;
      double epsilon = totalenergy_/N;
    }
  }
  return s_;
}

void Ising::alternative_sampling(std::vector<std::vector<int> > s_current, double T){
  // cecilie
  std::vector<double> boltzmann_factors = boltzmann_factor(T);

  double energy_before = calc_tot_energy_of_state(s_current);

  for (int i = 0; i < N; i++){ // one MC cycle
    // flip random spin
    int randRow = rand() % L;
    int randCol = rand() % L;

    s_current[randRow][randCol] *= -1; // flip spin

    double energy_after = calc_tot_energy_of_state(s_current);
    double delta_energy = energy_after - energy_before;
    // ....
  }
}

double Ising::calc_tot_energy_of_state(std::vector<std::vector<int> > s){
  // finding the energy of a particular spin configuration s
  double energy;
  for(int i=1 ; i<L+1 ; i++){ //the first row will be the Lth row
    for(int j=1 ; j<L+1 ; j++){ //the first column will be the Lth column
      int i_index = (i + L)%L;
      int j_index = (j + L)%L;
      energy += s[i_index][j_index]*s[i_index-1][j_index] + s[i_index][j_index]*s[i_index][j_index-1];
    }
  }
  return energy;
}


std::vector<double> Ising::calc_boltzmann_factors(double T){
  double beta = 1. / T;
  vector<double> boltzmann_values;
  boltzmann_values.push_back(exp(-beta*(-8))); // 0 +1 spins
  boltzmann_values.push_back(exp(-beta*(-4))); // 1 +1 spins
  boltzmann_values.push_back(exp(-beta*(0))); // = 1? // 2 +1 spins
  boltzmann_values.push_back(exp(-beta*(4))); // 3 +1 spins
  boltzmann_values.push_back(exp(-beta*(8))); // 4 +1 spins
  return boltzmann_values;
}
