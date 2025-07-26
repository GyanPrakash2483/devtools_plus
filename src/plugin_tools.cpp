#include <plugin_tools.hpp>
#include <endstone/color_format.h>
#include <genplugin.hpp>

ENDSTONE_PLUGIN("plugin_tools", "0.2.0", PluginTools) {
  description = "Tools to help develop endstone plugins in C++";
  command("genplugin")
    .description("Generate a new C++ Plugin with given name (Use only lowercase letter and underscores for plugin name).")
    .usages("/genplugin <plugin_name: str>")
    .permissions("plugin_tools.command.genplugin");

  permission("plugin_tools.command.genplugin")
    .description("Allows user's to use the /genplugin command.")
    .default_(endstone::PermissionDefault::Operator);
}

void PluginTools::onLoad()
{
  getLogger().info(endstone::ColorFormat::Green + "PluginTools: " + endstone::ColorFormat::Reset + "Plugin Loaded Successfully");
}

void PluginTools::onEnable()
{
  // On Plugin Enable
}

bool PluginTools::onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args)
{
  if(command.getName() == "genplugin") {
    return genplugin(sender, command, args);
    
  } else {
    return false;
  }
}
