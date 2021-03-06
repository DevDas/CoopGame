// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void BeginCrouch();
	void EndCrouch();

	//======== ADS Setup ========
	UFUNCTION(BlueprintCallable, Category = "Zoom")
	void BeginZoom();

	UFUNCTION(BlueprintCallable, Category = "Zoom")
	void EndZoom();

	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;

	float DefaultFOV; // Set During BeginPlay

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed;

	//======== Swap TPP to FPP ========
	UFUNCTION(BlueprintCallable, Category = "SwapCamera")
	void SwapCamera();

	class UCameraComponent* Select;

	//======= Camera Setup =======
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* TPPCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* FPPCameraComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Socket")
	FName HeadSocket;

	//======= Weapon Setup =======
	UPROPERTY(Replicated)
	class ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocket;

	//======= Health Setup =======
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComp")
	class USHealthComponent* HealthComp;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* HealthComponent, float Health, float HealthDelta,
		const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// Pawn Died Previously 
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bADS;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerADSOn();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerADSOff();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StopFire();
};