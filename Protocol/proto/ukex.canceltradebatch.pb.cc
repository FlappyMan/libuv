// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ukex.canceltradebatch.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ukex.canceltradebatch.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ukex {

namespace {

const ::google::protobuf::Descriptor* canceltradebatch_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  canceltradebatch_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* canceltradebatch_CONST_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ukex_2ecanceltradebatch_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_ukex_2ecanceltradebatch_2eproto() {
  protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ukex.canceltradebatch.proto");
  GOOGLE_CHECK(file != NULL);
  canceltradebatch_descriptor_ = file->message_type(0);
  static const int canceltradebatch_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(canceltradebatch, token_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(canceltradebatch, ids_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(canceltradebatch, marketid_),
  };
  canceltradebatch_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      canceltradebatch_descriptor_,
      canceltradebatch::default_instance_,
      canceltradebatch_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(canceltradebatch, _has_bits_[0]),
      -1,
      -1,
      sizeof(canceltradebatch),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(canceltradebatch, _internal_metadata_),
      -1);
  canceltradebatch_CONST_descriptor_ = canceltradebatch_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ukex_2ecanceltradebatch_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      canceltradebatch_descriptor_, &canceltradebatch::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ukex_2ecanceltradebatch_2eproto() {
  delete canceltradebatch::default_instance_;
  delete canceltradebatch_reflection_;
}

void protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033ukex.canceltradebatch.proto\022\004ukex\"R\n\020c"
    "anceltradebatch\022\r\n\005token\030\001 \001(\t\022\013\n\003ids\030\002 "
    "\003(\004\022\020\n\010marketid\030\003 \002(\004\"\020\n\005CONST\022\007\n\003CMD\020g", 119);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ukex.canceltradebatch.proto", &protobuf_RegisterTypes);
  canceltradebatch::default_instance_ = new canceltradebatch();
  canceltradebatch::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ukex_2ecanceltradebatch_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ukex_2ecanceltradebatch_2eproto {
  StaticDescriptorInitializer_ukex_2ecanceltradebatch_2eproto() {
    protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto();
  }
} static_descriptor_initializer_ukex_2ecanceltradebatch_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* canceltradebatch_CONST_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return canceltradebatch_CONST_descriptor_;
}
bool canceltradebatch_CONST_IsValid(int value) {
  switch(value) {
    case 103:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const canceltradebatch_CONST canceltradebatch::CMD;
const canceltradebatch_CONST canceltradebatch::CONST_MIN;
const canceltradebatch_CONST canceltradebatch::CONST_MAX;
const int canceltradebatch::CONST_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int canceltradebatch::kTokenFieldNumber;
const int canceltradebatch::kIdsFieldNumber;
const int canceltradebatch::kMarketidFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

canceltradebatch::canceltradebatch()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ukex.canceltradebatch)
}

void canceltradebatch::InitAsDefaultInstance() {
}

canceltradebatch::canceltradebatch(const canceltradebatch& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ukex.canceltradebatch)
}

void canceltradebatch::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  token_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  marketid_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

canceltradebatch::~canceltradebatch() {
  // @@protoc_insertion_point(destructor:ukex.canceltradebatch)
  SharedDtor();
}

void canceltradebatch::SharedDtor() {
  token_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void canceltradebatch::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* canceltradebatch::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return canceltradebatch_descriptor_;
}

const canceltradebatch& canceltradebatch::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ukex_2ecanceltradebatch_2eproto();
  return *default_instance_;
}

canceltradebatch* canceltradebatch::default_instance_ = NULL;

canceltradebatch* canceltradebatch::New(::google::protobuf::Arena* arena) const {
  canceltradebatch* n = new canceltradebatch;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void canceltradebatch::Clear() {
// @@protoc_insertion_point(message_clear_start:ukex.canceltradebatch)
  if (_has_bits_[0 / 32] & 5u) {
    if (has_token()) {
      token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    marketid_ = GOOGLE_ULONGLONG(0);
  }
  ids_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool canceltradebatch::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ukex.canceltradebatch)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string token = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_token()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->token().data(), this->token().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "ukex.canceltradebatch.token");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_ids;
        break;
      }

      // repeated uint64 ids = 2;
      case 2: {
        if (tag == 16) {
         parse_ids:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 1, 16, input, this->mutable_ids())));
        } else if (tag == 18) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, this->mutable_ids())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_ids;
        if (input->ExpectTag(24)) goto parse_marketid;
        break;
      }

      // required uint64 marketid = 3;
      case 3: {
        if (tag == 24) {
         parse_marketid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &marketid_)));
          set_has_marketid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ukex.canceltradebatch)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ukex.canceltradebatch)
  return false;
#undef DO_
}

void canceltradebatch::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ukex.canceltradebatch)
  // optional string token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ukex.canceltradebatch.token");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->token(), output);
  }

  // repeated uint64 ids = 2;
  for (int i = 0; i < this->ids_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(
      2, this->ids(i), output);
  }

  // required uint64 marketid = 3;
  if (has_marketid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->marketid(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ukex.canceltradebatch)
}

