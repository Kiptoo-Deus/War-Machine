// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "Player.h"
#include"CrySchematyc/Env/IEnvRegistrar.h"
#include "GamePlugin.h"


#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CryCore/StaticInstanceList.h>



namespace
{
	static void RegisterPlayerComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CPlayerComponent));
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterPlayerComponent);
}

void CPlayerComponent::Initialize()
{
	m_pCameraComponent = m_pEntity->GetOrCreateComponent < Cry::DefaultComponents::CCameraComponent>();
	m_pInputComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CInputComponent>();
	m_pCharacterController = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCharacterControllerComponent>();
	m_pAdvancedAnimation = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CAdvancedAnimationComponent>();

	m_pInputComponent->RegisterAction("player", "moveforward", [this](int activtionMode, float value) {m_movementDelta.y = value; });//move player forward
	m_pInputComponent->BindAction("player", "moveforward", eAID_KeyboardMouse, eKI_W, true, true, false);

	m_pInputComponent->RegisterAction("player", "movebackward", [this](int activtionMode, float value) {m_movementDelta.y = -value; });//move player backward
	m_pInputComponent->BindAction("player", "movebackward", eAID_KeyboardMouse, eKI_S, true, true, false);

	m_pInputComponent->RegisterAction("player", "moveleft", [this](int activtionMode, float value) {m_movementDelta.y = -value; });//move player left
	m_pInputComponent->BindAction("player", "moveleft", eAID_KeyboardMouse, eKI_A, true, true, false);

	m_pInputComponent->RegisterAction("player", "moveright", [this](int activtionMode, float value) {m_movementDelta.y = value; });//move player right
	m_pInputComponent->BindAction("player", "moveright", eAID_KeyboardMouse, eKI_D, true, true, false);
	
}

Cry::Entity::EventFlags CPlayerComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::Update;
}

void CPlayerComponent::ProcessEvent(const SEntityEvent& event)
{
	switch (event.event)
	{
	case Cry::Entity::EEvent::Update:
	{
		m_pEntity->SetPos(m_pEntity->GetWorldPos() + Vec3(m_movementDelta.x, m_movementDelta.y, 0.0f));
	}
		break;
	}
}
