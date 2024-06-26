
dnl  Copyright 2005 Red Hat, Inc.
dnl
dnl  Permission to use, copy, modify, distribute, and sell this software and its
dnl  documentation for any purpose is hereby granted without fee, provided that
dnl  the above copyright notice appear in all copies and that both that
dnl  copyright notice and this permission notice appear in supporting
dnl  documentation, and that the name of Red Hat not be used in
dnl  advertising or publicity pertaining to distribution of the software without
dnl  specific, written prior permission.  Red Hat makes no
dnl  representations about the suitability of this software for any purpose.  It
dnl  is provided "as is" without express or implied warranty.
dnl
dnl  RED HAT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
dnl  INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
dnl  EVENT SHALL RED HAT BE LIABLE FOR ANY SPECIAL, INDIRECT OR
dnl  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
dnl  DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
dnl  TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
dnl  PERFORMANCE OF THIS SOFTWARE.
dnl
dnl Process this file with autoconf to create configure.

# Initialize Autoconf
AC_PREREQ([2.60])
AC_INIT([xdpyinfo], [1.3.4],
	[https://gitlab.freedesktop.org/xorg/app/xdpyinfo/-/issues], [xdpyinfo])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])

# Initialize Automake
AM_INIT_AUTOMAKE([foreign dist-xz])

# Require X.Org macros 1.8 or later for MAN_SUBSTS set by XORG_MANPAGE_SECTIONS
m4_ifndef([XORG_MACROS_VERSION],
          [m4_fatal([must install xorg-macros 1.8 or later before running autoconf/autogen])])
XORG_MACROS_VERSION(1.8)
XORG_DEFAULT_OPTIONS

# Checks for pkg-config packages
PKG_CHECK_MODULES(XDPYINFO, [xext x11 xtst x11-xcb xcb xproto >= 7.0.22])

# This is used below to allow <X11/Xlib.h> to be found
PKG_CHECK_MODULES(DPY_X11, x11)

PKG_CHECK_MODULES(DPY_XEXT, xext,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XEXT_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/multibuf.h X11/extensions/XShm.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

PKG_CHECK_MODULES(DPY_XKB, x11,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XKB_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/XKB.h X11/XKBlib.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

PKG_CHECK_MODULES(DPY_XF86VIDMODE, xxf86vm,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XF86VIDMODE_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/xf86vmode.h X11/extensions/xf86vmstr.h X11/extensions/xf86vmproto.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

AC_ARG_WITH(dga, AS_HELP_STRING([--without-dga],[Disable dga support.]),
		[USE_DGA="$withval"], [USE_DGA="yes"])
if test "x$USE_DGA" != "xno" ; then
	PKG_CHECK_MODULES(DPY_XF86DGA, xxf86dga,
		[SAVE_CPPFLAGS="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $DPY_XF86DGA_CFLAGS $DPY_X11_CFLAGS"
		AC_CHECK_HEADERS([X11/extensions/Xxf86dga.h X11/extensions/xf86dgaproto.h X11/extensions/xf86dga.h X11/extensions/xf86dgastr.h],,,
				 [#include <X11/Xlib.h>
#include <X11/Xproto.h>])
		CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])
else
	echo "without dga"
fi


AC_ARG_WITH(xf86misc, AS_HELP_STRING([--with-xf86misc],[Enable xf86misc support.]),
		[USE_XF86MISC="$withval"], [USE_XF86MISC="no"])
if test "x$USE_XF86MISC" != "xno" ; then
	PKG_CHECK_MODULES(DPY_XF86MISC, xxf86misc,
		[SAVE_CPPFLAGS="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $DPY_XF86MISC_CFLAGS $DPY_X11_CFLAGS"
		AC_CHECK_HEADERS([X11/extensions/xf86misc.h X11/extensions/xf86mscstr.h],,,
				  [#include <X11/Xlib.h>
#include <X11/Xproto.h>])
		CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])
else
	echo "without xf86misc"
fi

PKG_CHECK_MODULES(DPY_XINPUT, xi,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XINPUT_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/XInput.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

PKG_CHECK_MODULES(DPY_XRENDER, xrender,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XRENDER_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/Xrender.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

PKG_CHECK_MODULES(DPY_XCOMPOSITE, xcomposite,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XCOMPOSITE_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/Xcomposite.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

AC_ARG_WITH(xinerama, AS_HELP_STRING([--without-xinerama],[Disable xinerama support.]),
		[USE_XINERAMA="$withval"], [USE_XINERAMA="yes"])
if test "x$USE_XINERAMA" != "xno" ; then
	PKG_CHECK_MODULES(DPY_XINERAMA, xinerama,
		[SAVE_CPPFLAGS="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $DPY_XINERAMA_CFLAGS $DPY_X11_CFLAGS"
		AC_CHECK_HEADERS([X11/extensions/Xinerama.h],,,[#include <X11/Xlib.h>])
		CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])
else
	echo "without xinerama"
fi

AC_ARG_WITH(dmx, AS_HELP_STRING([--with-dmx],[Enable dmx support.]),
		[USE_DMX="$withval"], [USE_DMX="no"])
if test "x$USE_DMX" != "xno" ; then
	PKG_CHECK_MODULES(DPY_DMX, dmx,
		[SAVE_CPPFLAGS="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $DPY_DMX_CFLAGS $DPY_X11_CFLAGS"
		AC_CHECK_HEADERS([X11/extensions/dmxext.h],,,[#include <X11/Xlib.h>])
		CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])
else
	echo "without dmx"
fi

PKG_CHECK_MODULES(DPY_XTST, xtst,
	[SAVE_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $DPY_XTST_CFLAGS $DPY_X11_CFLAGS"
	AC_CHECK_HEADERS([X11/extensions/record.h],,,[#include <X11/Xlib.h>])
	CPPFLAGS="$SAVE_CPPFLAGS"],[echo "not found"])

dnl Allow checking code with lint, sparse, etc.
XORG_WITH_LINT

AC_CONFIG_FILES([
	Makefile
	man/Makefile])
AC_OUTPUT
