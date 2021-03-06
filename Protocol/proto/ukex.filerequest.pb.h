// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ukex.filerequest.proto

#ifndef PROTOBUF_ukex_2efilerequest_2eproto__INCLUDED
#define PROTOBUF_ukex_2efilerequest_2eproto__INCLUDED

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
void protobuf_AddDesc_ukex_2efilerequest_2eproto();
void protobuf_AssignDesc_ukex_2efilerequest_2eproto();
void protobuf_ShutdownFile_ukex_2efilerequest_2eproto();

class filerequest;

enum filerequest_CONST {
  filerequest_CONST_CMD = 112
};
bool filerequest_CONST_IsValid(int value);
const filerequest_CONST filerequest_CONST_CONST_MIN = filerequest_CONST_CMD;
const filerequest_CONST filerequest_CONST_CONST_MAX = filerequest_CONST_CMD;
const int filerequest_CONST_CONST_ARRAYSIZE = filerequest_CONST_CONST_MAX + 1;

const ::google::protobuf::EnumDescriptor* filerequest_CONST_descriptor();
inline const ::std::string& filerequest_CONST_Name(filerequest_CONST value) {
  return ::google::protobuf::internal::NameOfEnum(
    filerequest_CONST_descriptor(), value);
}
inline bool filerequest_CONST_Parse(
    const ::std::string& name, filerequest_CONST* value) {
  return ::google::protobuf::internal::ParseNamedEnum<filerequest_CONST>(
    filerequest_CONST_descriptor(), name, value);
}
// ===================================================================

class filerequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ukex.filerequest) */ {
 public:
  filerequest();
  virtual ~filerequest();

  filerequest(const filerequest& from);

  inline filerequest& operator=(const filerequest& from) {
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
  static const filerequest& default_instance();

  void Swap(filerequest* other);

  // implements Message ----------------------------------------------

  inline filerequest* New() const { return New(NULL); }

  filerequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const filerequest& from);
  void MergeFrom(const filerequest& from);
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
  void InternalSwap(filerequest* other);
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

  typedef filerequest_CONST CONST;
  static const CONST CMD =
    filerequest_CONST_CMD;
  static inline bool CONST_IsValid(int value) {
    return filerequest_CONST_IsValid(value);
  }
  static const CONST CONST_MIN =
    filerequest_CONST_CONST_MIN;
  static const CONST CONST_MAX =
    filerequest_CONST_CONST_MAX;
  static const int CONST_ARRAYSIZE =
    filerequest_CONST_CONST_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CONST_descriptor() {
    return filerequest_CONST_descriptor();
  }
  static inline const ::std::string& CONST_Name(CONST value) {
    return filerequest_CONST_Name(value);
  }
  static inline bool CONST_Parse(const ::std::string& name,
      CONST* value) {
    return filerequest_CONST_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required string path = 2;
  bool has_path() const;
  void clear_path();
  static const int kPathFieldNumber = 2;
  const ::std::string& path() const;
  void set_path(const ::std::string& value);
  void set_path(const char* value);
  void set_path(const char* value, size_t size);
  ::std::string* mutable_path();
  ::std::string* release_path();
  void set_allocated_path(::std::string* path);

  // required uint64 size = 3;
  bool has_size() const;
  void clear_size();
  static const int kSizeFieldNumber = 3;
  ::google::protobuf::uint64 size() const;
  void set_size(::google::protobuf::uint64 value);

  // required uint64 modifytime = 4;
  bool has_modifytime() const;
  void clear_modifytime();
  static const int kModifytimeFieldNumber = 4;
  ::google::protobuf::uint64 modifytime() const;
  void set_modifytime(::google::protobuf::uint64 value);

  // required uint64 offset = 5;
  bool has_offset() const;
  void clear_offset();
  static const int kOffsetFieldNumber = 5;
  ::google::protobuf::uint64 offset() const;
  void set_offset(::google::protobuf::uint64 value);

  // required uint32 length = 6;
  bool has_length() const;
  void clear_length();
  static const int kLengthFieldNumber = 6;
  ::google::protobuf::uint32 length() const;
  void set_length(::google::protobuf::uint32 value);

  // optional string token = 7;
  bool has_token() const;
  void clear_token();
  static const int kTokenFieldNumber = 7;
  const ::std::string& token() const;
  void set_token(const ::std::string& value);
  void set_token(const char* value);
  void set_token(const char* value, size_t size);
  ::std::string* mutable_token();
  ::std::string* release_token();
  void set_allocated_token(::std::string* token);

  // @@protoc_insertion_point(class_scope:ukex.filerequest)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_path();
  inline void clear_has_path();
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_modifytime();
  inline void clear_has_modifytime();
  inline void set_has_offset();
  inline void clear_has_offset();
  inline void set_has_length();
  inline void clear_has_length();
  inline void set_has_token();
  inline void clear_has_token();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr path_;
  ::google::protobuf::uint64 size_;
  ::google::protobuf::uint64 modifytime_;
  ::google::protobuf::uint64 offset_;
  ::google::protobuf::internal::ArenaStringPtr token_;
  ::google::protobuf::uint32 length_;
  friend void  protobuf_AddDesc_ukex_2efilerequest_2eproto();
  friend void protobuf_AssignDesc_ukex_2efilerequest_2eproto();
  friend void protobuf_ShutdownFile_ukex_2efilerequest_2eproto();

  void InitAsDefaultInstance();
  static filerequest* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// filerequest

// required string name = 1;
inline bool filerequest::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void filerequest::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void filerequest::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void filerequest::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& filerequest::name() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void filerequest::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.filerequest.name)
}
inline void filerequest::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.filerequest.name)
}
inline void filerequest::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.filerequest.name)
}
inline ::std::string* filerequest::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:ukex.filerequest.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* filerequest::release_name() {
  // @@protoc_insertion_point(field_release:ukex.filerequest.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void filerequest::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:ukex.filerequest.name)
}

