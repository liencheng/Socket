// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PbMsg.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "PbMsg.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Protobuf {

namespace {

const ::google::protobuf::Descriptor* CS_PING_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  CS_PING_reflection_ = NULL;
const ::google::protobuf::Descriptor* SC_PONG_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SC_PONG_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_PbMsg_2eproto() {
  protobuf_AddDesc_PbMsg_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "PbMsg.proto");
  GOOGLE_CHECK(file != NULL);
  CS_PING_descriptor_ = file->message_type(0);
  static const int CS_PING_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_PING, ansi_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_PING, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_PING, name_),
  };
  CS_PING_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      CS_PING_descriptor_,
      CS_PING::default_instance_,
      CS_PING_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_PING, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CS_PING, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(CS_PING));
  SC_PONG_descriptor_ = file->message_type(1);
  static const int SC_PONG_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SC_PONG, ansi_time_),
  };
  SC_PONG_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SC_PONG_descriptor_,
      SC_PONG::default_instance_,
      SC_PONG_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SC_PONG, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SC_PONG, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SC_PONG));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_PbMsg_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    CS_PING_descriptor_, &CS_PING::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SC_PONG_descriptor_, &SC_PONG::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_PbMsg_2eproto() {
  delete CS_PING::default_instance_;
  delete CS_PING_reflection_;
  delete SC_PONG::default_instance_;
  delete SC_PONG_reflection_;
}

void protobuf_AddDesc_PbMsg_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013PbMsg.proto\022\010Protobuf\"6\n\007CS_PING\022\021\n\tan"
    "si_time\030\001 \002(\005\022\n\n\002id\030\002 \002(\005\022\014\n\004name\030\003 \002(\t\""
    "\034\n\007SC_PONG\022\021\n\tansi_time\030\001 \002(\005", 109);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "PbMsg.proto", &protobuf_RegisterTypes);
  CS_PING::default_instance_ = new CS_PING();
  SC_PONG::default_instance_ = new SC_PONG();
  CS_PING::default_instance_->InitAsDefaultInstance();
  SC_PONG::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_PbMsg_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_PbMsg_2eproto {
  StaticDescriptorInitializer_PbMsg_2eproto() {
    protobuf_AddDesc_PbMsg_2eproto();
  }
} static_descriptor_initializer_PbMsg_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int CS_PING::kAnsiTimeFieldNumber;
const int CS_PING::kIdFieldNumber;
const int CS_PING::kNameFieldNumber;
#endif  // !_MSC_VER

CS_PING::CS_PING()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Protobuf.CS_PING)
}

void CS_PING::InitAsDefaultInstance() {
}

CS_PING::CS_PING(const CS_PING& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Protobuf.CS_PING)
}

void CS_PING::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  ansi_time_ = 0;
  id_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CS_PING::~CS_PING() {
  // @@protoc_insertion_point(destructor:Protobuf.CS_PING)
  SharedDtor();
}

void CS_PING::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (this != default_instance_) {
  }
}

void CS_PING::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CS_PING::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return CS_PING_descriptor_;
}

const CS_PING& CS_PING::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_PbMsg_2eproto();
  return *default_instance_;
}

CS_PING* CS_PING::default_instance_ = NULL;

CS_PING* CS_PING::New() const {
  return new CS_PING;
}

void CS_PING::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<CS_PING*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(ansi_time_, id_);
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool CS_PING::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Protobuf.CS_PING)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 ansi_time = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ansi_time_)));
          set_has_ansi_time();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_id;
        break;
      }

      // required int32 id = 2;
      case 2: {
        if (tag == 16) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_name;
        break;
      }

      // required string name = 3;
      case 3: {
        if (tag == 26) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "name");
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
  // @@protoc_insertion_point(parse_success:Protobuf.CS_PING)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Protobuf.CS_PING)
  return false;
#undef DO_
}

void CS_PING::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Protobuf.CS_PING)
  // required int32 ansi_time = 1;
  if (has_ansi_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->ansi_time(), output);
  }

  // required int32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->id(), output);
  }

  // required string name = 3;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Protobuf.CS_PING)
}

::google::protobuf::uint8* CS_PING::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protobuf.CS_PING)
  // required int32 ansi_time = 1;
  if (has_ansi_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->ansi_time(), target);
  }

  // required int32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->id(), target);
  }

  // required string name = 3;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protobuf.CS_PING)
  return target;
}

int CS_PING::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 ansi_time = 1;
    if (has_ansi_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->ansi_time());
    }

    // required int32 id = 2;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

    // required string name = 3;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CS_PING::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const CS_PING* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const CS_PING*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void CS_PING::MergeFrom(const CS_PING& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ansi_time()) {
      set_ansi_time(from.ansi_time());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void CS_PING::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CS_PING::CopyFrom(const CS_PING& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CS_PING::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void CS_PING::Swap(CS_PING* other) {
  if (other != this) {
    std::swap(ansi_time_, other->ansi_time_);
    std::swap(id_, other->id_);
    std::swap(name_, other->name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata CS_PING::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = CS_PING_descriptor_;
  metadata.reflection = CS_PING_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SC_PONG::kAnsiTimeFieldNumber;
#endif  // !_MSC_VER

SC_PONG::SC_PONG()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Protobuf.SC_PONG)
}

void SC_PONG::InitAsDefaultInstance() {
}

SC_PONG::SC_PONG(const SC_PONG& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Protobuf.SC_PONG)
}

void SC_PONG::SharedCtor() {
  _cached_size_ = 0;
  ansi_time_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SC_PONG::~SC_PONG() {
  // @@protoc_insertion_point(destructor:Protobuf.SC_PONG)
  SharedDtor();
}

void SC_PONG::SharedDtor() {
  if (this != default_instance_) {
  }
}

void SC_PONG::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SC_PONG::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SC_PONG_descriptor_;
}

const SC_PONG& SC_PONG::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_PbMsg_2eproto();
  return *default_instance_;
}

SC_PONG* SC_PONG::default_instance_ = NULL;

SC_PONG* SC_PONG::New() const {
  return new SC_PONG;
}

void SC_PONG::Clear() {
  ansi_time_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SC_PONG::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Protobuf.SC_PONG)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 ansi_time = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ansi_time_)));
          set_has_ansi_time();
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
  // @@protoc_insertion_point(parse_success:Protobuf.SC_PONG)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Protobuf.SC_PONG)
  return false;
#undef DO_
}

void SC_PONG::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Protobuf.SC_PONG)
  // required int32 ansi_time = 1;
  if (has_ansi_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->ansi_time(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Protobuf.SC_PONG)
}

::google::protobuf::uint8* SC_PONG::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protobuf.SC_PONG)
  // required int32 ansi_time = 1;
  if (has_ansi_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->ansi_time(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protobuf.SC_PONG)
  return target;
}

int SC_PONG::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 ansi_time = 1;
    if (has_ansi_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->ansi_time());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SC_PONG::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SC_PONG* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SC_PONG*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SC_PONG::MergeFrom(const SC_PONG& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ansi_time()) {
      set_ansi_time(from.ansi_time());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SC_PONG::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SC_PONG::CopyFrom(const SC_PONG& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SC_PONG::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void SC_PONG::Swap(SC_PONG* other) {
  if (other != this) {
    std::swap(ansi_time_, other->ansi_time_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SC_PONG::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SC_PONG_descriptor_;
  metadata.reflection = SC_PONG_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protobuf

// @@protoc_insertion_point(global_scope)
