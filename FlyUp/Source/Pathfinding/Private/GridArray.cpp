// Fill out your copyright notice in the Description page of Project Settings.


#include "GridArray.h"

void UGridArray::Initialize(int XSize, int YSize, int ZSize)
{
	this->XSize = XSize;
	this->YSize = YSize;
	this->ZSize = ZSize;

	Nodes.Empty();
	Nodes.Reserve(XSize * YSize * ZSize);
}

void UGridArray::Set(int X, int Y, int Z, const FNodeGrid& Node)
{
	Nodes.Insert(Node, CalculateInnerArrayId(X, Y, Z));
}

FNodeGrid& UGridArray::Get(int X, int Y, int Z)
{
	return Nodes[CalculateInnerArrayId(X, Y, Z)];
}

bool UGridArray::Contains(int X, int Y, int Z) const
{
	return X >=0 && X < XSize && Y >= 0 && Y < YSize && Z >= 0 && Z < ZSize;
}

int UGridArray::CalculateInnerArrayId(int X, int Y, int Z) const
{
	return Z + ZSize * Y + ZSize * YSize * X;
}
