#include "SnakeDoes.h" 
 
/*void SnakeDoes::move() 
{ 
  
}*/ 
void SnakeDoes::field() { 
 int width = 36; 
 int height = 18; 
 for (int j = 0; j < width - 1; j++) 
  std::cout << "--"; 
 std::cout << "-" << std::endl; 
 
 for (int i = 1; i < height; ++i) 
 { 
  for (int j = 0; j < width; ++j) 
  { 
   if (j == 0 || j == width - 1) 
    std::cout << "| "; 
   else 
    std::cout << "  "; 
  } 
  std::cout<<std::endl; 
 } 
 for (int j = 0; j < width - 1; j++) 
  std::cout << "--"; 
 std::cout << "-" << std::endl; 
 
 std::random_access_iterator_tag(.); 
 
} 
void SnakeDoes::check_dies(bool q) { 
 if (q == true) 
  std::cout << "Game Over"; 
 else 
  SnakeDoes::move(); 
}