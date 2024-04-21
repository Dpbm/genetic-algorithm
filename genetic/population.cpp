#include <cstdint>
#include <unistd.h>
#include "population.h"
#include "../game/board.h"
#include "../helpers/utils.h"

using Game::Board;
using Utils::random_int;

namespace Genetic{
  Population::Population(uint16_t total, uint8_t board_w, uint8_t board_h, uint8_t total_steps){
    this->total_ind = total;
    this->generate_food_positions(total_steps, board_w, board_h);

    vec2 first_food_pos = this->food_positions.at(0);

    for(size_t i = 0; i < total; i++){
      Individual* ind = new Individual;
      ind->board = new Board(board_w, board_h);
      ind->player = new AIPlayer(board_w, board_h);

      ind->board->set_food_pos(first_food_pos.x, first_food_pos.y); 
      ind->board->add_player(ind->player);
      ind->fitness = 0;
      ind->same_dir_counter = 0;
      ind->index = i;
      ind->las_dir = ind->player->get_dir();

      this->individuals.push_back(ind); 
    }
  }

  void Population::generate_food_positions(uint8_t total, uint8_t w, uint8_t h){
    for(size_t _ = 0; _ < total; _++)
      this->food_positions.push_back(vec2{random_int(0, h-1), random_int(0, w-1)});
      // TODO: refactor this random position to a especialist class or something like this
  }

  Individual* Population::get_best_individual(){
    Individual* best_ind = this->individuals.at(0);
    int64_t best_fit = best_ind->fitness;
    for(Individual* ind: this->individuals){
      if(ind->fitness > best_fit){
        best_fit = ind->fitness;
        best_ind = ind;  
      }
    }
  
    return best_ind;
  }
  
  Individual* Population::get_best_alive_individual(){
    Individual* best_ind = this->individuals.at(0);
    int64_t best_fit = best_ind->fitness;
    for(Individual* ind: this->individuals){
      if(ind->fitness > best_fit && !ind->player->is_dead()){
        best_fit = ind->fitness;
        best_ind = ind;  
      }
    }
  
    return best_ind;
  }

  void Population::update_individual_food_position(Individual *ind){
    vec2 new_food_pos = this->food_positions.at(ind->player->get_score());
    ind->board->set_food_pos(new_food_pos.x, new_food_pos.y);
  }

  void Population::run(){
    uint16_t total_alive = 0;

    for(Individual* ind : this->individuals){
      AIPlayer* player = ind->player;
      Board* board = ind->board;

      if(player->is_dead())
        continue;
      
      total_alive++;

      player->update_input_data(board->get_food(), board->get_width(), board->get_height());
      player->compute_next_dir();
      player->update_dir();
      board->update_player_pos();

      if(player->get_dir() == ind->las_dir){
        ind->same_dir_counter++;
      }else{
        ind->same_dir_counter = 0;
        ind->las_dir = player->get_dir();
      }

      this->compute_fitness(ind);
      this->update_individual_food_position(ind);
    }
  
    if(total_alive == 0)
      this->gen ++;
  }

  uint32_t Population::get_gen(){
    return this->gen;
  }

  void Population::compute_fitness(Individual* ind){
    ind->fitness += ind->player->get_score()*5000;
  
    if(ind->same_dir_counter >= 4)
      ind->fitness += -100;
  }

  Population::~Population(){
    for(Individual* ind : this->individuals){
      delete ind->board;
      delete ind->player;
      delete ind;
    }   
  }
};
