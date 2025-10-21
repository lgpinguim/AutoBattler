#pragma once

#include <string>
#include "ECharacterClass.h"
#include "FGrid.h"
#include "FGridBox.h"

class FBattlefield;

class FCharacterBase
{
public:
	virtual ~FCharacterBase() = default;
	FCharacterBase();

	// Core functionality
	int ValidateCreationInput() const;
	std::string CreateCharacterName() const;

	void SetTarget(FCharacterBase* t);

	virtual void TakeDamage(float& Amount);
	void Die();

	bool CheckCloseTargets(FGrid* Battlefield) const;
	void MoveToEnemy(FBattlefield* Battlefield);
	virtual void Attack();

	// Movement
	void WalkLeft(FBattlefield* Battlefield, int& ListPosition);
	void WalkRight(FBattlefield* Battlefield, int& ListPosition);
	void WalkUp(FBattlefield* Battlefield, int& ListPosition);
	void WalkDown(FBattlefield* Battlefield, int& ListPosition);

protected:
	void Move(FBattlefield* Battlefield, int Offset, int& ListPosition, const std::string& Direction);

public:
	int PlayerIndex = 0;
	float Health = 100.f;
	float BaseDamage = 10.f;
	float DamageMultiplier = 2.f;
	int CriticalHitChance = 15;
	char Icon{ 'X' };
	bool bIsDead = false;
	ECharacterClass CharacterClass;
	FCharacterBase* Target = nullptr;
	FGridBox CurrentBox;
	std::string Name;
};
