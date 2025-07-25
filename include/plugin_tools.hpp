#pragma once

#include <endstone/plugin/plugin.h>

class PluginTools : public endstone::Plugin {
  public:
    void onLoad() override;
    void onEnable() override;
    bool onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) override;
};