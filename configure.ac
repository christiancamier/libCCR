#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(cc_library, 0.2, christian.c@promethee.services)
AC_CONFIG_SRCDIR([cc_path.c])
AC_CONFIG_HEADERS([cc_machdep.h])

AC_SUBST(ccr_top_dir, [`(cd $srcdir/..; pwd;)`])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
AC_PROG_MAKE_SET
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_STAT
AC_HEADER_STDBOOL
AC_HEADER_DIRENT
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h], [], [])
AC_CHECK_HEADERS([fcntl.h], [], [])
AC_CHECK_HEADERS([libintl.h], [], [])
AC_CHECK_HEADERS([limits.h  paths.h], [], [])
AC_CHECK_HEADERS([stdint.h stdio.h stdio_ext.h stdlib.h string.h strings.h], [], [])
AC_CHECK_HEADERS([sys/ioctl.h sys/param.h sys/socket.h sys/time.h], [], [])
AC_CHECK_HEADERS([syslog.h termios.h unistd.h], [], [])

AC_MSG_CHECKING([architecture word width (32 or 64 bits)])
AC_RUN_IFELSE(
	[AC_LANG_PROGRAM([], [return 4 == sizeof(unsigned long) ? 0 : 1;])],
	[AC_DEFINE([ARCH_32BITS], [], [32 bits architecture]) AC_MSG_RESULT([32 bits])], 
	[AC_RUN_IFELSE(
		[AC_LANG_PROGRAM([], [return 8 == sizeof(unsigned long) ? 0 : 1;])],
		[AC_DEFINE([ARCH_64BITS], [], [64 bits architecture]) AC_MSG_RESULT([64 bits])],
		[AC_MSG_ERROR([unsuported architecture])])])

AC_MSG_CHECKING([Operating system name])
ac_ccr_system_name=`uname -s`
case "${ac_ccr_system_name}" in
FreeBSD)	AC_DEFINE([OS_FREEBSD], [], [Define if operating system is FreeBSD]);;
Linux)		AC_DEFINE([OS_LINUX],   [], [Define if operating system is Linux]);;
NetBSD)		AC_DEFINE([OS_NETBSD],  [], [Define if operating system is NetBSD]);;
OpenBSD)	AC_DEFINE([OS_OPENBSD], [], [Define if operating system is OpenBSD]);;
# Place here other operating systems
*)		AC_DEFINE([OS_OTHER], [], [Define if not a known os]);;
esac
AC_MSG_RESULT([$ac_ccr_system_name])

AC_CHECK_FILES([/dev/arandom /dev/random /dev/urandom])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_MSG_CHECKING([for an ANSI C-conforming signed])
AC_RUN_IFELSE(
	[AC_LANG_PROGRAM([signed int x = 0;], [return (int)x;])],
        [AC_MSG_RESULT([yes])],
        [AC_DEFINE([signed], [], [Define to empty if `signed' does not conform to ANSI C.]) AC_MSG_RESULT([no])])
AC_STRUCT_TM
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPE(int64_t,  AC_DEFINE([HAVE_SINT64_T], [], [int64_t type is defined]), [])
AC_CHECK_TYPE(uint64_t, AC_DEFINE([HAVE_UINT64_T], [], [int64_t type is defined]), [])
AC_CHECK_MEMBERS([struct stat.st_blksize], [], [struct stat.stat is required])

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([alarm atexit dup2 memset pathconf realpath strcasecmp strerror strrchr])

AC_DEFINE_UNQUOTED([OS_NAME], "$ac_ccr_system_name", [Operating system name])
AC_DEFINE_UNQUOTED([DIR_ETC], "`echo $sysconfdir`", [System configuration directory])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
