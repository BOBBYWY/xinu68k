#include "conf.h"
#include "kernel.h"
#include "proc.h"
#include "network.h"

/*------------------------------------------------------------------------
 *  ethwrite - write a single packet to the ethernet
 *------------------------------------------------------------------------
 */

int
ethwrite(struct devsw *devptr, char *buff, int len)
{
	struct etblk *etptr;
	char ps;

	if (len > EMAXPAK)
		return (SYSERR);
	if (len < EMINPAK)
		len = EMINPAK;
	etptr = (struct etblk *) devptr->dvioblk;
	memmove(((struct eheader *) buff)->e_src, etptr->etpaddr, EPADLEN);
	disable(ps);
	wait(etptr->etwsem);
	ethwstrt(etptr, buff, etptr->etlen = len, DC_NORM);
	restore(ps);
	return (OK);
}
