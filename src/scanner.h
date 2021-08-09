#ifndef SCANNER_H
#define SCANNER_H

#include "logger.h"
#include "validator.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;


class Scanner
{
    unique_ptr<Validator> validator;
    unique_ptr<Logger> logger;

public:
    explicit Scanner()
        : validator(std::make_unique<Validator>()),
          logger(std::make_unique<Logger>())
    {

    }

    explicit Scanner(Validator *validator, Logger *logger) : validator(validator), logger(logger)
    {

    }

    /**
     * Адовая функция, так как необходимо разбить её на вызовы более простых функций
     */
    void scan(std::string path)
    {
        if (!path.empty())
        {
            std::string open_path = path;

            for (const auto &file : fs::directory_iterator(open_path))
            {
                LoggerEntry *entry = new LoggerEntry();
                entry->setPath(file.path());

                if (file.exists())
                {
                    if (file.is_regular_file())
                    {
                        if (fs::file_size(file) == 0)
                        {
                            entry->addError("file is empty");
                        } else {
                            auto perms = file.status().permissions();

                            if ((perms & fs::perms::owner_read) == fs::perms::none) {
                                entry->addError("read permission error");
                            } else {
                                for (auto rule : validator->getRules())
                                {
                                    int result = validator->applyRule(file.path(), rule->getIdRule());

                                    switch (result)
                                    {
                                    case NO_RULE_FOUND: {
                                        entry->addError("rule not found");
                                    } break;
                                    case FILE_OPEN_ERROR: {
                                        entry->addError("file open error");
                                    } break;
                                    case FILE_READ_ERROR: {
                                        entry->addError("file read error");
                                    } break;
                                    case FILE_VALIDATED: {
                                        entry->setValidationCode(FILE_VALIDATED);
                                    } break;
                                    default: {
                                        entry->setValidationCode(FILE_NO_VALIDATED);
                                        entry->setValidationRuleId(result);
                                    } break;
                                    }
                                }
                            }
                        }
                    }
                    else if (file.is_directory())
                    {
                        scan(file.path());
                    }
                } else {
                    entry->addError("file not exists");
                }

                logger->addLog(entry);
            }
        }
    }
    
    auto getValidator() const noexcept -> Validator*
    {
        return this->validator.get();
    }

    auto getLogger() const noexcept -> Logger*
    {
        return this->logger.get();
    }

};


#endif // SCANNER_H
