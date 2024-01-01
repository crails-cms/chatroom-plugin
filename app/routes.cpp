#include <crails/router.hpp>
#include <crails/sync/channel_actions.hpp>
#include <crails/cms/views/admin_menu.hpp>
#include "lib/plugin-odb.hxx"
#include "controllers/admin/chatroom.hpp"
#include "controllers/chatroom.hpp"

void initialize_plugin_routes()
{
  auto& router = Crails::Router::singleton::require();
  auto& admin_menu = Crails::Cms::AdminMenu::singleton::require();

  router.scope(ChatroomController::scope, [&]()
  {
    router.match_action("GET", "/:slug", ChatroomController, show);
    router.match_action("GET", "/by-id/:id", ChatroomController, show);
    router.match_action("POST", "/by-id/:id", ChatroomController, post);
    router.match_sync_channel("/by-id/:id/channel", Crails::Sync::ChannelListener);
  });

  router.scope(AdminApplicationController::scope, [&]()
  {
    router.scope(AdminChatroomController::scope, [&]()
    {
      admin_menu.add({3, "chatrooms", router.get_current_scope()});
      router.match_action("GET",    "/",    AdminChatroomController, index);
      router.match_action("POST",   "/",    AdminChatroomController, create);
      router.match_action("GET",    "/new", AdminChatroomController, new_);
      router.match_action("GET",    "/:id", AdminChatroomController, show);
      router.match_action("PUT",    "/:id", AdminChatroomController, update);
      router.match_action("DELETE", "/:id", AdminChatroomController, destroy);
    });
  });
}
