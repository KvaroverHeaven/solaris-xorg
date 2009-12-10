/* Copyright 2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
 * OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder
 * shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization
 * of the copyright holder.
 */

#pragma ident	"@(#)pix_update.c	35.6	09/11/09 SMI"

/*
** pix_update.c
**
** Routines of the update phase for pixmaps.
*/

#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif /* SERVER_DGA */
#include "dga_incls.h"
#include "pix_grab.h"

void
dgai_pix_notify(_Dga_pixmap dgapix)
{
    if (dgapix->siteNotifyFunc && (dgapix->changeMask & DGA_CHANGE_SITE)) {
	(*dgapix->siteNotifyFunc)((Dga_drawable)dgapix, -1,
				  dgapix->siteNotifyClientData,
				  dgapix->siteChgReason);
        dgapix->changeMask &= ~DGA_CHANGE_SITE;
    }
}

int
dgai_pix_update(Dga_drawable dgadraw, short bufIndex)
{
    _Dga_pixmap dgapix = (_Dga_pixmap)dgadraw;
    SHARED_PIXMAP_INFO *infop;

#ifdef MT
    if (dgaMTOn) {
	mutex_lock(dgapix->mutexp);
	DGA_LOCK(dgadraw);
	/* check the real change count that we saved away */
	if (dgapix->shadow_chngcnt[0] == *dgapix->s_chngcnt_p) {
	    mutex_unlock(dgapix->mutexp);
            DGA_UNLOCK(dgadraw);
	    return (0);
	}
    }
#endif

    infop = PIX_INFOP(dgapix);

    dgapix->changeMask = 0;

    /* first, see if the shared info is still valid */
    if (infop->obsolete) {
        dgapix->changeMask |= DGA_CHANGE_ZOMBIE;
    }
    if (dgapix->changeMask & DGA_CHANGE_ZOMBIE) {
        dgapix->changeMask |= (DGA_CHANGE_SITE | DGA_CHANGE_CLIP);
        dgapix->siteChgReason = DGA_SITECHG_ZOMBIE;
    }

    /* see if the dev_info has changed */
    if (dgapix->c_devinfocnt != *dgapix->s_devinfocnt_p) {
	dgapix->changeMask |= DGA_CHANGE_DEVINFO;
        dgapix->c_devinfocnt = *dgapix->s_devinfocnt_p;
    }

    /* Has the cache changed? */
    if (dgapix->c_cachecnt != *dgapix->s_cachecnt_p) {
        dgapix->changeMask |= (DGA_CHANGE_CACHE | DGA_CHANGE_SITE);
	dgapix->siteChgReason = DGA_SITECHG_CACHE;
        dgapix->c_cached = *dgapix->s_cached_p;
        dgapix->c_cachecnt = *dgapix->s_cachecnt_p;
    }

    dgai_pix_notify(dgapix);

#ifdef MT
    if (dgaMTOn) {
	/* save the real change count */
	dgapix->shadow_chngcnt[0] = *dgapix->s_chngcnt_p;
	/* For the MT case, make sure that this update function gets called
	 * the next time around, so make the change count different.
	 */
	dgapix->c_chngcnt[0] = *dgapix->s_chngcnt_p - 1;
	mutex_unlock(dgapix->mutexp);
        DGA_UNLOCK(dgadraw);
    } else {
	dgapix->c_chngcnt[0] = *dgapix->s_chngcnt_p;
    }
#else
    dgapix->c_chngcnt[0] = *dgapix->s_chngcnt_p;
#endif
    return(dgapix->changeMask);

}