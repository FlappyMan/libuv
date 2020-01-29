// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ukex.uptrade.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ukex.uptrade.pb.h"

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

const ::google::protobuf::Descriptor* uptrade_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  uptrade_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* uptrade_CONST_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ukex_2euptrade_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_ukex_2euptrade_2eproto() {
  protobuf_AddDesc_ukex_2euptrade_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ukex.uptrade.proto");
  GOOGLE_CHECK(file != NULL);
  uptrade_descriptor_ = file->message_type(0);
  static const int uptrade_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, token_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, paypassword_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, marketid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, price_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, num_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, main_coin_),
  };
  uptrade_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      uptrade_descriptor_,
      uptrade::default_instance_,
      uptrade_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, _has_bits_[0]),
      -1,
      -1,
      sizeof(uptrade),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(uptrade, _internal_metadata_),
      -1);
  uptrade_CONST_descriptor_ = uptrade_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ukex_2euptrade_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      uptrade_descriptor_, &uptrade::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ukex_2euptrade_2eproto() {
  delete uptrade::default_instance_;
  delete uptrade_reflection_;
}

void protobuf_AddDesc_ukex_2euptrade_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_ukex_2euptrade_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022ukex.uptrade.proto\022\004ukex\"\216\001\n\007uptrade\022\r"
    "\n\005token\030\001 \001(\t\022\023\n\013paypassword\030\002 \002(\t\022\020\n\010ma"
    "rketid\030\003 \002(\004\022\r\n\005price\030\004 \002(\004\022\013\n\003num\030\005 \002(\004"
    "\022\014\n\004type\030\006 \002(\r\022\021\n\tmain_coin\030\007 \001(\r\"\020\n\005CON"
    "ST\022\007\n\003CMD\020d", 171);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ukex.uptrade.proto", &protobuf_RegisterTypes);
  uptrade::default_instance_ = new uptrade();
  uptrade::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ukex_2euptrade_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ukex_2euptrade_2eproto {
  StaticDescriptorInitializer_ukex_2euptrade_2eproto() {
    protobuf_AddDesc_ukex_2euptrade_2eproto();
  }
} static_descriptor_initializer_ukex_2euptrade_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* uptrade_CONST_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return uptrade_CONST_descriptor_;
}
bool uptrade_CONST_IsValid(int value) {
  switch(value) {
    case 100:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const uptrade_CONST uptrade::CMD;
const uptrade_CONST uptrade::CONST_MIN;
const uptrade_CONST uptrade::CONST_MAX;
const int uptrade::CONST_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int uptrade::kTokenFieldNumber;
const int uptrade::kPaypasswordFieldNumber;
const int uptrade::kMarketidFieldNumber;
const int uptrade::kPriceFieldNumber;
const int uptrade::kNumFieldNumber;
const int uptrade::kTypeFieldNumber;
const int uptrade::kMainCoinFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

uptrade::uptrade()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ukex.uptrade)
}

void uptrade::InitAsDefaultInstance() {
}

uptrade::uptrade(const uptrade& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ukex.uptrade)
}

void uptrade::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  token_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  paypassword_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  marketid_ = GOOGLE_ULONGLONG(0);
  price_ = GOOGLE_ULONGLONG(0);
  num_ = GOOGLE_ULONGLONG(0);
  type_ = 0u;
  main_coin_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

uptrade::~uptrade() {
  // @@protoc_insertion_point(destructor:ukex.uptrade)
  SharedDtor();
}

void uptrade::SharedDtor() {
  token_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  paypassword_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void uptrade::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* uptrade::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return uptrade_descriptor_;
}

const uptrade& uptrade::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ukex_2euptrade_2eproto();
  return *default_instance_;
}

uptrade* uptrade::default_instance_ = NULL;

uptrade* uptrade::New(::google::protobuf::Arena* arena) const {
  uptrade* n = new uptrade;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void uptrade::Clear() {
// @@protoc_insertion_point(message_clear_start:ukex.uptrade)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(uptrade, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<uptrade*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 127u) {
    ZR_(marketid_, main_coin_);
    if (has_token()) {
      token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
    if (has_paypassword()) {
      paypassword_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool uptrade::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ukex.uptrade)
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
            "ukex.uptrade.token");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_paypassword;
        break;
      }

      // required string paypassword = 2;
      case 2: {
        if (tag == 18) {
         parse_paypassword:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_paypassword()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->paypassword().data(), this->paypassword().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "ukex.uptrade.paypassword");
        } else {
          goto handle_unusual;
        }
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
        if (input->ExpectTag(32)) goto parse_price;
        break;
      }

      // required uint64 price = 4;
      case 4: {
        if (tag == 32) {
         parse_price:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &price_)));
          set_has_price();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_num;
        break;
      }

      // required uint64 num = 5;
      case 5: {
        if (tag == 40) {
         parse_num:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &num_)));
          set_has_num();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_type;
        break;
      }

      // required uint32 type = 6;
      case 6: {
        if (tag == 48) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_main_coin;
        break;
      }

      // optional uint32 main_coin = 7;
      case 7: {
        if (tag == 56) {
         parse_main_coin:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &main_coin_)));
          set_has_main_coin();
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
  // @@protoc_insertion_point(parse_success:ukex.uptrade)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ukex.uptrade)
  return false;
