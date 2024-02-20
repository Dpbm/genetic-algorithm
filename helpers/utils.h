#pragma once

#include <iostream>
#include <vector>
#include "../matrix/matrix.h"
#include "../genetic/gene.h"

using std::vector;
using std::string;
using Matrices::Matrix;
using Genes::Gene;

namespace Utils {
  unsigned int get_random_pos(unsigned int max_range, unsigned int factor);
  double random(int start, int end);
  unsigned int random_int(int start, int end);
  bool passed_debounce_time(int last_tick);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
  vector<Gene*>* weights_to_genes_vector(Matrix<Gene>* weights);
  template <typename T> void concat_vectors(vector<T>* vector_a, vector<T>* vector_b, vector<T>* target_vector);
}
