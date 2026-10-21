// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalDoor.h"

// Sets default values
ASurvivalDoor::ASurvivalDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 3D modeli olusturur ve aktorun koku olarak ayarlar
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	//Kapi Baslangicta kapali olsun
	bIsOpen = false;

}

// Called when the game starts or when spawned
void ASurvivalDoor::BeginPlay()
{
	Super::BeginPlay();

	// Oyun baslarken kapinin durdugu aciyi hedef aci olarak kaydet
	TargetRotation = GetActorRotation();
	
}

// Called every frame
void ASurvivalDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Mevcut aciyi al
	FRotator CurrentRotation = GetActorRotation();

	// FMath::RInterpTo ile mevcut aciyi hedef aciya dogru yavasca dondur
	// Buradaki 5.0f degeri kapinin acilma hizidir
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);

	// Hesaplanan yeni aciyi kapiya uygula
	SetActorRotation(NewRotation);
}

void ASurvivalDoor::ToggleDoor()
{
	if (bIsOpen)
	{
		// Kapi acik ise kapat (-90 derece geri dondur)
		TargetRotation.Yaw -= 90.0f;
		bIsOpen = false;
	}
	else
	{
		// Kapi kapali ise ac (+90 derece dondur)
		TargetRotation.Yaw += 90.0f;
		bIsOpen = true;
	}
}

