#ifndef _divoom_base64_h_
#define _divoom_base64_h_
char * divoom_base64_encode( const unsigned char * bindata, char * base64, int binlength );
int divoom_base64_decode( const char * base64, unsigned char * bindata );

#endif



