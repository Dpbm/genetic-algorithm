#include <cmath>
#include <cstddef>
#include <cstdlib>
#include "ai_player.h"
#include "../genetic/chromosome.h"
#include "../matrix/matrix.h"
#include "../machine/activation.h"

using std::sqrt;
using std::pow;
using std::size_t;
using Chromosomes::Chromosome;
using Matrices::Matrix;

namespace Players{
  AIPlayer::AIPlayer(){}


  void AIPlayer::setup_agent(){ 
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(4);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(Machine::tanh);
    this->nn->get_layer(2)->set_activation_function(Machine::softmax);
    this->input_layer->set_values(this->input_data);
    
    // get the chromosome_size based on the total weights
    uint16_t chromosome_size = 0;
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      Weights* weights = this->nn->get_weight(weight_i);
      chromosome_size += weights->get_width()*weights->get_height();
    }
      
    this->chromosome = new Chromosome(chromosome_size);
    
    // load the genes into the weights
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      uint8_t w = this->nn->get_weight(weight_i)->get_width();
      uint8_t h = this->nn->get_weight(weight_i)->get_height();

      this->nn->get_weight(weight_i)->load_weights(
        this->get_genes_matrix(w, h)
      );
    }
  }

  Matrix* AIPlayer::get_genes_matrix(unsigned int w, unsigned int h){
    Matrix* genes_matrix = new Matrix(w, h);
    int16_t gene_index = 0;
    for(size_t i = 0; i < h; i++)
      for(size_t j = 0; j < w; j++){
        genes_matrix->update_value(i, j, this->chromosome->get_genes()[gene_index].get_gene_value());        
        gene_index++;
      }

    return genes_matrix;
  }

  void AIPlayer::update_input_data(uint16_t fx, uint16_t fy){
    double hip = sqrt(pow(fx-this->get_x(),2) + pow(this->get_y()-fy,2));
    // double angle = hip == 0 ? 0 : acos(abs(fx-this->get_x())/hip); 
    // 
    // if(fx > this->get_x() && fy > this->get_y())
    //   angle += (3*PI)/2;
    // else if(fx < this->get_x() && fy < this->get_y())
    //   angle += PI/2;
    // else if(fx < this->get_x() && fy > this->get_y())
    //   angle += PI;
    // else if(fy == this->get_y() && this->get_x() < fx)
    //   angle = 0;
    // else if(fy == this->get_y() && this->get_x() < fx)
    //   angle = PI;
    // else if(this->get_x() == fx && this->get_y() > fy)
    //   angle = PI/2;
    // else if(this->get_x() == fx && this->get_y() < fy)
    //   angle = (3*PI)/2;
    
    this->input_data->update_value(0, 0, (fx-this->get_x())%50);
    this->input_data->update_value(0, 1, (fy-this->get_y())%50);
    this->input_data->update_value(0, 2, 1);
  }

  Chromosome* AIPlayer::get_chromosome(){
    return this->chromosome;
  } 

  AIPlayer::~AIPlayer(){
    delete this->chromosome;
    delete this->nn;
  }
};
