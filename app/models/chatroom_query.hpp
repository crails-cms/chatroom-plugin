#pragma once
#include "chatroom.hpp"
#include "app/models/user.hpp"

#pragma db view object(ChatroomMessage) \
  object(User = user left: ChatroomMessage::author_id == user::id)
struct ChatroomMessageView
{
  std::string get_database_name() { return ::ChatroomMessage().get_database_name(); }
  Crails::Odb::id_type get_id() const { return message ? message->get_id() : ODB_NULL_ID; }

  std::shared_ptr<ChatroomMessage> message;
  std::shared_ptr<User> user;

  #pragma db view object(ChatroomMessage) object(User inner: ChatroomMessage::author_id == User::id)
  struct Count
  {
    #pragma db column("count(" + ChatroomMessage::id + ")")
    size_t value;
  };
};