#undef DO_
}

void uptrade::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ukex.uptrade)
  // optional string token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ukex.uptrade.token");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->token(), output);
  }

  // required string paypassword = 2;
  if (has_paypassword()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->paypassword().data(), this->paypassword().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ukex.uptrade.paypassword");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->paypassword(), output);
  }

  // required uint64 marketid = 3;
  if (has_marketid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->marketid(), output);
  }

  // required uint64 price = 4;
  if (has_price()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->price(), output);
  }

  // required uint64 num = 5;
  if (has_num()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(5, this->num(), output);
  }

  // required uint32 type = 6;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->type(), output);
  }

  // optional uint32 main_coin = 7;
  if (has_main_coin()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->main_coin(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ukex.uptrade)
}

::google::protobuf::uint8* uptrade::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ukex.uptrade)
  // optional string token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ukex.uptrade.token");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->token(), target);
  }

  // required string paypassword = 2;
  if (has_paypassword()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->paypassword().data(), this->paypassword().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ukex.uptrade.paypassword");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->paypassword(), target);
  }

  // required uint64 marketid = 3;
  if (has_marketid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->marketid(), target);
  }

  // required uint64 price = 4;
  if (has_price()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(4, this->price(), target);
  }

  // required uint64 num = 5;
  if (has_num()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(5, this->num(), target);
  }

  // required uint32 type = 6;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->type(), target);
  }

  // optional uint32 main_coin = 7;
  if (has_main_coin()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->main_coin(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ukex.uptrade)
  return target;
}

int uptrade::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:ukex.uptrade)
  int total_size = 0;

  if (has_paypassword()) {
    // required string paypassword = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->paypassword());
  }

  if (has_marketid()) {
    // required uint64 marketid = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->marketid());
  }

  if (has_price()) {
    // required uint64 price = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->price());
  }

  if (has_num()) {
    // required uint64 num = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->num());
  }

  if (has_type()) {
    // required uint32 type = 6;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->type());
  }

  return total_size;
}
int uptrade::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:ukex.uptrade)
  int total_size = 0;

  if (((_has_bits_[0] & 0x0000003e) ^ 0x0000003e) == 0) {  // All required fields are present.
    // required string paypassword = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->paypassword());

    // required uint64 marketid = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->marketid());

    // required uint64 price = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->price());

    // required uint64 num = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->num());

    // required uint32 type = 6;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->type());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_has_bits_[0 / 32] & 65u) {
    // optional string token = 1;
    if (has_token()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->token());
    }

    // optional uint32 main_coin = 7;
    if (has_main_coin()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->main_coin());
    }

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

void uptrade::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ukex.uptrade)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const uptrade* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const uptrade>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ukex.uptrade)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ukex.uptrade)
    MergeFrom(*source);
  }
}

void uptrade::MergeFrom(const uptrade& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ukex.uptrade)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_token()) {
      set_has_token();
      token_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.token_);
    }
    if (from.has_paypassword()) {
      set_has_paypassword();
      paypassword_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.paypassword_);
    }
    if (from.has_marketid()) {
      set_marketid(from.marketid());
    }
    if (from.has_price()) {
      set_price(from.price());
    }
    if (from.has_num()) {
      set_num(from.num());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_main_coin()) {
      set_main_coin(from.main_coin());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void uptrade::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ukex.uptrade)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void uptrade::CopyFrom(const uptrade& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ukex.uptrade)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool uptrade::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003e) != 0x0000003e) return false;

  return true;
}

