#include <iostream>
#include <chrono>
#include "scanner.h"
using namespace std;

int main(int argc, char** argv)
{
    if (argc == 2) {
        std::string path = argv[1];

        if (!path.empty())
        {
            Scanner scan;

            scan.getValidator()->addRule("Js detection", "<script>evil_script()</script>");
            scan.getValidator()->addRule("Bash detection", "rm -rf ~/Documents");
            scan.getValidator()->addRule("MacOS detection", "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")");


            try
            {
                auto begin = std::chrono::steady_clock::now();
                scan.scan(path);
                auto end = std::chrono::steady_clock::now();

                auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);


                /// View statistic
                cout << endl << "========= Results =========" << endl;
                cout << endl << "Time: " << elapsed_ms.count() * 0.000001 << " seconds" << endl;
                cout << endl << "Processed files (files & directoreis): " << scan.getLogger()->getLogs().size() << endl;
                cout << endl << "Validated files: " << scan.getLogger()->getValidatedLogs().size() << endl;
                cout << endl << "Detected files: " << scan.getLogger()->getDetectionLogs().size() << endl;
                cout << endl << "Errors: " << scan.getLogger()->getErrorLogs().size() << endl;

                /// View validated files
                cout << endl << "Validation list: " << endl;

                unsigned int i = 0;
                for (const auto &log : scan.getLogger()->getValidatedLogs())
                {
                    cout << (i+1) << " | " << log->getPath() << endl;
                    i++;
                }


                /// View error files
                cout << endl << "Error list: " << endl;

                i = 0;
                for (const auto &log : scan.getLogger()->getErrorLogs())
                {
                    cout << (i+1) << " | " << log->getPath() << " | ";
                    for (const auto &error : log->getErrors())
                    {
                        cout << error << ", ";
                    }
                    cout << endl;
                    i++;
                }

                /// View detected files
                cout << endl << "Detections: " << endl;

                i = 0;
                for (const auto &log : scan.getLogger()->getDetectionLogs())
                {
                    cout << (i+1) << " | " << scan.getValidator()->getRule(log->getValidationRuleId())->getRule() << " | " << log->getPath() << endl;
                    i++;
                }

                /// View rules
                cout << endl << "Rules:" << endl;

                for (auto rule : scan.getValidator()->getRules())
                {
                    cout << rule->getIdRule() << " | " << rule->getRule() << " | pattern -> " << rule->getStringPattern() << endl;
                }

                /// View files
                cout << endl << "Scanned files (files & directories): " << endl;

                i = 0;
                for (const auto &log : scan.getLogger()->getLogs())
                {
                    cout << (i+1) << " | " << log->getPath() << endl;
                    i++;
                }


            } catch (fs::filesystem_error &e) {
                std::cerr << e.what() << endl;
            }

            return 0;
        } else {
            std::cout << "Path can't be empty" << endl;
        }
    }

    std::cout << "Set path for scan" << endl;

    return 0;
}
