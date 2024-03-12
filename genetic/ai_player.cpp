#include <cstddef>
#include "ai_player.h"
#include "chromosome.h"
#include "../matrix/matrix.h"

using std::size_t;
using Chromosomes::Chromosome;
using Matrices::Matrix;

namespace AIAgent{
  AIPlayer::AIPlayer(){}

  void AIPlayer::setup_choromosome(unsigned int chromosome_size){
    this->chromosome = new Chromosome(chromosome_size);
  }

  Matrix* AIPlayer::get_genes_matrix(unsigned int w, unsigned int h){
    Matrix* genes_matrix = new Matrix(w, h);

    int gene_index = 0;
    for(size_t i = 0; i < h; i++)
      for(size_t j = 0; j < w; j++){
        genes_matrix->update_value(i, j, this->chromosome->get_genes()[gene_index].get_gene_value());        
        gene_index++;
      }

    return genes_matrix;
  }

  Chromosome* AIPlayer::get_chromosome(){
    return this->chromosome;
  } 

  AIPlayer::~AIPlayer(){
    delete this->chromosome;
  }

};