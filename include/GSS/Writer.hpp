#pragma once
#include <string>
#include <vector>

namespace GSS
{
    class Writer
    {
    private:
        bool updated;
    public:
        /** Constructor
          * Creates a Writer.
          *
          * @return A Writer.
          * @throw Never throws.
          *
          **/
        Writer(): updated(true) {}
        /** addClass
          * Adds a property class with the given information.
          *
          * @param A std::string containing the requested address.
          * @param A std::string containing the class name.
          * @param A std::vector containing properties (std::pairs,
          *        that contain one std::string with a property name
          *        and one std::string with a property value).
          * @throw InvalidRequestException if request adress is
          *        not valid or if class_name is empty.
          *
          **/
        void addClass(const std::string& request, const std::string& class_name, const std::vector<std::pair<std::string,std::string>>& properties = {});
        /** addProperty
          * Adds a property name with the given information.
          *
          * @param A std::string containing the requested address.
          * @param A std::string containing the property name.
          * @param A std::string containing the property value.
          * @throw InvalidRequestException if request adress is
          *        not valid, if property_name is empty or if
          *        property_value is empty.
          *
          **/
        void addProperty(const std::string& request, const std::string& property_name, const std::string& property_value);
        /** writeToFile
          * Writes the Writer's data to a file.
          *
          * @param The filename of a file.
          * @throw No throws.
          *
          **/
        void writeToFile(const std::string& filename);
    };
}
