void initialize_plugin_routes();
void initialize_plugin_renderers();
void install_plugin_database();
void uninstall_plugin_database();

extern "C"
{
  void initialize()
  {
    initialize_plugin_routes();
    initialize_plugin_renderers();
  }

  void install()
  {
    install_plugin_database();
  }

  void uninstall()
  {
    uninstall_plugin_database();
  }
}
