dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.13])
AC_INIT([glade], [0.6.4], [damon@ximian.com])
AC_CONFIG_SRCDIR([glade/gbwidget.c])
AC_CONFIG_AUX_DIR([build-aux])dnl

AM_INIT_AUTOMAKE([foreign])
AM_MAINTAINER_MODE
AM_SANITY_CHECK
AC_CONFIG_HEADERS([config.h])
AC_USE_SYSTEM_EXTENSIONS

dnl# Pick up GNOME macros
AC_CONFIG_MACRO_DIR([macros])
AM_ACLOCAL_INCLUDE([macros])dnl

AX_LIB_XML_SECURITY
AM_PATH_XML2

AC_ISC_POSIX

AM_PROG_LIBTOOL
IT_PROG_INTLTOOL

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_MKDIR_P
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for header files.
AC_HEADER_STDC
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([argz.h fcntl.h libintl.h limits.h locale.h malloc.h nl_types.h os2.h stddef.h stdlib.h string.h strings.h sys/param.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([__argz_count __argz_next __argz_stringify getcwd mempcpy mkdir munmap putenv setenv setlocale stpcpy strcasecmp strchr strdup strrchr tzset])

dnl ***************************************************************************
dnl GTK+ - Checks the version and sets GTK_CFLAGS & GTK_LIBS.
dnl ***************************************************************************

AM_PATH_GTK([1.2.0],[], [AC_MSG_ERROR([Cannot find GTK: Is gtk-config in path?])])


dnl ***************************************************************************
dnl Gettext stuff.
dnl ***************************************************************************

ALL_LINGUAS="az ca cs da de el en_GB es fr ga gl hu it ja ko lv nl nn no pl pt pt_BR ro ru sk sv tr uk zh_CN"
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18.2])
BISON_I18N
#AM_GNOME_GETTEXT

dnl Set the location of the locale messages to be used in main.c
dnl This will substitute GLADE_LOCALE_DIR in config.h (from acconfig.h).
if test "x$prefix" = "xNONE"; then
  GLADE_LOCALE_DIR=$ac_default_prefix/share/locale
else
  GLADE_LOCALE_DIR=$prefix/share/locale
fi
AC_DEFINE_UNQUOTED(GLADE_LOCALE_DIR, "$GLADE_LOCALE_DIR")


dnl ***************************************************************************
dnl GLADE_DATA_DIR - Sets the location of the data directory, where we install
dnl source files added to projects (such as all the Gnome m4 macros).
dnl This will substitute GLADE_DATA_DIR in config.h (from acconfig.h).
dnl ***************************************************************************

if test "x${datadir}" = 'x${prefix}/share'; then
  if test "x${prefix}" = "xNONE"; then
    AC_DEFINE_UNQUOTED(GLADE_DATA_DIR, "${ac_default_prefix}/share/${PACKAGE}")
  else
    AC_DEFINE_UNQUOTED(GLADE_DATA_DIR, "${prefix}/share/${PACKAGE}")
  fi
else
  AC_DEFINE_UNQUOTED(GLADE_DATA_DIR, "${datadir}/${PACKAGE}")
fi


dnl ***************************************************************************
dnl CFLAGS - Use -Wall if we have gcc, and use -ansi -pedantic if ansi enabled.
dnl ***************************************************************************

AC_ARG_ENABLE([ansi],
[  --enable-ansi           turn on strict ansi [default=no]],[],[enable_ansi=no])

changequote(,)dnl
if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[\ \	]-Wall[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -Wall" ;;
  esac

  if test "x$enable_ansi" = "xyes"; then
    case " $CFLAGS " in
    *[\ \	]-ansi[\ \	]*) ;;
    *) CFLAGS="$CFLAGS -ansi" ;;
    esac

    case " $CFLAGS " in
    *[\ \	]-pedantic[\ \	]*) ;;
    *) CFLAGS="$CFLAGS -pedantic" ;;
    esac
  fi
fi
changequote([,])dnl


dnl ***************************************************************************
dnl Gnome Support (use --disable-gnome to disable).
dnl (Use "#ifdef USE_GNOME" in Glade for Gnome-specific code.)
dnl ***************************************************************************

gnome_modules=

AC_ARG_ENABLE([gnome],
[  --disable-gnome         disable use of gnome],
	[gnome=$enableval], [gnome=yes])

if test "x$gnome" = "xyes"; then
  AC_PATH_PROG([gnome_config], [gnome-config])
  if test "x$gnome_config" = "x"; then
    gnome=no
  fi
fi

if test "$gnome" = yes; then
  AC_DEFINE([USE_GNOME])
  GLADE_GNOME_DIR="gnome"
  GLADE_GNOME_LIB="gnome/libgnomewidgets.a"
  AC_SUBST([GLADE_GNOME_DIR])
  AC_SUBST([GLADE_GNOME_LIB])
  gnome_modules="$gnome_modules gnomeui gnome gtk glib"
else
  CPPFLAGS="$CPPFLAGS $GTK_CFLAGS"
  LIBS="$LIBS $GTK_LIBS"
fi