::google::protobuf::uint8* canceltradebatch::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ukex.canceltradebatch)
  // optional string token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ukex.canceltradebatch.token");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->token(), target);
  }

  // repeated uint64 ids = 2;
  for (int i = 0; i < this->ids_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt64ToArray(2, this->ids(i), target);
  }

  // required uint64 marketid = 3;
  if (has_marketid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->marketid(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ukex.canceltradebatch)
  return target;
}

int canceltradebatch::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:ukex.canceltradebatch)
  int total_size = 0;

  // required uint64 marketid = 3;
  if (has_marketid()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->marketid());
  }
  // optional string token = 1;
  if (has_token()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->token());
  }

  // repeated uint64 ids = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->ids_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt64Size(this->ids(i));
    }
    total_size += 1 * this->ids_size() + data_size;
  }

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void canceltradebatch::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ukex.canceltradebatch)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const canceltradebatch* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const canceltradebatch>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ukex.canceltradebatch)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ukex.canceltradebatch)
    MergeFrom(*source);
  }
}

void canceltradebatch::MergeFrom(const canceltradebatch& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ukex.canceltradebatch)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  ids_.MergeFrom(from.ids_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_token()) {
      set_has_token();
      token_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.token_);
    }
    if (from.has_marketid()) {
      set_marketid(from.marketid());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void canceltradebatch::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ukex.canceltradebatch)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void canceltradebatch::CopyFrom(const canceltradebatch& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ukex.canceltradebatch)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool canceltradebatch::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000004) != 0x00000004) return false;

  return true;
}

void canceltradebatch::Swap(canceltradebatch* other) {
  if (other == this) return;
  InternalSwap(other);
}
void canceltradebatch::InternalSwap(canceltradebatch* other) {
  token_.Swap(&other->token_);
  ids_.UnsafeArenaSwap(&other->ids_);
  std::swap(marketid_, other->marketid_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata canceltradebatch::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = canceltradebatch_descriptor_;
  metadata.reflection = canceltradebatch_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// canceltradebatch

// optional string token = 1;
bool canceltradebatch::has_token() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void canceltradebatch::set_has_token() {
  _has_bits_[0] |= 0x00000001u;
}
void canceltradebatch::clear_has_token() {
  _has_bits_[0] &= ~0x00000001u;
}
void canceltradebatch::clear_token() {
  token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_token();
}
 const ::std::string& canceltradebatch::token() const {
  // @@protoc_insertion_point(field_get:ukex.canceltradebatch.token)
  return token_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void canceltradebatch::set_token(const ::std::string& value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.canceltradebatch.token)
}
 void canceltradebatch::set_token(const char* value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.canceltradebatch.token)
}
 void canceltradebatch::set_token(const char* value, size_t size) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.canceltradebatch.token)
}
 ::std::string* canceltradebatch::mutable_token() {
  set_has_token();
  // @@protoc_insertion_point(field_mutable:ukex.canceltradebatch.token)
  return token_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* canceltradebatch::release_token() {
  // @@protoc_insertion_point(field_release:ukex.canceltradebatch.token)
  clear_has_token();
  return token_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void canceltradebatch::set_allocated_token(::std::string* token) {
  if (token != NULL) {
    set_has_token();
  } else {
    clear_has_token();
  }
  token_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:ukex.canceltradebatch.token)
}

// repeated uint64 ids = 2;
int canceltradebatch::ids_size() const {
  return ids_.size();
}
void canceltradebatch::clear_ids() {
  ids_.Clear();
}
 ::google::protobuf::uint64 canceltradebatch::ids(int index) const {
  // @@protoc_insertion_point(field_get:ukex.canceltradebatch.ids)
  return ids_.Get(index);
}
 void canceltradebatch::set_ids(int index, ::google::protobuf::uint64 value) {
  ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:ukex.canceltradebatch.ids)
}
 void canceltradebatch::add_ids(::google::protobuf::uint64 value) {
  ids_.Add(value);
  // @@protoc_insertion_point(field_add:ukex.canceltradebatch.ids)
}
 const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
canceltradebatch::ids() const {
  // @@protoc_insertion_point(field_list:ukex.canceltradebatch.ids)
  return ids_;
}
 ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
canceltradebatch::mutable_ids() {
  // @@protoc_insertion_point(field_mutable_list:ukex.canceltradebatch.ids)
  return &ids_;
}

// required uint64 marketid = 3;
bool canceltradebatch::has_marketid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void canceltradebatch::set_has_marketid() {
  _has_bits_[0] |= 0x00000004u;
}
void canceltradebatch::clear_has_marketid() {
  _has_bits_[0] &= ~0x00000004u;
}
void canceltradebatch::clear_marketid() {
  marketid_ = GOOGLE_ULONGLONG(0);
  clear_has_marketid();
}
 ::google::protobuf::uint64 canceltradebatch::marketid() const {
  // @@protoc_insertion_point(field_get:ukex.canceltradebatch.marketid)
  return marketid_;
}
 void canceltradebatch::set_marketid(::google::protobuf::uint64 value) {
  set_has_marketid();
  marketid_ = value;
  // @@protoc_insertion_point(field_set:ukex.canceltradebatch.marketid)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace ukex

// @@protoc_insertion_point(global_scope)
