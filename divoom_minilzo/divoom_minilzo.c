/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_divoom_minilzo.h"
#include "minilzo.h"
#include "divoom_base64.h"

/* If you declare any globals in php_divoom_minilzo.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(divoom_minilzo)
*/

/* True global resources - no need for thread safety here */
static int le_divoom_minilzo;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("divoom_minilzo.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_divoom_minilzo_globals, divoom_minilzo_globals)
    STD_PHP_INI_ENTRY("divoom_minilzo.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_divoom_minilzo_globals, divoom_minilzo_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_divoom_minilzo_compiled(string arg)
   Return a string to confirm that the module is compiled in */
   

PHP_FUNCTION(divoom_minilzo_decompress_mul)
{
		long pic_num;
        int i,r,  in_off, out_off;
        lzo_uint in_len, out_len;
        unsigned char *in_buf, *out_buf,*base64_buf;
        char *ret_str;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &in_buf, &in_len, &pic_num) == FAILURE) {
                RETURN_NULL();
        }

        out_buf = (unsigned char *)safe_emalloc(16*1024 , 1, 1);
        if(out_buf == NULL)
        {
                RETURN_NULL();
        }
        if (lzo_init() != LZO_E_OK)
        {
                efree(out_buf);
                RETURN_NULL();
        }
        for(i = 0, in_off = 0, out_off = 0; i < pic_num; i ++)
        {
            in_len = ((int)in_buf[in_off] << 24) + ((int)in_buf[in_off + 1] << 16) + ((int)in_buf[in_off + 2] << 8) + (int)in_buf[in_off + 3];
            in_off += 4;
            r = lzo1x_decompress(in_buf + in_off, in_len,out_buf + out_off,&out_len,NULL);
            if (r == LZO_E_OK) {
                in_off += in_len;
                out_off += out_len;
				break;
            }
             else {

                    efree(out_buf);
                    RETURN_NULL();
            }
        }
    	base64_buf = (unsigned char *)safe_emalloc(out_off*2, 1, 1);
        if(base64_buf == NULL)
        {
                    efree(out_buf);
                    RETURN_NULL();
        }
    	divoom_base64_encode(out_buf, base64_buf, out_off);
        efree(out_buf);
        i = spprintf(&ret_str, "%s",base64_buf);
	    efree(base64_buf);
        RETURN_STRINGL(ret_str, i, 0);
}

PHP_FUNCTION(divoom_minilzo_decompress)
{
        int i,r;
        lzo_uint in_len, out_len;
        unsigned char *in_buf, *out_buf,*base64_buf;
        char *ret_str;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &in_buf, &in_len) == FAILURE) {
                RETURN_NULL();
        }

       // php_printf("we will start mini lzo!: %d\n", in_len);
        out_buf = (unsigned char *)safe_emalloc(750*1024, 1, 1);
        if(out_buf == NULL)
        {
               // php_printf("ths is malloc err!\n");
                RETURN_NULL();
        }
        if (lzo_init() != LZO_E_OK)
        {
               // php_printf("minilzo fails to init and exit!\n");
                efree(out_buf);
                RETURN_NULL();
        }
        r = lzo1x_decompress(in_buf, in_len,out_buf,&out_len,NULL);
        if (r == LZO_E_OK) {
        }
         else {

                efree(out_buf);
                //php_printf("minilzo out err: %d!\n", r);
                RETURN_NULL();
        }
    	base64_buf = (unsigned char *)safe_emalloc(out_len*2, 1, 1);
    	divoom_base64_encode(out_buf, base64_buf, out_len);
        i = spprintf(&ret_str, "%s",base64_buf);
        efree(out_buf);
	efree(base64_buf);
        RETURN_STRINGL(ret_str, i, 0);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_divoom_minilzo_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_divoom_minilzo_init_globals(zend_divoom_minilzo_globals *divoom_minilzo_globals)
{
	divoom_minilzo_globals->global_value = 0;
	divoom_minilzo_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(divoom_minilzo)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(divoom_minilzo)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(divoom_minilzo)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(divoom_minilzo)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(divoom_minilzo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "divoom_minilzo support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ divoom_minilzo_functions[]
 *
 * Every user visible function must have an entry in divoom_minilzo_functions[].
 */
const zend_function_entry divoom_minilzo_functions[] = {
	PHP_FE(divoom_minilzo_decompress,	NULL)		/* For testing, remove later. */
	PHP_FE(divoom_minilzo_decompress_mul,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in divoom_minilzo_functions[] */
};
/* }}} */

/* {{{ divoom_minilzo_module_entry
 */
zend_module_entry divoom_minilzo_module_entry = {
	STANDARD_MODULE_HEADER,
	"divoom_minilzo",
	divoom_minilzo_functions,
	PHP_MINIT(divoom_minilzo),
	PHP_MSHUTDOWN(divoom_minilzo),
	PHP_RINIT(divoom_minilzo),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(divoom_minilzo),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(divoom_minilzo),
	PHP_DIVOOM_MINILZO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DIVOOM_MINILZO
ZEND_GET_MODULE(divoom_minilzo)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
