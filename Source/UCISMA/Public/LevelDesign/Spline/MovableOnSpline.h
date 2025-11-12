// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovableOnSpline.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovableOnSpline : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UCISMA_API IMovableOnSpline
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetOnSpline(class ASplineController*, int32 ArrayIndex) = 0;
};
