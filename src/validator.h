#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <map>
#include <vector>
#include <fstream>
#include "validator_rule.h"
#include "validator_code.h"

class Validator
{
    std::vector<ValidatorRule*> rules;

public:
    Validator()
    {

    }

    virtual ~Validator()
    {
        if (!this->rules.empty())
        {
            for (auto rule : this->rules) {
                if (rule) {
                    delete rule;
                }
            }
        }
    }

    void addRule(ValidatorRule* rule)
    {
        if (rule)
        {
            rule->setIdRule(this->rules.size()+1);
            this->rules.push_back(rule);
        }
    }

    void addRule(std::string rule, std::regex pattern)
    {
        if (!rule.empty())
        {
            ValidatorRule *newRule = new ValidatorRule(rule, pattern);

            newRule->setIdRule(this->rules.size()+1);
            this->rules.push_back(newRule);
        }
    }

    void addRule(std::string rule, std::string pattern)
    {
        if (!rule.empty())
        {
            std::regex regexp(pattern, std::regex_constants::basic | std::regex_constants::icase);
            ValidatorRule *newRule = new ValidatorRule(rule, regexp);
            newRule->setStringPattern(pattern);

            newRule->setIdRule(this->rules.size()+1);
            this->rules.push_back(newRule);
        }
    }

    auto getRule(unsigned int idRule) const -> ValidatorRule*
    {
        for (auto rule : this->rules)
        {
            if (rule->getIdRule() == idRule) {
                return rule;
            }
        }

        return nullptr;
    }

    auto getRule(std::string rule_name) const -> ValidatorRule*
    {
        for (auto rule : this->rules)
        {
            if (rule->getRule() == rule_name) {
                return rule;
            }
        }

        return nullptr;
    }

    auto getRules() const -> std::vector<ValidatorRule*>
    {
        return this->rules;
    }

    auto applyRule(std::string path, unsigned int idRule) -> int
    {
        ValidatorRule* rule = this->getRule(idRule);

        if (rule)
        {
            std::ifstream file;
            file.open(path);

            if (file.is_open())
            {
                std::string line;

                while (getline(file, line))
                {
                    if (std::regex_match(line, rule->getPattern()))
                    {
                        return rule->getIdRule();
                    }
                }

                file.close();
                return static_cast<int>(ValidatorCode::FILE_VALIDATED);
            } else {
                return static_cast<int>(ValidatorCode::FILE_OPEN_ERROR);
            }
        }

        return static_cast<int>(ValidatorCode::NO_RULE_FOUND);
    }

};

#endif // VALIDATOR_H
