#ifndef ISING_HPP
#define ISING_HPP
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Ising {
    public:
        int L_, N_, seed, magnetisation_,sample_;
        double T_, totalenergy_, exp_val_eps_per_cycle_, exp_val_eps_per_cycle_squared_,
        exp_val_m_per_cycle_, exp_val_m_per_cycle_squared_, exp_val_E_per_cycle_,
        exp_val_E_per_cycle_squared_, heatcapacity_per_cycle_, exp_val_M_per_cycle_,
        exp_val_M_per_cycle_squared_, susceptibility_per_cycle_;
        double epsilon_, mag_per_spin_;
        mt19937 generator_;
        vector<double> boltzmann_factors_;
        vector<vector<int>> s_;
        normal_distribution<double> proposal_pdf_;
        uniform_int_distribution<int> lattice_uniform_distribution_, up_or_down_spin_;
        uniform_real_distribution<double> uniform_real_;

      //Ising(int lattice_side, double T, int seed);
      Ising(int lattice_side_length, double T, int seed, int ordered_spin);
      //Ising(vector<vector<int> > s_current, double T, int seed);

      void generate_unordered_lattice();

      void generate_ordered_lattice(int spin);

      vector<vector<int>> run_metropolis_MCMC();

      void calc_energy_of_lattice_state();
      int calc_energy_of_lattice_state(vector<vector<int> > s);

      void calc_tot_magnetization_of_state();
      int calc_tot_magnetization_of_state(vector<vector<int>> s);

      vector<double> calc_boltzmann_factors(double T);

      double mean(double value, int n_cycles);
      double expval_eps(int n_cycles);
      double expval_mag_per_spin(int n_cycles);
      double heat_capacity(int n_cycles);
      double susceptibility(int n_cycles);

      void analytical_2x2(double T);

      void write_parameters_to_file(ofstream& ofile);

      void print();


};
#endif
