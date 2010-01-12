//
// Creation:    BFWhatSystem.h
// Created:     June 6, 2001
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2001 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// If the user didn't tell us which OS we're compiling for or 
// whether the compiler is building for user or kernel level 
// then try to figure it out.
//
// History:
//
// 06/06/01     rbs     Created file.
// 06/03/03		rbs		Added DefaultToUserNT stuff.
//

#if !defined(__BFWHATSYSTEM__)
#define __BFWHATSYSTEM__

// If DefaultToUserNT is defined, the system type and level
// will be set to UserNT if it isn't set by the caller or it
// can't be determined through testing.
//
// If DefaultToUserNT is undefined, errors will be output
// if the system type and level aren't defined and can't be
// determined through tests. 

#define DefaultToUserNT

// Make sure all local flags are undefined.

#undef HaveTheOS
#undef MustGenOS

#undef HaveLX
#undef HaveNT
#undef HavePT

#undef HaveTheLevel
#undef MustGenLevel

#undef HaveKernel
#undef HaveUser

// Check for an OS definition.

// Doing Linux?

#if defined(UserLX) || defined(KernelLX)
	#if defined(HaveTheOS)
		#error More than one OS defined!
	#else
		#define HaveLX
		#define HaveTheOS
	#endif
#endif

// Doing NT?

#if defined(UserNT) || defined(KernelNT)
	#if defined(HaveTheOS)
		#error More than one OS defined!
	#else
		#define HaveNT
		#define HaveTheOS
	#endif
#endif

// Doing port test?

#if defined(UserPT) || defined(KernelPT)
	#if defined(HaveTheOS)
		#error More than one OS defined!
	#else
		#define HavePT
		#define HaveTheOS
	#endif
#endif

// Check for a build level definition.

// Building for the kernel level?

#if defined(KernelOS)
	#if defined(HaveTheLevel)
		#error More than one build level defined!
	#else
		#define HaveKernel
		#define HaveTheLevel
	#endif
#endif

// Building for system level?

#if defined(UserOS)
	#if defined(HaveTheLevel)
		#error More than one build level defined!
	#else
		#define HaveUser
		#define HaveTheLevel
	#endif
#endif

// If the system is undefined, try to figure which system compiler is building this file.

#if !defined(HaveTheOS)

	#define MustGenOS

	// Is it Windows NT?

	#if defined(_MSC_VER) && defined(_WIN32)
		#define HaveNT
		#define HaveTheOS
	#endif

#endif

// If the build level is undefined, try to figure it out.

#if !defined(HaveTheLevel)

	#define MustGenLevel

	// Check for NT kernel level.

	#if defined(HaveNT) && defined(_IDWBUILD)
		#define HaveKernel
		#define HaveTheLevel
	#endif

	// Check for NT user level.

	#if defined(HaveNT) && (defined(_WINDOWS) || defined(_CONSOLE))
		#define HaveUser
		#define HaveTheLevel
	#endif

#endif

// Set the system type and build level to User Level NT if
// the OS type or build level isn't defined at this point
// and the user has enabled defaults.

#if defined(DefaultToUserNT)

	#if !defined(HaveTheOS)
		#define HaveNT
		#define HaveTheOS
	#endif

	#if !defined(HaveTheLevel)
		#define HaveUser
		#define HaveTheLevel
	#endif

#endif

// If the user didn't specify the OS, try to generate it.

#if defined(MustGenOS)

	#if defined(HaveTheOS) && defined(HaveTheLevel)
		
		#if defined(HaveKernel)

			#if defined(HaveLX)
				#define KernelLX
			#endif

			#if defined(HaveNT)
				#define KernelNT
			#endif

		#endif

		#if defined(HaveUser)

			#if defined(HaveLX)
				#define UserLX
			#endif

			#if defined(HaveNT)
				#define UserNT
			#endif

		#endif

	#else
		#undef HaveTheOS
	#endif

#endif

// If the user didn't specify the build level, try to generate it.

#if defined(MustGenLevel)

	#if defined(HaveTheLevel)
		
		#if defined(HaveKernel)
			#define KernelOS
		#endif

		#if defined(HaveUser)
			#define UserOS
		#endif

	#else
		#undef HaveTheLevel
	#endif

#endif

// Spit out errors if system type or build level is not set.

#if !defined(HaveTheOS)
	#error OS type must be defined!
#endif

#if !defined(HaveTheLevel)
	#error Build level must be defined!
#endif

// Make sure all local flags are undefined.

#undef HaveTheOS
#undef MustGenOS

#undef HaveLX
#undef HaveNT
#undef HavePT

#undef HaveTheLevel
#undef MustGenLevel

#undef HaveKernel
#undef HaveUser

// If building the kernel level NT driver and the system type isn't
// specified, assume the legacy Win NT driver is being built. 

#if defined(KernelNT)

	#if !defined(BuildWinNT) && !defined(BuildWinXP)
		#define BuildWinNT
	#endif

#endif

// If building for the 64 bit version of Windows XP, define BuildWin64.

#if defined(BuildWinXP) && defined(_WIN64)

	#define BuildWin64

#endif

#endif

