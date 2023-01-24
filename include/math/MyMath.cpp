#include "MyMath.h"
#include "Vector4.h"



unsigned int Color::HsvaToRgba(float h, float s, float v, unsigned int a)
{
	Vector4 rgba;

	float H = fmodf(h, 360.0f);
	float V = Math::Clamp(v, 0.0f, 1.0f) * 255.0f;
	float S = Math::Clamp(s, 0.0f, 1.0f) * 255.0f;
	if (S <= 0) {
		rgba.x = v;
		rgba.y = v;
		rgba.z = v;
	}
	else {

		int Hi = (int)(H / 60.0f);
		float F = H / 60.0f - (float)Hi;
		float M = V * (1.0f - S / 255.0f);
		float N = V * (1.0f - S / 255.0f * F);
		float K = V * (1.0f - S / 255.0f * (1.0f - F));

		switch (Hi)
		{
		case 0:
			rgba.x = V;
			rgba.y = K;
			rgba.z = M;
			break;
		case 1:
			rgba.x = N;
			rgba.y = V;
			rgba.z = M;
			break;
		case 2:
			rgba.x = M;
			rgba.y = V;
			rgba.z = K;
			break;
		case 3:
			rgba.x = M;
			rgba.y = N;
			rgba.z = V;
			break;
		case 4:
			rgba.x = K;
			rgba.y = M;
			rgba.z = V;
			break;
		case 5:
		default:
			rgba.x = V;
			rgba.y = M;
			rgba.z = N;
			break;
		}
	}
	return Color::Create((unsigned int)rgba.x, (unsigned int)rgba.y, (unsigned int)rgba.z, a);
}

unsigned int Color::Lerp(float t, unsigned int start, unsigned int end)
{
	auto startColors = Detach(start);
	auto endColors = Detach(end);

	unsigned char r = static_cast<unsigned char>(Math::Lerp(t, static_cast<float>(startColors[0]), static_cast<float>(endColors[0])));
	unsigned char g = static_cast<unsigned char>(Math::Lerp(t, static_cast<float>(startColors[1]), static_cast<float>(endColors[1])));
	unsigned char b = static_cast<unsigned char>(Math::Lerp(t, static_cast<float>(startColors[2]), static_cast<float>(endColors[2])));
	unsigned char a = static_cast<unsigned char>(Math::Lerp(t, static_cast<float>(startColors[3]), static_cast<float>(endColors[3])));

	return Create(r, g, b, a);
}
