#pragma once
#include "Animation.h"

class _RenderImpl {
public:
	_RenderImpl() = default;
	virtual ~_RenderImpl() = 0;

	virtual Image LoadImageImpl(char const * filename) = 0;
	virtual void DrawImageImpl(Image const & img) = 0;
};

class _Render {
public:
	_Render() = default;
	virtual ~_Render() = 0;

	virtual void InitWindow(int wWidth, int wHeight, char const * wTitle) {

	}

	virtual Image LoadImage(char const * filename) {
		_imp->LoadImageImpl(filename);
	}
	virtual void DrawImage(Image const & img) {
		_imp->DrawImageImpl(img);
	}

protected:
	_RenderImpl* GetRenderImp() {
		if (_imp == nullptr) {
			_imp = GraphicSystem::getImpl();
		}
		return _imp;
	}
private:
	_RenderImpl *_imp;
};



class Render : public _Render{
public:
	Render() = default;
	virtual ~Render() = default;

	virtual void InitWindow(int wWidth, int wHeight, char const * wTitle) {
		_Render::InitWindow(wWidth, wHeight, wTitle);
	}

	virtual Image LoadImage(char const * filename) {
		_Render::LoadImage(filename);
	}
	virtual void DrawImage(Image const & img) {
		_Render::DrawImage(img);
	}
};

enum TypeSystem {
	OpenGL,
	DirectX
};
class GraphicSystem {
protected:
	GraphicSystem() = default;
public:
	static void is(TypeSystem ts);
	static _RenderImpl* getImpl();
private:
	static _RenderImpl* _ts;
};

void GraphicSystem::is(TypeSystem ts)
{
	if (ts == OpenGL) {
		_ts = new RenderOpenGL();
	}
}

_RenderImpl * GraphicSystem::getImpl()
{
	return _ts;
}
