#pragma once
#include <crails/paginator.hpp>
#include "app/controllers/userspace.hpp"
#include "app/models/chatroom.hpp"

class ChatroomController : public UserspaceBaseController
{
  typedef UserspaceBaseController Super;
public:
  static constexpr const char* scope = "chatroom";

  ChatroomController(Crails::Context& context) : Super(context), paginator(params.as_data())
  {
    vars["local_route"] = std::string(scope);
  }

  void show();
  void post();

private:
  bool must_protect_from_forgery() const override { return false; }

  odb::query<Chatroom> find_one_query() const;

  bool require_chatroom()
  {
    return Super::database.find_one(chatroom, find_one_query());
  }

  std::string make_post_route(const Chatroom&);
  std::string make_channel_name(const Chatroom&);

  Crails::Paginator paginator;
  std::shared_ptr<Chatroom> chatroom;
};
