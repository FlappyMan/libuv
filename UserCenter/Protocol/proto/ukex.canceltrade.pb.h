// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ukex.canceltrade.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ukex_2ecanceltrade_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ukex_2ecanceltrade_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3010000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3010000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ukex_2ecanceltrade_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ukex_2ecanceltrade_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ukex_2ecanceltrade_2eproto;
namespace ukex {
class canceltrade;
class canceltradeDefaultTypeInternal;
extern canceltradeDefaultTypeInternal _canceltrade_default_instance_;
}  // namespace ukex
PROTOBUF_NAMESPACE_OPEN
template<> ::ukex::canceltrade* Arena::CreateMaybeMessage<::ukex::canceltrade>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ukex {

enum canceltrade_CONST : int {
  canceltrade_CONST_CMD = 102
};
bool canceltrade_CONST_IsValid(int value);
constexpr canceltrade_CONST canceltrade_CONST_CONST_MIN = canceltrade_CONST_CMD;
constexpr canceltrade_CONST canceltrade_CONST_CONST_MAX = canceltrade_CONST_CMD;
constexpr int canceltrade_CONST_CONST_ARRAYSIZE = canceltrade_CONST_CONST_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* canceltrade_CONST_descriptor();
template<typename T>
inline const std::string& canceltrade_CONST_Name(T enum_t_value) {
  static_assert(::std::is_same<T, canceltrade_CONST>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function canceltrade_CONST_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    canceltrade_CONST_descriptor(), enum_t_value);
}
inline bool canceltrade_CONST_Parse(
    const std::string& name, canceltrade_CONST* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<canceltrade_CONST>(
    canceltrade_CONST_descriptor(), name, value);
}
// ===================================================================

class canceltrade :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ukex.canceltrade) */ {
 public:
  canceltrade();
  virtual ~canceltrade();

  canceltrade(const canceltrade& from);
  canceltrade(canceltrade&& from) noexcept
    : canceltrade() {
    *this = ::std::move(from);
  }

