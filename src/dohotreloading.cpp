#include <dohotreloading.hpp>
#include <config.hpp>

bool dohotreloading(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) {

  if(args.size() == 0) {
    
    config.live_reload_plugins = !config.live_reload_plugins;

  } else {
    
    if(args[0] == "true" || args[0] == "True") {
      config.live_reload_plugins = true;
    } else { // No extra checks required because otherwise, command will have been filtered by the handler.
      config.live_reload_plugins = false;
    }
    
  }
  sender.sendMessage("Rule dohotreloading set to " + (std::string)(config.live_reload_plugins ? "true" : "false"));


  return true;
}