dnl ***************************************************************************
dnl Check for ScrollKeeper
dnl ***************************************************************************
AC_PATH_PROG([SCROLLKEEPER_CONFIG], [scrollkeeper-config],[no])
if test x$SCROLLKEEPER_CONFIG = xno; then
  AC_MSG_ERROR([Couldn't find scrollkeeper-config, please install the scrollkeeper package])
fi
SCROLLKEEPER_REQUIRED=0.1.4
AC_SUBST([SCROLLKEEPER_REQUIRED])


dnl ***************************************************************************
dnl Check for Bonobo
dnl ***************************************************************************

try_bonobo=false
have_bonobo=false
bonobo_msg=no
using_oaf=no
AC_ARG_WITH([bonobo],
[  --with-bonobo           include Bonobo support (under development)],
	[if test x$withval = xyes; then
	  try_bonobo=true
	fi])

if $try_bonobo; then
  AC_MSG_CHECKING([for Bonobo >= 0.27])
  if $gnome_config --libs bonobox > /dev/null 2>&1; then

    vers=`gnome-config --modversion bonobox | sed -e "s/bonobo-//" | \
          awk 'BEGIN { FS = "."; } { printf "%d", $1 * 1000 + $2;}'`
    if test "$vers" -ge 27; then
      bonobo_ok=true
    else
      bonobo_ok=false
    fi
  else
    bonobo_ok=false
  fi

  if $bonobo_ok; then
    AC_MSG_RESULT([found])
    AC_DEFINE([ENABLE_BONOBO])
    gnome_modules="$gnome_modules bonobox"
    have_bonobo=true
    bonobo_msg=yes
  else
    AC_MSG_RESULT([not found])
  fi
fi

AM_CONDITIONAL([BONOBO], [$have_bonobo])

dnl ***************************************************************************
dnl Add all the cflags & libs needed for the Gnome modules.
dnl ***************************************************************************

if test "x$gnome_modules" != "x"; then
  GNOME_CFLAGS=`$gnome_config --cflags $gnome_modules 2>/dev/null`
  GNOME_LDFLAGS=`$gnome_config --libs $gnome_modules 2>/dev/null`
  CPPFLAGS="$CPPFLAGS $GNOME_CFLAGS"
  LIBS="$LIBS $GNOME_LDFLAGS"
fi


dnl ***************************************************************************
dnl Gnome-DB Support (use --enable-gnome-db to enable).
dnl ***************************************************************************

AC_ARG_ENABLE([gnome-db],
[  --enable-gnome-db      enable use of gnome-db],
	[gnome_db=$enableval], [gnome_db=yes])

if test "x$gnome" != "xyes"; then
  gnome_db=no
fi

if test "x$gnome_db" = "xyes"; then
  AC_PATH_PROG([gnomedb_config], [gnomedb-config])
  if test "x$gnomedb_config" = "x"; then
    gnome_db=no
  else
    gnomedbminvers="0.2.93"
    AC_MSG_CHECKING([for gnome-db >= $gnomedbminvers])
    gnomedbver=`gnomedb-config --version | awk 'BEGIN {FS="."}{printf "%d", $1*10000+$2*100+$3}'`
    if test "$gnomedbver" -ge 293
    then
      AC_MSG_RESULT([found])
      gnome_db=yes
    else
      AC_MSG_WARN([not found])
      gnome_db=no
    fi
  fi
fi

if test "x$gnome_db" = "xyes"; then
  AC_DEFINE([USE_GNOME_DB])
  GLADE_GNOME_DB_DIR="gnome-db"
  GLADE_GNOME_DB_LIB="gnome-db/libgnomedbwidgets.a"
  AC_SUBST([GLADE_GNOME_DB_DIR])
  AC_SUBST([GLADE_GNOME_DB_LIB])

  GNOMEDB_CFLAGS=`gnomedb-config --cflags 2>/dev/null`
  GNOMEDB_LIBS=`gnomedb-config --libs 2>/dev/null`
  CPPFLAGS="$GNOMEDB_CFLAGS $CPPFLAGS"
  LIBS="$GNOMEDB_LIBS $LIBS"
fi


dnl ***************************************************************************
dnl Palette type - temporary option to try the different palette layouts.
dnl ***************************************************************************

AC_ARG_WITH([palette],
[  --with-palette=TYPE     select the palette type: damon or martijn],
	[if test "x$withval" = "xmartijn"; then
		PALETTE_TYPE=2
	   AC_MSG_RESULT([Picking Martijn's palette layout])
	 else
	 	PALETTE_TYPE=1
	   AC_MSG_RESULT([Picking Damon's palette layout])
	 fi],
	[PALETTE_TYPE=1])
AC_DEFINE_UNQUOTED(PALETTE_TYPE, $PALETTE_TYPE)
	

dnl ***************************************************************************
dnl Debugging - defines GLADE_DEBUG if --enable-debug option is used.
dnl ***************************************************************************

AC_ARG_ENABLE([debug],
[  --enable-debug          turn on debugging [default=no]],
	[AC_DEFINE([GLADE_DEBUG])],[])


dnl ***************************************************************************
dnl Output the Makefiles etc.
dnl ***************************************************************************

AC_CONFIG_FILES([glade.spec
                 Makefile
                 glade/Makefile
                 glade/gbwidgets/Makefile
                 glade/gnome/Makefile
                 glade/gnome-db/Makefile
                 glade/data/Makefile
                 glade/data/gtk/Makefile
                 macros/Makefile
                 po/Makefile.in
                 doc/Makefile
                 doc/C/Makefile
                 doc/it/Makefile
                 omf-install/Makefile])
AC_CONFIG_SUBDIRS([examples/editor])
AC_OUTPUT

echo "

Configuration:

	Source code location:	${srcdir}
	Compiler:		${CC} 

	Gnome Support:		${gnome}
	Bonobo Support:		${bonobo_msg}
	Oaf Support:		${using_oaf}
	Gnome DB Support:	${gnome_db}
"
