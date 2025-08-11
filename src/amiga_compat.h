/*
 * Amiga compatibility header for texinfo216
 * Provides missing system functions and variables
 */

#ifndef AMIGA_COMPAT_H
#define AMIGA_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/* System error variables that some systems expect */
extern int sys_nerr;
extern char *sys_errlist[];

/* Alloca function - always use our implementation on Amiga */
/* This provides a proper stack-based alloca implementation */
void *alloca(unsigned size);

/* User/group library base - needed for getpwnam etc. */
extern struct Library *UserGroupBase;

#ifdef __cplusplus
}
#endif

#endif /* AMIGA_COMPAT_H */
