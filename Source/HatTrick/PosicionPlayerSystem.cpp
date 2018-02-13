// Fill out your copyright notice in the Description page of Project Settings.

#include "PosicionPlayerSystem.h"



FVector APosicionPlayerSystem::PlayerPosition(EnumPlayerPosiciones posicion, ETeamEnum equipo)
{
	switch (equipo)
	{
	case ETeamEnum::TE_Buenos:
		switch (posicion)
		{
		case EnumPlayerPosiciones::Arquero:
			posicionStart = ArqueroStart->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa1:
			posicionStart = Defensa1Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa2:
			posicionStart = Defensa2Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa3:
			posicionStart = Defensa3Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa4:
			posicionStart = Defensa4Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo1:
			posicionStart = Mediocampo1Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo2:
			posicionStart = Mediocampo2Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo3:
			posicionStart = Mediocampo3Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo4:
			posicionStart = Mediocampo4Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo5:
			posicionStart = Mediocampo5Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque1:
			posicionStart = Ataque1Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque2:
			posicionStart = Ataque2Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque3:
			posicionStart = Ataque3Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque4:
			posicionStart = Ataque4Start->GetActorLocation();
			break;
		default:
			posicionStart = Mediocampo3Start->GetActorLocation();
			break;
		}
		break;
	case ETeamEnum::TE_Malos:
		switch (posicion)
		{
		case EnumPlayerPosiciones::Arquero:
			posicionStart = MaloArqueroStart->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa1:
			posicionStart = MaloDefensa1Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa2:
			posicionStart = MaloDefensa2Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa3:
			posicionStart = MaloDefensa3Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Defensa4:
			posicionStart = MaloDefensa4Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo1:
			posicionStart = MaloMediocampo1Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo2:
			posicionStart = MaloMediocampo2Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo3:
			posicionStart = MaloMediocampo3Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo4:
			posicionStart = MaloMediocampo4Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Mediocampo5:
			posicionStart = MaloMediocampo5Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque1:
			posicionStart = MaloAtaque1Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque2:
			posicionStart = MaloAtaque2Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque3:
			posicionStart = MaloAtaque3Start->GetActorLocation();
			break;
		case EnumPlayerPosiciones::Ataque4:
			posicionStart = MaloAtaque4Start->GetActorLocation();
			break;
		default:
			posicionStart = MaloMediocampo3Start->GetActorLocation();
			break;
		}
		break;
	default:
		break;
	}
		

	return FVector(posicionStart);
}

