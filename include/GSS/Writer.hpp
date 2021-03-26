#pragma once
#include <string>
#include <vector>

namespace GSS
{
    class Writer
    {
    private:
        std::string out_filename;
        bool updated;
        bool save_on_destroy;
    public:
        /** Constructor
          * Creates a Writer which output is the given filename.
          *
          * @param A filename to send the output.
          * @param Whether the changes should be automatically
          *        saved to the file when the object is
          *        destroyed. Default to true.
          * @return A Writer which output is the given filename.
          * @throw Never throws.
          *
          **/
        Writer(std::string new_out_filename, bool new_save_on_destroy = true):
            out_filename(new_out_filename), updated(true), save_on_destroy(new_save_on_destroy) {}
        /** Destructor
          * If save_on_destroy is true, saves the changes to the
          * file.
          *
          * @relatesalso GSS::Writer::writeToFile.
          **/
        ~Writer(){this->writeToFile();}
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
        void addClass(const std::string& request, const std::string& class_name, const std::vector<std::pair<std::string,std::string>>& properties = {}) {updated = false;}
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
        void addProperty(const std::string& request, const std::string& property_name, const std::string& property_value){updated = false;}
        void writeToFile(){}
    };
}