// required string path = 2;
inline bool filerequest::has_path() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void filerequest::set_has_path() {
  _has_bits_[0] |= 0x00000002u;
}
inline void filerequest::clear_has_path() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void filerequest::clear_path() {
  path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_path();
}
inline const ::std::string& filerequest::path() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.path)
  return path_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void filerequest::set_path(const ::std::string& value) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.filerequest.path)
}
inline void filerequest::set_path(const char* value) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.filerequest.path)
}
inline void filerequest::set_path(const char* value, size_t size) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.filerequest.path)
}
inline ::std::string* filerequest::mutable_path() {
  set_has_path();
  // @@protoc_insertion_point(field_mutable:ukex.filerequest.path)
  return path_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* filerequest::release_path() {
  // @@protoc_insertion_point(field_release:ukex.filerequest.path)
  clear_has_path();
  return path_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void filerequest::set_allocated_path(::std::string* path) {
  if (path != NULL) {
    set_has_path();
  } else {
    clear_has_path();
  }
  path_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), path);
  // @@protoc_insertion_point(field_set_allocated:ukex.filerequest.path)
}

// required uint64 size = 3;
inline bool filerequest::has_size() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void filerequest::set_has_size() {
  _has_bits_[0] |= 0x00000004u;
}
inline void filerequest::clear_has_size() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void filerequest::clear_size() {
  size_ = GOOGLE_ULONGLONG(0);
  clear_has_size();
}
inline ::google::protobuf::uint64 filerequest::size() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.size)
  return size_;
}
inline void filerequest::set_size(::google::protobuf::uint64 value) {
  set_has_size();
  size_ = value;
  // @@protoc_insertion_point(field_set:ukex.filerequest.size)
}

// required uint64 modifytime = 4;
inline bool filerequest::has_modifytime() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void filerequest::set_has_modifytime() {
  _has_bits_[0] |= 0x00000008u;
}
inline void filerequest::clear_has_modifytime() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void filerequest::clear_modifytime() {
  modifytime_ = GOOGLE_ULONGLONG(0);
  clear_has_modifytime();
}
inline ::google::protobuf::uint64 filerequest::modifytime() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.modifytime)
  return modifytime_;
}
inline void filerequest::set_modifytime(::google::protobuf::uint64 value) {
  set_has_modifytime();
  modifytime_ = value;
  // @@protoc_insertion_point(field_set:ukex.filerequest.modifytime)
}

// required uint64 offset = 5;
inline bool filerequest::has_offset() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void filerequest::set_has_offset() {
  _has_bits_[0] |= 0x00000010u;
}
inline void filerequest::clear_has_offset() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void filerequest::clear_offset() {
  offset_ = GOOGLE_ULONGLONG(0);
  clear_has_offset();
}
inline ::google::protobuf::uint64 filerequest::offset() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.offset)
  return offset_;
}
inline void filerequest::set_offset(::google::protobuf::uint64 value) {
  set_has_offset();
  offset_ = value;
  // @@protoc_insertion_point(field_set:ukex.filerequest.offset)
}

// required uint32 length = 6;
inline bool filerequest::has_length() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void filerequest::set_has_length() {
  _has_bits_[0] |= 0x00000020u;
}
inline void filerequest::clear_has_length() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void filerequest::clear_length() {
  length_ = 0u;
  clear_has_length();
}
inline ::google::protobuf::uint32 filerequest::length() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.length)
  return length_;
}
inline void filerequest::set_length(::google::protobuf::uint32 value) {
  set_has_length();
  length_ = value;
  // @@protoc_insertion_point(field_set:ukex.filerequest.length)
}

// optional string token = 7;
inline bool filerequest::has_token() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void filerequest::set_has_token() {
  _has_bits_[0] |= 0x00000040u;
}
inline void filerequest::clear_has_token() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void filerequest::clear_token() {
  token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_token();
}
inline const ::std::string& filerequest::token() const {
  // @@protoc_insertion_point(field_get:ukex.filerequest.token)
  return token_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void filerequest::set_token(const ::std::string& value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.filerequest.token)
}
inline void filerequest::set_token(const char* value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.filerequest.token)
}
inline void filerequest::set_token(const char* value, size_t size) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.filerequest.token)
}
inline ::std::string* filerequest::mutable_token() {
  set_has_token();
  // @@protoc_insertion_point(field_mutable:ukex.filerequest.token)
  return token_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* filerequest::release_token() {
  // @@protoc_insertion_point(field_release:ukex.filerequest.token)
  clear_has_token();
  return token_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void filerequest::set_allocated_token(::std::string* token) {
  if (token != NULL) {
    set_has_token();
  } else {
    clear_has_token();
  }
  token_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:ukex.filerequest.token)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace ukex

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ukex::filerequest_CONST> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ukex::filerequest_CONST>() {
  return ::ukex::filerequest_CONST_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ukex_2efilerequest_2eproto__INCLUDED
