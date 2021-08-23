#pragma once 
#include<iostream>
#include"learning_pluginlib/Duck.h"

namespace learning_pluginlib{
    class happy_duck: public Duck{
        void initialize(std::string const &name){
            this->_type = "HappyDuck";
            this-> _name = name;
        }
    };
};