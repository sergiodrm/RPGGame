#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class URPGAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    URPGAttributeSet();


    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)
};
