#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ambient-light.hh"
#include "camera.hh"
#include "direction-light.hh"
#include "object.hh"
#include "parser.hh"
#include "light.hh"
#include "point-light.hh"
#include "list-to-word.hh"
#include "vector3.hh"

class Parser
{
    public:
        using vec = vector::Vector3;

        /* Constructor */
        Parser(std::string file_in);

        /* Methods */
        bool parse();
        void print() const;

        /* Getter */
        Camera camera_get() const;
        std::vector<light::Light*> lights_get() const;
        std::vector<Object> objects_get() const;

    private:
        std::string file_in_;
        Camera camera_;
        std::vector<light::Light*> lights_;
        std::vector<Object> objects_;
};
