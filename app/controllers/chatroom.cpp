#include <crails/sync/channels.hpp>
#include <crails/utils/random_string.hpp>
#include <crails/cms/routes.hpp>
#include "lib/odb/application-odb.hxx"
#include "lib/plugin-odb.hxx"
#include "chatroom.hpp"
#include "app/models/chatroom_query.hpp"

using namespace std;

static const string write_channel_password = Crails::generate_random_string(32);

string ChatroomController::make_post_route(const Chatroom& chatroom)
{
  const Crails::Cms::LocalRoute route(vars);

  return route.make("by-id") + '/' + std::to_string(chatroom.get_id());
}

string ChatroomController::make_channel_name(const Chatroom& chatroom)
{
  return make_post_route(chatroom) + "/channel";
}

odb::query<Chatroom> ChatroomController::find_one_query() const
{
  if (params["slug"].exists())
    return odb::query<Chatroom>::slug == params["slug"].as<std::string>();
  return odb::query<Chatroom>::id == params["id"].as<Crails::Odb::id_type>();
}

void ChatroomController::show()
{
  if (require_chatroom())
  {
    auto user = user_session.get_current_user();
    odb::result<ChatroomMessageView> messages;
    odb::query<ChatroomMessage> query = odb::query<ChatroomMessage>::chatroom_id == chatroom->get_id();

    vars["post_route"] = make_post_route(*chatroom);
    paginator.set_default_items_per_page(100);
    paginator.decorate_view(Super::vars, [this, query]()
    {
      return Super::database.template count<ChatroomMessage>(query);
    });
    paginator.decorate_query<ChatroomMessage>(query);
    Super::database.template find<ChatroomMessageView>(messages, query);
    render("chatrooms/show", {
      {"model",    const_cast<const Chatroom*>(chatroom.get())},
      {"messages", &messages},
      {"user_id",  user->get_id()}
    });
  }
  else
    respond_with(Crails::HttpStatus::not_found);
}

void ChatroomController::post()
{
  if (require_chatroom())
  {
    ChatroomMessage message;
    auto  user     = user_session.get_current_user();
    auto& channels = Crails::Sync::Channels::singleton::require();
    auto  channel  = channels.require_channel(make_channel_name(*chatroom));
    DataTree broadcast;

    message.set_chatroom_id(chatroom->get_id());
    message.set_author_id(user->get_id());
    message.set_body(params[ChatroomMessage::scope]["body"]);
    database.save(message);
    channel->set_password(chatroom->get_channel_password(), Crails::Sync::Channel::ReadMode);
    channel->set_password(write_channel_password, Crails::Sync::Channel::WriteMode);
    message.merge_data(broadcast.as_data());
    broadcast["avatar_url"] = user->get_avatar_url();
    broadcast["display_name"] = user->get_display_name();
    channel->broadcast(broadcast.to_json());
    render(TEXT, session["csrf-token"].as<string>());
  }
  else
    respond_with(Crails::HttpStatus::not_found);
}
