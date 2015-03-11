#include "bt.h"
insert (short rrn, char key, short *promo_r_child, char *promo_key)
{
BTPAGE page, // current page
newpage; // new page created if split occurs
int found, promoted; // boolean values
short pos,
p_b_rrn; // rrn promoted from below
char p_b_key; // key promoted from below
if (rrn == NIL)
{
*promo_key = key;
*promo_r_child = NIL;
return(YES);
}
btread(rrn, &page);
found = search_node ( key, &page, &pos);
if (found)
{
printf ("Error: attempt to insert duplicate key: %c \n\007", key);
return(0);
}
promoted = insert(page.child[pos], key, &p_b_rrn, &p_b_key);
if (!promoted)
{
return(NO);
}
if(page.keycount < MAXKEYS)
{
ins_in_page(p_b_key, p_b_rrn, &page);
btwrite(rrn, &page);
return(NO);
}
else
{
split(p_b_key, p_b_rrn, &page, promo_key, promo_r_child, &newpage);
btwrite(rrn, &page);
btwrite(*promo_r_child, &newpage);
return(YES);
}
}
