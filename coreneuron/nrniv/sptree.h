/*
Copyright (c) 2014 EPFL-BBP, All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE BLUE BRAIN PROJECT "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE BLUE BRAIN PROJECT
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
** sptree.h:  The following type declarations provide the binary tree
**  representation of event-sets or priority queues needed by splay trees
**
**  assumes that data and datb will be provided by the application
**  to hold all application specific information
**
**  assumes that key will be provided by the application, comparable
**  with the compare function applied to the addresses of two keys.
*/

# ifndef SPTREE_H
# define SPTREE_H

# ifndef NULL
# define NULL	0
# endif

#define STRCMP_DEF 0
#if STRCMP_DEF
# define STRCMP( a, b ) ( (Sct = *(a) - *(b)) ? Sct : strcmp( (a), (b) ) )
#else
#define STRCMP(a, b) (a - b)
#endif

typedef struct SPTREE
{
    SPBLK	* root;		/* root node */

    /* Statistics, not strictly necessary, but handy for tuning  */

    int		lookups;	/* number of splookup()s */
    int		lkpcmps;	/* number of lookup comparisons */
    
    int		enqs;		/* number of spenq()s */
    int		enqcmps;	/* compares in spenq */
    
    int		splays;
    int		splayloops;

} SPTREE;

#define spinit sptq_spinit
#define spempty sptq_spempty
#define spenq sptq_spenq
#define spdeq sptq_spdeq
#define spenqprior sptq_spenqprior
#define splay sptq_splay
#define sphead sptq_sphead
#define spdelete sptq_spdelete
#define spnext sptq_spnext
#define spprev sptq_spprev
#define spenqbefore sptq_spenqbefore
#define spenqafter sptq_spenqafter
#define splookup sptq_splookup
/*#define spinstall sptq_spinstall*/
#define sptail sptq_sptail
#define spscan sptq_spscan
#define sprscan sptq_sprscan
#define spfhead sptq_spfhead
#define spfnext sptq_spfnext
#define spfprev sptq_spfprev
#define spstats sptq_spstats

/* sptree.c */
extern void spinit(SPTREE*);		/* init tree */
extern int spempty(SPTREE*);		/* is tree empty? */
extern SPBLK * spenq(SPBLK*, SPTREE*);	/* insert item into the tree */
extern SPBLK * spdeq(SPBLK**);		/* return and remove lowest item in subtree */
extern SPBLK * spenqprior(SPBLK*, SPTREE*);/* insert before items with same key */
extern void splay(SPBLK*, SPTREE*);	/* reorganize tree */

/* spaux.c */
extern SPBLK * sphead(SPTREE*);		/* return first node in tree */
extern void spdelete(SPBLK*, SPTREE*);	/* delete node from tree */
extern SPBLK * spnext(SPBLK*, SPTREE*);	/* return next node in tree */
extern SPBLK * spprev(SPBLK*, SPTREE*);	/* return previous node in tree */
extern SPBLK * spenqbefore(SPBLK*, SPBLK*, SPTREE*);	/* enqueue before existing node */
extern SPBLK * spenqafter(SPBLK*, SPBLK*, SPTREE*);	/* enqueue after existing node */

/* spdaveb.c */
extern SPBLK * splookup(double, SPTREE*);	/* find key in a tree */
/*extern SPBLK * spinstall(double, void*, SPTREE*);*/	/* enter an item, allocating or replacing */
extern SPBLK * sptail(SPTREE*);	/* find end of a tree */
extern void spscan(void(*)(const TQItem*, int), SPBLK*, SPTREE*);		/* scan forward through tree */
extern void sprscan(void(*)(const TQItem*, int), SPBLK*, SPTREE*);		/* reverse scan through tree */
extern SPBLK * spfhead(SPTREE*);	/* fast non-splaying head */
extern SPBLK * spfnext(SPBLK*);	/* fast non-splaying next */
extern SPBLK * spfprev(SPBLK*);	/* fast non-splaying prev */
extern const char* spstats(SPTREE*);

# endif
