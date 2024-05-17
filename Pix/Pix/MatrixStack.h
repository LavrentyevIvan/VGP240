#pragma once

#include <vector>
#include "MathHelper.h"

class MatrixStack
{
public:
	static MatrixStack* Get();

	void OnNewFrame();

	void PushTranslation(const Vector3& d);
	void PushRotationX(float radians);
	void PushRotationY(float radians);
	void PushRotationZ(float radians);
	void PushScaling(const Vector3& s);
	void PopMatrix();

	const Matrix4& GetTransform() const;

private:
	std::vector<Matrix4> mMatrices;
	Matrix4 mCombinedMatrix;
};