dnl $Id$
dnl config.m4 for extension divoom_minilzo

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(divoom_minilzo, for divoom_minilzo support,
dnl Make sure that the comment is aligned:
dnl [  --with-divoom_minilzo             Include divoom_minilzo support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(divoom_minilzo, whether to enable divoom_minilzo support,
dnl Make sure that the comment is aligned:
[  --enable-divoom_minilzo           Enable divoom_minilzo support])

if test "$PHP_DIVOOM_MINILZO" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-divoom_minilzo -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/divoom_minilzo.h"  # you most likely want to change this
  dnl if test -r $PHP_DIVOOM_MINILZO/$SEARCH_FOR; then # path given as parameter
  dnl   DIVOOM_MINILZO_DIR=$PHP_DIVOOM_MINILZO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for divoom_minilzo files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DIVOOM_MINILZO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DIVOOM_MINILZO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the divoom_minilzo distribution])
  dnl fi

  dnl # --with-divoom_minilzo -> add include path
  dnl PHP_ADD_INCLUDE($DIVOOM_MINILZO_DIR/include)

  dnl # --with-divoom_minilzo -> check for lib and symbol presence
  dnl LIBNAME=divoom_minilzo # you may want to change this
  dnl LIBSYMBOL=divoom_minilzo # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DIVOOM_MINILZO_DIR/lib, DIVOOM_MINILZO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DIVOOM_MINILZOLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong divoom_minilzo lib version or lib not found])
  dnl ],[
  dnl   -L$DIVOOM_MINILZO_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DIVOOM_MINILZO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(divoom_minilzo, divoom_minilzo.c minilzo.c divoom_base64.c, $ext_shared)
fi
