// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PbMsg.proto

#include "PbMsg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
class test_msgDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<test_msg> _instance;
} _test_msg_default_instance_;
class CS_PINGDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<CS_PING> _instance;
} _CS_PING_default_instance_;
class SC_PONGDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<SC_PONG> _instance;
} _SC_PONG_default_instance_;
static void InitDefaultsscc_info_CS_PING_PbMsg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_CS_PING_default_instance_;
    new (ptr) ::CS_PING();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::CS_PING::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_CS_PING_PbMsg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_CS_PING_PbMsg_2eproto}, {}};

static void InitDefaultsscc_info_SC_PONG_PbMsg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_SC_PONG_default_instance_;
    new (ptr) ::SC_PONG();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::SC_PONG::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_SC_PONG_PbMsg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_SC_PONG_PbMsg_2eproto}, {}};

static void InitDefaultsscc_info_test_msg_PbMsg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_test_msg_default_instance_;
    new (ptr) ::test_msg();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::test_msg::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_test_msg_PbMsg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_test_msg_PbMsg_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_PbMsg_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_PbMsg_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_PbMsg_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_PbMsg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::test_msg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::test_msg, test_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::CS_PING, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::CS_PING, m_ansitime_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::SC_PONG, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::SC_PONG, m_ansitime_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::test_msg)},
  { 6, -1, sizeof(::CS_PING)},
  { 12, -1, sizeof(::SC_PONG)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_test_msg_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_CS_PING_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_SC_PONG_default_instance_),
};

const char descriptor_table_protodef_PbMsg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013PbMsg.proto\"\030\n\010test_msg\022\014\n\004test\030\001 \001(\005\""
  "\035\n\007CS_PING\022\022\n\nm_AnsiTime\030\001 \001(\005\"\035\n\007SC_PON"
  "G\022\022\n\nm_AnsiTime\030\001 \001(\005b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_PbMsg_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_PbMsg_2eproto_sccs[3] = {
  &scc_info_CS_PING_PbMsg_2eproto.base,
  &scc_info_SC_PONG_PbMsg_2eproto.base,
  &scc_info_test_msg_PbMsg_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_PbMsg_2eproto_once;
static bool descriptor_table_PbMsg_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_PbMsg_2eproto = {
  &descriptor_table_PbMsg_2eproto_initialized, descriptor_table_protodef_PbMsg_2eproto, "PbMsg.proto", 109,
  &descriptor_table_PbMsg_2eproto_once, descriptor_table_PbMsg_2eproto_sccs, descriptor_table_PbMsg_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_PbMsg_2eproto::offsets,
  file_level_metadata_PbMsg_2eproto, 3, file_level_enum_descriptors_PbMsg_2eproto, file_level_service_descriptors_PbMsg_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_PbMsg_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_PbMsg_2eproto), true);

// ===================================================================

void test_msg::InitAsDefaultInstance() {
}
class test_msg::_Internal {
 public:
};

test_msg::test_msg()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:test_msg)
}
test_msg::test_msg(const test_msg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  test_ = from.test_;
  // @@protoc_insertion_point(copy_constructor:test_msg)
}

void test_msg::SharedCtor() {
  test_ = 0;
}

test_msg::~test_msg() {
  // @@protoc_insertion_point(destructor:test_msg)
  SharedDtor();
}

void test_msg::SharedDtor() {
}

void test_msg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const test_msg& test_msg::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_test_msg_PbMsg_2eproto.base);
  return *internal_default_instance();
}


void test_msg::Clear() {
// @@protoc_insertion_point(message_clear_start:test_msg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  test_ = 0;
  _internal_metadata_.Clear();
}

const char* test_msg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 test = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          test_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* test_msg::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:test_msg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 test = 1;
  if (this->test() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_test(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test_msg)
  return target;
}

size_t test_msg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:test_msg)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 test = 1;
  if (this->test() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_test());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void test_msg::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:test_msg)
  GOOGLE_DCHECK_NE(&from, this);
  const test_msg* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<test_msg>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:test_msg)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:test_msg)
    MergeFrom(*source);
  }
}

void test_msg::MergeFrom(const test_msg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:test_msg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.test() != 0) {
    _internal_set_test(from._internal_test());
  }
}

void test_msg::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:test_msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void test_msg::CopyFrom(const test_msg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:test_msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool test_msg::IsInitialized() const {
  return true;
}

void test_msg::InternalSwap(test_msg* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(test_, other->test_);
}

::PROTOBUF_NAMESPACE_ID::Metadata test_msg::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void CS_PING::InitAsDefaultInstance() {
}
class CS_PING::_Internal {
 public:
};

CS_PING::CS_PING()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:CS_PING)
}
CS_PING::CS_PING(const CS_PING& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  m_ansitime_ = from.m_ansitime_;
  // @@protoc_insertion_point(copy_constructor:CS_PING)
}

