#ifndef _SUPPORT_H_
#define _SUPPORT_H_

int strcmpi(char *s1, char *s2);
#ifdef TARGET_PSX
int sprintf(char *string, char *fmt, ...);
#endif

#endif
