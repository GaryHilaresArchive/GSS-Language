#pragma once

namespace GSS
{
    class Writer
    {
    private:
        bool updated;
        string outFilename;
    public:
        PropertyRule(std::string newOutFilename): outFilename, updated(true) {}
        ~PropertyRule(){this->writeToFile();}
        void addClass(std::string request, std::string property){updated = false;}
        void addProperty(std::string request, std::string property){updated = false;}
        void writeToFile(){}
        void discardChanges(){}
    };
}
