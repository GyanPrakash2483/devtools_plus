#include <genplugin.hpp>
#include <configs.hpp>
#include <fstream>
#include <util.hpp>

bool genplugin(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) {

  config_t config = getConfig();

  const std::string plugin_name = args[0];

  if (!isSnakeCase(plugin_name))
  {
    sender.sendErrorMessage("Plugin name should include only lowercase characters or _(underscore)");
    return false;
  }

  const std::string plugin_name_camel = snakeToCamel(plugin_name);

  const std::string plugin_dir = config.development_dir + plugin_name + "/";

  if (std::filesystem::exists(plugin_dir))
  {
    sender.sendErrorMessage("A plugin with this name already exists at " + plugin_dir);
    return false;
  }

  if (!std::filesystem::create_directories(removeTrailingSlash(plugin_dir)))
  { // the removeTrailingSlash wrapper should be removed after https://github.com/llvm/llvm-project/issues/60634 is fixed.
    sender.sendErrorMessage("Could not create directory: " + plugin_dir);
    return false;
  }
  if (!std::filesystem::create_directories(plugin_dir + "include"))
  {
    sender.sendErrorMessage("Could not create directory: " + plugin_dir + "include");
    return false;
  }
  if (!std::filesystem::create_directories(plugin_dir + "src"))
  {
    sender.sendErrorMessage("Could not create directory: " + plugin_dir + "src");
    return false;
  }

  // Create CMakeLists.txt file
  const std::string cmake_file = plugin_dir + "CMakeLists.txt";
  std::ofstream cmake_out_stream(cmake_file);

  if (!cmake_out_stream)
  {
    sender.sendErrorMessage("Error occured while creating file: " + cmake_file);
    return false;
  }

  cmake_out_stream << "cmake_minimum_required(VERSION 3.15)" << std::endl
                   << std::endl
                   << "set(CMAKE_CXX_COMPILER clang++)" << std::endl
                   << std::endl
                   << "project(" << plugin_name << " CXX)" << std::endl
                   << std::endl
                   << "set(CMAKE_CXX_STANDARD 20)" << std::endl
                   << "set(CMAKE_CXX_STANDARD_REQUIRED ON)" << std::endl
                   << std::endl
                   << "include(FetchContent)" << std::endl
                   << "set(FETCHCONTENT_QUIET FALSE)" << std::endl
                   << "FetchContent_Declare(" << std::endl
                   << "\tendstone" << std::endl
                   << "\tGIT_REPOSITORY https://github.com/EndstoneMC/endstone.git" << std::endl
                   << "\tGIT_TAG \"v" << sender.getServer().getVersion() << "\"" << std::endl
                   << "\tGIT_PROGRESS TRUE" << std::endl
                   << ")" << std::endl
                   << "FetchContent_MakeAvailable(endstone)" << std::endl
                   << std::endl
                   << "endstone_add_plugin(${PROJECT_NAME} src/" << plugin_name << ".cpp)" << std::endl
                   << "target_include_directories(${PROJECT_NAME} PRIVATE include)" << std::endl;

  cmake_out_stream.close();

  // Create header file
  const std::string header_file = plugin_dir + "include/" + plugin_name + ".hpp";
  std::ofstream header_out_stream(header_file);

  if (!header_out_stream)
  {
    sender.sendErrorMessage("Error occured while creating file: " + header_file);
    return false;
  }

  header_out_stream << "#pragma once" << std::endl
                    << std::endl
                    << "#include <endstone/plugin/plugin.h>" << std::endl
                    << std::endl
                    << "class " << plugin_name_camel << " : public endstone::Plugin {" << std::endl
                    << "\tpublic:" << std::endl
                    << "\t\tvoid onLoad() override;" << std::endl
                    << "\t\tvoid onEnable() override;" << std::endl
                    << "\t\tbool onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) override;" << std::endl
                    << "};" << std::endl;

  header_out_stream.close();

  // Create source file
  const std::string source_file = plugin_dir + "src/" + plugin_name + ".cpp";
  std::ofstream source_out_stream(source_file);

  if (!source_out_stream)
  {
    sender.sendErrorMessage("Error occured while creating file: " + source_file);
    return false;
  }

  source_out_stream << "#include <" << plugin_name << ".hpp>" << std::endl
                    << "#include <endstone/color_format.h>" << std::endl
                    << std::endl
                    << "ENDSTONE_PLUGIN(\"" << plugin_name << "\", \"0.1.0\", " << plugin_name_camel << ") {" << std::endl
                    << "\tdescription = \"Edit this to add plugin description\";" << std::endl
                    << "\tcommand(\"hello\")" << std::endl
                    << "\t\t.description(\"Greets User\")" << std::endl
                    << "\t\t.usages(\"/hello\")" << std::endl
                    << "\t\t.permissions(\"" << plugin_name << ".command.hello\");" << std::endl
                    << std::endl
                    << "\tpermission(\"" << plugin_name << ".command.hello\")" << std::endl
                    << "\t\t.description(\"Allows user's to use the /hello command.\")" << std::endl
                    << "\t\t.default_(endstone::PermissionDefault::True);" << std::endl
                    << "}" << std::endl
                    << std::endl
                    << "void " << plugin_name_camel << "::onLoad()" << std::endl
                    << "{" << std::endl
                    << "\tgetLogger().info(endstone::ColorFormat::Green + \"" << plugin_name_camel << ": \" + endstone::ColorFormat::Reset + \"Plugin Loaded Successfully\");" << std::endl
                    << "}" << std::endl
                    << std::endl
                    << "void " << plugin_name_camel << "::onEnable()" << std::endl
                    << "{" << std::endl
                    << "\t// On Plugin Enable" << std::endl
                    << "}" << std::endl
                    << std::endl
                    << "bool " << plugin_name_camel << "::onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args)" << std::endl
                    << "{" << std::endl
                    << "\tif(command.getName() == \"hello\") {" << std::endl
                    << "\t\tsender.sendMessage(\"Hello, World!\");" << std::endl
                    << "\t}" << std::endl
                    << "\treturn true;" << std::endl
                    << "}" << std::endl;

  source_out_stream.close();

  sender.sendMessage("Plugin created at: " + plugin_dir);

  return true;
}