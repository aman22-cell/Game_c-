// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	void ProcessInput(const uint8_t* keystate);
	virtual void ActorInput(const uint8_t* keyState) {};
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);
	void ComputworldTransform();
	


	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos,recomputWorldTransform=true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale, recomputWorldTransform = true; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation, recomputWorldTransform = true; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	Vector2 GetForword() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }
	Matrix4 GetWorldMatrix() const {return  WorldTransform; }
private:
	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;
	Matrix4 WorldTransform;
	bool recomputWorldTransform;
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
