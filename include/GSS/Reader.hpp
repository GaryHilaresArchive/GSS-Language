#pragma once
#include <string>
#include <unordered_map>

namespace GSS
{
    class WrongTypeException : public std::exception
    {
        virtual const char *what() const noexcept;
    };
    class InvalidRequestException : public std::exception
    {
        virtual const char *what() const noexcept;
    };
    class PropertyInterface
    {
    public:
        virtual ~PropertyInterface() = default;
        virtual int getInt(const std::string& request) const = 0;
        virtual double getDouble(const std::string& request) const = 0;
        virtual std::string getString(const std::string& request) const = 0;
    };
    class Property : public PropertyInterface
    {
    private:
        std::string data;
    public:
        /** Constructor
          * Creates a Property Rule with the given data.
          *
          * @param A std::string containing the data.
          * @return A Property with the given data.
          * @throw No throw.
          *
          **/
        Property(const std::string& data) : data(data) {}
        /** getInt
          * Searchs an int in the given address.
          *
          * @param A std::string containing the requested
          *        address.
          * @return The int in the given address.
          * @throw InvalidRequestException if the address does
          *        not have an int on it.
          *
          **/
        int getInt(const std::string& request) const override;
        /** getDouble
          * Searchs a double in the given address.
          *
          * @param A std::stringstring containing the requested
          *        address.
          * @return The double in the given address.
          * @throw InvalidRequestException if the address does
          *        not have a double on it.
          *
          **/
        double getDouble(const std::string& request) const override;
        /** getString
          * Searchs a std::string in the given address.
          *
          * @param A std::string containing the requested address.
          * @return The std::string in the given address.
          * @throw InvalidRequestException if the address does
          *        not have a std::string on it.
          *
          **/
        std::string getString(const std::string& request) const override;
    };

    class PropertyClass : public PropertyInterface
    {
    protected:
        std::unordered_map<std::string, PropertyInterface*> properties;
    public:
        /** loadFromStream
          * Creates a PropertyClass from an istream. The content of
          * the istream must be written in GSS.
          *
          * @param A reference to an istream which is written in
          *        GSS syntax.
          * @return The Property Sheet generated from the istream.
          * @throw Never.
          *
          **/
        static PropertyClass loadFromStream(std::istream& in);
        /** loadFromFile
          * Creates a PropertyClass from a file. The content of
          * the file must be written in GSS.
          *
          * @param The filename of a file which is written in
          *        GSS syntax.
          * @return The Property Sheet generated from the file.
          * @throw InvalidRequestException if the file does
          *        not cannot be accessed (or not exists).
          *
          **/
        static PropertyClass loadFromFile(const std::string& filename);
        /** getPropertyClass
          * Searchs a PropertyClass in the given address.
          *
          * @param A std::string containing the requested address.
          * @return The PropertyClass in the given address.
          * @throw InvalidRequestException if the adress does
          *        not have a PropertyClass on it.
          *
          **/
        const PropertyClass& getPropertyClass(const std::string& request) const;
        /** getProperty
          * Searchs a Property in the given address.
          *
          * @param A std::string containing the requested address.
          * @return The Property in the given address.
          * @throw InvalidRequestException if the address does
          *        not have a Property on it.
          *
          **/
        const Property& getProperty(const std::string& request) const;
        /** getInt
          * Searchs an int in the given address.
          *
          * @param A std::string containing the requested
          *        address.
          * @return The int in the given address.
          * @throw InvalidRequestException if the address does
          *        not have an int on it.
          *
          **/
        int getInt(const std::string& request) const override;
        /** getDouble
          * Searchs a double in the given address.
          *
          * @param A std::stringstring containing the requested
          *        address.
          * @return The double in the given address.
          * @throw InvalidRequestException if the address does
          *        not have a double on it.
          *
          **/
        double getDouble(const std::string& request) const override;
        /** getString
          * Searchs a std::string in the given address.
          *
          * @param A std::string containing the requested address.
          * @return The std::string in the given address.
          * @throw InvalidRequestException if the address does
          *        not have a std::string on it.
          *
          **/
        std::string getString(const std::string& request) const override;
    };
    using PropertyReader = PropertyClass;
}
