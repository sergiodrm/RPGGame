#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "RPGStatusBarWidget.generated.h"

UCLASS(BlueprintType)
class URPGStatusBarWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    /** Begin UUserWidget methods */
    virtual void NativeConstruct() override;
    /** End UUserWidget methods */

    UFUNCTION(BlueprintCallable)
    void SetHealthPercentage(float healthPercentage);
    UFUNCTION(BlueprintCallable)
    void SetStaminaPercentage(float staminaPercentage);
    UFUNCTION(BlueprintCallable)
    void SetMagicPercentage(float magicPercentage);

protected:
    UFUNCTION()
    void OnHealthChanged(float oldValue, float newValue, float maxValue);
    UFUNCTION()
    void OnStaminaChanged(float oldValue, float newValue, float maxValue);
    UFUNCTION()
    void OnMagicChanged(float oldValue, float newValue, float maxValue);

private:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* StaminaBar;
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* MagicBar;
};
