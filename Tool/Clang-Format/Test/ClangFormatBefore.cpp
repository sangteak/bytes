//
//
// 전처리 지시자
//
//

// 전처리 지시문 #if... 내에서 들여쓰기 되어야 합니다.
#ifndef INDENT_DEFINE_
#define INDENT_DEFINE_
#endif // end INDENT_DEFINE_

#if defined(__GNUC__)
#if __GNUC__ > 3
#define INDENT_DEFINE_TEST_
#endif
#endif

// 들여쓰기 단계에 맞춰서 수정됩니다.
#if  defined(_WIN32)   ||   defined(_WIN64)
#		define NOMINMAX
# define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#  include <Windows.h>
#endif // end _WIN32 or _WIN64

//
//
// 헤더
//
//
#include  <iostream>     // 공백   
# include <vector>
#include <map>
#include <functional>
#include <algorithm>

//
//
// 주석
//
//

void Comment() {
	// 주석은 앞에 공백 한칸 고정.

	//이 주석은 공백이 추가되어야 합니다.

	//      이 주석은 앞에 공백을 하나 남기고 땡겨져야합니다.


	// 이 주석은 위로 한줄 땡겨져야 합니다.

	int a = 10;   //    이 후행 주석도 공백을 하나 남기고 땡겨져야합니다.
}

//
//
// 네임스페이스
//
//

// 네임스페이스 줄 끝에는 주석이 추가 되어야 합니다.
namespace format::test {
	// 내용이 아무것도 없으면 네임스페이스 끝에 주석이 추가되지 않아서 빈 클래스를 추가합니다.
	// 네임스페이스는 들여쓰기 하지 않음으로 앞으로 땡겨집니다.
	class EmptyClass {
	};
}

// 네임 스페이스 시작 중괄호는 namespace 키워드와 같은줄에 있도록 땡겨져야 합니다.
namespace format::brace
{
// 내용이 아무것도 없으면 네임스페이스 끝에 주석이 추가되지 않아서 빈 클래스를 추가합니다.
class EmptyClass {
};
}

// 스타일상 네임스페이스는 중첩으로 사용하지 않기로 했습니다.
// 포맷은 들여쓰기 없이 모두 앞으로 땡겨져야 합니다.
namespace format::outer {
	namespace inner {
		class EmptyClass {
		};
	}
}

//
//
// 열거형
//
//

// 열거형 시작 중괄호는 enum 키워드와 같은 라인에 있어야 합니다.
enum class EnumBrace
{
};

// 열거형 정의는 간단한 것이라도 한줄에 하지 않습니다.
// 모두 개행 됩니다.
enum class EnumOneLine { kVini, kMini, kDutti, kFlame, };

// 콤마는 뒤쪽에 위치, 대입연산자 주변으로 공백은 하나씩 두도록 수정합니다.
enum class EnumSmilemates {
	kVini = 10
	, kMini= 20
	, kDutti =30
	, kFlame =  40
	, kCloody=50
};

//
//
// 매크로
//
//

#define DEFINE_MACRO           0            // 공백

//
//
// 변수 및 배열 초기화
//
//

void VariableInitialize()  {
	// 정상
	int variable_init = 10;

	// = 앞뒤 공백 추가됩니다.
	int value=10;

	// 정상
	int* pointer_value = &value;
	int& reference_value = value;

	// 포인터, 레퍼런스 기호는 타입에 붙습니다.
	int *pointer_value1 = &value;
	int &reference_value1 = value;
	int * pointer_value2 = &value;
	int & reference_value2 = value;

	// 정상
	std::vector<int> vector_o{1, 2, 3, 4};
	int* arr_o = new int[3]{1, 2, 3};
	delete[] arr_o;
	

	// { } 앞쪽과 안쪽 공백이 제거됩니다.
	std::vector<int> vector_x { 1, 2, 3, 4 };
	int* arr_x = new int[3] { 1, 2, 3 };
	delete [] arr_x;

	// 배열 이름과 [] 사이에 공백이 제거됩니다.
	int arr1[5][5];
	int arr2 [5][5];
}

// 비트필드 콜론 앞뒤로 공백 한칸.
struct BitField {
	unsigned int num4 : 8;
	unsigned int num3: 8;
	unsigned int num2 :8;
	unsigned int num1:8;
};

//
//
// 타입 재정의
//
//

// template 키워드 이후에는 무조건 개행됩니다.
template <typename Element> using _myvector_t = std::vector<Element>;

// 정상
using _property_map_t = std::map<int, int>; 

//
//
// 함수
//
//

// 여는 소괄호 앞에 공백은 제거됩니다.
void MyFunction1() {
	
	// 함수 정의 내 첫라인은 비워둘 수 없어서 땡겨집니다.
}

