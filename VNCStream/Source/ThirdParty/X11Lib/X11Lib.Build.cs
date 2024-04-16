using System;
using System.IO;
using UnrealBuildTool;

public class X11Lib : ModuleRules
{
    public X11Lib(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        // /usr/include/X11/
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        
        // cp /usr/lib/x86_64-linux-gnu/libX11.so libX11.so
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libX11.so"));
    }
}
