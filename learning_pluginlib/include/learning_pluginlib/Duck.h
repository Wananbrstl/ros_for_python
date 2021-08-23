#ifndef DUCK_H
#define DUCK_H

#include<iostream>
#include<string>

namespace learning_pluginlib{
    class Duck{
    public:
        virtual void initialize(std::string const &name) = 0;
        virtual const std::string& get_name() const {return _name;}
        virtual const std::string& get_type() const {return _type;}
        virtual ~Duck(){}
    protected:
        Duck(){}
    protected:
        std::string _name;
        std::string _type;
    };
};
#endif