#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGHUDWidget.generated.h"

UCLASS(BlueprintType)
class URPGHUDWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    FORCEINLINE class URPGStatusBarWidget* GetStatusBarWidget() const { return StatusBar; }

protected:
private:
    UPROPERTY(meta = (BindWidget))
    class URPGStatusBarWidget* StatusBar;
};
