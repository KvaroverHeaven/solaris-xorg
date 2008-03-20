/*
 * Copyright 2008 Sun Microsystems, Inc. All rights reserved.
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

#pragma ident   "@(#)FBPM.c	1.7	08/03/12 SMI"

#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/extensions/fbpm.h>
#include <X11/extensions/fbpmstr.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/extutil.h>
#include <stdio.h>

static XExtensionInfo _fbpm_info_data;
static XExtensionInfo *fbpm_info = &_fbpm_info_data;
static char *fbpm_extension_name = FBPMExtensionName;

#define FBPMCheckExtension(dpy,i,val) \
  XextCheckExtension (dpy, i, fbpm_extension_name, val)

/*****************************************************************************
 *                                                                           *
 *                         private utility routines                          *
 *                                                                           *
 *****************************************************************************/

static int close_display();
static /* const */ XExtensionHooks fbpm_extension_hooks = {
    NULL,                               /* create_gc */
    NULL,                               /* copy_gc */
    NULL,                               /* flush_gc */
    NULL,                               /* free_gc */
    NULL,                               /* create_font */
    NULL,                               /* free_font */
    close_display,                      /* close_display */
    NULL,                               /* wire_to_event */
    NULL,                               /* event_to_wire */
    NULL,                               /* error */
    NULL                                /* error_string */
};

static XEXT_GENERATE_FIND_DISPLAY (find_display, fbpm_info,
				   fbpm_extension_name,
                                   &fbpm_extension_hooks, FBPMNumberEvents,
                                   NULL)

static XEXT_GENERATE_CLOSE_DISPLAY (close_display, fbpm_info)
                                                              
/*****************************************************************************
 *                                                                           *
 *                  public routines                                          *
 *                                                                           *
 *****************************************************************************/

Bool FBPMQueryExtension (dpy, event_basep, error_basep)
    Display *dpy;
    int *event_basep, *error_basep;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);

    if (XextHasExtension(info)) {
	*event_basep = info->codes->first_event;
	*error_basep = info->codes->first_error;
	return True;
    } else {
	return False;
    }
#else
	return False;
#endif
}

Status FBPMGetVersion(dpy, major_versionp, minor_versionp)
    Display *dpy;
    int	    *major_versionp, *minor_versionp;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);
    xFBPMGetVersionReply	    rep;
    register xFBPMGetVersionReq  *req;

    FBPMCheckExtension (dpy, info, 0);

    LockDisplay (dpy);
    GetReq (FBPMGetVersion, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMGetVersion;
    if (!_XReply (dpy, (xReply *) &rep, 0, xTrue)) {
	UnlockDisplay (dpy);
	SyncHandle ();
	return 0;
    }
    *major_versionp = rep.majorVersion;
    *minor_versionp = rep.minorVersion;
    UnlockDisplay (dpy);
    SyncHandle ();
    return 1;
#else
	return 0;
#endif
}

Bool FBPMCapable(dpy)
    Display *dpy;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMCapableReq *req;
    xFBPMCapableReply rep;

    FBPMCheckExtension (dpy, info, 0);

    LockDisplay(dpy);
    GetReq(FBPMCapable, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMCapable;

    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.capable;
#else
	return False;
#endif
}


Bool FBPMEnable(dpy,state)
    Display *dpy;
	int state;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMEnableReq *req;

    FBPMCheckExtension (dpy, info, 0);
    LockDisplay(dpy);
    GetReq(FBPMEnable, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMEnable;
	req->level = state;

    UnlockDisplay(dpy);
    SyncHandle();
    return True;
#else
	return False;
#endif
}

Status FBPMDisable(dpy)
    Display *dpy;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMDisableReq *req;

    FBPMCheckExtension (dpy, info, 0);
    LockDisplay(dpy);
    GetReq(FBPMDisable, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMDisable;

    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
#else
	return 0;
#endif
}
Status FBPMForceLevel(dpy, level)
    Display *dpy;
    CARD16 level;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMForceLevelReq *req;

    FBPMCheckExtension (dpy, info, 0);

    if ((level != FBPMModeOn) &&
        (level != FBPMModeStandby) &&
        (level != FBPMModeSuspend) &&
        (level != FBPMModeOff))
        return BadValue;

    LockDisplay(dpy);
    GetReq(FBPMForceLevel, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMForceLevel;
    req->level = level;

    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
#else
	return 0;
#endif
}

Status FBPMInfo(dpy, state, onoff)
    Display *dpy;
    CARD16 *state;
	BOOL *onoff;
{
#ifndef FBPM_STUB
    XExtDisplayInfo *info = find_display (dpy);
    register xFBPMInfoReq *req;
    xFBPMInfoReply rep;

    FBPMCheckExtension (dpy, info, 0);

    LockDisplay(dpy);
    GetReq(FBPMInfo, req);
    req->reqType = info->codes->major_opcode;
    req->fbpmReqType = X_FBPMInfo;

    if (!_XReply(dpy, (xReply *)&rep, 0, xTrue)) {
        UnlockDisplay(dpy);
        SyncHandle();
        return 0;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    *state = rep.power_level;
    *onoff = rep.state;
    return 1;
#else
	return 0;
#endif
}
