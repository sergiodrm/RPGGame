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
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
public:
    UPROPERTY(BlueprintReadOnly, Category = "Vitality")
    FGameplayAttributeData Vitality {5.f};
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Vitality)
    UPROPERTY(BlueprintReadOnly, Category = "Endurance")
    FGameplayAttributeData Endurance {5.f};
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Endurance)
    UPROPERTY(BlueprintReadOnly, Category = "Strength")
    FGameplayAttributeData Strength {5.f};
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Strength)
    UPROPERTY(BlueprintReadOnly, Category = "Intelligence")
    FGameplayAttributeData Intelligence {5.f};
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Intelligence)

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)
    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Stamina)
    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxStamina)

    UPROPERTY(BlueprintReadOnly, Category = "Magic")
    FGameplayAttributeData Magic;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Magic)
    UPROPERTY(BlueprintReadOnly, Category = "Magic")
    FGameplayAttributeData MaxMagic;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMagic)

    UPROPERTY(BlueprintReadOnly, Category = "AttackPower")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, AttackPower)
    UPROPERTY(BlueprintReadOnly, Category = "Defense")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Defense)
};
