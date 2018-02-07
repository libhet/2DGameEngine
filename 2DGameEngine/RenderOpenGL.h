#pragma once
#include "Render.h"

// ���������� ���������� ������� ������� ��� OpenGL

class RenderOpenGL : _RenderImpl {
public:
	RenderOpenGL() = default;
	virtual ~RenderOpenGL() = default;

	virtual Image LoadImageImpl() override;
	virtual void DrawImageImpl(Image img) override;
};