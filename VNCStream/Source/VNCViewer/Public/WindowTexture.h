// WindowTexture.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "X11Interface.h"

#include "RHI.h"
#include "RHICommandList.h"
#include "RenderUtils.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "WindowTexture.generated.h"

/**
* A texture that can be rendered in Unreal Engine
*/
UCLASS(BlueprintType)
class VNCVIEWER_API UWindowTexture : public UObject
{
   GENERATED_BODY()
public:
   /**
    * The texture object that can be rendered in Unreal Engine
    */
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
   UTexture2D* Texture;

   UPROPERTY(BlueprintReadWrite, Category = "Texture")
   UMaterialInstanceDynamic* Material;

   UFUNCTION(BlueprintCallable, Category = "Texture")
   void SetupX11WindowTexture(int WindowID);

   UFUNCTION(BlueprintCallable, Category = "Texture")
   void UpdateX11WindowTexture(int WindowID);

   // TODO: Move to a different UClass?
   UFUNCTION(BlueprintCallable, Category = "Config")
   TArray<FX11WindowDetails> GetWindowList();

private:
   uint8* Buffer = nullptr;
   
   // TODO: Implement a function to copy the X11 Window Texture directly to 
   // Render Hardware Interface
   // (so a dynamic material doesn't need to be created every frame!)
   // FTextureRHIRef DestinationTexture;

   // https://forums.unrealengine.com/t/c-updating-texture-data/365946/10
   
};