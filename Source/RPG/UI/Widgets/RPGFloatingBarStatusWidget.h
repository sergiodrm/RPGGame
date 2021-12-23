#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "RPGFloatingBarStatusWidget.generated.h"

UCLASS()
class URPGFloatingBarStatusWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetHealthBarPercent(float percent);

private:
    UPROPERTY(Transient, meta = (BindWidget))
    class UProgressBar* HealthBar;
};
