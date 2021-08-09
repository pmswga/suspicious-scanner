#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <vector>
#include <string>
#include <map>
#include "logger_entry.h"
#include "validator_code.h"

using LoggerEntries = std::vector<LoggerEntry*>;
using LoggerDetections = std::map<std::string, int>;

class Logger
{
    LoggerEntries logs;
    LoggerDetections detections;

public:
    explicit Logger()
    {

    }

    virtual ~Logger()
    {
        if (!logs.empty())
        {
            for (auto log : this->logs)
            {
                if (log)
                {
                    delete log;
                }
            }
        }
    }

    void addLog(LoggerEntry *log)
    {
        if (log)
        {
            this->logs.push_back(log);
        }
    }


    void addDetection(std::string rule_name)
    {
        if (this->detections.count(rule_name) == 1)
        {
            this->detections.at(rule_name)++;
        } else {
            this->detections.insert(std::pair(rule_name, 1));
        }
    }

    auto getDetectionLogs() const -> LoggerEntries
    {
        LoggerEntries detectionLogs;

        if (!this->logs.empty())
        {
            for (const auto &log : this->logs)
            {
                if (log->getValidationRuleId() > 0)
                {
                    detectionLogs.push_back(log);
                }
            }
        }

        return detectionLogs;
    }

    auto getErrorLogs() const -> LoggerEntries
    {
        LoggerEntries errorLogs;

        if (!this->logs.empty())
        {
            for (const auto &log : this->logs)
            {
                if (!log->getErrors().empty())
                {
                    errorLogs.push_back(log);
                }
            }
        }

        return errorLogs;
    }


    auto getValidatedLogs() const -> LoggerEntries
    {
        LoggerEntries validatedLogs;

        if (!this->logs.empty())
        {
            for (const auto &log : this->logs)
            {
                if (log->getValidationCode() == FILE_VALIDATED && log->getValidationRuleId() == 0)
                {
                    validatedLogs.push_back(log);
                }
            }
        }

        return validatedLogs;
    }

    auto getLogs() const -> LoggerEntries
    {
        return this->logs;
    }

};


#endif // LOGGER_H
