#include "../../include/GSS/Reader.hpp"
#include <fstream>
#include <list>
#include <sstream>
#include <stack>
#include <vector>

const char* GSS::WrongTypeException::what() const noexcept
{
    return "Requested int, addressed point is a std::string.";
}

const char* GSS::InvalidRequestException::what() const noexcept
{
   return "Request does not address to a valid point.";
}

int GSS::PropertyRule::getInt(const std::string& request) const
{
    std::string processing = this->getString(request);
    int ret;
    try
    {
        ret = std::stoi(processing);
    }
    catch (std::invalid_argument& error)
    {
        throw WrongTypeException();
    }
    return ret;
}

double GSS::PropertyRule::getDouble(const std::string& request) const
{
    std::string processing = this->getString(request);
    double ret;
    try
    {
        ret = std::stod(processing);
    }
    catch (std::invalid_argument& error)
    {
        throw WrongTypeException();
    }
    return ret;
}

std::string GSS::PropertyRule::getString(const std::string& request) const
{
    unsigned short int index;
    if (request == "")
    {
        index = 1;
    }
    else if (request[0] == '#')
    {
        try
        {
            index = std::stoi(request.substr(1, request.size() - 1));
        }
        catch (std::invalid_argument &error)
        {
            throw InvalidRequestException();
        }
    }
    else
    {
        throw InvalidRequestException();
    }
    std::istringstream ss(this->data);
    std::string processing;
    while (index--)
        if (!(ss >> processing))
            throw InvalidRequestException();
    return processing;
}

GSS::PropertySheet GSS::PropertySheet::loadFromStream(std::istream& in)
{
    GSS::PropertySheet root;
    std::stack<GSS::PropertySheet*, std::list<GSS::PropertySheet*>> outer_classes;
    std::vector<std::pair<std::string, std::string>> property_rules_saved;
    std::stack<int, std::list<int>> property_rules_saved_amount;
    int property_rules_saving_amount = 0;
    GSS::PropertySheet* inner_class = &root;
    std::string processing;
    while (std::getline(in, processing))
    {
        if (processing.find("end") != processing.npos)
        {
            for (int i = 0; i < property_rules_saving_amount; i++)
                property_rules_saved.pop_back();
            inner_class = outer_classes.top();
            outer_classes.pop();
            property_rules_saving_amount = property_rules_saved_amount.top();
            property_rules_saved_amount.pop();
            continue;
        }
        std::string::size_type determining_index = processing.find_first_of("=:;");
        if (determining_index == processing.npos || processing[determining_index] == ';')
        {
            continue;
        }
        else if (processing[determining_index] == '=')
        {
            std::string::size_type start_substr = processing.find_first_not_of(" \t");
            std::string::size_type end_substr = processing.find_last_not_of(" \t", determining_index - 1);
            std::string name = processing.substr(start_substr, end_substr - start_substr + 1);
            if (inner_class->properties.find(name) != inner_class->properties.end())
                delete inner_class->properties[name];
            inner_class->properties[name] = new PropertySheet();
            property_rules_saved_amount.push(property_rules_saving_amount);
            property_rules_saving_amount = 0;
            outer_classes.push(inner_class);
            inner_class = dynamic_cast<PropertySheet*>(inner_class->properties[name]);
            for (const std::pair<std::string, std::string> &property_rule_it : property_rules_saved)
            {
                if (inner_class->properties.find(name) != inner_class->properties.end())
                    delete inner_class->properties[name];
                inner_class->properties[property_rule_it.first] = new PropertyRule(property_rule_it.second);
            }
        }
        else if (processing[determining_index] == ':')
        {
            std::string::size_type start_name = processing.find_first_not_of(" \t");
            std::string::size_type end_name = processing.find_last_not_of(" \t", determining_index - 1);
            std::string::size_type start_value = processing.find_first_not_of(" \t", end_name + 2);
            std::string::size_type end_value = processing.find(';', end_name + 2);
            std::string name = processing.substr(start_name, end_name - start_name + 1);
            std::string value = processing.substr(start_value, end_value - start_value);
            if (inner_class->properties.find(name) != inner_class->properties.end())
                delete inner_class->properties[name];
            inner_class->properties[name] = new PropertyRule(value);
            property_rules_saved.push_back({name, value});
            property_rules_saving_amount++;
        }
    }
    return root;
}

