#include "RPGHUD.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/RPGHUDWidget.h"

ARPGHUD::ARPGHUD()
{ }

void ARPGHUD::BeginPlay()
{
    Super::BeginPlay();

    HUDWidget = CreateWidget<URPGHUDWidget>(GetWorld(), HUDWidgetClass);
    if (HUDWidget)
    {
        HUDWidget->AddToViewport();
    }
}
