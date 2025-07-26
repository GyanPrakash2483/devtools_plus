#include <buildplugin.hpp>
#include <endstone/plugin/plugin.h>
#include <util.hpp>
#include <filesystem>
#include <configs.hpp>
#include <thread>


bool buildplugin(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) {

  config_t config = getConfig();

  const std::string plugin_name = args[0];

  if(!isSnakeCase(plugin_name)) {
    sender.sendErrorMessage("Invalid plugin name: " + plugin_name);
    return false;
  }

  const std::string plugin_dir = config.development_dir + plugin_name;

  if(!std::filesystem::exists(plugin_dir)) {
    sender.sendErrorMessage("No plugin exist with name: " + plugin_dir);
    return false;
  }

  std::filesystem::create_directories(config.build_dir);

  std::string extra_paths = "/usr/bin:/usr/local/bin:/bin";

  // Configure CMake
  std::string configure_cmake_command = "PATH=" + extra_paths + ":$PATH && cd " + config.build_dir + " && cmake " + plugin_dir;
  std::system(configure_cmake_command.c_str());

  // Build Project
  unsigned int num_build_threads = std::thread::hardware_concurrency();
  if(num_build_threads == 0) {
    num_build_threads = 1;
  }

  std::string build_command = "PATH=" + extra_paths + ":$PATH && cd " + config.build_dir + " && make -j " + std::to_string(num_build_threads);
  std::system(build_command.c_str());

  const std::string built_plugin_filename = "endstone_" + plugin_name + ".so";
  const std::string built_plugin_path = config.build_dir + built_plugin_filename;

  if(!std::filesystem::exists(built_plugin_path)) {
    sender.sendErrorMessage("Error occured while building plugin, build manually to see errors");
    return false;
  }

  if(!std::filesystem::copy_file(built_plugin_path, config.build_output_dir + built_plugin_filename)) {
    sender.sendErrorMessage("Could not copy built plugin to plugin dir");
    return false;
  }

  sender.sendMessage("Plugin built successfully.");
  return true;

}
