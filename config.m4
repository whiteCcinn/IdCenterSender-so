dnl $Id$
dnl config.m4 for extension cckeyid

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(cckeyid, for cckeyid support,
dnl Make sure that the comment is aligned:
[  --with-cckeyid             Include cckeyid support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(cckeyid, whether to enable cckeyid support,
dnl Make sure that the comment is aligned:
dnl [  --enable-cckeyid           Enable cckeyid support])

if test "$PHP_CCKEYID" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-cckeyid -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/cckeyid.h"  # you most likely want to change this
  dnl if test -r $PHP_CCKEYID/$SEARCH_FOR; then # path given as parameter
  dnl   CCKEYID_DIR=$PHP_CCKEYID
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for cckeyid files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CCKEYID_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CCKEYID_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the cckeyid distribution])
  dnl fi

  dnl # --with-cckeyid -> add include path
  dnl PHP_ADD_INCLUDE($CCKEYID_DIR/include)

  dnl # --with-cckeyid -> check for lib and symbol presence
  dnl LIBNAME=cckeyid # you may want to change this
  dnl LIBSYMBOL=cckeyid # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CCKEYID_DIR/$PHP_LIBDIR, CCKEYID_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CCKEYIDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong cckeyid lib version or lib not found])
  dnl ],[
  dnl   -L$CCKEYID_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CCKEYID_SHARED_LIBADD)

  cckeyid_source_file="cckeyid.c \
        src/cckeyid.c \
        src/shm.c \
        src/spinlock.c"

  PHP_NEW_EXTENSION(cckeyid, $cckeyid_source_file, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
