#ifndef LOGGERENTRY_H
#define LOGGERENTRY_H

#include <string>
#include <vector>

class LoggerEntry
{
    std::string path;
    int validation_code;
    int validation_rule_id;
    std::vector<std::string> errors;

public:
    LoggerEntry() : path(""), validation_code(0), validation_rule_id(0)
    {

    }

    LoggerEntry(std::string path, int validation_code) :
        path(path), validation_code(validation_code)
    {

    }

    virtual ~LoggerEntry()
    {

    }

    void setPath(std::string path)
    {
        if (!path.empty())
        {
            this->path = path;
        }
    }

    auto getPath() const -> std::string
    {
        return this->path;
    }

    void setValidationCode(int validation_code)
    {
        this->validation_code = validation_code;
    }

    auto getValidationCode() const -> int
    {
        return this->validation_code;
    }

    void setValidationRuleId(int rule_id)
    {
        this->validation_rule_id = rule_id;
    }

    auto getValidationRuleId() const -> int
    {
        return this->validation_rule_id;
    }

    void addError(std::string error)
    {
        this->errors.push_back(error);
    }

    auto getErrors() const -> std::vector<std::string>
    {
        return this->errors;
    }

};

#endif // LOGGERENTRY_H
