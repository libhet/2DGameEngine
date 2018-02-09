#pragma once
#include "Image.h"
#include <vector>
#include <iterator>

class Animation {
public:
	Animation() = default;
	Animation(std::initializer_list<Image> list) : mImages(std::move(list)) {	}
	Animation(int size) { 
		mImages.reserve(size);
	}
	Animation(int size, int delay) { 
		mImages.reserve(size);
		mDelay = delay;
	}
	~Animation() = default;
	void addImage(Image const & image) {
		mImages.emplace_back(std::move(image));
	}
	void setDelay(int delay) {
		mDelay = delay;
	}
	int size() {
		return mImages.size();
	}

		class iterator 
			: std::iterator<std::forward_iterator_tag, Image>	
		{
		private:
			std::vector<Image>::iterator it;
		public:
			iterator(std::vector<Image>::iterator vit) 
				: it(vit) {}
			iterator & operator++() {
				++it;
				return *this;
			}
			Image & operator*() {
				return *it;
			}
			Image * operator->() {
				return &*(it);
			}
			bool operator!=(iterator _it) {
				return _it.it != it;
			}
		};
		iterator begin() {
			return iterator(mImages.begin());
		}
		iterator end() {
			return iterator(mImages.end());
		}
	
private:
	std::vector<Image> mImages;
	int mDelay = 1;
};
