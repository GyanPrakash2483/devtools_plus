#pragma once

#include <string>

std::string removeTrailingSlash(const std::string path);
bool isSnakeCase(std::string string);
std::string snakeToCamel(const std::string& snake);
