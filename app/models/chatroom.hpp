#pragma once
#include <crails/cms/models/sluggable.hpp>

#pragma db object
class ChatroomMessage : public Crails::Odb::Model
{
  odb_instantiable()
public:
  #pragma db view object(ChatroomMessage)
  struct Count
  {
    #pragma db column("count(" + ChatroomMessage::id + ")")
    size_t value;
  };

  static const std::string scope;

  template<typename QUERY>
  static QUERY default_order_by(QUERY query) { return query + "ORDER BY" + QUERY::created_at; }

  void merge_data(Data) const;
  std::string to_json() const;

  Crails::Odb::id_type get_chatroom_id() const { return chatroom_id; }
  void set_chatroom_id(Crails::Odb::id_type value) { chatroom_id = value; }
  Crails::Odb::id_type get_author_id() const { return author_id; }
  void set_author_id(Crails::Odb::id_type value) { author_id = value; }
  const std::string& get_body() const { return body; }
  void set_body(const std::string& value) { body = value; }

private:
  Crails::Odb::id_type chatroom_id;
  Crails::Odb::id_type author_id;
  std::string          body;
};

#pragma db object
class Chatroom : public Crails::Cms::Sluggable
{
  odb_instantiable()
public:
  #pragma db view object(Chatroom)
  struct Count
  {
    #pragma db column("count(" + Chatroom::id + ")")
    size_t value;
  };

  static const std::string scope;

  template<typename QUERY>
  static QUERY default_order_by(QUERY query) { return query + "ORDER BY" + QUERY::created_at; }

  const std::string& get_channel_password() const { return channel_password; }

  void initialize();

private:
  #pragma db value_type("VARCHAR(12)")
  std::string channel_password;
};
