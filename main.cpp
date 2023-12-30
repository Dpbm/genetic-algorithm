#include "constants.h"
#include "gui.h"
#include "player.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <cstring>

int main(){
  /**std::cout << "---Simple GA test---" << std::endl;
  
  unsigned int size = 10;
  Chromosomes::Chromosome chromosome = Chromosomes::Chromosome(size);
  chromosome.show();  

  std::cout << "---first---" << std::endl;
  chromosome.show();

  chromosome.mutate(0.5);
  std::cout << "---second---" << std::endl;
  chromosome.show();

  std::vector<Genes::Gene> genes = chromosome.slice(3, 8);
  for(Genes::Gene gene : genes){
    std::cout << "sliced : " << gene.get_gene_value() << std::endl;
  } 
*/

 /** unsigned int size = 10;
  Chromosomes::Chromosome ch1 = Chromosomes::Chromosome(size);
  Chromosomes::Chromosome ch2 = Chromosomes::Chromosome(size);

  std::cout << "---Chromossome 1---" << std::endl;
  ch1.show();
  std::cout << "---Chromossome 2---" << std::endl;
  ch2.show();
  std::cout << "crossover"<<std::endl;
  
  unsigned int start = 3;
  unsigned int end = 6;
  std::vector<Genes::Gene> slice = ch1.slice(start,end);
  for(Genes::Gene gene :slice){
    std::cout <<gene.get_gene_value() << " ";
  }
  std::cout << std::endl;


  ch2.crossover(start, end, slice);
  std::cout << "CH1" <<std::endl;
  ch1.show();

  std::cout << "CH2" <<std::endl;
  ch2.show();
**/

  /**
  Populations::Population population = Populations::Population(10, 5, 100);
  population.show();
  */
  
  char *title = (char*) malloc(5*sizeof(char));
  strcpy(title, "test");
  GUI::Game game = GUI::Game(title, WIDTH, HEIGHT);
  game.set_food_pos();
  
  SDL_Event event;

  int last_moviment_time = 0;

  do{

    event = game.get_event();
    Players::Player* player = game.get_player();

    if(event.type == SDL_KEYDOWN && SDL_GetTicks() - last_moviment_time >= 100){
      switch(event.key.keysym.sym){
        case SDLK_UP:
          player->move_up();
          break;
        case SDLK_DOWN:
          player->move_down();
          break;
        case SDLK_LEFT:
          player->move_left();
          break;
        case SDLK_RIGHT:
          player->move_right();
          break;
        default:
          break;
      }
      last_moviment_time = SDL_GetTicks();
    }

    game.clear_screen();
    game.draw_food();
    game.render_player();
    game.show();

  }while(event.type != SDL_QUIT);

  free(title);


  return 0;
}
