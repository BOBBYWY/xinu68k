/* scanf.c - scanf, fscanf, sscanf, getch, ungetch, sgetch, sungetch */

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <tty.h>

#ifndef	CONSOLE
#define	CONSOLE	0
#endif
#define	EOF	(-1)
#define	EMPTY	(-2)

/*------------------------------------------------------------------------
 *  scanf  --  read from the console according to a format
 *------------------------------------------------------------------------
 */
int
scanf(char *fmt, int args)
{
	int getch();
	int ungetch();
	int buf;

	buf = EMPTY;
	return (_doscan(fmt, &args, getch, ungetch, CONSOLE, &buf));
}

/*------------------------------------------------------------------------
 *  fscanf  --  read from a device (file) according to a format
 *------------------------------------------------------------------------
 */
int
fscanf(int dev, char *fmt, int args)
{
	int getch();
	int ungetch();
	int buf;

	buf = EMPTY;
	return (_doscan(fmt, &args, getch, ungetch, dev, &buf));
}

/*------------------------------------------------------------------------
 *  getch  --  get a character from a device with pushback
 *------------------------------------------------------------------------
 */
static
getch(int dev, int *buf)
{
	if (*buf != EOF && *buf != EMPTY)
		*buf = getc(dev);
	if (*buf != EOF)
		*buf = control(dev, TCNEXTC);
	return (*buf);
}

/*------------------------------------------------------------------------
 *  ungetch  --  pushback a character for getch
 *------------------------------------------------------------------------
 */
static
ungetch(int dev, int *buf)
{
	*buf = EMPTY;
}

/*------------------------------------------------------------------------
 *  sscanf  --  read from a string according to a format
 *------------------------------------------------------------------------
 */
int
sscanf(char *str, char *fmt, int args)
{
	int sgetch();
	int sungetch();
	char *s;

	s = str;
	return (_doscan(fmt, &args, sgetch, sungetch, 0, &s));
}

/*------------------------------------------------------------------------
 *  sgetch  -- get the next character from a string
 *------------------------------------------------------------------------
 */
static
sgetch(int dummy, char **cpp)
{
	return (*(*cpp) == '\0' ? EOF : *(*cpp)++);
}

/*------------------------------------------------------------------------
 *  sungetc  --  pushback a character in a string
 *------------------------------------------------------------------------
 */
static
sungetch(int dummy, char **cpp)
{
	return (*(*cpp)--);
}
