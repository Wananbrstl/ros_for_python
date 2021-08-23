#pragma once 
#include<iostream>
#include"learning_pluginlib/Duck.h"

namespace learning_pluginlib{
    class simple_duck : public Duck{
        public:
            void initialize(std::string const & name)
            {
                _name = name;
                _type = "SimpleDuck";
            }
    };
};