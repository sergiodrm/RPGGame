#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"

#include "RPGCharacterWidgetComponent.generated.h"

UCLASS()
class URPGCharacterWidgetComponent : public UWidgetComponent
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;

protected:
    UFUNCTION()
    void OnCharacterHealthChanged(float oldValue, float newValue, float maxValue);

protected:
    UPROPERTY(Transient)
    class URPGFloatingBarStatusWidget* FloatingWidget;
};
