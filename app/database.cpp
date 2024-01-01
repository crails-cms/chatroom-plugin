#include <crails/odb/connection.hpp>

const char* drop_chatroom_query = "DROP TABLE IF EXISTS \"chatroom_Chatroom\" CASCADE;";
const char* drop_chatroom_message_query = "DROP TABLE IF EXISTS \"chatroom_ChatroomMessage\" CASCADE;";
const char* create_chatroom_query =
  "CREATE TABLE \"chatroom_Chatroom\" ("
    "\"id\" BIGSERIAL NOT NULL PRIMARY KEY,"
    "\"deleted\" BOOLEAN NOT NULL DEFAULT FALSE,"
    "\"created_at\" BIGINT NULL,"
    "\"updated_at\" BIGINT NULL,"
    "\"title\" TEXT NOT NULL,"
    "\"slug\" TEXT NOT NULL,"
    "\"channel_password\" TEXT NOT NULL);";
const char* create_chatroom_message_query = 
  "CREATE TABLE \"chatroom_ChatroomMessage\" ("
    "\"id\" BIGSERIAL NOT NULL PRIMARY KEY,"
    "\"deleted\" BOOLEAN NOT NULL DEFAULT FALSE,"
    "\"created_at\" BIGINT NULL,"
    "\"updated_at\" BIGINT NULL,"
    "\"chatroom_id\" BIGINT NOT NULL,"
    "\"author_id\" BIGINT NOT NULL,"
    "\"body\" TEXT NOT NULL);";

void install_plugin_database()
{
  Crails::Odb::Connection database;

  database.transaction.require("odb");
  database.transaction.get_database().execute(create_chatroom_query);
  database.transaction.get_database().execute(create_chatroom_message_query);
  database.commit();
}

void uninstall_plugin_database()
{
  Crails::Odb::Connection database;

  database.transaction.require("odb");
  database.transaction.get_database().execute(drop_chatroom_query);
  database.transaction.get_database().execute(drop_chatroom_message_query);
  database.commit();
}
