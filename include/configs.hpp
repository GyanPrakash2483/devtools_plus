#pragma once

#include <string>
#include <platform.hpp>
#include <cstdlib>
#include <filesystem>

typedef struct {
  std::string current_dir;
  std::string development_dir;
  std::string build_output_dir;
  std::string build_dir;
  bool live_reload_plugins;
} config_t;

inline config_t getConfig() {
  config_t config = {
    .current_dir = std::filesystem::current_path(),
    .development_dir = (std::string)std::filesystem::current_path() + "/development_plugins/",
    .build_output_dir = (std::string)std::filesystem::current_path() + "/plugins/",
    
    #if defined(OS_UNIX)
    .build_dir = (std::string)std::getenv("HOME") + "/.local/share/devtools_plus/builddir/",
    #elif defined(OS_WINDOWS)
    .build_dir = (std::string)std::getenv("APPDATA") + "\\devtools_plus\\builddir\\",
    #endif

    .live_reload_plugins = true
  };

  return config;
}