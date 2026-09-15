// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "TimerManager.h"
#include "kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
	Health = MaxHealth;

	MaxHunger = 100.0f;
	Hunger = MaxHunger;

	MaxThirst = 100.0f;
	Thirst = MaxThirst;

	HungerDecayRate = 1.0f; // Hunger decreases by 1 unit per second
	ThirstDecayRate = 1.5f; // Thirst decreases by 1.5 units per second

}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
		GetWorld()->GetTimerManager().SetTimer(StatTimerHandle, this, &UAttributeComponent::HandleStatDecay, 1.0f, true);

}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UAttributeComponent::HandleStatDecay()
{
	// aclik ve susuzlugu dusur.(0'in altina dusurmeyi engeller)
	Hunger = FMath::Max(0.0f, Hunger - HungerDecayRate);
	Thirst = FMath::Max(0.0f, Thirst - ThirstDecayRate);

	// Log ekranına anlık değerleri yazdır
	UE_LOG(LogTemp, Warning, TEXT("Hunger: %f | Thirst: %f | Health: %f"), Hunger, Thirst, Health);

	// aclik susuzluk 0 olursa saglik dusur.
	if (Hunger <= 0.0f || Thirst <= 0.0f)
	{
		Health = FMath::Max(0.0f, Health - 2.0f); // Saglik 2 birim dusur.
	}

	UE_LOG(LogTemp, Warning, TEXT("Hunger: %f | Thirst: %f | Health: %f"), Hunger, Thirst, Health)
	CheckDeath(); // Can dususu sonrasi kontrol et.
}

void UAttributeComponent::AddThirst(float Amount)
{
	Thirst = FMath::Clamp(Thirst + Amount, 0.0f, MaxThirst);
}

void UAttributeComponent::Heal(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
}

void UAttributeComponent::AddHunger(float Amount)
{
	Hunger = FMath::Clamp(Hunger + Amount, 0.0f, MaxHunger);
}

void UAttributeComponent::CheckDeath()
{
	if (Health <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Karakter Öldü! Seviye Yeniden Başlatılıyor..."));

		UWorld* World = GetWorld();
		if (World)
		{
			FString CurrentLevelName = World->GetMapName();
			CurrentLevelName.RemoveFromStart(World->StreamingLevelsPrefix);

			UGameplayStatics::OpenLevel(World, FName(*CurrentLevelName));
		}
	}
}