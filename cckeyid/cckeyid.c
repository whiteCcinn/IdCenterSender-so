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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_cckeyid.h"

/* If you declare any globals in php_cckeyid.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(cckeyid)

/* True global resources - no need for thread safety here */
static int le_cckeyid;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("cckeyid.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_cckeyid_globals, cckeyid_globals)
    STD_PHP_INI_ENTRY("cckeyid.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_cckeyid_globals, cckeyid_globals)
PHP_INI_END()
*/
/* }}} */

/*
 * because of us use the php.ini the options info,so we must be invoke this api 
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("cckeyid.node_id","0", PHP_INI_ALL, OnUpdateInt, global_value, zend_cckeyid_globals, cckeyid_globals)
    STD_PHP_INI_ENTRY("cckeyid.epoch", "0", PHP_INI_ALL, OnUpdateLong, global_string, zend_cckeyid_globals, cckeyid_globals)
PHP_INI_END()



/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_cckeyid_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_cckeyid_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "cckeyid", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_cckeyid_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_cckeyid_init_globals(zend_cckeyid_globals *cckeyid_globals)
{
	cckeyid_globals->global_value = 0;
	cckeyid_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(cckeyid)
{
	/* If you have INI entries, uncomment these lines */
	REGISTER_INI_ENTRIES();
	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(cckeyid)
{
	/* uncomment this line if you have INI entries */
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cckeyid)
{
#if defined(COMPILE_DL_CCKEYID) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(cckeyid)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cckeyid)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Cckeyid support", "enabled");
        php_info_print_table_row(2, "Version", PHP_CCKEYID_VERSION);
        php_info_print_table_row(2, "Author", "wenhui.cai[email:471113744@qq.com]");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ cckeyid_functions[]
 *
 * Every user visible function must have an entry in cckeyid_functions[].
 */
const zend_function_entry cckeyid_functions[] = {
	PHP_FE(confirm_cckeyid_compiled,	NULL)		/* For testing, remove later. */
        PHP_FE(ck_get_id,NULL)
	PHP_FE_END	/* Must be the last line in cckeyid_functions[] */
};
/* }}} */

/* {{{ cckeyid_module_entry
 */
zend_module_entry cckeyid_module_entry = {
	STANDARD_MODULE_HEADER,
	"cckeyid",
	cckeyid_functions,
	PHP_MINIT(cckeyid),
	PHP_MSHUTDOWN(cckeyid),
	PHP_RINIT(cckeyid),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(cckeyid),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(cckeyid),
	PHP_CCKEYID_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CCKEYID
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(cckeyid)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
