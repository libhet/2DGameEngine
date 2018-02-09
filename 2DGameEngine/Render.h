#pragma once
#include "Animation.h"

class _RenderImpl {
public:
	_RenderImpl() = default;
	virtual ~_RenderImpl() = default;;

	virtual void	InitWindow(int wWidth, int wHeight, char const * wTitle) = 0;
	virtual Image	LoadImageImpl(char const * filename) = 0;
	virtual void	DrawImageImpl(Image const & img) = 0;
	virtual void	DrawAnimationImpl(Animation & ani) = 0;
};

class _Render {
public:
	_Render(_RenderImpl* impl) {
		_imp = impl;
	}
	virtual ~_Render() = default;;

	virtual void	InitWindow(int wWidth, int wHeight, char const * wTitle) {
		_imp->InitWindow(wWidth, wHeight, wTitle);
	}
	virtual Image	LoadImage(char const * filename) {
		return _imp->LoadImageImpl(filename);
	}
	virtual void	DrawImage(Image const & img) {
		_imp->DrawImageImpl(img);
	}
	virtual void	DrawAnimation(Animation & ani) {
		_imp->DrawAnimationImpl(ani);
	}

protected:
	_RenderImpl* GetRenderImp() {}
private:
	_RenderImpl *_imp;
};

class Render : public _Render{
public:
	Render(_RenderImpl* impl) : _Render(impl){}
	~Render() = default;

	virtual void	InitWindow(int wWidth, int wHeight, char const * wTitle) {
		_Render::InitWindow(wWidth, wHeight, wTitle);
	}
	virtual Image	LoadImage(char const * filename) {
		return _Render::LoadImage(filename);
	}
	virtual void	DrawImage(Image const & img) {
		_Render::DrawImage(img);
	}
	virtual void	DrawAnimation(Animation & ani) {
		_Render::DrawAnimation(ani);
	}
};


