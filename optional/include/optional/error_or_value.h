#ifndef _ERROR_OR_VALUE_H_
#define _ERROR_OR_VALUE_H_

#include "optional.h"
#include <string>
#include <exception>

namespace optional
{
	template<typename T>
	class ErrorOrValue
	{
	private:
		OptionalValue<T> value_;
		std::exception_ptr error_;

	public:
		template<typename Arg, typename... Args, typename = typename std::enable_if<!std::is_same<Arg, std::exception_ptr>::value, void>::type>
		ErrorOrValue(Arg&& arg, Args&&... args)
		{
			value_.emplace(std::forward<Arg>(arg), std::forward<Args>(args)...);
		}

		explicit ErrorOrValue(const std::exception_ptr& error)
			: error_(error)
		{}

		ErrorOrValue(const ErrorOrValue& val)
			: value_(val.value_), error_(val.error_)
		{}

		ErrorOrValue& operator=(const ErrorOrValue& val)
		{
			value_ = val.value_;
			error_ = val.error_;
			return *this;
		}

		ErrorOrValue(ErrorOrValue&& val) noexcept
			: value_(std::move(val.value_)), error_(val.error_)
		{
			val.error_ = nullptr;
		}

		explicit operator bool() const noexcept { return static_cast<bool>(value_); }
		
		const T* ptr() const 
		{
			if (error_)
			{
				std::rethrow_exception(error_);
			}

			return value_.ptr();
		}

		T* ptr()
		{
			if (error_)
			{
				std::rethrow_exception(error_);
			}

			return value_.ptr();
		}

		const T& value() const { return *ptr(); }
		T& value() { return *ptr(); }

		std::string what() const
		{
			std::string str;

			if (error_)
			{
				try
				{
					std::rethrow_exception(error_);
				}
				catch (std::exception& ex)
				{
					str = ex.what();
				}
			}

			return str;
		}
	};
}

#endif