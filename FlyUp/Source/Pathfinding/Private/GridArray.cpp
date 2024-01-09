// Fill out your copyright notice in the Description page of Project Settings.


#include "GridArray.h"

void UGridArray::Initialize(int GridXSize, int GridYSize, int GridZSize)
{
	XSize = GridXSize;
	YSize = GridYSize;
	ZSize = GridZSize;

	Nodes.Empty();
	Nodes.Reserve(GridXSize * GridYSize * GridZSize);
}

void UGridArray::Empty()
{
	Nodes.Empty();
	XSize = 0;
	YSize = 0;
	ZSize = 0;
}

void UGridArray::Set(int X, int Y, int Z, const FNodeGrid& Node)
{
	Nodes.Insert(Node, CalculateInnerArrayId(X, Y, Z));
}

const FNodeGrid* UGridArray::Get(int X, int Y, int Z) const
{
	return &Nodes[CalculateInnerArrayId(X, Y, Z)];
}

bool UGridArray::Contains(int X, int Y, int Z) const
{
	return X >=0 && X < XSize && Y >= 0 && Y < YSize && Z >= 0 && Z < ZSize;
}

int UGridArray::GetXSize() const
{
	return XSize;
}

int UGridArray::GetYSize() const
{
	return YSize;
}

int UGridArray::GetZSize() const
{
	return ZSize;
}

TArray<FNodeGrid>::RangedForIteratorType UGridArray::begin()
{
	return Nodes.begin();
}

TArray<FNodeGrid>::RangedForIteratorType UGridArray::end()
{
	return Nodes.end();
}

int UGridArray::CalculateInnerArrayId(int X, int Y, int Z) const
{
	return Z + ZSize * Y + ZSize * YSize * X;
}
