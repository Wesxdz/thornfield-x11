#pragma once

#include "Logging/LogMacros.h"

#define VNCVIEWER_SUPPORTED_PLATFORM (PLATFORM_LINUX && !UE_SERVER)

DECLARE_LOG_CATEGORY_EXTERN(LogVNCViewer, Log, All);