void CS_PING::SharedCtor() {
  m_ansitime_ = 0;
}

CS_PING::~CS_PING() {
  // @@protoc_insertion_point(destructor:CS_PING)
  SharedDtor();
}

void CS_PING::SharedDtor() {
}

void CS_PING::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const CS_PING& CS_PING::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_CS_PING_PbMsg_2eproto.base);
  return *internal_default_instance();
}


void CS_PING::Clear() {
// @@protoc_insertion_point(message_clear_start:CS_PING)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  m_ansitime_ = 0;
  _internal_metadata_.Clear();
}

const char* CS_PING::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 m_AnsiTime = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          m_ansitime_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* CS_PING::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:CS_PING)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 m_AnsiTime = 1;
  if (this->m_ansitime() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_m_ansitime(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CS_PING)
  return target;
}

size_t CS_PING::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:CS_PING)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 m_AnsiTime = 1;
  if (this->m_ansitime() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_m_ansitime());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void CS_PING::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:CS_PING)
  GOOGLE_DCHECK_NE(&from, this);
  const CS_PING* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<CS_PING>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:CS_PING)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:CS_PING)
    MergeFrom(*source);
  }
}

void CS_PING::MergeFrom(const CS_PING& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:CS_PING)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.m_ansitime() != 0) {
    _internal_set_m_ansitime(from._internal_m_ansitime());
  }
}

void CS_PING::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:CS_PING)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CS_PING::CopyFrom(const CS_PING& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:CS_PING)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CS_PING::IsInitialized() const {
  return true;
}

void CS_PING::InternalSwap(CS_PING* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(m_ansitime_, other->m_ansitime_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CS_PING::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void SC_PONG::InitAsDefaultInstance() {
}
class SC_PONG::_Internal {
 public:
};

SC_PONG::SC_PONG()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:SC_PONG)
}
SC_PONG::SC_PONG(const SC_PONG& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  m_ansitime_ = from.m_ansitime_;
  // @@protoc_insertion_point(copy_constructor:SC_PONG)
}

void SC_PONG::SharedCtor() {
  m_ansitime_ = 0;
}

SC_PONG::~SC_PONG() {
  // @@protoc_insertion_point(destructor:SC_PONG)
  SharedDtor();
}

void SC_PONG::SharedDtor() {
}

void SC_PONG::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SC_PONG& SC_PONG::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_SC_PONG_PbMsg_2eproto.base);
  return *internal_default_instance();
}


void SC_PONG::Clear() {
// @@protoc_insertion_point(message_clear_start:SC_PONG)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  m_ansitime_ = 0;
  _internal_metadata_.Clear();
}

const char* SC_PONG::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 m_AnsiTime = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          m_ansitime_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* SC_PONG::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:SC_PONG)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 m_AnsiTime = 1;
  if (this->m_ansitime() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_m_ansitime(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SC_PONG)
  return target;
}

size_t SC_PONG::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:SC_PONG)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 m_AnsiTime = 1;
  if (this->m_ansitime() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_m_ansitime());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SC_PONG::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SC_PONG)
  GOOGLE_DCHECK_NE(&from, this);
  const SC_PONG* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<SC_PONG>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SC_PONG)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SC_PONG)
    MergeFrom(*source);
  }
}

void SC_PONG::MergeFrom(const SC_PONG& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SC_PONG)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.m_ansitime() != 0) {
    _internal_set_m_ansitime(from._internal_m_ansitime());
  }
}

void SC_PONG::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SC_PONG)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SC_PONG::CopyFrom(const SC_PONG& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SC_PONG)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SC_PONG::IsInitialized() const {
  return true;
}

void SC_PONG::InternalSwap(SC_PONG* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(m_ansitime_, other->m_ansitime_);
}

::PROTOBUF_NAMESPACE_ID::Metadata SC_PONG::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::test_msg* Arena::CreateMaybeMessage< ::test_msg >(Arena* arena) {
  return Arena::CreateInternal< ::test_msg >(arena);
}
template<> PROTOBUF_NOINLINE ::CS_PING* Arena::CreateMaybeMessage< ::CS_PING >(Arena* arena) {
  return Arena::CreateInternal< ::CS_PING >(arena);
}
template<> PROTOBUF_NOINLINE ::SC_PONG* Arena::CreateMaybeMessage< ::SC_PONG >(Arena* arena) {
  return Arena::CreateInternal< ::SC_PONG >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
