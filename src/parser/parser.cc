#include "parser.hh"

Parser::Parser(std::string file_in) : file_in_(file_in)
{}

bool
Parser::parse()
{
    std::ifstream file_in;
    file_in.open(file_in_);
    if (file_in.is_open() == false)
    {
        std::cerr << "Raytracer: Failed to parse the input file: file not found" << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file_in, line))
    {
        if (line.size() == 0)
            continue;
        auto list_word = sentence_to_list(line);
        if (list_word.at(0) == "camera")
        {
            vec pos = vec(std::stof(list_word.at(3)), std::stof(list_word.at(4)), std::stof(list_word.at(5)));
            vec vec_u = vec(std::stof(list_word.at(6)), std::stof(list_word.at(7)), std::stof(list_word.at(8)));
            vec vec_v = vec(std::stof(list_word.at(9)), std::stof(list_word.at(10)), std::stof(list_word.at(11)));
            camera_ = Camera(std::stoi(list_word.at(1)), std::stoi(list_word.at(2)), pos, vec_u, vec_v, std::stof(list_word.at(12)));
        }
        else if (list_word.at(0) == "a_light")
        {
            auto light = light::AmbientLight(std::stof(list_word.at(1)), std::stof(list_word.at(2)), std::stof(list_word.at(3)));
            lights_.push_back(light);
        }
        else if (list_word.at(0) == "d_light")
        {
            auto dir = vec(std::stof(list_word.at(4)), std::stof(list_word.at(5)), std::stof(list_word.at(6)));
            auto light = light::DirectionLight(std::stof(list_word.at(1)), std::stof(list_word.at(2)), std::stof(list_word.at(3)), dir);
            lights_.push_back(light);
        }
        else if (list_word.at(0) == "p_light")
        {
            auto pos = vec(std::stof(list_word.at(4)), std::stof(list_word.at(5)), std::stof(list_word.at(6)));
            auto light = light::PointLight(std::stof(list_word.at(1)), std::stof(list_word.at(2)), std::stof(list_word.at(3)), pos);
            lights_.push_back(light);
        }
        else if (list_word.at(0) == "object")
        {
            auto obj = Object(std::stoi(list_word.at(1)));
            if (!std::getline(file_in, line))
                break;
            while (line.size() == 0)
            {
                if (std::getline(file_in, line))
                   // FIXME: end of file | object
            }
            list_word = sentence_to_list(line);
            while (list_word.at(0) != "v" && list_word.at(0) != "vn")
            {
                if (list_word.at(0) == "Ka")
                {
                    auto rgb = RGB(std::stof(list_word.at(1)), std::stof(list_word.at(2)), std::stof(list_word.at(3)));
                    obj.ka_set(rgb);
                }
                else if(list_word.at(0) == "Kd")
                {
                    auto rgb = RGB(std::stof(list_word.at(1)), std::stof(list_word.at(2)), std::stof(list_word.at(3)));
                    obj.kd_set(rgb);
                }
                else if(list_word.at(0) == "Ks")
                {
                    auto rgb = RGB(std::stof(list_word.at(1)), std::stof(list_word.at(2)), std::stof(list_word.at(3)));
                    obj.ks_set(rgb);
                }
                else if (list_word.at(0) == "Ns")
                    obj.ns_set(std::stof(list_word.at(1)));
                else if (list_word.at(0) == "Ni")
                    obj.ni_set(std::stof(list_word.at(1)));
                else if (list_word.at(0) == "Nr")
                    obj.nr_set(std::stof(list_word.at(1)));
            }
        }
    }

    file_in.close();
    return false;
}

Camera
Parser::camera_get() const
{
    return camera_;
}

std::vector<light::AmbientLight>
Parser::lights_get() const
{
    return lights_;
}

std::vector<Object>
Parser::objects_get() const
{
    return objects_;
}

