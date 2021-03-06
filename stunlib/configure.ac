#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([stunlib], [0.2], [palmarti@cisco.com])
AC_CONFIG_SRCDIR([include/stunlib.h])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
LT_INIT

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O


AC_ARG_ENABLE(gcov,
AS_HELP_STRING([--enable-gcov],
               [enable test coverage with gcov @<:@default=no@:>@]),
              [case "${enableval}" in
                 yes) gcov=true ;;
                 no)  gcov=false ;;
                 *)   AC_MSG_ERROR([bad value ${enableval} for --enable-gcov]) ;;
               esac],
              [gcov=false])

AM_CONDITIONAL(GCOV, test x"$gcov" = "xtrue")

# Support for running test cases using valgrind:
use_valgrind=false
AC_ARG_ENABLE(valgrind,
[  --enable-valgrind       Use valgrind when running unit tests. ],
[ use_valgrind=true ])

if [[ "$use_valgrind" = "true" ]]; then
        AC_CHECK_PROG(HAVE_VALGRIND, valgrind, yes, no)

        if [[ "$HAVE_VALGRIND" = "no" ]]; then
                AC_MSG_ERROR([Valgrind not found in PATH. ])
        fi
fi
AM_CONDITIONAL(USE_VALGRIND, $use_valgrind)

AM_CONDITIONAL(CHECK, "false")
AC_ARG_WITH([check],
  [AS_HELP_STRING([--with-check],
  [use Check for unit testing @<:@default=no@:>@])],
  [],
  [with_check=no])

  LIBCHECK=
  AS_IF([test "x$with_check" != xno],
    [AC_CHECK_LIB([check], [srunner_create],
    [AC_SUBST([LIBCHECK], ["-lcheck"])
     AM_CONDITIONAL(CHECK, "true")
     AC_DEFINE([HAVE_CHECK], [1],
               [Define if you have check])],
    [AC_MSG_FAILURE(
      [--with-check was given, but test for check failed])],
      [])])

# Checks for libraries.
#AC_CHECK_LIB([check], [srunner_create])

AC_CHECK_FILE(../sockaddrutil/include/sockaddr_util.h, local_sockaddr=true, local_sockaddr=false )

AM_CONDITIONAL(LOCAL_SOCKADDR, test x"$local_sockaddr" = "xtrue")



AM_COND_IF(LOCAL_SOCKADDR,
           [],
[AC_CHECK_LIB([sockaddrutil], [sockaddr_initFromString],[], [AC_MSG_FAILURE([could not find sockaddrutil])])])

dnl AC_CHECK_LIB([ssl], [SSL_library_init], [], [AC_MSG_FAILURE([could not find ssl])])

AC_CHECK_LIB([crypto], [MD5], [], [AC_MSG_FAILURE([could not find crypto])])
AC_CHECK_LIB([z], [crc32], [], [AC_MSG_FAILURE([could not find libz])])

dnl AC_CHECK_LIB([gsasl], [gsasl_check_version], [], [AC_MSG_FAILURE([could not find gsasl])])



# Checks for header files.
AC_CHECK_HEADERS([netinet/in.h stddef.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])

AC_OUTPUT
