#pragma once

#include "CoreMinimal.h"
#include "X11Interface.generated.h"

USTRUCT(BlueprintType)
struct FX11WindowDetails
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    int WindowID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    int X;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    int Y;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    int Width;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    int Height;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    FString WindowName;
};
// TODO: Refactor to use UE types...
class X11Interface
{
public:
    TArray<FX11WindowDetails> GetWindowList();
    void GetWindowPixels(unsigned long target_window_id, uint8*& buffer, unsigned int *width, unsigned int *height, unsigned int *depth);
};