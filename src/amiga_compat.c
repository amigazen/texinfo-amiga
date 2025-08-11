/*
 * Amiga compatibility implementation for texinfo216
 * Provides missing system functions and variables
 */

#include "amiga_compat.h"
#include <exec/libraries.h>
#include <proto/exec.h>
#include <stdlib.h>

/* System error variables - provide empty implementations */
int sys_nerr = 0;
char *sys_errlist[] = { NULL };

/* User/group library base - will be opened by PosixLib */
struct Library *UserGroupBase = NULL;

/* Alloca function - proper stack-based implementation */
/* Override any system alloca to use our implementation */
#undef alloca

#include <stdlib.h>
#include <stddef.h>

typedef void *pointer;		/* generic pointer type */

/*
	Define STACK_DIRECTION if you know the direction of stack
	growth for your system; otherwise it will be automatically
	deduced at run-time.

	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown
*/

#ifndef STACK_DIRECTION
#define	STACK_DIRECTION	0		/* direction unknown */
#endif

#if (STACK_DIRECTION) != 0

#define	STACK_DIR	STACK_DIRECTION	/* known at compile-time */

#else	/* STACK_DIRECTION == 0; need run-time code */

static int	stack_dir;		/* 1 or -1 once known */
#define	STACK_DIR	stack_dir

static void
find_stack_direction(void)
{
  static char	*addr = NULL;	/* address of first
				   `dummy', once known */
  auto char	dummy;		/* to get stack address */

  if (addr == NULL)
    {				/* initial entry */
      addr = &dummy;

      find_stack_direction ();	/* recurse once */
    }
  else				/* second entry */
    if (&dummy > addr)
      stack_dir = 1;		/* stack grew upward */
    else
      stack_dir = -1;		/* stack grew downward */
}

#endif	/* STACK_DIRECTION == 0 */

/*
	An "alloca header" is used to:
	(a) chain together all alloca()ed blocks;
	(b) keep track of stack depth.

	It is very important that sizeof(header) agree with malloc()
	alignment chunk size.  The following default should work okay.
*/

#ifndef	ALIGN_SIZE
#define	ALIGN_SIZE	sizeof(double)
#endif

typedef union hdr
{
  char	align[ALIGN_SIZE];	/* to force sizeof(header) */
  struct
    {
      union hdr *next;		/* for chaining headers */
      char *deep;		/* for stack depth measure */
    } h;
} header;

/*
	alloca( size ) returns a pointer to at least `size' bytes of
	storage which will be automatically reclaimed upon exit from
	the procedure that called alloca().  Originally, this space
	was supposed to be taken from the current stack frame of the
	caller, but that method cannot be made to work for some
	implementations of C, for example under Gould's UTX/32.
*/

static header *last_alloca_header = NULL; /* -> last alloca header */

pointer
alloca(unsigned size)		/* returns pointer to storage */
{
  auto char	probe;		/* probes stack depth: */
  register char	*depth = &probe;

#if STACK_DIRECTION == 0
  if (STACK_DIR == 0)		/* unknown growth direction */
    find_stack_direction ();
#endif

				/* Reclaim garbage, defined as all alloca()ed storage that
				   was allocated from deeper in the stack than currently. */

  {
    register header	*hp;	/* traverses linked list */

    for (hp = last_alloca_header; hp != NULL;)
      if (STACK_DIR > 0 && hp->h.deep > depth
	  || STACK_DIR < 0 && hp->h.deep < depth)
	{
	  register header	*np = hp->h.next;

	  free ((pointer) hp);	/* collect garbage */

	  hp = np;		/* -> next header */
	}
      else
	break;			/* rest are not deeper */

    last_alloca_header = hp;	/* -> last valid storage */
  }

  if (size == 0)
    return NULL;		/* no allocation required */

  /* Allocate combined header + user data storage. */

  {
    register pointer	new = malloc (sizeof (header) + size);
    /* address of header */

    ((header *)new)->h.next = last_alloca_header;
    ((header *)new)->h.deep = depth;

    last_alloca_header = (header *)new;

    /* User storage begins just after header. */

    return (pointer)((char *)new + sizeof(header));
  }
}
