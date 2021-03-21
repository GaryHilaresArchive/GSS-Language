#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <list>
#include <vector>

namespace GSS
{
    class wrongType: public std::exception
    {
        virtual const char* what() const noexcept
        {
            return "Requested int, addressed point is a std::string.";
        }
    };
    class invalidRequest: public std::exception
    {
        virtual const char* what() const noexcept
        {
            return "Request does not address to a valid point.";
        }
    };

    class PropertyHolder
    {
    public:
        virtual int getInt(const std::string& request) const {throw invalidRequest();}
        virtual std::string getString(const std::string& request) const {throw invalidRequest();}
        virtual ~PropertyHolder() = default;
    };

    class PropertyRule: public PropertyHolder
    {
    private:
        std::string data;
    public:
        PropertyRule(std::string data): data(data) {}
        int getInt(const std::string& request) const override
        {
            std::string processing = this->getString(request);
            int ret;
            try
            {
                ret = std::stoi(processing);
            }
            catch(std::invalid_argument& error)
            {
                throw wrongType();
            }
            return ret;
        }
        std::string getString(const std::string& request) const override
        {
            unsigned short int index;
            if(request == "")
            {
                index = 1;
            }
            else if(request[0] == '#')
            {
                try
                {
                    index = std::stoi(request.substr(1,request.size()-1));
                }
                catch(std::invalid_argument& error)
                {
                    throw invalidRequest();
                }
            }
            else
            {
                throw invalidRequest();
            }
            std::istringstream ss(this->data);
            std::string processing;
            while(index--)
                if(!(ss >> processing))
                    throw invalidRequest();
            return processing;
        }
    };

