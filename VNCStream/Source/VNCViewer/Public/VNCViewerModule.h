// #pragma once

// #include "Templates/SharedPointer.h"
// #include "Modules/ModuleInterface.h"
// #include "Modules/ModuleManager.h"

// class IMediaEventSink;
// class IMediaPlayer;

// class IVNCViewerModule
// 	: public IModuleInterface
// {
// public:

// 	virtual bool IsInitialized() const = 0;

// 	/** Get this module */
// 	static IVNCViewerModule* Get()
// 	{
// 		static const FName ModuleName = "VNCViewer";
// 		return FModuleManager::GetModulePtr<IVNCViewerModule>(ModuleName);
// 	}

// 	/**
// 	 * TODO: Stream headless fork of TurboVNC viewer
// 	 * Simple implementation: streams pixels from X11 compositor window into Unreal Engine
// 	 */
// 	virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;

// public:

// 	/** Virtual destructor. */
// 	virtual ~IVNCViewerModule();
// };