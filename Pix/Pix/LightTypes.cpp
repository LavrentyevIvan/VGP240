#include "LightTypes.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
    Camera* camera = Camera::Get();
    MaterialManager* mm = MaterialManager::Get();


    X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient();

    Vector3 dirToLight = -mDirection;
    float dot = MathHelper::Dot(dirToLight, normal);
    X::Color colorDiffuse = mDiffuse * X::Math::Max(dot, 0.0f) * mm->GetMaterialDiffuse();

    Vector3 dirToEye = MathHelper::Normalize(camera->GetPosition()-position);
    Vector3 half = MathHelper::Normalize(dirToLight + dirToEye);
    float fallOff = pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess());
    X::Color colorSpecular = mSpecular * X::Math::Max(fallOff, 0.0f) * mm->GetMaterialSpecular();


    return colorAmbient + colorDiffuse + colorSpecular;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
    mDirection = direction;
}
