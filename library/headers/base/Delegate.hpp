#pragma once

#include <utility>

template<typename ReturnType, typename... Params>
class Function {
	
	static ReturnType StaticPointerMethodStub(void* callee, Params ... params)
	{
		return reinterpret_cast<Signature>(callee)(std::forward<Params>(params)...);
	}
public:
	typedef ReturnType(*Signature)(Params ...);
	typedef ReturnType(*Func)(void*, Params ...);

	Function() {
		callee = nullptr;
		function = nullptr;
	}

	Function(Signature method) {
		callee = (void*)method;
		function = &StaticPointerMethodStub;
	}

	Function(const Function& other)
		: callee(other.callee)
		, function(other.function)
	{}

	void* callee;
	Func function;

	ReturnType operator()(Params ... params) {
		if(callee)
			function(callee, params ...);
	}
};

template<typename ... Params>
class Delegate {

};