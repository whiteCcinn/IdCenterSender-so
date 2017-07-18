/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:caiwenhui 471113744@qq.com                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_CCKEYID_H
#define PHP_CCKEYID_H

extern zend_module_entry cckeyid_module_entry;
#define phpext_cckeyid_ptr &cckeyid_module_entry

#define PHP_CCKEYID_VERSION "1.0.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_CCKEYID_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_CCKEYID_API __attribute__ ((visibility("default")))
#else
#	define PHP_CCKEYID_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

// [kernal] this is zend module api
//PHP_MINIT_FUNCTION(cckeyid); // Declare the function to load when the module is loaded
//PHP_MSHUTDOWN_FUNCTOIN(cckeyid);
//PHP_RINIT_FUNCTION(cckeyid);
//PHP_RSHUTDOWN_FUNCTION(cckeyid);
//PHP_MINFO_FUNCTION(cckeyid);


// [user] this is my define function
PHP_FUNCTION(ck_get_id);


/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:
*/
ZEND_BEGIN_MODULE_GLOBALS(cckeyid)
	int  ck_node_id; // the node id
	long ck_epoch;  // the begin service time
ZEND_END_MODULE_GLOBALS(cckeyid)


/* Always refer to the globals in your function as CCKEYID_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define CCKEYID_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(cckeyid, v)

#if defined(ZTS) && defined(COMPILE_DL_CCKEYID)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_CCKEYID_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