void uptrade::Swap(uptrade* other) {
  if (other == this) return;
  InternalSwap(other);
}
void uptrade::InternalSwap(uptrade* other) {
  token_.Swap(&other->token_);
  paypassword_.Swap(&other->paypassword_);
  std::swap(marketid_, other->marketid_);
  std::swap(price_, other->price_);
  std::swap(num_, other->num_);
  std::swap(type_, other->type_);
  std::swap(main_coin_, other->main_coin_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata uptrade::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = uptrade_descriptor_;
  metadata.reflection = uptrade_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// uptrade

// optional string token = 1;
bool uptrade::has_token() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void uptrade::set_has_token() {
  _has_bits_[0] |= 0x00000001u;
}
void uptrade::clear_has_token() {
  _has_bits_[0] &= ~0x00000001u;
}
void uptrade::clear_token() {
  token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_token();
}
 const ::std::string& uptrade::token() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.token)
  return token_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void uptrade::set_token(const ::std::string& value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.uptrade.token)
}
 void uptrade::set_token(const char* value) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.uptrade.token)
}
 void uptrade::set_token(const char* value, size_t size) {
  set_has_token();
  token_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.uptrade.token)
}
 ::std::string* uptrade::mutable_token() {
  set_has_token();
  // @@protoc_insertion_point(field_mutable:ukex.uptrade.token)
  return token_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* uptrade::release_token() {
  // @@protoc_insertion_point(field_release:ukex.uptrade.token)
  clear_has_token();
  return token_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void uptrade::set_allocated_token(::std::string* token) {
  if (token != NULL) {
    set_has_token();
  } else {
    clear_has_token();
  }
  token_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:ukex.uptrade.token)
}

// required string paypassword = 2;
bool uptrade::has_paypassword() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void uptrade::set_has_paypassword() {
  _has_bits_[0] |= 0x00000002u;
}
void uptrade::clear_has_paypassword() {
  _has_bits_[0] &= ~0x00000002u;
}
void uptrade::clear_paypassword() {
  paypassword_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_paypassword();
}
 const ::std::string& uptrade::paypassword() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.paypassword)
  return paypassword_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void uptrade::set_paypassword(const ::std::string& value) {
  set_has_paypassword();
  paypassword_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ukex.uptrade.paypassword)
}
 void uptrade::set_paypassword(const char* value) {
  set_has_paypassword();
  paypassword_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ukex.uptrade.paypassword)
}
 void uptrade::set_paypassword(const char* value, size_t size) {
  set_has_paypassword();
  paypassword_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ukex.uptrade.paypassword)
}
 ::std::string* uptrade::mutable_paypassword() {
  set_has_paypassword();
  // @@protoc_insertion_point(field_mutable:ukex.uptrade.paypassword)
  return paypassword_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* uptrade::release_paypassword() {
  // @@protoc_insertion_point(field_release:ukex.uptrade.paypassword)
  clear_has_paypassword();
  return paypassword_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void uptrade::set_allocated_paypassword(::std::string* paypassword) {
  if (paypassword != NULL) {
    set_has_paypassword();
  } else {
    clear_has_paypassword();
  }
  paypassword_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), paypassword);
  // @@protoc_insertion_point(field_set_allocated:ukex.uptrade.paypassword)
}

// required uint64 marketid = 3;
bool uptrade::has_marketid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void uptrade::set_has_marketid() {
  _has_bits_[0] |= 0x00000004u;
}
void uptrade::clear_has_marketid() {
  _has_bits_[0] &= ~0x00000004u;
}
void uptrade::clear_marketid() {
  marketid_ = GOOGLE_ULONGLONG(0);
  clear_has_marketid();
}
 ::google::protobuf::uint64 uptrade::marketid() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.marketid)
  return marketid_;
}
 void uptrade::set_marketid(::google::protobuf::uint64 value) {
  set_has_marketid();
  marketid_ = value;
  // @@protoc_insertion_point(field_set:ukex.uptrade.marketid)
}

// required uint64 price = 4;
bool uptrade::has_price() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void uptrade::set_has_price() {
  _has_bits_[0] |= 0x00000008u;
}
void uptrade::clear_has_price() {
  _has_bits_[0] &= ~0x00000008u;
}
void uptrade::clear_price() {
  price_ = GOOGLE_ULONGLONG(0);
  clear_has_price();
}
 ::google::protobuf::uint64 uptrade::price() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.price)
  return price_;
}
 void uptrade::set_price(::google::protobuf::uint64 value) {
  set_has_price();
  price_ = value;
  // @@protoc_insertion_point(field_set:ukex.uptrade.price)
}

// required uint64 num = 5;
bool uptrade::has_num() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
void uptrade::set_has_num() {
  _has_bits_[0] |= 0x00000010u;
}
void uptrade::clear_has_num() {
  _has_bits_[0] &= ~0x00000010u;
}
void uptrade::clear_num() {
  num_ = GOOGLE_ULONGLONG(0);
  clear_has_num();
}
 ::google::protobuf::uint64 uptrade::num() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.num)
  return num_;
}
 void uptrade::set_num(::google::protobuf::uint64 value) {
  set_has_num();
  num_ = value;
  // @@protoc_insertion_point(field_set:ukex.uptrade.num)
}

// required uint32 type = 6;
bool uptrade::has_type() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
void uptrade::set_has_type() {
  _has_bits_[0] |= 0x00000020u;
}
void uptrade::clear_has_type() {
  _has_bits_[0] &= ~0x00000020u;
}
void uptrade::clear_type() {
  type_ = 0u;
  clear_has_type();
}
 ::google::protobuf::uint32 uptrade::type() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.type)
  return type_;
}
 void uptrade::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:ukex.uptrade.type)
}

// optional uint32 main_coin = 7;
bool uptrade::has_main_coin() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
void uptrade::set_has_main_coin() {
  _has_bits_[0] |= 0x00000040u;
}
void uptrade::clear_has_main_coin() {
  _has_bits_[0] &= ~0x00000040u;
}
void uptrade::clear_main_coin() {
  main_coin_ = 0u;
  clear_has_main_coin();
}
 ::google::protobuf::uint32 uptrade::main_coin() const {
  // @@protoc_insertion_point(field_get:ukex.uptrade.main_coin)
  return main_coin_;
}
 void uptrade::set_main_coin(::google::protobuf::uint32 value) {
  set_has_main_coin();
  main_coin_ = value;
  // @@protoc_insertion_point(field_set:ukex.uptrade.main_coin)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace ukex

// @@protoc_insertion_point(global_scope)
