#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

UCLASS(BlueprintType)
class ARPGHUD : public AHUD
{
    GENERATED_BODY()
public:
    ARPGHUD();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class URPGHUDWidget> HUDWidgetClass;
private:
    UPROPERTY(Transient)
    class URPGHUDWidget* HUDWidget;
};
