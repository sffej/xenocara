#
#  Copyright © 2003 Keith Packard, Noah Levitt
#
#  Permission to use, copy, modify, distribute, and sell this software and its
#  documentation for any purpose is hereby granted without fee, provided that
#  the above copyright notice appear in all copies and that both that
#  copyright notice and this permission notice appear in supporting
#  documentation, and that the name of Keith Packard not be used in
#  advertising or publicity pertaining to distribution of the software without
#  specific, written prior permission.  Keith Packard makes no
#  representations about the suitability of this software for any purpose.  It
#  is provided "as is" without express or implied warranty.
#
#  KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
#  INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
#  EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
#  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
#  DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
#  TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
#  PERFORMANCE OF THIS SOFTWARE.
#

# Initialize Autoconf
AC_PREREQ([2.60])
#
# Version should match the current XComposite version. XCompositeQueryVersion
# returns the version from xcompositewire.h, NOT the version we set here.
# But we try to keep these the same.  Note that the library has an extra
# digit in the version number to track changes which don't affect the
# protocol, so Xcomposite version l.n.m corresponds to protocol version l.n
# that 'revision' number appears in Xcomposite.h and has to be manually
# synchronized.
#
AC_INIT(libXcomposite, [0.4.6],
	[https://gitlab.freedesktop.org/xorg/lib/libxcomposite/-/issues],
	[libXcomposite])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])

# Initialize Automake
AM_INIT_AUTOMAKE([foreign dist-xz])

# Initialize libtool
AC_PROG_LIBTOOL

# Require X.Org macros 1.8 or later for MAN_SUBSTS set by XORG_MANPAGE_SECTIONS
m4_ifndef([XORG_MACROS_VERSION],
	  [m4_fatal([must install xorg-macros 1.8 or later before running autoconf/autogen])])
XORG_MACROS_VERSION(1.8)
XORG_DEFAULT_OPTIONS
XORG_WITH_XMLTO(0.0.20)

# Determine if the source for man pages is available
# It may already be present (tarball) or can be generated using xmlto
AM_CONDITIONAL([INSTALL_MANPAGES],
	[test -f "$srcdir/man/Xcomposite.man" || test "x$have_xmlto" = xyes])

# Check compositeext configuration, strip extra digits from package version to
# find the required protocol version
if test "$VERSION" = "" ; then
       VERSION=$PACKAGE_VERSION;
fi
COMPOSITEEXT_VERSION=[`echo $VERSION | sed 's/^\([0-9][0-9]*\.[0-9][0-9]*\).*$/\1/'`]
AC_SUBST(COMPOSITEEXT_VERSION)

# Obtain compiler/linker options for dependencies
PKG_CHECK_MODULES(XCOMPOSITE,
        [compositeproto >= $COMPOSITEEXT_VERSION xproto >= 7.0.22 x11])
PKG_CHECK_MODULES(XFIXES, xfixes)

AC_CONFIG_FILES([Makefile
		src/Makefile
		man/Makefile
		xcomposite.pc])
AC_OUTPUT