    class PropertySheet: public PropertyHolder
    {
    private:
        std::unordered_map<std::string,PropertyHolder*> properties;
    public:
        static PropertySheet loadFromStream(std::istream& in)
        {
            PropertySheet root;
            std::stack<PropertySheet*,std::list<PropertySheet*>> outerClasses;
            std::vector<std::pair<std::string,std::string>> propertyRulesSaved;
            std::stack<int,std::list<int>> propertyRulesSavedAmount;
            int propertyRulesSavingAmount = 0;
            PropertySheet* innerClass = &root;
            std::string processing;
            while(std::getline(in,processing))
            {
                if(processing.find("end") != processing.npos)
                {
                    for(int i = 0; i < propertyRulesSavingAmount; i++)
                        propertyRulesSaved.pop_back();
                    innerClass = outerClasses.top();
                    outerClasses.pop();
                    propertyRulesSavingAmount = propertyRulesSavedAmount.top();
                    propertyRulesSavedAmount.pop();
                    continue;
                }
                std::string::size_type determiningIndex = processing.find_first_of("=:;");
                if(determiningIndex == processing.npos || processing[determiningIndex] == ';')
                {
                    continue;
                }
                else if(processing[determiningIndex] == '=')
                {
                    std::string::size_type startSubstr = processing.find_first_not_of(" \t");
                    std::string::size_type endSubstr = processing.find_last_not_of(" \t", determiningIndex-1);
                    std::string name = processing.substr(startSubstr,endSubstr-startSubstr+1);
                    if(innerClass->properties.find(name) != innerClass->properties.end())
                        delete innerClass->properties[name];
                    innerClass->properties[name] = new PropertySheet();
                    propertyRulesSavedAmount.push(propertyRulesSavingAmount);
                    propertyRulesSavingAmount = 0;
                    outerClasses.push(innerClass);
                    innerClass = dynamic_cast<PropertySheet*>(innerClass->properties[name]);
                    for(const std::pair<std::string,std::string>& propertyRuleIt: propertyRulesSaved)
                    {
                        if(innerClass->properties.find(name) != innerClass->properties.end())
                            delete innerClass->properties[name];
                        innerClass->properties[propertyRuleIt.first] = new PropertyRule(propertyRuleIt.second);
                    }
                }
                else if(processing[determiningIndex] == ':')
                {
                    std::string::size_type startName = processing.find_first_not_of(" \t");
                    std::string::size_type endName = processing.find_last_not_of(" \t", determiningIndex-1);
                    std::string::size_type startValue = processing.find_first_not_of(" \t",endName+2);
                    std::string::size_type endValue = processing.find(';',endName + 2);
                    std::string name = processing.substr(startName,endName-startName+1);
                    std::string value = processing.substr(startValue,endValue-startValue);
                    if(innerClass->properties.find(name) != innerClass->properties.end())
                        delete innerClass->properties[name];
                    innerClass->properties[name] = new PropertyRule(value);
                    propertyRulesSaved.push_back({name,value});
                    propertyRulesSavingAmount++;
                }
            }
            return root;
        }
        static PropertySheet loadFromFile(const std::string filename)
        {
            std::ifstream ifile(filename);
            if(ifile.fail())
                throw invalidRequest();
            PropertySheet root = loadFromStream(ifile);
            ifile.close();
            return root;
        }
        const PropertySheet& getPropertySheet(const std::string& request) const
        {
            const PropertySheet* cur = this;
            std::string::size_type substrStart = 0;
            while(substrStart < request.size())
            {
                std::string::size_type substrEnd = request.find("::",substrStart);
                substrEnd = (substrEnd == request.npos ? request.size() : substrEnd-1);
                std::string requestSubstr = request.substr(substrStart,substrEnd-substrStart+1);
                try
                {
                    cur = dynamic_cast<PropertySheet*>(cur->properties.at(requestSubstr));
                    if(cur == nullptr)
                        throw invalidRequest();
                }
                catch(std::out_of_range& error)
                {
                    throw invalidRequest();
                }
                substrStart = substrEnd + 3;
            }
            return *cur;
        }
        const PropertyRule& getPropertyRule(const std::string& request) const
        {
            const PropertySheet* cur = this;
            std::string::size_type substrStart = 0;
            while(substrStart < request.size())
            {
                std::string::size_type substrEnd = request.find("::",substrStart);
                substrEnd = (substrEnd == request.npos ? request.size()-1 : substrEnd-1);
                std::string requestSubstr = request.substr(substrStart,substrEnd-substrStart+1);
                try
                {
                    PropertySheet* tmp = dynamic_cast<PropertySheet*>(cur->properties.at(requestSubstr));
                    if(tmp == nullptr)
                    {
                        if(substrEnd != request.size()-1)
                            throw invalidRequest();
                        const PropertyRule* ret = dynamic_cast<PropertyRule*>(cur->properties.at(requestSubstr));
                        if(ret == nullptr)
                            throw invalidRequest();
                        return *ret;
                    }
                    cur = tmp;
                }
                catch(std::out_of_range& error)
                {
                    throw invalidRequest();
                }
                substrStart = substrEnd + 3;
            }
            throw invalidRequest();
        }
        int getInt(const std::string& request) const override
        {
            std::string::size_type delimiterIndex = request.find_last_of(":#");
            if(delimiterIndex == request.npos)
                delimiterIndex = 0;
            if(request[delimiterIndex] == ':')
                return this->getPropertyRule(request).getInt("");
            else
                return this->getPropertyRule(request.substr(0,delimiterIndex-2)).getInt(request.substr(delimiterIndex,request.size()-delimiterIndex));
        }
        std::string getString(const std::string& request) const override
        {
            std::string::size_type delimiterIndex = request.find_last_of(":#");
            if(delimiterIndex == request.npos)
                delimiterIndex = 0;
            if(request[delimiterIndex] == ':')
                return this->getPropertyRule(request).getString("");
            else
                return this->getPropertyRule(request.substr(0,delimiterIndex-2)).getString(request.substr(delimiterIndex,request.size()-delimiterIndex));
        }
    };
}