// 정상. 소괄호 사이에는 공백이 존재해서는 안됩니다.
void MyFunction2(int a, int b);
// 소괄호 사이에 공백이 제거됩니다.
void MyFunction3( int a, int b );
void MyFunction4( int a, int b);
void MyFunction5(int a, int b );


// 정상. 닫는 소괄호와 여는 중괄호는 항상 마지막 인자와 같은 라인에 존재해야합니다.
void Initialize(
	const int& id,
	const std::vector<int>& data) {
}

// 한줄 정상
void ManyParamFunction1(const int& a, const int& b, const int& c, const int& d, const int& e) {
}

// 첫 파라메터를 개행하지 않아 한줄로 변경됩니다.
void ManyParamFunction2(const int& a,
	const int& b,
	const int& c,
	const int& d,
	const int& e) {
}

// 정상
bool ManyParamFunction3(
	const int& a,
	const int& b,
	const int& c,
	const int& d,
	const int& e) {
	return true;
}

// 함수 호출
void ManyParamFunctionCall() {
	// 한줄 정상
	ManyParamFunction3(1, 2, 3, 4, 5);

	// 마찬가지로 첫 파라메터를 개행하지 않아 한줄로 변경됩니다.
	ManyParamFunction3(1,
	2, 3, 4, 5);
	ManyParamFunction3(1,
		2,
		3,
		4,
		5);

	// 정상
	ManyParamFunction3(
		1,
		2,
		3,
		4,
		5);

	// 첫 파라메터만 개행하면 파라메터를 한줄에 하나씩 두도록 변경됩니다.
	ManyParamFunction3(
		1, 2, 3, 4 ,5);
}

void LambdaParameterFunction(std::function<void()> func, int param) {
}

void LambdaParameterFunctionCall() {
	// 람다 파라메터를 가진 함수 호출 정상.
	LambdaParameterFunction(
		[]() {
			std::cout << "called" << std::endl;
		},
		7777);

	// 람다 파라메터를 개행하지 않아서 이상하게 포맷팅 됩니다.
	LambdaParameterFunction([]() {
			std::cout << "called" << std::endl;
	}, 7777);
}

using _long_long_long_long_long_long_return_type_t = int;

// 리턴타입이 길어져서 개행을 한 경우, 개행 후 들여쓰기 하지 않습니다.
_long_long_long_long_long_long_return_type_t
	LongReturnFunction() {
		return 0;
	}

//
//
// if문
//
//

void IfFunction() {
	bool cond = true;
	bool cond1 = true;
	bool cond2 = true;
	bool cond3 = true;
	bool cond4 = true;

	// 정상
	if (cond) {
	}

	// if 키워드와 여는 소괄호 사이 공백
	if(cond) {
	}

	// 소괄호 사이에 공백.
	if ( cond ) {
	}

	if ( cond) {
	}

	if (cond ) {
	}

	// 여는 소괄호 위치.
	if
	(cond) {
	}

	// 정상
	if (cond1
		&& cond2) {
	}

	// 닫는 소괄호가 마지막 조건과 같은 줄에 있어야 합니다.
	if (cond1
		&& cond2
		) {
	}

	// 닫는 소괄호와 여는 중괄호 사이에 공백이 있어야 합니다.
	if (cond){
	}

	// 여는 중괄호가 닫는 소괄호와 같은 줄에 있어야 합니다.
	if (cond)
	{
	}

	// else는 닫는 중괄호에서 개행합니다.
	if (cond1) {
	} else if (cond2) {
	} else {
	}

	// 짧은 조건문도 중괄호를 사용하며 개행해야합니다.
	if (cond) { return; }

	// 중괄호가 생성되고 개행됩니다.
	if (cond) return;

	// 중괄호 누락시 중괄호 생성됩니다.
	if (cond)
		return;

	// 정상
	if (true == cond1
		&& true == cond2
		&& true == cond3
		&& true == cond4) {
	}

	// 한줄로 변경됩니다.
	if (true == cond1 &&
		true == cond2 &&
		true == cond3 &&
		true == cond4) {
	}

	// if문 내에서 함수 호출 시 파라메터 모두 한줄로 수정됩니다.
	if (false == ManyParamFunction3(
		1,
		2,
		3,
		4,
		5)) {

	}
}

//
//
// 삼항 연산자
//
//

void TernaryOperators() {
	bool a = true;
	bool b = true;

	// 정상
	a > b ? a : b;

	// 공백 확인
	a > b? a : b;
	a > b ?a : b;
	a > b ? a: b;
	a > b ? a :b;

	// 한줄로 땡겨집니다.
	a > b ?
	a :	b;

	// 삼항연산자 기호가 앞으로 가도록 포맷팅 됩니다.
	a > b
	? a : b;
}

