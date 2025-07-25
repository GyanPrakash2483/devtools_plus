#pragma once

#include <string>
#include <platform.hpp>
#include <cstdlib>
#include <filesystem>

typedef struct {
  std::string current_dir;
  std::string development_dir;
  std::string build_output_dir;
  std::string temp_build_dir;
  bool live_reload_plugins;
} config_t;

config_t getConfig() {
  config_t config = {
    .current_dir = std::filesystem::current_path(),
    .development_dir = (std::string)std::filesystem::current_path() + "/development_plugins/",
    .build_output_dir = (std::string)std::filesystem::current_path() + "plugins",
    
    #if defined(OS_UNIX)
    .temp_build_dir = "/temp/",
    #elif defined(OS_WINDOWS)
    .temp_build_dir = std::getenv("TEMP"),
    #endif

    .live_reload_plugins = true
  };

  return config;
}