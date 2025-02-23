// This pre-processor directive says that this file can only be included once
// It prevents us from including a header file multiple times into a single translation unit
// In essence this prevents duplicate object issues
// Same as the ifdef and ifndef directives
#pragma once
#include <string>

void Log(const char* message);
void Log(std::string message);
void ShowPointers();
void ShowReference();
void ShowStrings();
void ShowConsts();