#include <devtools_plus.hpp>
#include <endstone/color_format.h>
#include <genplugin.hpp>
#include <buildplugin.hpp>
#include <dohotreloading.hpp>

ENDSTONE_PLUGIN("devtools_plus", "0.4.0", DevtoolsPlus) {
  description = "Tools to help develop endstone plugins in C++";
  
  
  command("genplugin")
    .description("Generate a new C++ Plugin with given name (Use only lowercase letter and underscores for plugin name).")
    .usages("/genplugin <plugin_name: str>")
    .permissions("devtools_plus.command.genplugin");

  permission("devtools_plus.command.genplugin")
    .description("Allows users to use the /genplugin command.")
    .default_(endstone::PermissionDefault::Operator);

  
  command("buildplugin")
    .description("Build a plugin from source.")
    .usages("/buildplugin <plugin_name: str>")
    .permissions("devtools_plus.command.buildplugin");

  permission("devtools_plus.command.buildplugin")
    .description("Allows users to use the /buildplugin command.")
    .default_(endstone::PermissionDefault::Operator);


  command("dohotreloading")
    .description("Change wether development plugins should be reloaded on code change.")
    .usages("/dohotreloading [do_hot_reloading: bool]")
    .permissions("devtools_plus.command.dohotreloading");

  permission("devtools_plus.command.dohotreloading")
    .description("Allows users to use the /dohotreloading command.")
    .default_(endstone::PermissionDefault::Operator);

}

void DevtoolsPlus::onLoad()
{
  getLogger().info(endstone::ColorFormat::Green + "DevtoolsPlus: " + endstone::ColorFormat::Reset + "Plugin Loaded Successfully");
}

void DevtoolsPlus::onEnable()
{
  // on Enable
}

bool DevtoolsPlus::onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args)
{
  if(command.getName() == "genplugin") {
    return genplugin(sender, command, args);

  } else if(command.getName() == "buildplugin") {
    return buildplugin(sender, command, args);

  } else if(command.getName() == "dohotreloading") {
    return dohotreloading(sender, command, args);

  } else {
    return false;
  }
}
