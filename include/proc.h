/* proc.h - isbadpid */

/* process table declarations and defined constants			*/

#ifndef	NPROC				/* set the number of processes	*/
#define	NPROC		10		/*  allowed if not already done	*/
#endif

/* process state constants */

#define	PRCURR		'\001'		/* process is currently running	*/
#define	PRFREE		'\002'		/* process slot is free		*/
#define	PRREADY		'\003'		/* process is on ready queue	*/
#define	PRRECV		'\004'		/* process waiting for message	*/
#define	PRSLEEP		'\005'		/* process is sleeping		*/
#define	PRSUSP		'\006'		/* process is suspended		*/
#define	PRWAIT		'\007'		/* process is on semaphore queue*/
#define	PRTRECV		'\010'		/* process is timing a receive	*/

/* miscellaneous process definitions */

#define	PNREGS		16		/* size of saved register area	*/
#define	PNMLEN		16		/* length of process "name"	*/
#define	NULLPROC	0		/* id of the null process; it	*/
					/*  is always eligible to run	*/
#define	BADPID		-1		/* used when invalid pid needed	*/

#define	isbadpid(x)	(x<=0 || x>=NPROC)

/* process table entry */

struct	pentry	{
	char	pstate;			/* process state: PRCURR, etc.	*/
	short	pprio;			/* process priority		*/
	uword	pregs[PNREGS];		/* saved regs. R0-R5,SP,PC,PS	*/
	int	psem;			/* semaphore if process waiting	*/
	int	pmsg;			/* message sent to this process	*/
	Bool	phasmsg;		/* True iff pmsg is valid	*/
	char	*pbase;			/* base of run time stack	*/
	short	pstklen;		/* stack length			*/
	char	*plimit;		/* lowest extent of stack	*/
	char	pname[PNMLEN];		/* process name			*/
	int	pargs;			/* initial number of arguments	*/
	char	*paddr;			/* initial code address		*/
	int	pnxtkin;		/* next-of-kin notified of death*/
	short	pdevs[2];		/* devices to close upon exit	*/
};

extern	struct	pentry proctab[];
extern	int	numproc;		/* currently active processes	*/
extern	int	nextproc;		/* search point for free slot	*/
extern	int	currpid;		/* currently executing process	*/
