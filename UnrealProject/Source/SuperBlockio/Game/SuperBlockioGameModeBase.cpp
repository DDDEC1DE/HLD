// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperBlockioGameModeBase.h"
#include "Pawns/PlayerCharacter.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SuperBlockioGameStateBase.h"

ASuperBlockioGameModeBase::ASuperBlockioGameModeBase()
{
    
}

void ASuperBlockioGameModeBase::BeginPlay()
{
    Super::BeginPlay();

	//DECLARE a variable called World of type UWorld* const and assign it to the return value of GetWorld()
    const UWorld* World = GetWorld();
	//IF World NOT EQUAL to nullptr
   if(World != nullptr)
    {
    	//SET PlayerCharacter to the return value of Cast<APlayerCharacter>(World->GetFirstPlayerController()->GetPawn())
       PlayerCharacter = Cast<APlayerCharacter>(World->GetFirstPlayerController()->GetPawn());
    	//SET GameState to the return value of World->GetGameState<ASuperBlockioGameStateBase>()
       GameState = World->GetGameState<ASuperBlockioGameStateBase>();

    	//IF PlayerCharacter NOT nullptr
       if(PlayerCharacter != nullptr)
		{
			//CALL SetCheckpointLocation() on GameState passing in PlayerCharacter->GetActorLocation()
           GameState->SetCheckpointLocation(PlayerCharacter->GetActorLocation());
		}
    	//ENDIF
    }
}

void ASuperBlockioGameModeBase::OnCheckpoint(FVector FlagPos)
{
	//IF GameState NOT nullptr
   if(GameState != nullptr)
     {
     	 //CALL SetCheckpointLocation() on GameState passing in FlagPos
       GameState->SetCheckpointLocation(FlagPos);
     }
	//ENDIF
}

void ASuperBlockioGameModeBase::OnDeath()
{
    //IF GameState->GetLives() NOT EQUAL 0
    if (GameState->GetLives() != 0)
    {
        //CALL SetActorLocation() on PlayerCharacter passing in GameState->GetCheckpointLocation()
        PlayerCharacter->SetActorLocation(GameState->GetCheckpointLocation());
        //CALL IncreaseLives() on GameState passing in -1
        GameState->IncreaseLives(-1);
    }
    //ELSE
    else
    {
        /* If world not null, then cast Aplayer, however if the condition is not met, nullptr */
        //SET PlayerCharacter to the return of --> GetWorld() != nullptr ? Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : nullptr
        PlayerCharacter = GetWorld() != nullptr ? Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) : nullptr;
        //CALL Destroy() on PlayerCharacter
        PlayerCharacter->Destroy();
        /*Show GameOver*/
        //CALL GameOver()
        GameOver();

    }
}
//    // Get a reference to the player character
//    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
//
//    if (PlayerCharacter)
//    {
//        // Check if the player has lives left
//        if (GameState->GetLives() > 0)
//        {
//            // Get the checkpoint location from the game state
//            FVector CheckpointLocation = GameState->GetCheckpointLocation();
//
//            // Respawn the player character at the checkpoint
//            PlayerCharacter->SetActorLocation(CheckpointLocation);
//
//            // Decrease the player's lives
//            GameState->IncreaseLives(-1);
//        }
//        else
//        {
//            // Handle game over logic here
//            GameOver();
//        }
//    }
//}


void ASuperBlockioGameModeBase::GameOver()
{
	//CALL OnGameOver()
    OnGameOver();
}

void ASuperBlockioGameModeBase::Goal()
{
	//CALL OnGoal()
    OnGoal();
}



void ASuperBlockioGameModeBase::OnGoal_Implementation()
{
    
}

void ASuperBlockioGameModeBase::OnGameOver_Implementation()
{
    
}





