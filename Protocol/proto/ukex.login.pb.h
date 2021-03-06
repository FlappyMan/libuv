// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ukex.login.proto

#ifndef PROTOBUF_ukex_2elogin_2eproto__INCLUDED
#define PROTOBUF_ukex_2elogin_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace ukex {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_ukex_2elogin_2eproto();
void protobuf_AssignDesc_ukex_2elogin_2eproto();
void protobuf_ShutdownFile_ukex_2elogin_2eproto();

class login;

enum login_CONST {
  login_CONST_CMD = 114
};
bool login_CONST_IsValid(int value);
const login_CONST login_CONST_CONST_MIN = login_CONST_CMD;
const login_CONST login_CONST_CONST_MAX = login_CONST_CMD;
const int login_CONST_CONST_ARRAYSIZE = login_CONST_CONST_MAX + 1;

const ::google::protobuf::EnumDescriptor* login_CONST_descriptor();
inline const ::std::string& login_CONST_Name(login_CONST value) {
  return ::google::protobuf::internal::NameOfEnum(
    login_CONST_descriptor(), value);
}
inline bool login_CONST_Parse(
    const ::std::string& name, login_CONST* value) {
  return ::google::protobuf::internal::ParseNamedEnum<login_CONST>(
    login_CONST_descriptor(), name, value);
}
// ===================================================================

class login : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ukex.login) */ {
 public:
  login();
  virtual ~login();

  login(const login& from);

  inline login& operator=(const login& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const login& default_instance();

  void Swap(login* other);

  // implements Message ----------------------------------------------

  inline login* New() const { return New(NULL); }

  login* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const login& from);
  void MergeFrom(const login& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(login* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef login_CONST CONST;
  static const CONST CMD =
    login_CONST_CMD;
  static inline bool CONST_IsValid(int value) {
    return login_CONST_IsValid(value);
  }
  static const CONST CONST_MIN =
    login_CONST_CONST_MIN;
  static const CONST CONST_MAX =
    login_CONST_CONST_MAX;
  static const int CONST_ARRAYSIZE =
    login_CONST_CONST_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CONST_descriptor() {
    return login_CONST_descriptor();
  }
  static inline const ::std::string& CONST_Name(CONST value) {
    return login_CONST_Name(value);
  }
  static inline bool CONST_Parse(const ::std::string& name,
      CONST* value) {
    return login_CONST_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required string key = 1;
  bool has_key() const;
  void clear_key();
  static const int kKeyFieldNumber = 1;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  void set_key(const char* value);
  void set_key(const char* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // required string hash = 2;
  bool has_hash() const;
  void clear_hash();
  static const int kHashFieldNumber = 2;
  const ::std::string& hash() const;
  void set_hash(const ::std::string& value);
  void set_hash(const char* value);
  void set_hash(const char* value, size_t size);
  ::std::string* mutable_hash();
  ::std::string* release_hash();
  void set_allocated_hash(::std::string* hash);

  // @@protoc_insertion_point(class_scope:ukex.login)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_hash();
  inline void clear_has_hash();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  ::google::protobuf::internal::ArenaStringPtr hash_;
  friend void  protobuf_AddDesc_ukex_2elogin_2eproto();
  friend void protobuf_AssignDesc_ukex_2elogin_2eproto();
  friend void protobuf_ShutdownFile_ukex_2elogin_2eproto();

  void InitAsDefaultInstance();
  static login* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// login

// required string key = 1;
inline bool login::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void login::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void login::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void login::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_key();
}
inline const ::std::string& login::key() const {
  // @@protoc_insertion_point(field_get:ukex.login.key)
  return key_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void login::set_key(const ::std::string& value) {
  set_has_key();
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.login.key)
}
inline void login::set_key(const char* value) {
  set_has_key();
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.login.key)
}
inline void login::set_key(const char* value, size_t size) {
  set_has_key();
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.login.key)
}
inline ::std::string* login::mutable_key() {
  set_has_key();
  // @@protoc_insertion_point(field_mutable:ukex.login.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* login::release_key() {
  // @@protoc_insertion_point(field_release:ukex.login.key)
  clear_has_key();
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void login::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    set_has_key();
  } else {
    clear_has_key();
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:ukex.login.key)
}

// required string hash = 2;
inline bool login::has_hash() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void login::set_has_hash() {
  _has_bits_[0] |= 0x00000002u;
}
inline void login::clear_has_hash() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void login::clear_hash() {
  hash_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_hash();
}
inline const ::std::string& login::hash() const {
  // @@protoc_insertion_point(field_get:ukex.login.hash)
  return hash_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void login::set_hash(const ::std::string& value) {
  set_has_hash();
  hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.login.hash)
}
inline void login::set_hash(const char* value) {
  set_has_hash();
  hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.login.hash)
}
inline void login::set_hash(const char* value, size_t size) {
  set_has_hash();
  hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.login.hash)
}
inline ::std::string* login::mutable_hash() {
  set_has_hash();
  // @@protoc_insertion_point(field_mutable:ukex.login.hash)
  return hash_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* login::release_hash() {
  // @@protoc_insertion_point(field_release:ukex.login.hash)
  clear_has_hash();
  return hash_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void login::set_allocated_hash(::std::string* hash) {
  if (hash != NULL) {
    set_has_hash();
  } else {
    clear_has_hash();
  }
  hash_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), hash);
  // @@protoc_insertion_point(field_set_allocated:ukex.login.hash)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace ukex

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ukex::login_CONST> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ukex::login_CONST>() {
  return ::ukex::login_CONST_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ukex_2elogin_2eproto__INCLUDED
