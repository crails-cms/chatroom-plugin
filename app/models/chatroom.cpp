#include "chatroom.hpp"
#include "lib/plugin-odb.hxx"
#include <crails/utils/random_string.hpp>

using namespace std;

const string Chatroom::scope = "chatroom";
const string ChatroomMessage::scope = "message";

odb_instantiable_impl(Chatroom)
odb_instantiable_impl(ChatroomMessage)

void Chatroom::initialize()
{
  channel_password = Crails::generate_random_string(12);
}

void ChatroomMessage::merge_data(Data out) const
{
  out["author_id"] = author_id;
  out["body"] = body;
  out["created_at"] = get_created_at();
}

string ChatroomMessage::to_json() const
{
  DataTree output;

  merge_data(output.as_data());
  return output.to_json();
}
