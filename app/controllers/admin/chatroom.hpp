#pragma once
#include <crails/cms/controllers/admin/resource.hpp>
#include "app/controllers/admin/application.hpp"
#include "app/models/user.hpp"
#include "app/models/chatroom.hpp"

struct ChatroomTraits
{
  typedef User     UserModel;
  typedef Chatroom Model;
  typedef Chatroom IndexModel;
};

class AdminChatroomController : public Crails::Cms::AdminResourceController<ChatroomTraits, Chatroom, AdminApplicationController>
{
  typedef AdminResourceController<ChatroomTraits, Chatroom, AdminApplicationController> Super;
public:
  static constexpr const char* scope = "chatrooms";

  AdminChatroomController(Crails::Context& context) : Super(context)
  {
    Super::vars["local_route"] = std::string(Super::scope) + '/' + scope;
    Super::vars["page_title"] = i18n::t("admin.menu.chatrooms");
    Super::vars["page_subtitle"] = i18n::t("admin.chatrooms-subtitle");
  }

  std::string get_view_scope() const override { return "chatrooms"; }
  std::string get_url() const override { return "/admin/chatrooms"; }
};
