// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ukex.canceltradebatch.proto

#ifndef PROTOBUF_ukex_2ecanceltradebatch_2eproto__INCLUDED
#define PROTOBUF_ukex_2ecanceltradebatch_2eproto__INCLUDED

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
void protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto();
void protobuf_AssignDesc_ukex_2ecanceltradebatch_2eproto();
void protobuf_ShutdownFile_ukex_2ecanceltradebatch_2eproto();

class canceltradebatch;

enum canceltradebatch_CONST {
  canceltradebatch_CONST_CMD = 103
};
bool canceltradebatch_CONST_IsValid(int value);
const canceltradebatch_CONST canceltradebatch_CONST_CONST_MIN = canceltradebatch_CONST_CMD;
const canceltradebatch_CONST canceltradebatch_CONST_CONST_MAX = canceltradebatch_CONST_CMD;
const int canceltradebatch_CONST_CONST_ARRAYSIZE = canceltradebatch_CONST_CONST_MAX + 1;

const ::google::protobuf::EnumDescriptor* canceltradebatch_CONST_descriptor();
inline const ::std::string& canceltradebatch_CONST_Name(canceltradebatch_CONST value) {
  return ::google::protobuf::internal::NameOfEnum(
    canceltradebatch_CONST_descriptor(), value);
}
inline bool canceltradebatch_CONST_Parse(
    const ::std::string& name, canceltradebatch_CONST* value) {
  return ::google::protobuf::internal::ParseNamedEnum<canceltradebatch_CONST>(
    canceltradebatch_CONST_descriptor(), name, value);
}
// ===================================================================

class canceltradebatch : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:ukex.canceltradebatch) */ {
 public:
  canceltradebatch();
  virtual ~canceltradebatch();

  canceltradebatch(const canceltradebatch& from);

  inline canceltradebatch& operator=(const canceltradebatch& from) {
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
  static const canceltradebatch& default_instance();

  void Swap(canceltradebatch* other);

  // implements Message ----------------------------------------------

  inline canceltradebatch* New() const { return New(NULL); }

  canceltradebatch* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const canceltradebatch& from);
  void MergeFrom(const canceltradebatch& from);
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
  void InternalSwap(canceltradebatch* other);
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

  typedef canceltradebatch_CONST CONST;
  static const CONST CMD =
    canceltradebatch_CONST_CMD;
  static inline bool CONST_IsValid(int value) {
    return canceltradebatch_CONST_IsValid(value);
  }
  static const CONST CONST_MIN =
    canceltradebatch_CONST_CONST_MIN;
  static const CONST CONST_MAX =
    canceltradebatch_CONST_CONST_MAX;
  static const int CONST_ARRAYSIZE =
    canceltradebatch_CONST_CONST_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CONST_descriptor() {
    return canceltradebatch_CONST_descriptor();
  }
  static inline const ::std::string& CONST_Name(CONST value) {
    return canceltradebatch_CONST_Name(value);
  }
  static inline bool CONST_Parse(const ::std::string& name,
      CONST* value) {
    return canceltradebatch_CONST_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional string token = 1;
  bool has_token() const;
  void clear_token();
  static const int kTokenFieldNumber = 1;
  const ::std::string& token() const;
  void set_token(const ::std::string& value);
  void set_token(const char* value);
  void set_token(const char* value, size_t size);
  ::std::string* mutable_token();
  ::std::string* release_token();
  void set_allocated_token(::std::string* token);

  // repeated uint64 ids = 2;
  int ids_size() const;
  void clear_ids();
  static const int kIdsFieldNumber = 2;
  ::google::protobuf::uint64 ids(int index) const;
  void set_ids(int index, ::google::protobuf::uint64 value);
  void add_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_ids();

  // required uint64 marketid = 3;
  bool has_marketid() const;
  void clear_marketid();
  static const int kMarketidFieldNumber = 3;
  ::google::protobuf::uint64 marketid() const;
  void set_marketid(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:ukex.canceltradebatch)
 private:
  inline void set_has_token();
  inline void clear_has_token();
  inline void set_has_marketid();
  inline void clear_has_marketid();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr token_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > ids_;
  ::google::protobuf::uint64 marketid_;
  friend void  protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto();
  friend void protobuf_AssignDesc_ukex_2ecanceltradebatch_2eproto();
  friend void protobuf_ShutdownFile_ukex_2ecanceltradebatch_2eproto();

  void InitAsDefaultInstance();
  static canceltradebatch* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// canceltradebatch

// optional string token = 1;
inline bool canceltradebatch::has_token() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void canceltradebatch::set_has_token() {
  _has_bits_[0] |= 0x00000001u;
}
inline void canceltradebatch::clear_has_token() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void canceltradebatch::clear_token() {
  token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_token();
}
inline const ::std::string& canceltradebatch::token() const {
  // @@protoc_insertion_point(field_get:ukex.canceltradebatch.token)
  return token_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void canceltradebatch::set_token(const ::std::string& value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.canceltradebatch.token)
}
inline void canceltradebatch::set_token(const char* value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.canceltradebatch.token)
}
inline void canceltradebatch::set_token(const char* value, size_t size) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.canceltradebatch.token)
}
inline ::std::string* canceltradebatch::mutable_token() {
  set_has_token();
  // @@protoc_insertion_point(field_mutable:ukex.canceltradebatch.token)
  return token_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* canceltradebatch::release_token() {
  // @@protoc_insertion_point(field_release:ukex.canceltradebatch.token)
  clear_has_token();
  return token_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void canceltradebatch::set_allocated_token(::std::string* token) {
  if (token != NULL) {
    set_has_token();
  } else {
    clear_has_token();
  }
  token_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:ukex.canceltradebatch.token)
}

// repeated uint64 ids = 2;
inline int canceltradebatch::ids_size() const {
  return ids_.size();
}
inline void canceltradebatch::clear_ids() {
  ids_.Clear();
}
inline ::google::protobuf::uint64 canceltradebatch::ids(int index) const {
  // @@protoc_insertion_point(field_get:ukex.canceltradebatch.ids)
  return ids_.Get(index);
}
inline void canceltradebatch::set_ids(int index, ::google::protobuf::uint64 value) {
  ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:ukex.canceltradebatch.ids)
}
inline void canceltradebatch::add_ids(::google::protobuf::uint64 value) {
  ids_.Add(value);
  // @@protoc_insertion_point(field_add:ukex.canceltradebatch.ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
canceltradebatch::ids() const {
  // @@protoc_insertion_point(field_list:ukex.canceltradebatch.ids)
  return ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
canceltradebatch::mutable_ids() {
  // @@protoc_insertion_point(field_mutable_list:ukex.canceltradebatch.ids)
  return &ids_;
}

// required uint64 marketid = 3;
inline bool canceltradebatch::has_marketid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void canceltradebatch::set_has_marketid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void canceltradebatch::clear_has_marketid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void canceltradebatch::clear_marketid() {
  marketid_ = GOOGLE_ULONGLONG(0);
  clear_has_marketid();
}
inline ::google::protobuf::uint64 canceltradebatch::marketid() const {
  // @@protoc_insertion_point(field_get:ukex.canceltradebatch.marketid)
  return marketid_;
}
inline void canceltradebatch::set_marketid(::google::protobuf::uint64 value) {
  set_has_marketid();
  marketid_ = value;
  // @@protoc_insertion_point(field_set:ukex.canceltradebatch.marketid)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace ukex

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ukex::canceltradebatch_CONST> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ukex::canceltradebatch_CONST>() {
  return ::ukex::canceltradebatch_CONST_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ukex_2ecanceltradebatch_2eproto__INCLUDED
