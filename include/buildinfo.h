/**
 * @file buildinfo.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#pragma once

#include "types.h"

#ifndef __BUILD_ARCH__
# define __BUILD_ARCH__ "unknown"
#endif /* __BUILD_ARCH__ */

#ifndef __BUILD_GITREF__
# define __BUILD_GITREF__ "unknown"
#endif /* __BUILD_GITREF__ */

#ifndef __BUILD_UNAME__
# define __BUILD_UNAME__ "unknown"
#endif /* __BUILD_UNAME__ */

#ifndef __BUILD_DATE__
# define __BUILD_DATE__ "unknown"
#endif /* __BUILD_DATE__ */

#ifndef __BUILD_VERSION__
# define __BUILD_VERSION__ "unknown"
#endif /* __BUILD_VERSION__ */

#ifndef __QEMU__
# define __QEMU__ FALSE
#endif /* __QEMU__ */

#ifndef __SERIAL_COLORS__
# define __SERIAL_COLORS__ FALSE
#endif /* __SERIAL_COLORS__ */