GSS::PropertySheet GSS::PropertySheet::loadFromFile(const std::string& filename)
{
    std::ifstream ifile(filename);
    if (ifile.fail())
        throw InvalidRequestException();
    GSS::PropertySheet root = loadFromStream(ifile);
    ifile.close();
    return root;
}

const GSS::PropertySheet& GSS::PropertySheet::getPropertySheet(const std::string& request) const
{
    const PropertySheet* cur = this;
    std::string::size_type substr_start = 0;
    while (substr_start < request.size())
    {
        std::string::size_type substr_end = request.find("::", substr_start);
        substr_end = (substr_end == request.npos ? request.size() : substr_end - 1);
        std::string request_substr = request.substr(substr_start, substr_end - substr_start + 1);
        try
        {
            cur = dynamic_cast<PropertySheet *>(cur->properties.at(request_substr));
            if (cur == nullptr)
                throw InvalidRequestException();
        }
        catch (std::out_of_range& error)
        {
            throw InvalidRequestException();
        }
        substr_start = substr_end + 3;
    }
    return *cur;
}

const GSS::PropertyRule& GSS::PropertySheet::getPropertyRule(const std::string& request) const
{
    const GSS::PropertySheet* cur = this;
    std::string::size_type substr_start = 0;
    while (substr_start < request.size())
    {
        std::string::size_type substr_end = request.find("::", substr_start);
        substr_end = (substr_end == request.npos ? request.size() - 1 : substr_end - 1);
        std::string request_substr = request.substr(substr_start, substr_end - substr_start + 1);
        try
        {
            GSS::PropertySheet *tmp = dynamic_cast<GSS::PropertySheet*>(cur->properties.at(request_substr));
            if (tmp == nullptr)
            {
                if (substr_end != request.size() - 1)
                    throw InvalidRequestException();
                const GSS::PropertyRule *ret = dynamic_cast<GSS::PropertyRule*>(cur->properties.at(request_substr));
                if (ret == nullptr)
                    throw InvalidRequestException();
                return *ret;
            }
            cur = tmp;
        }
        catch (std::out_of_range& error)
        {
            throw InvalidRequestException();
        }
        substr_start = substr_end + 3;
    }
    throw InvalidRequestException();
}

int GSS::PropertySheet::getInt(const std::string& request) const
{
    std::string::size_type delimiter_index = request.find_last_of(":#");
    if (delimiter_index == request.npos)
        delimiter_index = 0;
    if (request[delimiter_index] == ':')
        return this->getPropertyRule(request).getInt("");
    else
        return this->getPropertyRule(request.substr(0, delimiter_index - 2)).getInt(request.substr(delimiter_index, request.size() - delimiter_index));
}

double GSS::PropertySheet::getDouble(const std::string& request) const
{
    std::string::size_type delimiter_index = request.find_last_of(":#");
    if (delimiter_index == request.npos)
        delimiter_index = 0;
    if (request[delimiter_index] == ':')
        return this->getPropertyRule(request).getDouble("");
    else
        return this->getPropertyRule(request.substr(0, delimiter_index - 2)).getDouble(request.substr(delimiter_index, request.size() - delimiter_index));
}

std::string GSS::PropertySheet::getString(const std::string& request) const
{
    std::string::size_type delimiter_index = request.find_last_of(":#");
    if (delimiter_index == request.npos)
        delimiter_index = 0;
    if (request[delimiter_index] == ':')
        return this->getPropertyRule(request).getString("");
    else
        return this->getPropertyRule(request.substr(0, delimiter_index - 2)).getString(request.substr(delimiter_index, request.size() - delimiter_index));
}
