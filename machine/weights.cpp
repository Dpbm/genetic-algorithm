#include <sstream>
#include "weights.h"
#include "../matrix/matrix.h"
#include "../helpers/utils.h"

using Matrices::Matrix;
using std::string;
using std::stringstream;
using Utils::append_to_file;

namespace Machine{
  Weights::Weights(unsigned int first_layer_size, unsigned int second_layer_size){
    this->width = first_layer_size;
    this->height = second_layer_size;
    this->weights = new Matrix(first_layer_size, second_layer_size);
  }
  
  void Weights::load_weights(Matrix* weights){
    if(this->weights != nullptr)
      delete this->weights;
    this->width = weights->get_width();
    this->height = weights->get_height();
    this->weights = weights;
  }

  void Weights::save_weights(string filename){
    stringstream header;
    header << this->width << "," << this->height << "." << "\n"; 
    
    append_to_file(filename, header.str());

    for(unsigned int i = 0; i < this->height; i++){
      for(unsigned int j = 0; j < this->width; j++){
        stringstream data;
        data << this->weights->get_position_value(i, j) << (j+1 < this->width ? "," : ".");
        append_to_file(filename, data.str());
      }

      append_to_file(filename, "\n");
    }
  }

  Matrix *Weights::get_weights(){
    return this->weights;
  }

  Weights::~Weights(){ 
    delete this->weights;
  }

  unsigned int Weights::get_height(){
    return this->height;
  }
  
  unsigned int Weights::get_width(){
    return this->width;
  }
}