//
//
// for, while 문
//
//

void ForWhile() {
	// 정상
	for (auto i = 0; i < 10; ++i) {
	}

	// 공백 확인
	for(auto i = 0; i < 10; ++i) {
	}
	for ( auto i = 0; i < 10; ++i ) {
	}
	for ( auto i = 0; i < 10; ++i) {
	}
	for (auto i = 0; i < 10; ++i ) {
	}

	int count = 10;

	// 정상
	while (10 > count) {
	}

	// 공백 확인
	while(10 > count) {
	}
	while( 10 > count ) {
	}
	while( 10 > count) {
	}
	while(10 > count ) {
	}

	// 여는 중괄호는 닫는 소괄호와 같은 줄에 있어야 합니다.
	for (auto i = 0; i < 10; ++i) 
	{
	}

	while (10 > count)
	{
	}

	// for문은 세미콜론 뒤에 공백을 사용합니다.
	for (auto i = 0;i < 10;++i) {
	}

	// 연산자들 사이에 공백을 사용합니다.
	for (auto i=0; i<10; ++i) {
	}
	while (10>count){
	}

	// 중괄호가 없는 경우 추가해줍니다.
	for (auto i = 0; i < 10; ++i);
	while (10 > count);

	// 범위 for 사용시 : 앞뒤에 공백을 사용합니다.
	std::vector<int> container;
	for (auto i:container) {
	}
}

//
//
// do/while 문
//
//

void DoWhile() {
	bool cond = true;

	// 정상
	do {
	} while (cond);

	// 공백과 개행 확인. 포맷팅 후 모두 정상으로 수정 되어야 합니다.
	do{
	} while (cond);

	do
	{
	} while (cond);

	do {
	}
	while (cond);

	do {
	}while(cond);

	do {
	}while (cond);

	do {
	} while(cond);

	do {
	} while ( cond );
}

//
//
// switch 문
//
//

void Switch() {
	int cond = 1;

	// 정상
	switch (cond) {
		case 1: {
			break;
		}

		default: {
			break;
		}
	}
	
	// 공백과 중괄호 위치 확인
	switch(cond){
	}
	switch (cond){
	}
	switch (cond) 
	{
	}
}

//
//
// try/catch 문
//
//

void TryCatch() {
	// 정상
	try {
	}
	catch (...) {
	}

	// 공백과 중괄호 위치 확인.
	try
	{
	}
	catch (...)
	{
	}

	try{
	}
	catch (...){
	}

	try {
	} catch (...) {
	}
}

//
//
// 클래스
//
//

class MyClass {
public:
	// 생성자 초기화리스트는 무조건 한라인에 하나씩 개행됩니다.
	MyClass() : value1_(100), value2_(200), value3_(300), value4_(400) {
	}
protected: // 첫 번째 접근제한자를 제외한 다른 접근제한자 위에는 빈줄이 있어야 합니다.
	void ProtectedMemberFunction() {
	}

private:
	int value1_ = 0;
	int value2_ = 0;
	int value3_ = 0;
	int value4_ = 0;
};

class Base {
};

class AfterColon {
};

// 한줄 기본 형식 포맷팅 후에 변화 없습니다.
class BreakInheritanceList1 : public AfterColon, public Base {
};

// 아래 같은 세 가지 케이스들은 한줄로 수정됩니다.
class BreakInheritanceList2
: public AfterColon, public Base {
};

class BreakInheritanceList3 : public AfterColon
, public Base {
};

class BreakInheritanceList4 : public AfterColon,
public Base {
};

// AfterColon 기본 형식
class BreakInheritanceList5 :
	public AfterColon,
	public Base {
};

// : 이후에 개행하면 AfterColon 기본 형식으로 수정됩니다.
class BreakInheritanceList6 :
public AfterColon, public Base {
};

//
//
// 람다 표현식
//
//

// 함수쪽에 람다 파라메터 내용이 있어서 생략합니다.

//
//
// 템플릿
//
//

// 정상
template <typename T>
T TemplateFunction1() {
}

// 공백 확인
template<typename T>
T TemplateFunction2() {
}

// template 이후 줄바꿈 확인
template <typename T> T TemplateFunction3() {
}

void Template() {
	short arg = 1;

	// 정상
	static_cast<int>(arg);
	std::function<void(int)> fct1;

	// 공백 확인
	static_cast< int >(arg);
	std::function< void(int) > fct2;
}

int main() {
	std::cout << " hello, world" << std::endl;
}