#ifndef _OPTIONAL_H_
#define _OPTIONAL_H_

#include <type_traits>
#include <stdexcept>

#ifdef _WIN32
#pragma warning(disable :  4522)
#endif

namespace optional
{
	template<typename T>
	class OptionalValue
	{
	private:
		typename std::aligned_storage<sizeof(T), alignof(T)>::type value_;
		bool init_{ false };

	public:
		OptionalValue()
		{}

		OptionalValue(T&& val) noexcept(std::is_nothrow_move_constructible<T>::value)
		{
			construct(std::move(val));
		}

		OptionalValue(const T& val) noexcept(std::is_nothrow_copy_constructible<T>::value)
		{
			construct(val);
		}

		OptionalValue(const OptionalValue& val) noexcept(std::is_nothrow_copy_constructible<T>::value)
		{
			if (val.init_)
			{
				construct(val.value());
			}
		}

		OptionalValue(OptionalValue&& val) noexcept(std::is_nothrow_move_constructible<T>::value)
		{
			if (val.init_)
			{
				construct(std::move(val.value()));
				val.init_ = false;
			}
		}

		OptionalValue& operator=(const OptionalValue& val) noexcept(std::is_nothrow_copy_constructible<T>::value)
		{
			if (val.init_)
			{
				if (init_)
				{
					value() = val.value();
				}
				else
				{
					construct(val.value());
				}
			}
			else
			{
				clear();
			}

			return *this;
		}

		OptionalValue& operator=(OptionalValue&& val) noexcept(std::is_nothrow_move_constructible<T>::value)
		{
			if (val.init_)
			{
				if (init_)
				{
					value() = std::move(val.value());
				}
				else
				{
					construct(std::move(val.value()));
				}
			}
			else
			{
				clear();
			}

			val.init_ = false;
			return *this;
		}

		~OptionalValue()
		{
			clear();
		}

		explicit operator bool() const noexcept { return init_; }

		OptionalValue& operator=(T&& val)
		{
			construct(std::forward<T>(val));
			return *this;
		}

		OptionalValue& operator=(const T& val)
		{
			construct(val);
			return *this;
		}

		T* ptr()
		{
			if (!init_)
			{
				throw std::logic_error("attempted access to an uninitialized value");
			}

			return reinterpret_cast<T*>(&value_);
		}

		const T* ptr() const
		{
			if (!init_)
			{
				throw std::logic_error("attempted access to an uninitialized value");
			}

			return reinterpret_cast<const T*>(&value_);
		}

		const T& value() const { return *ptr(); }
		T& value() { return *ptr(); }

		template<typename... Args>
		void emplace(Args&&... args)
		{
			clear();
			::new (&value_) T(std::forward<Args>(args)...);
			init_ = true;
		}

		void clear()
		{
			if (init_)
			{
				reinterpret_cast<T*>(&value_)->~T();
				init_ = false;
			}
		}

		private:
			template<typename... Args>
			void construct(Args&&... args)
			{
				::new (&value_) T(std::forward<Args>(args)...);
				init_ = true;
			}
	};
}

#endif