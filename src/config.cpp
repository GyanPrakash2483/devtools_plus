#include <config.hpp>

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