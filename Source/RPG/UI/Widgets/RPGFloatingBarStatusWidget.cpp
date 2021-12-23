#include "RPGFloatingBarStatusWidget.h"

#include "Components/ProgressBar.h"

void URPGFloatingBarStatusWidget::SetHealthBarPercent(float percent)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(percent);
    }
}
