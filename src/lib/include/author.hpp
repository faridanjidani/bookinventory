#include <string>
#include <stdexcept>

class Author
{
    public:
    Author (std::string name_, std::string email_):
    name(name_), email(email_){};
    Author (std::string name_):
    name(name_){};

    inline std::string getName() const
    {
        return name; 
    }   

    inline std::string getEmail() // throw an exception if email is not found
    const 
    {
        if (email.empty())
            throw std::runtime_error("Email not found");

        return email; 
    }  

    private:
    std::string email;
    std::string name;
};