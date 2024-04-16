#include "VNCViewerModule.h"
#include "VNCViewerCommon.h"

// #if VNCVIEWER_SUPPORTED_PLATFORM
// #endif

DEFINE_LOG_CATEGORY(LogVNCViewer)

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVNCViewer : public IModuleInterface
{
protected:
    bool Initialized;
public:
    virtual void StartupModule() override
    {
        Initialized = true;
    }

    virtual void ShutdownModule() override
    {
        Initialized = false;
    }
};


IMPLEMENT_MODULE(FVNCViewer, VNCViewer);