  inline canceltrade& operator=(const canceltrade& from) {
    CopyFrom(from);
    return *this;
  }
  inline canceltrade& operator=(canceltrade&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const canceltrade& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const canceltrade* internal_default_instance() {
    return reinterpret_cast<const canceltrade*>(
               &_canceltrade_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(canceltrade& a, canceltrade& b) {
    a.Swap(&b);
  }
  inline void Swap(canceltrade* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline canceltrade* New() const final {
    return CreateMaybeMessage<canceltrade>(nullptr);
  }

  canceltrade* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<canceltrade>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const canceltrade& from);
  void MergeFrom(const canceltrade& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(canceltrade* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ukex.canceltrade";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ukex_2ecanceltrade_2eproto);
    return ::descriptor_table_ukex_2ecanceltrade_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef canceltrade_CONST CONST;
  static constexpr CONST CMD =
    canceltrade_CONST_CMD;
  static inline bool CONST_IsValid(int value) {
    return canceltrade_CONST_IsValid(value);
  }
  static constexpr CONST CONST_MIN =
    canceltrade_CONST_CONST_MIN;
  static constexpr CONST CONST_MAX =
    canceltrade_CONST_CONST_MAX;
  static constexpr int CONST_ARRAYSIZE =
    canceltrade_CONST_CONST_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  CONST_descriptor() {
    return canceltrade_CONST_descriptor();
  }
  template<typename T>
  static inline const std::string& CONST_Name(T enum_t_value) {
    static_assert(::std::is_same<T, CONST>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function CONST_Name.");
    return canceltrade_CONST_Name(enum_t_value);
  }
  static inline bool CONST_Parse(const std::string& name,
      CONST* value) {
    return canceltrade_CONST_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kTokenFieldNumber = 1,
    kIdFieldNumber = 2,
    kMarketidFieldNumber = 3,
  };
  // required string token = 1;
  bool has_token() const;
  private:
  bool _internal_has_token() const;
  public:
  void clear_token();
  const std::string& token() const;
  void set_token(const std::string& value);
  void set_token(std::string&& value);
  void set_token(const char* value);
  void set_token(const char* value, size_t size);
  std::string* mutable_token();
  std::string* release_token();
  void set_allocated_token(std::string* token);
  private:
  const std::string& _internal_token() const;
  void _internal_set_token(const std::string& value);
  std::string* _internal_mutable_token();
  public:

  // required uint64 id = 2;
  bool has_id() const;
  private:
  bool _internal_has_id() const;
  public:
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // required uint64 marketid = 3;
  bool has_marketid() const;
  private:
  bool _internal_has_marketid() const;
  public:
  void clear_marketid();
  ::PROTOBUF_NAMESPACE_ID::uint64 marketid() const;
  void set_marketid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_marketid() const;
  void _internal_set_marketid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // @@protoc_insertion_point(class_scope:ukex.canceltrade)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr token_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint64 marketid_;
  friend struct ::TableStruct_ukex_2ecanceltrade_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// canceltrade

// required string token = 1;
inline bool canceltrade::_internal_has_token() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool canceltrade::has_token() const {
  return _internal_has_token();
}
inline void canceltrade::clear_token() {
  token_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& canceltrade::token() const {
  // @@protoc_insertion_point(field_get:ukex.canceltrade.token)
  return _internal_token();
}
inline void canceltrade::set_token(const std::string& value) {
  _internal_set_token(value);
  // @@protoc_insertion_point(field_set:ukex.canceltrade.token)
}
inline std::string* canceltrade::mutable_token() {
  // @@protoc_insertion_point(field_mutable:ukex.canceltrade.token)
  return _internal_mutable_token();
}
inline const std::string& canceltrade::_internal_token() const {
  return token_.GetNoArena();
}
inline void canceltrade::_internal_set_token(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void canceltrade::set_token(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  token_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:ukex.canceltrade.token)
}
inline void canceltrade::set_token(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.canceltrade.token)
}
inline void canceltrade::set_token(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.canceltrade.token)
}
inline std::string* canceltrade::_internal_mutable_token() {
  _has_bits_[0] |= 0x00000001u;
  return token_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* canceltrade::release_token() {
  // @@protoc_insertion_point(field_release:ukex.canceltrade.token)
  if (!has_token()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return token_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void canceltrade::set_allocated_token(std::string* token) {
  if (token != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  token_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:ukex.canceltrade.token)
}

// required uint64 id = 2;
inline bool canceltrade::_internal_has_id() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool canceltrade::has_id() const {
  return _internal_has_id();
}
inline void canceltrade::clear_id() {
  id_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 canceltrade::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 canceltrade::id() const {
  // @@protoc_insertion_point(field_get:ukex.canceltrade.id)
  return _internal_id();
}
inline void canceltrade::_internal_set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000002u;
  id_ = value;
}
inline void canceltrade::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:ukex.canceltrade.id)
}

// required uint64 marketid = 3;
inline bool canceltrade::_internal_has_marketid() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool canceltrade::has_marketid() const {
  return _internal_has_marketid();
}
inline void canceltrade::clear_marketid() {
  marketid_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 canceltrade::_internal_marketid() const {
  return marketid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 canceltrade::marketid() const {
  // @@protoc_insertion_point(field_get:ukex.canceltrade.marketid)
  return _internal_marketid();
}
inline void canceltrade::_internal_set_marketid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000004u;
  marketid_ = value;
}
inline void canceltrade::set_marketid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_marketid(value);
  // @@protoc_insertion_point(field_set:ukex.canceltrade.marketid)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ukex

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::ukex::canceltrade_CONST> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ukex::canceltrade_CONST>() {
  return ::ukex::canceltrade_CONST_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ukex_2ecanceltrade_2eproto
