#pragma once 
#include <iostream> 
#include <vector> 
 
enum { LEFT, RIGHT, UP, DOWN }; 
 
class SnakeDoes { 
public: 
    SnakeDoes(); 
    ~SnakeDoes(); 
    void move(); 
    void field(); 
    void eat(); 
    void check_dies(); 
 
};