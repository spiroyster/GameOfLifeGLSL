#ifndef CGOL_HPP
#define CGOL_HPP

#include <vector>
#include <assert.h>

namespace cgol
{
	class field
	{
	public:
		field(unsigned int w, unsigned int h)
			:	data_(w * h, 0)
		{
		}

		// insert another field into this field... policy is what is done when oversizing...
		void insert(unsigned int x, unsigned int y, const field& f)
		{
			assert(x < f.w_ && x + f.w_ < w_);
			assert(y < f.h_ && y + f.h_ < h_);
			
			for (unsigned int i = 0; i < f.w_; ++i)
				for (unsigned int j = 0; j < f.h_; ++j)
					data_[y * w_ + x] = f.data()[j * f.w_ + i];
		}
		
		// iteration
		void iterate()
		{
			// ignore the border of single pixel...
			std::vector<unsigned char> d(data_.size(), 0);

			for (unsigned int i = 1; i < data_.size() - 1; ++i)
				for (unsigned int j = 1; j < data_.size() - 1; ++j)
				{
					unsigned char& c = data_[j * w_ + i];

					// Sum the neighbouring cells...
					unsigned int sum = 0;
					sum += static_cast<unsigned int>(cell(i - 1, j+1));	sum += static_cast<unsigned int>(cell(i, j+1));	sum += static_cast<unsigned int>(cell(i + 1, j+1));
					sum += static_cast<unsigned int>(cell(i - 1, j));													sum += static_cast<unsigned int>(cell(i + 1, j));
					sum += static_cast<unsigned int>(cell(i - 1, j-1));	sum += static_cast<unsigned int>(cell(i, j-1));	sum += static_cast<unsigned int>(cell(i + 1, j-1));

					if (c && (sum < 2 || sum > 3))
						c = 0;
					else if (sum == 3)
						c = 1;
				}

			data_.swap(d);
		}

		const std::vector<unsigned char>& data() const { return data_; }
		const unsigned char& cell(unsigned int x, unsigned int y) const { return data_[y * w_ + x]; }
		unsigned int iteration() const { return iteration_; }
		unsigned int width() const { return w_; }
		unsigned int height() const { return h_; }

	private:

		std::vector<unsigned char> data_;
		unsigned int w_;
		unsigned int h_;
		unsigned int iteration_;
	};

}	// namespace cgol

#endif // CGOL_HPP