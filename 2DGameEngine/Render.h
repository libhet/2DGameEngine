//#pragma once
//
//
//class _Render {
//public:
//	_Render() = default;
//	virtual ~_Render() = 0;
//
//	virtual Image LoadImage();
//	virtual void DrawImage(Image cosnt & img);
//
//protected:
//	_RenderImpl* GetRenderImp();
//private:
//	_RenderImpl *_imp;
//};
//
//class _RenderImpl {
//public:
//	_RenderImpl() = default;
//	virtual ~_RenderImpl() = 0;
//
//	virtual Image LoadImageImpl();
//	virtual void DrawImageImpl(Image const & img);
//};
//
//class Render : _Render{
//public:
//	Render() = default;
//	virtual ~Render() = default;
//
//	virtual Image LoadImage();
//	virtual void DrawImage(Image const & img);
//};