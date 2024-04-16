// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class VNCViewer : ModuleRules
	{
		public VNCViewer(ReadOnlyTargetRules Target) : base(Target)
		{
            bEnableExceptions = true;

            DynamicallyLoadedModuleNames.AddRange(
				new string[] {
				});

            PublicDependencyModuleNames.AddRange(
                new string[] {
                    });

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
                    "Engine",
                    "MediaUtils",
					"Projects",
					"RenderCore",
                    "RHI",
					"X11Lib"
                });


            PrivateIncludePathModuleNames.AddRange(
				new string[] {
					"X11Lib"
				});

			if (Target.bCompileAgainstEngine)
			{
				PrivateDependencyModuleNames.Add("Engine");
				PrivateDependencyModuleNames.Add("HeadMountedDisplay");
			}
			
			PublicDefinitions.Add("VNC_VIEWER_VERSION=1");
		}
	}
}
