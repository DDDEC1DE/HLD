// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/PlayerCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SUPERBLOCKIO_API AAICharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
    AAICharacter();

    virtual void Tick(float DetaTime) override;
    /* Let the guard go on patrol */
    UPROPERTY(EditInstanceOnly, Category = "AI")
    bool bPatrol;

    /* First of two patrol points to patrol between */
    UPROPERTY(EditAnywhere, Category = "AI")
    AActor* FirstPatrolPoint;

    /* Second of two patrol points to patrol between */
    UPROPERTY(EditAnywhere, Category = "AI")
    AActor* SecondPatrolPoint;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

 

    // The current point the actor is either moving to or standing at
    AActor* CurrentPatrolPoint;

    UFUNCTION() //WIthout this, the function will be inlined and optimized out
        void MoveToNextPatrolPoint();


    //Sensing
    UPROPERTY(VisibleAnywhere, Category = "Ai")
        class UPawnSensingComponent* PawnSensingComponent;

    UFUNCTION()
        void OnPawnSeen(APawn* SeenPawn);

    UFUNCTION()
        void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

    virtual void Shoot() override;

private:
    FTimerHandle SpawnProjectileTimer;

    APawn* TargetActor;
    FVector HeardLocation;
};
