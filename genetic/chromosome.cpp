#include <cstddef>
#include <iostream>
#include "gene.h"
#include "chromosome.h"

using std::size_t;
using std::cout;
using std::endl;
using Genes::Gene;

namespace Chromosomes {
  Chromosome::Chromosome(unsigned int size){
    this->genes = new Gene[size];
    this->total_genes = size;
  }
 
  Chromosome::Chromosome(Gene* genes, unsigned int size){
    this->genes = genes;
    this->total_genes = size;
  }

  void Chromosome::copy_genes(Gene* genes){
    for(size_t i = 0; i < this->total_genes; i++)
      this->genes[i] = genes[i].get_gene_value();
  }

  Gene* Chromosome::get_genes(){
    return this->genes;
  }
  
  void Chromosome::mutate(float rate){
    for(unsigned int i = 0; i < this->total_genes; i++)
      this->genes[i].mutate(rate);
  }
 
  void Chromosome::show(){
    for(unsigned int i = 0; i < this->total_genes; i++)
      cout << this->genes[i].get_gene_value() << " ";
    cout << endl;
  }

  unsigned int Chromosome::get_size(){
    return this->total_genes;
  }
  
  Chromosome::~Chromosome(){
    delete[] this->genes;
  }
}

