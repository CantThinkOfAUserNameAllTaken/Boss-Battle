// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<typename T>
class BOSSBATTLE_API BaseVariableStore
{


public:
	virtual void SetObject(T Object);


	UFUNCTION()
	virtual T GetRegisteredObject() const;

	virtual void Clear() = 0;

protected:
	UPROPERTY(VisibleAnywhere)
	T m_Object;


};


template<typename T>
inline void BaseVariableStore<T>::SetObject(T InObject)
{
	m_Object = InObject;
}

template<typename T>
T BaseVariableStore<T>::GetRegisteredObject() const
{
	return m_Object;
}
