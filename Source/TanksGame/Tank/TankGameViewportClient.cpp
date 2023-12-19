// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameViewportClient.h"

bool UTankGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
    if (EventArgs.IsGamepad())
    {
        FInputKeyEventArgs args(EventArgs);
        args.ControllerId += 1;
        // Map the gamepad to the next player index (so 1st controller is player index 1, etc.)
        return Super::InputKey(args);
    }
    else
    {
        return Super::InputKey(EventArgs);
    }
}
