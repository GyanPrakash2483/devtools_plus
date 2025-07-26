#include <util.hpp>

std::string removeTrailingSlash(const std::string path) {
  if(path[path.length() - 1] == '/') {
    std::string path_with_no_trailing_slash(path);
    path_with_no_trailing_slash.pop_back();
    return path_with_no_trailing_slash;
  } else {
    return path;
  }
}

bool isSnakeCase(std::string string) {
  for(int i = 0; i < string.length(); i++) {
    if(!(string[i] >= 'a' && string[i] <= 'z') && string[i] != '_') {
      return false;
    }
  }
  return true;
}

std::string snakeToCamel(const std::string& snake) {
  std::string result;
  bool capitalizeNext = false;

  for (char ch : snake) {
      if (ch == '_') {
          capitalizeNext = true;
      } else if (capitalizeNext) {
          result += std::toupper(ch);
          capitalizeNext = false;
      } else {
          result += ch;
      }
  }

  return result;
}