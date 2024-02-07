#pragma once

#include <iostream>
#include <type_traits>
#include <sched.h>
#include "../genetic/gene.h"

using std::enable_if;
using std::is_integral;
using std::is_floating_point;
using std::is_same;
using Genes::Gene;

namespace Matrices {
 
  template <typename T, 
            typename enable_if<is_floating_point<T>::value || 
                               is_integral<T>::value || 
                               is_same<T, Gene>::value>::type* = nullptr> 
    using MatrixTemplate = T;

  template <typename T,
            typename enable_if<is_floating_point<T>::value || is_integral<T>::value>::type* = nullptr> 
    using MatrixRandomTemplate = T;

  template <typename T>
  class Matrix{
    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      void random(int start, int end);
      MatrixTemplate<T>** get_matrix();
      void update_value(unsigned int i, unsigned int j, MatrixTemplate<T> value);
      MatrixTemplate<T> get_position_value(unsigned int i, unsigned int j) const;
      Matrix<MatrixTemplate<T>> operator *(MatrixTemplate<T> scalar);
      Matrix<MatrixTemplate<T>> copy();
      void operator=(const Matrix<MatrixTemplate<T>>& another_matrix);
      Matrix<MatrixTemplate<T>> operator *(const Matrix<MatrixTemplate<T>>& another_matrix);
      unsigned int get_height() const;
      unsigned int get_width() const;
      MatrixTemplate<T>* get_row(unsigned int i) const;
      MatrixTemplate<T>* get_column(unsigned int j) const;
      void show();
      ~Matrix();
      void transpose();
      void map_to_a_single_value(MatrixTemplate<T> value);
    
    private:
      unsigned int width, height;
      MatrixTemplate<T>** matrix;
      void clear_pointers();
      MatrixTemplate<T>** generate_matrix_body(unsigned int width, unsigned int height);
  };

};

