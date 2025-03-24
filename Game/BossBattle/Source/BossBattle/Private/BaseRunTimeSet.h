// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template <typename T>
class BaseRunTimeSet {


public:
	/// <summary>
	/// Add an Object to the Array
	/// </summary>
	/// <param name="Object"></param>
	UFUNCTION(BlueprintCallable)
	void RegisterObject(T Object);

	/// <summary>
	/// Remove an ObJect From the Array
	/// </summary>
	/// <param name="Object"></param>
	UFUNCTION(BlueprintCallable)
	void DeregisterObject(T Object);

	UFUNCTION(BlueprintCallable)
	const TArray<T> GetRegisteredObjects();

	inline void ClearList();

protected:

	UPROPERTY(VisibleAnywhere)
	TArray<T> m_RegisteredObjects;


};


template<typename T>
inline void BaseRunTimeSet<T>::RegisterObject(T Object)
{
	m_RegisteredObjects.Add(Object);
}

template<typename T>
inline void BaseRunTimeSet<T>::DeregisterObject(T Object)
{
	m_RegisteredObjects.Remove(Object);
}

template<typename T>
inline void BaseRunTimeSet<T>::ClearList() {
	m_RegisteredObjects.Empty();
}

template<typename T>
const inline TArray<T> BaseRunTimeSet<T>::GetRegisteredObjects()
{
	return m_RegisteredObjects;
}
