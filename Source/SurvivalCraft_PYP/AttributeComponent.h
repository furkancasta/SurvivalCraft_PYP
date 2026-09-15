// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCRAFT_PYP_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

	// Can kontrolu ve olum mantigi
	void CheckDeath();

protected:
	// Called when the game starts
	// Stats degiskenleri 
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float Hunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float MaxHunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float Thirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float MaxThirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float HungerDecayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes")
	float ThirstDecayRate;

	// Stamina degiskenleri
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes|stamina")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributes|stamina")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Stamina")
	float StaminaDrainRate = 10.0f; // Stamina decreases by 10 units per second when running
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes|Stamina")
	float StaminaRegenRate = 5.0f; // Stamina regenerates by 5 units per second when not running



	void HandleStatDecay();
	FTimerHandle StatTimerHandle;

public:	
	// Called every frame
	// Stat fonksiyonlari
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// stat ekleme fonksiyonlari
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddHunger(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddThirst(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Attributes|Stamina")
	void UseStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Attributes|Stamina")
	void RegenStamina(float DeltaTime);

};
