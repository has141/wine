/*****************************************************************************
 * Copyright 1998, Luiz Otavio L. Zorzella
 *
 * File:      multimedia.h
 * Purpose:   multimedia declarations
 *
 *****************************************************************************
 */
#ifndef __WINE_MULTIMEDIA_H 
#define __WINE_MULTIMEDIA_H

#include "mmsystem.h"

#define MAX_MIDIINDRV 	(16)
/* For now I'm making 16 the maximum number of midi devices one can
 * have. This should be more than enough for everybody. But as a purist,
 * I intend to make it unbounded in the future, as soon as I figure
 * a good way to do so.
 */
#define MAX_MIDIOUTDRV 	(16)
#define MAX_MCIMIDIDRV 	(1)

#ifdef HAVE_SYS_SOUNDCARD_H
# include <sys/soundcard.h>
#endif
#ifdef HAVE_MACHINE_SOUNDCARD_H
# include <machine/soundcard.h>
#endif

#include <sys/errno.h>

#ifdef HAVE_OSS
#define MIDI_SEQ "/dev/sequencer"
#else
#define MIDI_DEV "/dev/midi"
#endif

#ifdef SOUND_VERSION
#define IOCTL(a,b,c)		ioctl(a,b,&c)
#else
#define IOCTL(a,b,c)		(c = ioctl(a,b,c))
#endif

struct WINE_MCIDRIVER {
	HDRVR16						hDrv;
	DRIVERPROC16				driverProc;
	MCI_OPEN_DRIVER_PARMS	modp;
	MCI_OPEN_PARMS16			mop;
	DWORD							dwPrivate;
};

/* function prototypes */
extern BOOL32 MULTIMEDIA_Init(void);
extern DWORD  mciSendCommandAsync32(UINT32 wDevID, UINT32 wMsg, DWORD dwParam1, DWORD dwParam2);

#endif /* __WINE_MULTIMEDIA_H */
