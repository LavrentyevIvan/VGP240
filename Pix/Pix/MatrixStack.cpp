#include "MatrixStack.h"

MatrixStack* MatrixStack::Get()
{
    static MatrixStack sInstance;
    return &sInstance;
}

void MatrixStack::OnNewFrame()
{
    mCombinedMatrix = Matrix4::Identity();
    mMatrices.clear();

}

void MatrixStack::PushTranslation(const Vector3& d)
{
    Matrix4 translationMatrix = Matrix4::Translation(d);
    mMatrices.push_back(translationMatrix);
    mCombinedMatrix = translationMatrix * mCombinedMatrix;


}

void MatrixStack::PushRotationX(float radians)
{
    Matrix4 rotMatrix = Matrix4::RotationX(radians);
    mMatrices.push_back(rotMatrix);
    mCombinedMatrix = rotMatrix * mCombinedMatrix;

}

void MatrixStack::PushRotationY(float radians)
{
    Matrix4 rotMatrix = Matrix4::RotationY(radians);
    mMatrices.push_back(rotMatrix);
    mCombinedMatrix = rotMatrix * mCombinedMatrix;
}
void MatrixStack::PushRotationZ(float radians)
{
    Matrix4 rotMatrix = Matrix4::RotationZ(radians);
    mMatrices.push_back(rotMatrix);
    mCombinedMatrix = rotMatrix * mCombinedMatrix;
}

void MatrixStack::PushScaling(const Vector3& s)
{
    Matrix4 scaleMatrix = Matrix4::Scaling(s);
    mMatrices.push_back(scaleMatrix);
    mCombinedMatrix = scaleMatrix * mCombinedMatrix;
}

void MatrixStack::PopMatrix()
{
    if (!mMatrices.empty())
    {
        Matrix4 matrix = mMatrices.back();
        mMatrices.pop_back();
        mCombinedMatrix = MathHelper::Inverse(matrix) * mCombinedMatrix;
    }
}

const Matrix4& MatrixStack::GetTransform() const
{
    return mCombinedMatrix;
}