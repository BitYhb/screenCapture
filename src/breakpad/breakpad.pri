HEADERS += \
    $$PWD/crashhandler.h  \
    $$PWD/src/client/minidump_file_writer-inl.h \
    $$PWD/src/client/minidump_file_writer.h \
    $$PWD/src/client/windows/common/auto_critical_section.h \
    $$PWD/src/client/windows/common/ipc_protocol.h \
    $$PWD/src/client/windows/crash_generation/crash_generation_client.h \
    $$PWD/src/client/windows/handler/exception_handler.h \
    $$PWD/src/common/basictypes.h \
    $$PWD/src/common/convert_UTF.h \
    $$PWD/src/common/linux/linux_libc_support.h \
    $$PWD/src/common/macros.h \
    $$PWD/src/common/memory_allocator.h \
    $$PWD/src/common/memory_range.h \
    $$PWD/src/common/scoped_ptr.h \
    $$PWD/src/common/string_conversion.h \
    $$PWD/src/common/using_std_string.h \
    $$PWD/src/common/windows/guid_string.h \
    $$PWD/src/common/windows/string_utils-inl.h \
    $$PWD/src/google_breakpad/common/breakpad_types.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_amd64.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_arm.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_arm64.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_mips.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_ppc.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_ppc64.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_sparc.h \
    $$PWD/src/google_breakpad/common/minidump_cpu_x86.h \
    $$PWD/src/google_breakpad/common/minidump_exception_fuchsia.h \
    $$PWD/src/google_breakpad/common/minidump_exception_linux.h \
    $$PWD/src/google_breakpad/common/minidump_exception_mac.h \
    $$PWD/src/google_breakpad/common/minidump_exception_ps3.h \
    $$PWD/src/google_breakpad/common/minidump_exception_solaris.h \
    $$PWD/src/google_breakpad/common/minidump_exception_win32.h \
    $$PWD/src/google_breakpad/common/minidump_format.h \
    $$PWD/src/google_breakpad/common/minidump_size.h \
    $$PWD/src/third_party/lss/linux_syscall_support.h

SOURCES += \
    $$PWD/crashhandler.cpp \
    $$PWD/src/client/minidump_file_writer.cc \
    $$PWD/src/client/windows/crash_generation/crash_generation_client.cc \
    $$PWD/src/client/windows/handler/exception_handler.cc \
    $$PWD/src/common/convert_UTF.cc \
    $$PWD/src/common/string_conversion.cc \
    $$PWD/src/common/windows/guid_string.cc \
    $$PWD/src/common/windows/string_utils.cc
