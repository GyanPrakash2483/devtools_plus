# devtools_plus

devtools_plus is a plugin for the Endstone framework that simplifies Minecraft Bedrock plugin development in C++.

# Features

✅ Generate skeleton files for a new plugin.  
✅ Build plugins from source code.  
🏗️ Automatically Build and Load plugins when code changes. (coming soon)  

# Commands

✅ `/genplugin <plugin_name: str>`: Generate a new C++ Plugin with given name (Use only lowercase letter and underscores for plugin name).  
✅ `/buildplugin <plugin_name: str>`: Build a plugin from it's source code.  
🏗️ `/dohotreload <do_hot_reload: bool>`: Wether development plugins should be reloaded when code changes. (coming soon)  

# Building your plugins

## Prerequisite

- `clang++ >= 18`
- `libc++-dev >= 18` (package name may be different depending on distro)
- `cmake >= 3.15`
- `make >= 4.3`

## Building

1. Go to the plugin's home directory (`<minecraft_server_directory>/bedrock_server/development_plugins/<plugin_name>`).
2. run:
```bash
  mkdir build && cd build
```
3. run:
```bash
  cmake ..
```

4. run:
```bash
  make -j $(nproc)
```

## Building on Windows

Similar steps should work on windows too, however it has not been tested. If someone has a Windows machine to test and wants to make a contribution, you are most welcome.

# Contributing

Thankyou for choosing to contribute to this project, check [CONTRIBUTING.md](/CONTRIBUTING.md) for more details.