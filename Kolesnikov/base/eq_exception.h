#include <string>
class EqExcepion {
    public:
        std::string comment;
        enum error_code 
        {
            incorrect_expression,
            zero_division
        } error;
        EqExcepion(error_code _error, const std::string& _comment = "")
        : error(_error), comment(_comment) {}

        int GetError() const 
        {
            return error;
        }

        std::string GetComment() const
        {
            return comment;
        }
};